import nltk
nltk.download('punkt')

from nltk.tokenize import word_tokenize, sent_tokenize

text = "AI is transforming the world. It's fascinating!"

# Word tokenization
print(word_tokenize(text))

# Sentence tokenization
print(sent_tokenize(text))

