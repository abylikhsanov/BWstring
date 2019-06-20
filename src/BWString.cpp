//
// Created by abyl on 20.06.19.
//

#include "BWstring/BWstring.h"

namespace bwstring
{
    // Constructors and destructor:
    BWString::BWString(const char *s)
    {
        this->copy_str(s);

    }

    BWString::BWString(const BWString &old)
    {
        this->copy_str(old);
    }

    BWString::~BWString()
    {
        reset();
    }

    // Move semantics:
    BWString::BWString(BWString &&other) noexcept
    {
        reset();
        _str = other._str;
        _str_len = other._str_len;
        _str = nullptr;
        _str_len = 0;
        other.reset();
    }

    // Private methods:
    void BWString::_reset_split_array() const
    {
        if (_split_count) while (_split_count) _split_array[--_split_count].reset();
        _split_array.reset();
        _split_count = 0;

    }

    void BWString::_append_split_array(const bwstring::BWString &s) const
    {
        if (_split_count >= __BWString__MAX_SPLIT) return;
        if (!_split_count) _split_array.reset(new bwsp[__BWString__MAX_SPLIT + 1]);
        _split_array[_split_count] = std::make_shared<BWString>(s);
        ++_split_count;
    }

    void BWString::reset()
    {
        this->_reset_split_array();
        if (_str) delete[] _str;
        _str = nullptr;
        _str_len = 0;
    }

    void BWString::alloc_str(size_t sz)
    {
        if (_str) reset();
        this->_str_len = sz > __BWString__MAX_LEN ? __BWString__MAX_LEN : sz;
        this->_str = new char[sz + 1]();
    }

    const char* BWString::copy_str(const char *s)
    {
        if (s)
        {
            size_t size = strnlen(s, __BWString__MAX_LEN);
            this->alloc_str(size);
            strncpy(static_cast<char*>(_str), s, size);
        }
        return _str;
    }
}