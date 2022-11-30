/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_CLOSURE_HPP
#define BOOST_SPIRIT_CLOSURE_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/non_terminal/parser_context.hpp>
#include <boost/spirit/home/classic/attribute/parametric.hpp>
#include <boost/spirit/home/classic/attribute/closure_context.hpp>
#include <boost/spirit/home/classic/attribute/closure_fwd.hpp>

#include <boost/spirit/home/classic/phoenix/closures.hpp>
#include <boost/spirit/home/classic/phoenix/primitives.hpp>
#include <boost/spirit/home/classic/phoenix/casts.hpp>
#include <boost/spirit/home/classic/phoenix/operators.hpp>
#include <boost/spirit/home/classic/phoenix/tuple_helpers.hpp>

#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum closure limit. This limit defines the maximum
//  number of elements a closure can hold. This number defaults to 3. The
//  actual maximum is rounded up in multiples of 3. Thus, if this value
//  is 4, the actual limit is 6. The ultimate maximum limit in this
//  implementation is 15.
//
//  It should NOT be greater than PHOENIX_LIMIT!
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_SPIRIT_CLOSURE_LIMIT)
#define BOOST_SPIRIT_CLOSURE_LIMIT PHOENIX_LIMIT
#endif

///////////////////////////////////////////////////////////////////////////////
//
// ensure BOOST_SPIRIT_CLOSURE_LIMIT <= PHOENIX_LIMIT and SPIRIT_CLOSURE_LIMIT <= 15
//
///////////////////////////////////////////////////////////////////////////////
BOOST_STATIC_ASSERT(BOOST_SPIRIT_CLOSURE_LIMIT <= PHOENIX_LIMIT);
BOOST_STATIC_ASSERT(BOOST_SPIRIT_CLOSURE_LIMIT <= 15);

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  closure_context class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ClosureT>
    class closure_context : public parser_context_base
    {
    public:

        typedef typename ::phoenix::tuple_element<0,
            typename ClosureT::tuple_t>::type attr_t;
        typedef ClosureT base_t;
        typedef closure_context_linker<closure_context<ClosureT> >
        context_linker_t;

        closure_context(ClosureT const& clos)
        : frame(clos) {}

        ~closure_context() {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const&, ScannerT const&) {}

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT& post_parse(ResultT& hit, ParserT const&, ScannerT const&)
        { hit.value(frame[::phoenix::tuple_index_names::_1]); return hit; }

    private:

        ::phoenix::closure_frame<typename ClosureT::phoenix_closure_t> frame;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  init_closure_context class
    //
    //      The init_closure_context class is a special parser context type
    //      which additionally initializes a closure contained in the derived
    //      parser with values from a given tuple. Please note, that this
    //      given tuple does not contain the required values directly, it
    //      contains phoenix::actor objects. These actors have to be
    //      dereferenced to gain the values to be used for initialization
    //      (this is done by the help of the phoenix::convert_actors<>
    //      template).
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename ClosureT>
    class init_closure_context : public parser_context_base
    {
        typedef typename ClosureT::tuple_t      tuple_t;
        typedef typename ClosureT::closure_t    closure_t;

    public:

        init_closure_context(ClosureT const& clos)
        : frame(clos.subject(), ::phoenix::convert_actors<tuple_t>(clos.init)) {}

        ~init_closure_context() {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const& /*p*/, ScannerT const&) {}

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT& post_parse(ResultT& hit, ParserT const&, ScannerT const&)
        { hit.value(frame[::phoenix::tuple_index_names::_1]); return hit; }

    private:

        ::phoenix::closure_frame<closure_t> frame;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  init_closure_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT, typename ActorTupleT>
    struct init_closure_parser
    : public unary<ParserT, parser<init_closure_parser<ParserT, ActorTupleT> > >
    {
        typedef init_closure_parser<ParserT, ActorTupleT>           self_t;
        typedef unary<ParserT, parser<self_t> >                     base_t;
        typedef typename ParserT::phoenix_closure_t                 closure_t;
        typedef typename ParserT::tuple_t                           tuple_t;
        typedef typename ::phoenix::tuple_element<0, tuple_t>::type   attr_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, attr_t>::type type;
        };

        init_closure_parser(ParserT const& p, ActorTupleT const& init_)
        : base_t(p), init(init_) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse_main(ScannerT const& scan) const
        {
            return this->subject().parse_main(scan);
        }

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef init_closure_context<self_t> init_context_t;
            typedef parser_scanner_linker<ScannerT> scanner_t;
            typedef closure_context_linker<init_context_t> context_t;
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            BOOST_SPIRIT_CONTEXT_PARSE(
                scan, *this, scanner_t, context_t, result_t);
        }

        ActorTupleT init;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  closure class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
            typename DerivedT
        ,   typename T0
        ,   typename T1
        ,   typename T2

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 3
        ,   typename T3
        ,   typename T4
        ,   typename T5

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 6
        ,   typename T6
        ,   typename T7
        ,   typename T8

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 9
        ,   typename T9
        ,   typename T10
        ,   typename T11

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 12
        ,   typename T12
        ,   typename T13
        ,   typename T14
    #endif
    #endif
    #endif
    #endif
    >
    struct closure :
        public ::phoenix::closure<
            T0, T1, T2
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 3
        ,   T3, T4, T5
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 6
        ,   T6, T7, T8
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 9
        ,   T9, T10, T11
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 12
        ,   T12, T13, T14
    #endif
    #endif
    #endif
    #endif
        >
    {
        typedef ::phoenix::closure<
                T0, T1, T2
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 3
            ,   T3, T4, T5
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 6
            ,   T6, T7, T8
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 9
            ,   T9, T10, T11
    #if BOOST_SPIRIT_CLOSURE_LIMIT > 12
            ,   T12, T13, T14
    #endif
    #endif
    #endif
    #endif
            > phoenix_closure_t;

        typedef closure_context<DerivedT> context_t;

        template <typename DerivedT2>
        struct aux
        {
            DerivedT2& aux_derived()
            { return *static_cast<DerivedT2*>(this); }

            DerivedT2 const& aux_derived() const
            { return *static_cast<DerivedT2 const*>(this); }

        // initialization functions
            template <typename A>
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type
                >
            >
            operator()(A const &a) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef ::phoenix::tuple<a_t> actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a)
                        )
                    );
            }

            template <typename A, typename B>
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type
                >
            >
            operator()(A const &a, B const &b) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef ::phoenix::tuple<a_t, b_t> actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b)
                        )
                    );
            }

            template <typename A, typename B, typename C>
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type
                >
            >
            operator()(A const &a, B const &b, C const &c) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef ::phoenix::tuple<a_t, b_t, c_t> actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c)
                        )
                    );
            }

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 3

            template <
                typename A, typename B, typename C, typename D
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f)
                        )
                    );
            }

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 6

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i)
                        )
                    );
            }

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 9

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J,
                typename K
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type,
                    typename ::phoenix::as_actor<K>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j,
                K const &k
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef typename ::phoenix::as_actor<K>::type k_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t,
                            k_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j),
                            ::phoenix::as_actor<K>::convert(k)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J,
                typename K, typename L
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type,
                    typename ::phoenix::as_actor<K>::type,
                    typename ::phoenix::as_actor<L>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j,
                K const &k, L const &l
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef typename ::phoenix::as_actor<K>::type k_t;
                typedef typename ::phoenix::as_actor<L>::type l_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t,
                            k_t, l_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j),
                            ::phoenix::as_actor<K>::convert(k),
                            ::phoenix::as_actor<L>::convert(l)
                        )
                    );
            }

    #if BOOST_SPIRIT_CLOSURE_LIMIT > 12

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J,
                typename K, typename L, typename M
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type,
                    typename ::phoenix::as_actor<K>::type,
                    typename ::phoenix::as_actor<L>::type,
                    typename ::phoenix::as_actor<M>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j,
                K const &k, L const &l, M const &m
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef typename ::phoenix::as_actor<K>::type k_t;
                typedef typename ::phoenix::as_actor<L>::type l_t;
                typedef typename ::phoenix::as_actor<M>::type m_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t,
                            k_t, l_t, m_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j),
                            ::phoenix::as_actor<K>::convert(k),
                            ::phoenix::as_actor<L>::convert(l),
                            ::phoenix::as_actor<M>::convert(m)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J,
                typename K, typename L, typename M, typename N
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type,
                    typename ::phoenix::as_actor<K>::type,
                    typename ::phoenix::as_actor<L>::type,
                    typename ::phoenix::as_actor<M>::type,
                    typename ::phoenix::as_actor<N>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j,
                K const &k, L const &l, M const &m, N const &n
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef typename ::phoenix::as_actor<K>::type k_t;
                typedef typename ::phoenix::as_actor<L>::type l_t;
                typedef typename ::phoenix::as_actor<M>::type m_t;
                typedef typename ::phoenix::as_actor<N>::type n_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t,
                            k_t, l_t, m_t, n_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j),
                            ::phoenix::as_actor<K>::convert(k),
                            ::phoenix::as_actor<L>::convert(l),
                            ::phoenix::as_actor<M>::convert(m),
                            ::phoenix::as_actor<N>::convert(n)
                        )
                    );
            }

            template <
                typename A, typename B, typename C, typename D, typename E,
                typename F, typename G, typename H, typename I, typename J,
                typename K, typename L, typename M, typename N, typename O
            >
            init_closure_parser<
                DerivedT2,
                ::phoenix::tuple<
                    typename ::phoenix::as_actor<A>::type,
                    typename ::phoenix::as_actor<B>::type,
                    typename ::phoenix::as_actor<C>::type,
                    typename ::phoenix::as_actor<D>::type,
                    typename ::phoenix::as_actor<E>::type,
                    typename ::phoenix::as_actor<F>::type,
                    typename ::phoenix::as_actor<G>::type,
                    typename ::phoenix::as_actor<H>::type,
                    typename ::phoenix::as_actor<I>::type,
                    typename ::phoenix::as_actor<J>::type,
                    typename ::phoenix::as_actor<K>::type,
                    typename ::phoenix::as_actor<L>::type,
                    typename ::phoenix::as_actor<M>::type,
                    typename ::phoenix::as_actor<N>::type,
                    typename ::phoenix::as_actor<O>::type
                >
            >
            operator()(
                A const &a, B const &b, C const &c, D const &d, E const &e,
                F const &f, G const &g, H const &h, I const &i, J const &j,
                K const &k, L const &l, M const &m, N const &n, O const &o
            ) const
            {
                typedef typename ::phoenix::as_actor<A>::type a_t;
                typedef typename ::phoenix::as_actor<B>::type b_t;
                typedef typename ::phoenix::as_actor<C>::type c_t;
                typedef typename ::phoenix::as_actor<D>::type d_t;
                typedef typename ::phoenix::as_actor<E>::type e_t;
                typedef typename ::phoenix::as_actor<F>::type f_t;
                typedef typename ::phoenix::as_actor<G>::type g_t;
                typedef typename ::phoenix::as_actor<H>::type h_t;
                typedef typename ::phoenix::as_actor<I>::type i_t;
                typedef typename ::phoenix::as_actor<J>::type j_t;
                typedef typename ::phoenix::as_actor<K>::type k_t;
                typedef typename ::phoenix::as_actor<L>::type l_t;
                typedef typename ::phoenix::as_actor<M>::type m_t;
                typedef typename ::phoenix::as_actor<N>::type n_t;
                typedef typename ::phoenix::as_actor<O>::type o_t;
                typedef ::phoenix::tuple<
                            a_t, b_t, c_t, d_t, e_t, f_t, g_t, h_t, i_t, j_t,
                            k_t, l_t, m_t, n_t, o_t
                        > actor_tuple_t;

                return init_closure_parser<DerivedT2, actor_tuple_t>(
                        aux_derived(),
                        actor_tuple_t(
                            ::phoenix::as_actor<A>::convert(a),
                            ::phoenix::as_actor<B>::convert(b),
                            ::phoenix::as_actor<C>::convert(c),
                            ::phoenix::as_actor<D>::convert(d),
                            ::phoenix::as_actor<E>::convert(e),
                            ::phoenix::as_actor<F>::convert(f),
                            ::phoenix::as_actor<G>::convert(g),
                            ::phoenix::as_actor<H>::convert(h),
                            ::phoenix::as_actor<I>::convert(i),
                            ::phoenix::as_actor<J>::convert(j),
                            ::phoenix::as_actor<K>::convert(k),
                            ::phoenix::as_actor<L>::convert(l),
                            ::phoenix::as_actor<M>::convert(m),
                            ::phoenix::as_actor<N>::convert(n),
                            ::phoenix::as_actor<O>::convert(o)
                        )
                    );
            }

    #endif
    #endif
    #endif
    #endif
        };

        ~closure() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  overloads for chseq_p and str_p taking in phoenix actors
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ActorT>
    struct container_begin
    {
        typedef container_begin<ActorT> self_t;

        template <typename TupleT>
        struct result
        {
            typedef typename ::phoenix::actor_result<ActorT, TupleT>
                ::plain_type::iterator type;
        };

        container_begin(ActorT actor_)
        : actor(actor_) {}

        template <typename TupleT>
        typename ::phoenix::actor_result<self_t, TupleT>::type
        eval(TupleT const& /*args*/) const
        { return actor().begin(); }

        ActorT actor;
    };

    template <typename ActorT>
    struct container_end
    {
        typedef container_begin<ActorT> self_t;

        template <typename TupleT>
        struct result
        {
            typedef typename ::phoenix::actor_result<ActorT, TupleT>
                ::plain_type::iterator type;
        };

        container_end(ActorT actor_)
        : actor(actor_) {}

        template <typename TupleT>
        typename ::phoenix::actor_result<self_t, TupleT>::type
        eval(TupleT const& /*args*/) const
        { return actor().end(); }

        ActorT actor;
    };

    template <typename BaseT>
    inline f_chseq<
        ::phoenix::actor<container_begin< ::phoenix::actor<BaseT> > >,
        ::phoenix::actor<container_end< ::phoenix::actor<BaseT> > >
    >
    f_chseq_p(::phoenix::actor<BaseT> const& a)
    {
        typedef ::phoenix::actor<container_begin< ::phoenix::actor<BaseT> > >
            container_begin_t;
        typedef ::phoenix::actor<container_end< ::phoenix::actor<BaseT> > >
            container_end_t;
        typedef f_chseq<container_begin_t, container_end_t> result_t;

        return result_t(container_begin_t(a), container_end_t(a));
    }

    template <typename BaseT>
    inline f_strlit<
        ::phoenix::actor<container_begin< ::phoenix::actor<BaseT> > >,
        ::phoenix::actor<container_end< ::phoenix::actor<BaseT> > >
    >
    f_str_p(::phoenix::actor<BaseT> const& a)
    {
        typedef ::phoenix::actor<container_begin< ::phoenix::actor<BaseT> > >
            container_begin_t;
        typedef ::phoenix::actor<container_end< ::phoenix::actor<BaseT> > >
            container_end_t;
        typedef f_strlit<container_begin_t, container_end_t> result_t;

        return result_t(container_begin_t(a), container_end_t(a));
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* closure.hpp
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
*/