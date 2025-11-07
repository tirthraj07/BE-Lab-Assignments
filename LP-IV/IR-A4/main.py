from collections import Counter
from multiprocessing import Pool, cpu_count

# Mapper: counts characters in a chunk
def mapper(chunk):
    return Counter(c for c in chunk.lower() if c.isalpha())

# Reducer: merges all counters
def reducer(counts_list):
    result = Counter()
    for counts in counts_list:
        result.update(counts)
    return result

if __name__ == "__main__":
    # Dataset
    data = "This is a sample dataset. Count the number of occurrences of each letter, case-insensitive."

    # Split into chunks for parallel processing
    num_workers = cpu_count()   # use number of CPU cores
    chunk_size = len(data) // num_workers or 1
    chunks = [data[i:i + chunk_size] for i in range(0, len(data), chunk_size)]

    # Map step (parallel)
    with Pool(processes=num_workers) as pool:
        mapped_counts = pool.map(mapper, chunks)

    # Reduce step
    final_counts = reducer(mapped_counts)

    # Print results (sorted by letter)
    for letter, count in sorted(final_counts.items()):
        print(f"{letter}: {count}")
