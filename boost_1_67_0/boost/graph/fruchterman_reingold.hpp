// Copyright 2004, 2005 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT_HPP
#define BOOST_GRAPH_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/topology.hpp> // For topology concepts
#include <boost/graph/detail/mpi_include.hpp>
#include <vector>
#include <list>
#include <algorithm> // for std::min and std::max
#include <numeric> // for std::accumulate
#include <cmath> // for std::sqrt and std::fabs
#include <functional>

namespace boost
{

struct square_distance_attractive_force
{
    template < typename Graph, typename T >
    T operator()(typename graph_traits< Graph >::edge_descriptor, T k, T d,
        const Graph&) const
    {
        return d * d / k;
    }
};

struct square_distance_repulsive_force
{
    template < typename Graph, typename T >
    T operator()(typename graph_traits< Graph >::vertex_descriptor,
        typename graph_traits< Graph >::vertex_descriptor, T k, T d,
        const Graph&) const
    {
        return k * k / d;
    }
};

template < typename T > struct linear_cooling
{
    typedef T result_type;

    linear_cooling(std::size_t iterations)
    : temp(T(iterations) / T(10)), step(0.1)
    {
    }

    linear_cooling(std::size_t iterations, T temp)
    : temp(temp), step(temp / T(iterations))
    {
    }

    T operator()()
    {
        T old_temp = temp;
        temp -= step;
        if (temp < T(0))
            temp = T(0);
        return old_temp;
    }

private:
    T temp;
    T step;
};

struct all_force_pairs
{
    template < typename Graph, typename ApplyForce >
    void operator()(const Graph& g, ApplyForce apply_force)
    {
        typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
        vertex_iterator v, end;
        for (boost::tie(v, end) = vertices(g); v != end; ++v)
        {
            vertex_iterator u = v;
            for (++u; u != end; ++u)
            {
                apply_force(*u, *v);
                apply_force(*v, *u);
            }
        }
    }
};

template < typename Topology, typename PositionMap > struct grid_force_pairs
{
    typedef typename property_traits< PositionMap >::value_type Point;
    BOOST_STATIC_ASSERT(Point::dimensions == 2);
    typedef typename Topology::point_difference_type point_difference_type;

    template < typename Graph >
    explicit grid_force_pairs(
        const Topology& topology, PositionMap position, const Graph& g)
    : topology(topology), position(position)
    {
        two_k = 2. * this->topology.volume(this->topology.extent())
            / std::sqrt((double)num_vertices(g));
    }

    template < typename Graph, typename ApplyForce >
    void operator()(const Graph& g, ApplyForce apply_force)
    {
        typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
        typedef std::list< vertex_descriptor > bucket_t;
        typedef std::vector< bucket_t > buckets_t;

        std::size_t columns = std::size_t(topology.extent()[0] / two_k + 1.);
        std::size_t rows = std::size_t(topology.extent()[1] / two_k + 1.);
        buckets_t buckets(rows * columns);
        vertex_iterator v, v_end;
        for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
        {
            std::size_t column = std::size_t(
                (get(position, *v)[0] + topology.extent()[0] / 2) / two_k);
            std::size_t row = std::size_t(
                (get(position, *v)[1] + topology.extent()[1] / 2) / two_k);

            if (column >= columns)
                column = columns - 1;
            if (row >= rows)
                row = rows - 1;
            buckets[row * columns + column].push_back(*v);
        }

        for (std::size_t row = 0; row < rows; ++row)
            for (std::size_t column = 0; column < columns; ++column)
            {
                bucket_t& bucket = buckets[row * columns + column];
                typedef typename bucket_t::iterator bucket_iterator;
                for (bucket_iterator u = bucket.begin(); u != bucket.end(); ++u)
                {
                    // Repulse vertices in this bucket
                    bucket_iterator v = u;
                    for (++v; v != bucket.end(); ++v)
                    {
                        apply_force(*u, *v);
                        apply_force(*v, *u);
                    }

                    std::size_t adj_start_row = row == 0 ? 0 : row - 1;
                    std::size_t adj_end_row = row == rows - 1 ? row : row + 1;
                    std::size_t adj_start_column = column == 0 ? 0 : column - 1;
                    std::size_t adj_end_column
                        = column == columns - 1 ? column : column + 1;
                    for (std::size_t other_row = adj_start_row;
                         other_row <= adj_end_row; ++other_row)
                        for (std::size_t other_column = adj_start_column;
                             other_column <= adj_end_column; ++other_column)
                            if (other_row != row || other_column != column)
                            {
                                // Repulse vertices in this bucket
                                bucket_t& other_bucket
                                    = buckets[other_row * columns
                                        + other_column];
                                for (v = other_bucket.begin();
                                     v != other_bucket.end(); ++v)
                                {
                                    double dist = topology.distance(
                                        get(position, *u), get(position, *v));
                                    if (dist < two_k)
                                        apply_force(*u, *v);
                                }
                            }
                }
            }
    }

private:
    const Topology& topology;
    PositionMap position;
    double two_k;
};

template < typename PositionMap, typename Topology, typename Graph >
inline grid_force_pairs< Topology, PositionMap > make_grid_force_pairs(
    const Topology& topology, const PositionMap& position, const Graph& g)
{
    return grid_force_pairs< Topology, PositionMap >(topology, position, g);
}

template < typename Graph, typename PositionMap, typename Topology >
void scale_graph(const Graph& g, PositionMap position, const Topology& topology,
    typename Topology::point_type upper_left,
    typename Topology::point_type lower_right)
{
    if (num_vertices(g) == 0)
        return;

    typedef typename Topology::point_type Point;
    typedef typename Topology::point_difference_type point_difference_type;

    // Find min/max ranges
    Point min_point = get(position, *vertices(g).first), max_point = min_point;
    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        min_point = topology.pointwise_min(min_point, get(position, v));
        max_point = topology.pointwise_max(max_point, get(position, v));
    }

    Point old_origin = topology.move_position_toward(min_point, 0.5, max_point);
    Point new_origin
        = topology.move_position_toward(upper_left, 0.5, lower_right);
    point_difference_type old_size = topology.difference(max_point, min_point);
    point_difference_type new_size
        = topology.difference(lower_right, upper_left);

    // Scale to bounding box provided
    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        point_difference_type relative_loc
            = topology.difference(get(position, v), old_origin);
        relative_loc = (relative_loc / old_size) * new_size;
        put(position, v, topology.adjust(new_origin, relative_loc));
    }
}

namespace detail
{
    template < typename Topology, typename PropMap, typename Vertex >
    void maybe_jitter_point(const Topology& topology, const PropMap& pm,
        Vertex v, const typename Topology::point_type& p2)
    {
        double too_close = topology.norm(topology.extent()) / 10000.;
        if (topology.distance(get(pm, v), p2) < too_close)
        {
            put(pm, v,
                topology.move_position_toward(
                    get(pm, v), 1. / 200, topology.random_point()));
        }
    }

    template < typename Topology, typename PositionMap,
        typename DisplacementMap, typename RepulsiveForce, typename Graph >
    struct fr_apply_force
    {
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
        typedef typename Topology::point_type Point;
        typedef typename Topology::point_difference_type PointDiff;

        fr_apply_force(const Topology& topology, const PositionMap& position,
            const DisplacementMap& displacement, RepulsiveForce repulsive_force,
            double k, const Graph& g)
        : topology(topology)
        , position(position)
        , displacement(displacement)
        , repulsive_force(repulsive_force)
        , k(k)
        , g(g)
        {
        }

        void operator()(vertex_descriptor u, vertex_descriptor v)
        {
            if (u != v)
            {
                // When the vertices land on top of each other, move the
                // first vertex away from the boundaries.
                maybe_jitter_point(topology, position, u, get(position, v));

                double dist
                    = topology.distance(get(position, u), get(position, v));
                typename Topology::point_difference_type dispv
                    = get(displacement, v);
                if (dist == 0.)
                {
                    for (std::size_t i = 0; i < Point::dimensions; ++i)
                    {
                        dispv[i] += 0.01;
                    }
                }
                else
                {
                    double fr = repulsive_force(u, v, k, dist, g);
                    dispv += (fr / dist)
                        * topology.difference(
                            get(position, v), get(position, u));
                }
                put(displacement, v, dispv);
            }
        }

    private:
        const Topology& topology;
        PositionMap position;
        DisplacementMap displacement;
        RepulsiveForce repulsive_force;
        double k;
        const Graph& g;
    };

} // end namespace detail

template < typename Topology, typename Graph, typename PositionMap,
    typename AttractiveForce, typename RepulsiveForce, typename ForcePairs,
    typename Cooling, typename DisplacementMap >
void fruchterman_reingold_force_directed_layout(const Graph& g,
    PositionMap position, const Topology& topology,
    AttractiveForce attractive_force, RepulsiveForce repulsive_force,
    ForcePairs force_pairs, Cooling cool, DisplacementMap displacement)
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator;

    double volume = topology.volume(topology.extent());

    // assume positions are initialized randomly
    double k = pow(volume / num_vertices(g),
        1. / (double)(Topology::point_difference_type::dimensions));

    detail::fr_apply_force< Topology, PositionMap, DisplacementMap,
        RepulsiveForce, Graph >
        apply_force(topology, position, displacement, repulsive_force, k, g);

    do
    {
        // Calculate repulsive forces
        vertex_iterator v, v_end;
        for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
            put(displacement, *v, typename Topology::point_difference_type());
        force_pairs(g, apply_force);

        // Calculate attractive forces
        edge_iterator e, e_end;
        for (boost::tie(e, e_end) = edges(g); e != e_end; ++e)
        {
            vertex_descriptor v = source(*e, g);
            vertex_descriptor u = target(*e, g);

            // When the vertices land on top of each other, move the
            // first vertex away from the boundaries.
            ::boost::detail::maybe_jitter_point(
                topology, position, u, get(position, v));

            typename Topology::point_difference_type delta
                = topology.difference(get(position, v), get(position, u));
            double dist = topology.distance(get(position, u), get(position, v));
            double fa = attractive_force(*e, k, dist, g);

            put(displacement, v, get(displacement, v) - (fa / dist) * delta);
            put(displacement, u, get(displacement, u) + (fa / dist) * delta);
        }

        if (double temp = cool())
        {
            // Update positions
            BGL_FORALL_VERTICES_T(v, g, Graph)
            {
                BOOST_USING_STD_MIN();
                BOOST_USING_STD_MAX();
                double disp_size = topology.norm(get(displacement, v));
                put(position, v,
                    topology.adjust(get(position, v),
                        get(displacement, v)
                            * (min BOOST_PREVENT_MACRO_SUBSTITUTION(
                                   disp_size, temp)
                                / disp_size)));
                put(position, v, topology.bound(get(position, v)));
            }
        }
        else
        {
            break;
        }
    } while (true);
}

namespace detail
{
    template < typename DisplacementMap > struct fr_force_directed_layout
    {
        template < typename Topology, typename Graph, typename PositionMap,
            typename AttractiveForce, typename RepulsiveForce,
            typename ForcePairs, typename Cooling, typename Param, typename Tag,
            typename Rest >
        static void run(const Graph& g, PositionMap position,
            const Topology& topology, AttractiveForce attractive_force,
            RepulsiveForce repulsive_force, ForcePairs force_pairs,
            Cooling cool, DisplacementMap displacement,
            const bgl_named_params< Param, Tag, Rest >&)
        {
            fruchterman_reingold_force_directed_layout(g, position, topology,
                attractive_force, repulsive_force, force_pairs, cool,
                displacement);
        }
    };

    template <> struct fr_force_directed_layout< param_not_found >
    {
        template < typename Topology, typename Graph, typename PositionMap,
            typename AttractiveForce, typename RepulsiveForce,
            typename ForcePairs, typename Cooling, typename Param, typename Tag,
            typename Rest >
        static void run(const Graph& g, PositionMap position,
            const Topology& topology, AttractiveForce attractive_force,
            RepulsiveForce repulsive_force, ForcePairs force_pairs,
            Cooling cool, param_not_found,
            const bgl_named_params< Param, Tag, Rest >& params)
        {
            typedef typename Topology::point_difference_type PointDiff;
            std::vector< PointDiff > displacements(num_vertices(g));
            fruchterman_reingold_force_directed_layout(g, position, topology,
                attractive_force, repulsive_force, force_pairs, cool,
                make_iterator_property_map(displacements.begin(),
                    choose_const_pmap(
                        get_param(params, vertex_index), g, vertex_index),
                    PointDiff()));
        }
    };

} // end namespace detail

template < typename Topology, typename Graph, typename PositionMap,
    typename Param, typename Tag, typename Rest >
void fruchterman_reingold_force_directed_layout(const Graph& g,
    PositionMap position, const Topology& topology,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    typedef typename get_param_type< vertex_displacement_t,
        bgl_named_params< Param, Tag, Rest > >::type D;

    detail::fr_force_directed_layout< D >::run(g, position, topology,
        choose_param(get_param(params, attractive_force_t()),
            square_distance_attractive_force()),
        choose_param(get_param(params, repulsive_force_t()),
            square_distance_repulsive_force()),
        choose_param(get_param(params, force_pairs_t()),
            make_grid_force_pairs(topology, position, g)),
        choose_param(
            get_param(params, cooling_t()), linear_cooling< double >(100)),
        get_param(params, vertex_displacement_t()), params);
}

template < typename Topology, typename Graph, typename PositionMap >
void fruchterman_reingold_force_directed_layout(
    const Graph& g, PositionMap position, const Topology& topology)
{
    fruchterman_reingold_force_directed_layout(g, position, topology,
        attractive_force(square_distance_attractive_force()));
}

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / fruchterman_reingold.hpp >)

#endif // BOOST_GRAPH_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT_HPP

/* fruchterman_reingold.hpp
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
*/