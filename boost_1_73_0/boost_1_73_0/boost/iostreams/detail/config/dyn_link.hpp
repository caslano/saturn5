// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//------------------Enable dynamic linking on windows-------------------------// 

#ifdef BOOST_HAS_DECLSPEC 
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL __declspec(dllexport)
#  else
#   define BOOST_IOSTREAMS_DECL __declspec(dllimport)
#  endif  
# endif
//--------------Enable dynamic linking for non-windows---------------------//
#else // BOOST_HAS_DECLSPEC
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_EXPORT
#  else
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_IMPORT
#  endif
# endif
#endif 

#ifndef BOOST_IOSTREAMS_DECL
# define BOOST_IOSTREAMS_DECL
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

/* dyn_link.hpp
z6+4oy8w5YPxNCY2rQLB0CZAtBOqhBQ58W1jcOzIdgqd+PE7ToFqElNfcJTYvl/n3nNvRh+KSpnCN8no4/utZERbVzm8JRb26HDl7B3X4W3jsnyi9QOnW+xbIAraeDyVe7TV44l2B4/yGeMonstyC8xtTCx+iuh4W8YjJMkIfse2Wzm1aALtHu/Rp8PDz5TRwf7BfkonwijWNAlsKnaLlI7kIPneiMfH3PO3lDiQ0PkQaNooT97Ow4NwTDhrVbPxLEl4kuxrpypclKHQMM2VZjq+vJqdX5yl9NCoGr2lle3JN7bXkhqxZHJcs1quQ3TCBbJzeCO2VD4gXh+UNTmgmQK71iNEBBfaWxJLobSoACMCNSF0/ktR1L3TyLyQtvZF/VJ63oT2uYoZMmjFimwXKFjqPacU7VJqrVTzuIMKCLu+0so36SYVABlZWEeetUYouCn265SZJs/MpNGKOmSrQty8NT4iPTS2/ccQFCLIvHcGMKAANtKC4JR6I9kNtkPRLwjPbA7U/qclm1wlWYNMaGc8ofPJDlXCK5/Szfn0x+XvKd2Mr6/HF9MZXZ7S+GKGWD/PL07QbwUkR/zYOfZAdqTaTiuWA+D7rSTJi6pXWtbWzJP2XipHWUf10iW1HLY8L6JOLXqUlmWoLPY6
*/