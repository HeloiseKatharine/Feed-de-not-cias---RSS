
*****************Integrantes do grupo*****************

Heloise Katharine Pereira Silva 
Kacio Felipe 
Ruan Soares Barroso 
Jaied dos Santos Pires

*****************Instruções para a compilação*****************

-entre na pasta do trabalho e insira os seguintes comandos:

make all
./main


*****************Descrição do código*****************

Modulo: feed_rss.c 

Descrição: Faz a leitura de um arquivo RSS (Really Simple Syndication) .xml e gera um arquivo .html denominado "rss" com as seguintes informações das notícias e do canal:

Canal:
- Título do canal
- Descrição do canal
- Link do canal

Notícia:
- Título da notícia
- Descrição da notícia
- Link (se disponível)
- Data de publicação se disponível


Observações:

Ao gerar o arquivo .html é possivel que algumas tags como "<![CDATA[]]>" sejam escritas no arquivo, o que pode alterar algumas informações.


*****************Fonte de dados*****************

A fonte de dados escolhida foi retirada do New York Times.
link para download do feed ultilizado: https://rss.nytimes.com/services/xml/rss/nyt/World.xml

