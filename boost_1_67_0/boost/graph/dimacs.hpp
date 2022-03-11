// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Alex Breuer
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DIMACS_HPP
#define BOOST_GRAPH_DIMACS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <exception>
#include <vector>
#include <queue>
#include <boost/assert.hpp>

namespace boost
{
namespace graph
{

    class BOOST_SYMBOL_VISIBLE dimacs_exception : public std::exception
    {
    };

    class dimacs_basic_reader
    {
    public:
        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;
        typedef double vertex_weight_type;
        typedef double edge_weight_type;
        typedef std::pair< vertices_size_type, vertices_size_type > edge_type;
        enum incr_mode
        {
            edge,
            edge_weight
        };

        dimacs_basic_reader(std::istream& in, bool want_weights = true)
        : inpt(in), seen_edges(0), want_weights(want_weights)
        {
            while (getline(inpt, buf) && !buf.empty() && buf[0] == 'c')
                ;

            if (buf[0] != 'p')
            {
                boost::throw_exception(dimacs_exception());
            }

            std::stringstream instr(buf);
            std::string junk;

            instr >> junk >> junk >> num_vertices >> num_edges;
            read_edge_weights.push(-1);
            incr(edge_weight);
        }

        // for a past the end iterator
        dimacs_basic_reader()
        : inpt(std::cin)
        , num_vertices(0)
        , num_edges(0)
        , seen_edges(0)
        , want_weights(false)
        {
        }

        edge_type edge_deref()
        {
            BOOST_ASSERT(!read_edges.empty());
            return read_edges.front();
        }

        inline edge_type* edge_ref()
        {
            BOOST_ASSERT(!read_edges.empty());
            return &read_edges.front();
        }

        inline edge_weight_type edge_weight_deref()
        {
            BOOST_ASSERT(!read_edge_weights.empty());
            return read_edge_weights.front();
        }

        inline dimacs_basic_reader incr(incr_mode mode)
        {
            if (mode == edge)
            {
                BOOST_ASSERT(!read_edges.empty());
                read_edges.pop();
            }
            else if (mode == edge_weight)
            {
                BOOST_ASSERT(!read_edge_weights.empty());
                read_edge_weights.pop();
            }

            if ((mode == edge && read_edges.empty())
                || (mode == edge_weight && read_edge_weights.empty()))
            {

                if (seen_edges > num_edges)
                {
                    boost::throw_exception(dimacs_exception());
                }

                while (getline(inpt, buf) && !buf.empty() && buf[0] == 'c')
                    ;

                if (!inpt.eof())
                {
                    int source, dest, weight;
                    read_edge_line((char*)buf.c_str(), source, dest, weight);

                    seen_edges++;
                    source--;
                    dest--;

                    read_edges.push(edge_type(source, dest));
                    if (want_weights)
                    {
                        read_edge_weights.push(weight);
                    }
                }
                BOOST_ASSERT(read_edges.size() < 100);
                BOOST_ASSERT(read_edge_weights.size() < 100);
            }

            // the 1000000 just happens to be about how many edges can be read
            // in 10s
            //     if( !(seen_edges % 1000000) && !process_id( pg ) && mode ==
            //     edge ) {
            //       std::cout << "read " << seen_edges << " edges" <<
            //       std::endl;
            //     }
            return *this;
        }

        inline bool done_edges()
        {
            return inpt.eof() && read_edges.size() == 0;
        }

        inline bool done_edge_weights()
        {
            return inpt.eof() && read_edge_weights.size() == 0;
        }

        inline vertices_size_type n_vertices() { return num_vertices; }

        inline vertices_size_type processed_edges()
        {
            return seen_edges - read_edges.size();
        }

        inline vertices_size_type processed_edge_weights()
        {
            return seen_edges - read_edge_weights.size();
        }

        inline vertices_size_type n_edges() { return num_edges; }

    protected:
        bool read_edge_line(char* linebuf, int& from, int& to, int& weight)
        {
            char *fs = NULL, *ts = NULL, *ws = NULL;
            char* tmp = linebuf + 2;

            fs = tmp;
            if ('e' == linebuf[0])
            {
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ts = ++tmp;
                        break;
                    }
                    tmp++;
                }
                *tmp = '\0';
                if (NULL == fs || NULL == ts)
                    return false;
                from = atoi(fs);
                to = atoi(ts);
                weight = 0;
            }
            else if ('a' == linebuf[0])
            {
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ts = ++tmp;
                        break;
                    }
                    tmp++;
                }
                while (*tmp != '\n' && *tmp != '\0')
                {
                    if (*tmp == ' ')
                    {
                        *tmp = '\0';
                        ws = ++tmp;
                        break;
                    }
                    tmp++;
                }
                while (*tmp != '\n' && *tmp != '\0')
                    tmp++;
                *tmp = '\0';
                if (fs == NULL || ts == NULL || ws == NULL)
                    return false;
                from = atoi(fs);
                to = atoi(ts);
                if (want_weights)
                    weight = atoi(ws);
                else
                    weight = 0;
            }
            else
            {
                return false;
            }

            return true;
        }

        std::queue< edge_type > read_edges;
        std::queue< edge_weight_type > read_edge_weights;

        std::istream& inpt;
        std::string buf;
        vertices_size_type num_vertices, num_edges, seen_edges;
        bool want_weights;
    };

    template < typename T > class dimacs_edge_iterator
    {
    public:
        typedef dimacs_basic_reader::edge_type edge_type;
        typedef dimacs_basic_reader::incr_mode incr_mode;

        typedef std::input_iterator_tag iterator_category;
        typedef edge_type value_type;
        typedef value_type reference;
        typedef edge_type* pointer;
        typedef std::ptrdiff_t difference_type;

        dimacs_edge_iterator(T& reader) : reader(reader) {}

        inline dimacs_edge_iterator& operator++()
        {
            reader.incr(dimacs_basic_reader::edge);
            return *this;
        }

        inline edge_type operator*() { return reader.edge_deref(); }

        inline edge_type* operator->() { return reader.edge_ref(); }

        // don't expect this to do the right thing if you're not comparing
        // against a general past-the-end-iterator made with the default
        // constructor for dimacs_basic_reader
        inline bool operator==(dimacs_edge_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return arg.reader.done_edges();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return reader.done_edges();
            }
            else
            {
                return false;
            }
            return false;
        }

        inline bool operator!=(dimacs_edge_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return !arg.reader.done_edges();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return !reader.done_edges();
            }
            else
            {
                return true;
            }
            return true;
        }

    private:
        T& reader;
    };

    template < typename T > class dimacs_edge_weight_iterator
    {
    public:
        typedef dimacs_basic_reader::edge_weight_type edge_weight_type;
        typedef dimacs_basic_reader::incr_mode incr_mode;

        dimacs_edge_weight_iterator(T& reader) : reader(reader) {}

        inline dimacs_edge_weight_iterator& operator++()
        {
            reader.incr(dimacs_basic_reader::edge_weight);
            return *this;
        }

        inline edge_weight_type operator*()
        {
            return reader.edge_weight_deref();
        }

        // don't expect this to do the right thing if you're not comparing
        // against a general past-the-end-iterator made with the default
        // constructor for dimacs_basic_reader
        inline bool operator==(dimacs_edge_weight_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return arg.reader.done_edge_weights();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return reader.done_edge_weights();
            }
            else
            {
                return false;
            }
            return false;
        }

        inline bool operator!=(dimacs_edge_weight_iterator arg)
        {
            if (reader.n_vertices() == 0)
            {
                return !arg.reader.done_edge_weights();
            }
            else if (arg.reader.n_vertices() == 0)
            {
                return !reader.done_edge_weights();
            }
            else
            {
                return true;
            }
            return true;
        }

    private:
        T& reader;
    };

}
} // end namespace boost::graph
#endif

/* dimacs.hpp
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
*/