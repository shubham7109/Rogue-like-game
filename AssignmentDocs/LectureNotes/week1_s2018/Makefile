#target: dependency list
#	rule to build target from dependencies

all: hello hello.class times_tables

hello: hello.c
	gcc hello.c -o hello

hello.class: hello.java
	javac hello.java

times_tables: times_tables.c
	gcc times_tables.c -o times_tables

clean:
	rm -f hello hello.class

