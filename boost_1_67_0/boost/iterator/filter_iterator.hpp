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