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
+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
*/