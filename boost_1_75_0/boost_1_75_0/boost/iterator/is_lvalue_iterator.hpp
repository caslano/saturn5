// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_LVALUE_ITERATOR_DWA2003112_HPP
# define IS_LVALUE_ITERATOR_DWA2003112_HPP

#include <boost/detail/workaround.hpp>

#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/iterator/detail/any_conversion_eater.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <iterator>

// should be the last #includes
#include <boost/type_traits/integral_constant.hpp>
#include <boost/iterator/detail/config_def.hpp>

#ifndef BOOST_NO_IS_CONVERTIBLE

namespace boost {

namespace iterators {

namespace detail
{
#ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  // Calling lvalue_preserver( <expression>, 0 ) returns a reference
  // to the expression's result if <expression> is an lvalue, or
  // not_an_lvalue() otherwise.
  struct not_an_lvalue {};

  template <class T>
  T& lvalue_preserver(T&, int);

  template <class U>
  not_an_lvalue lvalue_preserver(U const&, ...);

# define BOOST_LVALUE_PRESERVER(expr) detail::lvalue_preserver(expr,0)

#else

# define BOOST_LVALUE_PRESERVER(expr) expr

#endif

  // Guts of is_lvalue_iterator.  Value is the iterator's value_type
  // and the result is computed in the nested rebind template.
  template <class Value>
  struct is_lvalue_iterator_impl
  {
      // Eat implicit conversions so we don't report true for things
      // convertible to Value const&
      struct conversion_eater
      {
          conversion_eater(typename add_lvalue_reference<Value>::type);
      };

      static char tester(conversion_eater, int);
      static char (& tester(any_conversion_eater, ...) )[2];

      template <class It>
      struct rebind
      {
          static It& x;

          BOOST_STATIC_CONSTANT(
              bool
            , value = (
                sizeof(
                    is_lvalue_iterator_impl<Value>::tester(
                        BOOST_LVALUE_PRESERVER(*x), 0
                    )
                ) == 1
            )
          );
      };
  };

#undef BOOST_LVALUE_PRESERVER

  //
  // void specializations to handle std input and output iterators
  //
  template <>
  struct is_lvalue_iterator_impl<void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
  template <>
  struct is_lvalue_iterator_impl<const void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_lvalue_iterator_impl<volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_lvalue_iterator_impl<const volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };
#endif

  //
  // This level of dispatching is required for Borland.  We might save
  // an instantiation by removing it for others.
  //
  template <class It>
  struct is_readable_lvalue_iterator_impl
    : is_lvalue_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type const
      >::template rebind<It>
  {};

  template <class It>
  struct is_non_const_lvalue_iterator_impl
    : is_lvalue_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type
      >::template rebind<It>
  {};
} // namespace detail

template< typename T > struct is_lvalue_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_readable_lvalue_iterator_impl<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_lvalue_iterator,(T))
};

template< typename T > struct is_non_const_lvalue_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_non_const_lvalue_iterator_impl<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_non_const_lvalue_iterator,(T))
};

} // namespace iterators

using iterators::is_lvalue_iterator;
using iterators::is_non_const_lvalue_iterator;

} // namespace boost

#endif

#include <boost/iterator/detail/config_undef.hpp>

#endif // IS_LVALUE_ITERATOR_DWA2003112_HPP

/* is_lvalue_iterator.hpp
OPyMGbunyBVbMiDysBFrhv2wZbuKoZF6BwQXRk2qS7HZ1lvUelqJLL23obFzDc9Od6y7ry7X2y/xGedEZPr70TbtUxOznOQI0OlDk/d3CX+TkUz85q9PUIr6iLRcdebcSzha8d24yeEyKOx6CwSCARvJ9gv+InARRQhvqvo8Q4U/vv8Lc2Nkk/JA3qJ9bU8Ecn19ZJIyPCiz85SPjGM1hn8zySBO5q3cK135nZU9MIp0Funqo+NkCbtBPwbtqqzW0GF7PV7Y9PVeLv3dkJ1hQ7cbIMaxW61MIBo5FaPmIksbgub+EiKFrj1ZEbWLic2xN0uOJ2pjriusSLXZHKxgCcvhUdVXNrVmkFBgv32OxzXu9fzpqjv0GbyvkxQmGr8NFH1uH0Pu2K1KWnm6xTYCU3fx2juv2nwel7tjGLzzGQ00J9rTju+HL7oGt748oso7cD3B9JHoRivESZFhbJM39KgjtfubYzfQU3lqZgJuilFcbiS+4ExSlFUmIFl/96zxgj52060+9oDsWMbrpzv/fju7uq+zLz27utZ3YSJ7ClkRLHVgwIGKo46xpBh1Iuf5NM4AVgMO/BjfJAWhJ9rG4FWiX3hxv2iDOkwPnSclF5rv46Pqw9sjxroKrmYmOdr154Yv/nXOmRjXXzjmDAtLzbz65vpQB1wwYjaRidyONhJ1lrzj8UyBOg1ZcGt9M6H4gxByjlhzHev78fS7
*/