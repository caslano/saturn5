// Copyright 2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP
#define BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP

#include <vector>
#include <boost/assert.hpp>
#include <boost/graph/loop_erased_random_walk.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/named_function_params.hpp>

namespace boost
{

namespace detail
{
    // Use Wilson's algorithm (based on loop-free random walks) to generate a
    // random spanning tree.  The distribution of edges used is controlled by
    // the next_edge() function, so this version allows either weighted or
    // unweighted selection of trees.
    // Algorithm is from http://en.wikipedia.org/wiki/Uniform_spanning_tree
    template < typename Graph, typename PredMap, typename ColorMap,
        typename NextEdge >
    void random_spanning_tree_internal(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s, PredMap pred,
        ColorMap color, NextEdge next_edge)
    {
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

        BOOST_ASSERT(num_vertices(g)
            >= 1); // g must also be undirected (or symmetric) and connected

        typedef color_traits< typename property_traits< ColorMap >::value_type >
            color_gen;
        BGL_FORALL_VERTICES_T(v, g, Graph) put(color, v, color_gen::white());

        std::vector< vertex_descriptor > path;

        put(color, s, color_gen::black());
        put(pred, s, graph_traits< Graph >::null_vertex());

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            if (get(color, v) != color_gen::white())
                continue;
            loop_erased_random_walk(g, v, next_edge, color, path);
            for (typename std::vector<
                     vertex_descriptor >::const_reverse_iterator i
                 = path.rbegin();
                 boost::next(i)
                 != (typename std::vector<
                     vertex_descriptor >::const_reverse_iterator)path.rend();
                 ++i)
            {
                typename std::vector<
                    vertex_descriptor >::const_reverse_iterator j
                    = i;
                ++j;
                BOOST_ASSERT(get(color, *j) == color_gen::gray());
                put(color, *j, color_gen::black());
                put(pred, *j, *i);
            }
        }
    }
}

// Compute a uniformly-distributed spanning tree on a graph.  Use Wilson's
// algorithm:
// @inproceedings{wilson96generating,
//    author = {Wilson, David Bruce},
//    title = {Generating random spanning trees more quickly than the cover
//    time}, booktitle = {STOC '96: Proceedings of the twenty-eighth annual ACM
//    symposium on Theory of computing}, year = {1996}, isbn = {0-89791-785-5},
//    pages = {296--303},
//    location = {Philadelphia, Pennsylvania, United States},
//    doi = {http://doi.acm.org/10.1145/237814.237880},
//    publisher = {ACM},
//    address = {New York, NY, USA},
//  }
//
template < typename Graph, typename Gen, typename PredMap, typename ColorMap >
void random_spanning_tree(const Graph& g, Gen& gen,
    typename graph_traits< Graph >::vertex_descriptor root, PredMap pred,
    static_property_map< double >, ColorMap color)
{
    unweighted_random_out_edge_gen< Graph, Gen > random_oe(gen);
    detail::random_spanning_tree_internal(g, root, pred, color, random_oe);
}

// Compute a weight-distributed spanning tree on a graph.
template < typename Graph, typename Gen, typename PredMap, typename WeightMap,
    typename ColorMap >
void random_spanning_tree(const Graph& g, Gen& gen,
    typename graph_traits< Graph >::vertex_descriptor root, PredMap pred,
    WeightMap weight, ColorMap color)
{
    weighted_random_out_edge_gen< Graph, WeightMap, Gen > random_oe(
        weight, gen);
    detail::random_spanning_tree_internal(g, root, pred, color, random_oe);
}

template < typename Graph, typename Gen, typename P, typename T, typename R >
void random_spanning_tree(
    const Graph& g, Gen& gen, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
    vertex_descriptor default_vertex = *vertices(g).first;
    vertex_descriptor start_vertex = arg_pack[_root_vertex | default_vertex];
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map >::type pred_map
        = arg_pack[_predecessor_map];
    static_property_map< double > default_weight_map(1.);
    typename boost::parameter::value_type< arg_pack_type,
        boost::graph::keywords::tag::weight_map,
        static_property_map< double > >::type e_w_map
        = arg_pack[_weight_map | default_weight_map];
    typename boost::detail::map_maker< Graph, arg_pack_type,
        boost::graph::keywords::tag::color_map,
        boost::default_color_type >::map_type c_map
        = boost::detail::make_color_map_from_arg_pack(g, arg_pack);
    random_spanning_tree(g, gen, start_vertex, pred_map, e_w_map, c_map);
}
}

#include <boost/graph/iteration_macros_undef.hpp>

#endif // BOOST_GRAPH_RANDOM_SPANNING_TREE_HPP

/* random_spanning_tree.hpp
0NDsLCJtN97HtMg/P60oGkBJ4riFQuAIUFODWWnhgh19eBf+y3FLhcC3Wb4xZPPK135SUNwuGEZux5u448eEoHE7rzTx0p77P9UcSRSlv7sMme42nSEGvmhKiYHPbAy9CzLamH/dh0tr1N8MxL7W/z2JfU3xGVLytDkpi5bJlCbf8ZOspd1Gaun5v2hbosuhI1UGXcY4MmtY7WeMFIhGUmPIoJFxihlvgo9upuDUS/wUIT0Wt5JXLp5x0qDrz3MnnDSo6fYK5nYtSwyFYIQKOKjp3dwE0NRhq3HFShPuvHpBsVWs/3nKAN9buMKdMPXXm2gLOGjRPbQ3gZ3fLd24JXlCR/sX2MpZzHxo0N+gGB8IG3HLxg1r525uR8XvC8UAIuzmdihYC9S/rB33ixYT7VYaFes11BGN4BZSqItS8g6xcc6LDRSavOKwkTTqXtTB5Wd82L5lVA30g/IU7/OaSA8e9PwvqdxO+N7BdNJbulFYP28kfRnHPJ6N2cxUUSzGRtmJ+u0iKndbo3ylTx3k12kGmX6M07VjPF7Fxri/Lz7G/46wMfYtSD/GPkN8jK9FzjDGdw3qGB+rOsMYNTTh7WU0ESqrUKyT4YdivQr+bqa4Q/RwRK+a3A7oKqc3KUejmoc9H55S/paQ6QlDmmWx+hQR9i/YAnP8LWmB7VsITUpukjhaGOKtZllixSpWB2vlFtbKi39OauWJhZplmr7+qZNU/0es/pTkUfz07PXfYPVf0FN9/38l1T/v7PUfZPW3s/pfvJBU/4N7z1rfweqPBMKG+t6/JM8/uX5ynm/FeiXUxUTfZjTFWnOv4ez5x4+doN4u1GfQz3rRxxAQbtWTaWdur0ZPzNenxpGTXAUeEFiUbNopBnXksh80a+NHuu1qMmqefVS4gzptPBMQRGqXz2epXcL36xAawayup59PyqUQ86+Zj/nfsmKxfvHKwoIQsD1Kd8fy0l8hLGeaE6DoyvqjNv4uDHOChfyMK+v4rCytbyQ955Ofx+CHYUPQS79ZcdRh5LfS8ixLajCHIZSTOCmXUvq7ymJFkHZRNOavQMVbsYBiLlKQIF6argZeECv3gxL8Q14aIjj28dIOkRM/8Upb5OGE6unlguFz9wQY2HVOoXKLYDgt2PfBsKMXoMkq+v1OxpRY+Ws9Ol5pxMjfCsaHW/m46kSSuKFsZJeU2svJcx33L0XpOl5QIz1Mr0gaN2pTOO73Y+O+/Vc07or4uPmkcY/AfEkbZjOfZRuOfTCNulEd+PpzGTiN3TSI4un8zKwL/MzCUkbXpfhL9fcRLsNtSDnLpullBIjkKd/9e73uUdqwyZ/egxPoZQEPr3gGAx7myM89hY503cwLj5df/V2GgIe83AKvAD7Q24NAwqVqGouZAN2ZhfAbb3Wc8IkRPIEJl8KASoHjlt4InxUsrBE8R28sqbSCfRSoP53qZzl9qPnMJB/FT4n7J7tA3xZDLpsYdBVy68Oe4qa1q9G0yb02GGRqvIVC/4UwwqQLRoKRJWHhhlwwEheMBCgg6KrwomeFi6dwo7ie8aOA/XKyD2QCqFRCU2ijPMsJ/3lqGiMKhij2YDk2xQd/i0Ymkmnr8RxgSEFUEYOrf5NwP9yumsIkOQPE7GFU/7ZOuvPfwwe2cUJjLRnYOnbj5fWe6A9FyWVDK5m2Ln7T3/6L/eOPf8K3HeYdzYuHCFItb68VHeFrQyOzFhsExP3MrOIevEn3IgKXDJK7FxjIiZ8SFwdeIMOMZIsNxbr4G+Q4pqknDDrVwMY69vmYqW7b3Qbdo2hI9iZLzCe9oKYeU835pP+hptBV6AJMxWtZBGMfjoExd5Kh7bvyeBwCvQHocvKT0GADaAvBK9ElTAzeZeEDpyw8V9o3rcGI/iQpljixuFj329AxEdsYIN94NzZZCYujsdTGQfcN/XPdqvw2sPlJmrJ0wodMMLBNkTpgfTrq0TvlEWbvb+1GXWGpHvbuafI6AEUwbqvTbv2J3zJu2+95uaKLx+2IaON2/IN5LguT9M3+8X3IY24YLiC+0sIb2oA6qkzchqzo6Hh8G6k3EFEcveiPaWB548sK0sffAUpYfhrkrBrKXyMvybSATIB0qq9h1iaDhtrVMvBa+9hrj4glaPXDTYO/rqQ4rol5sAS7kgWNANoxAg8whxJL1biAovjM3IZpiqPRT0JLYQxDMcMbztMi1UaX89JjT6reX7/C8nfzJRLC0z/UyW1oUawXfmnQIT82So3RMhFrhx4jQ+ASi2+KKM0scK69CnedIBeHALNayABpFgwY8R+QkY89gjqKKkBpub15dS0ynKA5+hKepqXNA6KGxu8Vyb+6Di/vHXVVg0BTPgFaD+UV3S7aw6KjUeCm9aIOcC1ROC6efFw8beynAZ2PDK2YLtIQ4Q07FavrCwPeqltE+8d84EGbRQzOpVoGrFUPS8imyxDP6zvmRazEvIi3ha6zyH+/y5CaFvGHGdIiKqtS8ilcfpJyjafJhnjpmnPJhpjkhxV8krw7Izi8K7DnPDxfyvaEXEaKyKNYb/gcV7LfppKEO+SkUIjhE6hb1WPownPTb1RT/cDJvsWItH3HAWmObwBpIP5KZtmq8hCx8qiTihKtwBD1HihqqZrKS3dbeMf7PDftMMPfCFEag8bUeWhELb0nj5hnQFsK+bGfG+K8iw8usDjXXm2PnodTymecLng/If9851qHVm9AfaGmh/QHNQVOwh62v07gxDh6FNRFeV4N6vLBmwiJXSyoy59q8BxkhHMdMgSXckMRC6aSnIf67PEfHmFxChq7c+JxCurxe1L8h0coTsHf4DnFf+jLYfEf4JPiFPwbVmDxHx6hOAWr8cE5xX949LvEKeg5rY3/MCcR/+EL2sEEno3Hf/iZJk7B50dyEvEfHs4c/+FhNf7DI4n4Dw9njP+QoOtm+XdkvLoNTwHpIOS1+Um5v1PzfPDAeFzrZCRCwR6OBUGvW4K0WnQMaPWRr4BWgZy46mfIwutqELIKo2ULvr+X3pcw0O6UbzwOhDwCETaCH3O/Jc6KspCp1DYwx4UbYdbwqi/LbyXOk+A6zrWXmqMXpj7k3n4fmJYoNciv3IHi+UEk6wc1JRqMk3VnzkHizJR327Wum51QyV/8EZ/fDprlXWW0y3fiJor7vUrvn22O07tT/j9riN5fLVDJfe0M0DBX8jp/vnSTJdBsJCfdFvlXz1G0JLYxvXW9Xpc+4Xb/+A00qpOMcSh+BPYfjwKw9d0I7BgveRQfHTlC8I9zko5jDAHt/vP4MbMyIEAEHGb5h/UDfhHUjD3Lw2fbAPYfiFKjPLniDIDPEPkxfRygwM/Hles8wHdHAVOvOc32FyHTG1/jN5cZ7bvZSTkLQxUy/ZbeGM9PRHySJ/apWYSS4wRJW2bf5JrNh+b/IZ76x8Ml+eZLpgXvqsZwnqm0YtQQXJdhfEDUzyrRxY93tFWNUEMapgQp7DqNh+mBN0gX9Jth+XQdpuP1G0DLD5Cza4neD1vPmcDZQAPAPVcpWrrbm1Dmw4Yg8MYqqgu0IzGt8Z2DoFa0gGLCVT8LbXEbervWZ9HoJxFbD9w5XtfgGa6LV3g4UWFuFgqne/XudWE0OAx5h8vDgDOJ8IUPLJ9kEblS73Ax5BkOXzyg90gsfW2+aPCO50OeHGYVGPL0qrbxnuOq5u5R6HYHNBzch2CO9JowtxYjBLocW1fkB3oNXM0+yv57z/iq6dFLqCr2WuLJ8d8Jv1j/PHYrSh4FlJTidrnwOBKBOo3GTw06nMPv0EbboeCoPfFRe4Z78Qgep3RcsW6HotyGW4/T20WVwM+HR0GZno1NTxICvdhPs+QZL0pexWWvNdTylb2wLS8U7N9O494eyKliXLHOhYZgCazIxpLRTqyOzWDb2AzuCprla2416EDID4vqWH8DsD+5EJ+CpuudihaGr99m0KZlAl2jqgg9GW69PRGrgNGj6hTa6Imk0OLH22K02EtLfTMRBld9L+B01eYg+/Ezoq6sQLPCDgP8OZeHu65n5CGr5NEJ5NGqc72Fm3PXqm8Ze7jvCLCH1iiwBy8Zkoa8rfJ9t6A+fk8noAfkw3KZ0NPa4DQDSXhbRWm2zIdmtwqggghcaRugo9XLldYmqAaUtU4xNFAP9cMp5FEEyly2EvE/EM1pCATZ5tDTGmtWbRKaWh7m7b2+iTgc9WGTyAgC+AzZ0CrWzw4Akhy9/mlYFZtY9Qa1CLptjcLVlCsY8UCl91Z5HOhkXVfDs4Cs9+mjg2hii2BFe1ujF9EPbk2ExCIUrpxr0HW9Dr+w80VmDMxaBo9eBu3O24t4PYAgUhXJNEhV8ao64yexGkVFL6LW2BxD7SSSqbhad5IB+Bhyup7F0yHXBNr7Ic/J5Utyqy5AhnMDL0p6gYUrc60tkhq6vtSwHK76o3+M3YwAVv5ufBmM209Lz9PX9Qg051zrPwQTGK2S03Agpxyd601GTqcZOV0Eeo28uovIaQuRU4580c1ITncOJ0YSWD6ayClHJaccQN5oIKccDTnlpJCTYfbwGMuZjKcbRaLKfI4QdQEXk6HWoQSVFSIT2o43fL1Z3CN/ZlSWE+stRmWidOdx0d5JVJaTQmUwepXKVnXC6B2d/qlYFZtgdAvSCHos8RzxF6PjZk0JXW8vH15QZaPgFDeCoMbJvwhbr65h8DI6lWhJAFpiX7k1M5DAgLSOlQO1XQU/gF36bdzb3kNxDDz/sYoBYjKjGZPJkevLVSYzCYlx9s3MjJk8W1jKvP75yhO+jrE9sBj6w1oKh9zFkqqBeiOWFPiHugInskCbUBmN38Ar78aONXwPyuIpRYEdyCJQdv0mvM8crp5ruNE59QPFevvHtCeapT4mHQn2kewp7C5uKhBLLkJinAGa+/VLiRhnkJeXNKPc3hSkwEJOinkRLDVLDyFOMcH9UFgwlRSfB7Z6dBgTNKA6V6ZqFerJptaXmt3ZW4TgApsQrCpQd8lOM7nY7RErI3xlN3qV278SoCvBUBSbJ/OPlitO4ly56vWkasSnU6RY13xE01mBKr8tBgDa/QEEbmUv70iuMpU9nYkhdgAIQZoYH3pIszzPBJGi9BCZVdgfIuSAwadPIZWqQxb34IFgySs4UN9Y+Ve0c6Vh9+ziR+zlx36sWJ/7EEfOc56PeOkoOhu0uEPT9PKew4qSOW575tiSeGR8uEs9Mlbp6hJgdsCrVmuAIWTgVaveoMA6FH5MnqigjhcyNcsGNvsH58dvOH68hN1wPDE7ccPBQlB2jV6n16W/J5Ld0GL8mmju7EzXRHju1q1exjwepZPM3O7kuxqL+npx7DXe2xxkdzVfrk3c1ZxV/70zGtd/D5H+a+mv/+ZHVf2XDkISSvCEo2mUYFEa9MrBHBBgpnX/DR9Smxg0/QUeeNHpS2CxM6+DEZeJkunRg7gxtv4WP1gUBArGCSw4H1/fx14/oL4eqH0tJN0jZDr7kE66pWaX1B04ZHSt3k8nPlJXT53TZwg0Z/XUmfFTX9y0+gDT/S7e2NWnhFxZwGUddb78Uqm6+lm9SScoYaUWlleUr9ztCrz57JPwTEcReeYjGAt76nJ9Y2GgTx02AKdqII+RHXsMdLqUR2kINsKvaIsgrd9XkGWKl/nrHkMsa9NrQFg2CjaG5K9Y/30PXfnCNmcbJpKo73fh0u+25V8Gg9fkfwYGHg0M2nZrYfDa7hgMWjUweHF3Rhg8vfu7wqDraDxU2vauaCKHX9wmcr7WId/pKe6h4EVd7uDCAvmlnxhAXn2E2UOkY4KyRZBO+yaKod+w+EF44sIcdEVKn3nfQj0MbsUg/kn0XjR0g0rpb+cbaxWF4nDQaSDeb3DOWty7X/drvc4dRCsBFIe96LF1CSXopIuF94EfsGYvYM0OhmYDjXreIKPF2AeoDTrnuYNX8hhLAj3rFzj7e9enz7E7WRubNmT69hNDag6yzHn/uuksdXcs79/8WIZBNT72sgxpBsvke5dp8/4ZmFuzUraQvsycL1cuQk60NV2aP7yrjt9l8+wuu0J7lx0ynd+VMgfmPx+buLRHnXpZWj954seUIZVNaQ/OikJDUvLEZQ9mTJ741IMZkieyeMu8xr6g1tw1szohBzAeVkqsdLzeoEsP9ECflcT7C8X4Xb3Q1tv/up7KeOMwEtpO9AdT6l05y/HqaGXX5f0TCAyh0NDa8+Q0MWCYUKe7gAOwbPDaeRnsXePX5Z74dXlXTdOKErou/xZjlHDikZmhWy4DcVAvf3I9rnhPuWj4xD2hEPRMp1C5lTeEBcMx2Cvj9fNYdiK/QymbvJkNO+IbNs8VNI7jlQYhsEXPKy0giVdWqwGzf4mSvyF2qFWQ5MZP9myH0tGL08VZdF/DH8yCyEzugBi4CW606cnHgBBl5ak5nRGvlWu0eC1MwSufiueEfYMhrDFlIJqI49AZx6HWbIPdy1Uyo400dKK5mwuE+5Jjr2vsJ5L7xYNBvF8OzbKxi+BZhWe7ZxZRT9KsRR27Z9YlGZvoku7WgrOgAOY/RAC5cVcllFPTEu2zXBXx8VBE9frvRnOwVYqbOngqkmiOTB2A5t5Lorl7vURzFXGa49PSnIvbOGwcEZ4tTngcI7iG70JzsTylpntRJYvnEpeN91KibUtqJiTYS2CNCiDGLBdaocXCW9ClaoRXQ0Ac5VaSc9xKcpAuDccionhDM3d5Q3jhugdthCmxOvVQMTdpv/Kv7cP5PfRh7t+H+6q6lUM93Nth7u06V4gf4KhdaXTZw/Xuq5pXngfPa9lzEzzPgeeBcG795BvHFa7Md3NvA2XG3644EIgo/fJF/+weFUNp8v8BPrlPk/D5o3vS45Pxl3XucUuRx8Ds10LP8HMhcpkimn7RWsZvEoB0pvTnlBL1g2eqP/mfrF+UoT6vaYA/YwuFKS181/oFaesTf0bvs6VUUcqnulCD2HNhohFowZZhDt+lDcs/DQdzunkg3Yw/kEQ3p3/xPfGBsu9hjfLfQx+F30Mflv59zAALLPTTczvqlgCz2RgG7UjLbOBF8xLgNhtr2Qstt5lXAuxmCbCbjchuYq9X7E+wmwRdrOxMootP538HfoLta8lwXjAjR0nLD85Qf/K5recztFB4rmvpDG0UnHVNs8rpF/W8YPpV3aC/GO/SXD21Bb7sBp0dNHz4bsbvY/H7OvOqE6IvZ60ZfkQHzWvUCT9ucOp/BBqWwSU1rd6vG6zTrT6hM8Lu1+R65d7oKPhh1ul82Z51fFaUc4X3G1w9ba5V+wtcq5rK3WvNDc4sncbqMY77jo+ScC/P+554wuTvYS0VfA992Pr3EYftoQ+TYPubO8+0rs59XRSdRU6dCz3a/um1Ze63LoCmxdBPGE3nuBr0dkGpgx8W+jEWfsxzNeonXiIE6vRo4ZPtWauHh5vuwhP6TboinS7E93nGRlxAyhadjnPXehwRbkNk0x14XO2m5wV4K1y7eR49qXWt1bsapiXR9TpXeXw88H3trPKkvQpsKGbF8+JwGxOF8fu8YKI0Wqhq9vr37Es9rwiZNreyg06TT2tLHjLN6lc20/lnWeL+f1/8/LM9fv9flnL/387OPxF2Fs3556AqshZKPWM4a5/58T4f2Zupz4N70/f51KJ0fSb8BV7c
*/