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
FNlikZUWPXKf8VEomTLwlSsDju/VgDswjAu2mM/a/jOFIfjo8zQr6/IhsGLiL9VUK1OGjAgyV8kqP076xTsQIAai2vVH2qVYLgVNNqg3uXa6cWtOAsnRz0AgeRYEkk26/88yFJj7c35Kxprq7EjlDOgzZ/o4d56qYhGxtnaiTkcn6nDWA3r/4gnVidFOhmF9qdMnPpWdflJ2uuZeNAzrbLf2n0aPZyt/ZkwrUtLyeVq+kpbL03KVtDyeludVLkxgverNW0uSVyiKTzVvNVnmGTynb8BkoF2zkN7bgYG8UAS1lGtuKVdvKc/cUp5o6dTOj6f7Ud//W2/B1efSAJ/1iRzgjXKAWyxFro5TGNaDj/CE956fF/e/xyy4aiw1uv6wbPQpXf+5RPhTj7DgKjHiKSZnXlslhDQItJSjmWwqMIkdbWjTPAWn35Ps74FHdaJaBZHmPoRu4VHDXeJ45MpBpOT1auWrDBcSfv5SYNPFXJGcbAhX6KbasVRo1QunFnpQ7Y9UWjWj/gjXWjlkhaQ9+ukfcsi2yCH7+R5cCKayIqJekGm3y2KPUqxGvaRAR3d+pu/mVnOthPmzCLFzgfyFaibFRkVrsI0E4JQdoc3+DvGbXx6rKmmjtM97zhaO/j+hDIQU/Q7gPKdNqMbwH9TS8jfitB3S+m4M7LZSsWYw8XTTF6BP2XA44IAsvz8SKQBVW2cLz/V8bAN5+bebmSYwl3EyssEZVK6dwie0PH3oIeNNnma/m/t/bg89Qj10w0zom8W0AvMmGO6bCZh7u5g4qjWYSxteD2mYpn06Q2q7XdqkCcipoOhWrTzzhBBMrWq/LCDgB8plEND6gKwopuMLkWBEqiKm78cx4mN4TeA8HT58dDCVeoUjK2WFDOkS6NZW2SQvnEVMVw5yO0AQZqOJpyo7nImPeb3/4EFjlHep/eZsIH0w9i433tJGBHjk9F4V3Mg5D/XklLhmE08cTL/Xs5EhSOnazCBI7anQh3fwShBrhRMUVk9hyEt3vzFU+HIGkeBFz0WB03Va+8RJ5S3U7m5eKzTBax82BHmVDqqqJyOwLFr1Ngf92wrdFtYzDfiwSL/AQ9aRFdxa43xuwPIDxdgHjbAhfCCoi30Yjc3QUMH9/Lywnertx3qsM2z5rBQKa1OdNmt5nQU2/vpWVvlBEuh3/I2csWrGG+8mIgKjQwFHZYkB/u4H+H4oI6RxNx4nNgYrezkkLrILZ1j+/B1MnMipGBstAx1APiSs2gFWAAK1v4a29oAeQCVkxjYlgW/n5qCxj278D4uqFqT/W6MbYJOnhlQh3bqBfOfp2LX3WsM4+TtQ8qZraWm8hnFVu2hbgq1vBFsz/bA+FZBUMpGgRT8C1oqdCmO1JWLEA2g3nTgnFg5YPOksSEplSe0eE0kx2nUz+HeLEJeZhEeDxaesggqp/1+t6v+vC9P+b1WQ/d/Mutj/rTLb/z15NGz7P6qr9Vqn2F8tuioce77uvGrNgzSan27mteoQr/2H+wnGDoCBhyAoCtc3JpVZ9FiuMqvN/pcAcpN+5tBuji8wDbc9fg+xJIUVMD8pisUu0c6+mrrVYHOwJVAXwMyNNUCdtorCMzTRjuYp9kEDrqQLMJQnTmtnVfpXuVLtX6Na+ld8kv4dfJj61/HpWvt3h+jfqoeV/o0bc+b6Z1xfPrhPdjJP+2uCzWb22tgVQtKWZs7vi2AJV7OO6Mndmqjm/UCL/lIszkSxOOl6/XbzdjquzH4Tjiugp6l4WB5XLlqAne8dmE9YvrhaWek4jVsgWF1cy5Rmm2fYOSPI/m2FwiTfLVdPhQpmLkWQFP5CzrDEQHN7HUV7crrewW51dBvuGDqfXsc=
*/