/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UNCAST_HPP
#define BOOST_INTRUSIVE_DETAIL_UNCAST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ConstNodePtr>
struct uncast_types
{
   typedef typename pointer_traits<ConstNodePtr>::element_type element_type;
   typedef typename remove_const<element_type>::type           non_const_type;
   typedef typename pointer_traits<ConstNodePtr>::
      template rebind_pointer<non_const_type>::type            non_const_pointer;
   typedef pointer_traits<non_const_pointer>                   non_const_traits;
};

template<class ConstNodePtr>
static typename uncast_types<ConstNodePtr>::non_const_pointer
   uncast(const ConstNodePtr & ptr)
{
   return uncast_types<ConstNodePtr>::non_const_traits::const_cast_from(ptr);
}

} //namespace detail {
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

/* uncast.hpp
iBLfb9dmT8ER+LO0UNzjz0KPo2awQmPMSBBgWlOT/ha2qITR6ciZjoH0uEK8YZUb1MG2lMpc9er/S8R9k6nIVJT/Q+C9yZmnVPHp8xkRIzXbJP0c1ZPxkjCrYmP8HFDK7xtb12WwenXMmnubKfJEVQxg/FaQcdxztc2k8XC69hhPZPrSdnpQhbMx3AY9DBWiaxbTCKBi9QkI3S3JCmp4Sl3o2DedLLxrZR9ESDjq5M20P1jFccsIiqWkdRk2bCOcV38M2FL08Qbj+IJYZ4cKwqE2h493mqAO/w7Dj+9DTwQP+AvZf/gUihqtEkzyWtRmXdH9mKZF9ggLT3eY16lD1pyp884O5GpQKwMMI0V87cUZ9426wSfwrj1vX8fLP5Vkqp4dCE7vcCOLEvl9njwVUbSglMgQeYsFNylPGTWdLIfkGxUZe673mSnI/5dnzhFrh9FFK/V80gmCC5tijVOzjDiqoMQ0p2ykjOVSJxB9Dqp6Iy6zpqPL5De/pocHyXIuskfFL0tvurkvsMW4ZI0NshmMT5eAXXSnqraDHKhn0Bk5/6rHg5E0dxt5Rg==
*/