//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CONVERT_HPP_INCLUDED
#define BOOST_NOWIDE_CONVERT_HPP_INCLUDED

#include <boost/nowide/detail/is_string_container.hpp>
#include <boost/nowide/utf/convert.hpp>
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
        return utf::convert_buffer(output, output_size, begin, end);
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
        return narrow(output, output_size, source, source + utf::strlen(source));
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
        return utf::convert_buffer(output, output_size, begin, end);
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
        return widen(output, output_size, source, source + utf::strlen(source));
    }

    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s Input string
    /// \param count Number of characters to convert
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename T_Char, typename = detail::requires_wide_char<T_Char>>
    inline std::string narrow(const T_Char* s, size_t count)
    {
        return utf::convert_string<char>(s, s + count);
    }
    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s NULL terminated input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename T_Char, typename = detail::requires_wide_char<T_Char>>
    inline std::string narrow(const T_Char* s)
    {
        return narrow(s, utf::strlen(s));
    }
    ///
    /// Convert wide string (UTF-16/32) to narrow string (UTF-8).
    ///
    /// \param s Input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename StringOrStringView, typename = detail::requires_wide_string_container<StringOrStringView>>
    inline std::string narrow(const StringOrStringView& s)
    {
        return utf::convert_string<char>(s.data(), s.data() + s.size());
    }

    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s Input string
    /// \param count Number of characters to convert
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename T_Char, typename = detail::requires_narrow_char<T_Char>>
    inline std::wstring widen(const T_Char* s, size_t count)
    {
        return utf::convert_string<wchar_t>(s, s + count);
    }
    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s NULL terminated input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename T_Char, typename = detail::requires_narrow_char<T_Char>>
    inline std::wstring widen(const T_Char* s)
    {
        return widen(s, utf::strlen(s));
    }
    ///
    /// Convert narrow string (UTF-8) to wide string (UTF-16/32).
    ///
    /// \param s Input string
    /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    ///
    template<typename StringOrStringView, typename = detail::requires_narrow_string_container<StringOrStringView>>
    inline std::wstring widen(const StringOrStringView& s)
    {
        return utf::convert_string<wchar_t>(s.data(), s.data() + s.size());
    }
} // namespace nowide
} // namespace boost

#endif

/* convert.hpp
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
*/