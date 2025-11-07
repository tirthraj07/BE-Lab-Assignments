import time
import requests
from urllib.parse import urljoin
from bs4 import BeautifulSoup

def crawl(url, visited=None, depth=0, max_depth=2, delay=1.0):
    """Recursively crawl a website up to a specified depth."""
    if visited is None:
        visited = set()

    if depth > max_depth or url in visited:
        return visited

    print(f"[Depth {depth}] Crawling: {url}")
    visited.add(url)

    try:
        response = requests.get(url, headers={'User-Agent': 'Mozilla/5.0'}, timeout=10)
        response.raise_for_status()
    except requests.RequestException as e:
        print(f"Failed to fetch {url}: {e}")
        return visited

    soup = BeautifulSoup(response.text, 'html.parser')
    links = {
        urljoin(url, a['href'])
        for a in soup.find_all('a', href=True)
        if a['href'].startswith(('http', '/'))
    }

    print(f"Found {len(links)} links")
    time.sleep(delay)

    for link in links:
        if link not in visited:
            crawl(link, visited, depth + 1, max_depth, delay)

    return visited


if __name__ == "__main__":
    seed_url = "https://example.com"
    visited_pages = crawl(seed_url, max_depth=2, delay=1.0)

    print("\nCrawling finished")
    print(f"Total pages crawled: {len(visited_pages)}")

