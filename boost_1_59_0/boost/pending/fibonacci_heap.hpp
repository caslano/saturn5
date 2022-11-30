// (C) Copyright Jeremy Siek    2004.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_FIBONACCI_HEAP_HPP
#define BOOST_FIBONACCI_HEAP_HPP

#if defined(__sgi) && !defined(__GNUC__)
#include <math.h>
#else
#include <boost/config/no_tr1/cmath.hpp>
#endif
#include <iosfwd>
#include <vector>
#include <functional>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>

//
// An adaptation of Knuth's Fibonacci heap implementation
// in "The Stanford Graph Base", pages 475-482.
//

namespace boost
{

template < class T, class Compare = std::less< T >,
    class ID = identity_property_map >
class fibonacci_heap
{
    typedef typename boost::property_traits< ID >::value_type size_type;
    typedef T value_type;

protected:
    typedef fibonacci_heap self;
    typedef std::vector< size_type > LinkVec;
    typedef typename LinkVec::iterator LinkIter;

public:
    fibonacci_heap(
        size_type n, const Compare& cmp, const ID& id = identity_property_map())
    : _key(n)
    , _left(n)
    , _right(n)
    , _p(n)
    , _mark(n)
    , _degree(n)
    , _n(0)
    , _root(n)
    , _id(id)
    , _compare(cmp)
    , _child(n)
    ,
#if defined(BOOST_MSVC) || defined(__ICL) // need a new macro?
        new_roots(size_type(log(float(n))) + 5)
    {
    }
#else
        new_roots(size_type(std::log(float(n))) + 5)
    {
    }
#endif

    // 33
    void push(const T& d)
    {
        ++_n;
        size_type v = get(_id, d);
        _key[v] = d;
        _p[v] = nil();
        _degree[v] = 0;
        _mark[v] = false;
        _child[v] = nil();
        if (_root == nil())
        {
            _root = _left[v] = _right[v] = v;
            // std::cout << "root added" << std::endl;
        }
        else
        {
            size_type u = _left[_root];
            _left[v] = u;
            _right[v] = _root;
            _left[_root] = _right[u] = v;
            if (_compare(d, _key[_root]))
                _root = v;
            // std::cout << "non-root node added" << std::endl;
        }
    }
    T& top() { return _key[_root]; }
    const T& top() const { return _key[_root]; }

    // 38
    void pop()
    {
        --_n;
        int h = -1;
        size_type v, w;
        if (_root != nil())
        {
            if (_degree[_root] == 0)
            {
                v = _right[_root];
            }
            else
            {
                w = _child[_root];
                v = _right[w];
                _right[w] = _right[_root];
                for (w = v; w != _right[_root]; w = _right[w])
                    _p[w] = nil();
            }
            while (v != _root)
            {
                w = _right[v];
                add_tree_to_new_roots(v, new_roots.begin(), h);
                v = w;
            }
            rebuild_root_list(new_roots.begin(), h);
        }
    }
    // 39
    inline void add_tree_to_new_roots(size_type v, LinkIter new_roots, int& h)
    {
        int r;
        size_type u;
        r = _degree[v];
        while (1)
        {
            if (h < r)
            {
                do
                {
                    ++h;
                    new_roots[h] = (h == r ? v : nil());
                } while (h < r);
                break;
            }
            if (new_roots[r] == nil())
            {
                new_roots[r] = v;
                break;
            }
            u = new_roots[r];
            new_roots[r] = nil();
            if (_compare(_key[u], _key[v]))
            {
                _degree[v] = r;
                _mark[v] = false;
                std::swap(u, v);
            }
            make_child(u, v, r);
            ++r;
        }
        _degree[v] = r;
        _mark[v] = false;
    }
    // 40
    void make_child(size_type u, size_type v, size_type r)
    {
        if (r == 0)
        {
            _child[v] = u;
            _left[u] = u;
            _right[u] = u;
        }
        else
        {
            size_type t = _child[v];
            _right[u] = _right[t];
            _left[u] = t;
            _right[t] = u;
            _left[_right[u]] = u;
        }
        _p[u] = v;
    }
    // 41
    inline void rebuild_root_list(LinkIter new_roots, int& h)
    {
        size_type u, v, w;
        if (h < 0)
            _root = nil();
        else
        {
            T d;
            u = v = new_roots[h];
            d = _key[u];
            _root = u;
            for (h--; h >= 0; --h)
                if (new_roots[h] != nil())
                {
                    w = new_roots[h];
                    _left[w] = v;
                    _right[v] = w;
                    if (_compare(_key[w], d))
                    {
                        _root = w;
                        d = _key[w];
                    }
                    v = w;
                }
            _right[v] = u;
            _left[u] = v;
        }
    }

    // 34
    void update(const T& d)
    {
        size_type v = get(_id, d);
        assert(!_compare(_key[v], d));
        _key[v] = d;
        size_type p = _p[v];
        if (p == nil())
        {
            if (_compare(d, _key[_root]))
                _root = v;
        }
        else if (_compare(d, _key[p]))
            while (1)
            {
                size_type r = _degree[p];
                if (r >= 2)
                    remove_from_family(v, p);
                insert_into_forest(v, d);
                size_type pp = _p[p];
                if (pp == nil())
                {
                    --_degree[p];
                    break;
                }
                if (_mark[p] == false)
                {
                    _mark[p] = true;
                    --_degree[p];
                    break;
                }
                else
                    --_degree[p];
                v = p;
                p = pp;
            }
    }

    inline size_type size() const { return _n; }
    inline bool empty() const { return _n == 0; }

    void print(std::ostream& os)
    {
        if (_root != nil())
        {
            size_type i = _root;
            do
            {
                print_recur(i, os);
                os << std::endl;
                i = _right[i];
            } while (i != _root);
        }
    }

protected:
    // 35
    inline void remove_from_family(size_type v, size_type p)
    {
        size_type u = _left[v];
        size_type w = _right[v];
        _right[u] = w;
        _left[w] = u;
        if (_child[p] == v)
            _child[p] = w;
    }
    // 36
    inline void insert_into_forest(size_type v, const T& d)
    {
        _p[v] = nil();
        size_type u = _left[_root];
        _left[v] = u;
        _right[v] = _root;
        _left[_root] = _right[u] = v;
        if (_compare(d, _key[_root]))
            _root = v;
    }

    void print_recur(size_type x, std::ostream& os)
    {
        if (x != nil())
        {
            os << x;
            if (_degree[x] > 0)
            {
                os << "(";
                size_type i = _child[x];
                do
                {
                    print_recur(i, os);
                    os << " ";
                    i = _right[i];
                } while (i != _child[x]);
                os << ")";
            }
        }
    }

    size_type nil() const { return _left.size(); }

    std::vector< T > _key;
    LinkVec _left, _right, _p;
    std::vector< bool > _mark;
    LinkVec _degree;
    size_type _n, _root;
    ID _id;
    Compare _compare;
    LinkVec _child;
    LinkVec new_roots;
};

} // namespace boost

#endif // BOOST_FIBONACCI_HEAP_HPP

/* fibonacci_heap.hpp
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
*/