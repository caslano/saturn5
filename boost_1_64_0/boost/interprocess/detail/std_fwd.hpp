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
AN/wlr153EUDHS1lZLjwEpFfyks54Kt6PFmjAYnYeoIJEaRtgPcfpSg5IKFXqZMMSF4f6VhxPpKp0qYmypTKpQIiIB6fb+MuXnaZkE8lC3zPyaoLgdKzsNBNCUWwoZKmhfTaCyaORib6YvXXvOJE1EZDuilfMbaWPkpEzZQFb+us/ap5Gp6BshiSDQU4QK1Ek7NuB5+Q1wXqqEb29ePCf8p3Qnp+Y/R9mK0tpnkm9keEoDI5fUNw/oiNcDC6h7oWtEHjalvCtICJyHo1j0HQmX0fWZ71Jc+NJuds+406oZBZOdqWNUpXs09wpMJCyvFH/o+NmfWOLMx23Tibtnw4DzDeu8k9hQ+P/zCe4upmFza+O/QQBMkj5N5Ih8hE8iRmrR2VvAljYDD65Uf5+lbSD8b8DaxbvjimO2APaJLIjaGhzu9FBtsmn6qZiVBAIEfV8L0NgqZX3FZESzi6ONuVoualBQV6O8DG6Z5AqAEsSdAtnreT1SaTRN5kqQCnrXvUyKMdqvUL48zluCcUjvodxOpv1FVvkjLyQ6/XciR0YuiIWlXGU3ezE+LKZQ==
*/