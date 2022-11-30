// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_DWA2002512_HPP
# define ITERATOR_DWA2002512_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/detail/target.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/python/object/iterator.hpp>
# include <boost/python/object_core.hpp>

# if defined(BOOST_MSVC) && (BOOST_MSVC == 1400) /*
> warning C4180: qualifier applied to function type has no meaning; ignored
Peter Dimov wrote:
This warning is caused by an overload resolution bug in VC8 that cannot be
worked around and will probably not be fixed by MS in the VC8 line. The
problematic overload is only instantiated and never called, and the code
works correctly. */
#  pragma warning(disable: 4180)
# endif

# include <boost/bind/bind.hpp>
# include <boost/bind/protect.hpp>

namespace boost { namespace python { 

namespace detail
{
  // Adds an additional layer of binding to
  // objects::make_iterator(...), which allows us to pass member
  // function and member data pointers.
  template <class Target, class Accessor1, class Accessor2, class NextPolicies>
  inline object make_iterator(
      Accessor1 get_start
    , Accessor2 get_finish
    , NextPolicies next_policies
    , Target&(*)()
  )
  {
      using namespace boost::placeholders;
      return objects::make_iterator_function<Target>(
          boost::protect(boost::bind(get_start, _1))
        , boost::protect(boost::bind(get_finish, _1))
        , next_policies
      );
  }

  // Guts of template class iterators<>, below.
  template <bool const_ = false>
  struct iterators_impl
  {
      template <class T>
      struct apply
      {
          typedef typename T::iterator iterator;
          static iterator begin(T& x) { return x.begin(); }
          static iterator end(T& x) { return x.end(); }
      };
  };

  template <>
  struct iterators_impl<true>
  {
      template <class T>
      struct apply
      {
          typedef typename T::const_iterator iterator;
          static iterator begin(T& x) { return x.begin(); }
          static iterator end(T& x) { return x.end(); }
      };
  };
}

// An "ordinary function generator" which contains static begin(x) and
// end(x) functions that invoke T::begin() and T::end(), respectively.
template <class T>
struct iterators
    : detail::iterators_impl<
        detail::is_const<T>::value
      >::template apply<T>
{
};

// Create an iterator-building function which uses the given
// accessors. Deduce the Target type from the accessors. The iterator
// returns copies of the inderlying elements.
template <class Accessor1, class Accessor2>
object range(Accessor1 start, Accessor2 finish)
{
    return detail::make_iterator(
        start, finish
      , objects::default_iterator_call_policies()
      , detail::target(start)
    );
}

// Create an iterator-building function which uses the given accessors
// and next() policies. Deduce the Target type.
template <class NextPolicies, class Accessor1, class Accessor2>
object range(Accessor1 start, Accessor2 finish, NextPolicies* = 0)
{
    return detail::make_iterator(start, finish, NextPolicies(), detail::target(start));
}

// Create an iterator-building function which uses the given accessors
// and next() policies, operating on the given Target type
template <class NextPolicies, class Target, class Accessor1, class Accessor2>
object range(Accessor1 start, Accessor2 finish, NextPolicies* = 0, boost::type<Target>* = 0)
{
    // typedef typename add_reference<Target>::type target;
    return detail::make_iterator(start, finish, NextPolicies(), (Target&(*)())0);
}

// A Python callable object which produces an iterator traversing
// [x.begin(), x.end()), where x is an instance of the Container
// type. NextPolicies are used as the CallPolicies for the iterator's
// next() function.
template <class Container
          , class NextPolicies = objects::default_iterator_call_policies>
struct iterator : object
{
    iterator()
        : object(
            python::range<NextPolicies>(
                &iterators<Container>::begin, &iterators<Container>::end
                ))
    {
    }
};

}} // namespace boost::python

#endif // ITERATOR_DWA2002512_HPP

/* iterator.hpp
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
*/