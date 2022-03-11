//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CONVERT_HPP_INCLUDED
#define BOOST_NOWIDE_CONVERT_HPP_INCLUDED

#include <boost/nowide/detail/convert.hpp>
#include <string>

namespace boost {
namespace nowide {

    ///
    /// Convert wide string (UTF-16/32) in range [begin,end) to NULL terminated narrow string (UTF-8)
    /// stored in \a output of size \a output_size (including NULL)
    ///
    /// If there is not enough room NULL is returned, else output is returned.
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline char* narrow(char* output, size_t output_size, const wchar_t* begin, const wchar_t* end)
    {
        return detail::convert_buffer(output, output_size, begin, end);
    }
    ///
    /// Convert NULL terminated wide string (UTF-16/32) to NULL terminated narrow string (UTF-8)
    /// stored in \a output of size \a output_size (including NULL)
    ///
    /// If there is not enough room NULL is returned, else output is returned.
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline char* narrow(char* output, size_t output_size, const wchar_t* source)
    {
        return narrow(output, output_size, source, source + detail::strlen(source));
    }

    ///
    /// Convert narrow string (UTF-8) in range [begin,end) to NULL terminated wide string (UTF-16/32)
    /// stored in \a output of size \a output_size (including NULL)
    ///
    /// If there is not enough room NULL is returned, else output is returned.
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline wchar_t* widen(wchar_t* output, size_t output_size, const char* begin, const char* end)
    {
        return detail::convert_buffer(output, output_size, begin, end);
    }
    ///
    /// Convert NULL terminated narrow string (UTF-8) to NULL terminated wide string (UTF-16/32)
    /// most output_size (including NULL)
    ///
    /// If there is not enough room NULL is returned, else output is returned.
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline wchar_t* widen(wchar_t* output, size_t output_size, const char* source)
    {
        return widen(output, output_size, source, source + detail::strlen(source));
    }

    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s Input string
    /// \param count Number of characters to convert
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::string narrow(const wchar_t* s, size_t count)
    {
        return detail::convert_string<char>(s, s + count);
    }
    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s NULL terminated input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::string narrow(const wchar_t* s)
    {
        return narrow(s, detail::strlen(s));
    }
    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s Input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::string narrow(const std::wstring& s)
    {
        return narrow(s.c_str(), s.size());
    }

    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s Input string
    /// \param count Number of characters to convert
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::wstring widen(const char* s, size_t count)
    {
        return detail::convert_string<wchar_t>(s, s + count);
    }
    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s NULL terminated input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::wstring widen(const char* s)
    {
        return widen(s, detail::strlen(s));
    }
    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s Input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    inline std::wstring widen(const std::string& s)
    {
        return widen(s.c_str(), s.size());
    }
} // namespace nowide
} // namespace boost

#endif

/* convert.hpp
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
*/