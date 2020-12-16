// Copyright 2004-5 The Trustees of Indiana University.
// Copyright 2002 Brad King and Douglas Gregor

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_PAGE_RANK_HPP
#define BOOST_GRAPH_PAGE_RANK_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <vector>

namespace boost
{
namespace graph
{

    struct n_iterations
    {
        explicit n_iterations(std::size_t n) : n(n) {}

        template < typename RankMap, typename Graph >
        bool operator()(const RankMap&, const Graph&)
        {
            return n-- == 0;
        }

    private:
        std::size_t n;
    };

    namespace detail
    {
        template < typename Graph, typename RankMap, typename RankMap2 >
        void page_rank_step(const Graph& g, RankMap from_rank, RankMap2 to_rank,
            typename property_traits< RankMap >::value_type damping,
            incidence_graph_tag)
        {
            typedef typename property_traits< RankMap >::value_type rank_type;

            // Set new rank maps
            BGL_FORALL_VERTICES_T(v, g, Graph)
            put(to_rank, v, rank_type(1 - damping));

            BGL_FORALL_VERTICES_T(u, g, Graph)
            {
                rank_type u_rank_out
                    = damping * get(from_rank, u) / out_degree(u, g);
                BGL_FORALL_ADJ_T(u, v, g, Graph)
                put(to_rank, v, get(to_rank, v) + u_rank_out);
            }
        }

        template < typename Graph, typename RankMap, typename RankMap2 >
        void page_rank_step(const Graph& g, RankMap from_rank, RankMap2 to_rank,
            typename property_traits< RankMap >::value_type damping,
            bidirectional_graph_tag)
        {
            typedef
                typename property_traits< RankMap >::value_type damping_type;
            BGL_FORALL_VERTICES_T(v, g, Graph)
            {
                typename property_traits< RankMap >::value_type rank(0);
                BGL_FORALL_INEDGES_T(v, e, g, Graph)
                rank += get(from_rank, source(e, g))
                    / out_degree(source(e, g), g);
                put(to_rank, v, (damping_type(1) - damping) + damping * rank);
            }
        }
    } // end namespace detail

    template < typename Graph, typename RankMap, typename Done,
        typename RankMap2 >
    void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping,
        typename graph_traits< Graph >::vertices_size_type n,
        RankMap2 rank_map2 BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
            Graph, vertex_list_graph_tag))
    {
        typedef typename property_traits< RankMap >::value_type rank_type;

        rank_type initial_rank = rank_type(rank_type(1) / n);
        BGL_FORALL_VERTICES_T(v, g, Graph) put(rank_map, v, initial_rank);

        bool to_map_2 = true;
        while ((to_map_2 && !done(rank_map, g))
            || (!to_map_2 && !done(rank_map2, g)))
        {
            typedef typename graph_traits< Graph >::traversal_category category;

            if (to_map_2)
            {
                detail::page_rank_step(
                    g, rank_map, rank_map2, damping, category());
            }
            else
            {
                detail::page_rank_step(
                    g, rank_map2, rank_map, damping, category());
            }
            to_map_2 = !to_map_2;
        }

        if (!to_map_2)
        {
            BGL_FORALL_VERTICES_T(v, g, Graph)
            put(rank_map, v, get(rank_map2, v));
        }
    }

    template < typename Graph, typename RankMap, typename Done >
    void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping,
        typename graph_traits< Graph >::vertices_size_type n)
    {
        typedef typename property_traits< RankMap >::value_type rank_type;

        std::vector< rank_type > ranks2(num_vertices(g));
        page_rank(g, rank_map, done, damping, n,
            make_iterator_property_map(ranks2.begin(), get(vertex_index, g)));
    }

    template < typename Graph, typename RankMap, typename Done >
    inline void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping = 0.85)
    {
        page_rank(g, rank_map, done, damping, num_vertices(g));
    }

    template < typename Graph, typename RankMap >
    inline void page_rank(const Graph& g, RankMap rank_map)
    {
        page_rank(g, rank_map, n_iterations(20));
    }

    // TBD: this could be _much_ more efficient, using a queue to store
    // the vertices that should be reprocessed and keeping track of which
    // vertices are in the queue with a property map. Baah, this only
    // applies when we have a bidirectional graph.
    template < typename MutableGraph >
    void remove_dangling_links(
        MutableGraph& g BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
            MutableGraph, vertex_list_graph_tag))
    {
        typename graph_traits< MutableGraph >::vertices_size_type old_n;
        do
        {
            old_n = num_vertices(g);

            typename graph_traits< MutableGraph >::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end;
                /* in loop */)
            {
                typename graph_traits< MutableGraph >::vertex_descriptor v
                    = *vi++;
                if (out_degree(v, g) == 0)
                {
                    clear_vertex(v, g);
                    remove_vertex(v, g);
                }
            }
        } while (num_vertices(g) < old_n);
    }

}
} // end namespace boost::graph

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / page_rank.hpp >)

#endif // BOOST_GRAPH_PAGE_RANK_HPP

/* page_rank.hpp
66lwm+r6vNzGldc/eRxzL4rzeTTL25hbA90L4nwefdJ4naycw8fcRw8rYy5utPBHhGqilUf8v/aPNdhohg82YqWC1z9s9ZPXqOsUXtu68Bre1pnTUx7b6spSta0+do/btrqio99tdauBh4d84OGdUtW2j6V7a6u3QPcIgmLbx2qMbdVRJjh9fJGfnH6TpnCa7PpOoJ3GZ3OLx/dfZSqfTywy3FMSnctX+t+uXjDw+a4PfCaVq+swnmhF6zCiEz3yeQJ1TixX+XxitZHPbeWCzyf7+snnH/sofDZ3nSdor3CZafHU38+Ic9j/Mfp6gLmZfAoxbvt7NXRPi3N4pofxOWRchfYc8mxT3XOI3Rbly3lsozX26Sxejos18vsbLZbS2QemRHYmHnXX3dOd4MczP/OQGF+wGIe3gqUHeSvwuQ20zTCs8cjw2AbEOWfM1c75uaX+P3v9NNgsn6nXc05V+/Bcte0/FyLavu5W9sY1/rf90YbzLsjw3vYT56nt5tl9aDd4nmru8XnqOOrcAPpKu3munrHdlM8THNoOsD5B5kjBolcODwFX0L6yhUzP08+8THudA6z3UvROk7m5M1PLpvjbPvYNd+bpueHe24cDGypekesRhnrEmKNlpnrLTLVy9VkSgzwM+hkIClfIs4kxl7n1+Xq++hXaQv3j6/Qw2l/EnOa/F2h89f3UHV9Lk/zl6y8Gvv7mA1+VCzS++s7zzlcK9BcjqHz1/d6Vr3cW6PkaeLO/7cs60rV9TVqo8TWQuW1fR/zla9tYw9resd75qlmo8TVgo3e+sqG/D0Hla2AdV74si/R8pX/mb/uaOtq1fd2ySOMrPcdt+9rsL18vGvg66gNfJxdpfA36zjtfVdA/gaDylV7uylfHxXq+Mp/wt311oj1GRU587V+s8ZXZSuHLMFO57BQnzFe+3pvszNfZyd75ilii8ZXxvDnSG18HFkN3icZXZg9XvvKWCL7CD7Bh9/jLV+JE1/Z1donG17B4PV/JooG95idfjxr4etkHvtKu1/ga+pD39nUO9e5xvcbXsGtc+dp4vXaPcYCNbmYL94+ve7PlepZQub3U59YblDJRSthysz0Q1u2FXTx1bprirm/eaPW3b5bkOHN3U4537hbfoHE3qov3ttYG+vMRVO5GPapxF2IBLyDmnkicP8IOhBF1FHwtipDCG9z/CALF/xZFf/M8mk+St3lIguwsdBLqiCDS3kRZf0Z4Wy4PersQ7kN4CeEI5G/Jafx42xD+EkPoFObwY76DtOcQ/ojwrK6O78Zo4aguHNOF4wjvIbyP8AHCCYQPEQ4hHHSDHyFcVxfnq5N9rP79L8STCJ/o4qf4eX9K8dr/Pq37+6+6v/+m+/sz3d9n+N+j6whfbJC7hgMxIp38t33Ofbhl1VHq+TLCkUhKF/Uej7QHgYiLcqoQNJ/aIo10JwC/QHyNmzxrXfMI/S8RziIMQhnr3ehtBLrLg4A8SkhC+ErkNaL4fptAQ7oo/2tgdh2BFP7O/z7H8TzHbzh+y/GCU97LH+LZSPqG/wCEoACnb/iT/0/se6FfEO05jIO+LINQ+KIZGGBnF6zmgBQqa4S+rLIcUZi+rC60p7Iei9GV5SBZP2ZmSjnv1FPL0ZfiXKfvIslPqVM5EVHO5ThEfUo9lpND5YQ7lVMS6VzOMFGO7BbAmaPRvBwpgvypWmJIpufoVEA4WxQQg3LKmVIOCyjHh4kU//ff8+tCaLys+3h6AEuReklxbJLURqoyxbGHTMnSSfPtbIklWXrYOoD9ZL1GSgmMgxeAZKkS153tQcnSkeA49nVwspRoi2O9bMlSiT2O3WpPlg6ExrGPQpOliPA41jY8Wco=
*/