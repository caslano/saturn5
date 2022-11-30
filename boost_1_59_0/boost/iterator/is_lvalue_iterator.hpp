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
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
*/