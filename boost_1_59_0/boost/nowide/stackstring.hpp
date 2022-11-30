//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_STACKSTRING_HPP_INCLUDED
#define BOOST_NOWIDE_STACKSTRING_HPP_INCLUDED

#include <boost/nowide/convert.hpp>
#include <boost/nowide/utf/utf.hpp>
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
        using output_char = CharOut;
        /// Type of the input character (converted from)
        using input_char = CharIn;

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
                return convert(input, input + utf::strlen(input));
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
                if(min_output_size <= buffer_size && utf::convert_buffer(buffer_, buffer_size, begin, end))
                    data_ = buffer_;
                else
                {
                    // Fallback: Allocate a buffer that is surely large enough on heap
                    // Max size: Every input char is transcoded to the output char with maximum with + trailing NULL
                    const size_t max_output_size = input_len * utf::utf_traits<output_char>::max_width + 1;
                    data_ = new output_char[max_output_size];
                    const bool success = utf::convert_buffer(data_, max_output_size, begin, end) == data_;
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
    using wstackstring = basic_stackstring<wchar_t, char, 256>;
    ///
    /// Convenience typedef
    ///
    using stackstring = basic_stackstring<char, wchar_t, 256>;
    ///
    /// Convenience typedef
    ///
    using wshort_stackstring = basic_stackstring<wchar_t, char, 16>;
    ///
    /// Convenience typedef
    ///
    using short_stackstring = basic_stackstring<char, wchar_t, 16>;

} // namespace nowide
} // namespace boost

#endif

/* stackstring.hpp
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
*/