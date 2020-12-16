// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CONTAINER_PROPERTY_MAP_HPP
#define BOOST_GRAPH_CONTAINER_PROPERTY_MAP_HPP

#include <boost/graph/detail/index.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{
// This is an adapter built over the iterator property map with
// more useful uniform construction semantics. Specifically, this
// requires the container rather than the iterator and the graph
// rather than the optional index map.
template < typename Graph, typename Key, typename Container >
struct container_property_map
: public boost::put_get_helper<
      typename iterator_property_map< typename Container::iterator,
          typename property_map< Graph,
              typename detail::choose_indexer< Graph,
                  Key >::index_type >::type >::reference,
      container_property_map< Graph, Key, Container > >
{
    typedef typename detail::choose_indexer< Graph, Key >::indexer_type
        indexer_type;
    typedef typename indexer_type::index_type index_type;
    typedef iterator_property_map< typename Container::iterator,
        typename property_map< Graph, index_type >::type >
        map_type;
    typedef typename map_type::key_type key_type;
    typedef typename map_type::value_type value_type;
    typedef typename map_type::reference reference;
    typedef typename map_type::category category;

    // The default constructor will *probably* crash if its actually
    // used for referencing vertices since the underlying iterator
    // map points past the end of an unknown container.
    inline container_property_map() : m_map() {}

    // This is the preferred constructor. It is invoked over the container
    // and the graph explicitly. This requires that the underlying iterator
    // map use the indices of the vertices in g rather than the default
    // identity map.
    //
    // Note the const-cast this ensures the reference type of the
    // vertex index map is non-const, which happens to be an
    // artifact of passing const graph references.
    inline container_property_map(Container& c, const Graph& g)
    : m_map(c.begin(), indexer_type::index_map(const_cast< Graph& >(g)))
    {
    }

    // Typical copy constructor.
    inline container_property_map(const container_property_map& x)
    : m_map(x.m_map)
    {
    }

    // The [] operator delegates to the underlying map/
    inline reference operator[](const key_type& k) const { return m_map[k]; }

    map_type m_map;
};
}

#endif

/* container_property_map.hpp
7kXg707+bmaOGaCfb2dIHA6d4FpHHNNB30C6zsggjV+kdyMv13nXUKlX1dD9ZcN+T577mDT8W+meqn3Gd0hXInzQGv4TmJ1dBR4Nv3i5Yy/Qw+QpNTJIW35+iNEU7PS70J74afa+nxfI11VozXeu062CXPoSHeGj3IMwJ5jQGEd2N/LIbswzuyHx0wl18LGIn+TFwQDGSjHO5JJvHPh2Rvia1iVZPI8LjyXHvwv6CZhdMN+D+T7Mk0LvbkA7jOg5Wc317CVo6C32m+E63qgiHa3TIde8h12HOfaVdralq8G/pjDMT5g9iKcAhu2sqmpJuCa/umxBRWHNkqoSa+z7ONu1Wmv7oj/KXb1LROX0/Gid5bcap5lHTgIiDqRb43CfwewR9XAUJhPmCMxJlHlY0l1VXp1fWlMTzp9XxLr2eXTevGa5Y+57LXnHgta1DPi31zJmRNepF+neNnVvxfY8xLDlDno/bQc7yRNUvWIP6Uv1TOe5IbmHBH4TWJ8jybXPSV5P/v3IRTPaTtKEx6GrdGEYWaozvUk/42PEAXelExjeM80lvOKw9hnP0/9kfNdozZ+f0m4NbBK5pnon6sqQ7phLZJsoCCagTXjre4bwXQy+PRG+pJDy/NDDUwueZyI8KbV79by+8FjxPajx1T6ECH3jO2CFlVR7pV9YJ8CzlzKgKpiACuY9P2+Ns/aBfg5mv4VnMI/8OefyWM90Pgr1CHasR671uSE9owF0gkmFaQXzSqTtsaxqEUh+Nfa8zKspr1yQX44dC/m8oIFleKi51me77YVsvTdV5tVrSqXu2u4q814Az4/TjAbvQ0Kc7m/TcRbjcX1bbu9oALNFtuTB/BL+N7u/bWlJVdn8FflY7ymsYUfu+Tadi7qX/kZz79sIGPlmCS9D5zPAcx5zye7ThWc2dOoeqiPuo11bpC3e5ZdfIn7zYvjN8/pVHaGiUmImX1kMv2Wn9MuYYTc2fTL8ojzEv6n3LmWg3ALAnyCtL8H89AzqpbPsQq6y0/zyjJ01LzxjZ/1Oz9hZv8HVv7wq9aCP1PHuojsdi9aD4hJsj6lckW9vYDbsdvmztEgc07jP+Z2OsEhUNi3/+BaUc6etw07d0jgLJhI+TBbM0zAR+ZnDsGpx+Q26DSwI5NdAydDxYr0xsvC3Upl8DuntLl2UbU9526q+ci7pR53jD13PLIimQ8+4v4ywDsIcEnMY5hXbzrY/g/pgsozle1gfVJdw74eUvAKwHXeGGdkc5Sd5hQFdZD6BG7b95gUzgOTXMTp+Z8EgHp17akDaOe8fYw6H+5KydK7Elf7avlr/mP5Okv6cLFf6McA9ZfrB705/P9IJDU3/hNOlf6hP+nP7xc7/PHf6UZCnTn+eJ/2FZ5b/p03/pT7p3y3p7wiTKu1tIBJQG00/J+gq86trissqTtuGI/FssuMhfafQ13jirekf9TgMJlPwffDslHixCwKFXlyyXNr3e+xziotAajt8gbwdpb1bfkO6v+JD0qb2p0fOsA2+R5nMOF267eaBUeafS5m/CPMReI9F0x7ZB1sczl9SZa0ZhzKY9rC9H0R4EUJf41bHWGsB9X/rTsBeLSM8G+h+VYbcM+YYzw2je2rMveZd6VaH0V0q/R9PF//V9v7wLPLchRhM8pxHPXZJVZlj3DaZPOgfZdzWl/Qi9PMDVY+BH1zcZKdrPnkyVV9eQXow0pkTKxzOyy9HffhyAM5VU//rzX3oF/vvQyd/Dsrh19Q9c+uP/aQvfgP0mzBvnUG5hziukfJytSkpH9RrfJPsvXX3p/GDogE+AtMWZou0p73kry0trI42pvxlhWU1WI62xmulzVh+FeElNVUl86Jzod0=
*/