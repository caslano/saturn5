// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SHADOW_ITERATOR_HPP
#define BOOST_SHADOW_ITERATOR_HPP

#include <boost/iterator_adaptors.hpp>
#include <boost/operators.hpp>

namespace boost
{

namespace detail
{

    template < class A, class B, class D >
    class shadow_proxy : boost::operators< shadow_proxy< A, B, D > >
    {
        typedef shadow_proxy self;

    public:
        inline shadow_proxy(A aa, B bb) : a(aa), b(bb) {}
        inline shadow_proxy(const self& x) : a(x.a), b(x.b) {}
        template < class Self > inline shadow_proxy(Self x) : a(x.a), b(x.b) {}
        inline self& operator=(const self& x)
        {
            a = x.a;
            b = x.b;
            return *this;
        }
        inline self& operator++()
        {
            ++a;
            return *this;
        }
        inline self& operator--()
        {
            --a;
            return *this;
        }
        inline self& operator+=(const self& x)
        {
            a += x.a;
            return *this;
        }
        inline self& operator-=(const self& x)
        {
            a -= x.a;
            return *this;
        }
        inline self& operator*=(const self& x)
        {
            a *= x.a;
            return *this;
        }
        inline self& operator/=(const self& x)
        {
            a /= x.a;
            return *this;
        }
        inline self& operator%=(const self& x) { return *this; } // JGS
        inline self& operator&=(const self& x) { return *this; } // JGS
        inline self& operator|=(const self& x) { return *this; } // JGS
        inline self& operator^=(const self& x) { return *this; } // JGS
        inline friend D operator-(const self& x, const self& y)
        {
            return x.a - y.a;
        }
        inline bool operator==(const self& x) const { return a == x.a; }
        inline bool operator<(const self& x) const { return a < x.a; }
        //  protected:
        A a;
        B b;
    };

    struct shadow_iterator_policies
    {
        template < typename iter_pair > void initialize(const iter_pair&) {}

        template < typename Iter >
        typename Iter::reference dereference(const Iter& i) const
        {
            typedef typename Iter::reference R;
            return R(*i.base().first, *i.base().second);
        }
        template < typename Iter >
        bool equal(const Iter& p1, const Iter& p2) const
        {
            return p1.base().first == p2.base().first;
        }
        template < typename Iter > void increment(Iter& i)
        {
            ++i.base().first;
            ++i.base().second;
        }

        template < typename Iter > void decrement(Iter& i)
        {
            --i.base().first;
            --i.base().second;
        }

        template < typename Iter > bool less(const Iter& x, const Iter& y) const
        {
            return x.base().first < y.base().first;
        }
        template < typename Iter >
        typename Iter::difference_type distance(
            const Iter& x, const Iter& y) const
        {
            return y.base().first - x.base().first;
        }
        template < typename D, typename Iter > void advance(Iter& p, D n)
        {
            p.base().first += n;
            p.base().second += n;
        }
    };

} // namespace detail

template < typename IterA, typename IterB > struct shadow_iterator_generator
{

    // To use the iterator_adaptor we can't derive from
    // random_access_iterator because we don't have a real reference.
    // However, we want the STL algorithms to treat the shadow
    // iterator like a random access iterator.
    struct shadow_iterator_tag : public std::input_iterator_tag
    {
        operator std::random_access_iterator_tag()
        {
            return std::random_access_iterator_tag();
        };
    };
    typedef typename std::iterator_traits< IterA >::value_type Aval;
    typedef typename std::iterator_traits< IterB >::value_type Bval;
    typedef typename std::iterator_traits< IterA >::reference Aref;
    typedef typename std::iterator_traits< IterB >::reference Bref;
    typedef typename std::iterator_traits< IterA >::difference_type D;
    typedef detail::shadow_proxy< Aval, Bval, Aval > V;
    typedef detail::shadow_proxy< Aref, Bref, Aval > R;
    typedef iterator_adaptor< std::pair< IterA, IterB >,
        detail::shadow_iterator_policies, V, R, V*, shadow_iterator_tag, D >
        type;
};

// short cut for creating a shadow iterator
template < class IterA, class IterB >
inline typename shadow_iterator_generator< IterA, IterB >::type
make_shadow_iter(IterA a, IterB b)
{
    typedef typename shadow_iterator_generator< IterA, IterB >::type Iter;
    return Iter(std::make_pair(a, b));
}

template < class Cmp > struct shadow_cmp
{
    inline shadow_cmp(const Cmp& c) : cmp(c) {}
    template < class ShadowProxy1, class ShadowProxy2 >
    inline bool operator()(const ShadowProxy1& x, const ShadowProxy2& y) const
    {
        return cmp(x.a, y.a);
    }
    Cmp cmp;
};

} // namespace boost

namespace std
{
template < class A1, class B1, class D1, class A2, class B2, class D2 >
void swap(boost::detail::shadow_proxy< A1&, B1&, D1 > x,
    boost::detail::shadow_proxy< A2&, B2&, D2 > y)
{
    std::swap(x.a, y.a);
    std::swap(x.b, y.b);
}
}

#endif // BOOST_SHADOW_ITERATOR_HPP

/* shadow_iterator.hpp
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
*/