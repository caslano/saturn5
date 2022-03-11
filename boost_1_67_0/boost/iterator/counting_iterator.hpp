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
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
*/