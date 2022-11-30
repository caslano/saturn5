//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

/*
  Reads maximal flow problem in extended DIMACS format.
  This works, but could use some polishing.
*/

/* ----------------------------------------------------------------- */

#ifndef BOOST_GRAPH_READ_DIMACS_HPP
#define BOOST_GRAPH_READ_DIMACS_HPP

#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <boost/graph/graph_traits.hpp>

namespace boost
{

namespace detail
{

    template < class Graph, class CapacityMap, class ReverseEdgeMap >
    int read_dimacs_max_flow_internal(Graph& g, CapacityMap capacity,
        ReverseEdgeMap reverse_edge,
        typename graph_traits< Graph >::vertex_descriptor& src,
        typename graph_traits< Graph >::vertex_descriptor& sink,
        std::istream& in, bool require_source_and_sink,
        const std::string& problem_type)
    {
        //  const int MAXLINE = 100;      /* max line length in the input file
        //  */
        const int ARC_FIELDS = 3; /* no of fields in arc line  */
        const int NODE_FIELDS = 2; /* no of fields in node line  */
        const int P_FIELDS = 3; /* no of fields in problem line */

        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;
        typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;

        std::vector< vertex_descriptor > verts;

        long m, n, /*  number of edges and nodes */
            i, head, tail, cap;

        long no_lines = 0, /* no of current input line */
            no_plines = 0, /* no of problem-lines */
            no_nslines = 0, /* no of node-source-lines */
            no_nklines = 0, /* no of node-source-lines */
            no_alines = 0; /* no of arc-lines */

        std::string in_line; /* for reading input line */
        char pr_type[4]; /* for reading type of the problem */
        char nd; /* source (s) or sink (t) */

        int k, /* temporary */
            err_no; /* no of detected error */

        /* -------------- error numbers & error messages ---------------- */
        const int EN1 = 0;
        const int EN2 = 1;
        const int EN3 = 2;
        const int EN4 = 3;
        //  const int EN6   = 4;
        //  const int EN10  = 5;
        //  const int EN7   = 6;
        const int EN8 = 7;
        const int EN9 = 8;
        const int EN11 = 9;
        const int EN12 = 10;
        //  const int EN13 = 11;
        const int EN14 = 12;
        const int EN16 = 13;
        const int EN15 = 14;
        const int EN17 = 15;
        const int EN18 = 16;
        const int EN21 = 17;
        const int EN19 = 18;
        const int EN20 = 19;
        const int EN22 = 20;

        static const char* err_message[] = {
            /* 0*/ "more than one problem line.",
            /* 1*/ "wrong number of parameters in the problem line.",
            /* 2*/ "it is not a Max Flow problem line.",
            /* 3*/ "bad value of a parameter in the problem line.",
            /* 4*/ "can't obtain enough memory to solve this problem.",
            /* 5*/ "more than one line with the problem name.",
            /* 6*/ "can't read problem name.",
            /* 7*/ "problem description must be before node description.",
            /* 8*/ "this parser doesn't support multiply sources and sinks.",
            /* 9*/ "wrong number of parameters in the node line.",
            /*10*/ "wrong value of parameters in the node line.",
            /*11*/ " ",
            /*12*/
            "source and sink descriptions must be before arc descriptions.",
            /*13*/ "too many arcs in the input.",
            /*14*/ "wrong number of parameters in the arc line.",
            /*15*/ "wrong value of parameters in the arc line.",
            /*16*/ "unknown line type in the input.",
            /*17*/ "reading error.",
            /*18*/ "not enough arcs in the input.",
            /*19*/ "source or sink doesn't have incident arcs.",
            /*20*/ "can't read anything from the input file."
        };
        /* --------------------------------------------------------------- */

        /* The main loop:
           -  reads the line of the input,
           -  analyses its type,
           -  checks correctness of parameters,
           -  puts data to the arrays,
           -  does service functions
        */

        while (std::getline(in, in_line))
        {
            ++no_lines;

            switch (in_line[0])
            {
            case 'c': /* skip lines with comments */
            case '\n': /* skip empty lines   */
            case '\0': /* skip empty lines at the end of file */
                break;

            case 'p': /* problem description      */
                if (no_plines > 0)
                /* more than one problem line */
                {
                    err_no = EN1;
                    goto error;
                }

                no_plines = 1;

                if (
                    /* reading problem line: type of problem, no of nodes, no of
                       arcs */
                    std::sscanf(
                        in_line.c_str(), "%*c %3s %ld %ld", pr_type, &n, &m)
                    != P_FIELDS)
                /*wrong number of parameters in the problem line*/
                {
                    err_no = EN2;
                    goto error;
                }

                if (pr_type != problem_type)
                /*wrong problem type*/
                {
                    err_no = EN3;
                    goto error;
                }

                if (n <= 0 || m <= 0)
                /*wrong value of no of arcs or nodes*/
                {
                    err_no = EN4;
                    goto error;
                }

                {
                    for (long vi = 0; vi < n; ++vi)
                        verts.push_back(add_vertex(g));
                }
                break;

            case 'n': /* source(s) description */
                if (no_plines == 0)
                /* there was not problem line above */
                {
                    err_no = EN8;
                    goto error;
                }

                /* reading source  or sink */
                k = std::sscanf(in_line.c_str(), "%*c %ld %c", &i, &nd);
                --i; // index from 0
                if (k < NODE_FIELDS)
                /* node line is incorrect */
                {
                    err_no = EN11;
                    goto error;
                }

                if (i < 0 || i > n)
                /* wrong value of node */
                {
                    err_no = EN12;
                    goto error;
                }

                switch (nd)
                {
                case 's': /* source line */

                    if (no_nslines != 0)
                    /* more than one source line */
                    {
                        err_no = EN9;
                        goto error;
                    }

                    no_nslines = 1;
                    src = verts[i];
                    break;

                case 't': /* sink line */

                    if (no_nklines != 0)
                    /* more than one sink line */
                    {
                        err_no = EN9;
                        goto error;
                    }

                    no_nklines = 1;
                    sink = verts[i];
                    break;

                default:
                    /* wrong type of node-line */
                    err_no = EN12;
                    goto error;
                }
                break;

            case 'a': /* arc description */
                if (require_source_and_sink
                    && (no_nslines == 0 || no_nklines == 0))
                /* there was not source and sink description above */
                {
                    err_no = EN14;
                    goto error;
                }

                if (no_alines >= m)
                /*too many arcs on input*/
                {
                    err_no = EN16;
                    goto error;
                }

                if (
                    /* reading an arc description */
                    std::sscanf(
                        in_line.c_str(), "%*c %ld %ld %ld", &tail, &head, &cap)
                    != ARC_FIELDS)
                /* arc description is not correct */
                {
                    err_no = EN15;
                    goto error;
                }

                --tail; // index from 0, not 1
                --head;
                if (tail < 0 || tail > n || head < 0 || head > n)
                /* wrong value of nodes */
                {
                    err_no = EN17;
                    goto error;
                }

                {
                    edge_descriptor e1, e2;
                    bool in1, in2;
                    boost::tie(e1, in1) = add_edge(verts[tail], verts[head], g);
                    boost::tie(e2, in2) = add_edge(verts[head], verts[tail], g);
                    if (!in1 || !in2)
                    {
                        std::cerr << "unable to add edge (" << head << ","
                                  << tail << ")" << std::endl;
                        return -1;
                    }
                    capacity[e1] = cap;
                    capacity[e2] = 0;
                    reverse_edge[e1] = e2;
                    reverse_edge[e2] = e1;
                }
                ++no_alines;
                break;

            default:
                /* unknown type of line */
                err_no = EN18;
                goto error;

            } /* end of switch */
        } /* end of input loop */

        /* ----- all is red  or  error while reading ----- */

        if (in.eof() == 0) /* reading error */
        {
            err_no = EN21;
            goto error;
        }

        if (no_lines == 0) /* empty input */
        {
            err_no = EN22;
            goto error;
        }

        if (no_alines < m) /* not enough arcs */
        {
            err_no = EN19;
            goto error;
        }

        if (require_source_and_sink
            && (out_degree(src, g) == 0 || out_degree(sink, g) == 0))
        /* no arc goes out of the source */
        {
            err_no = EN20;
            goto error;
        }

        /* Thanks God! all is done */
        return (0);

        /* ---------------------------------- */
    error: /* error found reading input */

        std::printf(
            "\nline %ld of input - %s\n", no_lines, err_message[err_no]);

        return -1;
    }
    /* --------------------   end of parser  -------------------*/

} // namespace detail

template < class Graph, class CapacityMap, class ReverseEdgeMap >
int read_dimacs_max_flow(Graph& g, CapacityMap capacity,
    ReverseEdgeMap reverse_edge,
    typename graph_traits< Graph >::vertex_descriptor& src,
    typename graph_traits< Graph >::vertex_descriptor& sink,
    std::istream& in = std::cin)
{
    return detail::read_dimacs_max_flow_internal(
        g, capacity, reverse_edge, src, sink, in, true, "max");
}

template < class Graph, class CapacityMap, class ReverseEdgeMap >
int read_dimacs_min_cut(Graph& g, CapacityMap capacity,
    ReverseEdgeMap reverse_edge, std::istream& in = std::cin)
{
    typename graph_traits< Graph >::vertex_descriptor dummy_src,
        dummy_sink; // Not filled in
    return detail::read_dimacs_max_flow_internal(
        g, capacity, reverse_edge, dummy_src, dummy_sink, in, false, "cut");
}

} // namespace boost

#endif // BOOST_GRAPH_READ_DIMACS_HPP

/* read_dimacs.hpp
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
*/