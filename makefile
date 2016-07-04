FLAGS += -funsigned-char -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx

all: indexing search

indexing: main.o tokenizer.o inverted_index.o func.o document.o stopwords.o inverted_index_anchor.o linkmap.o graph.o pagerank.o
	g++ -std=c++11 Document.o func.o Inverted_Index.o Inverted_Index_Anchor.o Tokenizer.o Stopwords.o linkmap.o graph.o pagerank.o main.o $(FLAGS) -o indexing

main.o: main.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/indexer/Inverted_Index.h lib/indexer/Inverted_Index_Anchor.h lib/common/Document.h lib/common/linkmap.h lib/search/pagerank.h
	g++ -std=c++11 $(FLAGS) -c main.cpp

inverted_index.o: lib/indexer/Inverted_Index.cpp lib/indexer/Inverted_Index.h lib/indexer/Tokenizer.h lib/common/func.h lib/common/Stopwords.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/indexer/Inverted_Index.cpp

tokenizer.o: lib/indexer/Tokenizer.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/indexer/Tokenizer.cpp

func.o: lib/common/func.cpp lib/common/func.h
	g++ -std=c++11 $(FLAGS) -c lib/common/func.cpp

document.o: lib/common/Document.cpp lib/common/Document.h lib/common/func.h lib/common/linkmap.h
	g++ -std=c++11 $(FLAGS) -c lib/common/Document.cpp

graph.o: lib/search/graph.cpp lib/search/graph.h lib/common/func.h lib/common/Document.h lib/common/linkmap.h
	g++ -std=c++11 $(FLAGS) -c lib/search/graph.cpp

stopwords.o: lib/common/Stopwords.cpp lib/common/Stopwords.h lib/common/func.h
	g++ -std=c++11 $(FLAGS) -c lib/common/Stopwords.cpp

linkmap.o: lib/common/linkmap.cpp lib/common/linkmap.h lib/common/func.h
	g++ -std=c++11 $(FLAGS) -c lib/common/linkmap.cpp

inverted_index_anchor.o: lib/indexer/Inverted_Index_Anchor.cpp lib/indexer/Inverted_Index_Anchor.h lib/indexer/Tokenizer.h lib/common/func.h lib/common/Document.h lib/common/Stopwords.h
	g++ -std=c++11 $(FLAGS) -c lib/indexer/Inverted_Index_Anchor.cpp

clean:
	rm *.o indexing search

dir:
	mkdir util/htmls util/index util/index/split util/index/anchor util/index/anchor/split util/pagerank

remove_o:
	rm *.o

search: main_search.o func.o pagerank.o document.o stopwords.o inverted_index.o inverted_index_anchor.o graph.o heap.o search.o v_search.o linkmap.o tokenizer.o
	g++ -std=c++11 PriorityQueue.o Document.o pagerank.o func.o Inverted_Index.o Inverted_Index_Anchor.o Tokenizer.o Stopwords.o search.o vectorialsearch.o linkmap.o graph.o main_search.o $(FLAGS) -o search

main_search.o: lib/search/main_search.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/indexer/Inverted_Index.h lib/indexer/Inverted_Index_Anchor.h lib/common/Document.h lib/common/linkmap.h lib/common/Stopwords.h lib/common/PriorityQueue.h lib/search/graph.h lib/search/search.h lib/search/vectorialsearch.h lib/search/pagerank.h
	g++ -std=c++11 $(FLAGS) -c lib/search/main_search.cpp

heap.o: lib/common/PriorityQueue.cpp lib/common/PriorityQueue.h
	g++ -std=c++11 $(FLAGS) -c lib/common/PriorityQueue.cpp

search.o: lib/search/search.cpp lib/search/search.h lib/common/PriorityQueue.h lib/common/func.h lib/common/Document.h lib/indexer/Inverted_Index.h lib/indexer/Inverted_Index_Anchor.h
	g++ -std=c++11 $(FLAGS) -c lib/search/search.cpp

v_search.o: lib/search/vectorialsearch.cpp lib/search/vectorialsearch.h lib/search/search.h lib/common/PriorityQueue.h lib/common/func.h lib/common/Document.h lib/indexer/Inverted_Index.h lib/indexer/Inverted_Index_Anchor.h
	g++ -std=c++11 $(FLAGS) -c lib/search/vectorialsearch.cpp

pagerank.o: lib/search/pagerank.cpp lib/search/pagerank.h lib/common/func.h lib/common/linkmap.h lib/common/Document.h lib/search/graph.h
	g++ -std=c++11 $(FLAGS) -c lib/search/pagerank.cpp

# Run in ubuntu: export LD_LIBRARY_PATH="/usr/local/lib"
#ulimit -n MAX OPEN FILE

# ./indexing_full > full_index.out && ./indexing > short_index.out
