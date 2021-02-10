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
MEhQ0noR+rWBYEJgMl/GAYgBE8AYJwQDN8gycGjMxjKluYTcmsy0O6akxOqQMAAk5KBjkL5xQGZW4iYNctufXo9upuS2M5l09OknMrokHf0T8Hrf13sw3y5Iigl9iGKagOSYuH7kudRhAr/n2pQOv98PYjskQ+ueMrebA+zZ0vUcN7gjzCPoAyVrUI0MoemWHF91u0pbbaF+ngVGxsJg8GHY7HpWcCcjN5xFcBLwP8vzHskoooFhDMjxqXqitiy5Ae4/S5JFC1t+hepfUMdyS/0t64xTPyLHLfWV3EB+szhMPTejP8XxSepg7RVQS4dMgZvEuqPnsJ59QLlutxQfNCLKvNBM9dst0r28ulDm1EqXMT39Ly+1/iiK7T/+q6rqH8hRe7Bg+oDnfo6IX0kSD34jV1m7gesEOa5rN0jP2dq1waPY4ktgY6DByo3DwKdBSlZWzLzcDoM0Dj3mr2wKGmSuUvUc2SDN50H/nTnuTK8v7PMmE8ksVu2+OGXT+f2cA5xbc2AxIqbIAieYUS9cI9ooBM2wwOBaCcWlBnrG5DPOZgIlmyaq5M5hRc5L8FJRIhdEVZvwv6ILDWAjeZbQJAWvs2JnW7Ix7eWSeamUDI6kMD96vuR3mXNuin03GU0H/UxwpVyIznxaYS79
*/