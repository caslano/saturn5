// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef IS_INCREMENTABLE_DWA200415_HPP
# define IS_INCREMENTABLE_DWA200415_HPP

# include <boost/type_traits/integral_constant.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace detail {

// is_incrementable<T> metafunction
//
// Requires: Given x of type T&, if the expression ++x is well-formed
// it must have complete type; otherwise, it must neither be ambiguous
// nor violate access.

// This namespace ensures that ADL doesn't mess things up.
namespace is_incrementable_
{
  // a type returned from operator++ when no increment is found in the
  // type's own namespace
  struct tag {};

  // any soaks up implicit conversions and makes the following
  // operator++ less-preferred than any other such operator that
  // might be found via ADL.
  struct any { template <class T> any(T const&); };

  // This is a last-resort operator++ for when none other is found
# if BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ == 0 && __GNUC_PATCHLEVEL__ == 2

}

namespace is_incrementable_2
{
  is_incrementable_::tag operator++(is_incrementable_::any const&);
  is_incrementable_::tag operator++(is_incrementable_::any const&,int);
}
using namespace is_incrementable_2;

namespace is_incrementable_
{

# else

  tag operator++(any const&);
  tag operator++(any const&,int);

# endif

# if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) 
#  define BOOST_comma(a,b) (a)
# else
  // In case an operator++ is found that returns void, we'll use ++x,0
  tag operator,(tag,int);
#  define BOOST_comma(a,b) (a,b)
# endif

# if defined(BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4913) // Warning about operator,
# endif

  // two check overloads help us identify which operator++ was picked
  char (& check_(tag) )[2];

  template <class T>
  char check_(T const&);


  template <class T>
  struct impl
  {
      static typename boost::remove_cv<T>::type& x;

      BOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_incrementable_::check_(BOOST_comma(++x,0))) == 1
      );
  };

  template <class T>
  struct postfix_impl
  {
      static typename boost::remove_cv<T>::type& x;

      BOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_incrementable_::check_(BOOST_comma(x++,0))) == 1
      );
  };

# if defined(BOOST_MSVC)
#  pragma warning(pop)
# endif

}

# undef BOOST_comma

template<typename T>
struct is_incrementable :
    public boost::integral_constant<bool, boost::detail::is_incrementable_::impl<T>::value>
{
};

template<typename T>
struct is_postfix_incrementable :
    public boost::integral_constant<bool, boost::detail::is_incrementable_::postfix_impl<T>::value>
{
};

} // namespace detail

} // namespace boost

# include <boost/type_traits/detail/bool_trait_undef.hpp>

#endif // IS_INCREMENTABLE_DWA200415_HPP

/* is_incrementable.hpp
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
*/