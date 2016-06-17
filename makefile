FLAGS += -funsigned-char -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx

all: indexing #search

indexing: main.o tokenizer.o inverted_index.o func.o document.o stopwords.o inverted_index_anchor.o linkmap.o graph.o
	g++ -std=c++11 Document.o func.o Inverted_Index.o Inverted_Index_Anchor.o Tokenizer.o Stopwords.o linkmap.o graph.o main.o $(FLAGS) -o indexing 

main.o: main.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/indexer/Inverted_Index.h lib/indexer/Inverted_Index_Anchor.h lib/common/Document.h lib/common/linkmap.h
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
	mkdir util/htmls util/index util/index/split util/index/anchor util/index/anchor/split

remove_o:
	rm *.o

# search: main_search.o func.o document.o stopwords.o inverted_index.o inverted_index_anchor.o graph.o heap.o
	# g++ -std=c++11 PriorityQueue.o Document.o func.o Inverted_Index.o Inverted_Index_Anchor.o Tokenizer.o Stopwords.o linkmap.o graph.o boolean_search.o $(FLAGS) -o search

heap.o: lib/common/PriorityQueue.cpp lib/common/PriorityQueue.h
	g++ -std=c++11 $(FLAGS) -c lib/common/PriorityQueue.cpp

# main_search.o:
	# g++

# Run in ubuntu: export LD_LIBRARY_PATH="/usr/local/lib"
#ulimit -n MAX OPEN FILE

# ./indexing_full > full_index.out && ./indexing > short_index.out

