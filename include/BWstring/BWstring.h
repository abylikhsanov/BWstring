#ifndef __BWLIB__BWString__
#define __BWLIB__BWString__

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <memory>

#define __BWString__VERSION "0.0.1"
#define __BWString__MAX_LEN 65535
#define __BWString__MAX_SPLIT 1023

class BWString
{
	char* _str = nullptr;
	size_t _str_len = 0;
	using std::shared_ptr<BWString> = _bwsp;
	using std::unique_ptr<_bwsp[]> = _split_ptr;
	mutable _split_ptr _split_array;
	mutable size_t _split_count = 0;

	//private methods:
	void _reset_split_array() const;
	void _append_split_array(const BWString &s) const;

public:
	using _split_ptr = split_ptr;
	static const char* version() { return __BWString__VERSION; }
	BWString();
	BWString(const char* s);
	BWString(const BWString &);
	BWString(BWString &&) noexcept;
	~BWString();

	const char* alloc_str(size_t sz);
	void reset();
	void swap(BWString &b);
	const char* c_str() const;
	const char* copy_str(const char*);
	BWString &operator = (BWString);
	BWString &operator += (const char*);
	BWString &operator += (const BWString &);
	const char operator[] (const int) const;

	// comparison operators: (Note without &, left value can be R-value)
	bool operator == (const BWString &) const;
	bool operator != (const BWString &) const;
	bool operator > (const BWString &) const;
	bool operator < (const BWString &) const;
	bool operator >= (const BWString &) const;
	bool operator <= (const BWString &) const;

	// conversion operators
	operator const char * () const;

	bool have_value() const;
	size_t length() const { return _str_len; }
	size_t size() const { return _str_len; }
	BWString &format(const char* format, ...);
	BWString &trim();
	BWString lower() const;
	BWString upper() const;
	const char & back() const;
	const char & front() const;

	// find and replace methods
	long int char_find(const char &match) const;
	const BWString &char_repl(const char &match, const char &repl);
	BWString substr(size_t start, size_t length); // const
	long find(const BWString &match) const;
	const BWString replace(const BWString &match, const BWString &repl);

	// split methods
	const split_ptr &split(const char* match) const;
	const split_ptr &split(const char match) const;
	const split_ptr &split(const char* match, int max_split) const;
	const BWString &split_item(size_t index) const;
	size_t split_count() const { return _split_count; }

};

BWstring operator + (const BWString &lhs, const BWString &rhs);

#endif