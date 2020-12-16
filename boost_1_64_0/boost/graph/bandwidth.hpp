// Copyright (c) Jeremy Siek 2001, Marc Wintermantel 2002
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BANDWIDTH_HPP
#define BOOST_GRAPH_BANDWIDTH_HPP

#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type ith_bandwidth(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g,
    VertexIndexMap index)
{
    BOOST_USING_STD_MAX();
    using std::abs;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    vertices_size_type b = 0;
    typename graph_traits< Graph >::out_edge_iterator e, end;
    for (boost::tie(e, end) = out_edges(i, g); e != end; ++e)
    {
        int f_i = get(index, i);
        int f_j = get(index, target(*e, g));
        b = max BOOST_PREVENT_MACRO_SUBSTITUTION(
            b, vertices_size_type(abs(f_i - f_j)));
    }
    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type ith_bandwidth(
    typename graph_traits< Graph >::vertex_descriptor i, const Graph& g)
{
    return ith_bandwidth(i, g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type bandwidth(
    const Graph& g, VertexIndexMap index)
{
    BOOST_USING_STD_MAX();
    using std::abs;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    vertices_size_type b = 0;
    typename graph_traits< Graph >::edge_iterator i, end;
    for (boost::tie(i, end) = edges(g); i != end; ++i)
    {
        int f_i = get(index, source(*i, g));
        int f_j = get(index, target(*i, g));
        b = max BOOST_PREVENT_MACRO_SUBSTITUTION(
            b, vertices_size_type(abs(f_i - f_j)));
    }
    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type bandwidth(const Graph& g)
{
    return bandwidth(g, get(vertex_index, g));
}

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type edgesum(
    const Graph& g, VertexIndexMap index_map)
{
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef
        typename detail::numeric_traits< size_type >::difference_type diff_t;
    size_type sum = 0;
    typename graph_traits< Graph >::edge_iterator i, end;
    for (boost::tie(i, end) = edges(g); i != end; ++i)
    {
        diff_t f_u = get(index_map, source(*i, g));
        diff_t f_v = get(index_map, target(*i, g));
        using namespace std; // to call abs() unqualified
        sum += abs(f_u - f_v);
    }
    return sum;
}

} // namespace boost

#endif // BOOST_GRAPH_BANDWIDTH_HPP

/* bandwidth.hpp
QEoO8c3Q0B+0HpvM2n9fIuR7kkHSCMzkUp002/T+UE2HjUH4MSwlWIvVyOufkAw936EiyeLNBn+yU7fF29sUOloLTU64m7xSvsvkGyHzVp+v79Ml3ZscPN5wkyhMEslrgqaeCrmCvtA81z4OVaH3UXxvmQ0Ob+ySeddvmgSpJsH7NcGBUO1Jd0huHQ1uhCUfDMASpQV8T78+ujTEPDdfl2iTH1qTygkxNS7Pcj6hO9wZbL6jL7/+IGPhm77pD6WP1vS/wFbpV0t6+17VfVAYqikSfbmhZneOCuWT/L+UFJ+chy/fLQxCv/KYvidSCkxedlde73sjRNvytwN8+hZx+TW/JyXhSyZhmCS8q0flYnnjg03SBmi7Of7oW2bMPjouebAz5sq48Mjvb+Xr2YZ8Qz9keI6pkTEy4gyQafSE29P03Qqnl/y5JCUrbclth9NTUX8jfcxbS/6a4vXIG1s7erenLPlzhdMxpff1lCW3nR5Hpb4dZu1zAfKG0SUdzzuc3sjt6b1/Lm/fSe/dKssNTqsPcVXJiPXn+ns6bsoLRiK8uRl1fba+KA8Jyhd2god1PNsVmbYqZKqkmtgUGmDzxE4sDA20eZ6c6FINDNn3N/3Gun3eExnSjAJMI4j8ytGa3pI9QHJGSU55CvQ9S/5gi+yIXNJliyy0uXVmsMz8S2WQrVGbUtr4joUjxrwRuV3WLa3+LV03/wpFHvpdL5QWKBmOSYbIQ9eia5ynQh5kax1p+7knU1LjOueJmjzhoJpsKSxAXx1mz+jdmrFKh2Q9BxgaOiHUm1Afclpy1DWHnQr5vkwE6cEc8j2ZSrl73O55V12z/VTINgmGYMZWmdJdmajvDZK3gulpnHkzw5imD4eskbmRn2s6bsYbfRtD8t+lY1lysylEBxxzGjI7CMdBcP1Pfvp03TBbpQTNd4tSGlt1VHuJEV39P9cbTy/7cKh87rzMlGaOs4I6nSOFTPCP0msvYy4SdY/Ux2WGT2IwVmuZOmHXE8Wp5pnzZp2J3xU237PUF5ghMqVRn0vFSZB5EN53ONDKgWfIT8lD4/3leBDn6Y6W90T10q+ayKmOzDFv51+b3hG54bhOZ+hCfx9ulpbc1b9NJvWHr+6+9UTTkyGdc4Lw+GprCB5f1drSF49InZrjRDM39OLb9syA/yEOdgHe2xklKRMygo4uScTo9rvvm9EtI8Z7vq5Rz6P7zv1ZXaOe6si+Mf2h9Di9dPPkuijc319m1AcsSSypqbrsHVRXGxPsHVCfYV+75PL9ymt19wLnRsqbS5K/EOB5jD2qb0qgZJQCiuShGnMup+cXGJrqHPIz2j9I2P6b0V/A63RCsjJl88Yf91bLLoiR98Jh8EiPkVE/qqv/LglJl/OMTkf00mlJZTfhDTov3S4RURlHL9szxqTrJypjzNGM73fhn5T0lATGmIXpUjL0272rQn71gmmoGRlvt0rw2AtmrH35eKM+DCmVK3WwtkIi5XqwlzVmvPKuf8jpaViwb/szmAjUjTVte5eUIG9Jk7oLeU3yqavUPccPWdf3HmnQb/198Hsi/QGg8fpepXB95PqnD2SNfynvHwvLGH/J/ftHfo9H1umdZS01ZX3iHWUt+W9l6T+5byIditzvCFMuAleCq8HSXrjO7437EZg+DR4Gd4IN4FKwUqn1pdexYAI4FjwI5pj04cotmF4HLgangyfCUH4YykHKBOyDfQHH/+P1YNfl5Gl48b504ksS5ShpitxwtP6oHCsSLxVm5mXU/7w+zJct9dNgdvkZ2//5b1RWKOzKNp5OJ6t1Ph1Dr3nBeAu9mz5IN9OdLNdHn2X8ZbqDDsxk+fRwehydSk+nXfQyeg0=
*/