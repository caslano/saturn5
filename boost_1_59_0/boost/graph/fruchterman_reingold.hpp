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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/fruchterman_reingold.hpp>)

#endif // BOOST_GRAPH_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT_HPP

/* fruchterman_reingold.hpp
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
*/