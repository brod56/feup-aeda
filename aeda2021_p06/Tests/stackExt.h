# include <iostream>
# include <stack>
# include <stdexcept>

using namespace std;

template <class T>
class StackExt {
public:
	StackExt(): _values(), _mins() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
private:
	std::stack<T> _values;
	std::stack<T> _mins;
};

template <class T> 
bool StackExt<T>::empty() const
{
	return _values.empty();
}

template <class T> 
T& StackExt<T>::top()
{
    return _values.top();
}

template <class T> 
void StackExt<T>::pop()
{
    if (_values.empty()) throw std::logic_error("empty stack");
    if (_values.top() == _mins.top()){
        _mins.pop();
    }
    _values.pop();
}

template <class T> 
void StackExt<T>::push(const T & val)
{
    if (_values.empty() || val <= _mins.top()){
        _mins.push(val);
    }
    _values.push(val);
}

template <class T> 
T& StackExt<T>::findMin()
{
    if (_values.empty()) throw std::logic_error("empty stack");
    return _mins.top();
}

