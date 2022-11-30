// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CLOSENESS_CENTRALITY_HPP
#define BOOST_GRAPH_CLOSENESS_CENTRALITY_HPP

#include <boost/graph/detail/geodesic.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
template < typename Graph, typename DistanceType, typename ResultType,
    typename Reciprocal = detail::reciprocal< ResultType > >
struct closeness_measure
: public geodesic_measure< Graph, DistanceType, ResultType >
{
    typedef geodesic_measure< Graph, DistanceType, ResultType > base_type;
    typedef typename base_type::distance_type distance_type;
    typedef typename base_type::result_type result_type;

    result_type operator()(distance_type d, const Graph&)
    {
        BOOST_CONCEPT_ASSERT((NumericValueConcept< DistanceType >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< ResultType >));
        BOOST_CONCEPT_ASSERT((AdaptableUnaryFunctionConcept< Reciprocal,
            ResultType, ResultType >));
        return (d == base_type::infinite_distance()) ? base_type::zero_result()
                                                     : rec(result_type(d));
    }
    Reciprocal rec;
};

template < typename Graph, typename DistanceMap >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, double,
    detail::reciprocal< double > >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, double,
        detail::reciprocal< double > >();
}

template < typename T, typename Graph, typename DistanceMap >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, T,
    detail::reciprocal< T > >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, T, detail::reciprocal< T > >();
}

template < typename T, typename Graph, typename DistanceMap,
    typename Reciprocal >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, T, Reciprocal >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, T, Reciprocal >();
}

template < typename Graph, typename DistanceMap, typename Measure,
    typename Combinator >
inline typename Measure::result_type closeness_centrality(
    const Graph& g, DistanceMap dist, Measure measure, Combinator combine)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;
    BOOST_CONCEPT_ASSERT((NumericValueConcept< Distance >));
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));

    Distance n = detail::combine_distances(g, dist, combine, Distance(0));
    return measure(n, g);
}

template < typename Graph, typename DistanceMap, typename Measure >
inline typename Measure::result_type closeness_centrality(
    const Graph& g, DistanceMap dist, Measure measure)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;

    return closeness_centrality(g, dist, measure, std::plus< Distance >());
}

template < typename Graph, typename DistanceMap >
inline double closeness_centrality(const Graph& g, DistanceMap dist)
{
    return closeness_centrality(g, dist, measure_closeness(g, dist));
}

template < typename T, typename Graph, typename DistanceMap >
inline T closeness_centrality(const Graph& g, DistanceMap dist)
{
    return closeness_centrality(g, dist, measure_closeness< T >(g, dist));
}

template < typename Graph, typename DistanceMatrixMap, typename CentralityMap,
    typename Measure >
inline void all_closeness_centralities(
    const Graph& g, DistanceMatrixMap dist, CentralityMap cent, Measure measure)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< CentralityMap, Vertex >));
    typedef typename property_traits< CentralityMap >::value_type Centrality;

    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        DistanceMap dm = get(dist, *i);
        Centrality c = closeness_centrality(g, dm, measure);
        put(cent, *i, c);
    }
}

template < typename Graph, typename DistanceMatrixMap, typename CentralityMap >
inline void all_closeness_centralities(
    const Graph& g, DistanceMatrixMap dist, CentralityMap cent)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< CentralityMap >::value_type Result;

    all_closeness_centralities(
        g, dist, cent, measure_closeness< Result >(g, DistanceMap()));
}

} /* namespace boost */

#endif

/* closeness_centrality.hpp
ROimZCUUK48mvWixr1qa2Z46V7bjjtLejPxN88Hh0ERthwE5Sk3V06UgsdG3Yi7ViPZSvYhsn9cYLWL46r7aoC8Quj7ZoChYSrzp36XVzxtzQNNQCxto/YQwOuTIyeUtS+dBcr6YwbdSTdLwNjO97hUWXlzKuJJTi0l8bTLCtEzKOu18/8kw6LV86KP1YDL7o+t2sY4wn3SxFZXbOqObUryob0huauNug/itYqqAd+NwsQ9EWzaTZUNeP3Y+rG9Q3tNcifxegKxNIxj27YtOxqTgGZJ2gtslIfG0E+cRyQLpbGHKPpfYV8zeshlyTXABl094xyhOHc7dDUYega+y6Xqjz7UYzJ8OXMRaW8yRGIXH8vN7Z361ZxrZnHEkb7lLP+yS0GXkdjlfPuPTdIc3iTgk9QjnL27BMCHXOhFma1StqSToy3i7TukFDN9DICuxNS0ctfuY5d4xPy+WG/DThj7rOuazSEn/K1sOYta+fhuJbfa/WiuNNodCA+oWMdo+udsf8tOT891303XJG+8Y2Z4NxLXxJYax0WAEnQ/30en7CX9uQHy7k0mbr899TCMFDA2mM44CLGXODEYivAO3iZMXE4jdaCf77hQAACz/0658junKcnh0kFHwm/7PVdOmptDrJuMGEmpRXNJ/Nz++QTSjVvvumm+i2h4OMpMSxdRjn5u+tZppq1LS+tAWZxF49YFE4+cii8bG14nZ/tQ76I9WqRdBQmeqWIJcwxN5ixiR7490hl+m6C8q13OoJyh6ZwrgzzdfD0XZ1hlzEJspJ0TVpgifFlCZmtDKCXAai76Blhwqenw0O6q15XleJSA6UFrDKq3S178/9XPxNaqmdax0+XPbnmDBNYVobEtKnZ52W9Lo0G1K9wf5gwPG46cz874CFVRUQqiQthSXy/MJWZyFU9dbnlyBl/d7T9tbFy+0V47p3qU7+Z28kOG4e7P4jrWCInn+KuhRAnGEHa1OWEzJIFOFjIhLHO3QilKylMsg/8wnbkmzZzcq+T6JIkufagXVUK+zuc49nIS4GwkDn5160BMfCN9o//MnZn4+RPEqC9XSPtmed28uevVHnp/Yk0FLMkvxojcVIVqqirrKsmEvxzoLNH8llZwZv3ls9PS9Wrjpfzm9CVa1a5MCc3dt3pXeNz1hSii1cNUpXpT8Yga77ZxP94ovyo2owSNoqeBOAetbkwHOZDU9o7dldxIjrd44k6ZdPoWmdFwsaC7YuqaG6X9KyCds5jkkWdl9KALkSjhE600Waj8uWVDwDPjbayT2VsSunla4Sgm/Zz3sM2hp9BUJ+B3EZxb6qLjmcT1ln3t5wxS/vp/YVDy+0+ZZzGNVaJHPiHuaBNHzvap3I32Ov96WMmxQi+ti7j2uZJw2fL/rnx1f8Z5Dypp1BndSXPR6d6RxMoTPperthlhWOkcNfaLoi5u52XepncWEYjGPS+z+wF1hBVij98M0KXnTwM5tw3FOPf9vKkWCWgdT5HKrLfk/pI4KRvnTvzyYNXrFdLCDFjyNdJOQPzuWZEUqhQVBF/qF/ZN0I+aaa4+YfzQwqqnP13wRtzu/XguZ18aw+AawJZVfvxnvaOp7IPbA6g3zFzL2WazXvUyr7IbboRmeYVM5faaBdtZny40kyakvhz47EKC2XopKHAqscl69j5SVe+KNRr6YsEQ94YYrH1k500ouOpj+Vxd5ZBnWoqU0u/lHVt3nUbIpTItJr2MEP+NdXpLl8+El48EpWzL5TfX7jqZ7kT/Nzmudh5h6/S6T/PaJGJlHxpTuWvkZZ8KS/QuT02QDD/xp2rZ4nbflHCk1GIYf21m8K078V9VI0nLJhcQqvlNFcG4ajvikziDSHrgstjnASmRCWGXKOwT5OyS5rqP0vTjE7pLErDYVcn36o5Bp+GsmsuKRkTOLEHNmy8irw4NJ3671Ky0pl4wXfUySz3/8phhlpwl5HqTHxL/RutKtm+H/kOVj75zY0h/yPKDIckoe+7RMb4m8wuYHt2JUMfuAexlPYvlOgufVsaGKRrLARZX3GodPPu6RTd6cTRuDiaiJO/O9sgXfrZee2UH7mYgEsUCuTnxOMX4l/YeahfRI/JnPlhc7bEwpsPfs2dJBNuRGldTtoHjiROhqie3zfYt7lO8U6KL7Plob1Hy+V58V9zV+ZPnoE+iOnYbSO/gvzwdzMnZuo8GFVpSfrFInO8uSS6pouBFWdzadXqWAUFS6pjO1zo9LvisLzzr5CTgrPw+Y5dd+mLf5tLTSrwJN6W8tX/ridnouH/NN5/2JjNcSkdFOr6RmJD3D8J9H8t4rTsn9AHrNBDNs9fZ0GIMUhrH1FZlmNPdU+ALkt5uFfdDkTCih6XouXzeJvorBzfGsvy+jNSd2Lm7x1+T0MdLucXrI5S6/vSnazVfNcqkJmG674nqRwV8bxpK2W5R0L+pL3lNhB85d8aU8qslXJ6QxVdKBPvRbsO8h2OAkY+UoZAYqgF2VUJzh+uwsI1FDbjXwbOkxu9uv8ATTiBTpL7OPg/Sz8Dn/PRQipImRGrI0wmTOPv9WGs99/lFI9LsvR+lsbUr8hRv3AMWBeUxN5G675suM49Y6vvdSHrlZqlGMK/vG+I8zlEJyY0mfZAQDD8/6CH9bS9hQej8gLIMx3ryZx5gpqgmm2Yim1Vp1LTAbh+kOpYJjU2wnpa6pWXgy9o7q9+p9o59erN8nNNxFMr3Sd2jdOb5uru0mnlSXi24wCyinPf4Uf39700cPZjmIl7wjSSUqX5LCSLlYzfxydMNsrI/Jend1QGg9vJ5XfvJinkdSf6uszziN+aDh+UBDb5X90L3Pzn/czorusq5cLlp+eh5ack6zWuz1gI+vJ4DrleqJXeHisiT+nosimy51pLIzhkKWjpe7JNSoKsBHtM/Jfl7Ejn5Trdliu9+t1d2QoJdzccexa/3rb7PeZtenoPFbCUMft19SYO9NN0Yq5w8MRjm+7HvL87S243nxFS1Vcy+SdWBlNGXb/8m+BM8MXc+dx25Jud9l9ru3tS57cOL85JmaP+L2vje8jJ6kmGPQ/8B4qOnZYOSzqm30F3ypcsaZRSb26fH8oHKZjoSN642fMa0hvSH6dsvQyp30tbrCFIUkASS66ENS+oWnZMzIHe2179bGrs8r5+32VH+pR3soNSwpG+COU38zezJ/MKD/Gf/EqhjcsR66GlttUv6K+yK7yeEjMlbQhy5i2GHp2+X6bO+DzQo9D1GDhvUV6YNv7mXvT0fg+KEBubCLJbJy87CTK3zYCotuLXqG8+ZhjvoTHwcB0L1f/7kMfOcpYn3h2emVzHrkEZ43yMmUzDnCkTB9Vi7OwplU0yeix6l0rEUvuPAup7Ct3w26OfjT437hbK2buj/u97SFj47BWdV/Nyx/Cj7pPJljZHvcpUDinDdn2va73swnSO2nAQJfq0WIEz9qvwGRaztNpcEM9iht78Qv9i1078Mypz8wcf42FRzy/PDAY8Dk2C6LSaJB9oCVYUCOcd5vfqV9I4EGKMZ+eFt2TTXUFRtc+Xi3OYqUqPXWcWwoh1urpE1neljUnRyG9mdieQeNuZvcGzzNo6bvA4aTJxQbPz2PPNMIff78pHGhgmQPRavQZWIxNJTa/fhGpz/pU3di6nhG6viR7u9j3rJtPy/C0BgL+Zfvkym1Ljhrv/0vqsaDI1jRQkuEqhvPQO22iSVn5e+O8FPGJF3WgS6wTE/Cxk58hJaAiCkNduJIV9M5YDsaXqdUI5HTVdWgg41zBgulHTzaUpt/vzv2szr94kUeZ93N9BRR3sPbarsHJ58kryLbeOiPO/1k1wOPG47HLCZYvYpULpL/kvkMYlo/CBsG6tk0PfniMShJp+O5JnWz9vcU3RbEk3MIfms5wFvYn77/PNxnr3zIDp3nRn+H1V4Uo5TdnO9fGiX3ZOrMrtGvuE4h8D9OWOP6CO2OY5Jvk7MX5lblYp1rQqB7trGvTYfE91eDVzSAOl8HpfIsT278C7sUEkJW0/NqG8bqB7w/YZENjEjR3NDAq9ZRye6b3/QTehQjUtJr8T0FDwoUh8XkdmWjvVpYCl1UBa0WA1KHig2WPoYsPyfhfGjx2O8vJuYgkXEzsjYrhXfWi/XBYTpjkpj8ZW8m3vqMxiyh6jIlJo6MitGU9s9Gn5arlZsWCGJEWRbU9xYvxKLmyHUG2xCmYRZNlLhrHWjetdWvaiDDc+Y+0VKa6jw2XCAN4Rk2xgf9ibp1apx1yFXd6UF+yHD49Ane8sOV3mjz/cMjBwdYOLZp8NU87nsEaHngx9ZJR8R3foOc8/RcE3VV+azLHjvi7VDO2TI/TX6J0IGOGKlR5v7fZkoTZ3nXutUm1WWJsL4q54G4okr6IIRwiyDLfxa8YvcmAn4XUzJEq112xE64JEyIrdrVe/aZjH9ME5cLvP74uNWFcgP7X1bBUdDixsUrctNRHRN5dvWXufTuecihZXt6jPzbCnaCAf5d2KQoNqYsq/6HaWFEhVuj3qYvP1+FLvArYvADL3l2f3O/KtxLzeScR6fq9QA5nvLQW4Ppjjy+uZgk6sNJde4Zrftn7UyokL8wvpe3LARDp5toTjNCSfNWc1X+7c335dYvFQLBtqOzEQUcjQ47sWTnPZEMQi9h4ixt9bRCTeVL37aKkqmcyUqcwm2ZI07uF7jKuLk/VVV4v2pJ/5/075Alna4XWTuFvw1vJY2a31dEl8U0yytfN0xcc4e+uJcTX1t/A8n/8fnpwbNOySrWzwqyIn32BwfpHsLu+cbicuH920vLBUXSP/OMBV1bsqpE1rTdMw9b79X2jRZVbL/d+G/B2mskUee12H5q2mo3pfLgAeYwevS3s993LpM43S6vePHaELOTJ2Xkjwfpkh4crD856hWT+vGykEO8pevP5Jc24d77XG2z74Zkd5BAUBpkRSTK4iHNwvfBny1Km1bd8dProxq2Uc+NwkTyzBgEz6q5ft7Oty/Pk/EYNkqXLZ8yzJRuelrmIeujh4xkf8Ed87YuSiqn5VBtCV3sQDvIScUYwuTCx2J3aqdRE3TnDvOD8kkBVAIjw1OWcI7wA2p/78RDLnpVKBTZvkxsl6PyvOdpwXprY71Dv1fKc1MY+oHWjUpjb3R/6whLeJYYnxmdVcDphL9cvXW9VszoXPMTncv07qpF+5Qa2RtOIt9dIa+jj2mvrZgSY30MBOEZkV/sdqNeR3hoQvWpr9+lPMBFVJA4cJ121dQjhzxU6z5RJOYjsfbgvl9hsYKePuWjjcxIVf38Nav8K/bmtJPDpf9kmTwfj+M1D6TGm8Pe8mO+Jxa+lIupQmaNjVHvei3dtXKtXTTffujA/YJmOvelGzh4rfznDatQidV/PGIO1GZ3lB/uPCzZ6TwYb+3WiSzrv/79SnZ+vCpJb5FdIPxcrnxd4cfzFd6tJTv2Dbnguy8meYJerNertU7x9TNEr343sZNjOmLzeYEK9lc5GLcnifqRS3D+NGH42P/HLG8/2aaffYoUy+F3ejIqd28R0Ht4K8rZcINohHRzdnmAD+OziDX12k+421Nf23bjPvu2oNpqdi64ae6qPv/ep2+rD8oa591cjP7iFjuJHxicel4/Shz1bzDuv7SwMLCUloUnbBR5NjaISL9/wHYmB2EhKt9OetH/7LegPdvnvns3XzNVqinB4DepE8eaMqdzv+S09pW/9wHCom9JhC0qEymLCnZfRn1FkeMybJUZk2Sih90ZntqsiMG0UX5nrs/dEI++xfbagxNSEwEVkE/RFNjqOPMdkeNME3tGgg1P/SX/QzaXPanXPBYFqUYP3Tu63/fhOHLcxIgP5D6Kyt5SMMcQuqjlZNql+FRfHvuodrOCf3TqfPjxuaupPH2sTrIFAiHE3jkl/UJOTsnwkC8d+It8N2c7Iu5C1f2lo++Eh151gQC7mY0kG76zQ43raKKlU+MNewSJ4GLoAs7NBHylzNylXOZI12QRKijLz93gCFIG4H8vuKTMnki5yNK0S4Aesp1LqD7diOMDCgH5iFyse7ZPVyOonJQur1MJ8aaBJe4QRZynpoS4NfFJtSi0toLdkWWPpLvyKtvpaXdLnHcTSMKLhTu4tp6Szj3nUWUhI537z0ft4AjOe/4P9TlBWbUQx5Ba9onyT4g+ohLImkRXcN0Pbok6iHHvwzeDCAYaJcOPTnGG4IdOQu05oXV260cPEY8htVNloH/2Mk11/nQ0YNyJefdURFBHZfG2iGC8DITqjBmhSuKUqHaUmh3AJ8gz1jlHUwuIqPWAZVnaL0AjbPB4UxX+38cQJYfAyl5Tuo3WXqTNq2582lUFDkQbCTskFYfz1kBLT8NuEJBt0qtDTgToEjwzIg1tX209hsTNBCCIjyBD7MqVI1Avm8VU173xYDxoG0LnkvqwxlDHcBe5AxEM2EbmbgvBqcJh/HeKQwNAIaU+JbSltSJAED6NEA5Lp2R9iBZgPFI9DcObizAfamA7DIX1Y8GV3ITuAzUcmH4oy8aDY+8Rtp1Lf7U3KCZaHxEDvtqTRZxBnh7gedYfdCiPtdGTmkP1oyDsyv92a8YCEaExEP03Ish1yNilLxW3hkOG0p0FWm6oStxD+EXIhSxibuWMsvImGQdg8LQqN2a3LZDMEG38s/FGxG1O0qeXqhLm0Ps0jqsbEFeqPdNJQw59XYFImN7u7D+p4HCZQ9I9xUou0pPZTdAhqXDaGciw4d/tD+0C8hr8MBVGc1RAQH6nXKjrBRevRkC22EXuk9Q4dhOlyP21JgDE19SELVuCIHSPuKRkDX5pZgHrNitlaTeMhQCbwKrlv6cWWsfLIOAUQFVBN+B0FmKERfwmG7Oq9wWvt34tWed95o4QTBR3jT/9ZxUKUZNbqvlPXSu86W8xq95XCUb4852MqhMhjflOhlWJsoT5GhIjbq3cebqWFHMr0+7pWnzTrSXd74hFIz7XgJBbohXx7XL05OkMyQj1ToaT0BhkmQEYyg/shsOt3H1vEChvmeeRyyqvUXfH0EbzZ5nQdS2ecVJBGjUJECdp2y4S1Hmf57LyvvnlUzpjkmqzW5gXcWuB9FsQOqDZAc+ig+e5bJun8wsHnMJbMQrhSqmwIcI7CoaGe134ZIQHQw30LPTznw9jSmdZgy0NNIggLRgK3QL9Cl6xZMe/t/MRcfIZpUVr4EDEW5A0LKxcAxMghasIgO6YEZ2KfZm/q2rOMwSnv+V4jJsvaqNFY3zDLFA/IndoMTdb905q/O/U+OuDgV8zc8Ttw3SgW7Wg7ARibuH13YBPL2Y32OArryRUBnx9B/0Cw4EcAjWBtP4s9uY74Hcb3oAiTcq2AJRSlPIqqmA29FfZlsBRRRWcfBrDQ5DIf5FdByceugtfcbnQWhgTBAWNgmSzYy3aDMKi4ceN/X8vc/3/eefRNGkdB0BPUOAbx49ff4fPycOlcHGvquAiGJdj3MENzI8+8ibKDAu7b0qE8nvXPrUEt/aHcpGuPX4IMowBnWSQIjapQEMCoOx4YIU00JrmhIITokixbLTRPnX+hOZKghBgTsoBobkhAeSLgFycciSM4S2mwwdwWK5v+I6BnDHzXEY5+EBjbmgpklU+HTy4OsfCErGHiiCft6A5UvWbIQ6QneWb
*/