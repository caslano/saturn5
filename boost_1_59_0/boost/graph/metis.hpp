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
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
*/