## Assignment 05 - Exploring Morphology with Add Delete Tables 

**Q: Morphology & Morpheme**
Morphology is the branch of linguistics that studies the structure and formation of words.

It analyzes how words are built from smaller meaningful units and how word forms change.

Why morphology is important in NLP:

* Helps understand word meaning and grammatical structure.
* Useful for tasks like:

  * Lemmatization
  * Stemming
  * Machine translation
  * Information retrieval
  * Speech recognition
  * Text analysis

Example:
Words like:

* “play”
* “playing”
* “played”
* “player”

are related through morphology.

Understanding this relationship helps NLP systems treat them as related forms of the same root concept.

What is a morpheme?
A morpheme is the smallest meaning-bearing unit in a language.

Examples:

* “unhappy” = “un” + “happy”
* “cats” = “cat” + “s”

Here:

* “un” adds negation
* “s” indicates plural

A morpheme is not the same as a syllable.

Difference:

* Morphemes carry meaning.
* Syllables are units of pronunciation.

Example:
Word: “teacher”

* Morphemes:

  * “teach”
  * “er”
* Syllables:

  * “teach”
  * “er”

Another example:
Word: “banana”

* Syllables:

  * ba + na + na
* Morphemes:

  * “banana” is a single morpheme because smaller parts do not carry meaning.

So, the smallest meaning-bearing unit in language is the morpheme.

---
**What is the difference between a free morpheme and a bound morpheme?**
Free morpheme:

* A morpheme that can stand alone as an independent word.
* It has meaning by itself.

Examples:

* “book”
* “happy”
* “run”

Bound morpheme:

* A morpheme that cannot stand alone.
* It must be attached to another morpheme.

Examples:

* “un” in “unhappy”
* “ed” in “played”
* “s” in “cats”

Difference:

* Free morphemes can exist independently.
* Bound morphemes need another word/root to carry meaning.

---
**Q: What is an affix? What are the three types of affixes? (prefix, suffix, infix) . Does English use infixes? Which languages do?**

An affix is a morpheme added to a root word to modify its meaning or grammatical form.

Three types of affixes:

1. Prefix

* Added at the beginning of a word.

Examples:

* “un” + happy → unhappy
* “re” + write → rewrite

2. Suffix

* Added at the end of a word.

Examples:

* play + “ed” → played
* kind + “ness” → kindness

3. Infix

* Inserted inside a word.

English and infixes:

* English does not commonly use true grammatical infixes.
* Informal expressions like:

  * “abso-bloody-lutely”
    are sometimes considered infix-like, but they are not standard morphological infixes.

Languages that use infixes:

* Tagalog
* Arabic
* Indonesian
* Malay

Example from Tagalog:

* “sulat” (write)
* “sumulat” (wrote) where “um” is an infix.

---
**Q:What is an add-delete table? What is its purpose in morphological analysis?**
An add-delete table is a rule table used in morphological analysis to transform one word form into another by:

* Deleting certain characters
* Adding new characters

Purpose:

* Helps identify the root form or generate related word forms.
* Used in stemming, lemmatization, and morphological parsing.

Example:
For converting:

* “studies” → “study”

Rule:

* Delete “ies”
* Add “y”

It helps NLP systems handle different grammatical forms of words systematically.

---
**Q: Construct an add-delete table for the word "unhappiness". Show each step.**
Word: “unhappiness”

Goal: Break it into morphemes using add-delete operations.

| Step | Current Word | Delete | Add/Base Form | Result  |
| ---- | ------------ | ------ | ------------- | ------- |
| 1    | unhappiness  | “ness” | —             | unhappy |
| 2    | unhappy      | “un”   | —             | happy   |

Morpheme breakdown:

* “un” → prefix
* “happy” → root word
* “ness” → suffix

Meaning:

* “un” gives negation
* “ness” converts adjective to noun

Final root/base word:

* “happy”

---
**Q: Construct an add-delete table for the word "replayed". Identify each morpheme.**
Word: “replayed”

| Step | Current Word | Delete | Add/Base Form | Result |
| ---- | ------------ | ------ | ------------- | ------ |
| 1    | replayed     | “ed”   | —             | replay |
| 2    | replay       | “re”   | —             | play   |

Morpheme breakdown:

* “re” → prefix
* “play” → root word
* “ed” → suffix

Meaning:

* “re” means again
* “ed” indicates past tense

Final root/base word:

* “play”

---
**Q: What is a Finite State Transducer? How is it different from a Finite State Automaton?**
A Finite State Transducer (FST) is a finite-state machine that maps an input sequence to an output sequence.

It is used for transformations such as:

* Morphological analysis
* Stemming
* Speech processing
* Machine translation

An FST consists of:

* States
* Transitions
* Input symbols
* Output symbols

Example:
Input: “cats”
Output: “cat + plural”

Difference between FST and Finite State Automaton (FSA):

Finite State Automaton (FSA):

* Accepts or rejects input strings.
* Produces no output.
* Used mainly for pattern recognition.

Finite State Transducer (FST):

* Converts input strings into output strings.
* Produces output during transitions.
* Used for language transformation tasks.

So:

* FSA = recognition
* FST = transformation/mapping

---
**Q: What does an FST take as input and what does it produce as output? In an FST for morphological analysis, what do states represent? What do transitions represent?**
An FST takes an input string or sequence of symbols and produces an output string or sequence of symbols.

Example:
Input: “played”
Output: “play + past”

In morphological analysis:

States represent:

* Intermediate stages in word processing or morphological structure.

Transitions represent:

* Movement between states based on input symbols.
* They also generate corresponding output symbols.

Example transition:

* Input: “s”
* Output: “+plural”

So transitions perform the actual mapping from surface word forms to morphological representations.

---
**Q: What is the difference between a deterministic and non-deterministic FST?**
Deterministic FST:

* For a given state and input symbol, there is only one possible transition.
* The next state and output are uniquely determined.

Non-deterministic FST:

* For a given state and input symbol, multiple transitions may exist.
* The machine can follow different possible paths.

Difference:

* Deterministic FST has one unique computation path.
* Non-deterministic FST may have multiple possible computation paths for the same input.

---
**Q: Give two NLP applications where FSTs are used beyond morphological analysis.**

1. Spell Checking

FSTs are used in spell checkers to recognize whether a word belongs to a valid word-form in a language. The FST encodes all valid word forms in a language. When an unknown/misspelled word is input, the FST can compute the **edit distance** (via weighted FSTs) between the input and the nearest valid word and suggest corrections.

> Example: Input `"runing"` → FST recognizes it doesn't map to any valid form → suggests `"running"` by finding the closest valid transition path.

---

2. Text Normalization / Tokenization in Speech Processing

FSTs are used in **text-to-speech (TTS)** systems to normalize raw text before synthesis. They handle:
- Expanding abbreviations (`"Dr."` → `"Doctor"`)
- Expanding numbers (`"2026"` → `"two thousand and twenty six"`)
- Handling punctuation and special tokens

This is essentially a **string transduction** problem — mapping one string to another — which is exactly what FSTs are designed for. Google's Kestrel and similar TTS pipelines use cascaded FSTs for this normalization step.

---
**Q: What is morphological generation vs morphological recognition? Can an FST do both?**
Morphological recognition:

* Analyzes a surface word and identifies its root and grammatical information.

Example:

* “played” → “play + past”

Morphological generation:

* Produces the correct surface word from root and grammatical features.

Example:

* “play + past” → “played”

Can an FST do both?

* Yes.
* An FST can be used for both analysis and generation because the mapping between input and output can be reversed.

---
**Q: What is the difference between inflectional and derivational morphology?** 

Morphology studies how words are formed and modified using morphemes.

Two major types are:

1. Inflectional morphology

2. Derivational morphology

Inflectional morphology changes the grammatical form of a word without changing its core meaning or word category.

Purpose:

* Show grammatical information such as:

  * Tense
  * Number
  * Gender
  * Case
  * Degree

Examples:

* play → played
* cat → cats
* tall → taller

Characteristics:

* Does not create a new dictionary word.
* Core meaning remains same.
* Usually does not change part of speech.

Examples:

* “play” (verb) → “played” (still a verb)
* “cat” (noun) → “cats” (still a noun)

Common English inflectional suffixes:

* -s (plural)
* -ed (past tense)
* -ing (continuous form)
* -er (comparative)
* -est (superlative)

Example analysis:
“dogs”

* dog = root
* s = plural marker

Meaning remains related to “dog”.

2. Derivational Morphology

Derivational morphology creates a new word by adding affixes that change meaning or word class.

Purpose:

* Create new vocabulary words.

Examples:

* happy → happiness
* teach → teacher
* kind → unkind

Characteristics:

* Creates a new dictionary word.
* Meaning changes.
* Part of speech may change.

Examples:

* happy (adjective) → happiness (noun)
* teach (verb) → teacher (noun)

Types of derivational changes:

a) Meaning change only

* happy → unhappy

Part of speech remains adjective, but meaning changes.

b) Meaning + word class change

* govern (verb) → government (noun)

Common derivational affixes:

Prefixes:

* un-
* re-
* dis-

Suffixes:

* -ness
* -ment
* -er
* -tion

Detailed comparison:

| Feature               | Inflectional Morphology  | Derivational Morphology |
| --------------------- | ------------------------ | ----------------------- |
| Purpose               | Grammatical modification | Create new words        |
| Meaning change        | Very little              | Significant             |
| New dictionary word   | No                       | Yes                     |
| Part of speech change | Usually no               | Often yes               |
| Position in word      | Usually outermost suffix | Closer to root          |
| Productivity          | Limited                  | Highly productive       |

Examples:

Inflectional:

* walk → walked
* small → smaller
* car → cars

Derivational:

* act → action
* nation → national
* friend → friendship

Order example:
“nationalization”

Breakdown:

* nation (root)
* al (derivational)
* ize (derivational)
* ation (derivational)

Each step creates a new word form and meaning.

Important point:
Inflectional morphology adjusts grammar, while derivational morphology expands vocabulary.
