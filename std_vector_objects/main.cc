#include<iostream>
#include<vector>
#include<functional>
/* integer: a sample class
 * */
class integer {
private:
	int data;
public:
	integer(int value = 0): data(value) {}
	~integer() {
		std::cout<<"destructor "<<data<<" is called!"<<std::endl;
	}
	void increase() {
		data++;
	}
	friend std::ostream& operator<<(std::ostream& os, const integer& x);
};
/* std::ostream overriding
 * */
std::ostream& operator<<(std::ostream& os, const integer& x) {
	os << x.data;
	return os;
}
/* std::reference_wrapper is used to passing reference in container (std::vector)
 * */
void foo(const std::vector<std::reference_wrapper<integer>>& vec) {
	for (auto it = vec.begin(); it != vec.end(); it++) {
		(*it).get().increase();
	}
}
/* std::vector::reserve is used to reserve the data for vector. emplace new objects in vector will call destructors due to underlying implementation of container
 * */
std::vector<integer> bar(const std::vector<int>& src) {
	std::vector<integer> vec;
	vec.reserve(src.size());
	for (auto it = src.begin(); it!= src.end(); it++) {
		vec.emplace_back(*it);
	}
	return vec;
}
int main() {
{
	std::cout<<"\nFoo test:"<<std::endl;
	std::cout<<"3 destructors is passed!"<<std::endl;
	integer x1(3);
	integer x2(4);
	integer x3(5);

	std::cout << x1 << " " << x2 << " " << x3 << std::endl;
	foo({x1, x2, x3});
	std::cout << x1 << " " << x2 << " " << x3 << std::endl;
}
{
	std::cout<<"\nBar test:"<<std::endl;
	std::cout<<"7 destructors is passed!"<<std::endl;
	bar({1, 2, 3, 4, 5, 6, 7});
}
	return 0;
}
