// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef COUNTING_ITERATOR_DWA200348_HPP
# define COUNTING_ITERATOR_DWA200348_HPP

# include <boost/iterator/iterator_adaptor.hpp>
# include <boost/detail/numeric_traits.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/eval_if.hpp>

namespace boost {
namespace iterators {

template <
    class Incrementable
  , class CategoryOrTraversal
  , class Difference
>
class counting_iterator;

namespace detail
{
  // Try to detect numeric types at compile time in ways compatible
  // with the limitations of the compiler and library.
  template <class T>
  struct is_numeric_impl
  {
      // For a while, this wasn't true, but we rely on it below. This is a regression assert.
      BOOST_STATIC_ASSERT(::boost::is_integral<char>::value);

# ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS

      BOOST_STATIC_CONSTANT(bool, value = std::numeric_limits<T>::is_specialized);

# else

#  if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
      BOOST_STATIC_CONSTANT(
          bool, value = (
              boost::is_convertible<int,T>::value
           && boost::is_convertible<T,int>::value
      ));
#  else
    BOOST_STATIC_CONSTANT(bool, value = ::boost::is_arithmetic<T>::value);
#  endif

# endif
  };

  template <class T>
  struct is_numeric
    : mpl::bool_<(::boost::iterators::detail::is_numeric_impl<T>::value)>
  {};

#  if defined(BOOST_HAS_LONG_LONG)
  template <>
  struct is_numeric< ::boost::long_long_type>
    : mpl::true_ {};

  template <>
  struct is_numeric< ::boost::ulong_long_type>
    : mpl::true_ {};
#  endif

  // Some compilers fail to have a numeric_limits specialization
  template <>
  struct is_numeric<wchar_t>
    : mpl::true_ {};

  template <class T>
  struct numeric_difference
  {
      typedef typename boost::detail::numeric_traits<T>::difference_type type;
  };

  BOOST_STATIC_ASSERT(is_numeric<int>::value);

  template <class Incrementable, class CategoryOrTraversal, class Difference>
  struct counting_iterator_base
  {
      typedef typename detail::ia_dflt_help<
          CategoryOrTraversal
        , mpl::eval_if<
              is_numeric<Incrementable>
            , mpl::identity<random_access_traversal_tag>
            , iterator_traversal<Incrementable>
          >
      >::type traversal;

      typedef typename detail::ia_dflt_help<
          Difference
        , mpl::eval_if<
              is_numeric<Incrementable>
            , numeric_difference<Incrementable>
            , iterator_difference<Incrementable>
          >
      >::type difference;

      typedef iterator_adaptor<
          counting_iterator<Incrementable, CategoryOrTraversal, Difference> // self
        , Incrementable                                           // Base
        , Incrementable                                           // Value
# ifndef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
          const  // MSVC won't strip this.  Instead we enable Thomas'
                 // criterion (see boost/iterator/detail/facade_iterator_category.hpp)
# endif
        , traversal
        , Incrementable const&                                    // reference
        , difference
      > type;
  };

  // Template class distance_policy_select -- choose a policy for computing the
  // distance between counting_iterators at compile-time based on whether or not
  // the iterator wraps an integer or an iterator, using "poor man's partial
  // specialization".

  template <bool is_integer> struct distance_policy_select;

  // A policy for wrapped iterators
  template <class Difference, class Incrementable1, class Incrementable2>
  struct iterator_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return y - x;
      }
  };

  // A policy for wrapped numbers
  template <class Difference, class Incrementable1, class Incrementable2>
  struct number_distance
  {
      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return boost::detail::numeric_distance(x, y);
      }
  };
}

template <
    class Incrementable
  , class CategoryOrTraversal = use_default
  , class Difference = use_default
>
class counting_iterator
  : public detail::counting_iterator_base<
        Incrementable, CategoryOrTraversal, Difference
    >::type
{
    typedef typename detail::counting_iterator_base<
        Incrementable, CategoryOrTraversal, Difference
    >::type super_t;

    friend class iterator_core_access;

 public:
    typedef typename super_t::difference_type difference_type;

    counting_iterator() { }

    counting_iterator(counting_iterator const& rhs) : super_t(rhs.base()) {}

    counting_iterator(Incrementable x)
      : super_t(x)
    {
    }

# if 0
    template<class OtherIncrementable>
    counting_iterator(
        counting_iterator<OtherIncrementable, CategoryOrTraversal, Difference> const& t
      , typename enable_if_convertible<OtherIncrementable, Incrementable>::type* = 0
    )
      : super_t(t.base())
    {}
# endif

 private:

    typename super_t::reference dereference() const
    {
        return this->base_reference();
    }

    template <class OtherIncrementable>
    difference_type
    distance_to(counting_iterator<OtherIncrementable, CategoryOrTraversal, Difference> const& y) const
    {
      typedef typename mpl::if_<
          detail::is_numeric<Incrementable>
        , detail::number_distance<difference_type, Incrementable, OtherIncrementable>
        , detail::iterator_distance<difference_type, Incrementable, OtherIncrementable>
      >::type d;

      return d::distance(this->base(), y.base());
    }
};

// Manufacture a counting iterator for an arbitrary incrementable type
template <class Incrementable>
inline counting_iterator<Incrementable>
make_counting_iterator(Incrementable x)
{
  typedef counting_iterator<Incrementable> result_t;
  return result_t(x);
}

} // namespace iterators

using iterators::counting_iterator;
using iterators::make_counting_iterator;

} // namespace boost

#endif // COUNTING_ITERATOR_DWA200348_HPP

/* counting_iterator.hpp
QKsdq+aw9wEUw32I0sh25EOUBjto4gwHqKIPo+CJhH8HpVX8SuND9TTlI1/azuzaivJwDxYH3rxwoZPlqXdEZKtn96XsOXilMu9zCD6HNO2+aubnfK9xB3ve5LhOeVJZ4hjL38NfPUWx91B2P+ruYnTXOgTb8bHA7ezZdEcZWI7EoHtQzU9jB29KePxRTP55C6Ovc+zH7Oh3qGOxYwSfNxWyfGvwJFvI28nnY8fD8jieVBbreQX9VZeyaDA7t1AbPA/eC+FPajF/glI2FofxEYDqE84krU/I5za58I+nWD2ucTWr58zHY03aXLci9D2q/QpgP0pjfIA3pDHe2LjhG0wWRXm5MHx/QnP/muY+7dTg+2LN/RzN/XJ+rzkzPkcfq/OIGtPuee6TW1t8bnXhoVHRzq2FtlXF6NNlfR3KihmrEe1OPicU++CUXD2vVeOxjzjKa1tL+1bfNhM+a0349FwkPqdRjLPnAS56Z7wXDt0g8Nk+K9w3ZUb7f2q7EbqdnDdK4+P+nXD+dHVdAq5ZSM997HkK2jLS2F/Y+87SepR3o2RV3tPwX2H9odkrxFf+GKMtRPk8xiblH850+THKE1nr6ENZar+eDpv05MOP1DWGt3mcc93OlAWgUZ8N4NmefHp3C88W4ll+HtZj8sPv8WRPVllWddbyrLVZVWytIzMrKwuhLsdnjcO/srQRzpTktNnOlGHIK857sqkf+Abjs0Gc39DcB2tG7NlW3XtmpDr+Yc+uoXsHlZMpznG43/yDPUuChnDPae/AW/kdiBdVIM5xuE5/zmjWY+a1hOt07q/D5ZCtqZy7mL7ceeHAONepuky6zjkszZmZ6xyfpT6rQvouwPWaZ+o7Ugu5ZJcA6OtZHOtpfNzUB4cK06zDGl3kXcnW6LisHYynSawdlJq+J8X3Yqd6z3wM/ol7+CfuVT+B7+AevqNpJ+kUXy+PCs0F/BFp3b/m7YS/xDXjRln7pXwO0dZcpj3sWZbpGCEX+C5G57S8rmI0XvRTgOkPATIB9wDyYYveqGyoeBYGCXgelY3z8VVGVymf95GcRm056YVIWx7G/a6IpWHdkvoPBf0W/uP9glkbdxai3pHkS8lXOpMynelpoNH6FN2zsZiZf73I+L9U41/SeMWijlGm6F+M/5g+VjQqXOC9ZIe7AceQ1vDCIDugE5fbof0FQzugDHM7fI89z0O5KdwOv4jDDnthg56ii2eHz77w1tmhFzyzdkF26KH2UNo3yA6dRu1hRp+hHVCGuR3uVJ+zPjqN2+FjfUO3Q8kolfeLZ4fGvrfODjWjwwV+m+zwLcCXCsFz1A5oC+HBifh7z0Li9RVGNwMlpih5AMEOVAb/jaPWHlzeqS+y9yy3Rbl6jzuZzgcgi/o+OwBdHypBmwN2vr2BrQ00YN/lwRIaXyBtBtJ8SAuU0LiigY0rVmbVAk/MmhIZTiSz0USKOJbgc4oVjJfVSrlkvTRfNQR7XgcK5Jd861nDnq/Ab7pckXEFlZkuXTttYs/mKmORQvog+mTdmKJQHa+rz9iXpBGgRxqnL2Dfh/ZA/gchf6Oqp5QOZ+bwqF9uRpp2rFBIuu0rIX9OXeBErHzL44Vc0OSw+ouZ/6ZbGC/Qb2+Zrw6Y+GqwjOJAJqt7VwHAT5Qi/cVBvurr8qFsmh86InMqVHkMZb/CaCckl5H9Xmb3Y5M/Av09gbnjbxwpypVJY5WjSR5aR3coX/iNSvOOJKfyD8fUJOkZKeBBe+YJ6lWnH1T3kQu4wnZJjvj9136r3o9UxpAtz7Hnw5PfA019RbnOMR88PJxUy8eYRxn9J1hbK1K6aM4c4W9VUoryfkfAsV65BPxL1yyJR207LlI=
*/