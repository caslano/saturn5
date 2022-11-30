/*=============================================================================
    Phoenix v1.2
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_ACTOR_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_ACTOR_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/tuples.hpp>
#include <boost/type_traits/remove_reference.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

//  These are forward declared here because we cannot include impl.hpp
//  or operators.hpp yet but the actor's assignment operator and index
//  operator are required to be members.

//////////////////////////////////
struct assign_op;
struct index_op;

//////////////////////////////////
namespace impl {

    template <typename OperationT, typename BaseT, typename B>
    struct make_binary1;
}

///////////////////////////////////////////////////////////////////////////////
//
//  unpack_tuple class
//
//      This class is used to unpack a supplied tuple such, that the members of 
//      this tuple will be handled as if they would be supplied separately.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TupleT>
struct unpack_tuple : public TupleT {

    typedef TupleT tuple_t;
    
    unpack_tuple() {}
    unpack_tuple(tuple_t const &tuple_) : TupleT(tuple_) {}
};

///////////////////////////////////////////////////////////////////////////////
//
//  actor class
//
//      This class is a protocol class for all actors. This class is
//      essentially an interface contract. The actor class does not
//      really know how how to act on anything but instead relies on the
//      template parameter BaseT (from which the actor will derive from)
//      to do the actual action.
//
//      An actor is a functor that is capable of accepting arguments up
//      to a predefined maximum. It is up to the base class to do the
//      actual processing or possibly to limit the arity (no. of
//      arguments) passed in. Upon invocation of the functor through a
//      supplied operator(), the actor funnels the arguments passed in
//      by the client into a tuple and calls the base eval member
//      function.
//
//      Schematically:
//
//          arg0 ---------|
//          arg1 ---------|
//          arg2 ---------|---> tupled_args ---> base.eval
//          ...           |
//          argN ---------|
//
//          actor::operator()(arg0, arg1... argN)
//              ---> BaseT::eval(tupled_args);
//
//      Actor base classes from which this class inherits from are
//      expected to have a corresponding member function eval compatible
//      with the conceptual Interface:
//
//          template <typename TupleT>
//          actor_return_type
//          eval(TupleT const& args) const;
//
//      where args are the actual arguments passed in by the client
//      funneled into a tuple (see tuple.hpp for details).
//
//      The actor_return_type can be anything. Base classes are free to
//      return any type, even argument dependent types (types that are
//      deduced from the types of the arguments). After evaluating the
//      parameters and doing some computations or actions, the eval
//      member function concludes by returning something back to the
//      client. To do this, the forwarding function (the actor's
//      operator()) needs to know the return type of the eval member
//      function that it is calling. For this purpose, actor base
//      classes are required to provide a nested template class:
//
//          template <typename TupleT>
//          struct result;
//
//      This auxiliary class provides the result type information
//      returned by the eval member function of a base actor class. The
//      nested template class result should have a typedef 'type' that
//      reflects the return type of its member function eval. It is
//      basically a type computer that answers the question "given
//      arguments packed into a TupleT type, what will be the result
//      type of the eval member function of ActorT?". The template class
//      actor_result queries this to extract the return type of an
//      actor. Example:
//
//          typedef typename actor_result<ActorT, TupleT>::type
//              actor_return_type;
//
//      where actor_return_type is the actual type returned by ActorT's
//      eval member function given some arguments in a TupleT.
//
///////////////////////////////////////////////////////////////////////////////
template <typename ActorT, typename TupleT>
struct actor_result {

    typedef typename ActorT::template result<TupleT>::type type;
    typedef typename boost::remove_reference<type>::type plain_type;
};

//////////////////////////////////
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

template <typename BaseT>
struct actor : public BaseT {

    actor();
    actor(BaseT const& base);

    typename actor_result<BaseT, tuple<> >::type
    operator()() const;

    template <typename A>
    typename actor_result<BaseT, tuple<A&> >::type
    operator()(A& a) const;

    template <typename A, typename B>
    typename actor_result<BaseT, tuple<A&, B&> >::type
    operator()(A& a, B& b) const;

    template <typename A, typename B, typename C>
    typename actor_result<BaseT, tuple<A&, B&, C&> >::type
    operator()(A& a, B& b, C& c) const;

#if PHOENIX_LIMIT > 3
    template <typename A, typename B, typename C, typename D>
    typename actor_result<BaseT, tuple<A&, B&, C&, D&> >::type
    operator()(A& a, B& b, C& c, D& d) const;

    template <typename A, typename B, typename C, typename D, typename E>
    typename actor_result<BaseT, tuple<A&, B&, C&, D&, E&> >::type
    operator()(A& a, B& b, C& c, D& d, E& e) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F>
    typename actor_result<BaseT, tuple<A&, B&, C&, D&, E&, F&> >::type
    operator()(A& a, B& b, C& c, D& d, E& e, F& f) const;

#if PHOENIX_LIMIT > 6

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G>
    typename actor_result<BaseT, tuple<A&, B&, C&, D&, E&, F&, G&> >::type
    operator()(A& a, B& b, C& c, D& d, E& e, F& f, G& g) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&>
    >::type
    operator()(A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&>
    >::type
    operator()(A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i) const;

#if PHOENIX_LIMIT > 9

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j,
        K& k) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j,
        K& k, L& l) const;

#if PHOENIX_LIMIT > 12

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j,
        K& k, L& l, M& m) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j,
        K& k, L& l, M& m, N& n) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O>
    typename actor_result<BaseT,
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&, O&>
    >::type
    operator()(
        A& a, B& b, C& c, D& d, E& e, F& f, G& g, H& h, I& i, J& j,
        K& k, L& l, M& m, N& n, O& o) const;

#endif
#endif
#endif
#endif

    template <typename TupleT>
    typename actor_result<BaseT, unpack_tuple<TupleT> >::type
    operator()(unpack_tuple<TupleT> const &t) const;
    
    template <typename B>
    typename impl::make_binary1<assign_op, BaseT, B>::type
    operator=(B const& b) const;

    template <typename B>
    typename impl::make_binary1<index_op, BaseT, B>::type
    operator[](B const& b) const;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

///////////////////////////////////////////////////////////////////////////
//
//  as_actor
//
//      as_actor is a meta-program that converts an arbitrary type into
//      an actor. All participants in the framework must be first-class
//      actors. This meta-program is used all throughout the framework
//      whenever an unknown type needs to be converted to an actor.
//      as_actor specializations are expected to have a typedef 'type'.
//      This is the destination actor type. A static member function
//      'convert' converts an object to this target type.
//
//      The meta-program does no conversion if the object to be
//      converted is already an actor.
//
///////////////////////////////////////////////////////////////////////////
template <typename T>
struct as_actor;

//////////////////////////////////
template <typename BaseT>
struct as_actor<actor<BaseT> > {

    typedef actor<BaseT> type;
    static type convert(actor<BaseT> const& x) { return x; }
};

//////////////////////////////////
template <>
struct as_actor<nil_t> {

    typedef nil_t type;
    static nil_t convert(nil_t /*x*/)
    { return nil_t(); }
};

//////////////////////////////////
template <>
struct as_actor<void> {

    typedef void type;
    //  ERROR!!!
};

///////////////////////////////////////////////////////////////////////////////
//
//  actor class implementation
//
///////////////////////////////////////////////////////////////////////////////
template <typename BaseT>
actor<BaseT>::actor()
:   BaseT() {}

//////////////////////////////////
template <typename BaseT>
actor<BaseT>::actor(BaseT const& base)
:   BaseT(base) {}

//////////////////////////////////
template <typename BaseT>
inline typename actor_result<BaseT, tuple<> >::type
actor<BaseT>::operator()() const
{
    return BaseT::eval(tuple<>());
}

//////////////////////////////////
template <typename BaseT>
template <typename A>
inline typename actor_result<BaseT, tuple<A&> >::type
actor<BaseT>::operator()(A& a_) const
{
    return BaseT::eval(tuple<A&>(a_));
}

//////////////////////////////////
template <typename BaseT>
template <typename A, typename B>
inline typename actor_result<BaseT, tuple<A&, B&> >::type
actor<BaseT>::operator()(A& a_, B& b_) const
{
    return BaseT::eval(tuple<A&, B&>(a_, b_));
}

//////////////////////////////////
template <typename BaseT>
template <typename A, typename B, typename C>
inline typename actor_result<BaseT, tuple<A&, B&, C&> >::type
actor<BaseT>::operator()(A& a_, B& b_, C& c_) const
{
    return BaseT::eval(tuple<A&, B&, C&>(a_, b_, c_));
}

#if PHOENIX_LIMIT > 3
//////////////////////////////////
template <typename BaseT>
template <typename A, typename B, typename C, typename D>
inline typename actor_result<BaseT, tuple<A&, B&, C&, D&> >::type
actor<BaseT>::operator()(A& a_, B& b_, C& c_, D& d_) const
{
    return BaseT::eval(tuple<A&, B&, C&, D&>(a_, b_, c_, d_));
}

//////////////////////////////////
template <typename BaseT>
template <typename A, typename B, typename C, typename D, typename E>
inline typename actor_result<BaseT, tuple<A&, B&, C&, D&, E&> >::type
actor<BaseT>::operator()(A& a_, B& b_, C& c_, D& d_, E& e_) const
{
    return BaseT::eval(tuple<A&, B&, C&, D&, E&>(a_, b_, c_, d_, e_));
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&>
        (a_, b_, c_, d_, e_, f_)
    );
}

#if PHOENIX_LIMIT > 6
//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&>
        (a_, b_, c_, d_, e_, f_, g_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&>
        (a_, b_, c_, d_, e_, f_, g_, h_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_)
    );
}

#if PHOENIX_LIMIT > 9
//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_,
    K& k_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_,
    K& k_, L& l_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_)
    );
}

#if PHOENIX_LIMIT > 12
//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_,
    K& k_, L& l_, M& m_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_,
    K& k_, L& l_, M& m_, N& n_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_, n_)
    );
}

//////////////////////////////////
template <typename BaseT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
inline typename actor_result<BaseT,
    tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&, O&>
>::type
actor<BaseT>::operator()(
    A& a_, B& b_, C& c_, D& d_, E& e_, F& f_, G& g_, H& h_, I& i_, J& j_,
    K& k_, L& l_, M& m_, N& n_, O& o_
) const
{
    return BaseT::eval(
        tuple<A&, B&, C&, D&, E&, F&, G&, H&, I&, J&, K&, L&, M&, N&, O&>
        (a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_, n_, o_)
    );
}

#endif
#endif
#endif
#endif

//////////////////////////////////
template <typename BaseT>
template <typename TupleT>
typename actor_result<BaseT, unpack_tuple<TupleT> >::type
actor<BaseT>::operator()(unpack_tuple<TupleT> const &t) const
{
    return BaseT::eval(t);
}

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* actor.hpp
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
*/