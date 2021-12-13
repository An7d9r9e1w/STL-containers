test : test_dir/main.cpp
	g++ -Wall -Wextra -Werror -std=c++98 -o $@ $<

clean:
	rm test

re: clean test

opt1 : test_dir/main.cpp
	g++ -Wall -Wextra -Werror -std=c++98 -O1 -o test $<

opt2 : test_dir/main.cpp
	g++ -Wall -Wextra -Werror -std=c++98 -O2 -o test $<

opt3 : test_dir/main.cpp
	g++ -Wall -Wextra -Werror -std=c++98 -O3 -o test $<

.PHONY : clean re opt1 opt2 opt3
