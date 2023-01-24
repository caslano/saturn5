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
eZKWjoaIWNLq1UnlT0XhvliUbf78KHpZYfVqfBgniu3I+xFPnjmL4TZrNr7kWAaoIc5PlsyZO0tDbDYUqP19gigU2eaXzyyfM3dxlH3eTO2ZfOyDDGj57Hnz7U+VRLEFDOIysScW4N84gBrmzYEeYXVqmObMe3refMc8Pz7+elijSArixv5QKZms/sXKKCrarb6s/YTWPzOohycv6BWEPqRnGVEzy5+y4/voiN+j0D3PzJy3OApFGdoTC6LmzItSGVi/6TBOM8sQk/I5IA1GTb5rapR60BLl/4t3DG/a9/h3L9lYYZ9EzZ1dbIuivUGR1nCistJqbP/MWWPmz4POpaPSFw9sO4xHcjm+JhlFD/Emzcc7QgFahD60z7UF196rX+mNj6ejZi6cP2cWHQ/EFRfIYFrJQN+TT0MPBkY4RaNJJPE5z5SxV+ZpEasnad1ME4FGbND/c6llWxTKVdDAZ+347icAt8P8udMxwPIZfCTony/HbIk+QCzoanEK/EM3ET5M0+J18I2DsAnjoP60A/2XGQVlPR6UTw/fXAgvCsqLMLp+6sN8b1+h3ImQ55PLyt0K4aagcideoVzM57tCuY9DHvPBQLkG+CIhPPpg77IRTt9P2Zg3q0H3ODjy6ndMJB946wwIdF9WTyXktx3s3Z9OCD9/kJVfeYUxwDw50im+wkRs1yl2UylR7mnKM1uU4eF/MVsEN+f86wYj
*/