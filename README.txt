
*****************Integrantes do grupo*****************

Heloise Katharine Pereira Silva 
Kacio Felipe 
Ruan Soares Barroso 
Jaied dos Santos Pires

*****************Instru��es para a compila��o*****************

-entre na pasta do trabalho e insira os seguintes comandos:

make all
./main


*****************Descri��o do c�digo*****************

Modulo: feed_rss.c 

Descri��o: Faz a leitura de um arquivo RSS (Really Simple Syndication) .xml e gera um arquivo .html denominado "rss" com as seguintes informa��es das not�cias e do canal:

Canal:
- T�tulo do canal
- Descri��o do canal
- Link do canal

Not�cia:
- T�tulo da not�cia
- Descri��o da not�cia
- Link (se dispon�vel)
- Data de publica��o se dispon�vel


Observa��es:

Ao gerar o arquivo .html � possivel que algumas tags como "<![CDATA[]]>" sejam escritas no arquivo, o que pode alterar algumas informa��es.


*****************Fonte de dados*****************

A fonte de dados escolhida foi retirada do New York Times.
link para download do feed ultilizado: https://rss.nytimes.com/services/xml/rss/nyt/World.xml

