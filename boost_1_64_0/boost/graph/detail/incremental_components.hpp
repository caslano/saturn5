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
uKllv5CG2/mIYNdH+XNnqh9JQ+dIq/0VhU6VYzmgem9hdarR+SKbi2guwjKSYwscHqnlZDmnMHiK/TUhx764FcZGuwxmOSJLxkbIcCXclMhEOQ93eyR3H+/u9rTKEXw8UUuPgwxGUR6v/I0I+GwqVWByBFfuTHS816TsW6oj3p5DQnfGHZtuJP43x2vitEL6b0c88f+FIQ6dKqZg7fTYIyUS2KTfZ1dehPwCVAczfS/JO2ERvDyaqAuLl4UCk2mIQmGya3NWvTnAP0TIESbxHifpvY4BDGYiqqFJeXMTNzwX+hQDlgS6bQAH5jhNt78oiPm3mVZ0/D1PjFvp9V9LesQYFy0l72f0CT4iZIkxUuLsHcj3f8al9G0H2fiOcx7olzgosamwzXtx7ri6qFLKLVqQieqolynSIpc9kopPj9zof0OAgJpOqwIdoIeKZt62+f9ZjbI7WvyFMx4TeS7TrNlqFZN8Pr/KBB0Jm1oYQ5Ew7gL+XtVh/gB4EO6uVnZ8RpTiW079NKDjMOLsAcuUefsI/dAWfVGHwOVQJzKrsm+qLikg1sCAH7vl8A==
*/