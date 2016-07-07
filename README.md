# Search Engine

Para executar, necessário instalar htmlcxx [http://htmlcxx.sourceforge.net].

No terminal, criar pastas:
  $ make dir
  
Compilar código, no terminal:
  $ make
  
Antes de executar:
  ulimit -n 4000 # Para mudar valor, deve-se mudar no código.
  
  export LD_LIBRARY_PATH="/usr/local/lib"
  
Para executar indexação, htmls devem estar na pasta htmls:
  ./indexing
  
Na indexação já há a geração dos pesos wd dos documentos e o pagerank.

Para busca:
  ./search

Para ajustar os pesos considerados do pagerank e anchor text, ajustar em search/main_search.cpp os defines ANCHOR_TEXT e PAGERANK, valores default 0.25 e 0.3.

Para executar o servidor, mover para pastar server. Lá
  cmake .
  make
  ./http_examples

Acessar o servidor em [http://localhost:8080/].
Servidor baseado no trabalho de eidheim [https://github.com/eidheim/Simple-Web-Server]
  
