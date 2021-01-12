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
9ayf9+7c7twyV7TLgo9qRZMKBNhTXfWfSalhApSbrWbn+uZecU5WR8AtP3OyntBd3Bwon43hy/U6oEe0e5ri5HrsfT6ty/c30qKgD7/QITQwDJ2UG8on5YKVgRL05Ouud625FZeh6t3rkeiPvKikT6SRIalNdWp0CmhoU2D1LLIDfvt2n0sjMFY7ObeDc23pXHCWuAuNZ7ZHOb6RmGpLNNniFoLHGb9TiY6zhichgltxvKpX
*/