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
UQcVTqG8kpxOVzUqRZt6eDIYjwfvKx+XEvXp4LJfjQr9tJR8SMYUSkdvL8bYznrQrlyNdvVitFeBZzwslucmCmWjTv/U6QzO8uWXre64srw4QXjSftvq9zs952zYsZ91RiOQtige2gOo0R6XPTVb/XoBc4KvKGtJdrjox5q4FEFB4Tl3P3GWLEGxRbEa+EmaUCjFD1lyF06EYCFZBTy4MxzXE/8Lj6Z1kiiNffPXHwcfG+zoCAWx02uNxg0a05/WUfjtHgsh++Qok7NSGPnhFLoQwnhH+uPZ04UQ20q6T+Nozp5SuORp8me4Y/pr6iTlXzRwnKaUdcaYH1WZGvhjA+X2vTaZGDMhzAA8rN1r53SCM3VSYeGis79Sn0B3GCqkfujx2xVuJSGZBehzPgdFRIwQcLCStA/rBY9jqZDI56HQPo/YAc6C5t7AkbNfevRDXPEbzqIQtLlkuSANEj1TkQrH3YKO9QnmGwJZ+HM3vmPCqybWXXQHwGV9A3TZD4CN1jgGCy4OJWSVWAO6+/ztWCO1Zit8ocb+XaILASNskVkhypbzKzDEoylYxYCRq7tUKHcFfKKZ8yhkuD0d/gWKMRhuUez942eY+DTh6R8/f8QynEI8KVsoxKKseoBabV00b4h9LJ48O7g9k5/D
*/