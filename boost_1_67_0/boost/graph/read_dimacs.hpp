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