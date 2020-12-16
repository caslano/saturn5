//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_AUGMENT_HPP
#define BOOST_GRAPH_AUGMENT_HPP

#include <boost/graph/filtered_graph.hpp>

namespace boost
{
namespace detail
{

    template < class Graph, class ResCapMap >
    filtered_graph< const Graph, is_residual_edge< ResCapMap > > residual_graph(
        const Graph& g, ResCapMap residual_capacity)
    {
        return filtered_graph< const Graph, is_residual_edge< ResCapMap > >(
            g, is_residual_edge< ResCapMap >(residual_capacity));
    }

    template < class Graph, class PredEdgeMap, class ResCapMap,
        class RevEdgeMap >
    inline void augment(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor src,
        typename graph_traits< Graph >::vertex_descriptor sink, PredEdgeMap p,
        ResCapMap residual_capacity, RevEdgeMap reverse_edge)
    {
        typename graph_traits< Graph >::edge_descriptor e;
        typename graph_traits< Graph >::vertex_descriptor u;
        typedef typename property_traits< ResCapMap >::value_type FlowValue;

        // find minimum residual capacity along the augmenting path
        FlowValue delta = (std::numeric_limits< FlowValue >::max)();
        e = get(p, sink);
        do
        {
            BOOST_USING_STD_MIN();
            delta = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                delta, get(residual_capacity, e));
            u = source(e, g);
            e = get(p, u);
        } while (u != src);

        // push delta units of flow along the augmenting path
        e = get(p, sink);
        do
        {
            put(residual_capacity, e, get(residual_capacity, e) - delta);
            put(residual_capacity, get(reverse_edge, e),
                get(residual_capacity, get(reverse_edge, e)) + delta);
            u = source(e, g);
            e = get(p, u);
        } while (u != src);
    }

} // namespace detail
} // namespace boost

#endif /* BOOST_GRAPH_AUGMENT_HPP */

/* augment.hpp
zo96fewr4ldalFW3ddnrs49U5du+13B9ekO1TmtdB2wUe6uoah633Rdhlxe9l/km0WseZbU/nhJ7A90Gn/+htMGd9QBhOcYYzGPXG5kB+rPMMPWGqvNbSbyNcdUy2rqc4wpOP+aZqi6RXCF9unrP9brifporAs22Ri3XOa5IcZMTuq9R8sIkcePRe8B/LGG5iROJN370Qzveb4Mlfaqbus6ROGJFmFp/+9AuqY8jBxuF7l/cDY27Iy4Mmy8C25e1+StF/LvOtPYFuE38mxNxyN1Tjb/Y/qQakS7Rs/3GXt0Vqq+xFrbv9vh0LjA99rpj5a4b97TPdPaFWnn/z+JmgP0No8adqqv7GyX3m2Na/b4xEj/n8cyB97XY2IpeiuhZ8VQ7Msp41/2pO0Xueae0P6TvXY0hBaR1aZnIh2Nz9M3q9+pO8fOA52r3R0aqyOz0yDSudkdG1Obc5zlmcF+t6heTZznXtMrix+J2uCtFrtvP0piVTy+ilyp6dhinG7Pc37rTjUkR19lhqLE9y89rJH7e1GVsu4T5lhHeL+oV0bXDr8aKqB9YpeJrP/ambXJFM6tfd95e1X7Ubf4MpZPJgOmHyeh4FtwfG8MAU0yKt2a1SJe7lgw3RUd46yfZaVzBoJXdXp2xp+peD0+K3R7zVO80nWcWyvUs9U3HF5Y8U4wr1jhq2mEUW2FI+o4UN22NFLFbYQykHRpPPVJN5hAs4Tk3N7fG4xa8xH1HeGI9ahJB4JicfT/nil8Nld3yOzLsGN1ouV7f3/5W4bZuocN9MLZ5bHrYcUBVl3YVP9JChpEIu8n1VAnDmU4b01U6xSzIjo0NSqfECNyGS6eaAenUOXw6Sd2XIdc9Rqg0ScL27W57fClJ+9dU0qID8TE8XcfJhBNJC1+YP4qfDZXd8tMTNi2O7nakhQp3gx3uwNimx0+LXbvDj8kmwT1yvbZOi+YqLYZnkBYyLvsiQaQ1JhUa2qUlfDrcuLtqOrwr9qiw5eUergeXl9aMrtcOW14u1GmDXYfRXMaQniV+DrXU49Z/DT9ubd/DxeK+gbJb/sWETZeLVJxKuqgwczJ0mK/HNjt+uuSreA9XRs6X63V0umSpdPmplSojUfN7eD3VfNWZOzG2vS+NIqqkUVz4NKobkEYjxO4Nm0Yt5XrrgDR61YhlZ+xwafTzLkca6TBipPyMJq6Wt/LHF3frnj8h0u11RemkCpdOrqrppPxsETadft3lSCcV7tFWOp0GxzYnuGrRvjDjwoW5R/xoGjad9u2yy6jPpKh0atpajR/Gzu9ER1NwP5PSG9jaGu+c39jriTQC32HWe67c0ou+rF84neVWmHGXPeQMz6mzwfbntkB/HsGegf1H6fcKb7pwvQZGfYMF/f0uJvDv92Wc9F/3Z2ey7V76h3wPcIy5ZoehNdes4YeOuRlZhsjIy8HzNcwQ8zXM4PHZ8cjitMwe7ysxQ4/blmt9/T0i8llm6O/DeWbouWU5Qj2vQ3+37qyn55aJbLjQnhPi7DtkPa38Btbk21Ko9iT7SL4tefBQe5LZZWv8AenbUuXAcnea7itO2y/1vmmdVzbnY+mTjkgxvnSH3aNM/Bhn+Nt83JP40dDT1nSZ1Twe1W60/KoXdK6Z9V1y72H5ltLtzlVidxtd1bfIdeL+5/iDxsLYa1hc/KB3pFE3bo4ZU8NjnI7pXcNtlNa43UiPjzF6xnemb02+kSQPdJR7Gp9cZT8m6RUgzdR3QPI3Pp2/m42o7waZt+MWuQ43Uu+jtFX8ejFJfRfyI9onTM6fqL4BymGK3ecyxXeJXFNphXUeYeWKH+d60omjkR4XfiPXcfRT0H5v/vY8aS7Xn/ScZ/w=
*/