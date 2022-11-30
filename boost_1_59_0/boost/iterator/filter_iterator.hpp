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
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
*/