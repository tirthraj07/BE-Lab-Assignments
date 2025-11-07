def pagerank(graph, damping_factor=0.85, max_iterations=100, tolerance=1e-6):
    num_pages = len(graph)

    # Initialization of PageRank values for all pages
    pagerank = {page: 1 / num_pages for page in graph}

    for _ in range(max_iterations):
        new_pagerank = {}
        total_pagerank = 0

        for page in graph:
            new_pagerank[page] = (1 - damping_factor) / num_pages

            for linking_page, outlinks in graph.items():
                if page in outlinks:
                    new_pagerank[page] += damping_factor * (pagerank[linking_page] / len(outlinks))

            total_pagerank += new_pagerank[page]

        # Checking convergence
        max_diff = max(abs(new_pagerank[page] - pagerank[page]) for page in graph)
        if max_diff < tolerance:
            break

        pagerank = new_pagerank

    return pagerank

if __name__ == "__main__":
    # Example 
    graph = {
        'A': ['B', 'C'],
        'B': ['A'],
        'C': ['A', 'B'],
        'D': ['B'],
    }

    result = pagerank(graph)
    sorted_result = dict(sorted(result.items(), key=lambda item: item[1], reverse=True))

    for page, score in sorted_result.items():
        print(f"Page: {page}, PageRank: {score:.4f}")
