#ifndef SINGLETONT_H
#define SINGLETONT_H

// my singleton class template
// slight error with it, didn't end up using this
template <typename T> 
class SingletonT {
public:
	// delete the copy and move constructors
	SingletonT(const SingletonT&) = delete;
	SingletonT(SingletonT&&) = delete;
	SingletonT& operator = (const SingletonT&) = delete;
	SingletonT& operator = (SingletonT&&) = delete;

	static T* GetInstance();

public:
	SingletonT();
	~SingletonT();
	static std::unique_ptr<T> instance;
	friend std::default_delete<T>;
};

#endif