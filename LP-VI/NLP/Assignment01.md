## Assignment 01 - Perform Tokenisation & Stemming

**Q:  What are the common NLP techniques?**
The common NLP techniques for text extraction are: 
1. Named Entity Recognition 
2. Sentiment Analysis 
3. Text Summarization 
4. Aspect Mining 
5. Text Modelling

---
**Q: What are the components of NLP?**
1. Lexical Analysis
   Lexical analysis is the first step in NLP where raw text is broken into smaller units called tokens.

Tasks involved:

* Tokenization
* Removing punctuation/special symbols
* Identifying words
* Stemming/Lemmatization

Example:
Sentence:
“I love NLP”

Tokens:
[“I”, “love”, “NLP”]

Purpose:

* Convert raw text into a form suitable for further processing.

2. Syntactic Analysis
   Syntactic analysis studies the grammatical structure of a sentence.

It checks:

* Word order
* Grammar rules
* Relationship between words

Also called:

* Parsing

Example:
Sentence:
“Boy eats apple”

The parser identifies:

* “Boy” → subject
* “eats” → verb
* “apple” → object

Purpose:

* Determine whether a sentence is grammatically correct.
* Understand sentence structure.

3. Semantic Analysis
   Semantic analysis focuses on understanding the meaning of words and sentences.

It tries to determine:

* Actual meaning
* Word relationships
* Contextual interpretation

Example:
“The bank is near the river.”

Semantic analysis determines:

* “bank” means river bank, not financial bank.

Purpose:

* Extract meaningful interpretation from text.

4. Discourse Integration
   Discourse integration analyzes meaning across multiple sentences instead of a single sentence.

It helps connect information between sentences.

Example:
“Ravi bought a car. He loves it.”

Discourse analysis determines:

* “He” refers to Ravi
* “it” refers to the car

Purpose:

* Maintain context and coherence throughout a conversation or paragraph.

5. Pragmatic Analysis
   Pragmatic analysis studies the intended meaning based on real-world context and situation.

It considers:

* Speaker intention
* Context
* Implied meaning

Example:
Sentence:
“Can you open the window?”

Literal meaning:
Question about ability.

Pragmatic meaning:
A request to open the window.

Purpose:

* Understand what the speaker actually intends to convey beyond literal words.

---
**Q: What is Tokenization?**
Tokenization is the process of breaking down raw text into smaller, distinct pieces called tokens. A token can be a full word, a part of a word, or a single character.

**Why is it a fundamental preprocessing step?**

* **Structure:** Computers cannot process a continuous, unstructured block of text. Tokenization gives the text a defined structure.
* **Analysis:** It reduces text to its most basic, meaningful units, making it possible for the system to count frequencies and identify patterns.
* **Numerical Conversion:** Machine learning models only understand numbers. Tokenization is the required first step before these text units can be converted into numerical values.

**Types of Tokenization**

**Whitespace-based Tokenization**

* **What it is:** Splits sentences into tokens strictly wherever there is a blank space, tab, or new line.
* **Key characteristic:** It is the fastest and simplest method, but it leaves punctuation attached to the words. For example, the phrase `Hello, world!` becomes two tokens: `Hello,` and `world!`.

**Punctuation-based Tokenization**

* **What it is:** Splits text based on spaces, but also actively separates punctuation marks from the words.
* **Key characteristic:** It treats punctuation as separate tokens. Using the previous example, `Hello, world!` becomes four distinct tokens: `Hello` `,` `world` `!`.

**Treebank Tokenization**

* **What it is:** A rule-based method that uses standard English grammar conventions to split text.
* **Key characteristic:** Its defining feature is how it handles contractions and abbreviations. For example, it splits the word `don't` into `do` and `n't`. It also knows to keep abbreviations like `U.S.A.` as a single token while separating a normal period at the end of a sentence.

**Tweet Tokenization**

* **What it is:** A specialized method designed specifically for the messy, informal text found on social media.
* **Key characteristic:** It ensures that special formats are not broken apart. It keeps hashtags (#coding), user mentions (@student), web links, and text-based faces (like a smiley face) completely intact as single tokens.

**Multi-word Expression (MWE) Tokenization**

* **What it is:** A method that recognizes when a group of words has a single, combined meaning and treats them as one token.
* **Key characteristic:** It prevents meaningful phrases from losing their context. For example, it treats `New York` or `ice cream` as a single token rather than splitting them into separate, unrelated words.

--- 

**Q: How Treebank Tokenization Differs from Punctuation-Based Tokenization**

* **Handling Contractions:** Simple punctuation-based tokenization either strips the apostrophe or blindly splits around it (turning "don't" into "don", "'", "t"). Treebank tokenization uses grammar rules to split the word by its meaning, turning "don't" into "do" and "n't" (representing "not").
* **Handling Periods:** A simple punctuation tokenizer will remove or separate all periods. A Treebank tokenizer is smart enough to keep periods attached to abbreviations (like "U.S.A." or "Dr.") while separating a period that simply marks the end of a sentence.

**What is the Penn Treebank?**

* **Definition:** It is a massive, highly influential collection of English text (originally mostly from Wall Street Journal articles) created by researchers at the University of Pennsylvania.
* **Purpose:** Linguists manually labeled every word in this collection with its grammatical role and sentence structure. It essentially became the standard rulebook in language processing for how English sentences should be broken down and analyzed, which is where the "Treebank" rules for tokenization come from.

---
**Q: What is Stemming?**
Stemming is the process of reducing a word to its base or root form by simply chopping off its ends (prefixes or suffixes). It relies on strict, basic rules and does not consider the actual meaning or grammar of the word. For example, the words "running," "runs," and "runner" might all be chopped down to the basic stem "run."

**What is its purpose in NLP pipelines?**

* **Reduces Vocabulary Size:** By treating different variations of a word as a single item, it drastically decreases the total number of unique words a computer system has to learn and process, which saves memory and speeds up calculations.
* **Improves Matching:** It ensures that words with similar meanings are grouped together. For example, it allows a search engine to successfully match a user typing "fishing" with an article that only uses the word "fish."
* **Simplifies Data:** It removes unnecessary complexity from text, making it easier to train machine learning models on the core concepts rather than getting distracted by grammatical variations.
---
**Q: What is the difference between the Porter Stemmer and the Snowball Stemmer? Why is Snowball considered an improvement?**
**The Difference**

* **Porter Stemmer:** The original, oldest rule-based method for chopping off word endings. It uses a very rigid set of rules and was designed exclusively for the English language.
* **Snowball Stemmer:** A newer, updated framework created by the same inventor. While it includes an improved English stemmer (often called Porter2), it is actually a complete system designed to create stemming rules for many different languages.

**Why Snowball is an Improvement**

* **Multiple Languages:** The most significant advantage is that Snowball is not restricted to English. It supports stemming for languages like Arabic, Danish, Dutch, English, Finnish, French, German, Hungarian, Italian, Norwegian, Portuguese, Romanian, Russian, Spanish and Swedish
* **Higher Accuracy:** It fixes the known flaws and mistakes of the original Porter algorithm. It is slightly less aggressive, meaning it rarely chops off necessary letters and leaves the root word in a more accurate state.
* **Better Speed:** The underlying code and logic are optimized, making it computationally faster and more efficient to run on large amounts of text.
---
**Q: What does the Porter Stemmer output for words like "running", "flies", "happily"?**
The Porter stemmer applies strict letter-chopping rules, which sometimes results in outputs that are not real English words. For the words provided, the outputs are:

"running" outputs as run

"flies" outputs as fli

"happily" outputs as happili

---
**Q: What are over-stemming and under-stemming? Give examples of each.**
**Over-stemming**

* **What it is:** This happens when the algorithm cuts off too much of a word. As a result, words that have completely different meanings are mistakenly grouped together under the exact same stem.
* **Example:** The words "Universe" and "University" might both be chopped down to the stem "Univers". This causes the system to treat them as the same word, even though they mean very different things. Another example is "Wander" and "Wand" both being reduced to "Wand".

**Under-stemming**

* **What it is:** This happens when the algorithm does not cut off enough of a word. As a result, words that share the exact same core meaning fail to be grouped together.
* **Example:** The words "Absorb" and "Absorption" might be left as two separate stems ("absorb" and "absorpt") instead of being merged. Another common example is irregular forms, like "Data" and "Datum", which the stemmer might fail to connect.

---
**Q: What is Lemmatization?**
Lemmatization is the process of reducing a word to its proper, meaningful dictionary form, known as a lemma.

**How it Differs from Stemming**
Stemming blindly chops letters off the ends of words based on rigid spelling rules, often creating meaningless fragments. Lemmatization analyzes the word's meaning and structure using a built-in dictionary to ensure the final output is always a valid, real word.

**Why it Requires POS (Part-of-Speech) Information**
A single word can have different base forms depending on its grammatical role in a sentence. For example, the word "leaves" could be a plural noun (base form: leaf) or a verb (base form: leave). Providing the POS tag tells the system exactly which grammatical context to use to find the correct root.

**What Happens if POS is Not Provided?**
If you do not provide a POS tag, most lemmatizers will default to assuming every word is a noun. This leads to incorrect outputs for verbs and adjectives. For instance, without a verb tag, the system will not know how to convert the word "running" back to "run" or the word "are" back to "be", leaving them completely unchanged.

---
**Q: In what scenarios would you prefer stemming over lemmatization, and vice versa?**
**When to Prefer Stemming**

* **Speed is the priority:** It relies on simple chopping rules, making it much faster to process massive amounts of text.
* **Broad searching:** In basic search engines, retrieving any document related to the core concept is more important than exact grammatical matches.
* **Simple topic categorization:** For tasks like basic spam filtering, just identifying the general root of the words is usually enough.

**When to Prefer Lemmatization**

* **Accuracy is the priority:** It guarantees the output is a real word and considers the grammatical context of the sentence.
* **Conversational AI:** Chatbots and virtual assistants must understand exact meanings and generate grammatically correct responses.
* **Advanced understanding:** Tasks like machine translation or deep sentiment analysis require knowing the difference between "leaves" (plant) and "leaves" (departing), which only lemmatization can provide.

---
**Q: What does WordNetLemmatizer return for "better"**
**With specifying POS:**
If specified as an Adjective: It returns "good".
If specified as an Adverb: It returns "well".

**Without specifying POS:**
It returns "better". By default, the lemmatizer assumes every word is a noun. Since "better" can be a valid noun, it remains unchanged.

---
**Q: What is NLTK?**
NLTK stands for Natural Language Toolkit. It is a comprehensive, open-source library for Python that provides the foundational tools, programs, and datasets required to build software that processes and analyzes human language.

**Main Capabilities**

* **Text Preprocessing:** It handles the core steps of cleaning raw text, including tokenization, stemming, lemmatization, and removing common, low-value words (stopwords).
* **Part-of-Speech Tagging:** It can automatically label every word in a sentence with its correct grammatical category (noun, verb, adjective, etc.).
* **Sentence Parsing:** It analyzes the grammatical structure of sentences to determine how words are grouped and relate to one another.
* **Named Entity Recognition:** It scans text to locate and classify specific proper nouns, such as the names of people, organizations, and geographic locations.
* **Dataset Access:** It comes with immediate, built-in access to dozens of massive text collections (corpora) and lexical databases, such as WordNet and the Penn Treebank, which are necessary for testing and training language models.

---
**Q: Is tokenization language-independent? What challenges arise with languages like Hindi, Chinese, or Arabic?**
**Is Tokenization Language-Independent?**
No, it is highly language-dependent. A tokenizer built for English will fail on many other languages because it relies heavily on spaces and specific punctuation rules that do not exist universally.

**Challenges with Specific Languages**

* **Chinese:** Sentences are written continuously without any spaces between words. A standard tokenizer cannot split the text and instead requires complex dictionaries or advanced models to determine where one word ends and the next begins.
* **Arabic:** It frequently combines prepositions, conjunctions, and root words into a single continuous string of text. A tokenizer must understand the grammar to correctly split these combined blocks back into separate, meaningful tokens.
* **Hindi:** The writing system combines multiple letters to form single, joined characters. What appears visually as one character to a human might need to be broken down into multiple separate sound components by the computer, making standard character or space splitting ineffective.

---
**Q: Why is NLP considered hard? Name three specific challenges**
**Why NLP is Hard**
Human language is inherently messy, constantly changing, and heavily reliant on context. Unlike computer code, which is strict and logical, human language is full of exceptions and hidden meanings that machines struggle to interpret.

**Three Specific Challenges**

**1. Ambiguity**
Words or entire sentences can have multiple valid meanings depending on the context. For example, the word "bank" can refer to a financial institution or the side of a river. A computer must understand the surrounding context to guess the correct meaning.

**2. Sarcasm and Irony**
People frequently say the exact opposite of what they actually mean. For instance, saying "What a beautiful day" during a thunderstorm. Computers naturally read text literally and struggle to detect the unwritten tone or humor behind the words.

**3. Informal Language and Errors**
Real-world text rarely follows perfect grammatical rules. People use slang, abbreviations, misspellings, and mashed-up words (especially on social media). Systems trained strictly on formal dictionary words easily fail when faced with this messy, everyday text.

---
**Q What are the stages of an NLP pipeline? Where does tokenization fit?**
**Stages of an NLP Pipeline**

1. **Data Collection:** Gathering the raw text data required for the task.
2. **Text Preprocessing:** Cleaning and structuring the raw text so a machine can process it.
3. **Feature Engineering:** Converting the cleaned text into numerical formats (vectors) that algorithms can understand.
4. **Modeling:** Feeding the numerical data into a machine learning or deep learning algorithm to train it.
5. **Evaluation:** Testing the model against unseen data to measure its accuracy and performance.
6. **Deployment:** Integrating the trained model into a live application to process new user inputs.

**Where Tokenization Fits**

Tokenization fits exactly into the **Text Preprocessing** stage. It is typically the very first step of preprocessing. You must break the raw text into individual tokens before you can apply other preprocessing steps like stemming, lemmatization, or removing stop words.

---
**Q: Are natural languages regular? Can finite automata fully model them?**
**Are natural languages regular?**
No. Natural languages are much more complex than regular languages.

**Can finite automata fully model them?**
No. Finite automata have a fixed, limited memory and cannot fully model the structure of human language.

**Why?**
Human language features nesting (or recursion). You can endlessly embed phrases inside other phrases (for example: "The car that the man that my sister knows bought is fast.").

To correctly process this, a system must remember and match each subject to its correct verb, no matter how deep the sentence gets. Finite automata cannot keep track of or count these deep, nested relationships.

---
**Q: What is latent semantic indexing (LSI)?**
Latent Semantic Indexing (LSI) is a technique used in NLP and information retrieval to identify hidden relationships between words and documents.

It reduces the dimensionality of text data to capture underlying semantic meaning.

How it works:

1. Create a term-document matrix using word frequencies or TF-IDF.
2. Apply Singular Value Decomposition (SVD).
3. Reduce the matrix into a lower-dimensional semantic space.

Purpose:

* Group similar words and documents based on meaning.
* Handle synonymy and noise in text.

Example:
Words like:

* “car”
* “automobile”

may be treated as semantically related even if exact words differ.

Advantages:

* Captures hidden semantic relationships.
* Improves document retrieval and search quality.

Limitation:

* Computationally expensive for very large datasets.

---
**Q: What is parsing? Explain dependency parsing, semantic parsing, constituency parsing, shallow parsing**
Parsing is the process of analyzing the grammatical structure of a sentence and identifying relationships between words.

It helps NLP systems understand sentence structure and meaning.

Types of parsing:

1. Dependency Parsing
   Dependency parsing identifies dependency relationships between words in a sentence.

It determines:

* Which word depends on another word.

Example:
Sentence:
“Ravi eats apples”

Relations:

* “eats” → main verb
* “Ravi” depends on “eats” as subject
* “apples” depends on “eats” as object

Purpose:

* Understand grammatical relationships between words.

2. Semantic Parsing
   Semantic parsing converts natural language into a machine-understandable meaning representation.

It focuses on sentence meaning rather than grammar.

Example:
Sentence:
“Show me flights to Delhi”

Converted representation:
Intent: find_flights(destination=Delhi)

Purpose:

* Used in chatbots, virtual assistants, and question answering systems.

3. Constituency Parsing
   Constituency parsing breaks a sentence into nested phrases or constituents.

It creates a parse tree.

Example:
Sentence:
“The boy ate an apple”

Structure:

* Noun Phrase (NP): “The boy”
* Verb Phrase (VP): “ate an apple”

Purpose:

* Identify phrase structure and sentence hierarchy.

4. Shallow Parsing
   Shallow parsing identifies basic phrases in a sentence without generating a full parse tree.

Also called:

* Chunking

Example:
Sentence:
“The boy ate an apple”

Chunks:

* [NP The boy]
* [VP ate]
* [NP an apple]

Purpose:

* Faster and simpler than full parsing.
* Used for information extraction and named entity recognition.

---
**Q: What is text summarization in NLP?**
Text summarization is the process of generating a shorter version of a text while preserving its important information and main meaning.

Purpose:

* Reduce large text into concise and meaningful summaries.

Two types of text summarization:

1. Extractive Summarization

* Selects important sentences or phrases directly from the original text.
* Does not generate new sentences.

Example:
Picking key sentences from a news article.

2. Abstractive Summarization

* Generates new sentences that capture the meaning of the original text.
* Similar to how humans summarize.

Example:
Rewriting a paragraph in shorter form using different words.

---
**Q: What is NLTK? What is SpaCy? How is it different?**
NLTK (Natural Language Toolkit) is a Python library used for NLP research and education.

It provides tools for:

* Tokenization
* Stemming
* POS tagging
* Parsing
* Corpus processing

Characteristics:

* Easy for learning and experimentation.
* Contains many NLP algorithms and datasets.

SpaCy is an industrial-strength NLP library designed for fast and efficient real-world applications.

It provides:

* Tokenization
* Named Entity Recognition (NER)
* POS tagging
* Dependency parsing
* Word vectors

Difference between NLTK and SpaCy:

| NLTK                              | SpaCy                               |
| --------------------------------- | ----------------------------------- |
| Mainly for education and research | Mainly for production applications  |
| Slower                            | Faster                              |
| More manual processing            | More optimized and automated        |
| Provides many NLP algorithms      | Focuses on efficient pipelines      |
| Easier for learning NLP concepts  | Better for large-scale applications |

---
**Q: What is the difference between a regular expression and regular grammar?**

Regular Expression (Regex):

* A pattern used to match or search text strings.
* Mainly used for text processing and pattern matching.

Example:

* `[0-9]+` matches numbers.
* `[a-z]+` matches lowercase words.

Purpose:

* Search, validate, or extract text patterns.

Regular Grammar:

* A formal grammar used to define regular languages.
* Consists of production rules for generating valid strings.

Example rules:

* S → aA
* A → b

Purpose:

* Used in formal language theory and automata.

Difference:

* Regular expressions describe patterns directly.
* Regular grammar defines rules to generate those patterns/languages.

Both are equivalent in expressive power because both represent regular languages.
