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
OWmphfylBmdL+CtfE5W+Kk0wYV2BLlNqITKpkRwPs31E3WE1iawypxUkq0033FJ1Z/0ETrWy0hJR1E9SWg+zsrQMFFDD52aoBbllXi+9IxY5tVU3nrumsgb5yHsFlRmwdhlqIdqtQJM8KocZ2yQ10PBrI8TC6RY5P+gdIahJdl2stkRnrfW4K2j2TlltZFB1muHCu0Ry7cqhMquVJBO7nYSdYjaNtDqvNWQrz2kAa2V4hY18KyykCk1WXhO31nz9q1ekzNFYD3bPpnaQQ1Z5ARcs6qCtNDMn44mBnVkwnzSogWY7+yZZyu6yHpMQJ+HWRISD3h1SHlA7QEyP6LJQPUlOWmpxVtcGT8fURKWvShNMWFdIrV95RCY1kuNhto+oO6wmkVXmtIJktemGW6giT0VoJ054mqIGGnU5PpoFagj0MRBxEm5NRDjo3SHlAbUDxPSILgvVk+SkpZb+LhmMFFPUz09aD/PO7F4VUsPnZqgFuWVeL70jFjm1VTeeu6ayBvnMvodijayNaLcCTfKoHJb/7odDw6+NEAunW+T8oHeEoCbZdbHaEp211uPeKdf1fQ+fDKpOM1x4l0jeo5p9D9UUE7udhJ1iNo20Oq81ZCvPaQArZe6dNOuXCbUQ6cry8Txwg0jey1Jp+LUR
*/