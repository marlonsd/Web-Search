#ifndef STOPWORDS_H
#define STOPWORDS_H

#include "../common/func.h"

using namespace std;

class Stopwords {
private:
	unordered_set<string> words;
	static Stopwords *s_instance;

	Stopwords(string path);
	void load_words(string path);

public:

	unordered_set<string> get_value();
	void set_value(string path);

	static Stopwords *instance(string path = STOPWORDS_PATH){
		if (!s_instance){
			s_instance = new Stopwords(path);
		}

		return s_instance;
	}
};

#endif

// Stopwords *Stopwords::s_instance = 0;

// void foo(void)
// {
// 	Stopwords::instance()->set_value(1);
// 	cout << "foo: global_ptr is " << Stopwords::instance()->get_value() << '\n';
// }

// void bar(void)
// {
// 	Stopwords::instance()->set_value(2);
// 	cout << "bar: global_ptr is " << Stopwords::instance()->get_value() << '\n';
// }

// int main()
// {
// 	cout << "main: global_ptr is " << Stopwords::instance()->get_value() << '\n';
// 	foo();
// 	bar();
// }