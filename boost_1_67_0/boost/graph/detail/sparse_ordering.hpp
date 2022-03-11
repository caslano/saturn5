//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004, 2005 Trustees of Indiana University
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//          Doug Gregor, D. Kevin McGrath
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================//
#ifndef BOOST_GRAPH_DETAIL_SPARSE_ORDERING_HPP
#define BOOST_GRAPH_DETAIL_SPARSE_ORDERING_HPP

#include <boost/config.hpp>
#include <vector>
#include <queue>
#include <boost/pending/queue.hpp>
#include <boost/pending/mutable_queue.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/bind.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/depth_first_search.hpp>

namespace boost
{

namespace sparse
{

    // rcm_queue
    //
    // This is a custom queue type used in the
    // *_ordering algorithms.
    // In addition to the normal queue operations, the
    // rcm_queue provides:
    //
    //   int eccentricity() const;
    //   value_type spouse() const;
    //

    // yes, it's a bad name...but it works, so use it
    template < class Vertex, class DegreeMap,
        class Container = std::deque< Vertex > >
    class rcm_queue : public std::queue< Vertex, Container >
    {
        typedef std::queue< Vertex > base;

    public:
        typedef typename base::value_type value_type;
        typedef typename base::size_type size_type;

        /* SGI queue has not had a contructor queue(const Container&) */
        inline rcm_queue(DegreeMap deg)
        : _size(0), Qsize(1), eccen(-1), degree(deg)
        {
        }

        inline void pop()
        {
            if (!_size)
                Qsize = base::size();

            base::pop();
            if (_size == Qsize - 1)
            {
                _size = 0;
                ++eccen;
            }
            else
                ++_size;
        }

        inline value_type& front()
        {
            value_type& u = base::front();
            if (_size == 0)
                w = u;
            else if (get(degree, u) < get(degree, w))
                w = u;
            return u;
        }

        inline const value_type& front() const
        {
            const value_type& u = base::front();
            if (_size == 0)
                w = u;
            else if (get(degree, u) < get(degree, w))
                w = u;
            return u;
        }

        inline value_type& top() { return front(); }
        inline const value_type& top() const { return front(); }

        inline size_type size() const { return base::size(); }

        inline size_type eccentricity() const { return eccen; }
        inline value_type spouse() const { return w; }

    protected:
        size_type _size;
        size_type Qsize;
        int eccen;
        mutable value_type w;
        DegreeMap degree;
    };

    template < typename Tp, typename Sequence = std::deque< Tp > >
    class sparse_ordering_queue : public boost::queue< Tp, Sequence >
    {
    public:
        typedef typename Sequence::iterator iterator;
        typedef typename Sequence::reverse_iterator reverse_iterator;
        typedef queue< Tp, Sequence > base;
        typedef typename Sequence::size_type size_type;

        inline iterator begin() { return this->c.begin(); }
        inline reverse_iterator rbegin() { return this->c.rbegin(); }
        inline iterator end() { return this->c.end(); }
        inline reverse_iterator rend() { return this->c.rend(); }
        inline Tp& operator[](int n) { return this->c[n]; }
        inline size_type size() { return this->c.size(); }

    protected:
        // nothing
    };

} // namespace sparse

// Compute Pseudo peripheral
//
// To compute an approximated peripheral for a given vertex.
// Used in <tt>king_ordering</tt> algorithm.
//
template < class Graph, class Vertex, class ColorMap, class DegreeMap >
Vertex pseudo_peripheral_pair(
    Graph const& G, const Vertex& u, int& ecc, ColorMap color, DegreeMap degree)
{
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    sparse::rcm_queue< Vertex, DegreeMap > Q(degree);

    typename boost::graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
        if (get(color, *ui) != Color::red())
            put(color, *ui, Color::white());
    breadth_first_visit(G, u, buffer(Q).color_map(color));

    ecc = Q.eccentricity();
    return Q.spouse();
}

// Find a good starting node
//
// This is to find a good starting node for the
// king_ordering algorithm. "good" is in the sense
// of the ordering generated by RCM.
//
template < class Graph, class Vertex, class Color, class Degree >
Vertex find_starting_node(Graph const& G, Vertex r, Color color, Degree degree)
{
    Vertex x, y;
    int eccen_r, eccen_x;

    x = pseudo_peripheral_pair(G, r, eccen_r, color, degree);
    y = pseudo_peripheral_pair(G, x, eccen_x, color, degree);

    while (eccen_x > eccen_r)
    {
        r = x;
        eccen_r = eccen_x;
        x = y;
        y = pseudo_peripheral_pair(G, x, eccen_x, color, degree);
    }
    return x;
}

template < typename Graph >
class out_degree_property_map
: public put_get_helper< typename graph_traits< Graph >::degree_size_type,
      out_degree_property_map< Graph > >
{
public:
    typedef typename graph_traits< Graph >::vertex_descriptor key_type;
    typedef typename graph_traits< Graph >::degree_size_type value_type;
    typedef value_type reference;
    typedef readable_property_map_tag category;
    out_degree_property_map(const Graph& g) : m_g(g) {}
    value_type operator[](const key_type& v) const
    {
        return out_degree(v, m_g);
    }

private:
    const Graph& m_g;
};
template < typename Graph >
inline out_degree_property_map< Graph > make_out_degree_map(const Graph& g)
{
    return out_degree_property_map< Graph >(g);
}

} // namespace boost

#endif // BOOST_GRAPH_KING_HPP

/* sparse_ordering.hpp
0gF9Lah34/CxwacuWA1eeIm/xGmRH92M/NMHMVmmVpAUecwHox40vjbsJNrhtkN8E2tS7Oh/c1GLisLz88eLIl78JXk9uE0fIbrknzEe/o+FgDFr8ibR6B/CVwm6j6nmhASR1mX507sUKOycO4BqmlrviKe9qtdHv0+4nU3JZn2TP+tSQo7fNAYbADpTKUPZckRiUVf6IjqCB3BumKoSnwYyXPF2qlS0bEMr6o58rJCj5yLEcJ7vmMxyFgLl86TUdACvealdfBqf3iTrucpejeR0ygtoWICoDz5giI15oiiZylx3Tb1N32BybyGpEh5oG+vv3HRjmtJFWBlcyjotNjHqaBpCMQxtnNFP/sJLeLS/BEm67VH/YUWIHBAzjBm+Rh25LToXFeX2372onDQBTO6WKXodADdwGv0KO1/lu7o/Wcrhe7N49JpaR0UyRAfGMRB3d8E8ww3v4nvVUsy/4Q3dtgTZ+g64Wg64Kg68XgTdpgTdMt/vbgbY373psRrc70sn2CGWZfNK95gmeLkrew+4Cg68VgT9tBZd5O60/HPpv1Qt21WWAKmEOxksUNyd4R82PjsJ3Ph15+pptVbu1e+5zYqvwmb3ciq2Vt4wqiF/MiHCM3GuAeNebbMHMcxmOkW9obNfRuYws4fCc6TalXiFPMMfLTqFEsmJ4bZOdqcThDE/ejY/u4Xqb1yWuEMWfzvqGkmOdS14V9aBEzEmGfvwgGe4SY151gQx2qrE+TRXoRi7Qgu6mux3pYncoyQYVw3kn53UCiYDg+oO6hEAfBABXOj371rCjO1hTC/3+5JZAfH/KrhbtnuDJIc0gJkpR9N+RVD67ESgoAyVmECUs8dLtnKXKPtJY4dQ0vrdSRIYLgS/q4DkkeORasrUNhk9W8cpzO8j17QDqBF7+iWRXObqzLoe2KqHZW/yXw8oM/+8OLICI5mxH+idLnDK9sLO7R1v2UN66qBW+jEp+xICV7KcK40NnuA1DcYLGNu6K1Ea93JWK5Tg6cHAkdkI5FZoB3L2+pUqXzlPtqDGhffVecmtJVTIyn9YnH+3OHAln/cPd9QD/uR+vNKuOc4jGvXm48VpkEv/xnC2mgWu7lwABe07xb/zV5xXd5Yz7QQDKycuFpxQEbsfX3ekL/dCf8rF2ostLQdJyEzp452OzJTgvghxP4CrYIf1Ua3Hr1Kei4CKELJ/JE7OjXG1B0lc/BQ+O34qvf8CZRS4wCixbyHC8VcXn3Z12FDPQJh1aU9RanosOwZE/hbep/xkytnNeMZm+jrBHt23xFjte836l3Pok5YD2SO7SPtfrhvQEpY9bNICRmLbfIVqTctF8maNB+lK+J6PmGLHlPFwQ12SgfhcWf5WDle2iG4fUnsYz0EUVZ3eOMjSESBpTiLtDJTy0XAtX1eXUjLaw1FxDYouT0EpDia+38QBgq4RKmooLWlHfPTUluGqEt8bESPElTH2/29WVtWFYEnIvfRNZLIdzLWHftRvijjcfb5y7XXv9D67EvmGGxujUv6e94K7VYet0PFM083RrLmn58I7hJIRUoEJ5rLx5koM2fbpnM9tdTO34mr988+YcnyjAL8Pcahk9uII7cSw2P+ci//BwjOv44IFZFxFOUOWwepizsR0A9FncRVrO+ihDrRqktDCz4eaA0pxNXJxJfLidMIu4kf2urQjlrB0TYUvjjRO7kf+DpwqrNwxQPmaKvL2gpVoLjHW8gpWTx1FZ8mYHfWYF2S4fwPshDF+JGzc4DVdf7TeLjkyKHxhnAZCR6MPtIbzGwtDO+F4NXJnAPzO2QJpo+xaQeyOZHbNQuI9idyamDIh/ez3UitUKy8qkCxN2usLrmH+MM1Z8khzolqBbYgNspSJs/5nCXfa9uaJF1Ek8OMBAB3vxMsze4kCN7hSG6jFenRyP2s7WCpc7pPLbuAgLJ0mFGUQ6lBwyPRVREVqmslV3M/kAZ8ExoVSY9/ebG6zV5Xt0cTYdEZIevIqJHO3q+G7hnsOrRnmc5DwLF8Ax9Oajg/nV29qsMqUyLUeQQhIDFT3yEBaA2Zj2tAVbNyxzu4XA0PechvWYH+kSmuET/SlWsNbfFVmX3sX4c/FMmBDG/vdqjEpE4LALuIgc6HCzZhyQz/CxWgTQFExOIr3T4X5n5sRs6zGc8pQxQmwaxWYJ2mlhXRVRspe5LOuoqowmB/BUhJOhiRqqcVsKxVErzIQCW4NOkTh0rliF1TSw2lpMeoBGM5NzrheNyxOrvocOfuuVMutc3BJweVhDNDEQnHObABd5GbQv8vG6hnful3HS8Wb1x1Na5UXz90F2Z5dLA0uvSXz70lTrfz8eYBuIOROdLlCcF7wfX8mKdHQa03e9Gr7NZknndXtC2Hq+2Krf0atxfEvE5SfHar/jtKwoDzwMQb7+R1SSgL8KcSIQLi3meXCH2Z49Dc3FtsaGqVKVU8t56eMjlFaTZab3QaDLKyyZfthNukhPf49Bmv47bHGRE/ymEdlvyH/NITy+mch8XBUSAUqECz1fFrNwqzlbK7uJP6YfeYuRnvmWdy2xXPb+2A3J+nF/jbM5Fki4XBO+WbTXIG9MWJ+4WmLC6d+rGkWqmGvaP+i8LjE+eaFLI6cYKfHCcNQSV2hZwvaiqbz1PBPuQ8LzRq1Z+cFVqenxYl+JgEeRa7t/PyYGhEDOY3HJGcFegWOsUZ+2Y/ZFn9lJ9WivTulhpvIZpr9grqb6Y35uHficotOmvtjnVVkUZEsxtixZhjRNETH3DfcMYVtCxcPm2M0T/QAUAN8XAs5NfAXaQKmb7txMzxx/bt8l9x1WTeCKtD1ytt7vm6Y74WddcveLsLc+QVq0v63Wb+/Tm87VNAP/aukXzUVwXOwimxUGBX+vTUUIJO5rpxu7uQMRyGEaQ7pUj6cHJjvJa94bdUuiaYdleylDMLweTnWRvUyC8uSEF8SeYJI13cBmxuK4281TlilkCdNFmEQnHFyRa1Vy1rn244h94Kejb6IlGmNbPW1zltyTsdzytFd4JP0nzxE6L7RCKgCUBMvAuqioqpm8Eq2jyyzZxvG+iZz0ItX0OdvW6AUF/bbzyx1SNawjiWDJYwpJLsX4H+WUxYm4ZVBzrRpcb/2q0ZkG7OymyV1VLCg2vM01MWL3YTFzi985XVJ/bNVacXQBbE51HU4uz3/uSke9k8C3ZFxoRPAh5oaUoetrK7h2UZculM4Sq04RjExqr+2ghs+Q0o3uNoc9O9zwjLVaBEcQKSnUDoJpCx9ZdNuk1W15wwAW0dom2/3/qUM4YRjpQAALP/TP+njl825UKVgh8GJ14bCbMd1r7MO+0pfEJClsiLI+0yp2+4nAwPnM7H1IfdUCjawcoo005ieb3GEMi3EE6WXPCtjpZU8KseKSJt2fkeLKcTvSorDNrGWdDI8KPFeHC/lhLktxGOlmAm878IRXhsJ+Lkqij3dYvGymsjvSf60KOvvl2JsKA3hIcT7SkM3XHkIMppMA+dqgSJs8olX65dNA+K/EcG5ZIYlu9ALZHHU8+ed1G/w3YsNmwGZbW4WfPdKoUHpo8OLubfKQ4m/g+v0qtcFlDQ5cz653B9o9pEbgFwshB5AG6LUU/wPpaC3TV46cbyuMINdp6F2mreA+wv2/02+Q7Fzi5waJPZQ7PxOKym5aURT2qTQVBxyKfUP6K7WtQW2TFNEsl7GjQcb4zx8WMA9vNMcJF9wxs/el+VJ+UFfhu7RDxhjx6JEiBPxlL9h3ovLobdUdDXQnz9lvx0rQfqU9/ONHICm1GitDfD8gAIW44jUqgljM+kIOPZ2LO4/ePD906o2tc0tjZyWqYTq1jxb241cNhODAd5J3j4ce2KuMGiquPUFmIXyVOh3VGXgwvNGhZN1JOSK7fHQd1uZlQgp7VlRVaXbWBqklcxmu7565Q+ENZuiTY409s9hwwnh6v3oGwbobpGrteQ8k0F5r5TgqOoRrj9chHIyptm2Pr39GQv7QvOw2du+psgyHU18iU9lCL4wuVzj42k6sZdbU+Yv1gfMR7m1mBybE7VcueSj1gE5CcTfrovfA9TDXQFMrDy9nVRf5mniE7odRjL3T+YbcfFwCFXa6U21k5Ak8LBWEzwtyfFmwoDdoGpCF6dgW5t8xkcREZP2UwL6FAaASGVASYMnbpI9+0ZzjfooLai2FvkMml+5Zwwqn16GbMhLtln4b0Ml4EWtq7oCBf818WTXYMHsJwsvdYvPUiNdlANyu5a+UReQXe+r/tIc2Bg8MZy6A5dd2p9sxDyaUlxSB4B7qfKooaO2IyX9h2MG5vOb3Ul19Kc6V9LyjFg6+TvSUv2+jvCTttJYF0fF2Be2s9cW0Pgww0n5blYgrlJNsYo8UuUiNW7J95Mq9SPOcjnsCxLxXDd3VpjHyMT8qDuR4fHE0R0uXUxqUnxjtS7qXWBj89KuxK4FynDBxzuX4hqAWzGo7DdSVoqCQV2SZNOV2lYwe0l79aAI80sYp9C/vPkqPnakHc+q+zd37gllLv68HOVlP2UkGYQ7nG0lyYJbsjivzyINXugKUrqf+L2FEeS3ZoSyoIWDQN6LaWtTt5jTgHUatGMHP5yh0wywlmjzbDsDTWS1xBQPMj5gAXu77M15yh5nPhZLPRq0687YqyqgtEKVh5PGdUxiLYXPY5VlTVvYuu7L+Rvb531aG87jvEznxKnuzRUYrLeCP5RA5MQzBYrzarJvi/NscsDGw0TrpW5y4ewnWaGmH3nNT4ef3XZxuqq4UBT7ANHoJ/1KcMzaape2Vgi5okxzcTSGS7BADusNYLH5tPyMJHdGSZANYCVuFLmibmgHz0HIMAm8r+OkK0h3EZQmZJpUZREbaImZe6a2s/rKkxeYnikZF1Kza4JIeHk5RBizvxFl4IbX9iiGFpY8hratNvpXpSq2O+fGenUedjUvbBy/ImsbvUI8ETONhmUCgs/59o4kmbGIovU5pMhhBPm4KP7muq2UhWwGJC+LXJkdPrKNX5aLZH7BceRq6b76riyw579ZG/zbdjEFJ0oAYHtY0xa8TseRAf5regSd9UjZ6EnpzjfDv7i/VbTX1cqfDcOJ2LOZJwMCjYGo5fFyBTcmOgbNA/YGuoQJtXtCLUyWNBkzmYMr2yVld642qChkz74RiJh6MidTXHqwruExUZ7IY90rbgplUxpa3RbPPiCSU6RqoUopWN8oaQfOghmAAkGhW/qMaxjNwsK5vkoY8aImFuqKXDMJB9yZ+z2bWb9K1yWeBPUu5O9t3WWO1x1KiE1Om28Ym17PTrEN4If/8Ii5LN9hnoR2gvbby3T99FBGMbVZIhM6XjmkIm86JDS1XzSThWWm0DNAOhxtmXCHNcEwMy0j7OgyA0xeJhN8y2n/NluYhnMOUojO+brK0aBOu/C7lznt8tKfFyArac9LNfr+Yx648Th8YopQPtEWtwUJceG5Mgp/cbfAG6eK+No3hdutUJ42ilqlSso6WqlFUJmIlVkexeJxdL0S1tROEdw/liPbLxtjoduPj/txLGmqV90kYT583tdI6Xoxj5RB5HILArMc8KEn0vsoSjzC89tJhXYLxfQwPSrfAozHyYANY/7fFzlHPAH1ziofiw1D5rGqnNWSxOf+5LjPFzAVBrd/+lzfHlsz18iOH94wUB9zsAcvxxz50n1w9sFKtZyKy9aSmjrm0illZ6ZuQ4IJ24PmQXPX9H/8hSdkKp7GoG9uvCA8kMmjoXTXb2PwJT7wruaLT0cveXMjYEmxoT11CrTmeIyDpunXpGY2RJ0cWq/rV9Jk8YWpCk1dZ1UkSXXz5tJkfIUrJEkx8ozilBlbDamiR5f5/c6unxnVV/uJjYY9J3pXKB6/VkVsUbanGpYHcIUvje6vFbPowxkGYH4pdRivI2KTM9ut/ETMoMk1VZl0dtvkZC0MHLQtuN2bFQppIJZK6MoPDXzRDC+cZQB2yBu36YT5+ZCcvzS8WSDHUvtOXQQjaHJeqRqQbTnetdM+GF+u/75S4X61wX63wX8hvmKL+3ol9/C8R/a4bZz78c9kxPLKgDVWTlTgtg6KxM2c7OJ9nRQLw78vhhHczzDEasjcDovV716/0gmzUqq7kcBYelJb610BcEPahq/yBflD9/dI0D1OMb0/g2Csib9U7b7Hxme4WAMOmLFAr0q2qVQAjgZrpWcOGi8b5kFyu1vUZTWm7g+JHqr9GSnv3A1gxARQuGjBrDfwzpYLN3sS7Exf61R35O1Y0Z5i0V+0wrprvekyqRhJ+mM190pXQvPbEWiNQXyPa2U3td4AV2LO71ZhFs+EHk8g1wz6XMc33pvzNbPyb8nNLnuHiwx3D/qmjx8vnuq0ADb75P7dma/eT9huzPrOfcprfO4+L79O7W7tPQCDWWt+kuhsvvnsjPRMWAgI4HI+jIR5/e6qGSQ33xpE13jTfp0QSE34FXk+BAbS5gKRgKfp4vJvG8qaUnb7otzrg3Ehc8Y0d4VTgzZTZ9R70LzUTlmoJ5/9qlzgcRc4HbsIVdY5caTQ+M2EuJtKXVPR4FYv7J6O1geDNVPL+T42HWqXRb1mrwLY+mriqDpd55rXuT7L2LL/+i/5PuesptvL0koCfXSfUvgdMoUeJgGKEgK/4oyy2CpuMoXf6MI+RpAmRRzxctW7QCzn7Dqju0mC/GiUfZPUekvh/BzWJB36Al12Ln+IVOlCPsPdf3z+8n9vK/Ey1vxs5NRc4rn1nn2B1foGVRMgvjyseJAICvhljMtl0pOhuD5GGLLKKNQHUWQUE23lUi2fHzi7SK+kB1/0seS6+hNo5r3dYJGQ+zw4Hz3xAsiuZx5rJNUARbI1+qJJd32gAQhq33PRK/V4tw/Ih+6irqqR4S0XY6yeo/TdtH5hOEIx/8D8cpO+r5hLuaPoTi/rciwnl6BeXbLJkVrXBQXUzLYDj90fMvLKIoXVlteVwH5Bog745/9HBr0gofhp+gGT9uGZs2EWhvHDZQeLuguj4lAbYoNkB9H7wegySVYzPkLPguJaYEiyKWvETe0o6fP0+9+bLWBKAdf/+7skt6eX0nJ6Ynqm3Xx8e59fYXhcrkwyc/kQiWZgIKaEThpYIjRjICAQxRKBgJN+gEZgcogSbai9t15zpfLWM782nmYl7/18BnoqMAC/cGqE9bJxKymo1R0AgKFJ7y3n6U77YxhU5zfR4+QU96vXKeep16nX7Wxx8GHmmCkLB/Dj5tTtDzC9PSEtLpq7gJjT6aoViUtbkTimFF1hYHatl9BXh/TAIaO+3HdswibalJV3Wzoeb8xAaeMhSeyL5igOnHyncnuVAIadkxN5CLr6+HVmL8qGJ9R/wZwgfg7vhL9nqk/dLb3EoQXULAkmPFtDt81+4zgoUhi+8JxDYnJQaVw/b4NL10xAUlgB62fDQQrfm1ZB0sWsmC+Op/XEafSFAeQnxgZbwSvnCu/FgFL5ACZZfSbnfQ2oUwVhFlRp9dSC4uiGosHys69cUowq+tn1im+hBbOQQCOKcAgUreFlQPUSvW4O8DilkFHej4L3sBRrXOzjISw9DwQRG+tihHIL0h5pSs1pQu0I6OD7c32IL5taGyh3r5xvnLbZkp1AP3xMfKBJnXh1m07DUAJcWlZDVowYYKV3D0RG3jT4y2S+IJVI+JOCuxG9hL100ezdZ0bSAl0UQW5pBTnZRucuDYM98WtHbtEXsawVXpekRGoOsrZKa+cfR8PkOiiXsAfErltVa8XTPC78Tvp6HajUg3AwPBo10bCskttGl7wkhpDKvLyABWgZxnKU6/PSCgVI+taRVZ6O3XbPoBO3FGNdt1CC89MA5EfTbTkPyUnjfT1GwqcNSREzMoroWB06IgApxkpOJLNU6i7pvkFco3Iym7IFmYAMR3aqlh7QRAMIDBFTYFqUuz7oOyQw83kQb6X/oTNiS8MnuOkr4J73d9GDCLAnPDzGZT/B1mspUOKzGsUbeLiQzI56q5uYa/yX8lgnH+CG6dqcQVi0mlRHoWgyHsmABvOybWQ45WKlDPGbWeY5/aDhYA84nmrpEBlgEAGtvws2i51i6iJvo8A1/GvkA3jYTiaqTraLm3T+si6UhOkaF6hBbw7hEHQMnAsgYNX1JSE7WSVLqljCdA/9g3NXXMTO2f5lUgXjGTz9PiaSQDxJZYNzxmTxTM9wfGwLmfDw0BHoGp9xQJfyiD0R/p3XCDVWZIQrF8Ywi5+YPF8N0C7DjJVoBKh6bNNGUSgLVoS794DSRHNI3uIP3dk9wGYpefKjNM19xR5nWwa2sngvaekJ/EF2LfCvEyq5IW1lwVlX1Xp01IUtikVdCeByx4ts2cxJ4O2be89V/4lGyDrYXxeZVQ5xuJgKZDgQfw/j2VvZ59qZNMAgkWRbek5Z+T1OSxmFMmUDcuKxQ9ztt1TPiGad7I0rDiS3Fj45m4QHi+ot6U4aK+HND1vN762LXTZH7rU17Y1tOqpONrbBqO4WmaMGeILwl1kK3H0igpIpfNLwnKQ7sc9UHz72PM9/dpv8rau8dE+xF+6OHFbCyyP1l/defdGh4O0/EmFTY/bfQCf5aWQa9Qwfct/bNDHqzYoB/QbJWpU3ztSjNQ4b5asR6TkX5yX3djmO+61j5GepF8EpWJmVvHT2EYKd+WPgFz8LlEeYuejc642QCe6fqdCiE1p8ZujfyreSeJYQ3o4smVADLhxUY3lmiO93KmS75AL1iXnvd22U85twTvXEhXebzMamSidPUzQxJ6wOzzUqeUO298ji7jDSsjEGYQqoissYQ3ZDBIU+2NrxY8vRKD0jpXOf3RgjFGOqtktPw+eANgc853zV8q46uLe4PEjrzHX4ShVBfd/Enhd8UCDd+3V0+dS1w8vwcqoC1OvLnxEaCkQ8b027Z+WKQtYbL6HaEomhVgpk5EwPo4a9fpMdyg3DIYDT29NNYp4fqze5bO21QWeJ886eVvh/3dd5QwYtFPVzghG4Cs9xjCreEAc9oJc8uzlgl0yJEnSh7s60+itX6JD9NPOV+m4yKqUNIBG95HOazFIquS0/9MjbctL2Sxij3JZsY7zc29L1KF3Ao9+s1bxaQIfJXKgWOowkhRDH2XbnP2xSVzbekL33eEFY0bj2FwituPdn8YDeFhYKUNNPu1jVvHmlAnnhYQMueSjKs4eK9bvtM25qi1jZ0/ci03I=
*/