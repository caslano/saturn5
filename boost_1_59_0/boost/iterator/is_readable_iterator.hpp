// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_READABLE_ITERATOR_DWA2003112_HPP
# define IS_READABLE_ITERATOR_DWA2003112_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

#include <boost/iterator/detail/any_conversion_eater.hpp>

#include <iterator>

// should be the last #include
#include <boost/type_traits/integral_constant.hpp>
#include <boost/iterator/detail/config_def.hpp>

#ifndef BOOST_NO_IS_CONVERTIBLE

namespace boost {

namespace iterators {

namespace detail
{
  // Guts of is_readable_iterator.  Value is the iterator's value_type
  // and the result is computed in the nested rebind template.
  template <class Value>
  struct is_readable_iterator_impl
  {
      static char tester(typename add_lvalue_reference<Value>::type, int);
      static char (& tester(any_conversion_eater, ...) )[2];

      template <class It>
      struct rebind
      {
          static It& x;

          BOOST_STATIC_CONSTANT(
              bool
            , value = (
                sizeof(
                    is_readable_iterator_impl<Value>::tester(*x, 1)
                ) == 1
            )
          );
      };
  };

#undef BOOST_READABLE_PRESERVER

  //
  // void specializations to handle std input and output iterators
  //
  template <>
  struct is_readable_iterator_impl<void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
  template <>
  struct is_readable_iterator_impl<const void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_readable_iterator_impl<volatile void>
  {
      template <class It>
      struct rebind : boost::mpl::false_
      {};
  };

  template <>
  struct is_readable_iterator_impl<const volatile void>
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
  struct is_readable_iterator_impl2
    : is_readable_iterator_impl<
          BOOST_DEDUCED_TYPENAME std::iterator_traits<It>::value_type const
      >::template rebind<It>
  {};
} // namespace detail

template< typename T > struct is_readable_iterator
: public ::boost::integral_constant<bool,::boost::iterators::detail::is_readable_iterator_impl2<T>::value>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_readable_iterator,(T))
};

} // namespace iterators

using iterators::is_readable_iterator;

} // namespace boost

#endif

#include <boost/iterator/detail/config_undef.hpp>

#endif // IS_READABLE_ITERATOR_DWA2003112_HPP

/* is_readable_iterator.hpp
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
*/