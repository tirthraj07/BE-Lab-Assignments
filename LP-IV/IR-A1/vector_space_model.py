from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Documents
docs = [
    "Deep learning in AI",
    "Machine learning and AI"
]
query = ["Deep learning"]

# Step 1: Convert text to TF-IDF vectors
vectorizer = TfidfVectorizer()
tfidf_matrix = vectorizer.fit_transform(docs + query)

# Step 2: Compute cosine similarity between query and each document
similarities = cosine_similarity(tfidf_matrix[-1], tfidf_matrix[:-1])
print(similarities)
# Output: [[0.60832386 0.21173341]]
