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