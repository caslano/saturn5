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
C0qgy1WwjOOpGvbazCbTwdbTmdCyTpiCe5ifcYjzebqhwDTwobiWGagq9ODONF6trxvFzQ5i+UyCHcACGb2MFPVnHNt9Dl0bkB+OLyHfG9SbbhY4qrXXQXpKlYRWSsuI3XipJYoqeYv19OfK8rejtNLua+Wuao1Un8fheyiVgEdR7+XVTAVJoK1Q1KtdWSa6DOsJvb85YoP83sp7AqIXd6tssb2Tcq1IRFEgKMmbV6mLroC4ag0+fjyHRIJzqkBvHtd9smPK1caJRP6ea6+kirNw4hOyIliPJmQIE0JYSBMow0xbx7r3zBl6nrlQpppLtSNUrTvIF/ow1wyy76IlILmRQQyruC5oHWSNVembLUTkuSw4JX1TKjL6ZJYWNgk+WqxWi17YawkU8VQLl5iNw12agndS59+t2UmiMT1CAsaSxdgJk0JBidToA1lLUlve60YDri4Lufy1o9H4M8hBJ+KlNx0n62FDiZ66Hv4aUkqg8xix1dEjXGPhQVhzbOOVwt0/o2PsDJjYmguH1a9Dd7vdKIGJ87AdpE16EKF0RWjJVWePuFWKGLafsb7PM8xQJ29U6CXlEAj8kKi8lxCwT9LIhntHB2t5aOJu5nF19+ZEBvw0E4d5D8mwjcCp/Hioy+RrMTmYCjEXTALzcgbd6IYpYufDgf8UYPDbfPs6+6rm1kTXqxtMPQJzqA+xvDrjGsgiT96FppEwI/tw
*/