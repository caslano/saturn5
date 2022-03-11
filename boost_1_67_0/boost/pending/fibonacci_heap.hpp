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