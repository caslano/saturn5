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