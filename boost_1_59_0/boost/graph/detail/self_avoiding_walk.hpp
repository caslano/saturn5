//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_SELF_AVOIDING_WALK_HPP
#define BOOST_SELF_AVOIDING_WALK_HPP

/*
  This file defines necessary components for SAW.

  mesh language: (defined by myself to clearify what is what)
  A triangle in mesh is called an triangle.
  An edge in mesh is called an line.
  A vertex in mesh is called a point.

  A triangular mesh corresponds to a graph in which a vertex is a
  triangle and an edge(u, v) stands for triangle u and triangle v
  share an line.

  After this point, a vertex always refers to vertex in graph,
  therefore it is a traingle in mesh.

 */

#include <utility>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

#define SAW_SENTINAL -1

namespace boost
{

template < class T1, class T2, class T3 > struct triple
{
    T1 first;
    T2 second;
    T3 third;
    triple(const T1& a, const T2& b, const T3& c)
    : first(a), second(b), third(c)
    {
    }
    triple() : first(SAW_SENTINAL), second(SAW_SENTINAL), third(SAW_SENTINAL) {}
};

typedef triple< int, int, int > Triple;

/* Define a vertex property which has a triangle inside. Triangle is
  represented by a triple.  */
struct triangle_tag
{
    enum
    {
        num = 100
    };
};
typedef property< triangle_tag, Triple > triangle_property;

/* Define an edge property with a line. A line is represented by a
  pair.  This is not required for SAW though.
*/
struct line_tag
{
    enum
    {
        num = 101
    };
};
template < class T >
struct line_property : public property< line_tag, std::pair< T, T > >
{
};

/*Precondition: Points in a Triangle are in order */
template < class Triangle, class Line >
inline void get_sharing(const Triangle& a, const Triangle& b, Line& l)
{
    l.first = SAW_SENTINAL;
    l.second = SAW_SENTINAL;

    if (a.first == b.first)
    {
        l.first = a.first;
        if (a.second == b.second || a.second == b.third)
            l.second = a.second;
        else if (a.third == b.second || a.third == b.third)
            l.second = a.third;
    }
    else if (a.first == b.second)
    {
        l.first = a.first;
        if (a.second == b.third)
            l.second = a.second;
        else if (a.third == b.third)
            l.second = a.third;
    }
    else if (a.first == b.third)
    {
        l.first = a.first;
    }
    else if (a.second == b.first)
    {
        l.first = a.second;
        if (a.third == b.second || a.third == b.third)
            l.second = a.third;
    }
    else if (a.second == b.second)
    {
        l.first = a.second;
        if (a.third == b.third)
            l.second = a.third;
    }
    else if (a.second == b.third)
    {
        l.first = a.second;
    }
    else if (a.third == b.first || a.third == b.second || a.third == b.third)
        l.first = a.third;

    /*Make it in order*/
    if (l.first > l.second)
    {
        typename Line::first_type i = l.first;
        l.first = l.second;
        l.second = i;
    }
}

template < class TriangleDecorator, class Vertex, class Line >
struct get_vertex_sharing
{
    typedef std::pair< Vertex, Line > Pair;
    get_vertex_sharing(const TriangleDecorator& _td) : td(_td) {}
    inline Line operator()(const Vertex& u, const Vertex& v) const
    {
        Line l;
        get_sharing(td[u], td[v], l);
        return l;
    }
    inline Line operator()(const Pair& u, const Vertex& v) const
    {
        Line l;
        get_sharing(td[u.first], td[v], l);
        return l;
    }
    inline Line operator()(const Pair& u, const Pair& v) const
    {
        Line l;
        get_sharing(td[u.first], td[v.first], l);
        return l;
    }
    TriangleDecorator td;
};

/* HList has to be a handle of data holder so that pass-by-value is
 * in right logic.
 *
 * The element of HList is a pair of vertex and line. (remember a
 * line is a pair of two ints.). That indicates the walk w from
 * current vertex is across line. (If the first of line is -1, it is
 * a point though.
 */
template < class TriangleDecorator, class HList, class IteratorD >
class SAW_visitor : public bfs_visitor<>, public dfs_visitor<>
{
    typedef typename boost::property_traits< IteratorD >::value_type iter;
    /*use boost shared_ptr*/
    typedef typename HList::element_type::value_type::second_type Line;

public:
    typedef tree_edge_tag category;

    inline SAW_visitor(TriangleDecorator _td, HList _hlist, IteratorD ia)
    : td(_td), hlist(_hlist), iter_d(ia)
    {
    }

    template < class Vertex, class Graph >
    inline void start_vertex(Vertex v, Graph&)
    {
        Line l1;
        l1.first = SAW_SENTINAL;
        l1.second = SAW_SENTINAL;
        hlist->push_front(std::make_pair(v, l1));
        iter_d[v] = hlist->begin();
    }

    /*Several symbols:
      w(i): i-th triangle in walk w
      w(i) |- w(i+1): w enter w(i+1) from w(i) over a line
      w(i) ~> w(i+1): w enter w(i+1) from w(i) over a point
      w(i) -> w(i+1): w enter w(i+1) from w(i)
      w(i) ^ w(i+1): the line or point w go over from w(i) to w(i+1)
    */
    template < class Edge, class Graph > bool tree_edge(Edge e, Graph& G)
    {
        using std::make_pair;
        typedef typename boost::graph_traits< Graph >::vertex_descriptor Vertex;
        Vertex tau = target(e, G);
        Vertex i = source(e, G);

        get_vertex_sharing< TriangleDecorator, Vertex, Line > get_sharing_line(
            td);

        Line tau_i = get_sharing_line(tau, i);

        iter w_end = hlist->end();

        iter w_i = iter_d[i];

        iter w_i_m_1 = w_i;
        iter w_i_p_1 = w_i;

        /*----------------------------------------------------------
         *             true             false
         *==========================================================
         *a       w(i-1) |- w(i)    w(i-1) ~> w(i) or w(i-1) is null
         *----------------------------------------------------------
         *b       w(i) |- w(i+1)    w(i) ~> w(i+1) or no w(i+1) yet
         *----------------------------------------------------------
         */

        bool a = false, b = false;

        --w_i_m_1;
        ++w_i_p_1;
        b = (w_i->second.first != SAW_SENTINAL);

        if (w_i_m_1 != w_end)
        {
            a = (w_i_m_1->second.first != SAW_SENTINAL);
        }

        if (a)
        {

            if (b)
            {
                /*Case 1:

                  w(i-1) |- w(i) |- w(i+1)
                */
                Line l1 = get_sharing_line(*w_i_m_1, tau);

                iter w_i_m_2 = w_i_m_1;
                --w_i_m_2;

                bool c = true;

                if (w_i_m_2 != w_end)
                {
                    c = w_i_m_2->second != l1;
                }

                if (c)
                { /* w(i-1) ^ tau != w(i-2) ^ w(i-1)  */
                    /*extension: w(i-1) -> tau |- w(i) */
                    w_i_m_1->second = l1;
                    /*insert(pos, const T&) is to insert before pos*/
                    iter_d[tau] = hlist->insert(w_i, make_pair(tau, tau_i));
                }
                else
                { /* w(i-1) ^ tau == w(i-2) ^ w(i-1)  */
                    /*must be w(i-2) ~> w(i-1) */

                    bool d = true;
                    // need to handle the case when w_i_p_1 is null
                    Line l3 = get_sharing_line(*w_i_p_1, tau);
                    if (w_i_p_1 != w_end)
                        d = w_i_p_1->second != l3;
                    if (d)
                    { /* w(i+1) ^ tau != w(i+1) ^ w(i+2) */
                        /*extension: w(i) |- tau -> w(i+1) */
                        w_i->second = tau_i;
                        iter_d[tau]
                            = hlist->insert(w_i_p_1, make_pair(tau, l3));
                    }
                    else
                    { /* w(i+1) ^ tau == w(i+1) ^ w(i+2) */
                        /*must be w(1+1) ~> w(i+2) */
                        Line l5 = get_sharing_line(*w_i_m_1, *w_i_p_1);
                        if (l5 != w_i_p_1->second)
                        { /* w(i-1) ^ w(i+1) != w(i+1) ^ w(i+2) */
                            /*extension: w(i-2) -> tau |- w(i) |- w(i-1) ->
                             * w(i+1) */
                            w_i_m_2->second = get_sharing_line(*w_i_m_2, tau);
                            iter_d[tau]
                                = hlist->insert(w_i, make_pair(tau, tau_i));
                            w_i->second = w_i_m_1->second;
                            w_i_m_1->second = l5;
                            iter_d[w_i_m_1->first]
                                = hlist->insert(w_i_p_1, *w_i_m_1);
                            hlist->erase(w_i_m_1);
                        }
                        else
                        {
                            /*mesh is tetrahedral*/
                            // dont know what that means.
                            ;
                        }
                    }
                }
            }
            else
            {
                /*Case 2:

                  w(i-1) |- w(i) ~> w(1+1)
                */

                if (w_i->second.second == tau_i.first
                    || w_i->second.second == tau_i.second)
                { /*w(i) ^ w(i+1) < w(i) ^ tau*/
                    /*extension: w(i) |- tau -> w(i+1) */
                    w_i->second = tau_i;
                    Line l1 = get_sharing_line(*w_i_p_1, tau);
                    iter_d[tau] = hlist->insert(w_i_p_1, make_pair(tau, l1));
                }
                else
                { /*w(i) ^ w(i+1) !< w(i) ^ tau*/
                    Line l1 = get_sharing_line(*w_i_m_1, tau);
                    bool c = true;
                    iter w_i_m_2 = w_i_m_1;
                    --w_i_m_2;
                    if (w_i_m_2 != w_end)
                        c = l1 != w_i_m_2->second;
                    if (c)
                    { /*w(i-1) ^ tau != w(i-2) ^ w(i-1)*/
                        /*extension: w(i-1) -> tau |- w(i)*/
                        w_i_m_1->second = l1;
                        iter_d[tau] = hlist->insert(w_i, make_pair(tau, tau_i));
                    }
                    else
                    { /*w(i-1) ^ tau == w(i-2) ^ w(i-1)*/
                        /*must be w(i-2)~>w(i-1)*/
                        /*extension: w(i-2) -> tau |- w(i) |- w(i-1) -> w(i+1)*/
                        w_i_m_2->second = get_sharing_line(*w_i_m_2, tau);
                        iter_d[tau] = hlist->insert(w_i, make_pair(tau, tau_i));
                        w_i->second = w_i_m_1->second;
                        w_i_m_1->second = get_sharing_line(*w_i_m_1, *w_i_p_1);
                        iter_d[w_i_m_1->first]
                            = hlist->insert(w_i_p_1, *w_i_m_1);
                        hlist->erase(w_i_m_1);
                    }
                }
            }
        }
        else
        {

            if (b)
            {
                /*Case 3:

                  w(i-1) ~> w(i) |- w(i+1)
                */
                bool c = false;
                if (w_i_m_1 != w_end)
                    c = (w_i_m_1->second.second == tau_i.first)
                        || (w_i_m_1->second.second == tau_i.second);

                if (c)
                { /*w(i-1) ^ w(i) < w(i) ^ tau*/
                    /* extension: w(i-1) -> tau |- w(i) */
                    if (w_i_m_1 != w_end)
                        w_i_m_1->second = get_sharing_line(*w_i_m_1, tau);
                    iter_d[tau] = hlist->insert(w_i, make_pair(tau, tau_i));
                }
                else
                {
                    bool d = true;
                    Line l1;
                    l1.first = SAW_SENTINAL;
                    l1.second = SAW_SENTINAL;
                    if (w_i_p_1 != w_end)
                    {
                        l1 = get_sharing_line(*w_i_p_1, tau);
                        d = l1 != w_i_p_1->second;
                    }
                    if (d)
                    { /*w(i+1) ^ tau != w(i+1) ^ w(i+2)*/
                        /*extension: w(i) |- tau -> w(i+1) */
                        w_i->second = tau_i;
                        iter_d[tau]
                            = hlist->insert(w_i_p_1, make_pair(tau, l1));
                    }
                    else
                    {
                        /*must be w(i+1) ~> w(i+2)*/
                        /*extension: w(i-1) -> w(i+1) |- w(i) |- tau -> w(i+2)
                         */
                        iter w_i_p_2 = w_i_p_1;
                        ++w_i_p_2;

                        w_i_p_1->second = w_i->second;
                        iter_d[i] = hlist->insert(w_i_p_2, make_pair(i, tau_i));
                        hlist->erase(w_i);
                        Line l2 = get_sharing_line(*w_i_p_2, tau);
                        iter_d[tau]
                            = hlist->insert(w_i_p_2, make_pair(tau, l2));
                    }
                }
            }
            else
            {
                /*Case 4:

                  w(i-1) ~> w(i) ~> w(i+1)

                */
                bool c = false;
                if (w_i_m_1 != w_end)
                {
                    c = (w_i_m_1->second.second == tau_i.first)
                        || (w_i_m_1->second.second == tau_i.second);
                }
                if (c)
                { /*w(i-1) ^ w(i) < w(i) ^ tau */
                    /*extension: w(i-1) -> tau |- w(i) */
                    if (w_i_m_1 != w_end)
                        w_i_m_1->second = get_sharing_line(*w_i_m_1, tau);
                    iter_d[tau] = hlist->insert(w_i, make_pair(tau, tau_i));
                }
                else
                {
                    /*extension: w(i) |- tau -> w(i+1) */
                    w_i->second = tau_i;
                    Line l1;
                    l1.first = SAW_SENTINAL;
                    l1.second = SAW_SENTINAL;
                    if (w_i_p_1 != w_end)
                        l1 = get_sharing_line(*w_i_p_1, tau);
                    iter_d[tau] = hlist->insert(w_i_p_1, make_pair(tau, l1));
                }
            }
        }

        return true;
    }

protected:
    TriangleDecorator td; /*a decorator for vertex*/
    HList hlist;
    /*This must be a handle of list to record the SAW
      The element type of the list is pair<Vertex, Line>
     */

    IteratorD iter_d;
    /*Problem statement: Need a fast access to w for triangle i.
     *Possible solution: mantain an array to record.
     iter_d[i] will return an iterator
     which points to w(i), where i is a vertex
     representing triangle i.
    */
};

template < class Triangle, class HList, class Iterator >
inline SAW_visitor< Triangle, HList, Iterator > visit_SAW(
    Triangle t, HList hl, Iterator i)
{
    return SAW_visitor< Triangle, HList, Iterator >(t, hl, i);
}

template < class Tri, class HList, class Iter >
inline SAW_visitor< random_access_iterator_property_map< Tri*, Tri, Tri& >,
    HList, random_access_iterator_property_map< Iter*, Iter, Iter& > >
visit_SAW_ptr(Tri* t, HList hl, Iter* i)
{
    typedef random_access_iterator_property_map< Tri*, Tri, Tri& > TriD;
    typedef random_access_iterator_property_map< Iter*, Iter, Iter& > IterD;
    return SAW_visitor< TriD, HList, IterD >(t, hl, i);
}

// should also have combo's of pointers, and also const :(

}

#endif /*BOOST_SAW_H*/

/* self_avoiding_walk.hpp
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
*/