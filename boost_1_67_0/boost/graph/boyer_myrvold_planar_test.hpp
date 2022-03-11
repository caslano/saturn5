//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __BOYER_MYRVOLD_PLANAR_TEST_HPP__
#define __BOYER_MYRVOLD_PLANAR_TEST_HPP__

#include <boost/graph/planar_detail/boyer_myrvold_impl.hpp>
#include <boost/parameter.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>

namespace boost
{

struct no_kuratowski_subgraph_isolation
{
};
struct no_planar_embedding
{
};

namespace boyer_myrvold_params
{

    BOOST_PARAMETER_KEYWORD(tag, graph)
    BOOST_PARAMETER_KEYWORD(tag, embedding)
    BOOST_PARAMETER_KEYWORD(tag, kuratowski_subgraph)
    BOOST_PARAMETER_KEYWORD(tag, vertex_index_map)
    BOOST_PARAMETER_KEYWORD(tag, edge_index_map)

    typedef parameter::parameters< parameter::required< tag::graph >,
        tag::embedding, tag::kuratowski_subgraph, tag::vertex_index_map,
        tag::edge_index_map >
        boyer_myrvold_params_t;

    namespace core
    {

        template < typename ArgumentPack >
        bool dispatched_boyer_myrvold(
            ArgumentPack const& args, mpl::true_, mpl::true_)
        {
            // Dispatch for no planar embedding, no kuratowski subgraph
            // isolation

            typedef typename remove_const< typename parameter::value_type<
                ArgumentPack, tag::graph >::type >::type graph_t;

            typedef typename property_map< graph_t, vertex_index_t >::const_type
                vertex_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::vertex_index_map, vertex_default_index_map_t >::type
                vertex_index_map_t;

            graph_t const& g = args[graph];
            vertex_default_index_map_t v_d_map = get(vertex_index, g);
            vertex_index_map_t v_i_map = args[vertex_index_map | v_d_map];
            boyer_myrvold_impl< graph_t, vertex_index_map_t,
                graph::detail::no_old_handles, graph::detail::no_embedding >
                planarity_tester(g, v_i_map);

            return planarity_tester.is_planar() ? true : false;
        }

        template < typename ArgumentPack >
        bool dispatched_boyer_myrvold(
            ArgumentPack const& args, mpl::true_, mpl::false_)
        {
            // Dispatch for no planar embedding, kuratowski subgraph isolation
            typedef typename remove_const< typename parameter::value_type<
                ArgumentPack, tag::graph >::type >::type graph_t;

            typedef typename property_map< graph_t, vertex_index_t >::const_type
                vertex_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::vertex_index_map, vertex_default_index_map_t >::type
                vertex_index_map_t;

            typedef typename property_map< graph_t, edge_index_t >::const_type
                edge_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::edge_index_map, edge_default_index_map_t >::type
                edge_index_map_t;

            graph_t const& g = args[graph];
            vertex_default_index_map_t v_d_map = get(vertex_index, g);
            vertex_index_map_t v_i_map = args[vertex_index_map | v_d_map];
            edge_default_index_map_t e_d_map = get(edge_index, g);
            edge_index_map_t e_i_map = args[edge_index_map | e_d_map];
            boyer_myrvold_impl< graph_t, vertex_index_map_t,
                graph::detail::store_old_handles, graph::detail::no_embedding >
                planarity_tester(g, v_i_map);

            if (planarity_tester.is_planar())
                return true;
            else
            {
                planarity_tester.extract_kuratowski_subgraph(
                    args[kuratowski_subgraph], e_i_map);
                return false;
            }
        }

        template < typename ArgumentPack >
        bool dispatched_boyer_myrvold(
            ArgumentPack const& args, mpl::false_, mpl::true_)
        {
            // Dispatch for planar embedding, no kuratowski subgraph isolation
            typedef typename remove_const< typename parameter::value_type<
                ArgumentPack, tag::graph >::type >::type graph_t;

            typedef typename property_map< graph_t, vertex_index_t >::const_type
                vertex_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::vertex_index_map, vertex_default_index_map_t >::type
                vertex_index_map_t;

            graph_t const& g = args[graph];
            vertex_default_index_map_t v_d_map = get(vertex_index, g);
            vertex_index_map_t v_i_map = args[vertex_index_map | v_d_map];
            boyer_myrvold_impl< graph_t, vertex_index_map_t,
                graph::detail::no_old_handles,
#ifdef BOOST_GRAPH_PREFER_STD_LIB
                graph::detail::std_list
#else
                graph::detail::recursive_lazy_list
#endif
                >
                planarity_tester(g, v_i_map);

            if (planarity_tester.is_planar())
            {
                planarity_tester.make_edge_permutation(args[embedding]);
                return true;
            }
            else
                return false;
        }

        template < typename ArgumentPack >
        bool dispatched_boyer_myrvold(
            ArgumentPack const& args, mpl::false_, mpl::false_)
        {
            // Dispatch for planar embedding, kuratowski subgraph isolation
            typedef typename remove_const< typename parameter::value_type<
                ArgumentPack, tag::graph >::type >::type graph_t;

            typedef typename property_map< graph_t, vertex_index_t >::const_type
                vertex_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::vertex_index_map, vertex_default_index_map_t >::type
                vertex_index_map_t;

            typedef typename property_map< graph_t, edge_index_t >::const_type
                edge_default_index_map_t;

            typedef typename parameter::value_type< ArgumentPack,
                tag::edge_index_map, edge_default_index_map_t >::type
                edge_index_map_t;

            graph_t const& g = args[graph];
            vertex_default_index_map_t v_d_map = get(vertex_index, g);
            vertex_index_map_t v_i_map = args[vertex_index_map | v_d_map];
            edge_default_index_map_t e_d_map = get(edge_index, g);
            edge_index_map_t e_i_map = args[edge_index_map | e_d_map];
            boyer_myrvold_impl< graph_t, vertex_index_map_t,
                graph::detail::store_old_handles,
#ifdef BOOST_BGL_PREFER_STD_LIB
                graph::detail::std_list
#else
                graph::detail::recursive_lazy_list
#endif
                >
                planarity_tester(g, v_i_map);

            if (planarity_tester.is_planar())
            {
                planarity_tester.make_edge_permutation(args[embedding]);
                return true;
            }
            else
            {
                planarity_tester.extract_kuratowski_subgraph(
                    args[kuratowski_subgraph], e_i_map);
                return false;
            }
        }

        template < typename ArgumentPack >
        bool boyer_myrvold_planarity_test(ArgumentPack const& args)
        {

            typedef typename parameter::binding< ArgumentPack,
                tag::kuratowski_subgraph,
                const no_kuratowski_subgraph_isolation& >::type
                kuratowski_arg_t;

            typedef typename parameter::binding< ArgumentPack, tag::embedding,
                const no_planar_embedding& >::type embedding_arg_t;

            return dispatched_boyer_myrvold(args,
                boost::is_same< embedding_arg_t, const no_planar_embedding& >(),
                boost::is_same< kuratowski_arg_t,
                    const no_kuratowski_subgraph_isolation& >());
        }

    } // namespace core

} // namespace boyer_myrvold_params

template < typename A0 > bool boyer_myrvold_planarity_test(A0 const& arg0)
{
    return boyer_myrvold_params::core::boyer_myrvold_planarity_test(
        boyer_myrvold_params::boyer_myrvold_params_t()(arg0));
}

template < typename A0, typename A1 >
//  bool boyer_myrvold_planarity_test(A0 const& arg0, A1 const& arg1)
bool boyer_myrvold_planarity_test(A0 const& arg0, A1 const& arg1)
{
    return boyer_myrvold_params::core::boyer_myrvold_planarity_test(
        boyer_myrvold_params::boyer_myrvold_params_t()(arg0, arg1));
}

template < typename A0, typename A1, typename A2 >
bool boyer_myrvold_planarity_test(
    A0 const& arg0, A1 const& arg1, A2 const& arg2)
{
    return boyer_myrvold_params::core::boyer_myrvold_planarity_test(
        boyer_myrvold_params::boyer_myrvold_params_t()(arg0, arg1, arg2));
}

template < typename A0, typename A1, typename A2, typename A3 >
bool boyer_myrvold_planarity_test(
    A0 const& arg0, A1 const& arg1, A2 const& arg2, A3 const& arg3)
{
    return boyer_myrvold_params::core::boyer_myrvold_planarity_test(
        boyer_myrvold_params::boyer_myrvold_params_t()(arg0, arg1, arg2, arg3));
}

template < typename A0, typename A1, typename A2, typename A3, typename A4 >
bool boyer_myrvold_planarity_test(A0 const& arg0, A1 const& arg1,
    A2 const& arg2, A3 const& arg3, A4 const& arg4)
{
    return boyer_myrvold_params::core::boyer_myrvold_planarity_test(
        boyer_myrvold_params::boyer_myrvold_params_t()(
            arg0, arg1, arg2, arg3, arg4));
}

}

#endif //__BOYER_MYRVOLD_PLANAR_TEST_HPP__

/* boyer_myrvold_planar_test.hpp
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
*/