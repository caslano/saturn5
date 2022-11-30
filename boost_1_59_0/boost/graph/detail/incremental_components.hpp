//=======================================================================
// Copyright 2002 Indiana University.
// Copyright 2009 Trustees of Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP
#define BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

#include <boost/operators.hpp>

namespace boost
{

namespace detail
{

    // Iterator for a component index linked list.  The contents of
    // each array element represent the next index in the list.  A
    // special value (the maximum index + 1) is used to terminate a
    // list.
    template < typename IndexRandomAccessIterator >
    class component_index_iterator
    : boost::forward_iterator_helper<
          component_index_iterator< IndexRandomAccessIterator >,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::value_type,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::difference_type,
          typename std::iterator_traits< IndexRandomAccessIterator >::pointer,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::reference >
    {

    private:
        typedef component_index_iterator< IndexRandomAccessIterator > self;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::value_type value_type;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::difference_type reference;
        typedef
            typename std::iterator_traits< IndexRandomAccessIterator >::pointer
                pointer;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::reference difference_type;

        // Constructor for "begin" iterator
        component_index_iterator(
            IndexRandomAccessIterator index_iterator, value_type begin_index)
        : m_index_iterator(index_iterator), m_current_index(begin_index)
        {
        }

        // Constructor for "end" iterator (end_index should be the linked
        // list terminator).
        component_index_iterator(value_type end_index)
        : m_current_index(end_index)
        {
        }

        inline value_type operator*() const { return (m_current_index); }

        self& operator++()
        {
            // Move to the next element in the linked list
            m_current_index = m_index_iterator[m_current_index];
            return (*this);
        }

        bool operator==(const self& other_iterator) const
        {
            return (m_current_index == *other_iterator);
        }

    protected:
        IndexRandomAccessIterator m_index_iterator;
        value_type m_current_index;

    }; // class component_index_iterator

} // namespace detail

} // namespace detail

#endif // BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

/* incremental_components.hpp
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
*/