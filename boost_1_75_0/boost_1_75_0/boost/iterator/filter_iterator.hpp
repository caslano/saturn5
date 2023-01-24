// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_FILTER_ITERATOR_23022003THW_HPP
#define BOOST_FILTER_ITERATOR_23022003THW_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/type_traits/is_class.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace iterators {

  template <class Predicate, class Iterator>
  class filter_iterator;

  namespace detail
  {
    template <class Predicate, class Iterator>
    struct filter_iterator_base
    {
        typedef iterator_adaptor<
            filter_iterator<Predicate, Iterator>
          , Iterator
          , use_default
          , typename mpl::if_<
                is_convertible<
                    typename iterator_traversal<Iterator>::type
                  , random_access_traversal_tag
                >
              , bidirectional_traversal_tag
              , use_default
            >::type
        > type;
    };
  }

  template <class Predicate, class Iterator>
  class filter_iterator
    : public detail::filter_iterator_base<Predicate, Iterator>::type
  {
      typedef typename detail::filter_iterator_base<
          Predicate, Iterator
      >::type super_t;

      friend class iterator_core_access;

   public:
      filter_iterator() { }

      filter_iterator(Predicate f, Iterator x, Iterator end_ = Iterator())
          : super_t(x), m_predicate(f), m_end(end_)
      {
          satisfy_predicate();
      }

      filter_iterator(Iterator x, Iterator end_ = Iterator())
        : super_t(x), m_predicate(), m_end(end_)
      {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
          // Don't allow use of this constructor if Predicate is a
          // function pointer type, since it will be 0.
          BOOST_STATIC_ASSERT(is_class<Predicate>::value);
#endif
          satisfy_predicate();
      }

      template<class OtherIterator>
      filter_iterator(
          filter_iterator<Predicate, OtherIterator> const& t
          , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0
          )
          : super_t(t.base()), m_predicate(t.predicate()), m_end(t.end()) {}

      Predicate predicate() const { return m_predicate; }

      Iterator end() const { return m_end; }

   private:
      void increment()
      {
          ++(this->base_reference());
          satisfy_predicate();
      }

      void decrement()
      {
        while(!this->m_predicate(*--(this->base_reference()))){};
      }

      void satisfy_predicate()
      {
          while (this->base() != this->m_end && !this->m_predicate(*this->base()))
              ++(this->base_reference());
      }

      // Probably should be the initial base class so it can be
      // optimized away via EBO if it is an empty class.
      Predicate m_predicate;
      Iterator m_end;
  };

  template <class Predicate, class Iterator>
  inline filter_iterator<Predicate,Iterator>
  make_filter_iterator(Predicate f, Iterator x, Iterator end = Iterator())
  {
      return filter_iterator<Predicate,Iterator>(f,x,end);
  }

  template <class Predicate, class Iterator>
  inline filter_iterator<Predicate,Iterator>
  make_filter_iterator(
      typename iterators::enable_if<
          is_class<Predicate>
        , Iterator
      >::type x
    , Iterator end = Iterator())
  {
      return filter_iterator<Predicate,Iterator>(x,end);
  }

} // namespace iterators

using iterators::filter_iterator;
using iterators::make_filter_iterator;

} // namespace boost

#endif // BOOST_FILTER_ITERATOR_23022003THW_HPP

/* filter_iterator.hpp
Rb5cibkrzg35+o6dd3LeeYjyQF9wmQAzdHBBQRnoYEjHEWNOsXaDUEiuJmyIA0JR+Gv7fUtbz06dgSFMPf9khPwKZIZLemjI4EPx9r1mziF6qFG7B4jkvjsiEjp8GKARIkzxZjNq7n4g7RXyD2o+e02Nftjvxu7G/3hzO3/hy78DNE6z1Uu9hKSGSsABihjkf/2gfKpVdQ7GF0ieoQjPH415vnOwN4pTrRzLh16e8jfzY/FSJ8f3EQYNOUsE88NdeS4w5OG3HZXhMWo6kwDRAj8iKQSlcRYvUXCjuJdeYOm6dTIp+b94Py4f0+i4uCGUfkn7VQho358hiS+0lG1m45Azk+zDcPTtpIEZDW30P+7KHJNSQxeXLtGwjxYZOVSOjr512MHyrjlO6ahCWkDq0XIno+oL0Ib+HtZhjYF8zsmNuTiNInl2bt0oOPcP3e7swAAjCaNUuSG1DZ0+z7mRi24n/LAuqC/c1FAi2s9q/nOSEATdwhDJnzaj35Nxe3aiAtIyFZsnlMiIlLlGXSfRm0BhPdhabeA3k3tUYQL5wnsYNcIk2WvMvcOTS929yj8sFSbo15aMjZ9aCVbjAXlMItDLguHXoykMUlbr+IYrUtOOWcgDLC0UOtNRGhj2yD+2VNQsWUqBmMxHFtw7ZlwXnt3vc0J/2tdaKgWUxjFMXwRnrWtN0C0tsFJyPzZyA+jHbbWM7XuYi1y7LlRl
*/