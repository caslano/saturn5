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
sSC4bf7EguB9lm9fELzP8gpbZs7jUltmzmOMLTPn0d+WmfPobMvMeTSxZeY8IhYE77382fzgvZdftGXmPB6yZSbNN9kyk755tsykJX9+8Pz1FFvW2aTPlpk8eO0yIzPnu9SWpXj71WoYWRex3zfPa+8k9juMvWPA90bqLJ/vjdRTyKin7D4mfU8pl3r4XYmHJ5t+y6k537ZLn5uu//Z1C0uOQQ6bjyTxjrFI6k8eNOXTSws7lOZPzndHFfS99gKHV/cU8w18u9ijfrMe9947P4q+bd+1yL6Xti4KXj9g06Lga7LWlpnrvmpR8HWqtGWmLCxZFHzt5toyUz6mLQq+nqVG1lXsRcaeKva8Rf7Xe6ixdxZ71iL/659h7B3lukbZ35H/q9cV+L3WDwixHkCIefmh1zMokPUDtp15oPTk6aOHTav3fOMmM07+OdT6AaHWLQi1rsCJrwdwousQVD3P/sTXFah63YX/nfUG/pl1BVr5rCvwlkPWFZDvGsn8drrkW6P8Pg9D1KwaqWN+IPebuLlgcw2HLRPmunkURsIv4Jcwy62r/vLUXyTsheGQPdIawvqwKWwAW8KGsDVsBDvDRJitdm965v5Ker7R9HwLI+F3mp5jZlyKjJERf+fw+xPIIXvn1YR7YRp8Dp4P98MLYDzx91d7NjwAh8M45LnqXgD/hnw8fAlOVvep6j4Lyh568HW4Ab4Jb1O9rap3j7ofUneMuL+j7h/Cd3Ue+vvwmLr/pO5Oh2evvVh4BNaBbvcGMB42hp8jPxV+Adup+5nqngq/Qd4TfgcvUPcB6p4D/478YvgjLFT3S9R9IrTgCgeAa6EL3qJ6t6nenar3EgyDLbiPwmEKjIRdYBw8B8bDNFgDHoTR8A0YC99XvY9V73O4z50/Yrf3bpLxLWA5Jjlg76b70D8J7oBnwsdhJ7gbng0fgn3hLpgHH4GF8FE4U+VXqL+l4s+UV8anhC6vE9FzsxRGwknqL9U7rkTHo+BP/LSBHLJ37mmwO2wDe8LesBfsA3vDUng+nAoz4E0wE96u+rthf/gkHADfhtnQHWkOjIGDYSIcAlPghbATHAEz4EWwH7wYDoJ5MB+OhUVwHJwAL4EPw2L4FJwA98MSeBBOhMmc52R4JiyHA2AFHAWnwiI4DS6B2XAjnAGfhnnwgOjZe6lK3zi8XPPd7KWq6zbEw6mwAZwJU+GlUPaDhrLvNJyo8llwPZwPN0DvXqrSfwy7aDz2XqrQQTzwPJgMM2BLmAbbwPNhe5V/Cadh8jS8/RpeLCzW8Pqi1xz2U/8DYQc4CPaBQ+A8eBFcAEfCpfBieDW8EG6Fw+B2OBw+AHOh1tv0BYaut5tpvX0KbAqbw5awBWwNW8HOsCXMFru9Tov072l/X3LAOi05TupfmAvbwjzYAebDjvAI7AoLYDc4Do6HE+B8OBluhmVwOyyH++EU+J3aw4jrfVgXfghbwSOwLZwB0+AC2BsuhCPhIjgWLoHF8Ao4G14JN8Fr4Ha4Aj4BV8Kn4XXwJ7gGdnbveQq7wSOwJ7wZLoDr4YPqvlvd98LN8Ci8DTZx4Q5bwiOwNbwbdofbYIm6T1H3mXAHXAIfhlfAF+Ej8DW4B74Jn4Ez4fNwFnwZXgpfhXPhYQ3vU/gRPCmMeGB9eMS7t6ClfS6wrZaXcNjR+y1L9xKOgZEwCtZQextYC3rLfZaG82BwuafeI354BkyGKfB8tefAjrAEdoJzYWe4DnaBG2Aq3Azbw7tgB3ifyr+ERZZ+34c83yT+aH5fZPqXeG7CDrAUdoRlsCtcAc+C78Nz4EfwPPgZTIO1CasH7ArTzXNBvxvDOlU8Fxyab04YD10Qfwj1uy18Uv0=
*/