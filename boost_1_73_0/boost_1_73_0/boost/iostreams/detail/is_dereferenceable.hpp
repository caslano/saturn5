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
fmBL2yzQEpUNKAliUdONHHsSz9bxeGfGQKSqv33v9St24oQQnKrEmbmPM+fM3LHHn5ntChDj8e6OZFN4W90nCQjPfobR/yF+8DvzupHiX2brco/h8BfE/9BzgN+bJGvC3O3X8AA2c/sF+5HbMMn2ga6Hw00SDggn/WmS92BIl9iSuKYRzkQwk3ziatg/O4Djw6N3UMev48Ma9DR7YHApvCmrwQdFv4Yu/frsCj21uNewxfRjYyFg3+UKlBjrR0sywGuP28xXzAFLgcOULfkIf3AftMtgzD0GZ9c39+3O1xo8utx200AzEYJyReg54FoIRDKb8Yc4TmBJjdMGQ2AChyuNQUPNhd/A/Aw0k1OVxiEYlqcEWA+I2RphQkuDq3WgTppNO5ReQ7GmI2zVtFMyGq6eeosju0dAU2sGItCgBYQKaSGPGkyFw8f0zeQEG4Nw5HHl1ubIMKXvNIUExTwvjYe+nKl4GAx6CWU1MoUAR8A1fSnhK0r36IppwRC5TSONQ+ljQuQGDR2B9Ncg9B0mI4eIjTRNwnVE/LPSzfE7IHwEBkarB+2eASNLcVWDu3b/8vq2D3etbrfV6d/D9Rdode7TgN/anfMaMI6JJbCnQDKFQCTwaeBx5izkr3Lx7+6cjNiE+7s7ABT8zGX2
*/