// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_METIS_HPP
#define BOOST_GRAPH_METIS_HPP

#ifdef BOOST_GRAPH_METIS_NO_INLINE
#define BOOST_GRAPH_METIS_INLINE_KEYWORD
#else
#define BOOST_GRAPH_METIS_INLINE_KEYWORD inline
#endif

#include <string>
#include <iostream>
#include <iterator>
#include <utility>
#include <sstream>
#include <exception>
#include <vector>
#include <algorithm>

namespace boost
{
namespace graph
{

    class BOOST_SYMBOL_VISIBLE metis_exception : public std::exception
    {
    };
    class BOOST_SYMBOL_VISIBLE metis_input_exception : public metis_exception
    {
    };

    class metis_reader
    {
    public:
        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
        typedef double vertex_weight_type;
        typedef double edge_weight_type;

        class edge_iterator
        {
        public:
            typedef std::input_iterator_tag iterator_category;
            typedef std::pair< vertices_size_type, vertices_size_type >
                value_type;
            typedef const value_type& reference;
            typedef const value_type* pointer;
            typedef std::ptrdiff_t difference_type;

        private:
            class postincrement_proxy
            {
                postincrement_proxy(const value_type& value) : value(value) {}

            public:
                reference operator*() const { return value; }

            private:
                value_type value;
                friend class edge_iterator;
            };

        public:
            edge_iterator& operator++();
            postincrement_proxy operator++(int);

            reference operator*() const { return self->edge; }
            pointer operator->() const { return &self->edge; }

            // Default copy constructor and assignment operator are okay

        private:
            edge_iterator(metis_reader* self);
            void advance(bool skip_initial_read);

            metis_reader* self;

            friend class metis_reader;
            friend bool operator==(edge_iterator, edge_iterator);
            friend bool operator!=(edge_iterator, edge_iterator);
        };
        friend class edge_iterator;

        class edge_weight_iterator
        {
        public:
            typedef std::input_iterator_tag iterator_category;
            typedef edge_weight_type value_type;
            typedef const value_type& reference;
            typedef const value_type* pointer;

            // Default copy constructor and assignment operator are okay

            reference operator*() const { return self->edge_weight; }
            pointer operator->() const { return &self->edge_weight; }

            edge_weight_iterator& operator++() { return *this; }
            edge_weight_iterator operator++(int) { return *this; }

        private:
            edge_weight_iterator(metis_reader* self) : self(self) {}

            metis_reader* self;

            friend class metis_reader;
        };

        metis_reader(std::istream& in) : in(in), edge_weight(1.0) { start(); }

        edge_iterator begin();
        edge_iterator end();
        edge_weight_iterator weight_begin();

        vertices_size_type num_vertices() const { return n_vertices; }
        edges_size_type num_edges() const { return n_edges; }

        std::size_t num_vertex_weights() const { return n_vertex_weights; }

        vertex_weight_type vertex_weight(vertices_size_type v, std::size_t n)
        {
            return vertex_weights[v * num_vertex_weights() + n];
        }

        bool has_edge_weights() const { return edge_weights; }

    private:
        void start();

        // Configuration information
        std::istream& in;

        // Information about the current METIS file
        vertices_size_type n_vertices;
        edges_size_type n_edges;
        std::size_t n_vertex_weights;
        bool edge_weights;

        // Information about the current edge/vertex
        std::istringstream line_in;
        std::pair< vertices_size_type, vertices_size_type > edge;
        std::vector< vertex_weight_type > vertex_weights;
        edge_weight_type edge_weight;

        friend bool operator==(edge_iterator, edge_iterator);
        friend bool operator!=(edge_iterator, edge_iterator);
    };

    class metis_distribution
    {
    public:
        typedef int process_id_type;
        typedef std::size_t size_type;
        typedef std::vector< process_id_type >::iterator iterator;

        metis_distribution(std::istream& in, process_id_type my_id);

        size_type block_size(process_id_type id, size_type) const;
        process_id_type operator()(size_type n) const { return vertices[n]; }
        size_type local(size_type n) const;
        size_type global(size_type n) const { return global(my_id, n); }
        size_type global(process_id_type id, size_type n) const;

        iterator begin() { return vertices.begin(); }
        iterator end() { return vertices.end(); }

    private:
        process_id_type my_id;
        std::vector< process_id_type > vertices;
    };

#if !defined(BOOST_GRAPH_METIS_NO_INLINE) || defined(BOOST_GRAPH_METIS_SOURCE)
    BOOST_GRAPH_METIS_INLINE_KEYWORD
    bool operator==(
        metis_reader::edge_iterator x, metis_reader::edge_iterator y)
    {
        return (x.self == y.self
            || (x.self && x.self->edge.first == x.self->num_vertices())
            || (y.self && y.self->edge.first == y.self->num_vertices()));
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    bool operator!=(
        metis_reader::edge_iterator x, metis_reader::edge_iterator y)
    {
        return !(x == y);
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_iterator::edge_iterator(metis_reader* self) : self(self)
    {
        if (self)
            advance(true);
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_iterator& metis_reader::edge_iterator::operator++()
    {
        advance(false);
        return *this;
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    void metis_reader::edge_iterator::advance(bool skip_initial_read)
    {
        do
        {

            if (!skip_initial_read)
            {
                // Try to read the next edge
                if (self->line_in >> std::ws >> self->edge.second)
                {
                    --self->edge.second;
                    if (self->has_edge_weights())
                    {
                        if (!(self->line_in >> self->edge_weight))
                            boost::throw_exception(metis_input_exception());
                    }
                    return;
                }

                // Check if we're done
                ++self->edge.first;
                if (self->edge.first == self->num_vertices())
                    return;
            }

            // Find the next line
            std::string line;
            while (getline(self->in, line) && !line.empty() && line[0] == '%')
            {
                /* Keep reading lines in the loop header... */
            }
            if (!self->in)
                boost::throw_exception(metis_input_exception());
            self->line_in.str(line);
            self->line_in.clear();

            // Read the next line
            std::size_t weights_left = self->n_vertex_weights;
            vertex_weight_type weight;
            while (weights_left > 0)
            {
                if (self->line_in >> weight)
                    self->vertex_weights.push_back(weight);
                else
                    boost::throw_exception(metis_input_exception());
                --weights_left;
            }

            // Successive iterations will pick up edges for this vertex.
            skip_initial_read = false;
        } while (true);
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_iterator::postincrement_proxy
    metis_reader::edge_iterator::operator++(int)
    {
        postincrement_proxy result(**this);
        ++(*this);
        return result;
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_iterator metis_reader::begin()
    {
        if (edge.first != 0)
            start();
        return edge_iterator(this);
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_iterator metis_reader::end() { return edge_iterator(0); }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    metis_reader::edge_weight_iterator metis_reader::weight_begin()
    {
        return edge_weight_iterator(this);
    }

    BOOST_GRAPH_METIS_INLINE_KEYWORD
    void metis_reader::start()
    {
        in.seekg(0, std::ios::beg);
        std::string line;
        while (getline(in, line) && !line.empty() && line[0] == '%')
        {
            /* Keep getting lines in loop header. */
        }

        if (!in || line.empty())
            boost::throw_exception(metis_input_exception());

        // Determine number of vertices and edges in the graph
        line_in.str(line);
        if (!(line_in >> n_vertices >> n_edges))
            boost::throw_exception(metis_input_exception());

        // Determine whether vertex or edge weights are included in the graph
        int fmt = 0;
        line_in >> fmt;
        n_vertex_weights = fmt / 10;
        edge_weights = (fmt % 10 == 1);

        // Determine how many (if any!) vertex weights are included
        if (n_vertex_weights)
            line_in >> n_vertex_weights;

        // Setup the iteration data structures
        edge_weight = 1.0;
        edge.first = 0;
        edge.second = 0;
        vertex_weights.reserve(n_vertex_weights * num_vertices());
    }

    metis_distribution::metis_distribution(
        std::istream& in, process_id_type my_id)
    : my_id(my_id)
    , vertices(std::istream_iterator< process_id_type >(in),
          std::istream_iterator< process_id_type >())
    {
    }

    metis_distribution::size_type metis_distribution::block_size(
        process_id_type id, size_type) const
    {
        return std::count(vertices.begin(), vertices.end(), id);
    }

    metis_distribution::size_type metis_distribution::local(size_type n) const
    {
        return std::count(vertices.begin(), vertices.begin() + n, vertices[n]);
    }

    metis_distribution::size_type metis_distribution::global(
        process_id_type id, size_type n) const
    {
        std::vector< process_id_type >::const_iterator i = vertices.begin();
        while (*i != id)
            ++i;

        while (n > 0)
        {
            do
            {
                ++i;
            } while (*i != id);
            --n;
        }

        return i - vertices.begin();
    }

#endif

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_METIS_HPP

/* metis.hpp
0wsQ+4l4qquzqc5HHL9Hi6Yy3jf3Akf1zM/gHCAX52Cy7GFTpS0mC/aOBItxX+ajtHieuM/7hc4/KjCYDYMOZKKN7cBxqM/z+JMhD7BPTQ+ZR/LrlPC7Icb4gDIamxEX1x7hPyUD6XFU3x9snuZ+hlFdnpJasXmSyt1Kkt0k1cPOEdFfdM8dCbyPfkJtuK11MOuNtccRrLs0W/qTJYc14X21iuw+K6AH+mo0+upwqcJ0xDzQNDggUMcNmNG1lZdoDI0QbUMpY7CujFcsct5zsbiX43nhn4PuxeWxppzsXs56wC9VFMklWc7bQ6DwCalvq4V52njcgPReNl8rLTMp1xz/zkP12fXqQjnPANNq6X7Fp46w8a6QPWyHeZz1PlNqUEPTkhC7sS7CNocX0TOVlIQVy6pfoE8Wy7Jw5myXLLRirU0kUb4gHkctKB6iq2shKqvdp3eh9HAed6c/H41Gs9E2qoOtVhvJc4ZdQ5VvcuxHpcw3nQowmeth0qChVZ0zqORzBtr508SZqNfOcrKZOO4D5eIZRjduHDfJY6b8XKkec5s4Zj4/ZmOfjin3zbZ0jHa19muav+THOhTL5y+Dly2yB8/3NH9Jumdj1fnLZRsNz8Si7nFxqs7yJLslzG5G3KArjt0vTj32Chw72d2xhW6RKHfFd3ZzA2OZoo5Vql7YapsnncdEWasXe6rbCaGz5g06nge9oHrqOdzcwB7cu1b+2kBXKfPmjsbyRkgTIkcy3/0NzeHPVbuA9yG8RHElvM1DFYLqY+iYnKbT2c5xLcKd/O9KjmN1fu5DkcfCn+XMwGD+tz5YuSyLlz+ZIwLmR7R0jhQC8PfNQH0IiRV1NwaRT1+uDcFQFuLOc6nnWO3Pm2eAeN4Ufo0ilmh+jRxlmr+dTlx2eI6r36Bn5rj6DfrDHFe/QXvmuPoNumuOq9+g9XNcfQSt0GSpwn/PHFcfQWVzXH0EzZrj6iNIKnX2ERQGWfZCnY8NxEeVOfv4oWdWydWnT1fJ1adPlZNPH82/RqWTXPNt/hQQ10TIMbQb5rp68Im1J3GcZI5FkDmWiGdh7jRFm+sKjXAz10X6mWKu6y6Kz5Cm8rmuUNe5LnFd3US6pVKINFWb/yJZf/Hc9ufrle8H8ftU49wXXbvTNF9tPP9kxUeeBX2Y4n0l/n0Qbf5L6HYS92DLKb5UqpACmaY/VMyPraX0hdJMKdh5/gty43wU5XXj028p6fbR5r8M+c8gf21zsmdId702H2bIf66W+bBsp+cPYQ9hyzuI686kO6iWuTOH672S+IbBc1SXQVIr1LGXZPE49/WSwgO+dRAhkQyxenT8V9gUPKckYywP1ua+KLSL1ObAMH6hJtocWKWXObAS3RxY4A1iDkwZH/icFmzmNAd2SMgMc2BiXsv9HNhxkW86xU9SXJsDO8Pjxn58zsMcWLaHOTDtnZOoG8kdxrkx4/dlGvO9Xgj0DUSEGSg/gnipVKaN+EspD++kuG6CeN5sS/H92FcZoJvbonFH9PfWpPM4ZjttSn8X5dQ33oeKe+a+lL4Pe1Ul4Yt5G/QSo3TXZh98Mdf2jg/HFWOk5jvo8vlmce8T5vL5nLnSvoaky+STx72vIc++cfIjZfnWsibjnm/x0n25u5ed/2HDXZ968jXkyReTJx9QnnwEefIN5cm3kv8+ozz5UIoIQ5A+evh870c37dw54csjYybedfqUJx8+nnwoefL15MlnlCefSJ58N9XuO6gjAn64f4eOSfl+4LPa3/QMVolyS+hdn/J3L/yt7DHl61eAKRLSDHtMm0JUD9gcmABsAWwMvBbYBtgK2B3YEtibxx3AZGAWsA3wFi6/G9gNuJvnfxQ=
*/