// Boost.Geometry Index
//
// R-tree iterators
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace iterators {

template <typename Value, typename Allocators>
struct end_iterator
{
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    reference operator*() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        pointer p(0);
        return *p;
    }

    const value_type * operator->() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        const value_type * p = 0;
        return p;
    }

    end_iterator & operator++()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    end_iterator operator++(int)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    friend bool operator==(end_iterator const& /*l*/, end_iterator const& /*r*/)
    {
        return true;
    }
};

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class iterator
{
    typedef visitors::iterator<Value, Options, Translator, Box, Allocators> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    inline iterator()
    {}

    inline iterator(node_pointer root)
    {
        m_visitor.initialize(root);
    }

    reference operator*() const
    {
        return m_visitor.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }

    iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }

    iterator operator++(int)
    {
        iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(iterator const& l, iterator const& r)
    {
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(iterator const& l, end_iterator<Value, Allocators> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_iterator<Value, Allocators> const& /*l*/, iterator const& r)
    {
        return r.m_visitor.is_end();
    }
    
private:
    visitor_type m_visitor;
};

}}}}}} // namespace boost::geometry::index::detail::rtree::iterators

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ITERATORS_HPP

/* iterators.hpp
vJel8Qu/55+bXUBcnRXdzcajM0XeudsHqSLE4YdctbuWKl+w13ngyUtMIyE8pNwHom1NO/tLvSAw5MEPc0dh/eK6sKEDubvM0bEoOruFpO7yE/SwmsXdhHA+fWR5vlPvzTk+MbgQej2cYEly5dHuFuCXvDUexZlL+Mtqx22wKe/NT2SckY7dqeV3MnOovLoXxg7xJH/On8nVxAxjp6sZ1ScBkU+zu9oeseW5cf0mzUEShZuGfzZVfhYawYPw9zm/rf+19yC+dlKP+kvRRi3qqOgoxW9ONAVPBE6lzFs3nxb3Mug+fBVRsxg/ePxaxBs/CjD55g6zaK2Yb8GRKCeVlHa4uo0rfeAw5HjeHm9WRFcOPyacRY8gHOcmsua9Hki5fZrRmSEoO6w/NxL2o5GDop4T3xCzRCrzglXMYhzdR5G5UBtTk4mz+C8WNR85hb33J5HjMy/P5ak9Almf2laXyVsPpS53N8ndhGKPpT6o+xDal7wdnxsHXPDDLK0z+Op/IpiMyRTSpHdm6rPECq/6jcuTJ4e00jf4pn6cxPtYlIR0nL//+XncJlHUYZZUj7HRdabz4qEBKQXs2abMP7hBQ/ZtTz9N258fXPnxFrMEvNBd6sjv7GjIkEjh+6wvdSWbwgDigLyYH69UAV4JAO9TEOeNZRZfvOLZ1qmOLtslELkad3nL/Xc65wtczecKm8CLc5ho8Z6wm0ADpHO7
*/