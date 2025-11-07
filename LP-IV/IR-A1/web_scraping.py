import requests
from bs4 import BeautifulSoup

# Step 1: Send a request to the website
url = "https://quotes.toscrape.com/"
response = requests.get(url)

# Step 2: Parse the HTML content
soup = BeautifulSoup(response.text, "html.parser")

# Step 3: Find all quote elements
quotes = soup.find_all("span", class_="text")
authors = soup.find_all("small", class_="author")

# Step 4: Print extracted data
for i in range(len(quotes)):
    print(f"Quote: {quotes[i].text}")
    print(f"Author: {authors[i].text}")
    print("-" * 60)
