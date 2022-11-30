/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_FUNCTIONS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_FUNCTIONS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>
#include <boost/spirit/home/classic/phoenix/composite.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  function class
//
//      Lazy functions
//
//      This class provides a mechanism for lazily evaluating functions.
//      Syntactically, a lazy function looks like an ordinary C/C++
//      function. The function call looks the same. However, unlike
//      ordinary functions, the actual function execution is deferred.
//      (see actor.hpp, primitives.hpp and composite.hpp for an
//      overview). For example here are sample factorial function calls:
//
//          factorial(4)
//          factorial(arg1)
//          factorial(arg1 * 6)
//
//      These functions are automatically lazily bound unlike ordinary
//      function pointers or functor objects that need to be explicitly
//      bound through the bind function (see binders.hpp).
//
//      A lazy function works in conjunction with a user defined functor
//      (as usual with a member operator()). Only special forms of
//      functor objects are allowed. This is required to enable true
//      polymorphism (STL style monomorphic functors and function
//      pointers can still be used through the bind facility in
//      binders.hpp).
//
//      This special functor is expected to have a nested template class
//      result<A...TN> (where N is the number of arguments of its
//      member operator()). The nested template class result should have
//      a typedef 'type' that reflects the return type of its member
//      operator(). This is essentially a type computer that answers the
//      metaprogramming question "Given arguments of type A...TN, what
//      will be the operator()'s return type?".
//
//      There is a special case for functors that accept no arguments.
//      Such nullary functors are only required to define a typedef
//      result_type that reflects the return type of its operator().
//
//      Here's an example of a simple functor that computes the
//      factorial of a number:
//
//          struct factorial_impl {
//
//              template <typename Arg>
//              struct result { typedef Arg type; };
//
//              template <typename Arg>
//              Arg operator()(Arg n) const
//              { return (n <= 0) ? 1 : n * this->operator()(n-1); }
//          };
//
//      As can be seen, the functor can be polymorphic. Its arguments
//      and return type are not fixed to a particular type. The example
//      above for example, can handle any type as long as it can carry
//      out the required operations (i.e. <=, * and -).
//
//      We can now declare and instantiate a lazy 'factorial' function:
//
//          function<factorial_impl> factorial;
//
//      Invoking a lazy function 'factorial' does not immediately
//      execute the functor factorial_impl. Instead, a composite (see
//      composite.hpp) object is created and returned to the caller.
//      Example:
//
//          factorial(arg1)
//
//      does nothing more than return a composite. A second function
//      call will invoke the actual factorial function. Example:
//
//          int i = 4;
//          cout << factorial(arg1)(i);
//
//      will print out "24".
//
//      Take note that in certain cases (e.g. for functors with state),
//      an instance may be passed on to the constructor. Example:
//
//          function<factorial_impl> factorial(ftor);
//
//      where ftor is an instance of factorial_impl (this is not
//      necessary in this case since factorial is a simple stateless
//      functor). Take care though when using functors with state
//      because the functors are taken in by value. It is best to keep
//      the data manipulated by a functor outside the functor itself and
//      keep a reference to this data inside the functor. Also, it is
//      best to keep functors as small as possible.
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT>
struct function {

    function() : op() {}
    function(OperationT const& op_) : op(op_) {}

    actor<composite<OperationT> >
    operator()() const;

    template <typename A>
    typename impl::make_composite<OperationT, A>::type
    operator()(A const& a) const;

    template <typename A, typename B>
    typename impl::make_composite<OperationT, A, B>::type
    operator()(A const& a, B const& b) const;

    template <typename A, typename B, typename C>
    typename impl::make_composite<OperationT, A, B, C>::type
    operator()(A const& a, B const& b, C const& c) const;

#if PHOENIX_LIMIT > 3

    template <typename A, typename B, typename C, typename D>
    typename impl::make_composite<OperationT, A, B, C, D>::type
    operator()(A const& a, B const& b, C const& c, D const& d) const;

    template <typename A, typename B, typename C, typename D, typename E>
    typename impl::make_composite<
        OperationT, A, B, C, D, E
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f
    ) const;

#if PHOENIX_LIMIT > 6

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i
    ) const;

#if PHOENIX_LIMIT > 9

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J, K
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J, K, L
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l
    ) const;

#if PHOENIX_LIMIT > 12

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n
    ) const;

    template <
        typename A, typename B, typename C, typename D, typename E,
        typename F, typename G, typename H, typename I, typename J,
        typename K, typename L, typename M, typename N, typename O
    >
    typename impl::make_composite<
        OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
    >::type
    operator()(
        A const& a, B const& b, C const& c, D const& d, E const& e,
        F const& f, G const& g, H const& h, I const& i, J const& j,
        K const& k, L const& l, M const& m, N const& n, O const& o
    ) const;

#endif
#endif
#endif
#endif

    OperationT op;
};

///////////////////////////////////////////////////////////////////////////////
//
//  function class implementation
//
///////////////////////////////////////////////////////////////////////////////
template <typename OperationT>
inline actor<composite<OperationT> >
function<OperationT>::operator()() const
{
    return actor<composite<OperationT> >(op);
}

//////////////////////////////////
template <typename OperationT>
template <typename A>
inline typename impl::make_composite<OperationT, A>::type
function<OperationT>::operator()(A const& a) const
{
    typedef typename impl::make_composite<OperationT, A>::composite_type ret_t;
    return ret_t
    (
        op,
        as_actor<A>::convert(a)
    );
}

//////////////////////////////////
template <typename OperationT>
template <typename A, typename B>
inline typename impl::make_composite<OperationT, A, B>::type
function<OperationT>::operator()(A const& a, B const& b) const
{
    typedef 
        typename impl::make_composite<OperationT, A, B>::composite_type 
        ret_t;
        
    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b)
    );
}

//////////////////////////////////
template <typename OperationT>
template <typename A, typename B, typename C>
inline typename impl::make_composite<OperationT, A, B, C>::type
function<OperationT>::operator()(A const& a, B const& b, C const& c) const
{
    typedef 
        typename impl::make_composite<OperationT, A, B, C>::composite_type
        ret_t;
        
    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c)
    );
}

#if PHOENIX_LIMIT > 3
//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D
>
inline typename impl::make_composite<
    OperationT, A, B, C, D
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D
        >::composite_type ret_t;
        
    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d)
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E
        >::composite_type ret_t;

    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e)
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F
        >::composite_type ret_t;

    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f)
    );
}

#if PHOENIX_LIMIT > 6

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G
        >::composite_type ret_t;

    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g)
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H
        >::composite_type ret_t;
        
    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h)
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I
        >::composite_type ret_t;
        
    return ret_t(
        op,
        as_actor<A>::convert(a),
        as_actor<B>::convert(b),
        as_actor<C>::convert(c),
        as_actor<D>::convert(d),
        as_actor<E>::convert(e),
        as_actor<F>::convert(f),
        as_actor<G>::convert(g),
        as_actor<H>::convert(h),
        as_actor<I>::convert(i)
    );
}

#if PHOENIX_LIMIT > 9

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J
        >::composite_type ret_t;
        
    return ret_t(
        op,
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
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J, K
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J, K
        >::composite_type ret_t;
        
    return ret_t(
        op,
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
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J, K, L
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J, K, L
        >::composite_type ret_t;
        
    return ret_t(
        op,
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
    );
}

#if PHOENIX_LIMIT > 12

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M
        >::composite_type ret_t;
        
    return ret_t(
        op,
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
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N
        >::composite_type ret_t;

    return ret_t(
        op,
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
    );
}

//////////////////////////////////
template <typename OperationT>
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O
>
inline typename impl::make_composite<
    OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
>::type
function<OperationT>::operator()(
    A const& a, B const& b, C const& c, D const& d, E const& e,
    F const& f, G const& g, H const& h, I const& i, J const& j,
    K const& k, L const& l, M const& m, N const& n, O const& o
) const
{
    typedef typename impl::make_composite<
            OperationT, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O
        >::composite_type ret_t;
        
    return ret_t(
        op,
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
    );
}

#endif
#endif
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* functions.hpp
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
*/