## Assignment 04 - Transformers

**Q: Transformer**
A Transformer is a deep learning architecture introduced for sequence processing tasks like machine translation, text generation, summarization, and question answering.

It processes words in parallel using attention mechanisms instead of sequentially like RNNs or LSTMs.

Main idea:

* Learn relationships between words using self-attention.
* Capture long-range dependencies efficiently.

High-level Transformer architecture:
A standard Transformer has two main components:

1. Encoder

* Reads and understands the input sequence.

2. Decoder

* Generates the output sequence.

Multiple encoder and decoder layers are stacked together.

Encoder architecture:
Each encoder layer contains:

* Multi-head self-attention
* Feed-forward neural network
* Residual connections and layer normalization

Input to encoder:

* Token embeddings of the input sentence
* Positional encoding is added to preserve word order

Example input:
“I love NLP”

Output of encoder:

* Context-aware representations of every input token
* These representations are passed to the decoder

Decoder architecture:
Each decoder layer contains:

* Masked self-attention
* Encoder-decoder attention
* Feed-forward neural network
* Residual connections and normalization

Input to decoder:
The decoder takes two inputs:

1. Previously generated output tokens
2. Encoder output representations

The decoder predicts the next word one token at a time.

Is every Transformer an encoder-decoder?
No.

Types of Transformer models:

1. Encoder-only models

* Use only the encoder stack.
* Good for understanding tasks.

Examples:

* BERT
* RoBERTa

2. Decoder-only models

* Use only the decoder stack.
* Good for text generation.

Examples:

* GPT
* LLaMA

3. Encoder-decoder models

* Use both encoder and decoder.
* Good for sequence-to-sequence tasks.

Examples:

* T5
* BART

---
**Q: What is self-attention? What are Query, Key, and Value vectors in self-attention? What is the intuition behind each?**
Self-attention is a mechanism where each word in a sentence looks at other words in the same sentence to understand context and importance.

It helps the model capture relationships between words, even if they are far apart.

Example:
In “The animal didn’t cross the street because it was tired,”
self-attention helps identify that “it” refers to “animal”.

In self-attention, every word is converted into three vectors:

1. Query (Q)

* Represents what the current word is searching for.
* It asks: “Which other words are relevant to me?”

2. Key (K)

* Represents what information a word contains.
* It helps decide whether a word matches another word’s query.

3. Value (V)

* Represents the actual information/content of the word.
* This is the information passed forward after attention scores are calculated.

Intuition:

* Query = what I want
* Key = what I have
* Value = the information I give

Working:

* Query of one word is compared with Keys of all words.
* Similarity scores determine attention weights.
* Weighted combination of Values produces the final representation.

---
**Q: What is multi-head attention? Why use multiple heads instead of one? What does each attention head learn independently?**

Multi-head attention is an extension of self-attention where multiple attention mechanisms run in parallel.

Each attention head has its own Query, Key, and Value matrices and learns different relationships between words.

Why use multiple heads instead of one:

* A single attention head can focus on only one type of relationship at a time.
* Multiple heads allow the model to capture different patterns simultaneously.

Examples:

* One head may focus on grammar.
* Another may focus on semantic meaning.
* Another may focus on long-range dependencies.

What each head learns independently:

* Different contextual relationships between words.
* Different types of linguistic information such as:

  * Syntax
  * Semantics
  * Word dependencies
  * Positional relationships

The outputs of all heads are combined to form the final representation.

---
**Q: What were the limitations of RNNs and LSTMs that motivated the Transformer?**
Limitations of RNNs and LSTMs that motivated Transformers:

1. Sequential processing

* RNNs and LSTMs process words one by one.
* This makes training slow and difficult to parallelize.

2. Difficulty handling long-range dependencies

* Information from earlier words may get weakened over long sequences.
* Models struggle to remember distant context.

3. Vanishing and exploding gradient problems

* During training, gradients may become too small or too large, affecting learning.

4. Limited context capture

* Even LSTMs have limited memory capacity for very long sentences.

Transformers solved these issues using self-attention:

* Process all words in parallel.
* Capture long-distance relationships more effectively.
* Train faster on large datasets.

---

**Q: What is vanishing gradient problem in RNNs? Do Transformers suffer from it?**

The vanishing gradient problem occurs when gradients become extremely small during backpropagation through many time steps in RNNs.

As a result:

* Earlier layers learn very slowly.
* The model struggles to remember long-range information.

This happens because gradients are repeatedly multiplied during training.

Do Transformers suffer from it?

* Transformers are much less affected by the vanishing gradient problem.
* Because they do not process sequences recurrently over time.
* Self-attention creates direct connections between words, helping gradients flow more effectively.

---
**What is BERT? How does it use the Transformer architecture? Is BERT an encoder, decoder, or both? What is the difference between Word2Vec embeddings and BERT embeddings for the word "bank"?**
BERT (Bidirectional Encoder Representations from Transformers) is a pre-trained language model developed by Google for understanding natural language.

It uses the Transformer architecture to learn contextual representations of words.

How BERT uses Transformers:

* BERT uses only the encoder part of the Transformer.
* It processes text bidirectionally, meaning it looks at both left and right context simultaneously.

Example:
In “bank of river” and “bank account”, BERT understands different meanings of “bank” from context.

Is BERT an encoder, decoder, or both?

* BERT is an encoder-only Transformer model.

Difference between Word2Vec and BERT embeddings for “bank”:

Word2Vec:

* Produces one fixed embedding per word.
* “bank” has the same vector in all contexts.

BERT:

* Produces contextual embeddings.
* The embedding of “bank” changes depending on surrounding words.

Example:

* “river bank” → nature-related meaning
* “bank loan” → financial meaning

So BERT captures context-dependent meanings, while Word2Vec does not.

---
**Q: What is the difference between autoregressive and autoencoding Transformer models?**


Autoregressive Transformer models:

* Predict the next word using previous words.
* Generate text one token at a time.
* Mainly used for text generation tasks.

Example:

* GPT

Characteristics:

* Usually decoder-only models.
* Trained using left-to-right prediction.

Autoencoding Transformer models:

* Learn by masking some words and predicting the missing words.
* Used mainly for language understanding tasks.

Example:

* BERT

Characteristics:

* Usually encoder-only models.
* Use bidirectional context during training.

Difference:

* Autoregressive models generate text sequentially.
* Autoencoding models learn contextual understanding from masked text.

---
**Q: If you double the number of attention heads, does the model necessarily perform better? What is the tradeoff?**
No, increasing the number of attention heads does not necessarily improve performance.

Benefits:

* More heads can capture more types of relationships and patterns in text.

Tradeoffs:

* Increased computational cost and memory usage.
* Slower training and inference.
* Each head may get smaller representation size if total embedding size stays fixed.
* Too many heads can lead to redundant or less useful attention patterns.

So, performance improves only up to an optimal point.

---
**Q: What is the maximum sequence length limitation of Transformers and why does it exist?**
Transformers have a maximum sequence length, meaning they can process only a limited number of tokens at once.

Why it exists:

* Self-attention compares every token with every other token.
* This creates very high memory and computational cost.

Complexity:

* Time and memory grow proportional to the square of sequence length.

Example:

* If sequence length doubles, attention computation becomes roughly 4 times larger.

Another reason:

* Positional embeddings are usually trained only up to a fixed maximum length.

Because of this, many Transformer models use limits like:

* 512 tokens
* 1024 tokens
* 4096 tokens, etc.

---