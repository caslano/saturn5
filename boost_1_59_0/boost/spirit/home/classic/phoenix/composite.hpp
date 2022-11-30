/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_COMPOSITE_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_COMPOSITE_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  composite class
//
//      A composite is an actor base class composed of zero or more
//      actors (see actor.hpp) and an operation. A composite is itself
//      an actor superclass and conforms to its conceptual interface.
//      Its eval member function un-funnels the tupled actual arguments
//      from the tuple by invoking each of the actors' eval member
//      function. The results of each are then passed on as arguments to
//      the operation. Specializations are provided to handle different
//      numbers of actors.
//
//      Schematically:
//
//          actor0.eval(tupled_args) --> arg0 --> |
//          actor1.eval(tupled_args) --> arg1 --> |
//          actor2.eval(tupled_args) --> arg3 --> | --> operation(arg0...argN)
//            ...                                 |
//          actorN.eval(tupled_args) --> argN --> |
//
//      The operation can be any suitable functor that can accept the
//      arguments passed in by the composite. The operation is expected
//      to have a member operator() that carries out the actual
//      operation. There should be a one to one correspondence between
//      actors of the composite and the arguments of the operation's
//      member operator().
//
//      The operation is also expected to have a nested template class
//      result<T0...TN>. The nested template class result should have a
//      typedef 'type' that reflects the return type of its member
//      operator(). This is essentially a type computer that answers the
//      metaprogramming question "Given arguments of type T0...TN, what
//      will be its operator()'s return type?".
//
//      There is a special case for operations that accept no arguments.
//      Such nullary operations are only required to define a typedef
//      result_type that reflects the return type of its operator().
//
//      Here's an example of a simple operation that squares a number:
//
//          struct square {
//
//              template <typename ArgT>
//              struct result { typedef ArgT type; };
//
//              template <typename ArgT>
//              ArgT operator()(ArgT n) const { return n * n; }
//          };
//
//      As can be seen, operations can be polymorphic. Its arguments and
//      return type are not fixed to a particular type. The example
//      above for example, can handle any ArgT type as long as it has a
//      multiplication operator.
//
//      Composites are not created directly. Instead, there are meta-
//      programs provided that indirectly create composites. See
//      operators.hpp, binders.hpp and functions.hpp for examples.
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename OperationT
    ,   typename A = nil_t
    ,   typename B = nil_t
    ,   typename C = nil_t

#if PHOENIX_LIMIT > 3
    ,   typename D = nil_t
    ,   typename E = nil_t
    ,   typename F = nil_t

#if PHOENIX_LIMIT > 6
    ,   typename G = nil_t
    ,   typename H = nil_t
    ,   typename I = nil_t

#if PHOENIX_LIMIT > 9
    ,   typename J = nil_t
    ,   typename K = nil_t
    ,   typename L = nil_t

#if PHOENIX_LIMIT > 12
    ,   typename M = nil_t
    ,   typename N = nil_t
    ,   typename O = nil_t

#endif
#endif
#endif
#endif

    ,   typename NU = nil_t  // Not used
>
struct composite;

///////////////////////////////////////////////////////////////////////////////
//
//  composite <0 actor> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT>
struct composite0_result {

    typedef typename OperationT::result_type type;
};

//////////////////////////////////
template <typename OperationT>
struct composite<OperationT,
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 3
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite0_result<
            OperationT, TupleT
        >::type type;
    };

    composite(OperationT const& op_)
    :   op(op_) {}

    template <typename TupleT>
    typename OperationT::result_type
    eval(TupleT const& /*args*/) const
    {
        return op();
    }

    mutable OperationT op; //  operation
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <1 actor> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A>
struct composite1_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A>
struct composite<OperationT,
    A, nil_t, nil_t,
#if PHOENIX_LIMIT > 3
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite1_result<
            OperationT, TupleT, A
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_)
    :   op(op_), a(a_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        return op(ra);
    }

    mutable OperationT op; //  operation
    A a; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <2 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B>
struct composite2_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B>
struct composite<OperationT,
    A, B, nil_t,
#if PHOENIX_LIMIT > 3
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite2_result<
            OperationT, TupleT, A, B
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_)
    :   op(op_), a(a_), b(b_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        return op(ra, rb);
    }

    mutable OperationT op; //  operation
    A a; B b; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <3 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C>
struct composite3_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C>
struct composite<OperationT,
    A, B, C,
#if PHOENIX_LIMIT > 3
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite3_result<
            OperationT, TupleT, A, B, C
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_)
    :   op(op_), a(a_), b(b_), c(c_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        return op(ra, rb, rc);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; //  actors
};

#if PHOENIX_LIMIT > 3
///////////////////////////////////////////////////////////////////////////////
//
//  composite <4 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D>
struct composite4_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D>
struct composite<OperationT,
    A, B, C, D, nil_t, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite4_result<
            OperationT, TupleT, A, B, C, D
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        return op(ra, rb, rc, rd);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <5 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E>
struct composite5_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E>
struct composite<OperationT,
    A, B, C, D, E, nil_t,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite5_result<
            OperationT, TupleT, A, B, C, D, E
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        return op(ra, rb, rc, rd, re);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <6 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F>
struct composite6_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F>
struct composite<OperationT,
    A, B, C, D, E, F,
#if PHOENIX_LIMIT > 6
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E, F> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite6_result<
            OperationT, TupleT, A, B, C, D, E, F
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        return op(ra, rb, rc, rd, re, rf);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; //  actors
};

#if PHOENIX_LIMIT > 6
///////////////////////////////////////////////////////////////////////////////
//
//  composite <7 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
struct composite7_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
struct composite<OperationT,
    A, B, C, D, E, F, G, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E, F, G> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite7_result<
            OperationT, TupleT, A, B, C, D, E, F, G
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <8 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
struct composite8_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E, F, G, H> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite8_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <9 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
struct composite9_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E, F, G, H, I> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite9_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; //  actors
};

#if PHOENIX_LIMIT > 9
///////////////////////////////////////////////////////////////////////////////
//
//  composite <10 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
struct composite10_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT, A, B, C, D, E, F, G, H, I, J> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite10_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <11 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
struct composite11_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type,
        typename actor_result<K, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, K, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT,
        A, B, C, D, E, F, G, H, I, J, K> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite11_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J, K
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_,
        K const& k_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        typename actor_result<K, TupleT>::type rk = k.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j;
    K k;//  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <12 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
struct composite12_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type,
        typename actor_result<K, TupleT>::plain_type,
        typename actor_result<L, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, K, L,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
> {

    typedef composite<OperationT,
        A, B, C, D, E, F, G, H, I, J, K, L> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite12_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J, K, L
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_,
        K const& k_, L const& l_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        typename actor_result<K, TupleT>::type rk = k.eval(args);
        typename actor_result<L, TupleT>::type rl = l.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j;
    K k; L l;//  actors
};

#if PHOENIX_LIMIT > 12
///////////////////////////////////////////////////////////////////////////////
//
//  composite <13 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
struct composite13_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type,
        typename actor_result<K, TupleT>::plain_type,
        typename actor_result<L, TupleT>::plain_type,
        typename actor_result<M, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, nil_t, nil_t, nil_t
> {

    typedef composite<OperationT,
        A, B, C, D, E, F, G, H, I, J, K, L, M> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite13_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J, K, L, M
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_,
        K const& k_, L const& l_, M const& m_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        typename actor_result<K, TupleT>::type rk = k.eval(args);
        typename actor_result<L, TupleT>::type rl = l.eval(args);
        typename actor_result<M, TupleT>::type rm = m.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl, rm);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j;
    K k; L l; M m; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <14 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
struct composite14_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type,
        typename actor_result<K, TupleT>::plain_type,
        typename actor_result<L, TupleT>::plain_type,
        typename actor_result<M, TupleT>::plain_type,
        typename actor_result<N, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, nil_t, nil_t
> {

    typedef composite<OperationT,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite14_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J, K, L, M, N
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_,
        K const& k_, L const& l_, M const& m_, N const& n_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_), n(n_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        typename actor_result<K, TupleT>::type rk = k.eval(args);
        typename actor_result<L, TupleT>::type rl = l.eval(args);
        typename actor_result<M, TupleT>::type rm = m.eval(args);
        typename actor_result<N, TupleT>::type rn = n.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl, rm, rn);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j;
    K k; L l; M m; N n; //  actors
};

///////////////////////////////////////////////////////////////////////////////
//
//  composite <15 actors> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT, typename TupleT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
struct composite15_result {

    typedef typename OperationT::template result<
        typename actor_result<A, TupleT>::plain_type,
        typename actor_result<B, TupleT>::plain_type,
        typename actor_result<C, TupleT>::plain_type,
        typename actor_result<D, TupleT>::plain_type,
        typename actor_result<E, TupleT>::plain_type,
        typename actor_result<F, TupleT>::plain_type,
        typename actor_result<G, TupleT>::plain_type,
        typename actor_result<H, TupleT>::plain_type,
        typename actor_result<I, TupleT>::plain_type,
        typename actor_result<J, TupleT>::plain_type,
        typename actor_result<K, TupleT>::plain_type,
        typename actor_result<L, TupleT>::plain_type,
        typename actor_result<M, TupleT>::plain_type,
        typename actor_result<N, TupleT>::plain_type,
        typename actor_result<O, TupleT>::plain_type
    >::type type;
};

//////////////////////////////////
template <typename OperationT,
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
struct composite<OperationT,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, nil_t
> {

    typedef composite<OperationT,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O> self_t;

    template <typename TupleT>
    struct result {

        typedef typename composite15_result<
            OperationT, TupleT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
        >::type type;
    };

    composite(OperationT const& op_,
        A const& a_, B const& b_, C const& c_, D const& d_, E const& e_,
        F const& f_, G const& g_, H const& h_, I const& i_, J const& j_,
        K const& k_, L const& l_, M const& m_, N const& n_, O const& o_)
    :   op(op_), a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_), n(n_), o(o_) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        typename actor_result<A, TupleT>::type ra = a.eval(args);
        typename actor_result<B, TupleT>::type rb = b.eval(args);
        typename actor_result<C, TupleT>::type rc = c.eval(args);
        typename actor_result<D, TupleT>::type rd = d.eval(args);
        typename actor_result<E, TupleT>::type re = e.eval(args);
        typename actor_result<F, TupleT>::type rf = f.eval(args);
        typename actor_result<G, TupleT>::type rg = g.eval(args);
        typename actor_result<H, TupleT>::type rh = h.eval(args);
        typename actor_result<I, TupleT>::type ri = i.eval(args);
        typename actor_result<J, TupleT>::type rj = j.eval(args);
        typename actor_result<K, TupleT>::type rk = k.eval(args);
        typename actor_result<L, TupleT>::type rl = l.eval(args);
        typename actor_result<M, TupleT>::type rm = m.eval(args);
        typename actor_result<N, TupleT>::type rn = n.eval(args);
        typename actor_result<O, TupleT>::type ro = o.eval(args);
        return op(ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl, rm, rn, ro);
    }

    mutable OperationT op; //  operation
    A a; B b; C c; D d; E e; F f; G g; H h; I i; J j;
    K k; L l; M m; N n; O o; //  actors
};

#endif
#endif
#endif
#endif

namespace impl {

    ///////////////////////////////////////////////////////////////////////////
    //
    //      make_composite is basically a type computer that answers the
    //      question "Given types T0..TN, what composite type should I
    //      create <composite_type> and if I were to generate an actual
    //      composite, what type <type> should I return?"
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename OperationT
        ,   typename A = nil_t
        ,   typename B = nil_t
        ,   typename C = nil_t

#if PHOENIX_LIMIT > 3
        ,   typename D = nil_t
        ,   typename E = nil_t
        ,   typename F = nil_t

#if PHOENIX_LIMIT > 6
        ,   typename G = nil_t
        ,   typename H = nil_t
        ,   typename I = nil_t

#if PHOENIX_LIMIT > 9
        ,   typename J = nil_t
        ,   typename K = nil_t
        ,   typename L = nil_t

#if PHOENIX_LIMIT > 12
        ,   typename M = nil_t
        ,   typename N = nil_t
        ,   typename O = nil_t

#endif
#endif
#endif
#endif
    >
    struct make_composite {

        typedef composite<OperationT
            ,   typename as_actor<A>::type
            ,   typename as_actor<B>::type
            ,   typename as_actor<C>::type

#if PHOENIX_LIMIT > 3
            ,   typename as_actor<D>::type
            ,   typename as_actor<E>::type
            ,   typename as_actor<F>::type

#if PHOENIX_LIMIT > 6
            ,   typename as_actor<G>::type
            ,   typename as_actor<H>::type
            ,   typename as_actor<I>::type

#if PHOENIX_LIMIT > 9
            ,   typename as_actor<J>::type
            ,   typename as_actor<K>::type
            ,   typename as_actor<L>::type

#if PHOENIX_LIMIT > 12
            ,   typename as_actor<M>::type
            ,   typename as_actor<N>::type
            ,   typename as_actor<O>::type

#endif
#endif
#endif
#endif
        > composite_type;

        typedef actor<composite_type> type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //      make_unary, make_binary, make_binary1, make_binary2 and
    //      make_binary3 utilities are provided here for easy creation of
    //      unary and binary composites.
    //
    ///////////////////////////////////////////////////////////////////////////

    //////////////////////////////////  input is an actor
    template <typename OperationT, typename BaseT>
    struct make_unary {

        typedef typename make_composite
            <OperationT, actor<BaseT> >::type type;

        static type
        construct(actor<BaseT> const& _0)
        {
            typedef typename make_composite
                    <OperationT, actor<BaseT> >::composite_type
                ret_t;

            return ret_t(OperationT(), _0);
        }
    };

    //////////////////////////////////  LHS is an actor, RHS is unknown
    template <typename OperationT, typename BaseT, typename B>
    struct make_binary1 {

        typedef typename make_composite
            <OperationT, actor<BaseT>, B>::type type;

        static type
        construct(actor<BaseT> const& _0_, B const& _1_)
        {
            typedef typename make_composite
                    <OperationT, actor<BaseT>, B>::composite_type
                ret_t;
            
            return ret_t(OperationT(), _0_, as_actor<B>::convert(_1_));
        }
    };

    //////////////////////////////////  LHS is unknown, RHS is an actor
    template <typename OperationT, typename A, typename BaseT>
    struct make_binary2 {

        typedef typename make_composite
            <OperationT, A, actor<BaseT> >::type type;

        static type
        construct(A const& _0_, actor<BaseT> const& _1_)
        {
            typedef typename make_composite
                    <OperationT, A, actor<BaseT> >::composite_type
                ret_t;

            return ret_t(OperationT(), as_actor<A>::convert(_0_), _1_);
        }
    };

    //////////////////////////////////  Both LHS and RHS are actors
    template <typename OperationT, typename BaseA, typename BaseB>
    struct make_binary3 {

        typedef typename make_composite
            <OperationT, actor<BaseA>, actor<BaseB> >::type type;

        static type
        construct(actor<BaseA> const& _0_, actor<BaseB> const& _1_)
        {
            typedef typename make_composite
                    <OperationT, actor<BaseA>, actor<BaseB> >::composite_type
                ret_t;

            return ret_t(OperationT(), _0_, _1_);
        }
    };

}   // namespace impl

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

}   //  namespace phoenix

#endif

/* composite.hpp
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
*/