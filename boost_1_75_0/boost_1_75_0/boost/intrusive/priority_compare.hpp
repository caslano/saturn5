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
0RObwmtSfgAtOlOrYyPKmhsdkS56Ufljxj3wKreB2+wimlaju9fafJOB8XaVdPo+1+M3Q9bPrENV/SjiMFoZ0/mUDPrDxXii8CUDLcgYptDUk2fexyhbTGkNuc/1Fw4EcpJCblfdh6rLtYt/gDahP80Y0+SdR7Z6S6sCOU3kIj97DMrr6skAlGTikIYVh0hJX421ZfhmlxdmSd5DuYPSiJ70gOIl3CFpDtiuyPz8evzPAkSECbo/jjQZcQ6s1RrzL1P8XcBhe8Jui03I0rb7L1Eo624Fxe0XoipG0Xgqd7fGyMgv7W5cdwjjJLLSVKh0IJGCepOnfMcVCTgtBFJrHg+prS0sLa1ckFvxSltuq9CZXp9ZjI+CrEWRr+WfS1UsayZWhp6/Srvc85Kdn6V9E26zLPON0H1IDSKnRdW7ajnr+k01X9L5ZyPJmsaz5qh6c3TEeOG+ff1rzI08nAnpEn3O/11KvQ1nG2yqUUCYnu5DfCpXvPVAx+9RoZfvMwQCeNiDwegkTqfxU5L8pbTmrKXHXtNT8VqC5udCCcpYTCDuRqH8+dIWJ4zRSd+TQNJ09dZogPEXOveLynIBfomn2oA7hjnP4GSv4+PNS2ZHvvEFyo9uNEpOi/3DoSE7SNqROzhKlueN5OkKO1EeJOi9gEnTawWNzoxE0Dxgy26WrHEnZeyVvXG/o3KzxseIaGVJ1H2w3JFktwdVH63i
*/