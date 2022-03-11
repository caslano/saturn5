// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_KAMADA_KAWAI_SPRING_LAYOUT_HPP
#define BOOST_GRAPH_KAMADA_KAWAI_SPRING_LAYOUT_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/topology.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <utility>
#include <iterator>
#include <vector>
#include <iostream>
#include <boost/limits.hpp>
#include <boost/config/no_tr1/cmath.hpp>

namespace boost
{
namespace detail
{
    namespace graph
    {
        /**
         * Denotes an edge or display area side length used to scale a
         * Kamada-Kawai drawing.
         */
        template < bool Edge, typename T > struct edge_or_side
        {
            explicit edge_or_side(T value) : value(value) {}

            T value;
        };

        /**
         * Compute the edge length from an edge length. This is trivial.
         */
        template < typename Graph, typename DistanceMap, typename IndexMap,
            typename T >
        T compute_edge_length(
            const Graph&, DistanceMap, IndexMap, edge_or_side< true, T > length)
        {
            return length.value;
        }

        /**
         * Compute the edge length based on the display area side
           length. We do this by dividing the side length by the largest
           shortest distance between any two vertices in the graph.
         */
        template < typename Graph, typename DistanceMap, typename IndexMap,
            typename T >
        T compute_edge_length(const Graph& g, DistanceMap distance,
            IndexMap index, edge_or_side< false, T > length)
        {
            T result(0);

            typedef
                typename graph_traits< Graph >::vertex_iterator vertex_iterator;

            for (vertex_iterator ui = vertices(g).first,
                                 end = vertices(g).second;
                 ui != end; ++ui)
            {
                vertex_iterator vi = ui;
                for (++vi; vi != end; ++vi)
                {
                    T dij = distance[get(index, *ui)][get(index, *vi)];
                    if (dij > result)
                        result = dij;
                }
            }
            return length.value / result;
        }

        /**
         * Dense linear solver for fixed-size matrices.
         */
        template < std::size_t Size > struct linear_solver
        {
            // Indices in mat are (row, column)
            // template <typename Vec>
            // static Vec solve(double mat[Size][Size], Vec rhs);
        };

        template <> struct linear_solver< 1 >
        {
            template < typename Vec >
            static Vec solve(double mat[1][1], Vec rhs)
            {
                return rhs / mat[0][0];
            }
        };

        // These are from http://en.wikipedia.org/wiki/Cramer%27s_rule
        template <> struct linear_solver< 2 >
        {
            template < typename Vec >
            static Vec solve(double mat[2][2], Vec rhs)
            {
                double denom = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
                double x_num = rhs[0] * mat[1][1] - rhs[1] * mat[0][1];
                double y_num = mat[0][0] * rhs[1] - mat[1][0] * rhs[0];
                Vec result;
                result[0] = x_num / denom;
                result[1] = y_num / denom;
                return result;
            }
        };

        template <> struct linear_solver< 3 >
        {
            template < typename Vec >
            static Vec solve(double mat[3][3], Vec rhs)
            {
                double denom = mat[0][0]
                        * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
                    - mat[1][0]
                        * (mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2])
                    + mat[2][0]
                        * (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]);
                double x_num
                    = rhs[0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
                    - rhs[1] * (mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2])
                    + rhs[2] * (mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2]);
                double y_num
                    = mat[0][0] * (rhs[1] * mat[2][2] - rhs[2] * mat[1][2])
                    - mat[1][0] * (rhs[0] * mat[2][2] - rhs[2] * mat[0][2])
                    + mat[2][0] * (rhs[0] * mat[1][2] - rhs[1] * mat[0][2]);
                double z_num
                    = mat[0][0] * (mat[1][1] * rhs[2] - mat[2][1] * rhs[1])
                    - mat[1][0] * (mat[0][1] * rhs[2] - mat[2][1] * rhs[0])
                    + mat[2][0] * (mat[0][1] * rhs[1] - mat[1][1] * rhs[0]);
                Vec result;
                result[0] = x_num / denom;
                result[1] = y_num / denom;
                result[2] = z_num / denom;
                return result;
            }
        };

        /**
         * Implementation of the Kamada-Kawai spring layout algorithm.
         */
        template < typename Topology, typename Graph, typename PositionMap,
            typename WeightMap, typename EdgeOrSideLength, typename Done,
            typename VertexIndexMap, typename DistanceMatrix,
            typename SpringStrengthMatrix, typename PartialDerivativeMap >
        struct kamada_kawai_spring_layout_impl
        {
            typedef
                typename property_traits< WeightMap >::value_type weight_type;
            typedef typename Topology::point_type Point;
            typedef
                typename Topology::point_difference_type point_difference_type;
            typedef point_difference_type deriv_type;
            typedef
                typename graph_traits< Graph >::vertex_iterator vertex_iterator;
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor;

            kamada_kawai_spring_layout_impl(const Topology& topology,
                const Graph& g, PositionMap position, WeightMap weight,
                EdgeOrSideLength edge_or_side_length, Done done,
                weight_type spring_constant, VertexIndexMap index,
                DistanceMatrix distance, SpringStrengthMatrix spring_strength,
                PartialDerivativeMap partial_derivatives)
            : topology(topology)
            , g(g)
            , position(position)
            , weight(weight)
            , edge_or_side_length(edge_or_side_length)
            , done(done)
            , spring_constant(spring_constant)
            , index(index)
            , distance(distance)
            , spring_strength(spring_strength)
            , partial_derivatives(partial_derivatives)
            {
            }

            // Compute contribution of vertex i to the first partial
            // derivatives (dE/dx_m, dE/dy_m) (for vertex m)
            deriv_type compute_partial_derivative(
                vertex_descriptor m, vertex_descriptor i)
            {
#ifndef BOOST_NO_STDC_NAMESPACE
                using std::sqrt;
#endif // BOOST_NO_STDC_NAMESPACE

                deriv_type result;
                if (i != m)
                {
                    point_difference_type diff
                        = topology.difference(position[m], position[i]);
                    weight_type dist = topology.norm(diff);
                    result = spring_strength[get(index, m)][get(index, i)]
                        * (diff
                            - distance[get(index, m)][get(index, i)] / dist
                                * diff);
                }

                return result;
            }

            // Compute partial derivatives dE/dx_m and dE/dy_m
            deriv_type compute_partial_derivatives(vertex_descriptor m)
            {
#ifndef BOOST_NO_STDC_NAMESPACE
                using std::sqrt;
#endif // BOOST_NO_STDC_NAMESPACE

                deriv_type result;

                // TBD: looks like an accumulate to me
                BGL_FORALL_VERTICES_T(i, g, Graph)
                {
                    deriv_type deriv = compute_partial_derivative(m, i);
                    result += deriv;
                }

                return result;
            }

            // The actual Kamada-Kawai spring layout algorithm implementation
            bool run()
            {
#ifndef BOOST_NO_STDC_NAMESPACE
                using std::sqrt;
#endif // BOOST_NO_STDC_NAMESPACE

                // Compute d_{ij} and place it in the distance matrix
                if (!johnson_all_pairs_shortest_paths(
                        g, distance, index, weight, weight_type(0)))
                    return false;

                // Compute L based on side length (if needed), or retrieve L
                weight_type edge_length = detail::graph::compute_edge_length(
                    g, distance, index, edge_or_side_length);

                // std::cerr << "edge_length = " << edge_length << std::endl;

                // Compute l_{ij} and k_{ij}
                const weight_type K = spring_constant;
                vertex_iterator ui, end;
                for (ui = vertices(g).first, end = vertices(g).second;
                     ui != end; ++ui)
                {
                    vertex_iterator vi = ui;
                    for (++vi; vi != end; ++vi)
                    {
                        weight_type dij
                            = distance[get(index, *ui)][get(index, *vi)];
                        if (dij == (std::numeric_limits< weight_type >::max)())
                            return false;
                        distance[get(index, *ui)][get(index, *vi)]
                            = edge_length * dij;
                        distance[get(index, *vi)][get(index, *ui)]
                            = edge_length * dij;
                        spring_strength[get(index, *ui)][get(index, *vi)]
                            = K / (dij * dij);
                        spring_strength[get(index, *vi)][get(index, *ui)]
                            = K / (dij * dij);
                    }
                }

                // Compute Delta_i and find max
                vertex_descriptor p = *vertices(g).first;
                weight_type delta_p(0);

                for (ui = vertices(g).first, end = vertices(g).second;
                     ui != end; ++ui)
                {
                    deriv_type deriv = compute_partial_derivatives(*ui);
                    put(partial_derivatives, *ui, deriv);

                    weight_type delta = topology.norm(deriv);

                    if (delta > delta_p)
                    {
                        p = *ui;
                        delta_p = delta;
                    }
                }

                while (!done(delta_p, p, g, true))
                {
                    // The contribution p makes to the partial derivatives of
                    // each vertex. Computing this (at O(n) cost) allows us to
                    // update the delta_i values in O(n) time instead of O(n^2)
                    // time.
                    std::vector< deriv_type > p_partials(num_vertices(g));
                    for (ui = vertices(g).first, end = vertices(g).second;
                         ui != end; ++ui)
                    {
                        vertex_descriptor i = *ui;
                        p_partials[get(index, i)]
                            = compute_partial_derivative(i, p);
                    }

                    do
                    {
                        // For debugging, compute the energy value E
                        double E = 0.;
                        for (ui = vertices(g).first, end = vertices(g).second;
                             ui != end; ++ui)
                        {
                            vertex_iterator vi = ui;
                            for (++vi; vi != end; ++vi)
                            {
                                double dist = topology.distance(
                                    position[*ui], position[*vi]);
                                weight_type k_ij = spring_strength[get(
                                    index, *ui)][get(index, *vi)];
                                weight_type l_ij = distance[get(index, *ui)]
                                                           [get(index, *vi)];
                                E += .5 * k_ij * (dist - l_ij) * (dist - l_ij);
                            }
                        }
                        // std::cerr << "E = " << E << std::endl;

                        // Compute the elements of the Jacobian
                        // From
                        // http://www.cs.panam.edu/~rfowler/papers/1994_kumar_fowler_A_Spring_UTPACSTR.pdf
                        // with the bugs fixed in the off-diagonal case
                        weight_type dE_d_d[Point::dimensions]
                                          [Point::dimensions];
                        for (std::size_t i = 0; i < Point::dimensions; ++i)
                            for (std::size_t j = 0; j < Point::dimensions; ++j)
                                dE_d_d[i][j] = 0.;
                        for (ui = vertices(g).first, end = vertices(g).second;
                             ui != end; ++ui)
                        {
                            vertex_descriptor i = *ui;
                            if (i != p)
                            {
                                point_difference_type diff
                                    = topology.difference(
                                        position[p], position[i]);
                                weight_type dist = topology.norm(diff);
                                weight_type dist_squared = dist * dist;
                                weight_type inv_dist_cubed
                                    = 1. / (dist_squared * dist);
                                weight_type k_mi = spring_strength[get(
                                    index, p)][get(index, i)];
                                weight_type l_mi
                                    = distance[get(index, p)][get(index, i)];
                                for (std::size_t i = 0; i < Point::dimensions;
                                     ++i)
                                {
                                    for (std::size_t j = 0;
                                         j < Point::dimensions; ++j)
                                    {
                                        if (i == j)
                                        {
                                            dE_d_d[i][i] += k_mi
                                                * (1
                                                    + (l_mi
                                                        * (diff[i] * diff[i]
                                                            - dist_squared)
                                                        * inv_dist_cubed));
                                        }
                                        else
                                        {
                                            dE_d_d[i][j] += k_mi * l_mi
                                                * diff[i] * diff[j]
                                                * inv_dist_cubed;
                                            // dE_d_d[i][j] += k_mi * l_mi *
                                            // sqrt(hypot(diff[i], diff[j])) *
                                            // inv_dist_cubed;
                                        }
                                    }
                                }
                            }
                        }

                        deriv_type dE_d = get(partial_derivatives, p);

                        // Solve dE_d_d * delta = -dE_d to get delta
                        point_difference_type delta
                            = -linear_solver< Point::dimensions >::solve(
                                dE_d_d, dE_d);

                        // Move p by delta
                        position[p] = topology.adjust(position[p], delta);

                        // Recompute partial derivatives and delta_p
                        deriv_type deriv = compute_partial_derivatives(p);
                        put(partial_derivatives, p, deriv);

                        delta_p = topology.norm(deriv);
                    } while (!done(delta_p, p, g, false));

                    // Select new p by updating each partial derivative and
                    // delta
                    vertex_descriptor old_p = p;
                    for (ui = vertices(g).first, end = vertices(g).second;
                         ui != end; ++ui)
                    {
                        deriv_type old_deriv_p = p_partials[get(index, *ui)];
                        deriv_type old_p_partial
                            = compute_partial_derivative(*ui, old_p);
                        deriv_type deriv = get(partial_derivatives, *ui);

                        deriv += old_p_partial - old_deriv_p;

                        put(partial_derivatives, *ui, deriv);
                        weight_type delta = topology.norm(deriv);

                        if (delta > delta_p)
                        {
                            p = *ui;
                            delta_p = delta;
                        }
                    }
                }

                return true;
            }

            const Topology& topology;
            const Graph& g;
            PositionMap position;
            WeightMap weight;
            EdgeOrSideLength edge_or_side_length;
            Done done;
            weight_type spring_constant;
            VertexIndexMap index;
            DistanceMatrix distance;
            SpringStrengthMatrix spring_strength;
            PartialDerivativeMap partial_derivatives;
        };
    }
} // end namespace detail::graph

/// States that the given quantity is an edge length.
template < typename T >
inline detail::graph::edge_or_side< true, T > edge_length(T x)
{
    return detail::graph::edge_or_side< true, T >(x);
}

/// States that the given quantity is a display area side length.
template < typename T >
inline detail::graph::edge_or_side< false, T > side_length(T x)
{
    return detail::graph::edge_or_side< false, T >(x);
}

/**
 * \brief Determines when to terminate layout of a particular graph based
 * on a given relative tolerance.
 */
template < typename T = double > struct layout_tolerance
{
    layout_tolerance(const T& tolerance = T(0.001))
    : tolerance(tolerance)
    , last_energy((std::numeric_limits< T >::max)())
    , last_local_energy((std::numeric_limits< T >::max)())
    {
    }

    template < typename Graph >
    bool operator()(T delta_p,
        typename boost::graph_traits< Graph >::vertex_descriptor p,
        const Graph& g, bool global)
    {
        if (global)
        {
            if (last_energy == (std::numeric_limits< T >::max)())
            {
                last_energy = delta_p;
                return false;
            }

            T diff = last_energy - delta_p;
            if (diff < T(0))
                diff = -diff;
            bool done = (delta_p == T(0) || diff / last_energy < tolerance);
            last_energy = delta_p;
            return done;
        }
        else
        {
            if (last_local_energy == (std::numeric_limits< T >::max)())
            {
                last_local_energy = delta_p;
                return delta_p == T(0);
            }

            T diff = last_local_energy - delta_p;
            bool done
                = (delta_p == T(0) || (diff / last_local_energy) < tolerance);
            last_local_energy = delta_p;
            return done;
        }
    }

private:
    T tolerance;
    T last_energy;
    T last_local_energy;
};

/** \brief Kamada-Kawai spring layout for undirected graphs.
 *
 * This algorithm performs graph layout (in two dimensions) for
 * connected, undirected graphs. It operates by relating the layout
 * of graphs to a dynamic spring system and minimizing the energy
 * within that system. The strength of a spring between two vertices
 * is inversely proportional to the square of the shortest distance
 * (in graph terms) between those two vertices. Essentially,
 * vertices that are closer in the graph-theoretic sense (i.e., by
 * following edges) will have stronger springs and will therefore be
 * placed closer together.
 *
 * Prior to invoking this algorithm, it is recommended that the
 * vertices be placed along the vertices of a regular n-sided
 * polygon.
 *
 * \param g (IN) must be a model of Vertex List Graph, Edge List
 * Graph, and Incidence Graph and must be undirected.
 *
 * \param position (OUT) must be a model of Lvalue Property Map,
 * where the value type is a class containing fields @c x and @c y
 * that will be set to the @c x and @c y coordinates of each vertex.
 *
 * \param weight (IN) must be a model of Readable Property Map,
 * which provides the weight of each edge in the graph @p g.
 *
 * \param topology (IN) must be a topology object (see topology.hpp),
 * which provides operations on points and differences between them.
 *
 * \param edge_or_side_length (IN) provides either the unit length
 * @c e of an edge in the layout or the length of a side @c s of the
 * display area, and must be either @c boost::edge_length(e) or @c
 * boost::side_length(s), respectively.
 *
 * \param done (IN) is a 4-argument function object that is passed
 * the current value of delta_p (i.e., the energy of vertex @p p),
 * the vertex @p p, the graph @p g, and a boolean flag indicating
 * whether @p delta_p is the maximum energy in the system (when @c
 * true) or the energy of the vertex being moved. Defaults to @c
 * layout_tolerance instantiated over the value type of the weight
 * map.
 *
 * \param spring_constant (IN) is the constant multiplied by each
 * spring's strength. Larger values create systems with more energy
 * that can take longer to stabilize; smaller values create systems
 * with less energy that stabilize quickly but do not necessarily
 * result in pleasing layouts. The default value is 1.
 *
 * \param index (IN) is a mapping from vertices to index values
 * between 0 and @c num_vertices(g). The default is @c
 * get(vertex_index,g).
 *
 * \param distance (UTIL/OUT) will be used to store the distance
 * from every vertex to every other vertex, which is computed in the
 * first stages of the algorithm. This value's type must be a model
 * of BasicMatrix with value type equal to the value type of the
 * weight map. The default is a vector of vectors.
 *
 * \param spring_strength (UTIL/OUT) will be used to store the
 * strength of the spring between every pair of vertices. This
 * value's type must be a model of BasicMatrix with value type equal
 * to the value type of the weight map. The default is a vector of
 * vectors.
 *
 * \param partial_derivatives (UTIL) will be used to store the
 * partial derivates of each vertex with respect to the @c x and @c
 * y coordinates. This must be a Read/Write Property Map whose value
 * type is a pair with both types equivalent to the value type of
 * the weight map. The default is an iterator property map.
 *
 * \returns @c true if layout was successful or @c false if a
 * negative weight cycle was detected.
 */
template < typename Topology, typename Graph, typename PositionMap,
    typename WeightMap, typename T, bool EdgeOrSideLength, typename Done,
    typename VertexIndexMap, typename DistanceMatrix,
    typename SpringStrengthMatrix, typename PartialDerivativeMap >
bool kamada_kawai_spring_layout(const Graph& g, PositionMap position,
    WeightMap weight, const Topology& topology,
    detail::graph::edge_or_side< EdgeOrSideLength, T > edge_or_side_length,
    Done done,
    typename property_traits< WeightMap >::value_type spring_constant,
    VertexIndexMap index, DistanceMatrix distance,
    SpringStrengthMatrix spring_strength,
    PartialDerivativeMap partial_derivatives)
{
    BOOST_STATIC_ASSERT(
        (is_convertible< typename graph_traits< Graph >::directed_category*,
            undirected_tag* >::value));

    detail::graph::kamada_kawai_spring_layout_impl< Topology, Graph,
        PositionMap, WeightMap,
        detail::graph::edge_or_side< EdgeOrSideLength, T >, Done,
        VertexIndexMap, DistanceMatrix, SpringStrengthMatrix,
        PartialDerivativeMap >
        alg(topology, g, position, weight, edge_or_side_length, done,
            spring_constant, index, distance, spring_strength,
            partial_derivatives);
    return alg.run();
}

/**
 * \overload
 */
template < typename Topology, typename Graph, typename PositionMap,
    typename WeightMap, typename T, bool EdgeOrSideLength, typename Done,
    typename VertexIndexMap >
bool kamada_kawai_spring_layout(const Graph& g, PositionMap position,
    WeightMap weight, const Topology& topology,
    detail::graph::edge_or_side< EdgeOrSideLength, T > edge_or_side_length,
    Done done,
    typename property_traits< WeightMap >::value_type spring_constant,
    VertexIndexMap index)
{
    typedef typename property_traits< WeightMap >::value_type weight_type;

    typename graph_traits< Graph >::vertices_size_type n = num_vertices(g);
    typedef std::vector< weight_type > weight_vec;

    std::vector< weight_vec > distance(n, weight_vec(n));
    std::vector< weight_vec > spring_strength(n, weight_vec(n));
    std::vector< typename Topology::point_difference_type > partial_derivatives(
        n);

    return kamada_kawai_spring_layout(g, position, weight, topology,
        edge_or_side_length, done, spring_constant, index, distance.begin(),
        spring_strength.begin(),
        make_iterator_property_map(partial_derivatives.begin(), index,
            typename Topology::point_difference_type()));
}

/**
 * \overload
 */
template < typename Topology, typename Graph, typename PositionMap,
    typename WeightMap, typename T, bool EdgeOrSideLength, typename Done >
bool kamada_kawai_spring_layout(const Graph& g, PositionMap position,
    WeightMap weight, const Topology& topology,
    detail::graph::edge_or_side< EdgeOrSideLength, T > edge_or_side_length,
    Done done,
    typename property_traits< WeightMap >::value_type spring_constant)
{
    return kamada_kawai_spring_layout(g, position, weight, topology,
        edge_or_side_length, done, spring_constant, get(vertex_index, g));
}

/**
 * \overload
 */
template < typename Topology, typename Graph, typename PositionMap,
    typename WeightMap, typename T, bool EdgeOrSideLength, typename Done >
bool kamada_kawai_spring_layout(const Graph& g, PositionMap position,
    WeightMap weight, const Topology& topology,
    detail::graph::edge_or_side< EdgeOrSideLength, T > edge_or_side_length,
    Done done)
{
    typedef typename property_traits< WeightMap >::value_type weight_type;
    return kamada_kawai_spring_layout(g, position, weight, topology,
        edge_or_side_length, done, weight_type(1));
}

/**
 * \overload
 */
template < typename Topology, typename Graph, typename PositionMap,
    typename WeightMap, typename T, bool EdgeOrSideLength >
bool kamada_kawai_spring_layout(const Graph& g, PositionMap position,
    WeightMap weight, const Topology& topology,
    detail::graph::edge_or_side< EdgeOrSideLength, T > edge_or_side_length)
{
    typedef typename property_traits< WeightMap >::value_type weight_type;
    return kamada_kawai_spring_layout(g, position, weight, topology,
        edge_or_side_length, layout_tolerance< weight_type >(),
        weight_type(1.0), get(vertex_index, g));
}
} // end namespace boost

#endif // BOOST_GRAPH_KAMADA_KAWAI_SPRING_LAYOUT_HPP

/* kamada_kawai_spring_layout.hpp
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
*/