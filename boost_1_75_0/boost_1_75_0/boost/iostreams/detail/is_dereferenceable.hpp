// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// (C) Copyright David Abrahams 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED

# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace iostreams { namespace detail { 

// is_dereferenceable<T> metafunction
//
// Requires: Given x of type T&, if the expression *x is well-formed
// it must have complete type; otherwise, it must neither be ambiguous
// nor violate access.

// This namespace ensures that ADL doesn't mess things up.
namespace is_dereferenceable_
{
  // a type returned from operator* when no increment is found in the
  // type's own namespace
  struct tag {};
  
  // any soaks up implicit conversions and makes the following
  // operator* less-preferred than any other such operator that
  // might be found via ADL.
  struct any { template <class T> any(T const&); };

  // This is a last-resort operator* for when none other is found
  tag operator*(any const&);

# if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202))
#  define BOOST_comma(a,b) (a)
# else 
  // In case an operator++ is found that returns void, we'll use ++x,0
  tag operator,(tag,int);  
#  define BOOST_comma(a,b) (a,b)
# endif 
  
  // two check overloads help us identify which operator++ was picked
  char (& check_increment(tag) )[2];
  
  template <class T>
  char check_increment(T const&);
  
  template <class T>
  struct impl
  {
      static typename boost::remove_cv<T>::type& x;

      BOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_dereferenceable_::check_increment(BOOST_comma(*x,0))) == 1
      );
  };
}

# undef BOOST_comma

template<typename T> 
struct is_dereferenceable 
    : public ::boost::integral_constant<bool, is_dereferenceable_::impl<T>::value >
{ 
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_dereferenceable,(T))
};

} } 


} // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED

/* is_dereferenceable.hpp
76vPRXqNLQ4lh80oM6PY4Ood1Tu3xrxB80IXPamH63bPkM1UVaA7bgE6DDf0Gr2cEnIjRg6c003BgaT/KcCgnMRkZazC6z+jzsHi3a2Wfji3GecyzXGxFpHxVfwDMiPyvS6dVYO3RdRkpYSztNJlsX0Td7Rx4E3zjB87Y34VosO+VU0rPqoer6tyqBv5FzINlnSehu9Vp97RuH44l4Mh3RgZCtePRxIUvtmatbcyyoSdbXUGd47e/DK5lYS63Qp1ZPsZiQRKpCvKh9vSgtYWJyJQAc3KAC8CAdi0oCorlIkhlIoxXEtz/I28pH6N56tXI8O/sCIloAtR+ezWqED/R4/orKiG1v7rHdqe+YBmucECHbjedbMupbkT9gRrRtcSysXAinvudimyz2+2R9M1xxqL3JE2uRXW3fZu+U7vqqfe+TBwWpvp9R2vXCG+BDPFI1kcYMlC2ghMVpixiqhD63DA4z4c2Ec79dj7hdsAceO+N4RGVKgk81oEBxaADzgIGrfKiomb9M+alF8Jc3G3ECn7qZaj/afKh/OphQzbIXf0/thpM4fULe/HR/dcmW5q8bWDzrjf3JgGcFv64Wq2bIo1F0V3AG5KIvFPwPw965sf3ZWUdbMefMJi/Py0gluzGJgT9I1X0XHszAN70+MAphvyMzAswphh1jEy4Ss+QBysKBTRGxBDZFBOtulP+FW0YNvghi+BsMByZdcy
*/