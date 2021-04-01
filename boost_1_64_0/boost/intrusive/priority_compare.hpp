/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP
#define BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

template<class U>
void priority_order();

/// @endcond

template <class T = void>
struct priority_compare
{
   //Compatibility with std::binary_function
   typedef T      first_argument_type;
   typedef T      second_argument_type;
   typedef bool   result_type;

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T &val, const T &val2) const
   {
      return priority_order(val, val2);
   }
};

template <>
struct priority_compare<void>
{
   template<class T, class U>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T &t, const U &u) const
   {
      return priority_order(t, u);
   }
};

/// @cond

template<class PrioComp, class T>
struct get_prio_comp
{
   typedef PrioComp type;
};


template<class T>
struct get_prio_comp<void, T>
{
   typedef ::boost::intrusive::priority_compare<T> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_PRIORITY_COMPARE_HPP

/* priority_compare.hpp
ffmjfYRC+C1c9wa6hZkQzzfAQZqOFcBGGrQuYQ7Etcm+hkLuml9ADdPAijNR1ogAmPLCF2npb9a1M1Ibrc1REJ9BwtCFTYOSFk//8t3SOZ1RdvlxPd9htFHNwA2Nx2aFl5ij1vpzG8PPgvA6ZH9Pvojn+q+ZNyqwWj0V5DwwJ5qdiSQ6Hi+LxEZYJ2JQRXxccE/YsmrhZIdN1EMjwjm1cXHkN1NiFo/AnoM+RYTXQPghXej8ITDMfUYydrnThMfXrvX7WUof0H2ZISpemgVMQXN9/8BpcFAYcOnxquKobcFH8ER39IBjkpKAoJuUPfrjQziLI0SdE9chKJ+1Gpw8+lomPHbEu8CYqGF/9FdUtntZwMf+L+XJ6w4XhozhhwNe3dido2DicWRgcYX0piYfyGPeHpV6wuuxVEChMUQWNCXaAC/0MqEyw7tmgcoAWByN6CJuXRATmgwB8mGADydBDypyD9nRPjuX9fcE3esiwieabRjkYRo26/+c/cJfDgztSqXcmAfNsFWWZrwtt02+O0KWhF0SqDw6bepDeudXaskVMKv1E8piF6I3lg==
*/