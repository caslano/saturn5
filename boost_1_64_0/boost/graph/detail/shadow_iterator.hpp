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
32PfE+D+UoD9vQB77enG7neNr6kT/E70F+JImW6u8YSC0O9D6Pm/D2VON+9D4mclYTmYx+r7LtR7etC7EOH4vws9Hf/P5L2kzdz3xI1M4vY750PIZa5qGP6UHd1zAuxzLimcVm75tpdO17QPmOGZ+zKSWmmqo6b1MybXWdO6A9OcN4wsV03TvmV0XjGlwUrQ8rdnFn4ZudaTWAcx48dnj123mtF7SfQ2Wh3Jo0Vo+YQ3AUVTnhvMlnlu2M29IeHEB8WXZ/m0r8y1e1DON82K12vwgNgvtlwi6xe3qg4hUl4+IPDYuMv22nVQcB1o9luV/Im2ErR92VnsA113sap8J97a2omc2VszkbOTwJnUbdOs/oy3G8nY0RzG//ZkJQQna/w2oRV6hu99b85rrJxXAtpbPftPkq4Y5EtJzwLMCJsYSa/wNK7xepkf4v+Msswzym43rZZ0f+KMZfV6dLlOXl3zDdS0U9dLvo1wpLj3HNK200GRdaV0NHF45ysvnq1zqAmPa6Hh6bdTza/DEm8T3jFipeynHsc76j4J17bfNtt+R02cHbyXW4wtM++tO2YF77M2fFbwnJYXZgbPVRkxM3gOSurMwPkmvs+ZcVKORWbetyqKjcw8x+W+CNQzfu3wxKvUcy1n+M/9WDbTvx68Vu3D1R4+y9+9boC90Syj7/8tqYElR1sP2NHKU4ckX2rXIRUTcqn4y6vcy/S0S/XZaM9zLPVdtyFV3OtZ7jb/a9RXRcT3uOynyf8asWGUdyn7J/KeGZXocXhQ2zf3Yd6nfZNlp7k0f9zkUHW96jWw4vW7SpHYNzDW+Vzx8y5hOSx3EDp32/hJ1joGV7Fn8qxpGrKdlGX8PWiNQlfD1jyynyOFonMtZzhfZIOQjRfZzTzHzjXrLuwXWRN9thz/94Ffe7aQHmRyriG/n/iWl76NdC0P0tgYdoV34VJ7jp33fDiQSEz+S79Miua/V3eaFW3mDZaYOc8nzZX3SDOv+XvRHYU9TvZu812D5mZxC/N5JkwybbQYCWeo9/sNh73X9EDx94TJ10zRDZc1FmIpW0VJ3vezxjHhvAq3Dv1eKNe4g4TX3krQ+nG+2N/mnspkHuzJId/TOopeQ+97qcT9tYm7zLNkThSoIQscxIR6P1wi4bTW91Jvno1H0iJk3AtFJ03t6kfXOzix8qTXljqmueQj6z9rndPBtvu3x7UM1fFA6r4ruKilc71lSOqbE/omvr6Jx+FJTBPlY+RlpR1mhTTyrZDvParb3LQBt4l9nTVL3vFou1TV1jf+mppvT3eKfaO1kL/Rps1TbNZxedXtTqh9ZI60b5tfLqt5dr8levnUnj1MW+kBkV0f3PZXf/XhTtFZTWsv9ndr/zcLqBMSgtr/kna57uSb37NnZ4D9BbXvTvLYPw9wrz/P3352gD3D2P3LwI9Nqv6umTfPlAFtIB3fd01vuOc09zhsDaN+Ut7TgHO3wzXrB9jfKhDb3ypUt5643+Upe6UTkF+pdVKluNcMa8nfUZhpmDsxP2A6OegpwFRgbsTsxxzF1HayWggmHTMSU4FZhtmAeRDzN8ynmHAXX4MwnTD9MIWY2ZhrMVswuzGvY77BaJnW9Cbb7VZ5P+0h5WOZuNWR9X22SS5OYc9Qu9yuukzajKyfEuXXZmjiXWNG3Gs7WuDeEdObXPjAamDqoqsX6vcts//kRL/wd88z4YvOS1KRTCtFybTfM91x4H4z5f9UXFvoe9jp3ICt9ftXG9gW007tZyhTYHtMB0w2YZ8JO2I6YTpjuvzOpslvft+PBdSbC+328KKFwfsnl9gy06YdsjB4/+Rutsy0m1vaMtP2rWXLTFv62wWmfW3mX78=
*/