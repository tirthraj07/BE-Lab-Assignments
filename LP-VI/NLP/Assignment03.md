### Assignment 03 - Preprocessing and Text Representation Techniques for Natural Language Processing.

**Q: Text Cleaning**

Text cleaning is the process of removing unwanted or irrelevant parts from text to make it suitable for NLP tasks. It improves data quality and model performance.

Typical text cleaning pipeline:

1. Lowercasing
2. Removing HTML tags, URLs, punctuation, special characters
3. Tokenization
4. Stopword removal
5. Stemming or lemmatization

The order matters because some steps depend on tokenized words.

Noise in NLP means unnecessary or meaningless text information.

Examples:

* URLs
* Emojis/special characters
* HTML tags

Text cleaning can happen both before and after tokenization depending on the operation:

* Character-level cleaning usually happens before tokenization.
* Word-level cleaning like stopword removal happens after tokenization.

---
**Q: What is morphological analysis? How does it underpin lemmatization? What is the difference between inflectional and derivational morphology?**
Morphological analysis is the study of the internal structure of words and how words are formed using smaller meaningful units called morphemes.

A morpheme is the smallest unit of meaning.

Example:

* “unhappiness” = “un” + “happy” + “ness”

Morphological analysis helps identify:

* Root word
* Prefixes
* Suffixes
* Grammatical information like tense, number, gender, etc.

How it underpins lemmatization:

* Lemmatization uses morphological analysis to convert a word into its base or dictionary form called lemma.
* It considers the word’s meaning and grammatical role.

Examples:

* “running” → “run”
* “better” → “good”
* “studies” → “study”

Unlike stemming, lemmatization produces valid dictionary words because it uses morphological knowledge.

Types of morphology:

1. Inflectional Morphology

* Changes the grammatical form of a word without changing its core meaning or word class.

Examples:

* “play” → “played”
* “cat” → “cats”
* “big” → “bigger”

Characteristics:

* Meaning remains mostly same.
* Part of speech usually does not change.

2. Derivational Morphology

* Creates a new word with a different meaning or sometimes a different word class.

Examples:

* “happy” → “happiness”
* “teach” → “teacher”
* “kind” → “unkind”

Characteristics:

* Meaning changes.
* Part of speech may change.

Difference:

* Inflectional morphology modifies grammatical form.
* Derivational morphology creates new words.

---
**What are stop words? Give five examples in English. Why do stop words hurt NLP model performance if left in? Can removing stop words ever be harmful?**
Stop words are very common words in a language that usually carry little meaningful information in NLP tasks.

Examples in English:

* the
* is
* and
* in
* of

Why they can hurt performance:

* They increase data size without adding much meaning.
* They can introduce noise.
* They increase computation and may reduce model efficiency.

Can removing stop words be harmful?
Yes. In some tasks, stop words carry important meaning.

Example: Sentiment Analysis

* “good” → positive
* “not good” → negative

If “not” is removed as a stop word, the meaning changes completely.

---
**Q: What is label encoding? What problem does it solve? What is the difference between label encoding and one-hot encoding?**
Label encoding converts categorical labels into numerical values.

Example:

* Positive → 0
* Negative → 1
* Neutral → 2

Problem it solves:

* Machine learning models work with numbers, not text labels.

Difference between label encoding and one-hot encoding:

Label Encoding:

* Assigns a single integer to each category.
* Efficient but may create a false order between categories.

Example:

* Red → 0
* Blue → 1
* Green → 2

One-Hot Encoding:

* Represents each category as a separate binary vector.
* Avoids false ordering.

Example:

* Red → [1,0,0]
* Blue → [0,1,0]
* Green → [0,0,1]

Label encoding is appropriate when:

* Categories have a natural order.
* Example: Low, Medium, High.
* Tree-based models like Decision Trees or Random Forests are used, since they are less affected by numeric ordering.

One-hot encoding is appropriate when:

* Categories have no natural order.
* Example: Red, Blue, Green.
* Models like Logistic Regression, SVM, or Neural Networks are used, where numeric ordering can mislead the model.

Difference:

* Label encoding uses one number per category.
* One-hot encoding uses a binary vector for each category.

---
**Q:What is the danger of using label encoding for nominal categorical variables?**
The danger is that label encoding introduces a false ordinal relationship between categories.

Example:

* Red → 0
* Blue → 1
* Green → 2

The model may incorrectly assume:

* Green > Blue > Red

But nominal categories have no actual order.

This can mislead models that depend on numerical relationships and negatively affect performance.

---
**Q: What is ordinal encoding?**
Ordinal encoding is a technique where categorical values are converted into numerical values based on their natural order or ranking.

Example:

* Low → 1
* Medium → 2
* High → 3

It is used when categories have meaningful order.
