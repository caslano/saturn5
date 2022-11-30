/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Hartmut Kaiser

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_CASTS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_CASTS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>
#include <boost/spirit/home/classic/phoenix/composite.hpp>
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  Phoenix predefined maximum construct_ limit. This limit defines the maximum
//  number of parameters supported for calles to the set of construct_ template
//  functions (lazy object construction, see below). This number defaults to 3.
//  The actual maximum is rounded up in multiples of 3. Thus, if this value
//  is 4, the actual limit is 6. The ultimate maximum limit in this
//  implementation is 15.
//  PHOENIX_CONSTRUCT_LIMIT should NOT be greater than PHOENIX_LIMIT!

#if !defined(PHOENIX_CONSTRUCT_LIMIT)
#define PHOENIX_CONSTRUCT_LIMIT PHOENIX_LIMIT
#endif

// ensure PHOENIX_CONSTRUCT_LIMIT <= PHOENIX_LIMIT
BOOST_STATIC_ASSERT(PHOENIX_CONSTRUCT_LIMIT <= PHOENIX_LIMIT);

// ensure PHOENIX_CONSTRUCT_LIMIT <= 15
BOOST_STATIC_ASSERT(PHOENIX_CONSTRUCT_LIMIT <= 15);

///////////////////////////////////////////////////////////////////////////////
//
//  Lazy C++ casts
//
//      The set of lazy C++ cast template classes and functions provide a way
//      of lazily casting certain type to another during parsing.
//      The lazy C++ templates are (syntactically) used very much like
//      the well known C++ casts:
//
//          A *a = static_cast_<A *>(...actor returning a convertible type...);
//
//      where the given parameter should be an actor, which eval() function
//      returns a convertible type.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename A>
struct static_cast_l {

    template <typename TupleT>
    struct result { typedef T type; };

    static_cast_l(A const& a_)
    :   a(a_) {}

    template <typename TupleT>
    T
    eval(TupleT const& args) const
    {
        return static_cast<T>(a.eval(args));
    }

    A a;
};

//////////////////////////////////
template <typename T, typename BaseAT>
inline actor<static_cast_l<T, BaseAT> >
static_cast_(actor<BaseAT> const& a)
{
    typedef static_cast_l<T, BaseAT> cast_t;
    return actor<cast_t>(cast_t(a));
}

//////////////////////////////////
template <typename T, typename A>
struct dynamic_cast_l {

    template <typename TupleT>
    struct result { typedef T type; };

    dynamic_cast_l(A const& a_)
    :   a(a_) {}

    template <typename TupleT>
    T
    eval(TupleT const& args) const
    {
        return dynamic_cast<T>(a.eval(args));
    }

    A a;
};

//////////////////////////////////
template <typename T, typename BaseAT>
inline actor<dynamic_cast_l<T, BaseAT> >
dynamic_cast_(actor<BaseAT> const& a)
{
    typedef dynamic_cast_l<T, BaseAT> cast_t;
    return actor<cast_t>(cast_t(a));
}

//////////////////////////////////
template <typename T, typename A>
struct reinterpret_cast_l {

    template <typename TupleT>
    struct result { typedef T type; };

    reinterpret_cast_l(A const& a_)
    :   a(a_) {}

    template <typename TupleT>
    T
    eval(TupleT const& args) const
    {
        return reinterpret_cast<T>(a.eval(args));
    }

    A a;
};

//////////////////////////////////
template <typename T, typename BaseAT>
inline actor<reinterpret_cast_l<T, BaseAT> >
reinterpret_cast_(actor<BaseAT> const& a)
{
    typedef reinterpret_cast_l<T, BaseAT> cast_t;
    return actor<cast_t>(cast_t(a));
}

//////////////////////////////////
template <typename T, typename A>
struct const_cast_l {

    template <typename TupleT>
    struct result { typedef T type; };

    const_cast_l(A const& a_)
    :   a(a_) {}

    template <typename TupleT>
    T
    eval(TupleT const& args) const
    {
        return const_cast<T>(a.eval(args));
    }

    A a;
};

//////////////////////////////////
template <typename T, typename BaseAT>
inline actor<const_cast_l<T, BaseAT> >
const_cast_(actor<BaseAT> const& a)
{
    typedef const_cast_l<T, BaseAT> cast_t;
    return actor<cast_t>(cast_t(a));
}

///////////////////////////////////////////////////////////////////////////////
//
//  construct_
//
//      Lazy object construction
//
//      The set of construct_<> template classes and functions provide a way
//      of lazily constructing certain object from a arbitrary set of
//      actors during parsing.
//      The construct_ templates are (syntactically) used very much like
//      the well known C++ casts:
//
//          A a = construct_<A>(...arbitrary list of actors...);
//
//      where the given parameters are submitted as parameters to the
//      constructor of the object of type A. (This certainly implies, that
//      type A has a constructor with a fitting set of parameter types
//      defined.)
//
//      The maximum number of needed parameters is controlled through the
//      preprocessor constant PHOENIX_CONSTRUCT_LIMIT. Note though, that this
//      limit should not be greater than PHOENIX_LIMIT.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct construct_l_0 {
    typedef T result_type;

    T operator()() const {
        return T();
    }
};


template <typename T>
struct construct_l {

    template <
            typename A
        ,   typename B
        ,   typename C

#if PHOENIX_CONSTRUCT_LIMIT > 3
        ,   typename D
        ,   typename E
        ,   typename F

#if PHOENIX_CONSTRUCT_LIMIT > 6
        ,   typename G
        ,   typename H
        ,   typename I

#if PHOENIX_CONSTRUCT_LIMIT > 9
        ,   typename J
        ,   typename K
        ,   typename L

#if PHOENIX_CONSTRUCT_LIMIT > 12
        ,   typename M
        ,   typename N
        ,   typename O
#endif
#endif
#endif
#endif
    >
    struct result { typedef T type; };

    T operator()() const 
    {
        return T();
    }

    template <typename A>
    T operator()(A const& a) const 
    {
        T t(a); 
        return t;
    }

    template <typename A, typename B>
    T operator()(A const& a, B const& b) const 
    {
        T t(a, b);
        return t;
    }

    template <typename A, typename B, typename C>
    T operator()(A const& a, B const& b, C const& c) const 
    {
        T t(a, b, c);
        return t;
    }

#if PHOENIX_CONSTRUCT_LIMIT > 3
    template <
        typename A, typename B, typename C, typename D
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d) const
    {
        T t(a, b, c, d);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e) const
    {
        T t(a, b, c, d, e);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f) const
    {
        T t(a, b, c, d, e, f);
        return t;
    }

#if PHOENIX_CONSTRUCT_LIMIT > 6
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g) const
    {
        T t(a, b, c, d, e, f, g);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h) const
    {
        T t(a, b, c, d, e, f, g, h);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i) const
    {
        T t(a, b, c, d, e, f, g, h, i);
        return t;
    }

#if PHOENIX_CONSTRUCT_LIMIT > 9
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j) const
    {
        T t(a, b, c, d, e, f, g, h, i, j);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l);
        return t;
    }

#if PHOENIX_CONSTRUCT_LIMIT > 12
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l, m);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l, m, n);
        return t;
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n, O const& o) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o);
        return t;
    }

#endif
#endif
#endif
#endif
};


template <typename T>
struct construct_1 {

    template <
            typename A
    >
    struct result { typedef T type; };

    template <typename A>
    T operator()(A const& a) const 
    {
        T t(a);
        return t;
    }

};

template <typename T>
struct construct_2 {

    template <
            typename A
        ,   typename B
    >
    struct result { typedef T type; };

    template <typename A, typename B>
    T operator()(A const& a, B const& b) const 
    {
        T t(a, b);
        return t;
    }

};

template <typename T>
struct construct_3 {

    template <
            typename A
        ,   typename B
        ,   typename C
    >
    struct result { typedef T type; };

    template <typename A, typename B, typename C>
    T operator()(A const& a, B const& b, C const& c) const 
    {
        T t(a, b, c);
        return t;
    }
};

#if PHOENIX_CONSTRUCT_LIMIT > 3
template <typename T>
struct construct_4 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d) const
    {
        T t(a, b, c, d);
        return t;
    }
};


template <typename T>
struct construct_5 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e) const
    {
        T t(a, b, c, d, e);
        return t;
    }
};


template <typename T>
struct construct_6 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f) const
    {
        T t(a, b, c, d, e, f);
        return t;
    }
};
#endif


#if PHOENIX_CONSTRUCT_LIMIT > 6
template <typename T>
struct construct_7 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g) const
    {
        T t(a, b, c, d, e, f, g);
        return t;
    }
};

template <typename T>
struct construct_8 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h) const
    {
        T t(a, b, c, d, e, f, g, h);
        return t;
    }
};

template <typename T>
struct construct_9 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i) const
    {
        T t(a, b, c, d, e, f, g, h, i);
        return t;
    }
};
#endif


#if PHOENIX_CONSTRUCT_LIMIT > 9
template <typename T>
struct construct_10 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j) const
    {
        T t(a, b, c, d, e, f, g, h, i, j);
        return t;
    }
};

template <typename T>
struct construct_11 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
        ,   typename K
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k);
        return t;
    }
};

template <typename T>
struct construct_12 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
        ,   typename K
        ,   typename L
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l) const
    {
        T t(a, b, c, d, f, e, g, h, i, j, k, l);
        return t;
    }
};
#endif

#if PHOENIX_CONSTRUCT_LIMIT > 12
template <typename T>
struct construct_13 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
        ,   typename K
        ,   typename L
        ,   typename M
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l, m);
        return t;
    }
};

template <typename T>
struct construct_14 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
        ,   typename K
        ,   typename L
        ,   typename M
        ,   typename N
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n) const
    {
        T t(a, b, c, d, e, f, g, h, i, j, k, l, m, n);
        return t;
    }
};

template <typename T>
struct construct_15 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
        ,   typename H
        ,   typename I
        ,   typename J
        ,   typename K
        ,   typename L
        ,   typename M
        ,   typename N
        ,   typename O
    >
    struct result { typedef T type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O
    >
    T operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n, O const& o) const
    {
        T t(a, b, c, d, f, e, g, h, i, j, k, l, m, n, o);
        return t;
    }
};
#endif


#if defined(BOOST_BORLANDC) || (defined(__MWERKS__) && (__MWERKS__ <= 0x3002))

///////////////////////////////////////////////////////////////////////////////
//
//  The following specializations are needed because Borland and CodeWarrior
//  does not accept default template arguments in nested template classes in
//  classes (i.e construct_l::result)
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename TupleT>
struct composite0_result<construct_l_0<T>, TupleT> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A>
struct composite1_result<construct_l<T>, TupleT, A> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B>
struct composite2_result<construct_l<T>, TupleT, A, B> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C>
struct composite3_result<construct_l<T>, TupleT, A, B, C> {

    typedef T type;
};

#if PHOENIX_LIMIT > 3
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D>
struct composite4_result<construct_l<T>, TupleT,
    A, B, C, D> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E>
struct composite5_result<construct_l<T>, TupleT,
    A, B, C, D, E> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F>
struct composite6_result<construct_l<T>, TupleT,
    A, B, C, D, E, F> {

    typedef T type;
};

#if PHOENIX_LIMIT > 6
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
struct composite7_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
struct composite8_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
struct composite9_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I> {

    typedef T type;
};

#if PHOENIX_LIMIT > 9
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
struct composite10_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
struct composite11_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
struct composite12_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L> {

    typedef T type;
};

#if PHOENIX_LIMIT > 12
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
struct composite13_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
struct composite14_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N> {

    typedef T type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
struct composite15_result<construct_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O> {

    typedef T type;
};

#endif
#endif
#endif
#endif
#endif

//////////////////////////////////
template <typename T>
inline typename impl::make_composite<construct_l_0<T> >::type
construct_()
{
    typedef impl::make_composite<construct_l_0<T> > make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;
    
    return type_t(composite_type_t(construct_l_0<T>()));
}

//////////////////////////////////
template <typename T, typename A>
inline typename impl::make_composite<construct_1<T>, A>::type
construct_(A const& a)
{
    typedef impl::make_composite<construct_1<T>, A> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_1<T>(), 
        as_actor<A>::convert(a)
    ));
}

//////////////////////////////////
template <typename T, typename A, typename B>
inline typename impl::make_composite<construct_2<T>, A, B>::type
construct_(A const& a, B const& b)
{
    typedef impl::make_composite<construct_2<T>, A, B> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_2<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b)
    ));
}

//////////////////////////////////
template <typename T, typename A, typename B, typename C>
inline typename impl::make_composite<construct_3<T>, A, B, C>::type
construct_(A const& a, B const& b, C const& c)
{
    typedef impl::make_composite<construct_3<T>, A, B, C> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_3<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c)
    ));
}

#if PHOENIX_CONSTRUCT_LIMIT > 3
//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D
>
inline typename impl::make_composite<construct_4<T>, A, B, C, D>::type
construct_(
    A const& a, B const& b, C const& c, D const& d)
{
    typedef
        impl::make_composite<construct_4<T>, A, B, C, D>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_4<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E
>
inline typename impl::make_composite<construct_5<T>, A, B, C, D, E>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e)
{
    typedef
        impl::make_composite<construct_5<T>, A, B, C, D, E>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_5<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F
>
inline typename impl::make_composite<construct_6<T>, A, B, C, D, E, F>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f)
{
    typedef
        impl::make_composite<construct_6<T>, A, B, C, D, E, F>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_6<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f)
    ));
}

#if PHOENIX_CONSTRUCT_LIMIT > 6
//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G
>
inline typename impl::make_composite<construct_7<T>, A, B, C, D, E, F, G>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g)
{
    typedef
        impl::make_composite<construct_7<T>, A, B, C, D, E, F, G>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_7<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H
>
inline typename impl::make_composite<construct_8<T>, A, B, C, D, E, F, G, H>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h)
{
    typedef
        impl::make_composite<construct_8<T>, A, B, C, D, E, F, G, H>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_8<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I
>
inline typename impl::make_composite<construct_9<T>, A, B, C, D, E, F, G, H, I>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i)
{
    typedef
        impl::make_composite<construct_9<T>, A, B, C, D, E, F, G, H, I>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_9<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i)
    ));
}

#if PHOENIX_CONSTRUCT_LIMIT > 9
//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J
>
inline typename impl::make_composite<
    construct_10<T>, A, B, C, D, E, F, G, H, I, J>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j)
{
    typedef
        impl::make_composite<
            construct_10<T>, A, B, C, D, E, F, G, H, I, J
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_10<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J, typename K
>
inline typename impl::make_composite<
    construct_11<T>, A, B, C, D, E, F, G, H, I, J, K>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k)
{
    typedef
        impl::make_composite<
            construct_11<T>, A, B, C, D, E, F, G, H, I, J, K
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_11<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j),
        as_actor<K>::convert(k)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J, typename K,
    typename L
>
inline typename impl::make_composite<
    construct_12<T>, A, B, C, D, E, F, G, H, I, J, K, L>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l)
{
    typedef
        impl::make_composite<
            construct_12<T>, A, B, C, D, E, F, G, H, I, J, K, L
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_12<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j),
        as_actor<K>::convert(k),
        as_actor<L>::convert(l)
    ));
}

#if PHOENIX_CONSTRUCT_LIMIT > 12
//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J, typename K,
    typename L, typename M
>
inline typename impl::make_composite<
    construct_13<T>, A, B, C, D, E, F, G, H, I, J, K, L, M>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m)
{
    typedef
        impl::make_composite<
            construct_13<T>, A, B, C, D, E, F, G, H, I, J, K, L, M
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_13<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j),
        as_actor<K>::convert(k),
        as_actor<L>::convert(l),
        as_actor<M>::convert(m)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J, typename K,
    typename L, typename M, typename N
>
inline typename impl::make_composite<
    construct_14<T>, A, B, C, D, E, F, G, H, I, J, K, L, M>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n)
{
    typedef
        impl::make_composite<
            construct_14<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, N
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_14<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j),
        as_actor<K>::convert(k),
        as_actor<L>::convert(l),
        as_actor<M>::convert(m),
        as_actor<N>::convert(n)
    ));
}

//////////////////////////////////
template <
    typename T, typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J, typename K,
    typename L, typename M, typename N, typename O
>
inline typename impl::make_composite<
    construct_15<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, O>::type
construct_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n, O const& o)
{
    typedef
        impl::make_composite<
            construct_15<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(construct_15<T>(), 
        as_actor<A>::convert(a), 
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i),
        as_actor<J>::convert(j),
        as_actor<K>::convert(k),
        as_actor<L>::convert(l),
        as_actor<M>::convert(m),
        as_actor<N>::convert(n),
        as_actor<O>::convert(o)
    ));
}

#endif
#endif
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* casts.hpp
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
*/