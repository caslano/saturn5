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
+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
*/