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