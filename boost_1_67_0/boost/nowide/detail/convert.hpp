//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_DETAIL_CONVERT_HPP_INCLUDED
#define BOOST_NOWIDE_DETAIL_CONVERT_HPP_INCLUDED

#include <boost/nowide/detail/utf.hpp>
#include <boost/nowide/replacement.hpp>
#include <iterator>
#include <string>

namespace boost {
namespace nowide {
    /// \cond INTERNAL
    namespace detail {
        ///
        /// Convert a buffer of UTF sequences in the range [source_begin, source_end)
        /// from \tparam CharIn to \tparam CharOut to the output \a buffer of size \a buffer_size.
        ///
        /// \return original buffer containing the NULL terminated string or NULL
        ///
        /// If there is not enough room in the buffer NULL is returned, and the content of the buffer is undefined.
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        ///
        template<typename CharOut, typename CharIn>
        CharOut*
        convert_buffer(CharOut* buffer, size_t buffer_size, const CharIn* source_begin, const CharIn* source_end)
        {
            CharOut* rv = buffer;
            if(buffer_size == 0)
                return 0;
            buffer_size--;
            while(source_begin != source_end)
            {
                using namespace detail::utf;
                code_point c = utf_traits<CharIn>::template decode(source_begin, source_end);
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
                buffer = utf_traits<CharOut>::template encode(c, buffer);
                buffer_size -= width;
            }
            *buffer++ = 0;
            return rv;
        }

        ///
        /// Convert the UTF sequences in range [begin, end) from \tparam CharIn to \tparam CharOut
        /// and return it as a string
        ///
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        ///
        template<typename CharOut, typename CharIn>
        std::basic_string<CharOut> convert_string(const CharIn* begin, const CharIn* end)
        {
            std::basic_string<CharOut> result;
            result.reserve(end - begin);
            typedef std::back_insert_iterator<std::basic_string<CharOut> > inserter_type;
            inserter_type inserter(result);
            using namespace detail::utf;
            code_point c;
            while(begin != end)
            {
                c = utf_traits<CharIn>::template decode(begin, end);
                if(c == illegal || c == incomplete)
                {
                    c = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                utf_traits<CharOut>::template encode(c, inserter);
            }
            return result;
        }

        /// Return the length of the given string.
        /// That is the number of characters until the first NULL character
        /// Equivalent to `std::strlen(s)` but can handle wide-strings
        template<typename Char>
        size_t strlen(const Char* s)
        {
            const Char* end = s;
            while(*end)
                end++;
            return end - s;
        }

    } // namespace detail
      /// \endcond
} // namespace nowide
} // namespace boost

#endif

/* convert.hpp
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
*/