//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_UTF_CONVERT_HPP_INCLUDED
#define BOOST_NOWIDE_UTF_CONVERT_HPP_INCLUDED

#include <boost/nowide/detail/is_string_container.hpp>
#include <boost/nowide/replacement.hpp>
#include <boost/nowide/utf/utf.hpp>
#include <iterator>
#include <string>

namespace boost {
namespace nowide {
    namespace utf {

        /// Return the length of the given string in code units.
        /// That is the number of elements of type Char until the first NULL character.
        /// Equivalent to `std::strlen(s)` but can handle wide-strings
        template<typename Char>
        size_t strlen(const Char* s)
        {
            const Char* end = s;
            while(*end)
                end++;
            return end - s;
        }

        /// Convert a buffer of UTF sequences in the range [source_begin, source_end)
        /// from \a CharIn to \a CharOut to the output \a buffer of size \a buffer_size.
        ///
        /// \return original buffer containing the NULL terminated string or NULL
        ///
        /// If there is not enough room in the buffer NULL is returned, and the content of the buffer is undefined.
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        template<typename CharOut, typename CharIn>
        CharOut*
        convert_buffer(CharOut* buffer, size_t buffer_size, const CharIn* source_begin, const CharIn* source_end)
        {
            CharOut* rv = buffer;
            if(buffer_size == 0)
                return nullptr;
            buffer_size--;
            while(source_begin != source_end)
            {
                code_point c = utf_traits<CharIn>::decode(source_begin, source_end);
                if(c == illegal || c == incomplete)
                {
                    c = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                size_t width = utf_traits<CharOut>::width(c);
                if(buffer_size < width)
                {
                    rv = NULL;
                    break;
                }
                buffer = utf_traits<CharOut>::encode(c, buffer);
                buffer_size -= width;
            }
            *buffer++ = 0;
            return rv;
        }

        /// Convert the UTF sequences in range [begin, end) from \a CharIn to \a CharOut
        /// and return it as a string
        ///
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        /// \tparam CharOut Output character type
        template<typename CharOut, typename CharIn>
        std::basic_string<CharOut> convert_string(const CharIn* begin, const CharIn* end)
        {
            std::basic_string<CharOut> result;
            result.reserve(end - begin);
            using inserter_type = std::back_insert_iterator<std::basic_string<CharOut>>;
            inserter_type inserter(result);
            code_point c;
            while(begin != end)
            {
                c = utf_traits<CharIn>::decode(begin, end);
                if(c == illegal || c == incomplete)
                {
                    c = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                utf_traits<CharOut>::encode(c, inserter);
            }
            return result;
        }

    } // namespace utf
} // namespace nowide
} // namespace boost

#endif

/* convert.hpp
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
*/