//  (C) Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TUPLE_HPP_INCLUDED
#  define BOOST_MATH_TUPLE_HPP_INCLUDED
#  include <boost/config.hpp>
#  include <boost/detail/workaround.hpp>
#  include <boost/math/tools/cxx03_warn.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500)

#include <tuple>

namespace boost{ namespace math{

using ::std::tuple;

// [6.1.3.2] Tuple creation functions
using ::std::ignore;
using ::std::make_tuple;
using ::std::tie;
using ::std::get;

// [6.1.3.3] Tuple helper classes
using ::std::tuple_size;
using ::std::tuple_element;

}}

#elif (defined(__BORLANDC__) && (__BORLANDC__ <= 0x600)) || defined(__IBMCPP__)

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost{ namespace math{

using ::boost::tuple;

// [6.1.3.2] Tuple creation functions
using ::boost::tuples::ignore;
using ::boost::make_tuple;
using ::boost::tie;

// [6.1.3.3] Tuple helper classes
template <class T> 
struct tuple_size 
   : public ::boost::integral_constant
   < ::std::size_t, ::boost::tuples::length<T>::value>
{};

template < int I, class T>
struct tuple_element
{
   typedef typename boost::tuples::element<I,T>::type type;
};

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
// [6.1.3.4] Element access
using ::boost::get;
#endif

} } // namespaces

#else

#include <boost/fusion/include/tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace boost{ namespace math{

using ::boost::fusion::tuple;

// [6.1.3.2] Tuple creation functions
using ::boost::fusion::ignore;
using ::boost::fusion::make_tuple;
using ::boost::fusion::tie;
using ::boost::fusion::get;

// [6.1.3.3] Tuple helper classes
using ::boost::fusion::tuple_size;
using ::boost::fusion::tuple_element;

}}

#endif

#endif



/* tuple.hpp
6SG0tFc7rNu0sntTWxmhxqZ8BWPfBBvVGYUPgvehQCi73UpT9YflnJ9NZ8vydp6fxVPms0XJs9HlGNLrCISSOfqLruExzNWgtmuudq6OrkO7C4OP6ZXgMYdI9ICOkD5E+bS9EuUqUNFHzW2kJ2ZoYOA3NgyY6KRGnRDonHXKVhTs4oLi/TMXjbPBKlsXLDLvcRxUkrCp9SGH/6glbBEved5deH9F7NKE3VMX0smaMiUpES5+9nCzWN7O/iZsohQ2ZD7n571gTqcKfkyTn35xr1BLAwQKAAAACAAtZ0pSUZOycAkCAADNBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwNDNVVAUAAbZIJGDlVE1vm0AQva/Efxi58iUqXrBdp14RpMiN4lRxbNk09w0MBgXvWuySxP++s+CPSr1EvfayzLCP+Xjzhsiisak0GLOoVLmmxyse3nWdmZjNk2TVHnB/l7A1mmaHLOIXQMS7b9gX2GD9hrVvyowgNe6rA11n0souDA8HIQyDCaxkbUtZwUwri8p67Ie0KGCh1VcIR/Ck3wgWXJMtxqEIpnC/SDz2KI31Fzor8xIzAUmDLfpnoxw6gHAowkCQ0aJv0xT31l9LtUUj4OVATXrsmNF/RLW1hYBJ
*/