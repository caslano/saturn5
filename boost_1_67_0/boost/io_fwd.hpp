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
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
*/