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
x7tR0n5g5zdS2uZt92+s1E99170Zsk/VemOctPcn6v6flKF83RTJT80f0yWevy2bKTqot8vIhCx9jq2rHMgcdU/hHsiqYu385ks8ZRtFkDUMVPf/pB2z1Pmf9K/yEY+JrtR5XTlk1WPtOq+ALKjIjrcGshb1PfT7kMW8qs7/JJ767rxJ9DfSTvsTaYc6B3lW2qvuX9VIndUZzy7R1Zt2ua9IGWoP+ypkFcqf7hNdqTOyg9Jv6izoN1K/l9T5n+jqd3a8Zqmzut95THQw0pa9LzLVjo9Ef0rWLv22w5adlXiqzp9Je79ty76ELFCNVe/LHOcJJfODLL2nnbYbZEFq/XcFZNXP2fF6Q1al/F/gZV9fEw6+DHVWd3CvgcxRc3coZPnKN0VIvDo73g3SDrU/+pbUZaG6/wdZhRqr8ZC1qHtpYyELX2DLbpV429X5n9Rvmbr/J/pT89sdkN2g/NVsKSPETpsNWZ2aL/Okver8dJ6Uq77j3A9Zg1qDFEPWfqMtWyT5qTtej0o8dXb4uLRD7RcqpM/VfnC19K+K95TI1DeRZyQ/Zc8bpT/UenLLZXLX2c7vZ1K/qbb+nhf9XW/nt1PsSo3z3ZClKvv7hehZ6eqXUmd1tnlAdKpkhy6TsaXu/0E2XH17f0v0/IJdbovU+Ru27ITooM3O70OxtX7q/p+kVbo/I/2h9gvnxe432fl9IfHU3tSrK2RqHvTtCv39xq6ff1e0V5Xxja7oI1W/KyGbq2y8v5RxWJ3/QZb/ijr/k3JV/a7tCh0oXxIOWXuyLRsBWVCYLbsJMkftf7/TFSIfdf4nadWZUaKUq9o7AbLVXur+n+hA3RlLhWy/WnPNgCz9Z+r+n9RP+fE5kIWrvX2utNfbLmNu16/vJe+DLOARdf9Pyt2rzv8gq3vYLmOJ1EXdM1oGWYWak5+UMm5W9/8knro/tFby+8Iu92kpV603fih6Vn9jslnSKr+2TdqhynhO7EV9D31R6qL+FqUWsj1qXbdHdKrmntfEDtSe+NeQfaDSNkgf/dSWHZb6parzPyljuzr/k7TD1f0/KXeguv8nelZnSx9LPHU3/k8d7bBl5yCrUv7vouT3ubr/5486K111hiz/XbvcrpC1qPy6Qxag6tILshJlu/0gC1L5BUHWEKPO/6RcdfY1TOq3QZ3/SbnqfDISsoo3bFm0lKt8zrclXoI6/5P81F2XBMiqlb8fL/GUj5gkMrU/ug2y9sG2LA2yU2qsZki8Erttd4peMu0y7haZuo+UL2lX2Dot9HcQ2GU8IO14yi7jYcjqPlP3/yCbf0bd/5M+V77kCUkbZ6ddKeVW2fEqpX5Kz+tFNtlO+wPp8zY73o+lDDUvbIUsWY2F7ZDFqDXcC9If16n7f2KT6hypzh9VVrK9kp8av78S3at7AG9I/dR6o1HKUH7oiKRV89bb0h8Ntq7egyxcfVtslfpF2bJTEu8mdf4nMnWv4FPRaaqd9oKMI3W/zqMb2qG+pXbqhnjt6vyvG9qmzqUCukFXn6n7f5JfiS3rK2lvt2UDIctXeg6GrEWtQYZCFqDuFw+XeM+o+3/doGe1zo7qBj1/S53/QRauzq9GQzZd7XtukXKTbVmSlFus7v+JDjLteFOl3H7q/A+yikp1/idlqD1sluhFrTfugixI2fi9Uhe1Li6ArKqzXZcFovvf2rKHpH4TbNkjkDnKj5dJ/dR+a7mkTVbnf1KGuoPxPbEDZX/run3d/22Q9nqq+3+QtQ9X9//EJtUdyGqps9LVDsii1N7vJemjD9X9P6mzuldVL3UJVud/IlPlvi4yZWu/Fbs6Yeu0Seqnvh8dlbqoct+VvlR3bD6QeGq8tUEWrdY=
*/