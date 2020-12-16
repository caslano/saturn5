// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// mpl_graph - defines a metadata implementation of the BGL immutable graph concepts

// (c) 2008 Gordon Woodhull 
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSEmpl::_1_0.txt or copy at
// http://www.boost.org/LICENSEmpl::_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED

#include <boost/msm/mpl_graph/detail/graph_implementation_interface.ipp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/back_inserter.hpp>

namespace boost {
namespace msm {
namespace mpl_graph {

// Boost Graph concepts, MPL style

// The metafunctions of the public interface rely 
// metafunctions in the graph implementation to transform the input 
// into the maps which are required to deliver results.  Since the
// maps are produced lazily and are memoized, all of the graph
// concepts can be supported with no cost until they are actually
// used.

// Each of these dispatch to the correct producer metafunctions based
// on the representation inner type tag



// IncidenceGraph
template<typename Edge, typename Graph>
struct source : 
    mpl::first<typename mpl::at<typename detail::produce_edge_st_map<typename Graph::representation, typename Graph::data>::type,Edge>::type> 
{};
template<typename Edge, typename Graph>
struct target : 
    mpl::second<typename mpl::at<typename detail::produce_edge_st_map<typename Graph::representation, typename Graph::data>::type,Edge>::type> 
{};
template<typename Vertex, typename Graph>
struct out_edges :
    mpl::fold<typename detail::produce_out_map<typename Graph::representation, Vertex, typename Graph::data>::type,
         mpl::vector<>,
         mpl::push_back<mpl::_1, mpl::first<mpl::_2> > >
{};
template<typename Vertex, typename Graph>
struct out_degree : 
    mpl::size<typename out_edges<Vertex, Graph>::type>
{};

// BidirectionalGraph
template<typename Vertex, typename Graph>
struct in_edges :
    mpl::fold<typename detail::produce_in_map<typename Graph::representation, Vertex, typename Graph::data>::type,
         mpl::vector<>,
         mpl::push_back<mpl::_1, mpl::first<mpl::_2> > >
{};
template<typename Vertex, typename Graph>
struct in_degree :
    mpl::size<typename in_edges<Vertex, Graph>::type>
{};
template<typename Vertex, typename Graph>
struct degree :
    mpl::plus<typename out_degree<Vertex, Graph>::type,typename in_degree<Vertex, Graph>::type>
{};

// AdjacencyGraph 
template<typename Vertex, typename Graph>
struct adjacent_vertices :
    mpl::transform<typename detail::produce_out_map<typename Graph::representation, Vertex, typename Graph::data>::type,
              mpl::second<mpl::_1>,
              mpl::back_inserter<mpl::vector<> > >
{};

// VertexListGraph
template<typename Graph>
struct vertices :
    detail::produce_vertex_set<typename Graph::representation, typename Graph::data>
{};
template<typename Graph>
struct num_vertices :
    mpl::size<typename vertices<Graph>::type>
{};

// EdgeListGraph
template<typename Graph>
struct edges :
    detail::produce_edge_set<typename Graph::representation, typename Graph::data>
{};
template<typename Graph>
struct num_edges :
    mpl::size<typename edges<Graph>::type>
{};
// source and target are defined in IncidenceGraph

} // mpl_graph
} // msm
} // boost

#endif // BOOST_MSM_MPL_GRAPH_MPL_GRAPH_HPP_INCLUDED

/* mpl_graph.hpp
4deRl4LPEN0xi2EuNTPwFKNMqxcuCImH6GwtKCriYCdqla/hN4XU0Ou2LfKjuJCttpfjErBasedrxGrGd7wR6jpR0GWJ/KyNRVaJlbIUjTeM2Ikf1PJ00SgIn4NYE8iU+IhLGZcrsRFPKykCBJTrQPd+c3wJWYXoe3Ti6UQfL5/Sx2UT15ZOAQc805KNMRELxYO9wxgvYRuXkFaKEzSi8Q8RfgzZ3TKcr/envVeLhnEp7q7G67P43AiX6gXOpOI1OJU71oGWNh8Kt5UjmpTj1kyHU2SX2tLmQ5LHsMbAvcy158OprBpnsS7LC1sejvjx3X4TZG8ev8M5+EbG3jzkY9hM6N78HjQZ8beLH9n2LGnSKS3f1NV95gZLQ97RFeiK20zkHn890GWaXpTB7ZobMCc1/pD5jLywxcZvwcIdGne6XwX6mGo2cQlO85JXsSVfNv32/C3Q5LxBlsDDUOSMRxuXVR96y9Xdv6GOiWcVEJwyuWuJ91yOduieKbA0P7IUsdf8rETPxpsD0cRVmSg+ZKjHxg886NG2WSgxfjtFlWi8kf/6ULOxbsZxhstpmVNvPqd6UNlOGGM7yHCbhfjY9q+uyz72nVTrDy3kMCiaObYutJaY6CsVttDaKm8jhht2BWerDntcHfvPLsLcS9BUDrWQurY6KvY5rXbk+oiQwHpaxJIR92CKJafPxaiNQAkJhlXp2v/4Gg4nFLRFxgRuGTF0/BTug9KKaTrYwFJ6aVAbl3zeMuIZIax/kSCUgmxU7Q5d1eutWr1g7hHCwVgiI3wKfECyJRWfIBR53Ckge1ey0eX+twk8rRVNDJPcu9s2RxSbv6WOOYRP9SAOcR21QRl8QLH5jfWtFeCZAOEQaxpzo1nJd/Q6ZpAIeVkrrzGUt9wPTKqxdSDS5mwRpu08yMu54Yo5672gmnscS7GrO27kQ+dc5heWYfzYLZZlSvOqsnFYjPQ1rBXjopEhvh0lcFrUlhIxS/6cKq1ESwuHjgSBGwPVjj5HFYTrySVls55RwZ4TVuezSI8liVDlGM5JbqbluXZK6jnlnZERCxpBGf28oxhxxGKV4hu4YJ9RfLfInFcBon1BkMizXx4zb1untXXRJZu5SI/3FcdxG6HlU7MO7pxvFYP6qkh7qfWGbleKsKRYoGRytR4qGsNqXP0q0vTjcb7u4BSvFd6n+HAcS2tC1mzHzSQLZGalJ7aYL2A0soaVDfinmozf2MyUCyfD/RH78O0lzl7FycYPuD8Dt+gzHF9eyR8SaH9nOjglzVisur2tbcVu/ZqNIdHbI4VO8m8Jo5RByNz+IvRxWbLwOl9++7v4JsJ3yBgOuPc+3Kq7rqN7Vw3GtH2f7K7BGH5KbzCMVS89L2dPDcbI6+s1GPKfLDAHF3SMyIbkIW826ciCfDsbNJG0tL+8yaDPmA7FRPNDtv9mhrHHiimbePMOOFU20bhHPcb0C9AvcaV3Ij1aiSoL2QtMKb8w+kppu98SRtLVNOb3JLreB6rfj3tVGLvcqq7JRzhuMsJAVeuS3Jt9v8jadCYrg3+q45JhShnLznXZ3icwO9Tlbxbdrsv8PhXmv9flLoGbcg9R9P3H9xXfuaIVyUXefD98FzrQdBBR9C38/ZJ+ESeHhkK7Q6GJgxy13Rfvz2izAU+1WyYrHPTJOBsPEBjiVnS6H8hoO79tHjkA+v/xtvlFC2fLdRYfJDCySWvfWz9o47QyLTzYoteW6b02ztKZ2f8QC0PlpnQEZuc4EmwRAub/iCPxzhqc6Zdq30MtjBVr4r0Vxgh0JIpF7+ELD6vHKUWTfnd2wJq+hQ8+HDgmnyvHvvz+2kPiOx/7dAd4raPLDvBM3c5z3DQ=
*/