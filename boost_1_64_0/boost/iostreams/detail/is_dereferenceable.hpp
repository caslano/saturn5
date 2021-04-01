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
MH9nj+I/0xm6g5N35aqBzAoOCQvcxCA6FZXwGYt+Yz1eNwKzvj9Viyl+JVPYoP+eVzAz4CpGSG6E3oPJpNZtLowelu5JUopT+EfoonNdLXBc39dk6BW141cfFeC3bNuFxMmuJr0MWSGlLlgX8/j2GIesoWvagjttzQ1BBTsEg1l334N3wgvvDh80GLjMdE2Y7rKCALcGdbItHO9PDYz53OJt8l5aP6idXT2A6oSBSZUW9GUJDO51NqzBozuPzDhZ0ev7t+r8ffkiXvU02hks65bAsDEQkTaXwJkmK7XWPEQe1O8LOsesjKU/jcgLLu7KjZGN43KKt+Eip4cpoG6B93xmAJxHaYQS2VFgFU0uhFYskVCN2X2a74I/NYcpTBofegKMHm9603NnUToW7rY0cnLVLw3d1N3pJVTuPN+Pz3I5TDcxb6xWquU6u3rG0AWMR0USnjmyr6F+jRO03zqcgja1+UO2ETox8ErcnitPiaFRyrfrye4w/lfSowNMl4c88KMp5rEAQ3DZ4pLjfKABoO/ZalZWIInRcReh4Ga2Ag1N4ccUrMNmoQlm3Q==
*/