/*
Copyright 2002 Daryle Walker

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_FWD_HPP
#define BOOST_IO_FWD_HPP

#include <iosfwd>

namespace boost {
namespace io {

class ios_flags_saver;
class ios_precision_saver;
class ios_width_saver;
class ios_base_all_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_iostate_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_exception_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_tie_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_rdbuf_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_fill_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_locale_saver;

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_ios_all_saver;

typedef basic_ios_iostate_saver<char>      ios_iostate_saver;
typedef basic_ios_iostate_saver<wchar_t>   wios_iostate_saver;
typedef basic_ios_exception_saver<char>    ios_exception_saver;
typedef basic_ios_exception_saver<wchar_t> wios_exception_saver;
typedef basic_ios_tie_saver<char>          ios_tie_saver;
typedef basic_ios_tie_saver<wchar_t>       wios_tie_saver;
typedef basic_ios_rdbuf_saver<char>        ios_rdbuf_saver;
typedef basic_ios_rdbuf_saver<wchar_t>     wios_rdbuf_saver;
typedef basic_ios_fill_saver<char>         ios_fill_saver;
typedef basic_ios_fill_saver<wchar_t>      wios_fill_saver;
typedef basic_ios_locale_saver<char>       ios_locale_saver;
typedef basic_ios_locale_saver<wchar_t>    wios_locale_saver;
typedef basic_ios_all_saver<char>          ios_all_saver;
typedef basic_ios_all_saver<wchar_t>       wios_all_saver;

class ios_iword_saver;
class ios_pword_saver;
class ios_all_word_saver;

} /* io */
} /* boost */

#endif

/* io_fwd.hpp
qpCebuFvKErODDfrB9Zl/DmJkulThu8tuLll3DIulrzMUOx1eabhe54sM1UL7JyT1RXPbvkcL+g6FaaOCjciMnPr78K371nRApjdIhgnyM7OA0gG3ydxMuizH1GSwn/EIE6TJH+IfD6aDPs+tS26fedI4dWvPe3fzykb/XjwN37rSVgs6e/f8b0/UEsDBAoAAAAIAC1nSlIJ1Yh9MAMAAKUHAAAgAAkAY3VybC1tYXN0ZXIvQ01ha2UvRmluZFpzdGQuY21ha2VVVAUAAbZIJGCtVFFz2kYQfr9fsRP6IDoKpHlqMmknFHCtaSq7EiQhcXo+dAu6Wug0dyfbtPZ/754kAs6Q8YuXQSdO337f3rcrej8+XbAePBq8+XIKWn3CudH/YOaOgzm/g/ZDSRe0PiIxhH3GHe/Doxl3EDQZvNN44+85f0TmwhfmL0OfeMH9Le2wHuWNdbU1ap07CMZ9+OnVq5/hObx88fJFCBNRKiwgdVgu0axDeCObnbe5uL0dWPw1BHQgikFDNMuVBatX7kYYBLovVIalRQnCgkSbGbWkH6oElyOsVIEwPjtfRPHvIdzkKsuJY6trsLmuCwm5uEYwmKG6bikqYRzoFWUTt1TWEV/tlC4HJI3g0GwsUXhxUVgN4lqoQixJRjjI
*/