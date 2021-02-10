//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_BOUNDS_DETAIL_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_BOUNDS_DETAIL_FLC_12NOV2002_HPP

#include "boost/limits.hpp"
#include "boost/config.hpp"
#include "boost/mpl/if.hpp"

namespace boost { namespace numeric { namespace boundsdetail
{
  template<class N>
  class Integral
  {
      typedef std::numeric_limits<N> limits ;

    public :
    
      static N lowest  () { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N smallest() { return static_cast<N>(1); }
  } ;

  template<class N>
  class Float
  {
      typedef std::numeric_limits<N> limits ;

    public :
    
      static N lowest  () { return static_cast<N>(-limits::max BOOST_PREVENT_MACRO_SUBSTITUTION ()) ; }
      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N smallest() { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }
  } ;

  template<class N>
  struct get_impl
  {
    typedef mpl::bool_< ::std::numeric_limits<N>::is_integer > is_int ;

    typedef Integral<N> impl_int   ;
    typedef Float   <N> impl_float ;

    typedef typename mpl::if_<is_int,impl_int,impl_float>::type type ;
  } ;

} } } // namespace boost::numeric::boundsdetail.

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////

/* bounds.hpp
Wsdt2vvw4Vfapv3d/d2ATpgUPKOJ4XLGi3lAH2Mn+S1ld3c7mh8FxA2xbKdyNU2FJq0Ss2QFJ3zPRMSl5jExTTHXUSFmWAhJJuWUiIzT8ejiuj88D2iZiii1Tu5VSTpVZRZTym45FTzi4tb7yFlhSCUwh/NYaAOHpRFK7iA2J8OLhbY+bHiWaUXslomMzRCIGUqNyfVBpxOVRYbsO7GKdCeqy99JzWJVyTWSWLB7Urkho6jUPCCrGdBCxSKxbzQEwrycZUKnwTobhJJxRxWkeZZZX7ATXPu0OU2q9gRWjXJkLIx9aSW1DbVM1eKRIvpovSRlIREIfYBSrNDmgEoZ88Ipu8rrEFVPXYOfhWadb0xKIhlq9ibUnzRpxrTQAV31p59Gl1O66o3HveH0mkZn1BteW2d/9IcngF4gWEH8Li+4RvCCxCLPBI+rmD/u6TR+EjLKyphT03ANqJqNJyKwILPitRSFygyJPZYu+CLms3LuXKADJY6zKZjUCS9CbZgpNf3TIDq+HA9oizN938VKSLCHZehVvYpUKdH0LnW2/HdaFgLYRyzLZiz6DKVb9RmwI3lvkWfwxrtkLWS5wIFyeIkFlO4QXchEWWCsB2CC8wDW+qDWydeuzZcZEW14CyMljZAlb90qATXwtMiD
*/