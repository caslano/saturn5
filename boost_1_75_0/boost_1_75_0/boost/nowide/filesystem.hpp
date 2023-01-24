//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#if(defined(__GNUC__) && __GNUC__ < 5)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>
namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into  boost::filesystem::path such all char strings are interpreted as utf-8 strings
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif

/* filesystem.hpp
IJwrQ2JwfrSXeBe45SHFyhO9xEX/PthyaCfOus/C+aW0zthD32e82DiZVbmxarmhqsxwKLjMy+6z6CAMC/3L501vgs64CQy57HgPHMaQ6RS0SMS0NEZNJzdRihoJiCxqo5kiIZrDIyECGT7nDvT5vHs4W1L8Q/zeOlzEhg3HdDwOa+3NOqbDfiOauyfLTwZjwzEKwCmEt1S0AgNsJ8Fvmur2Ty8DBF1Gfg4FjNhmhSG2WQbEtoAx2nz+4YWynv6Z54ZyvQGuSc6Cr2Sa8ftFiNoWkXUEoBoPpzzBeso3Vlz1oYTd5jJ2+3dbJt0QwTnNTKbBjqDQP7GGcPXkcVOoowA45Dsxxpp0r7b5XzCH9qMARZHi77d+EQyKWSEEoG2c3qFXQgigzIgA8MYlb8lGFMDz2JFGDFCbbEDlaO2YBTv4HvbW2gSoNVP4OptIhzq0WClIIu4wBJo8vniE71kCvhdMYBRc8Gloho0w1Rz0jc2Ru0CXcsXZgF2UcDEy0fcoHacvNdRj7Hyi3nmEGAofiEZxbnmr3vXiYWRqnEUHrhxKCmfMBiB2EMD15VUE1wiXYerQ54cxHH8s4PnJYQjPHJfBAM8LGJ5tmTo8z6eT+2A25VbwyHUNWKWHxhtjzAOrhJkViqzZaSeC3TBmp81FMYGD7aDEFRhoyS79KcuefVSDaxwMvFds8r1Nk4xgfbEIjlGILSabMC4bnJdb
*/