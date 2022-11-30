// (C) Copyright 2009 Eric Bose-Wolf
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_TRANSITIVE_REDUCTION_HPP
#define BOOST_GRAPH_TRANSITIVE_REDUCTION_HPP

#include <vector>
#include <algorithm> //std::find
#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/topological_sort.hpp>

// also I didn't got all of the concepts thin. Am I suppose to check
// for all concepts, which are needed for functions I call? (As if I
// wouldn't do that, the users would see the functions called by
// complaining about missings concepts, which would be clearly an error
// message revealing internal implementation and should therefore be avoided?)

// the pseudocode which I followed implementing this algorithmn was taken
// from the german book Algorithmische Graphentheorie by Volker Turau
// it is proposed to be of O(n + nm_red ) where n is the number
// of vertices and m_red is the number of edges in the transitive
// reduction, but I think my implementation spoiled this up at some point
// indicated below.

namespace boost
{

template < typename Graph, typename GraphTR, typename G_to_TR_VertexMap,
    typename VertexIndexMap >
BOOST_CONCEPT_REQUIRES(
    ((VertexListGraphConcept< Graph >))((IncidenceGraphConcept< Graph >))(
        (MutableGraphConcept< GraphTR >))(
        (ReadablePropertyMapConcept< VertexIndexMap,
            typename graph_traits< Graph >::vertex_descriptor >))(
        (Integer< typename property_traits< VertexIndexMap >::value_type >))(
        (LvaluePropertyMapConcept< G_to_TR_VertexMap,
            typename graph_traits< Graph >::vertex_descriptor >)),
    (void))
transitive_reduction(const Graph& g, GraphTR& tr, G_to_TR_VertexMap g_to_tr_map,
    VertexIndexMap g_index_map)
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    typedef typename std::vector< Vertex >::size_type size_type;

    std::vector< Vertex > topo_order;
    topological_sort(g, std::back_inserter(topo_order));

    std::vector< size_type > topo_number_storage(num_vertices(g));

    iterator_property_map< size_type*, VertexIndexMap, size_type, size_type& >
        topo_number(&topo_number_storage[0], g_index_map);

    {
        typename std::vector< Vertex >::reverse_iterator it
            = topo_order.rbegin();
        size_type n = 0;
        for (; it != topo_order.rend(); ++it, ++n)
        {
            topo_number[*it] = n;
        }
    }

    std::vector< std::vector< bool > > edge_in_closure(
        num_vertices(g), std::vector< bool >(num_vertices(g), false));
    {
        typename std::vector< Vertex >::reverse_iterator it
            = topo_order.rbegin();
        for (; it != topo_order.rend(); ++it)
        {
            g_to_tr_map[*it] = add_vertex(tr);
        }
    }

    typename std::vector< Vertex >::iterator it = topo_order.begin(),
                                             end = topo_order.end();
    for (; it != end; ++it)
    {
        size_type i = topo_number[*it];
        edge_in_closure[i][i] = true;
        std::vector< Vertex > neighbors;

        // I have to collect the successors of *it and traverse them in
        // ascending topological order. I didn't know a better way, how to
        // do that. So what I'm doint is, collection the successors of *it here
        {
            typename Graph::out_edge_iterator oi, oi_end;
            for (boost::tie(oi, oi_end) = out_edges(*it, g); oi != oi_end; ++oi)
            {
                neighbors.push_back(target(*oi, g));
            }
        }

        {
            // and run through all vertices in topological order
            typename std::vector< Vertex >::reverse_iterator rit
                = topo_order.rbegin(),
                rend = topo_order.rend();
            for (; rit != rend; ++rit)
            {
                // looking if they are successors of *it
                if (std::find(neighbors.begin(), neighbors.end(), *rit)
                    != neighbors.end())
                {
                    size_type j = topo_number[*rit];
                    if (not edge_in_closure[i][j])
                    {
                        for (size_type k = j; k < num_vertices(g); ++k)
                        {
                            if (not edge_in_closure[i][k])
                            {
                                // here we need edge_in_closure to be in
                                // topological order,
                                edge_in_closure[i][k] = edge_in_closure[j][k];
                            }
                        }
                        // therefore we only access edge_in_closure only through
                        // topo_number property_map
                        add_edge(g_to_tr_map[*it], g_to_tr_map[*rit], tr);
                    } // if ( not edge_in_
                } // if (find (
            } // for( typename vector<Vertex>::reverse_iterator
        } // {

    } // for( typename vector<Vertex>::iterator

} // void transitive_reduction

} // namespace boost

#endif

/* transitive_reduction.hpp
SELOjHwMKX97cZyV67zrfeUeiFw61zc3Q5dF6I7IvRrKjLyfJ7Tx0AWx+3AZonELsgm2pDDtFALZPsY15N/473l54oEtbMkhj1r/vzZDESXEAjOmdCKZ5IoCK5Y2Q5X/9DnbTqtXHB6tkcafyLagO1KFpfD1VdqfxBABhSFi/dIsgQeYP7JT6xlL1jGJi/xmCJK5IbUS51DlQQBVlG58sisTfWEJgq5TrFNzAuKdGechDCGWlrwZOxYEQS4XWc3KfJf4ITIFlD24/6grgClgykNviH4pPlZS2Tm1vf32vd+QB1/vWvCv2ytLfJj1M3XxpvEzZcW/J+eMFWxb3Cb2jVBNFAhxTxVaBLxZlTE+2PwIfFz8SZUPdJI2vRSY0FfMhuB6SslahmVlJ8MpP4kTB6OuCFIau0iA14uf4OKds0/IsOhGWjP+F2bMTYVr1tpOanTRdUKWzFlfOBpYoo1E1uXoNomvGj1NH+mtyQx3/OGNYluKTM/PHcn7e0TSsemFVQ3Dbspvx0ddANo/MNShA607WhQSy3Qmov1sXJKYE72SM7CMUrnvTzHdZgxRWf3oEBRGjtWCc7/QwH+bX0CvMHq/b0K6oKQvnorMpQgXQdsygObhEA//doMQxzIiFI5hPBQ8hAYjPIyDfDVTCID3wCMby6PIgKgFtDVy7sidEYpFRLlc0n+RiLXs5o1vmbPunzrlWpf/2GULx5peRtl/01NYfJ5Spn7Rh1pIenudWLChOMwyWV7fnSyVdrXMbEZ8mwTDImxXy/DDyayFX1uzclOxMoFvPNpb7cz9RccsiCCokkPv89KlFIrGzUMAr62RO4Ev531gODk2XFsztA9lVi4V1ox5r0eOWsX/q43f+6KkdVsijzI2+yAovNvrWZoY8Pg/Nbbnf2rxCsXwChS1IPP2fAMtQF6B5jjbZnIFE+IfsNjRkTta0e71tYJSWzWlKotaZ+l68mu6Y/hqhEcFzcO9AE4X5hOis4al0qLfU1iyFQWzfWKU/BvZUJeLe/QmKaHHXHe4cv6D0ZM7pR4TpdbrAfHdIPZ+BF+jjseVdqREif/jhEoqpeTnW01pZYXHfYPRiyWOHSVVnrqO8laRpJvGZU1nNCViPOc8DXvvOOyyF/7HOOllGOYiUkFtpr8Ityhb19lV6U9f7RnCd4ixR3QtuGcew9idwsJWn52ibYZ9J6sH0YvprCzGpabNVblFaw63zistEQHbdx+P6SHZFIEEDl4ucaMgxBgvKRQqPzIOMeGaiXwgPzGNA1RbyLuzN+u5nUJZHowIduvP76mOKhH1/oYTmVwwFpaSbu7zvnoe8xFzwzjNmy0NJUkxyMdm8/bcg0g3Rh9/XEBP3yRB+hFk7cZuXLCEdYHhhcyFUBD3VjTWg2HDBAXm8JIK7/ze3jJ21pWIqocOLFcne3RFLn6ctArYa4Kb/qgSE6reA2iVZG+ty0fzErOezDOZ6BKGccNjGOhvvcynRo57VFh+wj61hcXiRuKNA9VDz6oNKsKAWsW6kSYmkhv5D5+lgPvc/E5DgUmRwACtj69ZXds+jj9Wn1c3Qyoyhkc7rwObIi93bM6NgL/ruQiwhJQLaiR0wKmMLFo+lLf/MgUY3rjFWDuXlqymje/MuN4WV46USI34Ua4EArpxNj8o8o5rGL/ecZUylrFZFh1OiPGFCiZx2FYhI+4NQQ7QI+O7UQXCAmjtmQGtOWI2/VYr4sgHxrQli6jD/ZFRJaqbGYl8w56spj9bbvkmLlzLs3iyUqmZ7TETQPnqBJ86uYXWhbnXSo9EAoLuNPfLmOL7DVnuhffQbNh1IxsdJlo67Rm4SfjUh7+Jg+M4PuzdorkytXRZMrXzYh1Wj/HX6yPx19xS4+zii8QQ9brDsnoDQRSIjkGMKf+dWlUp/6fQIFQRx2vCGYQpI1Amle9H9H4et/TH0wutSJQBVD7ymwikfB4JZKnQV1/Q81Ho9OkVFEU9h2r0JP0JE7pNnbpUOVsuqtb92Lx46Tkyeu2ZBj7jb+4sfnOG4r/Bxg3+jYndUa5ZPYsnqFa9UopE+hVP9TIIFwuSX6khADuBfadF4KXM42foc/OZ+rFGmMS7tth2wLUJ+RRnMwOkFggYLN0IZlwuoc81gq9RTpVr8lv4+A5zG+qUWxBd6qFqtbIN3MqxeQ+5JP8lQQB5A85Q8d93y0uCLzr7do87lA7ySAVBmL6syE7YEA68nTPbNvcLGY3pim8woJR/uA0+PGLlejnbszIb7oJafmlZGJ3yWdUQTE3xPIgDA6TnLiQngbCtuPQQyu5cooWywt7jYXRm46b7XavpEP3IhK4yueLomNyu/SWj09rthFU7/waHo5t1tT47jpTfVFcaHcO1ew+IeG7dbmnweSmSL9fl/DK0fXxt1RMe4J7Kh0ovvNBldzV51OZcLasDKtHtjimelnDy2ydslSsBlM0noh1hYqP7dNiLJ4FzDwasgVt2vy/dJaWC9E1VrdBscgJZJKbVCH/RXudtDbG03HAYZI/ahVLFmeP3kqk3SqdWvY0J5EkpyCeqlOAfZlXfQi2TAP5NFdkR2e3+4eV2rtn7RVq0lfYshV694qRyM5WxoEsnquK/aVaOnTuks62Ty9Uu/QnPoJ3w41A4Oo7uk7VySFid+4xljEz0eqBg7+QRBJCvwyBccZ9wtzbrjrgG6jv1h64JZq0bFQJjqhZuJyor3ioE9L7JR8QKELDTwoY0WJbFkA4J1+P8UQ9s9nELCuEDfEJdyDkXf8U03tvKY+4V5XXPKWvBj5JjGqqGD84pJy0FWfCPtOVnXJKAAfeaYu3ISXD4R4ry9C5JNILtCwrb0BO4+GRUhOHmueG0FajYmuuKGgXLLaok4TdNH3sx397MippnZ9YLYmwQCjoBZTV/lOnDLCELMgLLagSV4ZCXUYWbQRW2/MqgpX1AF3P7lNFMV0hJKkt9bLgr2f5OIRl6Iy8GYhEMXf4WhWLiCusXnEIwtEZWCsTCGZv6IwrJzBTnPz5NQzS9Kplw20QLVkZwTr1RHtqF28YWVs3QlvLuEiZJbTgdHBeh5eoPvujOfjfoXooVpSE40lSfgNLSpBUd/H30ceqI/oPkmr5lwAz1/+6z+h0LOZG/0r/8SFle8Du1yUeCdZwknksMUS/zU/zM6mkye/VIQATzUoKW1y2yv97vgjpAxhfQ0MNx31GN3lFbH8nIH8muT6U2F1NXv0gEtcjg8io0/jOZXhI5+FTwO36A6IGUkNicS8VaTG0rZmDKZ2Dyi9heTIX+B5cbgyizweVV+QN/j1CizwuiemMuLLbDCJvhhc3Y/OZO/OMconjz8cc5oFbKU1GDkm32L9X7/Aaa3V/crXXNNELZ5IU3LCYqspUP6nbviVxXAvOhBSmIaPWCNUb5qeqY9mQHSph8ZWlumqSIs1JREra0KqxIsmxko/pHpz2+yW+ATH0L6qscVLDuAnb+nJQAFf8Q6hEjsyFtijN31PDCDEQPwGHfLKuJgsNeKceLH1LH8aCUwZC3Q1FErOS0LDpGef5+nVCF08v2YJh/MCSPwAubwpBE1AmW+iVf1yreujWmxO+avEX7s0hxj6R7JbDWuZu1/kfEyS61wOPrjzMq8jRC2ma/w5DWe+0Zs69FHMk3lXIvlrkz9eM5Wv25GCej6GGfo0srTlHuO+P54QOjJV3JLBrCUZ1XZ2PlU5ngCLxH5eRa8dyhvUmxiI27MbxaKo6XLUwQ11oYyHQ4fb9TQSSM1QbqSgtJlY2cupaZqaQyQaE2UpSjIKOLCKf1ldztJ63RwHpLULPC9SKfgc2uUkwIr2g7AdZRwH85jrYlRDAVNLbSunspXX/fu7soapG9IRVRx0/V4Ar16AtLiUfaudqEEN8EduMlmXPhNZOHJLVWNHuLik3JHaZLw/67NN43ozMFhNw2cG84IfVD3jupKN94n+Qa/p2OOiPP4HbDg/DMY4+YSnO9Dp8tBzEfFl4ryKZrDGvDuKC4dOTGxkUyTIpOnT8fCcQyOTBpkjnYCxM8YDD5YhFIO0bDvPI2FAjmQIi0hVOaIZTd334AVi25IoedUngJdhjcYKEIdYjDELjIxF7bccHfUARPSh+9NZ3x5TIDTqcRroHZdqzC+qy919aFRKBwNxfbbNw8OTM/nM2gv+vsIP4wVqJ//qEODlfbUPk0W6O5mBUxSy5e+/zs/uglodGLnPGzZppM7BAU2HzoPZEmrfu5g0fNBmuQVjJiLRsxl4+ezzv/z7PLhAJIKtBO/gZDNC7noqssakeKTI5L4s+4hg4TNJ4i/lv6WQjUoAEbFToxO+5PmnUg+IAx0v8ov/9RvqCDxlfEfltfeoGDiZWIMdofuv8TXMW6R+0QcNbOiHDBinxGCDIS8fJQ+Q9FmGbrZL1TpqK1Is7TgrCjr4bEjjbbissiJdKmyw2voA4/V0026kOJ+Sq4L+Nfyt+BNbURx+D9a2YpTaLejIHVvr+n9O3wX8f33glYG9S7oaNpU+wGDmInN85KDvYJXfaOSbab99jNGuACUs8Vc05y7oH4J6DCuJPyuDZKCsT8NG+Jj2R8ZqP9d4Kb1NkfD8+9m75oII1a3HWNvwKpxGIoPqRRttN/Tp6ycMdmjyId1G0xH6Cfmrv1KrDOuB1511LZNoE9NSebfcdGuNcXHrStkeF5PTlGlpUdTh3l83a9exn7D4NvFVis3lHgbl/WxBQygeB/buvfrkepo+t6EBx8mBx8tPbfUfffXYeersIvLp5b0VLGyoCMhbpD0gpkMymPp7LmQU82YReR4RcbqMBUZKBYN+Bl6Kl8x7GIlPmcbaoMs/6cLtQBNgKqkOWcmIMoLEoIuR1B0Bg1YOx3hRdhgPjTRlyOLIZwcONvSe9XxyEeAAMs/NOY6cRYbI/0adThWthi557QJo6knCnTo5rzEFQa0isdsorkWofra7qS4OzS9YCkBSlNcap54dNDQx6gxwyY9Qb37Phuf+OMl+hvnBUPWUjhVu5ZDz8rlRM+CHufc14zkBqJ7BPhP25lDzlwYc/OOWgg85kzThi7OItvsv7EDCxZKt7Q0jT4yzKT08hpxPjL1Vb59mPvT/IiT8xuJg6Z6lfXlaG2a5UZ422ywIxxw2n6Pjade34QjOXYJnlbStwsJt+qCjV7gcCLFh6gjht05jWghA1t1FRONt7n25Oy4nHz2/voZ/fFlgsBtS09v6rs/Gy+2RrKnxzzLN/DY2zy8xMkcRw67QxI1suf6HaGWIIjqF/DLZBy1uwY68kPIT2d3lvxjCHAu/Wk0Y3lT4w7d9JjwFZBmaFwOQEfPhX3fWmIbtq2gwUpTO53jWOnoVM6WrWiUzIqjIF1NVzB/GH/JbuAxuO9chq+1fNX31YMCYmvPvAqJGd1mgrskF9nIvXi6vXgegajra4wypqKxEry2Xpy7bdLETTcnnPTGJn/wyjC0GU+HvLmtHPTa7G9ie3DBiiahr7zrHFUfmUKJtdXXEjw7+ZQ8CF7wYX7/ZLdu/dkj48/ScPerSR9hjyO1mLR/0V+cdYetG+nWG+zX+ytlmF/eqME5lIl1kusSGNM4zh+QXWuk1Nq/t8TyisdGbsDTtTp2LOHAhZCuMvyROn1mdDsocxhUh7MgXoTsTASmJRN12NWAR8JhQQVZXSNoga/ulU8Wh7PJ/UkSkXSyFhSzMYNNhUpJXSJg+zoiQwZAWoxfhvjLZGtJXTBF7g0B+Opu2lQ06xp0LBsUNOubNB94Slfyvr/buLDHiyza4L7NaSz4bOaP9DFlpudKT3nOCnPBA/ySqCiAwsIWBEr/gdc/ANq/gED/wBqr3/A1T+g5R+wT8A6o/xS9xvBAwluYe5/gj8SxIHa+5HkF9Ssyya3allinJbSbr8TClM8spjPbr8vhHWyej0Rj6nnJ4QQKx8+KLNrQtQW6dVMKoThnHKtuDd2IKcW/udO0JCOCwiTlRufdePxUn+zjy0i0TT8chsKAppbodTBJVZcX7aVvXq3DQKxMNfgSxVR3HQIW73116JOQ1TK62m+Rw4WO6t8w6U+Fl2MWphhTm/4E/uWSYM7aaR4tPTfuy5foIoSfcGgdjLfQPuKxkIzRog9bQxG7/c7EnP8swUzugR+dSGdzAL/rBFRl49caqeMJPCCPO6+zCfDuQyB+FOhcHI+wZvDYZ8+ve1GejMsHJfFQU16kw3NbXBoi9khQIpyNcpNexcNsShC+4NV4/CeVnPoQeazNHps6HbtVhFvgZbvgpq6SKZABhshgX27dINswUcpUmkCBMyTpAG7QQqrmw8LbussQ9C9I/Z+YNkrX77u5m++/mzw334AXHBANwYsxAftL9hndcpfl7XylKta/wi1/why/yPABjN7UZHOnBbGcRaG/t2P+h7/+NylNqYET2H8BRqJCetvAhfcFxD8V7/8L1GdeD6yeo48NK30PzPpPzPKPzN0cBoENBR2MRQUtggUlMtktPqIlcf5I80XgZPL3l/dhvidtTEUXC5TktrVMSv2+5DoLhOSUutDfFyPWVFYQAq4gFzAjeWD67J/Rq0I229u44benF9ZkRaD2x76NxZVkzI9id6Yb4gJ1/GdGewVJTf1SjrYwVgIMpfKKqJEokJoPMtJCmHzc0Oy6Ca/DFlZ65X4/j+zzP+ZWZYSHOLW5obgk43xjNlZHQZ8RfFXeZAu+aJFCAMwgm5Id0R6Atu8zpBm20dPGPRMPb8VXcS4n6+vM7ZyFs3A4KfZB/gdFz33CA3Po4Kr2UVEpbH7a5+uR18xptPMHrEsGpmYe7hYjmn4VCXjm6G4YU7CFRZDmGyQ0BtFKl1E/NaZIcsltFaQXSyyQ92/pDPuRZnkla4pIet52K0001dxvEbWcDLXMb1GNjC1VP/bWC55ovUQhjafd4YLZGH8QzOmhYV1918GiRLuYBWo6Vgsdr0Co5Nh4e245DV+/TxiUin0avz9L3+5Mu8VuQS+C4rxnKdk49mCUzr5Rxy2IwvKwhLtr60enp7HrdsjtGev8ZZ54pkDVsGQwOFo3T0hI0uJd+sX1F9PxuHYDfIhkB4alIOF3aQW9JPyHZoQpt8bqSopFfQq2DVuT29ZQKCs7Az609NiZuIexQ37mydOH6y3ys+1T66yR8e7XVwH31OXEq8cmPhWjucOVU6tYJOYHdwwin0twZRLKTv7yZM3I2bU+ioWF+C06lE5iFCib32qI538KjvdaZWlQYnpV/8HjE4OCvgm4zmTyC6K4Jfz4WsQBE7j7IbTq2lZzBbicn1nPrergPLoOcJK6Gkm1iXYb8gPcOhDlNN6arNnD6/EHfjl+o18bvZVLY9/rNt1a6ye8H7+/wzr5P5TzXzSgjN3mSlOMWqjyLENudq+qtvCfZ3uJmzxctfhIEUa7iNEYro9KdT58BlZuJq9Ym8asoO6Ksio+MS+c2S0o30MxkuJtNzG6IwDq/x1NsklLBYbMbUgxHaDUyVlb0Fyhy8nJNE1unRKhmK54e8I/0ZZfRS20/ifwa9cCGijN9o/WPNmIANt/HDIoi8afowjs6BB8QCM31Ev/yhL/6P8/KOAmINkOPixl6EgmAfiMPn/E7DbshkOwHCuVrgXNQ6NszhS2JPNUq/GwVTrsm4SbIJryRW7lTpv
*/