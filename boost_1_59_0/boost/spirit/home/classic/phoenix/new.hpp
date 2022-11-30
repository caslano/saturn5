/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Hartmut Kaiser
    Copyright (c) 2003 Vaclav Vesely

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_NEW_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_NEW_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>
#include <boost/spirit/home/classic/phoenix/composite.hpp>
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  Phoenix predefined maximum new_ limit. This limit defines the maximum
//  number of parameters supported for calles to the set of new_ template
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
//  new_
//
//      Lazy object construction
//
//      The set of new_<> template classes and functions provide a way
//      of lazily constructing certain object from a arbitrary set of
//      actors during parsing.
//      The new_ templates are (syntactically) used very much like
//      the well known C++ casts:
//
//          A *a = new_<A>(...arbitrary list of actors...);
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
struct new_l_0
{
    typedef T* result_type;

    T* operator()() const
    {
        return new T();
    }
};

template <typename T>
struct new_l {

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
    struct result { typedef T* type; };

    T* operator()() const {
        return new T();
    }

    template <typename A>
    T* operator()(A const& a) const {
        return new T(a);
    }

    template <typename A, typename B>
    T* operator()(A const& a, B const& b) const {
        return new T(a, b);
    }

    template <typename A, typename B, typename C>
    T* operator()(A const& a, B const& b, C const& c) const {
        return new T(a, b, c);
    }

#if PHOENIX_CONSTRUCT_LIMIT > 3
    template <
        typename A, typename B, typename C, typename D
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d) const
    {
        return new T(a, b, c, d);
    }

    template <
        typename A, typename B, typename C, typename D, typename E
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e) const
    {
        return new T(a, b, c, d, e);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f) const
    {
        return new T(a, b, c, d, e, f);
    }

#if PHOENIX_CONSTRUCT_LIMIT > 6
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g) const
    {
        return new T(a, b, c, d, e, f, g);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h) const
    {
        return new T(a, b, c, d, e, f, g, h);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i) const
    {
        return new T(a, b, c, d, e, f, g, h, i);
    }

#if PHOENIX_CONSTRUCT_LIMIT > 9
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l);
    }

#if PHOENIX_CONSTRUCT_LIMIT > 12
    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l, m);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l, m, n);
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n, O const& o) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o);
    }

#endif
#endif
#endif
#endif
};

template <typename T>
struct new_1 {

    template <
            typename A
    >
    struct result { typedef T* type; };

    template <typename A>
    T* operator()(A const& a) const {
        return new T(a);
    }

};

template <typename T>
struct new_2 {

    template <
            typename A
        ,   typename B
    >
    struct result { typedef T* type; };

    template <typename A, typename B>
    T* operator()(A const& a, B const& b) const {
        return new T(a, b);
    }

};

template <typename T>
struct new_3 {

    template <
            typename A
        ,   typename B
        ,   typename C
    >
    struct result { typedef T* type; };

    template <typename A, typename B, typename C>
    T* operator()(A const& a, B const& b, C const& c) const {
        return new T(a, b, c);
    }
};

#if PHOENIX_CONSTRUCT_LIMIT > 3
template <typename T>
struct new_4 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
    >
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d) const
    {
        return new T(a, b, c, d);
    }
};


template <typename T>
struct new_5 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
    >
    struct result { typedef T* type; };

    template <
        typename A, typename B, typename C, typename D, typename E
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e) const
    {
        return new T(a, b, c, d, e);
    }
};


template <typename T>
struct new_6 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
    >
    struct result { typedef T* type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f) const
    {
        return new T(a, b, c, d, e, f);
    }
};
#endif


#if PHOENIX_CONSTRUCT_LIMIT > 6
template <typename T>
struct new_7 {

    template <
            typename A
        ,   typename B
        ,   typename C
        ,   typename D
        ,   typename E
        ,   typename F
        ,   typename G
    >
    struct result { typedef T* type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g) const
    {
        return new T(a, b, c, d, e, f, g);
    }
};

template <typename T>
struct new_8 {

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
    struct result { typedef T* type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h) const
    {
        return new T(a, b, c, d, e, f, g, h);
    }
};

template <typename T>
struct new_9 {

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
    struct result { typedef T* type; };

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i) const
    {
        return new T(a, b, c, d, e, f, g, h, i);
    }
};
#endif


#if PHOENIX_CONSTRUCT_LIMIT > 9
template <typename T>
struct new_10 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j);
    }
};

template <typename T>
struct new_11 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k);
    }

};

template <typename T>
struct new_12 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l) const
    {
        return new T(a, b, c, d, f, e, g, h, i, j, k, l);
    }
};
#endif

#if PHOENIX_CONSTRUCT_LIMIT > 12
template <typename T>
struct new_13 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l, m);
    }
};

template <typename T>
struct new_14 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n) const
    {
        return new T(a, b, c, d, e, f, g, h, i, j, k, l, m, n);
    }

};

template <typename T>
struct new_15 {

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
    struct result { typedef T* type; };


    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O
    >
    T* operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n, O const& o) const
    {
        return new T(a, b, c, d, f, e, g, h, i, j, k, l, m, n, o);
    }

};
#endif


#if defined(BOOST_BORLANDC) || (defined(__MWERKS__) && (__MWERKS__ <= 0x3002))

///////////////////////////////////////////////////////////////////////////////
//
//  The following specializations are needed because Borland and CodeWarrior
//  does not accept default template arguments in nested template classes in
//  classes (i.e new_l::result)
//
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename TupleT>
struct composite0_result<new_l_0<T>, TupleT> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A>
struct composite1_result<new_l<T>, TupleT, A> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B>
struct composite2_result<new_l<T>, TupleT, A, B> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C>
struct composite3_result<new_l<T>, TupleT, A, B, C> {

    typedef T* type;
};

#if PHOENIX_LIMIT > 3
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D>
struct composite4_result<new_l<T>, TupleT,
    A, B, C, D> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E>
struct composite5_result<new_l<T>, TupleT,
    A, B, C, D, E> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F>
struct composite6_result<new_l<T>, TupleT,
    A, B, C, D, E, F> {

    typedef T* type;
};

#if PHOENIX_LIMIT > 6
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
struct composite7_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
struct composite8_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
struct composite9_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I> {

    typedef T* type;
};

#if PHOENIX_LIMIT > 9
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
struct composite10_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
struct composite11_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
struct composite12_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L> {

    typedef T* type;
};

#if PHOENIX_LIMIT > 12
//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
struct composite13_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
struct composite14_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N> {

    typedef T* type;
};

//////////////////////////////////
template <typename T, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
struct composite15_result<new_l<T>, TupleT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O> {

    typedef T* type;
};

#endif
#endif
#endif
#endif
#endif

//////////////////////////////////
template <typename T>
inline typename impl::make_composite<new_l_0<T> >::type
new_()
{
    typedef impl::make_composite<new_l_0<T> > make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_l_0<T>()));
}

//////////////////////////////////
template <typename T, typename A>
inline typename impl::make_composite<new_1<T>, A>::type
new_(A const& a)
{
    typedef impl::make_composite<new_1<T>, A> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_1<T>(),
        as_actor<A>::convert(a)
    ));
}

//////////////////////////////////
template <typename T, typename A, typename B>
inline typename impl::make_composite<new_2<T>, A, B>::type
new_(A const& a, B const& b)
{
    typedef impl::make_composite<new_2<T>, A, B> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_2<T>(),
        as_actor<A>::convert(a),
        as_actor<B>::convert(b)
    ));
}

//////////////////////////////////
template <typename T, typename A, typename B, typename C>
inline typename impl::make_composite<new_3<T>, A, B, C>::type
new_(A const& a, B const& b, C const& c)
{
    typedef impl::make_composite<new_3<T>, A, B, C> make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_3<T>(),
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
inline typename impl::make_composite<new_4<T>, A, B, C, D>::type
new_(
    A const& a, B const& b, C const& c, D const& d)
{
    typedef
        impl::make_composite<new_4<T>, A, B, C, D>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_4<T>(),
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
inline typename impl::make_composite<new_5<T>, A, B, C, D, E>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e)
{
    typedef
        impl::make_composite<new_5<T>, A, B, C, D, E>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_5<T>(),
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
inline typename impl::make_composite<new_6<T>, A, B, C, D, E, F>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f)
{
    typedef
        impl::make_composite<new_6<T>, A, B, C, D, E, F>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_6<T>(),
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
inline typename impl::make_composite<new_7<T>, A, B, C, D, E, F, G>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g)
{
    typedef
        impl::make_composite<new_7<T>, A, B, C, D, E, F, G>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_7<T>(),
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
inline typename impl::make_composite<new_8<T>, A, B, C, D, E, F, G, H>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h)
{
    typedef
        impl::make_composite<new_8<T>, A, B, C, D, E, F, G, H>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_8<T>(),
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
inline typename impl::make_composite<new_9<T>, A, B, C, D, E, F, G, H, I>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i)
{
    typedef
        impl::make_composite<new_9<T>, A, B, C, D, E, F, G, H, I>
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_9<T>(),
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
    new_10<T>, A, B, C, D, E, F, G, H, I, J>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j)
{
    typedef
        impl::make_composite<
            new_10<T>, A, B, C, D, E, F, G, H, I, J
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_10<T>(),
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
    new_11<T>, A, B, C, D, E, F, G, H, I, J, K>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k)
{
    typedef
        impl::make_composite<
            new_11<T>, A, B, C, D, E, F, G, H, I, J, K
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_11<T>(),
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
    new_12<T>, A, B, C, D, E, F, G, H, I, J, K, L>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l)
{
    typedef
        impl::make_composite<
            new_12<T>, A, B, C, D, E, F, G, H, I, J, K, L
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_12<T>(),
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
    new_13<T>, A, B, C, D, E, F, G, H, I, J, K, L, M>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m)
{
    typedef
        impl::make_composite<
            new_13<T>, A, B, C, D, E, F, G, H, I, J, K, L, M
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_13<T>(),
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
    new_14<T>, A, B, C, D, E, F, G, H, I, J, K, L, M>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n)
{
    typedef
        impl::make_composite<
            new_14<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, N
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_14<T>(),
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
    new_15<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, O>::type
new_(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n, O const& o)
{
    typedef
        impl::make_composite<
            new_15<T>, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
        >
        make_composite_t;
    typedef typename make_composite_t::type type_t;
    typedef typename make_composite_t::composite_type composite_type_t;

    return type_t(composite_type_t(new_15<T>(),
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

/* new.hpp
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
*/