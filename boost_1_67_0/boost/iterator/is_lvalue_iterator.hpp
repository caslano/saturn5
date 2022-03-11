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