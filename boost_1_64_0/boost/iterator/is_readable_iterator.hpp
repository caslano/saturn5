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
6WE0tMASIwG2tzpemRsXg9lA7RYLXFDJ7T9PBCzUvhiGMcizkP1Xlqv1DUXIjOK/TxXXgj5h6psNOh6S/bRzVobx75IPQNAuNf+a7V0kVltF8s2f9jkEH08uT0sM6b930wR8eD0GyI+Hj8i9dLFwymgizqrA7Oo95qsPd8+0/MgAtByoOeGy6fUykFaGkGLOKWzsASJaqJ/dzM69cvlTtdj0Ol39hqC+Zt+wVXozVnIqO5yw4w9wq4rQzbtBqbum8SVcBOvKFDaY4JmkvuGd+lVc9qKJl+Fev/+iWBsoRL6B9BGdjEg24Vb1mn6+/sX09fB9JzkiBc0wmx5E9dz7+2DPrne3Iz0pxb4yVEm9kCtaOGlr8+2dfZiI8cWVywE+puxZytTBsjVng9rP+/a6cKEfIPneVXhqr9rJ4stuv+b/sM+vU8MT7ZTL6wHRFcIftSM1Wd9SBT2vvL/wYQ59TtyMDhTwbxfMnpQpqI9B//wTVU+3JlZIZjgz5eW6FqvITr14QGdlJUj9ITyiV4785wylb1+KAexCXBoJMvI5OXaLo50GWpKUzHvTEQ==
*/