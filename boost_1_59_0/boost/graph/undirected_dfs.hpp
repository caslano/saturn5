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
#ifndef BOOST_GRAPH_UNDIRECTED_DFS_HPP
#define BOOST_GRAPH_UNDIRECTED_DFS_HPP

#include <boost/graph/depth_first_search.hpp>
#include <vector>
#include <boost/concept/assert.hpp>

namespace boost
{

namespace detail
{

// Define BOOST_RECURSIVE_DFS to use older, recursive version.
// It is retained for a while in order to perform performance
// comparison.
#ifndef BOOST_RECURSIVE_DFS

    template < typename IncidenceGraph, typename DFSVisitor,
        typename VertexColorMap, typename EdgeColorMap >
    void undir_dfv_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, VertexColorMap vertex_color, EdgeColorMap edge_color)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        typedef typename graph_traits< IncidenceGraph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< VertexColorMap, Vertex >));
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< EdgeColorMap, Edge >));
        typedef
            typename property_traits< VertexColorMap >::value_type ColorValue;
        typedef
            typename property_traits< EdgeColorMap >::value_type EColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        BOOST_CONCEPT_ASSERT((ColorValueConcept< EColorValue >));
        typedef color_traits< ColorValue > Color;
        typedef color_traits< EColorValue > EColor;
        typedef typename graph_traits< IncidenceGraph >::out_edge_iterator Iter;
        typedef std::pair< Vertex,
            std::pair< boost::optional< Edge >, std::pair< Iter, Iter > > >
            VertexInfo;

        std::vector< VertexInfo > stack;

        put(vertex_color, u, Color::gray());
        vis.discover_vertex(u, g);
        stack.push_back(std::make_pair(
            u, std::make_pair(boost::optional< Edge >(), out_edges(u, g))));
        while (!stack.empty())
        {
            VertexInfo& back = stack.back();
            u = back.first;
            boost::optional< Edge > src_e = back.second.first;
            Iter ei = back.second.second.first,
                 ei_end = back.second.second.second;
            stack.pop_back();
            while (ei != ei_end)
            {
                Vertex v = target(*ei, g);
                vis.examine_edge(*ei, g);
                ColorValue v_color = get(vertex_color, v);
                EColorValue uv_color = get(edge_color, *ei);
                put(edge_color, *ei, EColor::black());
                if (v_color == Color::white())
                {
                    vis.tree_edge(*ei, g);
                    src_e = *ei;
                    stack.push_back(std::make_pair(u,
                        std::make_pair(src_e, std::make_pair(++ei, ei_end))));
                    u = v;
                    put(vertex_color, u, Color::gray());
                    vis.discover_vertex(u, g);
                    boost::tie(ei, ei_end) = out_edges(u, g);
                }
                else if (v_color == Color::gray())
                {
                    if (uv_color == EColor::white())
                        vis.back_edge(*ei, g);
                    call_finish_edge(vis, *ei, g);
                    ++ei;
                }
                else
                { // if (v_color == Color::black())
                    call_finish_edge(vis, *ei, g);
                    ++ei;
                }
            }
            put(vertex_color, u, Color::black());
            vis.finish_vertex(u, g);
            if (src_e)
                call_finish_edge(vis, src_e.get(), g);
        }
    }

#else // BOOST_RECURSIVE_DFS

    template < typename IncidenceGraph, typename DFSVisitor,
        typename VertexColorMap, typename EdgeColorMap >
    void undir_dfv_impl(const IncidenceGraph& g,
        typename graph_traits< IncidenceGraph >::vertex_descriptor u,
        DFSVisitor& vis, // pass-by-reference here, important!
        VertexColorMap vertex_color, EdgeColorMap edge_color)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< IncidenceGraph >));
        BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, IncidenceGraph >));
        typedef
            typename graph_traits< IncidenceGraph >::vertex_descriptor Vertex;
        typedef typename graph_traits< IncidenceGraph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< VertexColorMap, Vertex >));
        BOOST_CONCEPT_ASSERT(
            (ReadWritePropertyMapConcept< EdgeColorMap, Edge >));
        typedef
            typename property_traits< VertexColorMap >::value_type ColorValue;
        typedef
            typename property_traits< EdgeColorMap >::value_type EColorValue;
        BOOST_CONCEPT_ASSERT((ColorValueConcept< ColorValue >));
        BOOST_CONCEPT_ASSERT((ColorValueConcept< EColorValue >));
        typedef color_traits< ColorValue > Color;
        typedef color_traits< EColorValue > EColor;
        typename graph_traits< IncidenceGraph >::out_edge_iterator ei, ei_end;

        put(vertex_color, u, Color::gray());
        vis.discover_vertex(u, g);
        for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
        {
            Vertex v = target(*ei, g);
            vis.examine_edge(*ei, g);
            ColorValue v_color = get(vertex_color, v);
            EColorValue uv_color = get(edge_color, *ei);
            put(edge_color, *ei, EColor::black());
            if (v_color == Color::white())
            {
                vis.tree_edge(*ei, g);
                undir_dfv_impl(g, v, vis, vertex_color, edge_color);
            }
            else if (v_color == Color::gray() && uv_color == EColor::white())
                vis.back_edge(*ei, g);
            call_finish_edge(vis, *ei, g);
        }
        put(vertex_color, u, Color::black());
        vis.finish_vertex(u, g);
    }

#endif // ! BOOST_RECURSIVE_DFS

} // namespace detail

template < typename Graph, typename DFSVisitor, typename VertexColorMap,
    typename EdgeColorMap, typename Vertex >
void undirected_dfs(const Graph& g, DFSVisitor vis, VertexColorMap vertex_color,
    EdgeColorMap edge_color, Vertex start_vertex)
{
    BOOST_CONCEPT_ASSERT((DFSVisitorConcept< DFSVisitor, Graph >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph >));

    typedef typename property_traits< VertexColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(vertex_color, *ui, Color::white());
        vis.initialize_vertex(*ui, g);
    }
    typename graph_traits< Graph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        put(edge_color, *ei, Color::white());

    if (start_vertex != *vertices(g).first)
    {
        vis.start_vertex(start_vertex, g);
        detail::undir_dfv_impl(g, start_vertex, vis, vertex_color, edge_color);
    }

    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        ColorValue u_color = get(vertex_color, *ui);
        if (u_color == Color::white())
        {
            vis.start_vertex(*ui, g);
            detail::undir_dfv_impl(g, *ui, vis, vertex_color, edge_color);
        }
    }
}

template < typename Graph, typename DFSVisitor, typename VertexColorMap,
    typename EdgeColorMap >
void undirected_dfs(const Graph& g, DFSVisitor vis, VertexColorMap vertex_color,
    EdgeColorMap edge_color)
{
    undirected_dfs(g, vis, vertex_color, edge_color, *vertices(g).first);
}

namespace detail
{
    template < typename VertexColorMap > struct udfs_dispatch
    {

        template < typename Graph, typename Vertex, typename DFSVisitor,
            typename EdgeColorMap, typename P, typename T, typename R >
        static void apply(const Graph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params< P, T, R >&, EdgeColorMap edge_color,
            VertexColorMap vertex_color)
        {
            undirected_dfs(g, vis, vertex_color, edge_color, start_vertex);
        }
    };

    template <> struct udfs_dispatch< param_not_found >
    {
        template < typename Graph, typename Vertex, typename DFSVisitor,
            typename EdgeColorMap, typename P, typename T, typename R >
        static void apply(const Graph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params< P, T, R >& params, EdgeColorMap edge_color,
            param_not_found)
        {
            std::vector< default_color_type > color_vec(num_vertices(g));
            default_color_type c = white_color; // avoid warning about un-init
            undirected_dfs(g, vis,
                make_iterator_property_map(color_vec.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    c),
                edge_color, start_vertex);
        }
    };

} // namespace detail

// Named Parameter Variant
template < typename Graph, typename P, typename T, typename R >
void undirected_dfs(const Graph& g, const bgl_named_params< P, T, R >& params)
{
    typedef typename get_param_type< vertex_color_t,
        bgl_named_params< P, T, R > >::type C;
    detail::udfs_dispatch< C >::apply(g,
        choose_param(
            get_param(params, graph_visitor), make_dfs_visitor(null_visitor())),
        choose_param(get_param(params, root_vertex_t()), *vertices(g).first),
        params, get_param(params, edge_color), get_param(params, vertex_color));
}

template < typename IncidenceGraph, typename DFSVisitor,
    typename VertexColorMap, typename EdgeColorMap >
void undirected_depth_first_visit(const IncidenceGraph& g,
    typename graph_traits< IncidenceGraph >::vertex_descriptor u,
    DFSVisitor vis, VertexColorMap vertex_color, EdgeColorMap edge_color)
{
    detail::undir_dfv_impl(g, u, vis, vertex_color, edge_color);
}

} // namespace boost

#endif

/* undirected_dfs.hpp
0kV6WfxEQIE3x3sTrB9Es0rOIQ5z7nyxt7FOQR+HHVGr5rUlsAFeetTVS7nNiLCCDTBLTxPnZgN2jg+6qwVIm7MoxF0KMKIm3L1O3v7I4Tu3PA/juyZ7hvvihAu4N5vV6ydaqpEVzgCjQ0lX2IO+8ZskHcClYq7teJMpTchz5rvmvfhqHY9jSf3J8nFqJc43l17S2qm0esUXKEEoH/L7lza7JsEk1W5ZEjzvKg/oidlUws+mZcJqyAU39qIchKZ6qOeaSscyL4gihXw88gPNKkLL6iP6bqGiyvAmvfgVqCL6uxuHRmgi50Txf8xJ0NYHRLLcb49A907iNVUEHJzICAWbVlE3HOKRPa6lksOQBRhJjKFjq9Ix85NLGN0PnCyippYwFlOy9t6vuwRpBlGQIb9nLp2lGaNg74G/LTSRNVf+mLrDatbJc3OPXPlmH2pQFTA7XZ2N97n2On5tqgeniDisCzakacasVPPsPnRRI5TuOsDx680/8+TkKy4lWrVpmlN3WKX2UaKIWUqZmJn8bRNLcun5EryRrGnLcgQreZUV/4SVjsOJCFFpLgcdPjsvo/t3Y9B5u8jkL+8IBEvMjQqcWbkRA/pPCWAueUNogmJ538kPBzzXhQVjg2atyvsbu2mk65mq8hyi28GJun6Tz+DOH6NtEJWsdrispslHymeHMg+sU3hl7rYDpUWCzXE4XeiwWuXmGbLt7OASlLyHLRwKcLGCxu/kAsxdKBhyL0H2pcPF3thooQCEFuFhr2pRp1EMmSkNIkDsUL67TpG9tDdHx2kefgEb2U1ujmiKS+DdF81mnJP3GP08jveDs57tMH/DbZ4yngvDbjBNssSCPjdZnCMCvvv7cW+klz2MeTLqsuOJtr78oSBYs/UEoLZYTUOXsKJfw8h0vvACM/LnR3xW1WpuphgFrv24vD7eSipoFsmS+Qs9DP2j/V1TFLb2Rmcb9GEbgaNqQ1IOrLhk+CHKgjQLbxiY8xmIxzAqYuwazmY6PoUw+UydfQ/BNYXrOsaaULKImvFR6sMfSPFbk4BoDWFtjq45Tne6vOXLOv30k15veE63nG54dtkqcun+i1uNN+ISpuVvQfEPBP5HwwcsWD0BTEKKQlXl68AXd6jVBwFOfXU15JY54uonq9CpOebopUPw+W+QIC2q+bp/CBa0H/C6a6PRGsLrPEJaaIfK690kD2nZlC0qQCR6C2RC9r+3GihzRY5suiwmKFXqKnnDPZo7+sD8cszhVqC6ADdsPKXOs0+4/M21SsYYJ3QXPVVqvHJ6o/tu8RgQYjf9M9zlk/eY1uWVx5ekCxjLH4b7k7iEZvWl9LROZFGNf6M9yPOfhLp2Mn4yIQnrYLsslqlqwK9gy2MpGw3rG+LQMCFMXUg+9yHP7WWi/Y1AahP6Q1sfJFOH93GtirKJD1F7PYYNMHz6QDNGL9tlaBIeGcerYB8s/9Y7TDJPql7jjpxMj80Hlzx3PBXxM8pk/8HekMHioKszLu/hVwcfWRdPJE2X+NetLM1knTKVP6NU+UcgSdjcWVC7fYiW0clbXUAYUV+VE271TgPJBumqFjLsYD7DosNPnTkpbPzn53oja5Zj54jnzvtj4LGGYfKUeZIPUqYM/tWhlk/0X2gnwitNFmzD5K1Yxt0LRL5cF2Y+R6p9ajGKcGrMaa1H/s7EcM+QtUpX2CXfxhNezVGGa/Y6mkwmpjpjriKlog/ED2F2iTH7b6Y/MJZHJGzJr3Xr3FhNHc6gl0LVsQbGkMOUybHCls6bB5WX+G/24MnlP5kr2zccimhA1Ktzv1nmumsAJJYeM5K+3w6ZPnizGHBHROjjHt9e1VFDszSRwwge1YikxUQvetlY8leydnXTrNytT6HK3C1o0kQv+CayRK+IM+9iDrsEmWvAXdPxw7VCI6elSjxI7iFCS7E54oA6XPunizTYMGSMhrWcGIaHJ7t+vGs9VnQ8TEJhQCugj+BtjEGd40/0fMZc/jQKa8XH6wAKX7d8MAcFDA5wIQ2j3sKZagw+WkM3b4kKEGyyzPVQvB1DJj7dJlGkbYK6CzwgP5eKXLDiw/AOHYZ70Styjanz4ebi+asjZjkltYBFkyux5vqufwQ7ybJEc+CIPesKYkvVu6M5lOn2IvA3y+9RY7txXs5qzSTcnK5pIzkcUOZb/NGeMwoAV5UYA7wfsIgM88WqBKC7Hfw2Ly+IoIXjm1aU81TWVwG28ol3Fy5vnQjG7HpLOfVT4gtUe7lnrgDg8XscJt8T852OeMpu79e602vXhqez9jFd0NpTTHcc/w1a2ddLxtpLZkbfDCBA9Mzyg00xlBejpdXP6hTVpXGZ39O5oDe6FNIG+RPoMBR20tOm+4n2bwFWrMXh/OcIRXZXR23CTdTVLnQFivNJ9YEDW37le9lI4voJ2nm4Iqzk9SWU3kCEnA2LsuaXQ2xc6L4zDFs1BhT/RvbbdHZ0ACdHJK+dGZMxbcFaSgOYhg5A8bNNKCW7HsrbK5MNibnYJZYWlNayYFrHuxzqo2xPYJzFjsjImjmntWqdr9Y2LikILSMVVrHeL+g0hPGU7rCbsWQdzulWTpd1GGXYvHQFwWWMPZQ1gmaUL0NpOKyXBx2oW9G4ySdBm5LtY89uIF651gYE4DulPOpvB7y5gqgaDS61RpGOnZGu6nzQ+CYPkIbR7VCr7wvDzvyTDGHr9mCMeD8WCNT7g+Lg4t3RR4rCzjfsBwq8805Gh+1KA5pHnKpkGYpBDni4UzFW1Nf/sXR7EJ3kPIL7lsvg/msnnQSySKK/0daNUblZvipYpeIYzOjlgpCdNjKbhHbBDQk9bNOidHRZF21/WtPkrbPrwVObkajSVkhUTwddVemjQSZCOjkhuRTCWjh6AGoyN0XjLTLsLaKPqy+gBiLlIBBiKntQlzysPmRIU4dBKkuHBHwaLHO5wBzc0SElx1/k1ReXI/vsr3eLxGDtMPrBirFXMpJMMQKsdF/H0oDfs4yrK+GPgjBKQqA4aScBZMhUsrtuYKzgjcUiwm+eqiYgJllAHAKDDQYz4O2RU0iYG75fa7A6WmgJDqLTp7R+UwWcWvOSZKCIvV+/YUDTxAXHzt+72q8KgTYyEeYFK5LHsAtCPteu+ECrAh3M6XY44pz1ltZ5P7lNdqhrVF48NA9QFxUzDQC9trkYKzUCwVxdhQlOciK4l+dpPfJiKBZkaE1nKDfQNTOo37zvfDL+MkekNEw/nF1EzKHc/Z861f5ICgI/ZbasmBDiCzUWNsqJ2BbovU+mb+K0eEFIGQseg+dVThxAC3evjTy3KS+4GbSy6HpNXX5an2gyYEgs2GGALPEeY6C3NUPHQe4veAnfTQ87GQKxOeuez9G6lEBL0aPlyrD+D0YgTSd9s3NnYfKaNSVZET/2AzZAct0Lq45aE4MVOT+kEu0Umhoo0sUQYo5zj534agRrDTLjJrDYCbZ9AmcjU+KS4a9ibpqVcxM79D2zf5vA6u0STggrxGFoXZ9iA3+ZNA44Lq6HfaitHAVikidoVaEMBYIBh30YOrVlDiPMCEV4t5pqT+hWjkdIS6SBRwjapZKcYzX0WKR+8kZVHvTrHqbm8KB6BLBwO7rQkAMC57Z09/LE4EsbEwu4BkOYOsJIgzA0VcMKiVztT/CNjITnS+V5EmCDnh/7bKMeOooo78+zSDs54qsxTl18F4lhrrPFiUT5VFK4R6fW24BxuBZVg3irFyD0m/27Q8/2lM8i0kHWk9Eb2XlqRRepSEzHOn1c4Wkojudz2w30o6fMqnvdZwHuevQJO0Vj/FcKkGU8z07E4kjFmme5LFM7oxdxlsEt4w6eLhINN3Zy5/rHYbDc/JfCtJ/qo5vVD93Lk8PUzdAdx+c5PFbtywb4sAVZtuuyN2VwbABCrKSgOTs9wgaYyNvu1SjtQ5AR8N7XYj3ITMx5lLAXC+usnZuRwTYwij6ScTHoGMLZOkafz3mKLD7E5RBJFfxgahx38AncS92oYKMNQ9LeL3yXM4QpkDXXqCIQWQd21o0JQ4dOcHh9bGF5ePoJ38RFHBnCdphCM46UrgGci9FJGY9k2dxMh2kSEhDRyhIRz3RPezB8WUTIkRBU53mwuo2EPC+0MwAmI7+MsXBQCL8iOvXCOEIUqOSa8j3Cy60d/1iCmAVa3zVR2z98dHsOdUFLwiJXf6im4zqKoSDhI7QvfxiCvl3vpEhasOC6Eztn67jniMUGJy/ZAzDYdrrKQzHJopMO1JUtqZnIcYLMvOxN6lAvlhAWnMEpJDDs2GuoLGdRevQ7oKJpzOo3Cd2ebbNHUwrrBwnO1+RgTi8QNxRThJOVrSDM4OFNxoFSbfuaExihMWD8U31dk/T6eQ0121PMQxMOS1VzU9E7x0s04M0mXOig98YcAz5UG7nj6swL/OLgI9eQaW7KBtbRaq2jF/FOLuU2cho3hdRmoHhwtRHOy3s2pS7Mu9BqgByUxFaqt/cdo6NNHoh8mpJXTsEHT0/eJL5/QbOn0qBhyrYw41wA23iCmIlZKBApLH5GFL+yItQjWQSo7ZoBTF0XLfxLZ34kdqRamkiJu+T632KMTZbGoT4UvO3bOW0sc+8oc6BxD0e4DAt81CS9JXU6YpAeWuC2m2RiRoi6qBuDR4Xp4jk5YzMa1PeOGnkZpyr6Q69tIVicWjOHQLuqa0k48irg1TP1DeMYMf4TdkAUblqtGaEXER2S15Cm2wd2cdayEgq7Dhh7l7m8Hp+zzo/S+aQsg7Q67A+6jIqSuB5fCDFNc+LQVheyFxuS0RUyuM9pAfU9fWL5ImfXsWYMSqI0ctFrTAxkalQlOsBxHSwuS5fAi0xfCMvUtMqlaTjunYUZeslcrpxwqXRgJNPrXgghpP2ijI2kTLChLM0/Dl29coYn9GddWRrAIDbuiXoH+tzn0j5w/uHJHOH+uFyoZqKnAYvCbeNZ/R1ySs81Tv2U3/O9OZHoT0Ms8JK7fI4klD69d+Hi+kanz/8liR80Cp1SBNB/WCWS7WZzv+ObN8CSj2a1IhPknh0SFDkjJAxKELTg4iH8dqMP/so+HO3i9oD4Xmvj+GW7NNkxIgZek4cma6Gw8BSg2LTv6ZLCf2gWZJJ1IdYNHqSKbaTPceAY9dZ1ODSFVWAHYb6/wsGamnP1jICKLd8EZ3wfWRl8O0JU794opteKudEIE4eo0F+jAS47yyzYUQ7IDvW+Rq04RvV/RmVajQYC/T6qyu/hOeXhL0oOOlmtj8UxlTcy+XVZgqXsHGCXnsgpkhplPS4+IJZNjEKr6JqoXRJXS3h6g184UAsj0/9DkOxiekjZtAJzUT22MBFh5MZlKRMViGqMAZfI95mrqby0XKi7fHtM2/coa5pf08PRdDc7xbb/D2ge5nIDt8joV5LYb1hM0bm9YR7xmUPwgfqpJLk3Y1dWcwVWVRq7Pb30OEfB6vgRpAgVxUXo5wnGivTH07BYlZGoLvE4+ReNmSFxakTE2TMjAhhnJgJ2otnBkhj8TGTWtgANqFLTCF8dsxWJalsBh8omyK96WKBdYppiHkXLpJrlSS6dEick9RiqCeBHteWI3SzNT7nhh0/445fROusui3iKq/HEgrlt1zcYjE0NWFdrNRt0QK0207au5p1LlNOTY4TvqWVjxucu3Onf9TXxZEQoSK/sibDcdnWjLzhPbyYffq9Wa7JMH5ktblabSxN4ev9rUkZPpenM07vdJn6pK5r8p7TPkUHV6IiMyeUqiI0dtqEF6P0WQuuS1ltWtQ1wxOgvWM2YWe1SVUq6BZqUOrSueylyj91EOEilwLbP0CVMq35O/29+GZM58SQAXLYcFfQFaCp6ffh6X81veIsruxER99UT/iiJsxw7dG99WCx5imRNuQRdCkIkIrqYQEr6JkfkBzwkqHhUflNPBWJjF5jq3mmzbVVmF+AEDDVl7cJuuTXud85kblBvQIqpUBAO0zuuSRLAf3S+biitRG/UIXaDWYTKjrSbj15XqOCre4D8gd9VVc1Atx8AqHxSxQMpwiI59ALDLoGRjIGR1KCo68IhpDmR6xbK+lQ0AsP98PFQ0IgPiWGaj/6JMizKeM87Gkkx2tYf/uRwLmW4VehSS+LxW4DxlRmZ/prVdXlwzeE+bf55DSI4JTt4CmxpyZupZb52YAeneDZHhQTkLJrl7zX2h5Z6pulQR2ptQJVXYP9Q1FlSHzBOxu4QvszEp6XzLBBZOAafSMcXnda6KRfJ5582LT7cs3nxSnoHStNk7PsVZw2Q+b1fr9aJSPyPQXbG5IrCaG+G0D5iOyDWLuDb7qRZyGsDSy8PlAbfyWhyj1cECQJwn95T9Xueoq3psiDOBJ2uukZUU+yM/G5I+ZWc+ZWjlRYA9mk3wKebMN+UmwEINJeAIPfR1gAUy/pq9CNseeVPXAPmmNYCQwzjrjeRwn5IBPkaM4ACJoGppTEnca7Ead0Zk9Zip93jsQjPBJhTuHwGm8avEGPc3PTXGdJJqy6MWQ3wItAfj3krPTloqeXNzMjHkE3hiXmj8mF+0VNZshCPl9sI8PpuHmWhfhA7HTXq+zAGpETam2dE91LtKPx/4V5U5sJbOW1ThHGRJkGN6rUZWsS1iEIEJxH5MS5PhRxQWOFIQssWiy6Ny8URB3/uwbfg2pOReV3hddyP7MKl6AtOlWc5WZGnLUkTSzI1FncVbzeDPpjrerv+WZhTwTq/C8bFxp27UfvoFosWEgPXLk9XKui3Scqhfy5/BpbDXDOduYRPr5nx2ZeAxdwTXQY/SAdJbUZ/QaFirZ37cnfL2I/ALCHeM1YluVexDrgRf3IM5duaYTx7JD3zXVpMKbq3mPbS+6pnrVU1OhDU5jvqg388DUL1z6hlyRPo2No4irPaT0FZZY9mCJkzjcUoYS8NNEYFpe3Xpk8B74rQPh37jgQycN2NOz4Bq9gHT10V26A7Uj8MAGR/iEx/F/or+W0UOV0YDeG6+59zO9kicXNldpHDjYJtIve10fq0nYjmOKyRtcBiniJlYzfAT+6nNI91iF4+Zrsovez/rGmTtu3uimV3CQAc2BAx76KkYo5baYHTrdptBOsMfHrtU8YHr676oNmaYq8nxKJ4MDfAzw5ZeIUoP2Q7dXDrKqxdvYrj7aE5Bign8JdMySCKv/ZHQZJ0KEAMEYE4ro8CQxjjfvvzh7Z1h7sFrA/Zuchc5Wg9ckyU+Bh9KUZngkaSu/3CnMrvfmMUNFZjsQEYMoHxbFsvogebU3Xo7X30+peSR5aI2cB5Ghq0Y/slJoMyRw6Dpu1R/oRSTh44NWIdWQsNqR+P36R0yvBS5928YknOxVaHId4xJOH98MNbrS3e2ceUbqbJ7K42Qr39RGdPz1iTsIit2tv28wJ/waJYPhm+PuWH+nWdgHzMPzoE/KeLshGtSZBuV8CSTwkRgrdaNxxAJ44LqDKR2Z0B9pOs93f+cQhwW2OJH7EsI2tD6+lVkgIrr563/fnUHavVDI+XDfGzDqFQITToUCwZJrM40mQ2w3MTArZrSRNamz3lH848V2BIblOdHzJ7yB4+KpTGFne6/bt4buEkdyqXxXMJLksdGpYEo/Ks4RRKiuSbAWGwtF7tsVSSOFSiKtujDPRVNevtWW6AFSdsXRzI
*/