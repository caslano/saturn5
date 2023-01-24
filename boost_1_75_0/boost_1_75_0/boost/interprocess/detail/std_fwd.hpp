//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP
#define BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template<class T>
struct char_traits;

#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1800) &&defined(BOOST_DINKUMWARE_STDLIB)
#define BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
// Compiler bug workaround. Previous versions (<= VC11)
// used dummy virtual functions
#  pragma vtordisp(push, 2)
#endif

template<class CharT, class Traits>
class basic_ostream;

template<class CharT, class Traits>
class basic_istream;

#ifdef BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
#  pragma vtordisp(pop)
#  undef BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
#endif

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP

/* std_fwd.hpp
D+ZBisygHz26ilcs4e06qy6/Aw3XEaoKMM4twGsEbg1XzLxE9fYmqEeC4xARF5idFBj47vZG+ea6/ApHdXEuPmCjddQ5T3fVq09ncuu2Kq7qcHskrtlQrLSG8Ls7BnJozT8RyB2/n77mX/7Lp60Hx7z8tz7wItrjgdhtzS0m0be9h/E39n64WiL2dfmt0tU3tpq7yhYONXHPCgxnjPfd/bZxkfx1/QXn7dE16uO1HHOm1GoqMMxk9SIZK1p/NXR+O37ZDvTp955nRlRnRzUGXtzkFCDYT5fmt/Ku6X/vz/3tOW0HSnAgYgZ9dpc6cYQXy0wIN5jNG8h4N6ChDOy7VTNEr0SlVWag3frlcDWC+WnGUPJzblehQbp19sGMvzpCgxJcdslaWgnc+tW+W8HMvaNH+L1/kzhYDeR6g7X/JnGaNlgeHhUOJeuSc3IVdAHvy5qQGgotXnWrFB65CN6Yw9IXovaBznHn5+bPOMznGPmIul8NmZ1y1HZh56JZJYFQ17cmwLCWn5/44EY63XHm+Z5wBuA+j+K47OGBbWZDECVF+SHnmvER6nPHqwCmo4WcsPXG37EsBdWvvK9OkDfHS8pA3Bujy4/seV7w66P7iATSOvvL93pZccnXV6NbPc4J6s+Loybsnvq9NPc0+JVdWMTXs10nkyGgUyzumB81ZUefIaBaTN8w0bdT1yvmQiiyt/UuljtEQLLY66i1
*/