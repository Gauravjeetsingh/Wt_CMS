
all: wtcms

wtcms: wtcms.o addPost.o showPost.o
	g++ wtcms.o addPost.o showPost.o -o wt  -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lwtdbo -lwtdbosqlite3

addPost.o:addPost.C
	g++ -std=c++11 -c addPost.C

showPost.o: showPost.C
	g++ -std=c++11 -c showPost.C

wtcms.o: wtcms.C
	g++ -std=c++0x -c wtcms.C

clean:
	rm -rvf *.o wt blog.db

run:
	./wt --docroot . --http-address 0.0.0.0 --http-port 1313
