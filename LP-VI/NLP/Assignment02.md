## Assignment 02 - Create embeddings using Word2Vec

**Q: What is the Bag-of-Words model?**
It is a method used to convert text into numbers so a computer can process it. It works by making a list of all unique words in a document and simply counting how many times each word appears.
It is called a "bag" because it completely ignores the original order of the words, grammar, and sentence structure. Just like items thrown randomly into a physical bag, the model only cares about what words are present and how many there are, not how they were arranged.

---
**Q: What information does BoW deliberately discard? Why is that a limitation?**
**What it deliberately discards:**

* **Word Order:** The exact sequence of how words appear in a sentence.
* **Grammar and Context:** How words connect to each other to form a specific thought.

**Why this is a limitation:**

* **Meaning is Destroyed:** Because the sequence is ignored, sentences with entirely different meanings look identical to the system. For example, "The dog bit the man" and "The man bit the dog" produce the exact same word counts, confusing the model.
* **Ignores Word Relationships:** It treats every word as a completely separate item. It has no way of knowing that words like "car" and "automobile" share the same meaning, making it inefficient for understanding actual concepts.

---
**Q: What is the difference between count occurrence and normalized count occurrence? When would you prefer one over the other?**
**Count Occurrence**
This is the raw, total number of times a specific word appears in a text. It is an absolute number.

**Normalized Count Occurrence**
This is the raw count of a word divided by the total number of words in that text. It is a ratio or proportion that represents how concentrated the word is within the document.

**The Difference**
Count occurrence is biased toward longer texts. A 100-page book will naturally have a higher count of the word "science" than a one-page article, simply because it has more words overall. Normalized count removes this bias by factoring in the document's length, allowing for fair comparisons.

**When to prefer Count Occurrence**

* When all the documents you are analyzing are roughly the same length.
* When you only care about the absolute volume of a word (for example, counting total mentions of a brand name across Twitter).

**When to prefer Normalized Count Occurrence**

* When you need to compare documents of drastically different lengths.
* When you want to determine the actual topic or focus of a text. A high normalized count proves a word is central to that specific document, regardless of how long the document is.

---
**Q: What is a vocabulary in the context of BoW? How does vocabulary size affect the feature matrix?**
**What is a Vocabulary in BoW?**
In the Bag-of-Words model, the vocabulary is the master list of all the unique words found across every document in your entire dataset. It acts as the model's dictionary; the system will completely ignore any word that is not on this list.

**How Vocabulary Size Affects the Feature Matrix**
The size of the vocabulary directly dictates the size and efficiency of your feature matrix:

* **Number of Columns:** Every single word in the vocabulary gets its own dedicated column in the matrix. If your vocabulary has 10,000 unique words, your matrix will be 10,000 columns wide.
* **Empty Space:** A single document only uses a tiny fraction of the total vocabulary. Therefore, as the vocabulary grows larger, the matrix becomes filled mostly with zeros.
* **Resource Cost:** A massive, mostly empty matrix requires significantly more memory to store and more computing power to process, which can slow down your system.

---
**Q:What is a sparse matrix? Why does BoW always produce one?**

**What is a sparse matrix?**
A sparse matrix is a large grid or table of numbers where the vast majority of the entries are zero.

**Why does Bag-of-Words always produce one?**
In the Bag-of-Words model, the system creates a separate column for every single unique word found in the entire collection of documents (the total vocabulary).

However, any single document or sentence only uses a very small fraction of those total words. As a result, for any given document, almost all the columns in its row will be recorded as zero (representing the thousands of words it did not use). When you put all the documents together, you get a massive grid filled overwhelmingly with zeros.

---
**Q: Can BoW capture the sentence "not good" differently from "good"? What does this tell you about its limitations?**
**Can it capture the difference?**
It captures the presence of the individual words, recording one count for "not" and one count for "good." However, it completely fails to connect them, meaning it cannot understand that "not" reverses the meaning of "good."

**What this tells us about its limitations:**
This demonstrates that the Bag-of-Words model cannot process negation or context. Because it ignores word order entirely, it treats every word in isolation. It cannot detect when one word alters or depends on the meaning of another, resulting in a loss of the actual sentiment of the sentence.

---
**Q: What is the Sklearn class used to implement BoW?**

Scikit-learn's CountVectorizer is the standard tool used to build the vocabulary and generate the final Bag-of-Words matrix.

---
**Q: TF-IDF**
**What TF and IDF Stand For**

* **TF** stands for **Term Frequency**.
* **IDF** stands for **Inverse Document Frequency**.

**Formulas**

**Term Frequency (TF):** Measures how often a word occurs within a single, specific document.


TF = {Count of word in the document}/{Total number of words in the document}

**Inverse Document Frequency (IDF):** Measures how rare or common a word is across the entire collection of documents (the corpus).


IDF = log({Total number of documents}/{Number of documents containing the word})

**Why take the log in IDF? What happens without it?**
We use the logarithm to dampen the scaling effect.

Without the log, if you had 1 million documents and a rare word appeared in only 1 of them, its IDF score would be 1,000,000. A common word might have a score of 2. This massive difference would cause rare words to completely overpower all other calculations in the model. The log "squashes" these massive numbers down to a manageable scale, giving rare words a boost without letting them break the math.

**Why does IDF penalize words that appear in many documents?**
If a word appears in almost every single document (like "the," "is," or "data" in a tech archive), it has zero descriptive power. It cannot help you distinguish document A from document B, nor can it help you figure out the specific topic of a text. IDF penalizes these words so the model can focus its mathematical weight on the unique, meaningful words that actually define a document's core subject.

**What is the TF-IDF score of a word that appears in only one document but very frequently?**
**The score will be very high.**

**Why?**

* **Term Frequency (TF) is high:** The word appears many times within that specific document.
* **Inverse Document Frequency (IDF) is high:** The word is extremely rare overall because it only exists in that single document out of the entire collection.

**Conclusion:**
Multiplying a high TF by a high IDF yields a maximum score. This tells the system that the word is a highly significant keyword uniquely tied to the core topic of that specific document.

---
**Q: How is TF-IDF better than simple BoW for information retrieval tasks?**
TF-IDF is better than simple Bag of Words (BoW) because it reduces the importance of highly common words and highlights unique, informative words.

* **The limitation of BoW:** It only scores words based on how often they appear. Universally common words (like "the" or "is") receive the highest scores, even though they do not help identify the specific topic of a document.
* **The advantage of TF-IDF:** It balances two metrics. It looks at Term Frequency (how often a word appears in a specific document) and multiplies it by Inverse Document Frequency (how rare that word is across the entire collection of documents).

By doing this, TF-IDF penalizes frequent words that offer little value and gives higher weight to rare, meaningful words, making search and information retrieval much more accurate.

---
**What is a word embedding? How is it fundamentally different from BoW or TF-IDF?**
A word embedding is a dense vector representation of a word where similar words have similar vector values based on meaning and context.

Difference from BoW and TF-IDF:

* BoW and TF-IDF represent text using word counts or importance scores.
* They treat words as independent and do not capture meaning or context.
* Their vectors are sparse and high-dimensional.

Word embeddings:

* Capture semantic relationships between words.
* Use dense, low-dimensional vectors.
* Similar words get similar representations.

Example:
“king” and “queen” will have related embeddings, but in BoW/TF-IDF they are treated as completely separate words.

---
**Q: What does it mean for words to exist in a continuous vector space?**
It means words are represented as points in a multi-dimensional space using real-valued vectors.

In this space:

* Similar words are located close to each other.
* Relationships between words can be captured mathematically.

Example:
Vectors for “cat” and “dog” will be closer than “cat” and “car” because their meanings are more similar.

---
**Q: What is the dimensionality of a word embedding typically? Who controls it?**
Typical dimensionality of a word embedding:
Usually ranges from 50 to 300 dimensions in traditional models.
Modern deep learning models may use 512, 768, or more dimensions.
The dimensionality is chosen by the model designer or researcher as a hyperparameter.

---
**Q: If two words have a high cosine similarity in embedding space, what does that mean semantically?**
Meaning of high cosine similarity:
It means the two words have similar meanings or appear in similar contexts.
Their vectors point in similar directions in embedding space.

---
**Q: What is the difference between cosine similarity and Euclidean distance for comparing embeddings?**
Cosine similarity vs Euclidean distance:
Cosine similarity measures the angle between vectors and focuses on direction.
Euclidean distance measures the actual straight-line distance between vectors.
Cosine similarity is preferred in NLP because semantic similarity depends more on direction than magnitude.

---
**Q: What is Word2Vec? Explain in detail**
Word2Vec is a neural network-based technique used to generate word embeddings, where words with similar meanings get similar vector representations.

It was developed by Google in 2013.

Main idea:

* Learn word meanings from context.
* Words appearing in similar contexts get similar vectors.

Word2Vec has two architectures:

1. CBOW (Continuous Bag of Words)

* Predicts the target word using surrounding context words.
* Faster and works well for frequent words.

Example:
Given: “I love ___ very much”
Predict: “NLP”

2. Skip-Gram

* Predicts surrounding context words from a target word.
* Works better for rare words.

Example:
Input: “NLP”
Predict nearby words like “love”, “learning”, etc.

Working:

* Each word is initially represented as a one-hot vector.
* The neural network learns dense embeddings during training.
* After training, the hidden layer weights become the word embeddings.

Important features:

* Captures semantic relationships.
* Similar words have nearby vectors.
* Supports operations like:
  vector(“King”) - vector(“Man”) + vector(“Woman”) ≈ vector(“Queen”)

Advantages:

* Efficient and fast to train.
* Produces meaningful semantic embeddings.

Limitations:

* Gives only one embedding per word.
* Cannot handle different meanings of the same word based on context.

---
**Q: Which architecture performs better on rare words — CBOW or Skip-gram? Why?**
Skip-gram performs better on rare words.
Because it learns by predicting surrounding words from a single target word, giving more learning signals for rare words.

---
**Q: Which architecture is faster to train? Why?**
CBOW is faster to train.
Because it averages context words and makes only one prediction for the target word, reducing computation.

---
**Q: What is the window size parameter in Word2Vec? How does it affect the embeddings learned?**
Window size defines how many surrounding words are considered as context for a target word.

Example:
For window size = 2, the model looks at 2 words before and 2 words after the target word.

Effect on embeddings:

* Small window size:

  * Captures syntactic relationships.
  * Focuses on local context.

* Large window size:

  * Captures semantic relationships.
  * Focuses on broader context.

---
**Q: What is the role of the hidden layer in Word2Vec? What is its size?**
Role of hidden layer:

* The hidden layer learns the dense vector representation of words.
* The weights connected to this layer become the word embeddings after training.

Size of hidden layer:

* Equal to the embedding dimension chosen by the user.
* Example: if embedding size is 100, the hidden layer has 100 neurons.

---
**Q: What is negative sampling in Word2Vec? Why is it needed?**

Negative sampling is a training optimization technique used in Word2Vec.

Instead of updating weights for all words in the vocabulary, the model:

* Updates the correct target word.
* Updates only a few randomly selected incorrect words called negative samples.

Why it is needed:

* Computing probabilities for the entire vocabulary is very expensive.
* Negative sampling reduces computation and speeds up training significantly, especially for large vocabularies.

---
**Q: What is hierarchical softmax? When would you use it over negative sampling?**

Hierarchical softmax is an efficient alternative to normal softmax used in Word2Vec.

It organizes words in a binary tree and predicts a word by traversing a path in the tree instead of computing probabilities for all vocabulary words.

Advantages:

* Reduces computation from proportional to vocabulary size to proportional to tree depth.

Use over negative sampling when:

* The dataset is small.
* Rare words are important.
* More accurate probability estimation is needed.

---
**Q: After training Word2Vec, where exactly is the word embedding stored**
After training Word2Vec, the word embeddings are stored in the weight matrix between:

The input layer and the hidden layer.

Each row of this matrix represents the embedding vector of a word.

---
**Q: Gensim**
Gensim is an open-source Python library used for natural language processing and topic modeling.
It is mainly used for:

Training Word2Vec, Doc2Vec, and FastText models.
Topic modeling using LDA.
Text similarity and document indexing.

It is efficient for handling large text datasets.

**What is the min_count parameter in Gensim's Word2Vec? Why is it important?**
min_count specifies the minimum number of times a word must appear in the corpus to be included in training.

Example:

min_count = 5 means words appearing fewer than 5 times are ignored.

Why it is important:

Removes very rare and noisy words.
Reduces vocabulary size.
Speeds up training and improves embedding quality.

---
**Q: What is doc2vec? How does it extend Word2Vec?**
Doc2Vec is an extension of Word2Vec used to generate vector representations for entire documents, paragraphs, or sentences.

How it extends Word2Vec:

* Word2Vec learns embeddings only for words.
* Doc2Vec adds a unique document vector along with word vectors during training.

The document vector helps capture:

* Overall meaning
* Context
* Topic of the document

Main types:

1. PV-DM (Distributed Memory)

   * Predicts a word using context words and document vector.

2. PV-DBOW (Distributed Bag of Words)

   * Predicts words directly from the document vector.

---
**Q: Can two completely different words have similar TF-IDF scores? Can they have similar Word2Vec vectors? Explain the difference.**
Yes, two completely different words can have similar TF-IDF scores if they appear with similar frequency and importance in documents.

However:

* TF-IDF only measures statistical importance.
* It does not capture meaning or semantic relationships.

Two different words can also have similar Word2Vec vectors if they appear in similar contexts.

Example:
“doctor” and “physician”

* May have different TF-IDF values.
* But their Word2Vec vectors will likely be very similar because they have similar meanings.

Difference:

* TF-IDF captures frequency-based importance.
* Word2Vec captures semantic similarity and context.

---
**Q: What is out-of-vocabulary (OOV) problem? Which of the three methods — BoW, TF-IDF, Word2Vec — suffers from it and how?**

Out-of-vocabulary (OOV) problem occurs when a model encounters a word during testing that was not seen during training.

Effect on methods:

1. BoW

* Suffers from OOV.
* Unknown words are not present in the vocabulary, so they are ignored.

2. TF-IDF

* Also suffers from OOV.
* New words cannot get TF-IDF scores because they were not in the training vocabulary.

3. Word2Vec

* Suffers from OOV as well.
* No embedding vector exists for unseen words, so the model cannot represent them.
