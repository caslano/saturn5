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
bkfelycP3zSqjQVRoyGp/5YPk9oA8prFV4f/CpY1PyLQfrlv9sx9QjDcLDQSK5d0kkgoltd44X8h45VWjK3in/jltOCaO2YRtTdYxN5RJornLQHXJOuIWjPqSaiUE8R4UtzQ+OSkORW+18xNlruBgGj1tLgvXugNefRnDiQkEMddA+norZVgpHOj7gV3fT/6mOvBo8JXst7TYjYZY2w2BY6Q1HtTybYlbmwt/bjk/iWNYOlbdddCslL8t1HUWTUvVD2KUmm2qgjB9s9I78+0dUic3dlsYZPGToVsejc46oOVZNyNXqGTqV2fm8bU9plpuVC0wcY3atdqOJcbmtEMvbAMe2yy+oCa89VRGxSeNA26ff+2TIdroExIXpDmvlj8Xig4GY+TSkoODZbneKPZaNyH/0bdQDoqTat2Uml4O0lzR6ZLpH54LlplisK+6Dy+CWiiQ/JUpsgDhJOzKrsLZJtZOsSLSS3pMaj1rn3uuNzAXobbNaC89hgw2wMsHciIWP93pQMAZhqo7yVSzNSeoGl/d/8jTgCJLn5iSptiE4aJFrAlvW43S73XG3ZBvoRBdlKOo/sXvZumyTNOWPPvQWlNqZWzggu4ix7Pj/FdQvAeR6hPSB9nNVer8i36o4WSNmipzeCmgvExXnV/ZUxYM6vTueT5sRQ4AUc2CsGHj0pQPAsqZ5c9R7cbS3pG4dhyD4Ucw6YZAbhwJAQqdtjlbnrsWKINrS6WQ17z7yo5dxhYdfEorqwbSkvxSlPmbZv8btzIp53KXgqH5/aeHu9H6kK/G6dBhpzXos2Zlsb0ROG8xmkonYoNtKsxTn1/JeDC0TlTqpyzJ2LIhhud9ZWX0GFSwqYDFlRgv8srlmZReDKF3eCV61C4kCXUndTQEPpZPIZd9kPF9yuH5DqDKB/xS8v7M7FHb0N6z1VzBftcu7TcBen2zaFYveH+n/LW6Q5TJP6oA6SSKJUqyoTmYncwt4Ts0qJhn1g1F5VvoBRNSUlrMKPNIAPzrVUk6Hk91tD/QiKyfcQX0EuvATqiRxylFgEj6TmgMu1gK1HutC024o/jGajVwhHQK8L4FyudEb0kv5EsLrhIBXx2qZ4UqhF3cIFJi3D3W1DNermxzUqJ6qpR+r9GSuwWeWYmC2ahtun7ZhCh764T8MXdlj1yHxGX5nGnxWKSZprM+WGavm86yNqlcqM662ZdZZCJ5cwgOo3o+mgr4OrjJ08kqeG9Mp+hKsXsyDPHNMiFFrtJGhxXuS509Y8sUpRS2LPaXnrk9MOAlX66d9moAbubwH71H1jxG7LEl3XEudt5+8nrCOM7wJc/x4JmxWsIkS9EZ27ktU7ul9fWESQTvMyVTcQlczJTPq8HQhIIWyWaivTDbEo/AReMj3NUcxK2clc2JCCX3HgKL9vPtxomM1Ef4f3FVmRsz3vqyekOEEJf3najjhy0PW8EjmXnDlYUHMkLVgAnUkqQEY0Gf/gM8JUcC4Y3mV3rh1HfzlPsPUZu3gE4+/63GOgXoqkrCl0W4DPcFHBMPX8UfAk6vXme+EqYHkJM+1bBRbXIG93qxiSHo6/YCJEZTtZA1Rn/isMKW9PvjnYN2TTNrauEDFkypW5UGJu6gz5qzt9gzgrhssjupZ20ZPjMJAW+oKNgjeCymfQir+1A+swCInJ5y1MovvfiJNSk43rxUcbQn7MrqFk3+2Y3+6jbi4rehzwewd4Vjs1u+XnQ5mJURvRR2e+XSouK7vsdvs0SEI4tzJpWAeTEIgqad1Nw11gp50arRbB1oakQsre3x7+UjiIiUGsW2wWlVUVTgZG1P82EJx+xuWXeK2ESuFC5OGxr99j8I5cM/ebDI0TfLbJMzxHIkAvYHIlcvBYD9HsSh5O7YBUmUYDKrc0G0/cIpFb/AipxNQKrdg0X5XYn6sO0IddgnrhBlfGg+4TxhKRruXab5DjGaUMfjzBvqAjskd/ybwn7+7iKCLAPbg1WERHMjdaCtt3XzckMbl+IOYNTzuYTpEFl+lcja3+SPTdUwrbm/FmfH9qgm9vH4PcQbivNfzAO/ifDtnXWPxBLOEVnvrfPlLYujeSeZDSz1bA5vZaedNx5ee+PRbC0wb2/99KOGsxSeyjmsz9LEh+0n3/LcrNUrem2DtJkQMaFpbR9upiPAayVaqeJTlImO5MFTAwfzZzfyhF8lsvNkCeN9ryoC2xG0IXXUp04tv3sfzTQtmUYXGv3QysFXNxYJJh/5BUpZAjWUoTqc1U0e5r1vQ26adc31C25LJhYbC8VXGB30878c5z5Ip0b2eNKatExccIp2fBP4RZ7gct23sWtGRWp5/5AG3sxVhAajoRVGJ2SQ7Db/CzxvYuwQ94goE135oy11WKdxMB7a7V4AV+c89043udQvohDf18teLwxfwvTHVYmp20B+L7omxWsrnPqmwTB9UxvC1BM4suPZuhqh13BNgtHkn0jwV/To/axtZz1zaQ5GfY16ts7Txxt9R+9DBgtIKDSjEn1dFOw9CoCyspi5GryBEzrN7n/8wTlnD0DPBInYPb7y2eVHe3Kl47euydOgiyPHl9s381xhE5t/OUclNeU2lD7ImwJMFNsaM6YAzR7QoNfJm3xg90g7SWjfU+xkXZD9pE05ke3I61F3ajvJ4N07sfL57qhKHbr/uMipW6mj/69pv7sR3EPaeHjJmLgebtOrJPqBr9eeVotFRzLJQpf3k4bZizBQ4EnlW2pLxZWfQkDOizxhc+fF5ASxEsWgerzCMA5xB1YdW/MOwql/BQhknNYqkgJNqVVgJzOul/1JtRAphe3UUCFLFESA/ff6+TOCMdzwR+X/XuJkrBIyBO+jQxmylgv/GS8wV/cxM/6fXOk4pPhI+Ko5+2Aof47HZ8+jJVa9fk5Uq9IPurKNKru/UJhsAYKZH7SlQmnDLrMxGvlSMLktNGwf4lRsTNYZbjYuSdrdbyaKfku63DyQ40ndLn+SmLndtn39M5TaD5PiG2iGv2sQmCM4gl6ejsBif35kF+aZXeeiER12nV26qol53fKluquiqa9yBO5tcTE9rTMUORn82eswdMXdEk9nF1cY+nx3o8Ykm9PUn1UeJCnYCP3gz0KhQu+PLLD+bxWU4TvC9l7ORvpgz1A3aqHyWOvOIEChsinewcz1Xaw36Z3Lg2H5zgdlRh+8FS3bGJcmVkbDNVcDY0Nkud6uZxgyabRn9/2huUecIfrpbA3U+6wkKvaUYmPDnZ1JjH5kGWxIcqMkPPZ/GXi+pubVXsXJyx6FCPXXzJXuMvopNReK1Wyvx+lpc5vPbKPGoviEc4ulRFu9eZvRXZT2cw50bmnlSo2WFE1C7IEnymJLuU8sGBJqzYiBf7x+4SY7az2iefvqXZWurRb8Fx+d9rFJrCZ0dzSybV0k69zlt884fW9SY1rpU5SCpQotVtXIrHZKmXRzuXpjKfTrrxKshdszi5U1GvXbHixfHyfQDMdI3Y+IDF/oiLnMtORdakoFHLleVc14i/+FzwVf0nkA8SB8bhlwGJAMXJY7RLO/zwUuFj3sBh/kZMRKsW5EIOVj1/Bm1YGkd93bxDdbmbDPC4PIcz4G8KDyLWXhxFKFzbB1zzekI1dxBe9fu0JILdRFWTDJGtgs2SgHsJ4WKrIhIF9NNPJqb5HyhFr5Xbn2gESa7RIggHQgy8LOTLXr4btD5/cCwRWMwfJPXbzwA2uU5BT1dU4r/b/H+rP2gB5rTbwQ+9gFLYnGOL2IRvwXLwOiNKgQdGhxIS7KSOe1r1AZCsxQUQYCMlnOQYp8QxGXDxsCYUGKLOBh6+nQ6iOs2Tuw0nUFjEN9Ee1YbTIg3trc49GX8HXoLTwK3p7EWS/W+BywLlDWfUKLkiabQfAV0cH0YBl1tSeCY0Doq4hBNguC877Tmvq3HlkWtMuhpjglEFM0EkDhA81vrbJq34N+w9VavUCQq4hxAT1PEL4xUMW9Y8Y0Du4YVAiXh5EBa/kDyUIlnS91C4HjqgPMVy414/qH/KPA72KvwAjfCf6/brdsT+tbPzA2C6YaOAkydRB4MbfIzFNvir7PoU4/3/ok9JPWOUTY1Ten2VMFd7StmUvxyDxgZS8Q9e94EfmCYnVha6DG3x0Da+F7xJK9HqRiTV8o45ZNZolO0GBy7QsRCNFGwMLPXcyt0MdB1Pwfoe6Q3/mr9oUN7a5oXOtXMkR7mMPLAaVbvcoIQaa/jwhWd2C87tftJmjeRa3zFDIUygxziM9IDxkVHrcNeKGXuYhoV+uSWbl1ma6sW2S8W9is5NjMmMoGbarJ5+QFm717NwEgwYSFD58WQe/r2wEfzZX26De/fC+1+KgsDbbjW230q/Vou6iuYK+xaCqT9xWucot+ApVfZlwkbnnJAEmX306Y1Ho5W1EH0FnflHpm1E62qRc+C+3dN/Q2R/1N4vVKucJX8on35VpfUtpWGpuestWE5o/8S2q+AtW2OeOrCZgp6CZUDaJBnmwaWzakTcthIGxCMd3FyKHhVeU3cKIhp+UeoEB3ft1M7+CvSrhzrKt1fDemRANXqPORbE3lWRlU9Zhi+HwZkKQaY8jYt2hGrH9DWC1JIiggXstw3WOu2SY+UH1RY6TmQ+KHwFDJ4FA80MYx4n5DF8b8GC2FTCNIsPGqGG96/ZzvNOvTNnntPnrlJP2j185nDl9mpyNoJlbeGpzZqdYRYrKn3CfkeDEcGPf5ZRjLGeQliaXwGOc6ZC3Nw41ZA7Nr7+S2uDrxBqsqSXHQWHirorIOklLODulydzXoFopbZuOfwPM6fz/ioQM5bB8K3cUdYmo/29ftJ1pt+KMz/vHUvZlIj2aMQqxubG6LJ8/9GJqMc9hXKtsZXXZ6cLFKuYEZ8v+Mg34pGBnjQSS3flLofMv3JgJHlSJXXk5GCFPqFKGDMYNDm9MND5yy57LDqrvxC+KWGUGQn7cUkU6zxjIzZDwlk+lI6Dq82fv4J4nt84wbqcW8WLGTGoPMzWmn0sfzMpozV/PGd7ZiuRV9WWGkW+laVxH6yCWX3OVc5482FFlnV/1JY6c6seDXspjCIDHcWazOt3Gmq1EGAHgMNMBlL6TYecH+p78w9YmlFMJ8HYf6W0LNB3Jw33YRNBwpLDhIK0JGwSvONNiei4kIMBRuFxNdImvk5+N+WA/Jay5vtuyYKJZfGx/PGLe3hc0d2Xjj21p+VDFC/k77/iUqxTy3CevWLvcIMtFbOqE+F6aafex4USKh6jaYROO3+99FvqdSnh93fs+LLxb8aco9OOS9avhR3uRxaslozvxdzKdkhOmj2HTZ9V6VS0MBRxOMzCHgAznjy20pkIb5yfflGml2Sq0LR5IsKHNP5nYWz9UrKt/XruMz1UpyXnT+bNLPnN6cP7pZfMH46R5f7VBOfOvgvK+9bkCLx656fO1QRqkOyAX6HBLzKHYK8XLb1g+srLS4ZQV2Mgqn0w6wA/YT+sXinO64SVOWRtLF/hzguajZp6DAMOJYQAynQkwLOFhjW/IgKbaCEL4/4eGo/SbwM2quJm1lx6XE7y7cy2eqk4iV4254r7OvDDy/vZ3UElyIX1gM7gMmrpzMIzt2V3zHZQKI+xBlNc1DTARmgEyLGfurTyl3L/pMenloJN0A75T8zmX4prGYb5P7qvp1xhwrxX7bQciHVbmcOB0FKtC8PDnaGie+b9RrDNEBdcq6p2KyZ+Agq4/3OWwh/n+wvTV3Z/DPHCtXfD/NVtP+ykpcLdo2Bry/j2hijvAR67F2rJwfnFGRfEzg+XBtSq4xCYWAelTxG086jlD3vRHfrEUgPe8foccPTt43r+03UzvOUVCOfhzP0p+fc21GtKwQ/b5qKX5uHYBk+YvdzqgAufVOhhRTpq3n/KY0Rj9Qb2C+jSiEdTFN6jYq0H88SGgOTH2wHPfqrhmViO+U+KUIcFErW7xpHHpwu5jrjmWx0K9o2pv3ev9bnV6Cz84rxKtmOHG5tD5InJf/RPbsd8nE22LlXzMjywUYrdkRZYl4cunIoWbypZDNce82cwqitk8Ywd/wucVzzGnJ0bGauXVmHix2L3UOMe8nRUZS0uZoltXnMURNRvbCGcx+GOH4e6YvdPHySo1XXsBUQt3qi6nZ8YQX05nW3yT4PV7eOX9XYJhVRIITSvaI27DMHAynvib/v3dOkEev3s03q3810oPggX6WXZjYn962jTrQmXipyLX7zcsZbtv+INlvbTUn3XD82op61+PgNts+B3pq6TkT3wul3oeO/Xt9XTqRrGJH/yPuW7w6qxja4wmFc7zCg1X/PjXAcXzb8pZqZy6hZegn0xo42OMB3oUDaOnmD8ekZBR2u8DJIXJBHjsVmgkYBYfqabnErfBF+oLlRd6bRUfKaFvEXdHRvcXq5mFPYT8uadQEwafnn1vVag57ZB+p7tolzXG9R2qrFh1XTgF0f33BeE4pKzos27hrgNPlmSOYc7D4nC3yy9DfowKXq8cwbtubhFdeJ8U+F0rzX4omre/JvFCVV4T9Opyj7NVjTVw/MHdMuGBzZxE5T1Sv21J7jrtd/L6/Yr9VAo2+EervAW/YOboz/iMg4rP0ulj+PZKiGOQ1PD8O4Vz5l8PvLNdev2+Yoz8yXPDSngIh+3NBS7RNUTLoPxsENcxstn2ZouMbi+MohaI9frvm9dqppJ8t+EuSKakUF/y99itVZbT/ZtC1ld/KX51Y1uRWLRBVo9E4jgfFLPXyxhPTwWWr57ZoqWOg8zOntGUwq4ZFjJdbw0O1ODTyjIba6D/ANeg/jGWYXTeHxppbMFiUd15J/vQ5Oir9tn2dcdm4dke86PHQzvzon9RoK3fEwkeByDfZVLEjWUyLe0SH4HEINMMCC1ZQ/tvebwBbCuzUM9x1gwbUwbHxB146N36973f/Fapx2UuaTFU/vBioWG5yvqNVoT9pM2muIav5ma7d9Cgpwu06hwKoGJel/bWFvr30Z6SLMYXn/XqgvkbP+h+1fEwt7x7l86Tmm9KtytMx9P1LpsOl/2Ki0myeJ/Dk0e3o/zGxravbDouPnKSVxhOjVXJdpbvUeB4/DJXqHvJgbe6iV1OjsCf6hIZGX1STMgoazSGcf7JyVToedDR8jjwPYDYIWMR72V+gwqROsMALw0ODcMfEpELA3iQuo1xSDbQH7EJHDgNAeyucoul9G2khiLDM8bYenxiV+q1xX7vYfn2uhvBzm7vqZSwb3tP79Lzlf7SmiavUbnX9gvP3RaRcuKfFOozdV1YNNV4XI3I/hFWxADM0YF/1j2MGze5IiIOG0HVzd1N83ak3Qe4eFqxsAzm0xTuAzsCIq716gKNMBF8PaSlYFn6B8CflHICK0blARnxZ2i3QbfC95hxQPFYl+x06QSWKkeGqJ66xCV6nV3bAqTtiWARqSPYbg220EsPwDtlLuGVJtg1M6I2Fe7BQ1gSIf1vbtsZhxwGarIftoxT4YN08rugBm7nUHrvD/dBP/wASwMk8Ar3TLwdi8AMnCFvE3VTl5tUqeFAqfMicMm17wxZ8BGb9xaOHLdYa6MvHA1MlK6aVr5T+Vm2juHcG3hbDWOr8nkHHsPCXKNivlDPJbolfqgJA68Pm6vcqoGiu7oj5uLVsx6CzwxJNDh3/+LGoA/W1wbO/p5N6jKryYSQy2oPLdqqPMyl5zlx1K7GJyVyZ2RvqxjEBUDrwoQmr9byzDuZhs65HpeWlt1K/uTHco3R4tX5kzq2II9AlyvBQ6Vhf01iv79i29pepaqJ+qCpMCAjFf7aamDWi7J5lcSf18ktod2IwWYt8EDIEargEZE/wWTi2xFKnQew/tOJiKq5RraS+jn8Y9df4491uWMM42Lgd/XFDO9grBlLp2VmLH3JK7bmzT0qiDdLZ7/IqF3z4as2zGztqjc5GKF5fveSugpPI91ufFXXXSXzD8+fGj3eMmVZkpm/2tB60xfKmF/+4J76L/rvwHvpNxcept4ljNy3eCTYoJ8GTsGYgIfnKmNqWOf6xL7+2WH8PePr+JmjENEoMTj0dv075JyU+IakCMeRPg+MtzmJ9rodxu4O+3rU+ccTQhxHLy6mRfLGLN/PZ3c9uk9n2kbYUYRsRyozS3EpWt6BWby5VfMrWra84nBArZoazTGR2PD6Ru5TxfPVavyyw+XhAzP3LQbUfz7bZV/cCBR/Ul7psfVu8KFCKe+qdNVrFwuOnRdvN4qSUn5ho0vMiC25ZkigaFv+jw0SsuA1JklmH3isMIFHRmgg2OCsTdXY0oMPLRBLD+m24sm+JX4IFj60AQNzSwSAfb7f68H9kQxkOUw4kTiTg1+K8Q0ueBPso6r5HLzaZF3mBr1+hKtL2eXJaSg/kppU1oz60HHgC9UHzbSwQZ2/BNROfMk7BZW7dRo2OflouZt4eaWyAzdNv50mkGqZrR8LQoPhXS/W4XagNRfvQeWGjVXsvbi2hsfvzx6H37QuV94eYcPqPZwwKvdJEgc/DrLMb1axz2+bDuP+Ki5VJkLULAqypDJpxUPgA/US8W5Jw/Essjy35jE/Hp7p6M19Pe9TORN4Z3dsg1+3ZzPu5oFI8qoVFF2Wvs+UrBlJdvbWcCkqLfIR7ERuZEPeQiN/Sov8Yhg03/wKEe7qeVhlwWbt1TRibvRD3TzSJNFuLcNc6baixYjp5GyLgIHpYw2abdKnwgFzKxz3oLXoWQZLhL9zSW/uUNrqof3zreEBuPlLh1vo6VPTzxIM8BP/BWOnzmCyWUM1zeM/N0/yZvkeoYB2xe+OfzYuIV9Vt96Hl0xjHZ/kr24bBcToiiphRU74n5urkI9QI6bfZUS2xjWNT6+/171qdSABb/DmNJ8cMEcZe3Dk72l95RSYk3JPvyAWRNAP6bHrVKRt7k3UPOezm2eSGe67uJXu4cIE/THT/M3D03TVeJXdNKvhB/w1gpeo8a6o9pzO99qrVpc9DMYOpTjXtaYiq5lZ0MIneiNUSYZa3Vtz5dZQg41yHLwkt/T0vY+H/GyTe37qtVm4eli5GrffRtYhyiZp60wjxfWgdh97fZVUbF/97Fmrx6sPO/CDInWjoYN9KQ/4ULB0XlPFQr1UJ3dCvtY3hMqX8HMOU5aqZguYur9W5WIc4/d8y5gP/CXyRjR/vEq0QiEUtKRCd+R/7z6+PrpiNawE3h2GB57h51bKFLHw39g=
*/