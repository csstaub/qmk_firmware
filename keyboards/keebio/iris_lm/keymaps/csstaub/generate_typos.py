#!/usr/bin/env python3
"""Generate a QMK autocorrect dictionary of mechanical typos.

Produces typos that stem from fast typing on a QWERTY keyboard:
  - Transpositions (swapping adjacent letters)
  - Dropped letters (skipping a keypress)
  - Adjacent-key errors (hitting a QWERTY neighbor)

Uses /usr/share/dict/words to filter out typos that are real English words.

Usage:
    python3 generate_typos.py > autocorrect_dictionary.txt
"""

import sys
from collections import defaultdict

# ── QWERTY adjacency map ────────────────────────────────────────────────────
# For each key, its immediate neighbors on a standard QWERTY layout.
QWERTY_NEIGHBORS = {
    'q': 'wa',
    'w': 'qeas',
    'e': 'wrds',
    'r': 'etdf',
    't': 'ryfg',
    'y': 'tugh',
    'u': 'yijh',
    'i': 'uojk',
    'o': 'iplk',
    'p': 'ol',
    'a': 'qwsz',
    's': 'wedxza',
    'd': 'erfcxs',
    'f': 'rtgvcd',
    'g': 'tyhbvf',
    'h': 'yujnbg',
    'j': 'uikmnh',
    'k': 'iolmj',
    'l': 'opk',
    'z': 'asx',
    'x': 'zsdc',
    'c': 'xdfv',
    'v': 'cfgb',
    'b': 'vghn',
    'n': 'bhjm',
    'm': 'njk',
}

# ── Top ~200 most common English words (4+ letters) ─────────────────────────
# Sourced from standard English word frequency lists.
COMMON_WORDS = [
    'that', 'with', 'have', 'this', 'will', 'your', 'from', 'they',
    'been', 'said', 'each', 'what', 'which', 'their', 'time', 'about',
    'would', 'make', 'like', 'just', 'over', 'such', 'take', 'year',
    'them', 'some', 'want', 'when', 'give', 'most', 'only', 'tell',
    'also', 'back', 'after', 'work', 'first', 'well', 'even', 'ways',
    'than', 'call', 'come', 'made', 'find', 'long', 'here', 'thing',
    'many', 'then', 'look', 'down', 'should', 'need', 'move', 'very',
    'much', 'know', 'still', 'good', 'life', 'into', 'does', 'help',
    'keep', 'today', 'check', 'return', 'update', 'switch', 'length',
    'place', 'where', 'same', 'being', 'world', 'again', 'never',
    'under', 'last', 'might', 'while', 'house', 'great', 'before',
    'hand', 'high', 'line', 'right', 'turn', 'home', 'read', 'play',
    'found', 'live', 'left', 'away', 'between', 'city', 'tree',
    'since', 'another', 'people', 'there', 'other', 'could', 'early',
    'these', 'little', 'through', 'change', 'point', 'number',
    'every', 'water', 'write', 'think', 'state', 'different', 'those',
    'start', 'story', 'until', 'three', 'often', 'second', 'later',
    'group', 'began', 'always', 'music', 'because', 'something',
    'both', 'part', 'once', 'large', 'must', 'name', 'really',
    'country', 'small', 'school', 'night', 'head', 'word', 'kind',
    'power', 'began', 'young', 'important', 'family', 'next', 'seem',
    'hard', 'open', 'example', 'begin', 'while', 'together', 'next',
    'white', 'children', 'during', 'able', 'enough', 'almost',
    'above', 'nothing', 'against', 'already', 'though', 'around',
    'without', 'whole', 'system', 'better', 'going', 'using',
    'having', 'doing', 'under', 'before', 'after', 'called',
    'given', 'several', 'possible', 'within', 'across', 'might',
    'however', 'rather', 'become', 'problem', 'whether', 'maybe',
    'anything', 'itself', 'someone', 'everything', 'morning',
    'actually', 'probably', 'himself', 'words', 'things', 'getting',
    'working', 'looking', 'making', 'trying', 'coming', 'taking',
    'wanted', 'started', 'turned', 'needed', 'asked', 'seemed',
    'following', 'different', 'running', 'usually', 'others',
    'years', 'times', 'thought', 'really', 'already',
]


def load_dictionary(path='/usr/share/dict/words'):
    """Load system dictionary as a set of lowercase words."""
    words = set()
    with open(path) as f:
        for line in f:
            words.add(line.strip().lower())
    return words


def gen_transpositions(word):
    """Swap each pair of adjacent characters."""
    for i in range(len(word) - 1):
        typo = word[:i] + word[i+1] + word[i] + word[i+2:]
        if typo != word:
            yield typo


def gen_dropped_letters(word):
    """Remove each character one at a time."""
    for i in range(len(word)):
        typo = word[:i] + word[i+1:]
        # Skip if typo is a prefix of the word (causes negative backspaces
        # in QMK's autocorrect trie serialization).
        if word.startswith(typo):
            continue
        yield typo


def gen_adjacent_key(word):
    """Replace each character with a QWERTY neighbor."""
    for i, ch in enumerate(word):
        for neighbor in QWERTY_NEIGHBORS.get(ch, ''):
            typo = word[:i] + neighbor + word[i+1:]
            if typo != word:
                yield typo


def generate_all_typos(word):
    """Generate all candidate typos for a word with their category and a
    plausibility score (lower = more likely typo)."""
    # Transpositions are the most common mechanical typo.
    # Score by position: middle-of-word swaps are more likely than edges.
    for i, typo in enumerate(gen_transpositions(word)):
        # Slightly prefer interior transpositions
        score = 1 if 0 < i < len(word) - 2 else 2
        yield typo, 'transpose', score

    # Dropped letters — common when typing fast, but produces shorter strings
    # which are more prone to false positives. Higher base score.
    for typo in gen_dropped_letters(word):
        yield typo, 'drop', 3


# Target number of entries in final dictionary
TARGET_ENTRIES = 200


def main():
    real_words = load_dictionary()

    # Deduplicate the input word list; earlier = higher frequency
    seen_words = set()
    words = []
    for w in COMMON_WORDS:
        wl = w.lower()
        if wl not in seen_words:
            seen_words.add(wl)
            words.append(wl)

    # Assign a frequency rank to each word (lower = more common)
    word_rank = {w: i for i, w in enumerate(words)}

    # Generate all candidate typos: typo -> list of (correction, category, score)
    candidates = defaultdict(list)
    for word in words:
        for typo, category, score in generate_all_typos(word):
            candidates[typo].append((word, category, score))

    # Score and filter candidates
    scored_entries = []  # (combined_score, typo, correction, category)
    for typo, corrections_list in candidates.items():
        if len(typo) < 5:
            continue

        # Typo must not be a real English word
        if typo in real_words:
            continue

        # Group by correction word
        by_correction = defaultdict(list)
        for correction, category, score in corrections_list:
            by_correction[correction].append((category, score))

        # Must map to exactly one correction (unambiguous)
        if len(by_correction) != 1:
            continue

        correction = next(iter(by_correction))
        cats = by_correction[correction]

        # Best (lowest) typo score for this entry
        best_score = min(s for _, s in cats)
        best_cat = min(cats, key=lambda x: x[1])[0]

        # Combined score: prioritize common words and plausible typo types
        # Lower = better (more likely to be useful)
        rank = word_rank.get(correction, 999)
        combined = rank * 0.5 + best_score * 10

        scored_entries.append((combined, typo, correction, best_cat))

    # Sort by score (best first)
    scored_entries.sort()

    # Limit entries per correction word, with per-category limits to ensure
    # all typo types get representation (not just the lowest-scored category).
    MAX_PER_WORD = 4
    MAX_PER_WORD_PER_CAT = 2
    word_counts = defaultdict(int)            # word -> total count
    word_cat_counts = defaultdict(lambda: defaultdict(int))  # word -> cat -> count
    entries = {}  # typo -> (correction, category)
    for _, typo, correction, category in scored_entries:
        if word_counts[correction] >= MAX_PER_WORD:
            continue
        if word_cat_counts[correction][category] >= MAX_PER_WORD_PER_CAT:
            continue

        # Check substring conflicts with existing entries
        conflict = False
        for existing_typo in list(entries.keys()):
            if typo in existing_typo or existing_typo in typo:
                conflict = True
                break
        if conflict:
            continue

        entries[typo] = (correction, category)
        word_counts[correction] += 1
        word_cat_counts[correction][category] += 1
        if len(entries) >= TARGET_ENTRIES:
            break

    # Sort by correction word for readability
    sorted_entries = sorted(entries.items(), key=lambda x: (x[1][0], x[0]))

    # Output
    print("# Mechanical typos for common English words")
    print("# Generated by generate_typos.py")
    print("# Categories: transpositions, dropped letters, adjacent-key")
    print(f"# Total entries: {len(sorted_entries)}")
    print()

    current_correction = None
    for typo, (correction, category) in sorted_entries:
        if correction != current_correction:
            if current_correction is not None:
                print()
            current_correction = correction
        # Use : prefix for word boundary
        print(f":{typo:<20s} -> {correction}")

    # Stats
    cats = defaultdict(int)
    for _, (_, cat) in sorted_entries:
        cats[cat] += 1
    print(file=sys.stderr)
    print(f"Generated {len(sorted_entries)} entries from {len(words)} source words", file=sys.stderr)
    for cat, count in sorted(cats.items(), key=lambda x: -x[1]):
        print(f"  {cat}: {count}", file=sys.stderr)


if __name__ == '__main__':
    main()
