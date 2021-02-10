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
AEnTVOfCOEZlRZvCdCePrd0gR8ZM6ZsUXGqoTSKyZ46oo86yLAuOQKgDOsUCZbah5DEtjLOpvIbYaWoEfrU1B74xCI5koO1MwZu2YUEkkzbce8GdPwvg3plMnFEwB/8WnNFcJ/vkjW6w9QzBCqCPeUElghfAsjxlNN5h/rir32r1D1WUHBVTVCoYIz3dVIiJIiDWyCYvxOO2B1OSUajeJZRolTYsTWFBYUU5LQhWbUQ1bSp0oOmGDkY74v3EeJSWMYW2Ruol7WNTRrOYLsqVMUulzwNECSkqHn/9DR+gfYfdF3CdijI+eeDtwd5Rsn9pqHBbkziMSJouSPSPZaK7uSrs+r2+7R84Ii5sWAsWQxf7RknWaf3Xgvo9kEyUXCGu8cTK9IsB9FEyoQgWvsUyQG982BCupK4RgC2tXeAlYNaUcktX0OmAzg3IUeGue/ZqgC++4sfSXDoVFW1D2CjfWqYC7Wg/T6hdvpnta6vVYrzq506F2WRYFXeNK+ga0h9gNBsOBztjJGI9FySa9aMb3jre0L0JvZEXaB8s+7j1eECVqRehS5ziOmMotRW6SVInt6GrsnyPVMljXFepWJA0ZLjvLI0Xfhz6V84wdIbDDpzUHPxPtWzLvMCSlpZUiI56tF9k6cAS5xKNcWMY
*/