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