all: main.o


main.o: feed_rss.o

gcc main.c feed_rss.o  -o feed_rss.o: 


gcc -c feed_rss.c feed_rss.o 

rm: 

rm *.o