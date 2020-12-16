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
texiD7OWC4tgf/DU1sf+3ffXk9DvZGuZfcgThxgS6ujH0ozxk+V1Tl063jJL9cowGG1GlpfZ7Mv31yJPsl+YXdqyoRjS1bNjneC0c6pf8rU5gr4lu86s1z/XOyKGULs4wczvrldfWH19nsNSppoRQwO7KGOX9mPcc3l9294ufvORtmvruiHIs7Md6/q1STtvnbrjBMZSV7vYwKxG8bohiIHsPjP7lJRkpOtuFzeZDTngro9x1kNfXuy1OZ0xznrKebc1/b2ZfEC+29mLjg/e0ma2z5OCdAPs4h1L97LSpnxIF6GNCc36pF6ARQ+i6z9mNTtZxsMG20VDZvP/eOdE7GRZWXnb3t/qhH4Yahc9WDpboeBy6AeyK8waP87mwb4yzC4imE3/t2E0xvxwu/iOlRd+7+t8xBdpx2/Jrehv53snJqNdRtpFZyHNdPFwCtKRDWC2xDvZghhG2UUmluft6XJtu7gou3ioWUsTtdOdQs/Q72Pp/Nrrm7VI678rY2BhE+jaQkhbfeS+fN6UrIY2PpvThv4zd7oQ+zRtDtEsf7vsK1HedNo3Ycqzd2QtvKXNr5NF/sY3xy4usXRl/z28Hu0SQ/cZWF2ahUTPRJ6L7fj9oRltWNHj4D7UkyyMWf1uK+Qa+mRFmW2dPwVzpGsJjWtmtda2mog5hKwRs9WnO2HfTGYWRhuy1x8hv/vxE52jMIvM7g5EW5Nt0eJrShtWftf+e4zrOLsYK6S1KNFJPl+3ks6Fmdk2Df8L+/QqfboHHWoWRHlkv5qkLW44ozzKW2PHe+VNTGnfMvk3BG29lu4XmKT1Lrz/J4zPddr9Cc0K3NgVir41MLGe5l1mS4fcyI1+2EDtycy78xv5nrdiLWr+Ls+lyEKZbZgWVwoxbNTbrJA999C3ZI2ZhaXu3o2+JbPAlHdUNskx3zhtHrxy7AHKI2thkta21MnsaOvN2n0Gza5l2GuDbbGLQ8wmtSjTALaV6gJT3iEmy6bt76G0oWL8JdQlcTvdE2BWct9v1dF/u+3imre08idzwsL+S+caWrp6aeX5yW/uxR2yi58zSMtYNRLlJZ+0i+Y+0ppOf5Ed6RK1fVOzgR1i96Pfz9F9G5j+d203WTSry9mbqT+h/y7ZRX1mL9ackWtgXrOLfCZpWV6NPYh95YZd3GD1XDxvVE65NppdFBAw3e/T8WRBzOLNfeW3QMnGM3s2q8Yo1PMunRfA9M9kJBqY6x4dj5iVGR0g32Eky2yWtj7fgOLo24d2UYnF/qRXhroo75G+rW93b7QO/Uc2m+V5sa24jn54po9v5cMi8xA7GWJQnskIem4XVWD6ZzIiyBCf8kyG+JfuOcL0z2S4yZ6y+Pxjz/dEuyTbRXtmRfIFLMC4fknjU0i71GBNAOZIMgtM+f2ILFyzumnXzDeuIYawV3axjdmkdU3uop6v6ZrLJG1nnmP95bOFWnmaNW9jG47xotjqtpuvIj7F9td1yfu7ZE2ZFS78Miv64a0+3aHxqXtRT7JAZv73L+M47VGs3Zf2h1FPslXMSqQc/xnp3tlFDmbDL/kUR+xkj5n57GhcCjG8p3tkzDplTpXzGdklZi3z91+FMfiB5nJmRftHyvWlPtpFsFnavLl9u2GcfaZzMJO0xgfdi1HeFzt+P6qTVs/cof8g3Vd5rV2bNiz4s6Fc75CslZe0bN7hXmgXL4fozNL1n9H2R8RA1pTZjADXVvn7ikPsZObqnVoL8fk4hB9M/5ychywrTHnW1iBdHJkFpnxn0iBdokF5yWRlmdUNLnoOMWRwYL3mWsp6zWFkQzSrSRvy5v8chTYjG2mStn1173bYp79ziCMsXfLVDfNhvg4xyCwt/l0=
*/