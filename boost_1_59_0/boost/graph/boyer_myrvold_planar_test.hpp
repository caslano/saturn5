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
rqf+S73xuz74XZ/9rqE/9dRF/e+/W/13dCrCYJ2KRFgLkIjqATJhI0BGaFVShFZtvtCqFJ0AjbIHAPpGWJvCbQitSoPQq21/9Sryb72Kduu3XoULOhusR1nGAAYXrFV5es+1KurtboAm0gPQRWGdKtALMG/3n+tVhFZFlxwAGNKwVhUfBthSIwBDZghgwpoVU2EEYMuOASylMYCjPAEwVcYBjsokwNacBEw6I4DDdBxcUp0GOGpw0ZgB2NrTAFd7FuDq/ASX9H8CHLiQyEGAXAUCNLK/AJPMT8CuMgfYtJYBn8Yc4NZZAFT3IcCkDuvZBxC4BReWhxDAhXXtZaMFgGsKa1ubZXDF+BcgMV8AJFaLAA+ha502AL/hKrjjOAt43JYBryWsYW0hIALrUKnH40DBbhzc9ZgHUjD3gfMykLDdAvccYb3qtA3r1X2g5LF3rlklXCEg6QbHeMC61fNCt2rBGlYXbtOB2+R9loFUyDpQjFwH90I2gJw3BJQCIKDqvQc0/PbAg5A9oB++D1/DbcGwng2HwMP4DfDg5YV21X99oV+NfGeAVdgvYBC5BJ4GrwLTV4vA6dUv4Pn6F6xh18HTuCXgmLACDHwgYBy9D2xjIWCSAgGbuAPgBOfyTDgB1ulbf/Wqy4d94JqzD5zfwviHA+CafgA88+EC60efpAXgmwwBv+QTEAPr0tTCNRDyHgIBnw5BeDYEot9tgvisLfAy8wzWrRCIhXVtPFy8EFq08AD4FR+A8NJDEANrzeTSfZBSBIHEiiOQU7EO8ir3QFoFBD6WQ+BTJQTryyMQV3cEUuE6HtaT2XXbIL0e5jYfgXctRyDzvEAgq/UIZLcfgdzOI5DXBoEvtRAobYZAcQesJ1tOQHU7BPJ+HIHPPbDu7DkGX/qOQOHAESiB9WNVH6wxu2HuEOzDmrN6+BiUwbqzvvMA1HZCoGbwEDT0QqAV1qXt8HXtEOzDvOaxI1AzcgKaRiHQOwzrTri9G/b7JyDQMHUMvv88AX2wDu2HdeiPWbh9GgIDcNvQ/CkYnzsD44un55p0YgUCUzBnev4EzC4cgV9LsC6FsbnlMzALa9Ofq2dgcfMMrG6dgbW9M7C7uws2ts/A5s4p2NmDznUqQqMewRr17Aw616lI/5ONGhaRJERE+PhYWJiY6LAh/8MQ+H/jxXOBZ75+GR1VsvWncTI0/eJCfByBM0CZsRVzf8DdzwFSljUX16kvLvA/KgA6Xp2MT2s4mgy9IKyKXOC7f/Ct7pOj3VpLSfOG3x0g8JtQ19/xHB3VhsXXbP2JSL10jn/9i4/1bx1BC7vt+UHpiMP76vVzPBNBx8HB+U2qcLY1VJe++xnRAYzzQJmIDohwcS/gcjdnW011qbtCiA4u8C/n+JWLIUQ+dzZ5mtIHIfDVC/w1vDZXyC/w5YjntqaGEJQegPB+4+0QREFBcbEGwc+fmqinfJI69/aRkASgovcfIYiWltbjjXcuBI0625poqKecr/QLJATeVPp6GT6032SipaWgSICXaQ6xF6tvRcWxLvCmii6IDbabzDDB53yUebrCYvoQOozLQE0VTU2QAI+Ap78aTLixDjX4SqjqPXpkd47LIuIrdgVkZOBDiD89LYXPgM5DGITtL95UMScrJwNv8hYzLa32gp0D4uPgAGGe452I05+8vPzcTl02GzOt1rLDuTkGnuNK0BSCoKysvNVeaMV2k9Z9KyUmJigkMPACv3+0dI6rKGdl3edjY6JNnMvO+ZSdk5NTfo67jO52dsnKw/HyMjJ8bMycuzCUBZecfAgHcYOHH093ysgjTEaAj41rt7w8u6g8p7y8sBDCR+A2o3s/ZGRkZGVkFB54FS/A7aVwKSwsrrjAkayXdn/Cpzl4EI0VVRVVVVWFcKmqKG36jSNZd+3tLU3BjM6WpsaqPwYvKtHv75hNeNffm/if9geHZ3FfSVFGQECAjQfeppuMjBTU1PAXE4H/kw/+L/yGAP7z+8P/rd8c4HMMxsn/7neH/845hb0CXOYtA0gEdecu4oyCQtoEUMhbAApVK0ClawNo9O0AjakDPnd0ASBQC4BIE0CHzx6YiL+RC8LnjDsDAEtkCOCKNwIgDp9r7n4H4F47ALJdAEeuFZBJtwAipVZArgSfaeS7AZYEfA6RHoPPHvD5QnECALUBALRHANAbBUB3DFBo9gBi3X5A8XAY0Ms1AbpHfYDSbBzQWkwARpsxwAQXTpsJcMthHPDajQIc1SmAozkLLuv+ApcfzgNgOAWfL+CzhOkSoHwyBfDNlgC+xTLAt1wB121XAPXjaSD9pA+oP++HzwgzQMBnHViGjoLHcNGK3QRWr6aBw/tl8Owd/B7/uAMC06bB66xZkJA9A3wz4Hcv/L4Ngd+1ETkQeAm/k6M/Q+DNVwgkf4NAWhkEPlTD71C4VHxfA2m1WyD/+xbIroFATj38Hmw4A4U/DkHZj2NQ/eMMNPdugua+LdA0uAvaB7bA6MIJ+Ll2CpbXj8AK/M7ZRrxj9qHzd8v/sv9l/08Z4tFEQYiPh4ODhYWOjoaGhoKGQvHvRx0KNaSvr6l5/76aioqKkgqEwgXpa2kyIytAykpKv319TVIkeUjl3EfjReA3cOXMH6kpqSif+/qaDEREZKLaVioqEDo/wmciJyciumpioQah34Z9rZs0MsYsuJKQGoQlBPv6InQPIHYiMUgdwhGGfTVBPmkdRiJJSBPCkbB4pH+Ljo6WhuS6oZUmhCf70FRf/BYHG6cU7OpDeKj3zEwf6f8xiAIV9d5Di//MB/ZRZSWEEX/15OXl4uKiBmD392+W0BYAR7sASJr/9sXhJycSAF1/cLjUhgGwBSF+t6wBUOoUjAerKEnjYpNiw8uJKysjqYZ42p4/cdHhSs/hoxniESwrKa7+LGml0rLQtNmJYm/Vcd0tXxqEX6cCRgxe6DJevgLR6cwJNKaWw69lE2N4bwUXprfIG8UJvOSNOjHUVaIRamUXegCXhMov6QIxRLht1+6FqJPcixFooJFUawhD/7Gwueu2PjFyqOp2kN1Zms/4mdm1wGtwf8JxSX11pGh+REN6I9Xs5Zrj53VkMc91D5exg/S2gYdfzNm+5XXYvQODSCVWXnqXp4CXR7o2ylPcKMG36dhonz8OIqGB/hVVJI32hhTVBZyQ617XvZCykYMAi4oYEkGR81ts3APgT5WgqRpbgq+f/Vwf0lI33M0Y2G7dZNbsLwtdXhApup4glitE3q+Rrd1s7PSx6qgGJ3gHT33ZEedDg0u5Srr/yKOZDw8HsVPpHHIuBVLb0yCljrNZkffE4cTj+DCRJqGyHIiEK4rPfqnt5yvhLnAudJsQmhLscR5qMbOFomffoGgjawOmPf3SIg1Tz2LsF8HY3JU1cWfKohuvMPBWkysdHzNM0tWMq+jl14ig5jOltZqLBzHxkPbbSrwTeBlKkG7vqCkvsXtEI0kixl9q1d8Y9NHY00yS0hGlOu/jILeUPy9lrh/JxvBBZtOluKipNsnBXJMlQ1l3TFEjDrQsaY9FAxXM7Fus6F/fit273bTqR6A3Vdje4YN3i3shxXk2Zu3QT3mr1KzFyGhQ+s0OxzU2BXa2MNxHdY+lXhwDm9FI8mWPYEemF8NoNUGLotv761WrTW1z6/qJ33VRS4hDPhVi+1JtueNoPGxK0mhyYTDwzCZ/6jc7WUSYIfeewp/A6C6PUmGf1I9SFDFkTB1enR46LBSjVyRa+f5fkt2v9aVY9509Nz1jHn95Ii5R0J2iVHJLgXC2HSciEx/Zf2QtPh8j5gxXauX6N1eG5uZn17G8LuN1uBRG2p3GYHqQ5Q3TLxXWMes+yaFI4HiXc+06tUUj6+dTmYeadBrK7Ua6Z1+wQVr19DS0laKlX+pykBKP8wTZrhyZjCjNTGv/yrzk4H2zuBDyCZ8SunuiVzL5NZcisw3jWO7Xc3ISiDHbSVK/fzL6IKXwEmcit8Q7/5j1+6c18jcl1fWifVoy7+nJ6NKLzynm/yQ0RrtGyIJVwGASzvqTku+yC/UC7bIfEX83/yXq5cnKTPQ3ATbmOnw476oDNBeUSygf5xTbctCdHDwvs0W6u8nmtv/p/U1ro3ynws/VSBCWDshZDYw8rRTKL18vC6dMDq24ElJOpW0ezZJzIJYnnC0ZBUJNMn5Y8Prd3uZdk8Be+nGgmohtb69c4iUx9JPeluoR5WJ1WduSQoxIrsOjBibqfFRDVdQYntf4QYrVPDhmU6rdBshfX8y4jYrVjVlX8DHU3mgWIDJyCH8evmFwXeKaeq8UowkJo+3ppoqgFIFDQe9BUJWO+LgOXa5/3GmUmMVUx6a0u/+0DM6quOkBt8Wsvjnri+uoYvUHymcHHi+Mu9yfpYJ8dLtDC67gYUKPvLtxqNqvnguIhTfdXhxXTtq/epLdZDDGVp9BsEKauCY3KTQUnsZLcpu5mOD2CE/QBnEWK6sf5fwc/kOFDUtNfgUxlL0hMXTspfWRN/gRD17Ry24T7UzeNeh5JpQWwz3vjFOPZMS0TvQYRGA0UYag75/poSD7Lj/bkFezvDfSxnpHXL4ySl6nteoBLx1VR8VAm6MXcud8y8nZ1KO+GV8SgNN12ncqykX5s5zoOYmcnTVEwimIheaCAcRMvW5UoDtMsbRU3d1zQTPpQjKYBSZdIi0jFAZVSDnrvjmrvp0Db7mabTzIScxqbHCjkLjawXUWbjEVOXHVRnc+ocg0Ls6Fg63DGMekI/GASxYnd0IjqtxxR6o2mt3UFflcJ06jjAQHl+a1q446XN4WcKpJJPPPuh2GMgHt2a6U46x6yI6vxQWpRJ5sHhc3z+1r0Lv1+v5vhiVra0cup8kkeaUo9bHf3BW9XDhvGSWobB3zt/K3NhI02kNwaM0SAODYN7ZzY9u2bdu2bdu2bd/Ytm3bycu/eIuvZhZnMV3Tp6u7ahZ2knqan53e0TyBICrS7Yq6vBU0IxjDW+lsTA6sjq20g3HHL4MLjE/br7BYewpDBnS9nyjXOIYB8DYK1GL/9E6Sbipq3UTbhZr/IH32kQ7eN9AqyXe3VV5fioDL+Djr54FgySOii0FK5bD3WfCXrVI3L2cddWLaH5g6sF3mfAVCPcVSXQ4VxpWOnZeM+og30duvLX1rmIA6a88uQ8fSOFQzfx1cGCSe0gbv5A/7kvF7/p4ifLvnO2ppshgRMieb52xEVOdMtC3kFp7rDMcYS8fZI3gfrA26MHwIRzKyQ3AcJwHpjbnNb9hicB+UZeFFwzLm/kho+t59qG1sq/3qaR6lvsUydyQuR2feRBBT1MPiDUgaRhxWEmVoV6TwEQnPJFkztc1cpf4PFR5nuK7H9rbmhdzhQk5/6hpr3egFv+HEqci+7q7GxFtGHA+emzbKgJuFGRL5wgdxCB5ceqeF3GkPEvCyZcq8LDrOC1DazR6vyrWm19b9ZBOdpUXlK+ew5EsDOHc4m5EEu0Ja4zJ1TRGHOFcsfWcYoMzmoTy9KZQyw9ffnu3GgRM1gHCK+6rvtILJYbdaaLeuiR4tOwOY/GU4DJBtL4XOBIUrRq4v6cJ3KdokamslDuuk+PFHiTV4C8rAoQNsFV//m1w7G9NG5zJHdpvMHl6FFczk5aQIokpPWXJbBdTXsC0MVpEVFRU18jq6PYsVxvlNsa84n9Jm3OlrZkreyuprAdqrKXlFBYG9PdZUmMa01hqrT6Fl60axH5v96/zjBnDsmzFYB0f6xCXM3T2CRoNWu2qk8DFI5L0TEVZM8BNQjWOXFIYikDUUsqWuXrCSVOGXhRjd1TAhRbBJkFH6eg5jS/Nw7ZrBTZ6cMDaubJh0Ho9EJ92OSYT2yYNzNECqL6LDlWOKxwertG7LVPTaQS5fv2vfaEdma69iv5lLB5OemBjzWDTWZomQm916wI2Sz8qYrzSumKWJ4FhBCGxj2qWG44dgX8XoYWrxjkl/FtKFwfC3CN7hmGEyQd4BZMdG23d3B43KmLG/sSZBR/czShjza1Wj3QL3QCLGfRMDjBU8TFiUe4IGruW3aZ5EKHAN0OzIhvtJJBcLENI5JV8KA8/7bFLBGnIVoHSV1xYwEhnv2dhKV47NijyGWYa8RwP6vj2vfKeihA/9AK7Spd3+3AyJXXd9biLDpUYmwuTzRiXgopSvpkgkSl0wZRRMSzFFGICTTuqEEbA7f7Vf6JUt06QiF5sOtse6U8RG9W1mm6wafvSI5jdIvOoi8ITFmCTHmWoCnbRF74AZYFFeWJEclgsk7uCpbk5wKThAYlgD2IWdrb1F3bpDNSRrjd+UHHAPKJjH7mWPt9GjDlg1bPHJFPB6lacK0sJkeb6akW80dN1fbMyruLj5njoa3YntGvaHDgLd+RBSBlKelT6kgTU2D+tNOI/iHT/WH1rAjQJx0nUqH9aALztKgyNGVQsYOT63CA04GS9LVhnjblo7g8xjpXwSMnFwtCdYGQq7LYg5HS/k1h8mPlNqaCJVx0T6svCvW/f7ik/Qb8akXDN2cK2xdD7WkSceNJb4Z9CYWKg79mLfUPUougy9d04wyHq8IqISt2s9FR3nCRCypT4BJfkyHMtm4nn8V+k5sqVQGZwVcT3ilP7Guon6REwtTm5RbwCe14751ALcaGRjgQtiaY5yOWx4evlZ3VpdX/MwMQcQRiyiT2Otu/70nVpYcNdGInx62fIQeNgfSS5Bl8qWGJVsNICN1IA9txagm1mLb8O7WRj1FNG96rDFWTyx9wzosHrU7d9hg+OVgj0kzL4aNqRcFgkfqwSe8sSDT4XqWpvaELJ3BP38o4+Sb/uJFHDTUPQ5AhSl6dzmVr+gfAto3dghDL6jXN1rsdpf/QPpbrnrsZeal8RZVW6+wgaU7ML8KS9IrXKpN5GmsUgSM0GGnpIWWQLJDQctyGBQ+upVQ1HrRDp6X74dHj3zpd7tZwVQViTcaiFU6ymP+PwhQtT7tLsebMtzkjVebY+4ET9cL9pizvJXjCXJbAW980+JtQade2aMHdV6NbXCe0dwE+9RXkZMYbHVeuLeNiLaJnXqNp7qdnZSlkVZ7lNPjIPnMsd2DdLQ2jxcp3S8fYRwBkEwzgTvUmZhSd1u9uuUUkHVM0y6n+UODmjCPh7bQQHqhNlSxPwXU993gQ552TD7y1SmKqu6ih5N3vnbCnrlCPHCmTWoGUhLgywoe2j5U13F09X8JTQVGYN4q7rvUh3oYvvw4QhQ5yg4udxEOVnhDId+oYxlI6OPt8bfkUjdI1DPtaWX1hVGwVWlr5+fn4AtAIDAX0G/gn+F/Ar9FfYr/FfEr8hfUb+if8X8iv0V9yv+V8KvxF9Jv5J/pfxK/ZX2K/1Xxq/MX1m/sn/l/Mr9lfcr/1fBr8JfRb+Kf5X8Kv1V9qv8V8Wvyl9Vv6p/1fyq/VX3q/5Xw6/GX02/mn+1/Gr91far/VfHr85fXb+6f/X86v3171ffr/5fA78Gfw39Gv418mv019iv8V8TvyZ/Tf2a/jXza/bX3K/5Xwu/Fn8t/Vr+tfJr9dfar/VfG782f2392v6182v3196v/V8Hvw5/Hf06/nXy6/TX2a/zXxe/Ln9d/br+dfPr9tfdr/tfD78efz39ev718uv119uv918fvz5/ff36/gWw/bv/
*/