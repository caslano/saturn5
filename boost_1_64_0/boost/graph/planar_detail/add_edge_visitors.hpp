//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __ADD_EDGE_VISITORS_HPP__
#define __ADD_EDGE_VISITORS_HPP__

#include <boost/property_map/property_map.hpp>

namespace boost
{

struct default_add_edge_visitor
{

    template < typename Graph, typename Vertex >
    void visit_vertex_pair(Vertex u, Vertex v, Graph& g)
    {
        add_edge(u, v, g);
    }
};

template < typename EdgeIndexMap > struct edge_index_update_visitor
{

    typedef
        typename property_traits< EdgeIndexMap >::value_type edge_index_value_t;

    edge_index_update_visitor(
        EdgeIndexMap em, edge_index_value_t next_index_available)
    : m_em(em), m_next_index(next_index_available)
    {
    }

    template < typename Graph, typename Vertex >
    void visit_vertex_pair(Vertex u, Vertex v, Graph& g)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_t;
        std::pair< edge_t, bool > return_value = add_edge(u, v, g);
        if (return_value.second)
            put(m_em, return_value.first, m_next_index++);
    }

private:
    EdgeIndexMap m_em;
    edge_index_value_t m_next_index;
};

} // namespace boost

#endif //__ADD_EDGE_VISITORS_HPP__

/* add_edge_visitors.hpp
XItDcQPOxE04B7fgWtyKG3A7vo2v4Qe4A4/iTjyJu/EsvoWX8F0MDWZ/xCjch5VwP1bDA5iIB7EzHsZR+Ak+ip/iXDyGC/A4LsLP8Xn8Al/AL3EjnsL9eA4P4nn8Cn/CK3gRo0LY7rAi/oYN8Aa2xJuYhLfwQfwLJ6BRjPWCJr6INlyLfrgb/fFjDMCTGIg/YRCaoYYRglUwFBtjcWyGJbAzRuIgLIlDsBSmYjRmYFmch+XwOayAr+I9+C+shCewMv6MVfAWVsXbWB2rhLG/4/1YE9MwAadgPXwUG+J+bIQnsDH+iq3RcbNpItbE5tgIa2F3fAD7YhdMxq7q+LhRP08m1wLk+FjPkN8t5N9/iql2MPbFKzgKf8NcvIpz8To+izcwH3/H3fgHHsA/8ST6Bar2Lv6BdizNdwVjHQzB5hiKvTAMh2JxTMVwnI+RuArL4A4si29gefwDK2CYjfNQrIUV8X6Mww5YHUdiPGbivTgX6+CzeB/mYwLuwrr4NtbDj7EBHsaG+Dk2wu+xCf4bm+ENbI4BLNcWGIItMRJbYSlMxDLYDmviLZZTInYknYKdcBhSF8n6umCoZ6vU81lJRIz8Xlv4L49yJXERlsbnMAaXorzPCSvhQayDL2BHXIED8EXMxFU4DtfgQtyAr+LLuB834ce4BS9iPv6Cr2EZk3oGy+KbWA7fwlh8F+/HDTgYD+AI/AAfww8xDw+q+U3Uz+9wrVLNb1WD5Y9ynxHlqmAPrKbSNVS6pkrXUel22Bs7q3Q3le6F/XAqDsHnMAVX4VBcg8NxE6aq5ZCGezEdz2Em/o7ZGMW0jVPzPR6r4QRsjZOwHU7GzpiDw3Cq2r4fwXSchjNxOs7Cx3Au5uJanInrcBa+jbNxLz6FZ3A+nsWnUd0PoJ4rkedfWI7u9wOc8mf94Gmshl9jTfwG2+G32BHP4BVM089ZyLMfMr57+XuQWi/n+N7q+D3WxR+wPv6olnvxIOohLIFyzxpOxNL4NMbi8xiHa7EybsCquAWr4WGsjscwHv/AezHQpP7EClgLK2FtbIB1sA0mYEesi/2xHo7CBpiFDXEcNsKF+DfT/QLexg1oOqYDbfg++uEHGICHsBgewUA8jpcY7jJeRsNWmA5B0lJP/Yql8BpWwOtYH2+o9bfbUPfL44NqPyjF31vV+ruf74nGdhiDXbAPdsNBmIRTsTfOwD44F/vii/ggvokDcS8Owq8xBc/jUDT5zpEYgmOxImZiDczC+piNzfFhbI8TkOnnnEvdt40z1PSX5e/javonU+5efBRb4XQcgjPVdjELp+ATuARn43J8EjfiHHwF5+IefAr34Tw8ik/jaczDH3AhXsZFeBsXq/lbgsXxWSyJz2E8LsO2+DxKf0o4BFdgKq5EqZ/1PcPsw2q/aMbfp9V+sYZy1fElNb+b8SHcgsNxK07CbfgI5qv1tBMX4G5ch2/iJnwLt+LbmI/v4S7ci+/g+2o5fICf4of4bzyIF/FfeA0/RsdEH8JwdKTLqXQF/BQr4TFsgp9hSzyh9qcv1HI5iT3xS+yHX2E6nsJM/AYfxTM4E7/DZXgOV+L3uBl/wO14Ad/A/6j97Ef8EH/CL/EinsJf8Bxewov4G/6JVzHCsV9hSbyBFfFvrIG3sSYawYXXkUxsjHbsgEE4EINxOIbiKAxD1jc9Nql7QLGrUbi+g7CPrG3SxTgOYi+Mxf4Yj72xNvbDevggNsZkbKnKdVTpvXbmg5Ev4+J0Mhv3rW02Y1p7tgnSh4jzxC0imovWCUQnIoXIIfKIrcQB4jRxlQjt7m9UIVoQfYgMYhaxjMgnCojzxC2ifA8+68JxAldjAXGTqMX0DCLyiD1EqW4=
*/