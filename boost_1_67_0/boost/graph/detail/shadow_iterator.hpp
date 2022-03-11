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