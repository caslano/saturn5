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

/*
  This file implements the function

  template <class EdgeListGraph, class Size, class P, class T, class R>
  bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N,
     const bgl_named_params<P, T, R>& params)

 */

#ifndef BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/relax.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < class Visitor, class Graph > struct BellmanFordVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.examine_edge(e, g);
        vis.edge_relaxed(e, g);
        vis.edge_not_relaxed(e, g);
        vis.edge_minimized(e, g);
        vis.edge_not_minimized(e, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor > class bellman_visitor
{
public:
    bellman_visitor() {}
    bellman_visitor(Visitors vis) : m_vis(vis) {}

    template < class Edge, class Graph > void examine_edge(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_examine_edge());
    }
    template < class Edge, class Graph > void edge_relaxed(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_relaxed());
    }
    template < class Edge, class Graph > void edge_not_relaxed(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_not_relaxed());
    }
    template < class Edge, class Graph > void edge_minimized(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_minimized());
    }
    template < class Edge, class Graph >
    void edge_not_minimized(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_not_minimized());
    }

protected:
    Visitors m_vis;
};
template < class Visitors >
bellman_visitor< Visitors > make_bellman_visitor(Visitors vis)
{
    return bellman_visitor< Visitors >(vis);
}
typedef bellman_visitor<> default_bellman_visitor;

template < class EdgeListGraph, class Size, class WeightMap,
    class PredecessorMap, class DistanceMap, class BinaryFunction,
    class BinaryPredicate, class BellmanFordVisitor >
bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N, WeightMap weight,
    PredecessorMap pred, DistanceMap distance, BinaryFunction combine,
    BinaryPredicate compare, BellmanFordVisitor v)
{
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< EdgeListGraph >));
    typedef graph_traits< EdgeListGraph > GTraits;
    typedef typename GTraits::edge_descriptor Edge;
    typedef typename GTraits::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< DistanceMap, Vertex >));
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< WeightMap, Edge >));

    typename GTraits::edge_iterator i, end;

    for (Size k = 0; k < N; ++k)
    {
        bool at_least_one_edge_relaxed = false;
        for (boost::tie(i, end) = edges(g); i != end; ++i)
        {
            v.examine_edge(*i, g);
            if (relax(*i, g, weight, pred, distance, combine, compare))
            {
                at_least_one_edge_relaxed = true;
                v.edge_relaxed(*i, g);
            }
            else
                v.edge_not_relaxed(*i, g);
        }
        if (!at_least_one_edge_relaxed)
            break;
    }

    for (boost::tie(i, end) = edges(g); i != end; ++i)
        if (compare(combine(get(distance, source(*i, g)), get(weight, *i)),
                get(distance, target(*i, g))))
        {
            v.edge_not_minimized(*i, g);
            return false;
        }
        else
            v.edge_minimized(*i, g);

    return true;
}

namespace detail
{

    template < typename VertexAndEdgeListGraph, typename Size,
        typename WeightMap, typename PredecessorMap, typename DistanceMap,
        typename P, typename T, typename R >
    bool bellman_dispatch2(VertexAndEdgeListGraph& g,
        typename graph_traits< VertexAndEdgeListGraph >::vertex_descriptor s,
        Size N, WeightMap weight, PredecessorMap pred, DistanceMap distance,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        bellman_visitor<> null_vis;
        typedef typename property_traits< WeightMap >::value_type weight_type;
        typename graph_traits< VertexAndEdgeListGraph >::vertex_iterator v,
            v_end;
        for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
        {
            put(distance, *v, (std::numeric_limits< weight_type >::max)());
            put(pred, *v, *v);
        }
        put(distance, s, weight_type(0));
        return bellman_ford_shortest_paths(g, N, weight, pred, distance,
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< D >()),
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(get_param(params, graph_visitor), null_vis));
    }

    template < typename VertexAndEdgeListGraph, typename Size,
        typename WeightMap, typename PredecessorMap, typename DistanceMap,
        typename P, typename T, typename R >
    bool bellman_dispatch2(VertexAndEdgeListGraph& g, param_not_found, Size N,
        WeightMap weight, PredecessorMap pred, DistanceMap distance,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        bellman_visitor<> null_vis;
        return bellman_ford_shortest_paths(g, N, weight, pred, distance,
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< D >()),
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(get_param(params, graph_visitor), null_vis));
    }

    template < class EdgeListGraph, class Size, class WeightMap,
        class DistanceMap, class P, class T, class R >
    bool bellman_dispatch(EdgeListGraph& g, Size N, WeightMap weight,
        DistanceMap distance, const bgl_named_params< P, T, R >& params)
    {
        dummy_property_map dummy_pred;
        return detail::bellman_dispatch2(g, get_param(params, root_vertex_t()),
            N, weight,
            choose_param(get_param(params, vertex_predecessor), dummy_pred),
            distance, params);
    }
} // namespace detail

template < class EdgeListGraph, class Size, class P, class T, class R >
bool bellman_ford_shortest_paths(
    EdgeListGraph& g, Size N, const bgl_named_params< P, T, R >& params)
{
    return detail::bellman_dispatch(g, N,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_pmap(get_param(params, vertex_distance), g, vertex_distance),
        params);
}

template < class EdgeListGraph, class Size >
bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N)
{
    bgl_named_params< int, int > params(0);
    return bellman_ford_shortest_paths(g, N, params);
}

template < class VertexAndEdgeListGraph, class P, class T, class R >
bool bellman_ford_shortest_paths(
    VertexAndEdgeListGraph& g, const bgl_named_params< P, T, R >& params)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< VertexAndEdgeListGraph >));
    return detail::bellman_dispatch(g, num_vertices(g),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_pmap(get_param(params, vertex_distance), g, vertex_distance),
        params);
}
} // namespace boost

#endif // BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP

/* bellman_ford_shortest_paths.hpp
ddtSJdgMgcfR5yk6RJLGfVWOB04u6WeEutDpZPcTzAEH94rKAU5PoGanUs3Ahp3tAbiN4I0eLJznAqHXUyjEOqhJipu6nsJWlA37C4XdXLaLdlJYd9mwbykMsuji4aVhyVaEXVc2bH8KW1U27GAKW1M27CgKW1a2DdMo7OHSUbO5H+CrNKxExrNVqNta9LVoU42jkPGz5KV1SVNZYnKUFHlao1W+Pk7wyq5EUi4pk6Y6RcBZraOs7kdpI1Vps3VpjPfKULj3SPiQB8gJAqVYVLZ+iOWuZk48Mxlx1wi6gKB0ysNrEyWWXH6tNzED5Ul8HSSL4Xr4FJemgkuJhCyQmr1ANjt4eCLYbBKvLcmVaQoNNfKrW/0pRIF2tR2cQw8GJ8afW/2J8aA3MQJkSsp0dIbwG2PkviLB/Hq56KozEyGlEzhRyY6R3ARhqj5H10SUIDlMCZJCyZFcnJYme3xp8qWgNCl08UqmTIcaD2eZEnYEC2DeT7IipF7nV5Kkk10gtekJ/9t7MnG6eYDBP1MsOPfQJljwU1PcC4U62Tybhc1g/YpONge+gWfHMTFUN4PrONxIBc4jCdyLivOfyZ6btLIusphe12NQJAu3ksvSiHubfEZj2aaI82tw0g81J30RnHQDeC0gwsG9ss50Ymbu7eAP4Yz84mg3/5ZNNmVrN6K1r2gO9H+MXXucFNWV7q6qrqp+zAzd09PdDI/mIVBM9/AaBAYQiBvUGBUHERXloYiIiNd0q4mMM2KyJhv3J1k0ahbjz8j6yBo1avCBj7hJdH0FbaPGxLhGk5jVGNeggu+ZPd+591ZV4wDzR3fd+91H3fc959a557TJ2tripyyn1RwXd6LGlhNEUWJZb4TFsnRFZT2/FyneIet5ZKzcqDs9Jv4WYWkE7x1o3Kk8f1Kwr+5SlNUuZWEFT3GxLQW12HOXFMt4DxFavdtceSbzkSYLPlIZfKyBjxXwiQY+UcCnGlCOnPe2zfYX1OlE1vuzPJ14ixf1ng8RbanRjWfZ7v1Afkbaw1ZqFOqYmz5Q30n2SKFi9Cnu2uQwBrNSDW6SNy8psZWJSvFT02vB6uP9nW/hlJOuQyzG3eisRTQcDRxV5Jqt3t3QH9ccI47gCD6+lNHbnerPoH3Cdqvb0Vtxxxb3YHGJe+9QBLUUxrwl0ZAczKGRWRvZHECkzfAaIMJEozDklGW/nno1zzTnm2BwTNu7wQVPVZzrNVPE3s/0wGsEU38vBh4gxr31GHhn01+qeh/K5RTmNONKkHc9K6gyDe9PICs5o891Rk1+RoAYDzJqjrnifiyycTYFnYl7O5g1Mby/gCHJpu3aPb7+TfEA2m9lOpa2xYOYPok4uR5CSx2Ztr3dEI7YgAUhwKdRSxV02Dn1YTmn0JGhsM4Evo65GqcyPAw1Oef29/cTpxPvyz0bcDqV39PYplV1IZREnBg3+ux/2Kp6QaUaSvNUrRKlYZmErBIsNvpvcuWbEvwmYqYbM4nwa+Jtau3dErnGiypeaW3U+550NysdDQWW7bmMhXSz3s/RIiVbPIKyzEX5RkqP6IAwnkd/lY5lNDP5/N/IaftyFr73R4Yir6rj8g1L7yMWo36TJXDs7jsiEVomME7Epw6WkD4MbYnb4hMsHzYWYwFtfox617o87FO22/0x+cXnQQrvPRuXzbLef6HAo2mhMV1kGoH9lbjMXHxgq/xKG+QbCh3DvNspRnm5bffZrqvV9N4fhY1UW9yHjzWuLXbg2alf9b4tL6j5LyP6IRa8LW3t/Tp8Dq6V9VItRxzzgVBU0Io2Kk4XvyCwt0+P7yEY37/E+AbEuHcuhsLX5Ar9K6zIU5OVa6jt9d0exjpcWqQf5WOL2qv1irX/yWy9fApBSSdXu08HbXPyYU8h7Bka9ojHTL7vhXEyGvsQlzvL5a4rVVACX0fY1+k5nPfX/+atWzwO5cu9ODG1m2O5Zru0GPNva8oVT2Ds4pjGkm5xCcj2eLklLhbxOdWTptbgYmQbjLgrdqvuKLsg5DZRpLSdPxHX8NKxzeum3ezgjM6JEL+Ou4/pag+WSdvijMSxPIQsnsoWv9ASTyEAJcwRHRXH2MyJE/HIi2X0MDu3RnnPW+joNN5EqAF1TYZKKkgchjS26KIHvkya7BKLJXqcj8IllgDtHmdQ92dNftIwN8VyhK3gFN0HEQjeZrd8F/tLAGAIThqBA0R5nxY+wqVSwU8x5Tkuq/MUq2UpTteHqWzDj6KeLqNabMmPrfiJNTLqGYgay8Sk6T6KeoaMGmMDfmy8T6yVUc/UNOQy1Sxnyqg225pjO3NinYx6lqYoX1e5niWjOmyuj031ifUy6tmI6mZcaYeOop4to7psjY4t0YkNiNo2w+T+NL0bse9P8+5wQZBVAv3gT0XYHHralBN6K6urJNLD7v4u1pVbMf3HqkDsQkmnnHXE05jtKTMvWxCRTENGEntwNnUbkN73QSnLpNCuJ+4AKm6BwL33OZWqvUH6vC9jNe3EaSJ7P0QWWHjMUHh7s/L0Ucqs92uTlbuKB/DpyVRv+Vh/43TYXEMxCl3286AiU06TBnysgp9j4vw1E80YGZM6+ROcpmW9KxENWh/vxT183++I7VAW4PtdcTf548o/3pL7Qd7iraBGtEtYvRI0Qd4ZBaul4rsmzc6Hor5+7BdxxxhlzXbFsl2N9GjE0852mcUZYicoAaJlZt2CTzxpayutLs9gA4UsVzZp80JCG0Etr19rHUuz1QIzYlp2F4UUdEgsCIlxyFAd0hgkshplqlY/LBYKk+lu10t4ox0Ks+2utEULDi1B8c3r5i/q52u5PM4grz+a98AFTrAH2sa4PiflqMMs0cljNqJlrsdw/I5wfF8eeyyH7TAGCjuIw+6vC9OnXLONbmKerKwpnjXlvV47ch6lGcdp7gun4TFVnJ4t8FbREM/VDvH3gHi+Ni/wZEWNFaKpbXBi9cYEtmeebY6oQokZXmq7ffZNOC17DsvqvYYss8UygeP5/TcY+2ybHyG6uM7AcM+F6AElf4l6T+A8fuDu3Sa4Gt6J7/2ewR+rvRctNmNhis9tNuMBaoL9u6T/h9r/mfRfp/2fsj90oRa7aXsmhIjfmCz9YIo+mfbheDhtLaZbzRbjoyqmeovpqJhRnJIa3l9BobbWLh0gRT/nlRwgJOJISdJddnBnCtcePKbJv8omYMpz7PNp/4u2d9jnj8SzJEXqaxvr9aJl7dq9GhHPm9pIx5Q6WqI9E0Jk7dlwiPpG8zptkBPxbisnyWsiDGNqHZhZiZ+sRB5aLzeYzMwZ2+x8bJtdMHjb9WJUnW32UJxVT/ZlUGiuqgWts7K5PgciaCiUKBmLCJhwHs5QY5sTysMQL/CpSWXEKVrqIhTd8iaFYr5IcK1Yv6iNrtztJwzSGfJWIKezgkWCG6rzOywuNMfcvK7QcbCZ28pkRzCNON/24WZeBWzxUyOg82oclJeX19U25ebCdXTzxja3EJqY7tAgl21uqPZmuUjFyHcM3UcxyqXK+8sHqF4o2qRQd1hded3fsE19FMthHZJg6UpvdoJlnJlBaOMcK9tWRM4t+D0ufkv5U7cbrACDevolM5AP9W3liq+oz+/SVm6Lbys34JnbWK5YvMufY9uTlbtXaMMYpqIwJdcUI64pxlxTynAt4Uqy0nHiTDJSkM81xcJck9Pbr2nyNJal34EmB8S4dx5o8vPBc9Ly36Ztv3hHRxRPJetS4nn4Og7442b1Iax3JcesbnflJ2Teu6+keOWAPjW9FDUh06e2pJfFEXBTVR0Qhccw4aoIHW5DGctSNKtVmDTGNh0vjVyYejWJ3z8ZK2gGECjZUiORtCHKFofSCWQuZOaOl9R7kxnZST3XHoUdPSaJEtmkdf4STD67nKE94GWTL+N5PwKPVjKyKYu5ZjSxmRenUD7xciYuTsAinJDPZqtUcMsZV/yB2W75JNCMgesnaiGlqWgzJo7CWVtzLF6eaMbZGjITu+SGsWRxJCLF2bo0E6F56u7VbnkV0SyvmFJMIJoPaGSC/8eENbEUceKsYTsdLyUlyCaYZYaueJVJPuKjW65ApETJzgeULr3E8i6A/nlqE2JxSlmtcbvZbozlJ43JNTuW9w0/oNkx03a7lXYgSrEU7Z8B4KRjMhVjpmUyo8O0KzML9cgSXqguxIgj5r/cYBLb/0eMjhXcBO2pTLKvZQsKmyzZcbbRzRQ8B6X6Wr6KoBSCYDWbyXAOauhruRJBDQiCcWwmuzmosa/lKAQ1Igg2sJnM5qCmvhZ8Wkg3IQimrpmx4KAhKmgIgmDtWXyDg8qNcbHQ0tQpWL2kBLzXcDPrAp0+rcqaRnpYpRYX6aCMKlAGQTA+LTZSUKOdWyzPioqjVhZHdRBlll8cL/OjMVaQfrecxEMNybCtn38mWsXM8frEVNJNO6QdFoz9tTQ3J2Fu3pxgUQFMtEp2Jb5PsPoeWJnrLeP63GusxjTrvY5Rl7flLrKjfpk1sm0OU0m2pJLwZqfPvgVr65+UNgMth3cpSgXx9LrygCiejPL8GOWx5MTnolSmr1RW78QUqWrL+zPG8PB9RPqLGUSi8vKis3d5o35xR6C4XCQq73/q8oqvYZWI5XhhKRPBJSMPp8iiyt9+Tb7vg+ks6dyNuKhB5c9XcZi6Cae0VYsNHVYPw02ZN3AHrnpM4IQNHeUsBejkwDk9cC4OnEt956b3te6VTbvlQW5eHuSONL0ZCalQpIfWbnyujRqs1LQbXikA2h3VzlPbVpjnb4auFVwmMG+C0yugYjfLBE1RfsgTl2aZkrCoxphIAv1LdGxkahQ2Hrup6laCnjF60nJ6vO39lQ/ws97/ou9ylSNW6ltmUiiXtzfXEW/yOa46MB5e+baO5rjiLVNrK+DI0DRbwuuPMbpNrIBWdSRW179hvC2jIfY2OhKJumIm79pdbZOqwynKJljjaNsIrctDsQH+HWvkOxClQD6G93/IAa1nydZDJdoeMLhSUmaWnaohYwEaq2vTfwvaFE5vtGpTS7YfHvKMsVmmJCymMWrTK7S4g+dh77K8NkeKZY53WEqzLGd7t22o43x2EOBowFGAqwFXAXENxBWQ0EBCAUkNJBUwRANDFJDWADuYZuok8mKavBP1DNj5Qs+dxHmZtRY9+YyLGlBBC5OqxTC64RNTYTVgqzcFu8expuTAZ5qSA7fqj/tGGQHSg8Q0BcPJ04bh3YSzBRdnA1OYkJ3s+McGCIaXVRf3pJBexZ8BlsUzapMDG1ZTFFXHKYiYKyDLH+MYZbpONROpxhu1g6J1qYh2V6mcIJVKI97F8B+iPP/A4WKfUYrmvGlOYKvrl/Ts4DPrAjSA5nQlmE1pMbpR8nJDOMOUeR6iVneZbLseTaPqfJDhHcyfd5uA5XkzIBbY3BbnLeG8x1lxHOus8zaC8uvGuWdds3VIny3ewwR8HxxyLlXKOLYLwyRE5ECln1LGiyjT3nBoodql5dZirJttOsuQoRCzYX3TqD3hHx5zo4EFkI3mcqP1NKJ7uCZBr3gx0ODD1cAZaISMDQZbXrP7Kt8450tUqkxOMxevkLFYWtHeRgTaY/z5OszxNxlaz9IRPv+NQSr1RHXwllTL1vOSY+2gHBJJ23sVtS3PPP2Yfec5LloXn+bcKD3nRqlJOFoDoxUwRgNjFDBWA+yQ/fEKvfPg0DwdpubpsGCejvDnKeUxIpimiZAvvzVZapKjEAdwXhxfMm1vDoab4x3Cs29u/eyb68++4aHZd6iaR3P1+wt6SIAXdNSI4GnUJpPUJtR3+xCj9rKvyJzjoZ7QoTCD5xGil8fo4nCHuEY3ytBOUweh1Q/k1CkCW27UntbDsxDM6dk8p/MyGzW5e0byOB3pDyUMZG6jbS4PpoQRJoyKHLs48Fx8ijWTyLOO/YyLYZG9x8UE3ckTVK97GvAUMFEDExXQpoE2BZQ0UFJAWQNlBbRroF0BkzQwSQGTNTBZAVM0MEUBUzUwVQHTNDBNAR0a6FDAeDznGfmecbzg97CftlH+stBqeIuCIZaSPm98gkUXxhv19tQuYZ0T4JbAf+8ObKPt0XbBfHYKL56uSzJdAQdr4GAFzNDADAXM1MBMBczSwCwFdGqgUwGzNTBbAXM0MEcBczUwVwLeQrXzH6IDDlEx52lgngLma2C+AhZoYIERuh2z0ZBSh7shvcsf6bVYwpc4mvwKxGec2xVPb0jM20NJOq9lAcDjHXljTIV8iMGfT9oS55NMiDbniNk4POiy+XbYN1WGSUwewoUSStgMBRIdXx5deW2lrzJrIe91KHWIUqR17mOtKx+6kWdy+Vu9b/GxBG6vDlPutnMM7xPwDVKpjfSYlvjU16UP3fWzcMbf2tFkQGDnm6idYbdlKfZnLDLSGhefm6zvVn5Pk1p9LCdQ6PPqFxX6aN2u4xf493yO1n11tOq8YzRwjAIWaWCRAo7VwLEK6NJAlwIWa2CxAo7TwHEKWKKBJQo4XgPHK2CpBpYq4AQNnKCAEzVwogJO0sBJClimgWUKOFkDJyvgFA2cooDlGliugBUaWKGAlRpYqYBVGlilgFM1cKoCTtPAaQpYrYHVCjhdA6crYI0G1ijgDA2coYC1GlirgDM1cKYC1mlgnQLO0sBZClivgfUKOErRIfLeXyefv/VhjmUilQdX0QzoBwdzlKGFwYkdvMth+aHqTny2f8znVcdR+tnROp1gZuWRVdpZfYbngiGeDSd/3PF1REB32RxOX55VZ/NYqSQx5buwoHLSJ53gDB9ln8tyvL5UsRV6t1V9Vl4JFM/Z/vsmSDNPaWm8+i7eBdkQW9LJs6UwIjee4GWDb+RfTY0meJ/dALZQyQGfY9QJBodtBM9j2lRIonCDn1KKxZ0kIhZbswHkXYRNHDF5AYYD4lyBKHbPBrlJ4W1tl5HjbC4C36NMGd3wqYuTXs3ROtoupHVgPpeBw6XGtZL0VZ5bpc+vg9AvXKkMZxxEKzZ0ZIzqr7AYP83U2K/5o4qM0Kqt3HuP8i3sUBY2C2gzH9p5Cct/+in42may1BYuasdwVdTDT9XM+sBlKzfVF+4B2SsOy4mn3PZc5fH6HOS5vNsWroTtPQdWb+KBq6Gi7qcAD6omUfI9bxOFPg8017hE50vk7mvu/bZJDEsv9U9xRDVK42Ac7445z2A3RMnzyg358YJyQ2h8qHJDdrpVuSF3OUy5IXA9XLkhSD1CuSFZPlK5J54WObcYV5458CSUB8LVxaTyQJq6mFIeiE8XG5QH8tLFRuWBEHSxSXkgLV0cojwQcy6mlQfy0MWM8kDIudisPJCbLWaVB/LDxRblgVh7UbcK5N+LulkgCV3U7QL556JuGIgTF3XLQPa5qJsGIrdF2TZ9zZvQBaonICRsEtrZaUYizsIRSlkK9nTcd1tEv/X4vEQ/6OzfpNSlQRP2o/R7WuqUhlwf9vAIVHpfTD/iKCK0fEV2QeaPiHKikSO07ERoz4xU6LeZfrfS7y763U+/WQ8YmH87eU79AcTIlfJL585guPmTRVy6n7Dv7Cdsiwx7WT5+Lx8vycfvBkzH56lSlOO7+8n4ZzLstwNGkXPp61hotyOj6wYV6/oDleeGA0X4j/2857yI/obx74OKdc2gYt0yqFg3Dar+14ZiyRHxoERePFC9Lz9QhH/dT0/+Yj9hV8mwF+Tjefn4TWgDmK6UushCYzcSjzi+bqJLtR6KYMEs+HvS0acNYk/ijOUl2PuwYo+Qkb2VLBvBoXy5wRZNQU5fXKUbOx7X6/PNND8XMN2zU9+krVq0HIgdQQMgTUO8MGca5vjRUX/zqt9UnxxEBbKJbHLWt+q3v2CnqdvM3XHNVnl+Wt5y4H2zfUhaXmFQvtLoUO2Tpcl7d1eipDfR2GpVNHcfm2imbg9bsKK/v99pT1bWrNZik6pt7+c7sjGLj9sfXD3AxhqOaAvbqu+FeXW9sGB7X3+/GjqVCacfuPnaVoQHJtdbPByMr3dxlzXi9yXfaL6nvhsTdmEO2t8uxhf8IKJXXLG9frQzzSc1OoQLHPf7es0gCnugrMPtMqd+dF6mG2XnYBplTzhxgiinAWe+uCu8nvDUvN0J7Az/kJ5fwrcyxwpIHjnAV6rCLFzjK+oYaPQm68g9R7hylPSsGWCU2I4qQtzazzRt6LhaltcWP9VnBTfW9/ENfB9+7z7OB0a6oOe4pFYkvmyiXsz0+sDwfjrmGd0xf1wziI5BeWkiRg4duF0vVHl95YxBU+P7b/HEYFo8OcgW/0kwr/qhLK6el0g6hUljHZpED9UvZtJ6yCvomuEGtOZFch4cpQsGnkgvDKLudmrAFzSoC4ztqYzV11LBl26r1EggtBzEV/H7E/tc5BoXrKdFTm9clVlrD1wO/77rl6ktereAKctERIrak7iM2/wMwo3un4Yd2hT1Grjl/8VkpYTIq0x5LcTYuFWpjkUYZ2z32T9BLo2UxOuhEQyVGU2WOm+CztDDkG4IxpRdeZPenRdp8tiVPWtBgyuPdSbxCcqdJXdBuZsOo0gLlGcMBYxUbmg/Lo5SnmkUULxYejZtUScGV+sjBHYsNbqvwJGp7b0mb3ZdoYOvUPGvwvPnUB9OXdZzFTPC32f+NcPNcWXAQn/oz0u1JhGtEDmcx933/XSi2WIGOiun0xcDWjhbIF4vGs6B7oXg7SXHyLJDKnHDWULOe8vRajqlU4dY0ntv6PwydLBgWD3/X9q1xLZRRVHbM56Px7EztuOxkhCHtEEjexygkaC1QLhCQEkpRQIJWKUbKBTCpJPCghAVFvwqNoWWsuKj/pO2Kis+EkiAhASroooFSLQgPkK0/EUpAgHv3PueZ0xRhcRi7Hn3febNm3vf3Dv39wxJ5tkAhjO1qv+topk0xSdbR9/apdl0xQhDKCaexbvb5AL5CaQp79CadG/bzcm2KDQ0fyvfj2mGVT32G+Achtf/o/9Msj8KyOSH74knTfrGEe+QNnbIAmuzG1ro8dAJz+9faHt9UlOq+dTQJdnU70KWnaKYMmIlykW3qC2ghVukhonvvRJS9U+Tra4selR0eIrtx2gTwWIaUm4PHtBrE6st8kaud/yf4IG8whqncrm/1K8o35WU7zaLAgjKr3eY9El+ygaBRR7V5VKpRHb9QV6cwOJfJpXPW14s3VgNxhy3+KdxGPRXA/09DNc=
*/