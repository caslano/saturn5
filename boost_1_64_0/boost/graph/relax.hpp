//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_RELAX_HPP
#define BOOST_GRAPH_RELAX_HPP

#include <functional>
#include <boost/limits.hpp> // for numeric limits
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

// The following version of the plus functor prevents
// problems due to overflow at positive infinity.

template < class T > struct closed_plus
{
    const T inf;

    closed_plus() : inf((std::numeric_limits< T >::max)()) {}
    closed_plus(T inf) : inf(inf) {}

    T operator()(const T& a, const T& b) const
    {
        using namespace std;
        if (a == inf)
            return inf;
        if (b == inf)
            return inf;
        return a + b;
    }
};

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap, class BinaryFunction, class BinaryPredicate >
bool relax(typename graph_traits< Graph >::edge_descriptor e, const Graph& g,
    const WeightMap& w, PredecessorMap& p, DistanceMap& d,
    const BinaryFunction& combine, const BinaryPredicate& compare)
{
    typedef typename graph_traits< Graph >::directed_category DirCat;
    bool is_undirected = is_same< DirCat, undirected_tag >::value;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    Vertex u = source(e, g), v = target(e, g);
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef typename property_traits< WeightMap >::value_type W;
    const D d_u = get(d, u);
    const D d_v = get(d, v);
    const W& w_e = get(w, e);

    // The seemingly redundant comparisons after the distance puts are to
    // ensure that extra floating-point precision in x87 registers does not
    // lead to relax() returning true when the distance did not actually
    // change.
    if (compare(combine(d_u, w_e), d_v))
    {
        put(d, v, combine(d_u, w_e));
        if (compare(get(d, v), d_v))
        {
            put(p, v, u);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (is_undirected && compare(combine(d_v, w_e), d_u))
    {
        put(d, u, combine(d_v, w_e));
        if (compare(get(d, u), d_u))
        {
            put(p, u, v);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap, class BinaryFunction, class BinaryPredicate >
bool relax_target(typename graph_traits< Graph >::edge_descriptor e,
    const Graph& g, const WeightMap& w, PredecessorMap& p, DistanceMap& d,
    const BinaryFunction& combine, const BinaryPredicate& compare)
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef typename property_traits< WeightMap >::value_type W;
    const Vertex u = source(e, g);
    const Vertex v = target(e, g);
    const D d_u = get(d, u);
    const D d_v = get(d, v);
    const W& w_e = get(w, e);

    // The seemingly redundant comparisons after the distance puts are to
    // ensure that extra floating-point precision in x87 registers does not
    // lead to relax() returning true when the distance did not actually
    // change.
    if (compare(combine(d_u, w_e), d_v))
    {
        put(d, v, combine(d_u, w_e));
        if (compare(get(d, v), d_v))
        {
            put(p, v, u);
            return true;
        }
    }
    return false;
}

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap >
bool relax(typename graph_traits< Graph >::edge_descriptor e, const Graph& g,
    WeightMap w, PredecessorMap p, DistanceMap d)
{
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef closed_plus< D > Combine;
    typedef std::less< D > Compare;
    return relax(e, g, w, p, d, Combine(), Compare());
}

} // namespace boost

#endif /* BOOST_GRAPH_RELAX_HPP */

/* relax.hpp
rNfu1vS9ha4b5ku6unl5BeVVlCtDP4jjdBLRrCeYS/7vUSl2kQfXR1nPuu/QuDvCuvC1676zrA7Cxfp915G/oy1C2MRkuP7KYLFcyWD9P7zzelkNLxODETZW1CN9tiVCmOSXl1VUGbqzY0nem6IR/p0Kx/rxnG5bs32/3JKi4tn4U+p7ZhHPceTNR5TDqXGLZNymlPZaYdaFrppdXiBYr02Im4nvktJFBIOWGjYMtFZCj69Q/E0cf5VLjZ83UXA9Z4N3DZV1i4yb4BF3B+tKxlFbWW2ajQL/bRT/QRm/h0f8PfAb5S+lxtbjNwRupPjr2S/bUspL8pC3D36rHrJhiy6B4gawX5fVwaqryfqD31O6ffjudJV2ebsb6VDnlPqBzxDfAMSDX8b7i3CBtk7EUzxbrJY/ee7Bku9cVaC01zeQ4qcq14kxlLd++CcJbqV6ZgDYH64jRlgKEH8TbQBcKtxAuEFwg+GCOU5NhHQIM2h0LoDS9267EXUmdVeidftfZLvROk6dCFsC9DwjsFLSeIyAtlbqsHD/5/ibJJ37NGg74Ec/BY36KcXfA4yjPHD/Y/o+GZ/7FctNAKL+6UyCfh7hK6pjkk3+gCNW/wz2Fze0nldIYhuUyxHYBDgLmIo4K4m/GjrqOPBUXFRQSvMNz2ncX3guY94EaZPwEPlzvJ3VYf728rzCQfJPludQmr2i+r8RI8R1nnOStGv4NMUZR/5MKbON1Nu2v0pjpba5SerY7qU4ExSek1hGvOdcRPxlCH+Pwlsr5nkIceTYrfYcuyZ90u84f6GiHtt/1Mv5mgjCvBgDaoooEYeFjWTUi6VxVCSEUeZI4n/O6/ijMzlXOL4C4dSxk8b88+EwpmgsJXkbS9wPJ8ixQ/2BaIW1jJnyWsbMLC9jptoyZmrv74Z9vivX0bhSXR4vulRedJqu/I7WK9V1+q10sq5UZ8qLbpRXXapSqs9nx2U0mbC/7aVbP2s/+cMdPcO86UB50y367e6A/a10oP7Vuk616y5duQ7Uleo64X+RpO/LeI+7Fn80x99dgepvMdvFWwbsBLwV2At4BJgKXAmcDbwduAx4B3A5h68BrgGeBK4DRrLeTTJwG3AocDswE7gDOBK4E1gOfBBYDXwIuAK4G7gBuAe4E/gIcA9wL/Bp4GPAl4GPA2uATwBfBz4JfA94AHgBeBB4CfgMUKC8zwIDgBuBDYD3AuOAm4DNgZuB7YCHgSnAF4HpwJeB2cAjQNQjkNcFXlfXeuhxXQ2+JsDewARgErAPMAU4BTgAWApMBV4PHAicDxwCXAXMAB4DjgBeAmYDbUhjDLAJcCywGXAcsC1wCHAAMB+YDiwA5gAnAccAC4Fu4FRgObAYOAtYArzoo+llnBqniK/g2K7dz+le/EP27P4d+hah45X/uM7FP6Jv8VvrWtTdNfbv06f4f9el+H+5a6zcZIuuFeaJpPF1OhN1v7pf3a/uV/er+9X96n51v7pf3a/u98/+/tXf/+kj/G/w/V+1ATjbJcS+74Swi8qKcndebnHxxNy8qTA6BCsj0QhXz2+14nDYB4TRqUmIW0l2++a4rPYBmeZpHxA0D/uATLNpfBmD0jJShTDoAVa7fJIeRPSUYRl0LaAhO9hkTzCaafU12oh094BhozLShyUPkPxAi61BooXrNLqv0KDHsO1Akm6iu6y2CSU91mqDUNJbWW0WSnprq21CSU8hetaIzGuJLvM+kOijRo0ylT9D481K72LQRhNtRHLGAENmTT2qV7d7YNqIrGyDfpzpmcPS01JGG/TXdfrIEZnDslJl3Z7Q6NxC7ozka1KFi8PesIYNSM201s+bHJ6cnZ2GaDLeSWu8wcM=
*/