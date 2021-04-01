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
NV/kNDfa9vOtzFQ8agb+td61kbKSzZNT1eQQJG7diLwvAO7M9YSbkDCg24yKp6xuqbRShU+LMtbq8Kio5qqvzbi6Okl79Bc8B7L77tMXQ3Y4jJZ3amcscRkbvmq60tg3KY7Eqb8prz55Ln8LhuDMZ/tQuWmpjOSYcf5s1IZq/bf8PSeL7Z+SWSt/Mo01vjfGhUbIkQ021MYpaa8wifEXUAUvGzOc3TI2fDVpJpXzCHGhEnBu8UZdtrZ2U4xWoi8uc/+/AkLRrEDriwh3aesECsIq3O6lcTyr+L3uomjYeo3dqfyhGnoVDgozUcwFz6R4TOgro9TiYSHmSe6rwMp6xT1BzttHOlmfC9dgGi/d5oK4i1ef5bEIL6ypmZfoLwilv2Al8doi6J1NAIMV20jf0opsIEDlGLsPMYqtI/tJelrP55U9guiaYScx5KE7QLMvV8FlPbD7DExNz4SZCiBFAO5PeVDN6GpaiSPx3DrLIF3t4jqR8k81PO4T6tCKGreIoXRa6kT05ZFhVcHNHjAvQLh5MdJ9NvINDEszSg1v6ZiI7QNfaqzAhCWZnA==
*/