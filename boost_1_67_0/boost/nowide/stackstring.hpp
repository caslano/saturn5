//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_STACKSTRING_HPP_INCLUDED
#define BOOST_NOWIDE_STACKSTRING_HPP_INCLUDED

#include <boost/nowide/convert.hpp>
#include <cassert>
#include <cstring>

namespace boost {
namespace nowide {

    ///
    /// \brief A class that allows to create a temporary wide or narrow UTF strings from
    /// wide or narrow UTF source.
    ///
    /// It uses a stack buffer if the string is short enough
    /// otherwise allocates a buffer on the heap.
    ///
    /// Invalid UTF characters are replaced by the substitution character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    /// If a NULL pointer is passed to the constructor or convert method, NULL will be returned by c_str.
    /// Similarily a default constructed stackstring will return NULL on calling c_str.
    ///
    template<typename CharOut = wchar_t, typename CharIn = char, size_t BufferSize = 256>
    class basic_stackstring
    {
    public:
        /// Size of the stack buffer
        static const size_t buffer_size = BufferSize;
        /// Type of the output character (converted to)
        typedef CharOut output_char;
        /// Type of the input character (converted from)
        typedef CharIn input_char;

        /// Creates a NULL stackstring
        basic_stackstring() : data_(NULL)
        {
            buffer_[0] = 0;
        }
        /// Convert the NULL terminated string input and store in internal buffer
        /// If input is NULL, nothing will be stored
        explicit basic_stackstring(const input_char* input) : data_(NULL)
        {
            convert(input);
        }
        /// Convert the sequence [begin, end) and store in internal buffer
        /// If begin is NULL, nothing will be stored
        basic_stackstring(const input_char* begin, const input_char* end) : data_(NULL)
        {
            convert(begin, end);
        }
        /// Copy construct from other
        basic_stackstring(const basic_stackstring& other) : data_(NULL)
        {
            *this = other;
        }
        /// Copy assign from other
        basic_stackstring& operator=(const basic_stackstring& other)
        {
            if(this != &other)
            {
                clear();
                const size_t len = other.length();
                if(other.uses_stack_memory())
                    data_ = buffer_;
                else if(other.data_)
                    data_ = new output_char[len + 1];
                else
                {
                    data_ = NULL;
                    return *this;
                }
                std::memcpy(data_, other.data_, sizeof(output_char) * (len + 1));
            }
            return *this;
        }

        ~basic_stackstring()
        {
            clear();
        }

        /// Convert the NULL terminated string input and store in internal buffer
        /// If input is NULL, the current buffer will be reset to NULL
        output_char* convert(const input_char* input)
        {
            if(input)
                return convert(input, input + detail::strlen(input));
            clear();
            return get();
        }
        /// Convert the sequence [begin, end) and store in internal buffer
        /// If begin is NULL, the current buffer will be reset to NULL
        output_char* convert(const input_char* begin, const input_char* end)
        {
            clear();

            if(begin)
            {
                const size_t input_len = end - begin;
                // Minimum size required: 1 output char per input char + trailing NULL
                const size_t min_output_size = input_len + 1;
                // If there is a chance the converted string fits on stack, try it
                if(min_output_size <= buffer_size && detail::convert_buffer(buffer_, buffer_size, begin, end))
                    data_ = buffer_;
                else
                {
                    // Fallback: Allocate a buffer that is surely large enough on heap
                    // Max size: Every input char is transcoded to the output char with maximum with + trailing NULL
                    const size_t max_output_size = input_len * detail::utf::utf_traits<output_char>::max_width + 1;
                    data_ = new output_char[max_output_size];
                    const bool success = detail::convert_buffer(data_, max_output_size, begin, end) == data_;
                    assert(success);
                    (void)success;
                }
            }
            return get();
        }
        /// Return the converted, NULL-terminated string or NULL if no string was converted
        output_char* get()
        {
            return data_;
        }
        /// Return the converted, NULL-terminated string or NULL if no string was converted
        const output_char* get() const
        {
            return data_;
        }
        /// Reset the internal buffer to NULL
        void clear()
        {
            if(!uses_stack_memory())
                delete[] data_;
            data_ = NULL;
        }
        /// Swap lhs with rhs
        friend void swap(basic_stackstring& lhs, basic_stackstring& rhs)
        {
            if(lhs.uses_stack_memory())
            {
                if(rhs.uses_stack_memory())
                {
                    for(size_t i = 0; i < buffer_size; i++)
                        std::swap(lhs.buffer_[i], rhs.buffer_[i]);
                } else
                {
                    lhs.data_ = rhs.data_;
                    rhs.data_ = rhs.buffer_;
                    for(size_t i = 0; i < buffer_size; i++)
                        rhs.buffer_[i] = lhs.buffer_[i];
                }
            } else if(rhs.uses_stack_memory())
            {
                rhs.data_ = lhs.data_;
                lhs.data_ = lhs.buffer_;
                for(size_t i = 0; i < buffer_size; i++)
                    lhs.buffer_[i] = rhs.buffer_[i];
            } else
                std::swap(lhs.data_, rhs.data_);
        }

    protected:
        /// True if the stack memory is used
        bool uses_stack_memory() const
        {
            return data_ == buffer_;
        }
        /// Return the current length of the string excluding the NULL terminator
        /// If NULL is stored returns NULL
        size_t length() const
        {
            if(!data_)
                return 0;
            size_t len = 0;
            while(data_[len])
                len++;
            return len;
        }

    private:
        output_char buffer_[buffer_size];
        output_char* data_;
    }; // basic_stackstring

    ///
    /// Convenience typedef
    ///
    typedef basic_stackstring<wchar_t, char, 256> wstackstring;
    ///
    /// Convenience typedef
    ///
    typedef basic_stackstring<char, wchar_t, 256> stackstring;
    ///
    /// Convenience typedef
    ///
    typedef basic_stackstring<wchar_t, char, 16> wshort_stackstring;
    ///
    /// Convenience typedef
    ///
    typedef basic_stackstring<char, wchar_t, 16> short_stackstring;

} // namespace nowide
} // namespace boost

#endif

/* stackstring.hpp
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
*/