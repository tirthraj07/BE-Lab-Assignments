import nltk
from nltk.corpus import stopwords
nltk.download('stopwords')  
from nltk.tokenize import word_tokenize

def preprocess_text(text):
    # Tokenization
    words = word_tokenize(text)

    # List of English stopwords
    stop_words = set(stopwords.words('english'))

    # Removal of stopwords
    filtered_words = [word for word in words if word.lower() not in stop_words]

    preprocessed_text = ' '.join(filtered_words)

    return preprocessed_text

if __name__ == "__main__":
    # Example
    text = "This is an example text document with some stop words that needa to be removed."

    # Text preprocessing
    preprocessed_text = preprocess_text(text)
    print("Original Text:")
    print(text)
    print("\nText after Stopword Removal:")
    print(preprocessed_text)
