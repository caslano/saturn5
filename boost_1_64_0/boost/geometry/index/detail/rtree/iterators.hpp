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
H6yPNbEb1sIe+Bheh744EP1QfTcepsj4bKyL92E9qccGWIBBuBOD8U0Mwa9wI34v5c9gKLoxb02xNjbDYAzDltgcO2MLY36wJQ7DVjgOO2MyRuAs7IYLsDvehT1wLfbEzXgtPom9cD/2xo+xD/6C1yGr3xGJdbEfNsH+2AYHYg8chP1wMI7EKJyEQzAJh+JMHIazcTguxBG4DEfhPTgaH8VJ+BVONuoHp+KveAMGsWLjsBnGY0dMwt44HafiDEzCVMzGbGP5cTZuw5uN5ca5eATn4+d4C36Dd2ATtpNl2A3vwv64EifgvTgN1+L9+DBuxMewAPNxNz6KH+BGPGGMl+14lXoW0NweT8t2XBsXO5+H8TSPu/XkeZX6GIWBOAzb4mQMxjgMwXgZnoWNcBmG4QpsiUUy/jC2xg8lfUrS+j62tqvtfWxtuY+tL/cBgVjXTOvnYEqk/E+Oys/B/Cr3DeexFV6Q5w9+w2HoL8vlkOVywWR0xRkyfh564Cr0xtVYC1+W8e+hL5ZI+gczra9rfP3M+etscV0zQ54jmon1MBVDMQPb4iy8xkzr6UVfZnrZMr3ZMr05Mr15Mr35Mj3SF68jZHo+Fse3W+R9hEXojYvNcmpgvpQ7bNGuP0yuy8biAIzBYTgOs3CqXEdNw9sxFldiIt6HybgeZ+J+nCDXUxPxDZyE+nrG3/48v1+Oz8XoiQdQb3eUs3t+v66cP+vJ+bi+nI8Dy1+X+Ntf138rn3taruu/K3d97htglptkdX5zl+sJDMVQbI9NsSu2wP7YEtX3WV68zqKgq+3zbr7Sju4n/W3+GCxpXR8B9tdpT0j53dIOvwcDzbRuFy+R8gNdKreL96wpzzdga+yDnfE67ImRcr/RF0ca08BUHITZOBjnYyLegUPxXhyNz+Mk/AGn4HmcikY/diw2xjgMxwTj8zDx4n2NOtGodjCL+5oSeV7gM2yKn2NLPIlt8QvsIOmukp6JX6JzfYfWc7V9/+VV6X97Td5/OSTvv7wu9x1vyPsvf5P3X46gHM/ZKOU606Xy8bytuzndTjgAe+BI7CnXe9fhFIzEBzAat2AUfolD8CcZ7mZcu6APjsLakg6QdDBGl98OA+23o8HyPG2UPE87BAPNtL7O3S3l51tc534j77V8hz2wFPvgj/L9Bj/hDDyDqfgzzsJzOMdM68+JbiDfn2zxOV/Lev8Gg/Fbaf88jc2Mz5ft4HtsI+lOkp6OP6Dzc0rkc3ZZfE5ZbXM9/YY91I5qrndXnIZ+8t5MdbwLa+G9RjZ8UI2X59mI4iDzc9zkc1wxRD7nDTkevYW63S7I/n4uSNqdg6XdOQT1+2uXKddYyoVKuSao318Lst8u3pb20iPSXvoOBqq0WT7ZmGawa4V+5Bo4RcrfJvdPd8jxcil2wmVyn7MKY/AeTMDlOAdX4GIZv0zG6/Y4Ps/uPZN/yHsmx+U9kxOoyqB+vjfEfnmD5HgaLMfTEAyUtG73CrGv5/vk/nW1tMfej7rd6zLlbpbtIEfeu5iL+j0qKRdmMb9LpJ1pqbTv3YkNJa3bj0Psz4cdpB34Gnl/Irz8++SXmd9BMr+DZX6jUJ9/L1NuipSbKuVu0MtprBD79eIi68VV1osbBkpa30c2tL8frC/rJVDaXRqg7qduaH+d4iHtkZ7SHlkNncf5aCn3ucV1+1bZ7rdhBO7EG/AZTMJ9mIy7MAd34wLcgxtwLz6CRfgEFuIBfArfkOFHJX1M0nr7bGS/vj+R+i9B9d4l6uvNRvbtmu9KufdkezuK+rxAObv3ZV6V92Vek/dlDqH6zid5X+aIvC9zWN6XeVPel3kbx5nj9fyFNrZfv01k/TaV9dtM1m8=
*/