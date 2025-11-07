"""
Text Summarization is the process of automatically creating a shorter version of a text that retains 
its most important information and meaning.

There are two main types:
Extractive Summarization
Idea:
Select important sentences or phrases directly from the original text and combine them to form the summary.
It works by: Scoring sentences based on importance (e.g., using TF-IDF, word frequency, or similarity). Picking the top N sentences.

Abstractive Summarization
Idea:
Generate new sentences that convey the same meaning as the original text, similar to how humans summarize.
Works using: Deep learning and language models (like GPT, BART, T5, Pegasus).
"""

"""
Extractive Summarization Example:
"""

from sumy.parsers.plaintext import PlaintextParser
from sumy.nlp.tokenizers import Tokenizer
from sumy.summarizers.lex_rank import LexRankSummarizer

text = """
Artificial Intelligence is transforming industries by automating tasks,
analyzing data, and enabling smarter decision-making.
It is widely used in healthcare, finance, education, and many other fields.
"""

parser = PlaintextParser.from_string(text, Tokenizer("english"))
summarizer = LexRankSummarizer()
summary = summarizer(parser.document, 1)
print(" ".join(str(s) for s in summary)) 
# Artificial Intelligence is transforming industries by automating tasks, analyzing data, and enabling smarter decision-making.