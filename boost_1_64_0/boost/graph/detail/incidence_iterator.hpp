//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_DETAIL_INCIDENCE_ITERATOR_HPP
#define BOOST_GRAPH_DETAIL_INCIDENCE_ITERATOR_HPP

#include <utility>
#include <iterator>

// OBSOLETE

namespace boost
{

namespace detail
{
    // EdgeDir tags
    struct in_edge_tag
    {
    };
    struct out_edge_tag
    {
    };

    template < class Vertex, class Edge, class Iterator1D, class EdgeDir >
    struct bidir_incidence_iterator
    {
        typedef bidir_incidence_iterator self;
        typedef Edge edge_type;
        typedef typename Edge::property_type EdgeProperty;

    public:
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef edge_type reference;
        typedef edge_type value_type;
        typedef value_type* pointer;
        inline bidir_incidence_iterator() {}
        inline bidir_incidence_iterator(Iterator1D ii, Vertex src)
        : i(ii), _src(src)
        {
        }

        inline self& operator++()
        {
            ++i;
            return *this;
        }
        inline self operator++(int)
        {
            self tmp = *this;
            ++(*this);
            return tmp;
        }

        inline reference operator*() const { return deref_helper(EdgeDir()); }
        inline self* operator->() { return this; }

        Iterator1D& iter() { return i; }
        const Iterator1D& iter() const { return i; }

        Iterator1D i;
        Vertex _src;

    protected:
        inline reference deref_helper(out_edge_tag) const
        {
            return edge_type(_src, (*i).get_target(), &(*i).get_property());
        }
        inline reference deref_helper(in_edge_tag) const
        {
            return edge_type((*i).get_target(), _src, &(*i).get_property());
        }
    };

    template < class V, class E, class Iter, class Dir >
    inline bool operator==(const bidir_incidence_iterator< V, E, Iter, Dir >& x,
        const bidir_incidence_iterator< V, E, Iter, Dir >& y)
    {
        return x.i == y.i;
    }
    template < class V, class E, class Iter, class Dir >
    inline bool operator!=(const bidir_incidence_iterator< V, E, Iter, Dir >& x,
        const bidir_incidence_iterator< V, E, Iter, Dir >& y)
    {
        return x.i != y.i;
    }

}
}
#endif

/* incidence_iterator.hpp
yiJlTWfOSimrir/el/o3qfnc78jnQw817fwZXk/GLr0pZXyT/to6rtP2GNSXvyVPHB6UPHn9XX5f6M+pJ2R/0sqXSD71vIdK7Kz8XqljPEE7q2jHWIJy/PCKkzv9N6yfPK/m5PUhDzG9nUGyDYtY4kvZhjtOny1O373qs/CI5PneGsoxs4DjpZTEHcfLYB+OF171WfTLnZ+rtjXpzzaQcUhburUbD1bl7ZHlvua9sOUfLsu8Tpqkx5HcJcvcNMpQTj6JZX4Mm/uH96jTa3iSvDKuvz4e+QyS0TsNPe5n6XfIQ1n5OT4KSczxGXTUZqNH/KcsdY0qbOPn1vTnW8RI/x7jhZb1hDB1U8ooaBSTaT4FZHoQ7dWL0P6wibGB0s8ZlfjObGxkVcdvgJGkzz0lP8+ylEzzqSLHQLQlC5XTg/jtupH32z3mluV9XYUUbETK+YiMjSTLWo3yEpOgKu9ZSyjv0XDKWEIZn1DGY1xvb8vy3UiO7eBdrs+Jzspy2XgecizpcgI4s4vkysoao6iUk8cSa9jHy7f3xb4uOH38tcDA0eUc/Snsycm+Mc9pMox/OV/9VpIx91UZp4OJy5j7ox91lLHLHONf8vxInlfteQLGRAZydd6R7znyOZdVgBdkoT1ftjEtHXlGuOSpE+IY439sgOsY/58zXdX5WrynpMf9d2tbr9MZp7H1d4aabeUPmmPW83sd1Xidk+zTTqkNaaokc6zPZaQZ5t/i26GyLkmbQ9mXyjeC0tf3Dn+vkvlMq3ODS8bvX/9POWxe/+8nf+eU6/XVVGzMAfdxxJ81YxGOWA8zVlW3wTdjuk1/lBnTbQyqm7HKut2BGdNtDB4zYxUdsYJmTLcxCDFjYY5Y1gPu45dbzJh+Hj/sdx+//KYZ08/jrBnTz+OoGdPbPNWM6e0bY8b09g3d7z5WebIZ09uXYMb09nUwY3r7Ys2Y3r4oM6b387EDOlbJ0R4j19v6nFHy8H3jdt9EEYt7m4zSFvdxyhN1vZQ+V5G8G3Rcfnerc01Hmfq3scTH6rj+XSzx4Zmcg+YjPkHXZenfD7o9SJ8DGduD7H8nfToplzpnVHVeOR815LGNlJf0GmllAT53DzvG5B6UEm/fTOIe6j1V3uL6nh+bXEOfyPVjP+f6HfVc9XeNWq6B0/jC8otSt0e6L/MHUbeQTX2uO5Yp6Fbv01zPq+tcf8I6ze/Hx2W7+lGPZMn03q5Q+5Tk4Y4wPjt52ai3MD/rDqnxhaf/A+2O/oF6Tb0/pF5T1z/IPpC6gbZm3cB/dRueh9VW52HdczNF2up8eyt/sc17u97dnNDk8eK9Wv/kvefmf/2em+/lnhh5yO+rhnrcXfPv+U5/L3L6e4HT3zJeoL7OwXte9ekTgstIPGRcnhB8F6vhFayNX2Kkmm6I17GxisfgJeyhphPVdF+8gKNVfJyanozv4yIVX6amV+N53K3i+9X0bUzRdftyHUO2m5fE6IE8ZDypktgJe2FnfBbjcQR2xbnYDddjd9yCCXgS++FlTMHr2B9vYSr+jAPxPvbGwqyzDxbFXtgaR2IHHIXdcTT2xrGYhi/gszgOx+AEnI4TcQFOwlU4BdfjdHwH5+JJnIen8S94HmfjR/gyfo4z8Aq+ijdwIf5VlfMrrsAA9tsSzIlrMBTXYgFchyVwA1bHTWq/n/dx1H1Kvavs9zkGn73Epc02T70YRmNJjMO62BqjsQMOxY74HHbCUdgZX8AuuA674jbshmexL36CyXgJU/BL7I9f4wC8gwPxLg7GX3AI/opD0V+10cqCwzEIn8MQHIEFcCT/CuForIE9sT2Ow+44ARNwEqbhZHwOp+BonIrjcTq+iC/hSzg=
*/