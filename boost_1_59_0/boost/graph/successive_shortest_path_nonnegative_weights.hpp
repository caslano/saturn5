//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
// This algorithm is described in "Network Flows: Theory, Algorithms, and
// Applications"
// by Ahuja, Magnanti, Orlin.

#ifndef BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP
#define BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP

#include <numeric>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/augment.hpp>

namespace boost
{

namespace detail
{

    template < class Graph, class Weight, class Distance, class Reversed >
    class MapReducedWeight
    : public put_get_helper< typename property_traits< Weight >::value_type,
          MapReducedWeight< Graph, Weight, Distance, Reversed > >
    {
        typedef graph_traits< Graph > gtraits;

    public:
        typedef boost::readable_property_map_tag category;
        typedef typename property_traits< Weight >::value_type value_type;
        typedef value_type reference;
        typedef typename gtraits::edge_descriptor key_type;
        MapReducedWeight(const Graph& g, Weight w, Distance d, Reversed r)
        : g_(g), weight_(w), distance_(d), rev_(r)
        {
        }

        reference operator[](key_type v) const
        {
            return get(distance_, source(v, g_)) - get(distance_, target(v, g_))
                + get(weight_, v);
        }

    private:
        const Graph& g_;
        Weight weight_;
        Distance distance_;
        Reversed rev_;
    };

    template < class Graph, class Weight, class Distance, class Reversed >
    MapReducedWeight< Graph, Weight, Distance, Reversed > make_mapReducedWeight(
        const Graph& g, Weight w, Distance d, Reversed r)
    {
        return MapReducedWeight< Graph, Weight, Distance, Reversed >(
            g, w, d, r);
    }

} // detail

template < class Graph, class Capacity, class ResidualCapacity, class Reversed,
    class Pred, class Weight, class Distance, class Distance2,
    class VertexIndex >
void successive_shortest_path_nonnegative_weights(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
    ResidualCapacity residual_capacity, Weight weight, Reversed rev,
    VertexIndex index, Pred pred, Distance distance, Distance2 distance_prev)
{
    filtered_graph< const Graph, is_residual_edge< ResidualCapacity > > gres
        = detail::residual_graph(g, residual_capacity);
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;

    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        put(residual_capacity, e, get(capacity, e));
    }

    BGL_FORALL_VERTICES_T(v, g, Graph) { put(distance_prev, v, 0); }

    while (true)
    {
        BGL_FORALL_VERTICES_T(v, g, Graph) { put(pred, v, edge_descriptor()); }
        dijkstra_shortest_paths(gres, s,
            weight_map(
                detail::make_mapReducedWeight(gres, weight, distance_prev, rev))
                .distance_map(distance)
                .vertex_index_map(index)
                .visitor(make_dijkstra_visitor(
                    record_edge_predecessors(pred, on_edge_relaxed()))));

        if (get(pred, t) == edge_descriptor())
        {
            break;
        }

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            put(distance_prev, v, get(distance_prev, v) + get(distance, v));
        }

        detail::augment(g, s, t, pred, residual_capacity, rev);
    }
}

// in this namespace argument dispatching tak place
namespace detail
{

    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class Distance2, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, Distance2 dist_pred)
    {
        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist, dist_pred);
    }

    // setting default distance map
    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, param_not_found)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist,
            make_iterator_property_map(d_map.begin(), index));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class Distance, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist,
        const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred, dist,
            get_param(params, vertex_distance2));
    }

    // setting default distance map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            make_iterator_property_map(d_map.begin(), index),
            get_param(params, vertex_distance2));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            get_param(params, vertex_distance), params);
    }

    // setting default predecessors map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;
        std::vector< edge_descriptor > pred_vec(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index,
            make_iterator_property_map(pred_vec.begin(), index),
            get_param(params, vertex_distance), params);
    }

} // detail

template < class Graph, class P, class T, class R >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    const bgl_named_params< P, T, R >& params)
{

    return detail::successive_shortest_path_nonnegative_weights_dispatch1(g, s,
        t,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        get_param(params, vertex_predecessor), params);
}

template < class Graph >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t)
{
    bgl_named_params< int, buffer_param_t > params(0);
    successive_shortest_path_nonnegative_weights(g, s, t, params);
}

} // boost
#endif /* BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP */

/* successive_shortest_path_nonnegative_weights.hpp
v33Dl2hZv77/cexK1/UZbbLQzkp6AjOPWvtdi5HGocsIMWqEEi3UeUceWrizYpbIXKm7Q4kEJ3OAa6DUHfL4k8N3zBE+PMxQ5dczLBqL0niEWo54iVkJjPVwinO17MZhdv2b4zmb7fPKH1WZ5mE0UIUTTmkakKRGB3mQdYUgvqsr0IFlcdS/0T2w7wBufECrGF2SagBLyNtCSf2debiiYFWxMfRv3SyVGur7tOPUIDxDPA7gm/ZFfOoSSVmCGpE66Sy0kul8tb3npvu7E6BWDmYye7LxEugW1AqAa9olwNUHOJJK11GCEH+hJnPJKZDaif/ITRBiAlbAed42nNuXHiKeiC/nXNs4q0Ov6xyW51nqE42LMsQXLwObvogPGA/4msa7mgmdnyWUve4olqAsfs9DJSdmMkyCAeFaipBhQMRPrt6KVNAhn27sFB0U8OYUbpm5fHVt/uI690oQ6JUSBxdjBC2/W8lIK9wKTAfUinaYuFCThUU7fOPwkFsrZlZX2ifY3MdPyF63/JbzlvWIGtTAP6zQT9TAr9kJ6CRe4C3co35vnQ4TDUhQyopkbSj5ucihbn5cAw2Q3TuVfU1vHMzgP1yLi9GUPtn+fGoOKh1Gfiw6iqyemnWpK5fRl4rmk3fp57BxLTrNs1DmeU+uNXkKS6nIiQCmVWRGsAyqK+vAp49YZPx45A8+MVX6OWXhYp/5IWrVwVKmBXx7zrl2cysXxlzdovddE04eEUYKxAoAj7fjfZqVzXXGOMxNEuI5K1vPZR80K5zeRg3M5lSMujO1n85/GZi8lcPzufOHFrFedND73/rS5/LiJuShXCP3djX3M1XI8PUPeVdeVc80OU9W1FzLlvzUbN3xh1+j76kAw2P9rZJ3+J0jE4HOhCdsywjuKylOk4n7r13o2qFa6MCS2hKWy6agi/BgRqdfvdqk7ILYNIs78nZ+sT7yv6vGJ+K0oGjPyZltmYDhiH6QIvJoxl56rmXfzbaDebjobDuseM891tZAZn697RvtGvQe5gNz5YA7AcdTyxdwFuwN6cZJwFi/X/SyZEsOo3cM6NePifLTaoRO/L9g7+CCbYkp6s9qzIfBk9SP3ePG9OVewFSI6QJ96ydQG+Vjs5cWmkQ7arM18Q0Fgw7j3V+fWov6pp831NI0BJ40ud2ctbxNh66KodG+cbryII5z+xRxcpDMyJPGyJNTZquJvQFuKGKUZctO5i7z8ObW3whdTzfvVPp246IdeSkuPnslsPGGLKDg4GOz0QlOPqj4DfJNqsG6zKfPUgdD5c9GWY3nmwH7ivkbS32c3hXe6pmucgWx1Lwz6LBKCKFDb5zBIhTwysPgTAViyedVzdLyMmgl1AeMplEONF8RHqILckuf70lGVH2SGqHF/FLcTp/EHE8212H55kVsymZFBPlkNiI9jDw+90+4K0IY4sj9hp7DBbB4i86fm1cRzZUr24U5a+EeXNsYC7xYMUCH2PxF4M3WGCklM1axV5Nb3rY/193w6eI/a1nN8Gia8EsBIj60XawyfpWe60q5Cicg36RWtfj2k71UOPIeJq94s6zv0xFpTSIdtHhIyO35Ym0IddG5lckSV4hbMU2s2tL8Bb/je3jxjSTeGoYETrYfnGeBvaW8lu27nfPJG6CYzt+lqJJ4xnOf82hkks/lc62lZFBYAMh5o/VFpQs1wgFfh6VC3GY5jz+lQtROiih2zOi1j91wDztxNaTKeUc3himBiL7GTN0eAMZ+ce2zF0Ro0MlDU692NFZSmaNvluAStjGRwudxgX/Jyoqdvql4Yf3D9gM6i41vTfHbytmKI5P7kxx0IB7145l7K2aovA1P0cmjpftA8eZhxinQ/smOFD0Iap0GkVgxe9HueO189I3yTqxss9I+94d7filvYDpEx7wM/Rt3RyGgxR/io4YDJiV9jaXXQQv99SYdqS8hGm3pyq5b8ExcAWkgE4f5SAJdN3lFfrbR/GJJjdj+RXz2MrCa8qo9IFPzqk/mFaCV382f48qxBuTMGkfiYiTX9oWiNXc5+kKrot6vR//XsGnFZUVUSWIJQvQNRlT6b6Nph52E+oCvTjy6gP/Q5mfZiw4OdQgqqBPbIH5hhw9FU51+BB7i8CqwvYgm6xPEixxLxxFq+zJaR6io+nnD5fOWa+e3eMeOmnmpgGPUbrrKuVsLKhDR4BUCF5G8zQD9SBrzIa0EpraMQtb18ZSHNOdJhVJDOpC/+vnxJZDoshZUMgD0bUNBp7LqEmhme0KZCpRIuwLWpDo3NqhipEKoORY/787OI+sdz7JjcB1W9girzow0VugtamBpfIKrd02cq5XEeX5056l5TYZ4OCCRthPb9/y86uolhMHu1vNDXcZQvWsvFh3xQP2cx7v8u4+ogfGsUF5qRFyNFnQhANTX7/vdPPUSaO4E53z93GUcZvTkPCssjxja2RiB93qy5jIB5vMP1crt0s61S7k83U3TAzp2n8JCqhJcPaPiXD9eObd8TD3jJOgIBeBjrlEjQq+fg59dAnGVIBipEb6TnXmRCzrkhQHPNLzkrhA1MIYVepsamAVJcH1ZGoe+hiNpVvJdAg1tSwreBNHlHYIVb4LAhdCbV6HFvSqufBH/d6Y89MsvXS9JTfqNZp0eBP1r8theJiAR3qyHomcm8MaXOJF0T+0pjCg6efdA2Dg1n2/5QdAFSJupWeqjrOTTa23LH4d9b+NXGXcDFfkkc7ADG0qm33HJzLtlk410xBqR1yAWET6ZNtfv117/aU3ekSX0OxgUjWIC8AryvOYj66uERT+3C+SlZUa953LNlvuecTaLaK32BPk8nREDYc+vpg4v2LivIePYIkbLzpQvPfL3QR19fkALN6bWVwjSy7icsx11CPPjR5qUZP81cJEhHhSTEyftSshiKztJ/m2iUstvLLml533eN6I8Jh42GRNop2YcU6mB9s349/WPZiQQ/JiuP33AMoV+Hzluu4OvYThLWfyHzvuVkrqhgGdRnp2JrMKNImRd8b765vAApVOzzVCE1xX8JvcQ0ggDU6G39lJadt40933EMWwyhgwZWFFQ5CRxCYXZ4W5WxuuFLGstyX+z9sRXPURa6u2iJpdooId31zFhqzQNKR8EM+2+xVVAPkuzO0pnXq5Ueum2f49mGRG1EqRcj36blIiaOvhZ+QXLUQLMszTLs33Hez+Hz1xsZZY9f2O2uO/Ilk6WpNFRk0W6Whxa4PMIREa/dfN6o6Cr2hx08u45omISWVplfHF88eHPRhAval6OydlWT5XLurgMyaAd1o14VkgJ41eMzjr7w1oA53FBh68mGT43+slfcGcyK+tOjDMU8OelqudnmVddIN2vDzOWchhWKT4wlbnKBmdpYJS15C3e8APGr9eHrcyCXo/81AEL83e650DF1UIFPOi9/l1LCoQADLdbc/CXTjmpNSChXVt2cQDqCHBagqph6fr2fY34LwWRJJcRKg2+ICycqi9aMg87uuEbJIidM/qLvbbbPKlv8rvPHtC5JpFBCd6Bq3HUfQzJLRLz37XcLlr+fSVMTykynTg8ZVSMq206eMaoqP9aPOMbnKBfih55schwAnkfJfFOwFvEO+KLuJipYt9N4RUFJcsBpHnheqselLDxtOINBvey0+7FzXNp9U7w+5vnV0tECjqQ5EtIBOR51mKOz2D+VUW4YdUvvZI3GME7A8D8L+iVS4JAKC8i/FGcQX+9WcfMC8it2k7kUy5S8Qg9gnsXaRuGFp8MqmVN1ScbbeAUTpl2eamBLT8vCilXEL23x7FV00dMP+ANd8wtpxwBZPvKmZee7UIZuCh6oIS3s9R5qHWup9V14cZiC75SenhVqcwbcuX7ERPX++BTGujpqha0IADE9zZMPMzchgZ6C1+X1nUx8pG09QQ8CadsSwhbbsO6ZN2NZn1i5Hy++siMzdcq7Q7syX1BxMUdHogn0zmNY8ezevUfsGYQeWST4Cp2gU5nhHLvfm9e4eJhbH98yx2zA9Zk8mt4A36Vzb9Sy8KKGehjwv0VEsFBp9eHhIGizdCbh4ITdkGPz9/vkFtND5VypSEM0MYtlZlh1cWZE3C6YkP9mFj9GKDeEfpKAPSTBpD5kN6ptl4eelR/gQioXwkoMh7BigYFjDIAt0GVmXAGBOOk01YYmssxk868tpA8M5CoYvE86HUHh+tXccsO374vaGAASGPAN9Sc4xLo50mzTSeZ+vBZR2WK+H8/CPxlwWhqZDRv2bHqsdJvcWmjqIT10XXe6+xRBqptHi9fjr19+qh3UO5ovTBY0jvrvuvPTeWSTfiwlIOD1uXIVwHH3/U4BJ+K6r6R1O3L60Xo1JDq4YQ1Ob8zuXPFdcz542VMO6IR6lpRj23Zq59RB4nbdZB9n15HMHQHSl4HLr5ayf851qpDdn2Ss2zU4W7U8dDoEbx/r9vkNxuiDx93NFL6pxv7in0t8+23ppySP7FoJvycIttRdgF5ND2ySlvIDavT3Zh1/lzoZGuMLBiDpF0LWKN9dGQ0H1X1RhBaocmz7jn/MQotu05IcSeWsAFFiDq3v53/U3cX737QjQ1c8y+4jlBbKxkfMzyWjO/zvZuT183ZHc7zvz74UmpIHuBZN7NhR9TxRKLneCJRPTwNR7GFEBENT8DTO6SZ+K0c7jW4hgD0o/UXjphVjB8elnPEfc+FH1DBBomsx8Q8Ni4kc81KQH84aoNSORHiMdpmzlwIW7y/w7W1VhVyWC8/lNc6ZL2PHxrbLdznATAeaX88FWnHduS1lu+44P9CpxzfJqouCE24ueCdGpoUJzHzdqGytbyiIWPd2DPObAnXEm3LvTbIyTAw7L6YqhR3qsS8ef1JDiGtV5XU6zcawomGOpbXmguQ0mdLexsUr9XsOn0dREtT4i6PdXxZTfeORZisgONn1NxLcsune5UH7w4JnY+7DbQv0I8P17aRP+4MJ+bwS7PBctn6Lkz7UBoYo7UdmSZrxczytXe9fqRyNn1x2ouLROqjNpeVWjPatSvZHcFWNH6Z267PiK73oDoXrsl+j6z2q1iNS+qmSu41OBvJ/LIG7dQ3OD/7Pb27YFgfOdfYgGkIyKgRtFVNyIlNk6w1oEfV4hZDZT34N/R1vuYkVB27movOb2G6tSNNpudTNK2FvRdL3vRBS7Ex4xVrFn1+iIr6inUPPG7oZTcyh5Yc5nkdbrzm3A28js3qrpEjKr+NlidFnUvXoPQWzt9bU/rS8Lvb5zRnls33vRUGETUbcFAXW/EFYKy/tvxVE6RsxYYkNnd4er7rOzldzT4kOqyxrX17VHMJawQUeBsMk4nbzeNZn7Vi77vaW6MiGFdxgkaaH2jmXIPVJ7JG5DTZP/Uz27bjIUKfX+ivQXzlLQV00NG+Wk7NxegfOkMOrTZPQU29isiNuUrOW6f1GJBWoc6dCfkUzSp57XT73R/gD9la6U8QZv6HfcJ8pK9bBTo5/MtJcOS6t6J2CbPNk9hzTSvr7EHPQuiuU7jNI/ckpUWJuMbyNb+f7uVvogrSSd/0VbiDit0eP6FzL7/vkkWzbHaCUcIHhZ4/PrJJlt3F/67inC7t/pm6LBGXa5Ei6/KEudHiEdx/Bzj/tlvC5xFEWFeN2ywSBrmaY2WC42hnDLZjRbLC7/tcPbvZ+SeWHrli1tQ5F9J3oQtVL7bPjhTbEcpnDHtZB3j9UuZbfXjDJT7Gp3R3DpnesWAa3bJDFdV+LOtfsvEFaSNKI1K381g4lDbOq5zKNs3mLMPPFDfJ3BXDE6qXhPnhP9xMVjdv3h92nRJe2ft6tbB8BMbgc96+d3C6KVglru8f5PBNQxrGIzJETE9t3iI+nSFGTUFpb03BjcyLFW05z2lT5MyCtP9Jx+uUWt9HKu1OeuVbJ8nLDGg+/jY69oYQnKxN4h8sG0CY7cqyJE46CAjj2LcvDtj75FN/jb7xOHuN7Bc5Ix7vox95DeEqpzwO+x77Zml8n3woaMfnDbjHHHV0naTbgD7ieJX9TgvRGoryFTm3nNHaFQz4bok/4D8vjitmf9Bi86bR9J3ZPexfrW3pShqSFfuhmtWmYggv/vp4/cC0cXbds8SZbSv/pY22q9n6wE180Duk9Ht7gc1nbijL9Vfbp6PeSmu5mXouRBQIjGayK/PkSvL8RGMEd371A++0TUa1HZCFJtSc8shT7y0FNkHMNbyyjmGYoGzGj0lnZfPwb7M9nvf8WAgviujqDGEhztHne/Qbqa2s2OqGqwcjc5+zXWOGZbSIilfT0RVn7fnDWLstlGUVq7UDcsz2QFcA2sKJ82uPBum3wZWc0Aq+AQ0vtblHUx4s9frUx+6XfCecOX7hmDFd2M1zHBJYXgO/UroAV/OSWBIceJzPZzxcnUSx+MnjZg+lGThgIweiOu1/ZjwiqbK1g+7GRKcjo4c9k3VE7AVWn/StR+DiJj5CUQFpxK2+DjPlrTuRzfpuMmCTRQPcZo/Z6NZtw/gGWaOiUkiHHk7YvECWmQAd6dAcyU5F8qcgJTd48w+urJWNVO8EfQ880vfUwVggNxvSN1NUD76hPxDka5Bqs7u+rA0TVVQc5h9xXx3V7D/ysf5GC75IPivPwgkvuL/K2qPd9C50Ov18JLtl+yLOHpF+JQW1C35nsvDOJDA9uBcBH6zblsZyL28RkN1L8yvaVdLn0j+aqpk8y/y7MxfOeQt1RpBmizViHMpTHhJCK4DWL4s3fJvoPflaNidFyeyLkOBNTBeihEuE8A1SfnJt9Mr3nKiA5A26lfs2EupFcSdiBlVxbQd6Y5nbG6Zw7L3t9P5on/DlgtG40zclM68sgRzb7C1Ni/tYkM3cYpnJ83brjdOJ565tvZvQg75ClneVNXxzgCyfgvbzgZPb+xtNfw/WKzvgQ5MXB4WZjGd+9iEmhOZFJeSjpn6NS4NnTu803Z7Zywo5GfQ6MlcSeyMe78sFyMAl84Bd6Xob6PghLxWTjcBmkYs2vSzuS7Bwhk64+Zry4OSFHsfR6t3Dqv63DvD2lmaveSGzd2fsG8u74W2qYQozTHpfXWibVe6N6TK7L+r9K53RWe54vU28N1ljyXqql4h1890eQR2YVsUEcPRzcdK3q32MO90t8U1uK3fbTg5XcIGLTrbq5dyjCehhnba5U7mswezGDqyvCvnjfBHlbFOhUzXRm/Vq1vzOlTYAm/MHDZa6n5HLHUzu0/4+RmgBmxzUwgwkHSk+bLjwReplkYyDk4visSU3y4Wt4vE8b3wbVyRLd0EQr3CwQmfhxJH6MpW5pOt2p7fWC8uW+ytHmtXPnl3xHxFa/vG1rYEVIogQ5Jx54eiB3Pcfp1oWHzjli2y7weBT2ZreMrLRW3jIm7LWFMtTsGx0/IdexXXubl+ATKlvdttAWB5290NfgEHAdv1PGevLJ4MRstNDv3KE2NuK3+SZ/Nw9f//kjb7Mzbb8vDEzQB3GKc883kkllf7gt9Q2VNM8ObyFpCE//+L48sqWe92S4dHDP2H6vugFiRz+ulcioRvP3LGjObkSdRDg7X9AkZaBZn+NqjFE2i8g+ihgrhtlI1yV2qUDS3JYun/+M4kRNuEZUrzxF27nuYpl7Nb2GA8HCubINmOcsAm8My6zUssMRfeqYDcyizqn
*/