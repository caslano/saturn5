/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2002 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_TUPLE_HELPERS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_TUPLE_HELPERS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <boost/spirit/home/classic/phoenix/tuples.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix
{

///////////////////////////////////////////////////////////////////////////////
//
//  make_tuple template class
//
//      This template class is used to calculate a tuple type required to hold
//      the given template parameter type
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  normal (non-tuple types are wrapped into a tuple)
template <typename ResultT>
struct make_tuple {

    typedef tuple<ResultT> type;
};

///////////////////////////////////////////////////////////////////////////////
//  nil_t is converted to an empty tuple type
template <>
struct make_tuple<nil_t> {

    typedef tuple<> type;
};

///////////////////////////////////////////////////////////////////////////////
//  tuple types are left alone without any refactoring
template <
      typename A, typename B, typename C
#if PHOENIX_LIMIT > 3
    , typename D, typename E, typename F
#if PHOENIX_LIMIT > 6
    , typename G, typename H, typename I
#if PHOENIX_LIMIT > 9
    , typename J, typename K, typename L
#if PHOENIX_LIMIT > 12
    , typename M, typename N, typename O
#endif
#endif
#endif
#endif
>
struct make_tuple<tuple<A, B, C
#if PHOENIX_LIMIT > 3
    , D, E, F
#if PHOENIX_LIMIT > 6
    , G, H, I
#if PHOENIX_LIMIT > 9
    , J, K, L
#if PHOENIX_LIMIT > 12
    , M, N, O
#endif
#endif
#endif
#endif
    > > {

// the tuple parameter itself is the required tuple type
    typedef tuple<A, B, C
#if PHOENIX_LIMIT > 3
        , D, E, F
#if PHOENIX_LIMIT > 6
        , G, H, I
#if PHOENIX_LIMIT > 9
        , J, K, L
#if PHOENIX_LIMIT > 12
        , M, N, O
#endif
#endif
#endif
#endif
        > type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat_tuple type computer
//
//      This class returns the type of a tuple, which is constructed by
//      concatenating a tuple with a given type
//
///////////////////////////////////////////////////////////////////////////////
template <typename TupleT, typename AppendT>
struct concat_tuple;

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <0 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename AppendT>
struct concat_tuple<tuple<>, AppendT> {

    typedef tuple<AppendT> type;
};

template <>
struct concat_tuple<tuple<>, nil_t> {

    typedef tuple<> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <1 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename AppendT>
struct concat_tuple<tuple<A>, AppendT> {

    typedef tuple<A, AppendT> type;
};

template <typename A>
struct concat_tuple<tuple<A>, nil_t> {

    typedef tuple<A> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <2 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename B, typename AppendT>
struct concat_tuple<tuple<A, B>, AppendT> {

    typedef tuple<A, B, AppendT> type;
};

template <typename A, typename B>
struct concat_tuple<tuple<A, B>, nil_t> {

    typedef tuple<A, B> type;
};

#if PHOENIX_LIMIT > 3
///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <3 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C>, AppendT> {

    typedef tuple<A, B, C, AppendT> type;
};

template <
    typename A, typename B, typename C
>
struct concat_tuple<tuple<A, B, C>, nil_t> {

    typedef tuple<A, B, C> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <4 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D>, AppendT> {

    typedef tuple<A, B, C, D, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D
>
struct concat_tuple<tuple<A, B, C, D>, nil_t> {

    typedef tuple<A, B, C, D> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <5 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E>, AppendT> {

    typedef tuple<A, B, C, D, E, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E
>
struct concat_tuple<tuple<A, B, C, D, E>, nil_t> {

    typedef tuple<A, B, C, D, E> type;
};

#if PHOENIX_LIMIT > 6
///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <6 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F>, AppendT> {

    typedef tuple<A, B, C, D, E, F, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F
>
struct concat_tuple<tuple<A, B, C, D, E, F>, nil_t> {

    typedef tuple<A, B, C, D, E, F> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <7 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G
>
struct concat_tuple<tuple<A, B, C, D, E, F, G>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <8 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H> type;
};

#if PHOENIX_LIMIT > 9
///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <9 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <10 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <11 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K> type;
};

#if PHOENIX_LIMIT > 12
///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <12 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <13 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L,
    typename M,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L, M>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L,
    typename M
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L, M>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L, M> type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  concat tuple <14 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L,
    typename M, typename N,
    typename AppendT
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N>, AppendT> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N, AppendT> type;
};

template <
    typename A, typename B, typename C, typename D, typename E, typename F,
    typename G, typename H, typename I, typename J, typename K, typename L,
    typename M, typename N
>
struct concat_tuple<tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N>, nil_t> {

    typedef tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N> type;
};

#endif
#endif
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  concat_tuples type computer
//
//      This template class returns the type of a tuple built from the
//      concatenation of two given tuples.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TupleT1, typename TupleT2, int N, typename AppendT>
struct concat_tuple_element {

    typedef
        typename concat_tuple_element<
                typename concat_tuple<TupleT1, AppendT>::type, TupleT2, N+1,
                typename tuple_element<N+1, TupleT2>::type
            >::type
        type;
};

template <typename TupleT1, typename TupleT2, int N>
struct concat_tuple_element<TupleT1, TupleT2, N, nil_t> {

    typedef TupleT1 type;
};

template <typename TupleT1, typename TupleT2>
struct concat_tuples {

    typedef
        typename concat_tuple_element<
                TupleT1, TupleT2, 0,
                typename tuple_element<0, TupleT2>::type
            >::type
        type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  convert_actors template function
//
//      The convert_actors template functions constructs a new tuple object
//      composed of the elements returned by the actors contained in the
//      input tuple. (i.e. the given tuple type 'actor_tuple' contains a set
//      of actors to evaluate and the resulting tuple contains the results of
//      evaluating the actors.)
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActorT, typename TupleT>
struct actor_result; // forward declaration

namespace impl
{
    template <unsigned N>
    struct convert_actors_ {};
}

template <typename TupleResultT, typename ActorTupleT>
TupleResultT
convert_actors(ActorTupleT const& actor_tuple)
{
    BOOST_STATIC_ASSERT(ActorTupleT::length <= TupleResultT::length);
    BOOST_STATIC_CONSTANT(int, length = TupleResultT::length);
    return impl::convert_actors_<length>
        ::template apply<TupleResultT, ActorTupleT>::do_(actor_tuple);
}

namespace impl
{
    template <int N, typename TupleResultT, typename ActorTupleT>
    struct convert_actor
    {
        typedef typename tuple_element<N, TupleResultT>::type type;

        template <bool C>
        struct is_default_t {};
        typedef is_default_t<true>  is_default;
        typedef is_default_t<false> is_not_default;

        static type
        actor_element(ActorTupleT const& /*actor_tuple*/, is_default)
        {
            return type(); // default construct
        }

        static type
        actor_element(ActorTupleT const& actor_tuple, is_not_default)
        {
            BOOST_STATIC_ASSERT(ActorTupleT::length <= TupleResultT::length);
            tuple_index<N> const idx;
            return actor_tuple[idx](); // apply the actor
        }

        static type
        do_(ActorTupleT const& actor_tuple)
        {
            return actor_element(
                actor_tuple, is_default_t<(N >= ActorTupleT::length)>());
        }
    };

    ///////////////////////////////////////
    template <>
    struct convert_actors_<1>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;

                return TupleResultT(
                    converter0::do_(actor_tuple)
                );
            }
        };
    };

    ///////////////////////////////////////
    template <>
    struct convert_actors_<2>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                );
            }
        };
    };

    ///////////////////////////////////////
    template <>
    struct convert_actors_<3>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                );
            }
        };
    };

    #if PHOENIX_LIMIT > 3

    /////////////////////////////////////
    template <>
    struct convert_actors_<4>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<5>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<6>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                );
            }
        };
    };

    #if PHOENIX_LIMIT > 6

    /////////////////////////////////////
    template <>
    struct convert_actors_<7>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<8>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<9>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                );
            }
        };
    };

    #if PHOENIX_LIMIT > 9

    /////////////////////////////////////
    template <>
    struct convert_actors_<10>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<11>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;
                typedef impl::convert_actor<10, TupleResultT, ActorTupleT> converter10;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                    ,   converter10::do_(actor_tuple)
                );
            }
        };
    };

    /////////////////////////////////////
    template <>
    struct convert_actors_<12>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;
                typedef impl::convert_actor<10, TupleResultT, ActorTupleT> converter10;
                typedef impl::convert_actor<11, TupleResultT, ActorTupleT> converter11;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                    ,   converter10::do_(actor_tuple)
                    ,   converter11::do_(actor_tuple)
                );
            }
        };
    };

    #if PHOENIX_LIMIT > 12

    /////////////////////////////////////
    template <>
    struct convert_actors_<13>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;
                typedef impl::convert_actor<10, TupleResultT, ActorTupleT> converter10;
                typedef impl::convert_actor<11, TupleResultT, ActorTupleT> converter11;
                typedef impl::convert_actor<12, TupleResultT, ActorTupleT> converter12;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                    ,   converter10::do_(actor_tuple)
                    ,   converter11::do_(actor_tuple)
                    ,   converter12::do_(actor_tuple)
                );
            }
        };
    };

    ///////////////////////////////////////
    template <>
    struct convert_actors_<14>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;
                typedef impl::convert_actor<10, TupleResultT, ActorTupleT> converter10;
                typedef impl::convert_actor<11, TupleResultT, ActorTupleT> converter11;
                typedef impl::convert_actor<12, TupleResultT, ActorTupleT> converter12;
                typedef impl::convert_actor<13, TupleResultT, ActorTupleT> converter13;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                    ,   converter10::do_(actor_tuple)
                    ,   converter11::do_(actor_tuple)
                    ,   converter12::do_(actor_tuple)
                    ,   converter13::do_(actor_tuple)
                );
            }
        };
    };

    ///////////////////////////////////////
    template <>
    struct convert_actors_<15>
    {
        template <typename TupleResultT, typename ActorTupleT>
        struct apply
        {
            static TupleResultT
            do_(ActorTupleT const& actor_tuple)
            {
                typedef impl::convert_actor<0, TupleResultT, ActorTupleT> converter0;
                typedef impl::convert_actor<1, TupleResultT, ActorTupleT> converter1;
                typedef impl::convert_actor<2, TupleResultT, ActorTupleT> converter2;
                typedef impl::convert_actor<3, TupleResultT, ActorTupleT> converter3;
                typedef impl::convert_actor<4, TupleResultT, ActorTupleT> converter4;
                typedef impl::convert_actor<5, TupleResultT, ActorTupleT> converter5;
                typedef impl::convert_actor<6, TupleResultT, ActorTupleT> converter6;
                typedef impl::convert_actor<7, TupleResultT, ActorTupleT> converter7;
                typedef impl::convert_actor<8, TupleResultT, ActorTupleT> converter8;
                typedef impl::convert_actor<9, TupleResultT, ActorTupleT> converter9;
                typedef impl::convert_actor<10, TupleResultT, ActorTupleT> converter10;
                typedef impl::convert_actor<11, TupleResultT, ActorTupleT> converter11;
                typedef impl::convert_actor<12, TupleResultT, ActorTupleT> converter12;
                typedef impl::convert_actor<13, TupleResultT, ActorTupleT> converter13;
                typedef impl::convert_actor<14, TupleResultT, ActorTupleT> converter14;

                using namespace tuple_index_names;
                return TupleResultT(
                        converter0::do_(actor_tuple)
                    ,   converter1::do_(actor_tuple)
                    ,   converter2::do_(actor_tuple)
                    ,   converter3::do_(actor_tuple)
                    ,   converter4::do_(actor_tuple)
                    ,   converter5::do_(actor_tuple)
                    ,   converter6::do_(actor_tuple)
                    ,   converter7::do_(actor_tuple)
                    ,   converter8::do_(actor_tuple)
                    ,   converter9::do_(actor_tuple)
                    ,   converter10::do_(actor_tuple)
                    ,   converter11::do_(actor_tuple)
                    ,   converter12::do_(actor_tuple)
                    ,   converter13::do_(actor_tuple)
                    ,   converter14::do_(actor_tuple)
                );
            }
        };
    };

    #endif
    #endif
    #endif
    #endif
}   //  namespace impl


///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* tuple_helpers.hpp
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
*/