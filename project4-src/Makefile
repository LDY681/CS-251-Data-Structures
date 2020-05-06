CC = g++
CFLAGS = -std=c++11 -g -I/homes/cs251/Spring2018/libcurl/include
LIBS = -L/homes/cs251/Spring2018/libcurl/lib \
	-lcurl

all: gethtml scan search

gethtml: gethtml.o SimpleHTMLParser.o
	$(CC) -o $@ $^ $(LIBS)
scan: scan.o SimpleHTMLParser.o
	$(CC) -o $@ $^ $(LIBS)
search: search.o
	$(CC) -o $@ $^

SimpleHTMLParser.o: SimpleHTMLParser.cpp SimpleHTMLParser.h
	$(CC) $(CFLAGS) -o $@ -c $<
gethtml.o: gethtml.cpp SimpleHTMLParser.h
	$(CC) $(CFLAGS) -o $@ -c $<
scan.o: scan.cpp SimpleHTMLParser.h RBTree.h Node.h
	$(CC) $(CFLAGS) -o $@ -c $<
search.o: search.cpp RBTree.h Node.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o gethtml scan search
