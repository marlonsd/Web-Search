FLAGS += -funsigned-char -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx

all: indexing bsearch 

indexing: main.o tokenizer.o inverted_index.o func.o document.o graph.o
	g++ -std=c++11 Document.o func.o Inverted_Index.o Tokenizer.o graph.o main.o $(FLAGS) -o indexing 

main.o: main.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/indexer/Inverted_Index.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c main.cpp

inverted_index.o: lib/indexer/Inverted_Index.cpp lib/indexer/Inverted_Index.h lib/indexer/Tokenizer.h lib/common/func.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/indexer/Inverted_Index.cpp

tokenizer.o: lib/indexer/Tokenizer.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/indexer/Tokenizer.cpp

func.o: lib/common/func.cpp lib/common/func.h
	g++ -std=c++11 $(FLAGS) -c lib/common/func.cpp		

document.o: lib/common/Document.cpp lib/common/Document.h lib/common/func.h
	g++ -std=c++11 $(FLAGS) -c lib/common/document.cpp		

graph.o: lib/search/graph.cpp lib/search/graph.h lib/common/func.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/search/graph.cpp

clean:
	rm *.o indexing search

bsearch: bsearch.o tokenizer.o inverted_index.o func.o
	g++ -std=c++11 func.o Inverted_Index.o Tokenizer.o boolean_search.o $(FLAGS) -o search

bsearch.o: lib/search/boolean_search.cpp lib/indexer/Tokenizer.h lib/common/func.h lib/indexer/Inverted_Index.h lib/common/Document.h
	g++ -std=c++11 $(FLAGS) -c lib/search/boolean_search.cpp

dir:
	mkdir util/htmls util/index util/index/split

remove_o:
	rm *.o

# Run in ubuntu: export LD_LIBRARY_PATH="/usr/local/lib"
#ulimit -n MAX OPEN FILE

# ./indexing_full > full_index.out && ./indexing > short_index.out

