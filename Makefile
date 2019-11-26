all: tweetprocess
tweetprocess:
	gcc -Wall -Werror -g -o tweetprocess maxTweet.c
tweetprocess.o: maxTweet.c
	gcc -Wall -Werror -c -g -o .o maxTweet.c
clean:
	rm -f tweetprocess.o tweetprocess