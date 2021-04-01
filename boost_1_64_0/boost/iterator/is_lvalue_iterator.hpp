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
yiJakgNJQyqtICIAcO5wkPo49ljWwR3VMsogIJfo+hIRWN3EP+3Q2Eylc/3ktwd6uIOeayFlNR1s2FWh2QzS5cf67rlcx1KDIDSi3ETFHSEb106Ba1djVAx16aWpP+RY21qC72OM3e+4GXvH5FmiLSWKgng4eW3cR3jEpq/ERPpauMivNFcVwlmh2lHAQySRtlBsu/vWuscCeLj6ZZ2GB/W1XELXbpH6TmzC89YfQ5uiiIe/xUzn/PMJA4UGe6LYQUA0px1DHHWvmV0IoFs+hLbbEx5WuEDtOvv22g9NWIG6tXHKI7H5B+3O/0S9YFZ/i6GbbDy6NpnTlq1MUMwqcc6xjGbXnIPaJ2ibgVXIQH5+Pp2W3tjRAipt2ZN9u6Ok1r1XUoxzzjd0JaNnyNKz0BBS+PC1IPmRkfe3zGbm03ocw6nS0g+zK0lghzLFpmoX75Xs0L15HUVMCZOkko7imOx4EpQAVuKv1Yt6Uy126Kx5s7DtbqKNDAedKd3/lP7lLMNW50o0aEMiM+VoiHWSGmrZ4rF7VZvuPK7En7k+Z+OSnOCwd4Q8/U9xrQ==
*/