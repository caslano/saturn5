/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_TUPLES_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_TUPLES_HPP

///////////////////////////////////////////////////////////////////////////////
//
//  Phoenix predefined maximum limit. This limit defines the maximum
//  number of elements a tuple can hold. This number defaults to 3. The
//  actual maximum is rounded up in multiples of 3. Thus, if this value
//  is 4, the actual limit is 6. The ultimate maximum limit in this
//  implementation is 15.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef PHOENIX_LIMIT
#define PHOENIX_LIMIT 3
#endif

///////////////////////////////////////////////////////////////////////////////
#include <boost/static_assert.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/remove_reference.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
// bogus https://developercommunity.visualstudio.com/t/buggy-warning-c4709/471956
#pragma warning(disable:4709) //comma operator within array index expression
#endif

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  tuple
//
//      Tuples hold heterogeneous types up to a predefined maximum. Only
//      the most basic functionality needed is provided. Unlike other
//      recursive list-like tuple implementations, this tuple
//      implementation uses simple structs similar to std::pair with
//      specialization for 0 to N tuple elements.
//
//          1)  Construction
//              Here are examples on how to construct tuples:
//
//                  typedef tuple<int, char> t1_t;
//                  typedef tuple<int, std::string, double> t2_t;
//
//                  // this tuple has an int and char members
//                  t1_t t1(3, 'c');
//
//                  // this tuple has an int, std::string and double members
//                  t2_t t2(3, "hello", 3.14);
//
//              Tuples can also be constructed from other tuples. The
//              source and destination tuples need not have exactly the
//              same element types. The only requirement is that the
//              source tuple have the same number of elements as the
//              destination and that each element slot in the
//              destination can be copy constructed from the source
//              element. For example:
//
//                  tuple<double, double> t3(t1); // OK. Compatible tuples
//                  tuple<double, double> t4(t2); // Error! Incompatible tuples
//
//          2)  Member access
//                  A member in a tuple can be accessed using the
//                  tuple's [] operator by specifying the Nth
//                  tuple_index. Here are some examples:
//
//                      tuple_index<0> ix0; // 0th index == 1st item
//                      tuple_index<1> ix1; // 1st index == 2nd item
//                      tuple_index<2> ix2; // 2nd index == 3rd item
//
//                      t1[ix0] = 33;  // sets the int member of the tuple t1
//                      t2[ix2] = 6e6; // sets the double member of the tuple t2
//                      t1[ix1] = 'a'; // sets the char member of the tuple t1
//
//                  There are some predefined names are provided in sub-
//                  namespace tuple_index_names:
//
//                      tuple_index<0> _1;
//                      tuple_index<1> _2;
//                      ...
//                      tuple_index<N> _N;
//
//                  These indexes may be used by 'using' namespace
//                  phoenix::tuple_index_names.
//
//                  Access to out of bound indexes returns a nil_t value.
//
//          3)  Member type inquiry
//                  The type of an individual member can be queried.
//                  Example:
//
//                      tuple_element<1, t2_t>::type
//
//                  Refers to the type of the second member (note zero based,
//                  thus 0 = 1st item, 1 = 2nd item) of the tuple.
//
//                  Aside from tuple_element<N, T>::type, there are two
//                  more types that tuple_element provides: rtype and
//                  crtype. While 'type' is the plain underlying type,
//                  'rtype' is the reference type, or type& and 'crtype'
//                  is the constant reference type or type const&. The
//                  latter two are provided to make it easy for the
//                  client in dealing with the possibility of reference
//                  to reference when type is already a reference, which
//                  is illegal in C++.
//
//                  Access to out of bound indexes returns a nil_t type.
//
//          4)  Tuple length
//                  The number of elements in a tuple can be queried.
//                  Example:
//
//                      int n = t1.length;
//
//                  gets the number of elements in tuple t1.
//
//                  length is a static constant. Thus, TupleT::length
//                  also works. Example:
//
//                      int n = t1_t::length;
//
///////////////////////////////////////////////////////////////////////////////
struct nil_t {};
using boost::remove_reference;
using boost::call_traits;

//////////////////////////////////
namespace impl {

    template <typename T>
    struct access {

        typedef const T& ctype;
        typedef T& type;
    };

    template <typename T>
    struct access<T&> {

        typedef T& ctype;
        typedef T& type;
    };
}

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_element
//
//      A query class that gets the Nth element inside a tuple.
//      Examples:
//
//          tuple_element<1, tuple<int, char, void*> >::type    //  plain
//          tuple_element<1, tuple<int, char, void*> >::rtype   //  ref
//          tuple_element<1, tuple<int, char, void*> >::crtype  //  const ref
//
//      Has type char which is the 2nd type in the tuple
//      (note zero based, thus 0 = 1st item, 1 = 2nd item).
//
//          Given a tuple object, the static function tuple_element<N,
//          TupleT>::get(tuple) gets the Nth element in the tuple. The
//          tuple class' tuple::operator[] uses this to get its Nth
//          element.
//
///////////////////////////////////////////////////////////////////////////////
template <int N, typename TupleT>
struct tuple_element
{
    typedef nil_t type;
    typedef nil_t& rtype;
    typedef nil_t const& crtype;

    static nil_t    get(TupleT const&)      { return nil_t(); }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<0, TupleT>
{
    typedef typename TupleT::a_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.a; }
    static crtype   get(TupleT const& t)    { return t.a; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<1, TupleT>
{
    typedef typename TupleT::b_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.b; }
    static crtype   get(TupleT const& t)    { return t.b; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<2, TupleT>
{
    typedef typename TupleT::c_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.c; }
    static crtype   get(TupleT const& t)    { return t.c; }
};

#if PHOENIX_LIMIT > 3
//////////////////////////////////
template <typename TupleT>
struct tuple_element<3, TupleT>
{
    typedef typename TupleT::d_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.d; }
    static crtype   get(TupleT const& t)    { return t.d; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<4, TupleT>
{
    typedef typename TupleT::e_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.e; }
    static crtype   get(TupleT const& t)    { return t.e; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<5, TupleT>
{
    typedef typename TupleT::f_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.f; }
    static crtype   get(TupleT const& t)    { return t.f; }
};

#if PHOENIX_LIMIT > 6
//////////////////////////////////
template <typename TupleT>
struct tuple_element<6, TupleT>
{
    typedef typename TupleT::g_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.g; }
    static crtype   get(TupleT const& t)    { return t.g; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<7, TupleT>
{
    typedef typename TupleT::h_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.h; }
    static crtype   get(TupleT const& t)    { return t.h; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<8, TupleT>
{
    typedef typename TupleT::i_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.i; }
    static crtype   get(TupleT const& t)    { return t.i; }
};

#if PHOENIX_LIMIT > 9
//////////////////////////////////
template <typename TupleT>
struct tuple_element<9, TupleT>
{
    typedef typename TupleT::j_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.j; }
    static crtype   get(TupleT const& t)    { return t.j; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<10, TupleT>
{
    typedef typename TupleT::k_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.k; }
    static crtype   get(TupleT const& t)    { return t.k; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<11, TupleT>
{
    typedef typename TupleT::l_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.l; }
    static crtype   get(TupleT const& t)    { return t.l; }
};

#if PHOENIX_LIMIT > 12
//////////////////////////////////
template <typename TupleT>
struct tuple_element<12, TupleT>
{
    typedef typename TupleT::m_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.m; }
    static crtype   get(TupleT const& t)    { return t.m; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<13, TupleT>
{
    typedef typename TupleT::n_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.n; }
    static crtype   get(TupleT const& t)    { return t.n; }
};

//////////////////////////////////
template <typename TupleT>
struct tuple_element<14, TupleT>
{
    typedef typename TupleT::o_type type;
    typedef typename impl::access<type>::type rtype;
    typedef typename impl::access<type>::ctype crtype;

    static rtype    get(TupleT& t)          { return t.o; }
    static crtype   get(TupleT const& t)    { return t.o; }
};

#endif
#endif
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  tuple forward declaration.
//
///////////////////////////////////////////////////////////////////////////////
template <
        typename A = nil_t
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
struct tuple;

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_index
//
//      This class wraps an integer in a type to be used for indexing
//      the Nth element in a tuple. See tuple operator[]. Some
//      predefined names are provided in sub-namespace
//      tuple_index_names.
//
///////////////////////////////////////////////////////////////////////////////
template <int N>
struct tuple_index {};

//////////////////////////////////
namespace tuple_index_names {

    tuple_index<0> const _1 = tuple_index<0>();
    tuple_index<1> const _2 = tuple_index<1>();
    tuple_index<2> const _3 = tuple_index<2>();

#if PHOENIX_LIMIT > 3
    tuple_index<3> const _4 = tuple_index<3>();
    tuple_index<4> const _5 = tuple_index<4>();
    tuple_index<5> const _6 = tuple_index<5>();

#if PHOENIX_LIMIT > 6
    tuple_index<6> const _7 = tuple_index<6>();
    tuple_index<7> const _8 = tuple_index<7>();
    tuple_index<8> const _9 = tuple_index<8>();

#if PHOENIX_LIMIT > 9
    tuple_index<9> const _10 = tuple_index<9>();
    tuple_index<10> const _11 = tuple_index<10>();
    tuple_index<11> const _12 = tuple_index<11>();

#if PHOENIX_LIMIT > 12
    tuple_index<12> const _13 = tuple_index<12>();
    tuple_index<13> const _14 = tuple_index<13>();
    tuple_index<14> const _15 = tuple_index<14>();

#endif
#endif
#endif
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_common class
//
///////////////////////////////////////////////////////////////////////////////
template <typename DerivedT>
struct tuple_base {

    typedef nil_t   a_type;
    typedef nil_t   b_type;
    typedef nil_t   c_type;

#if PHOENIX_LIMIT > 3
    typedef nil_t   d_type;
    typedef nil_t   e_type;
    typedef nil_t   f_type;

#if PHOENIX_LIMIT > 6
    typedef nil_t   g_type;
    typedef nil_t   h_type;
    typedef nil_t   i_type;

#if PHOENIX_LIMIT > 9
    typedef nil_t   j_type;
    typedef nil_t   k_type;
    typedef nil_t   l_type;

#if PHOENIX_LIMIT > 12
    typedef nil_t   m_type;
    typedef nil_t   n_type;
    typedef nil_t   o_type;

#endif
#endif
#endif
#endif

    template <int N>
    typename tuple_element<N, DerivedT>::crtype
    operator[](tuple_index<N>) const
    {
        return tuple_element<N, DerivedT>
            ::get(*static_cast<DerivedT const*>(this));
    }

    template <int N>
    typename tuple_element<N, DerivedT>::rtype
    operator[](tuple_index<N>)
    {
        return tuple_element<N, DerivedT>
            ::get(*static_cast<DerivedT*>(this));
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <0 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <>
struct tuple<>
:   public tuple_base<tuple<> > {

    BOOST_STATIC_CONSTANT(int, length = 0);
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <1 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A>
struct tuple<A, nil_t, nil_t,
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
>
:   public tuple_base<tuple<A> > {

    BOOST_STATIC_CONSTANT(int, length = 1);
    typedef A a_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_
    ):  a(a_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <2 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct tuple<A, B, nil_t,
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
>
:   public tuple_base<tuple<A, B> > {

    BOOST_STATIC_CONSTANT(int, length = 2);
    typedef A a_type; typedef B b_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_
    ):  a(a_), b(b_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <3 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename B, typename C>
struct tuple<A, B, C,
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
>
:   public tuple_base<tuple<A, B, C> > {

    BOOST_STATIC_CONSTANT(int, length = 3);
    typedef A a_type; typedef B b_type;
    typedef C c_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_
    ):  a(a_), b(b_), c(c_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c;
};

#if PHOENIX_LIMIT > 3
///////////////////////////////////////////////////////////////////////////////
//
//  tuple <4 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename B, typename C, typename D>
struct tuple<A, B, C, D, nil_t, nil_t,
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
>
:   public tuple_base<tuple<A, B, C, D> > {

    BOOST_STATIC_CONSTANT(int, length = 4);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_
    ):  a(a_), b(b_), c(c_), d(d_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <5 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <typename A, typename B, typename C, typename D, typename E>
struct tuple<A, B, C, D, E, nil_t,
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
>
:   public tuple_base<tuple<A, B, C, D, E> > {

    BOOST_STATIC_CONSTANT(int, length = 5);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <6 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F>
struct tuple<A, B, C, D, E, F,
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
>
:   public tuple_base<tuple<A, B, C, D, E, F> > {

    BOOST_STATIC_CONSTANT(int, length = 6);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f;
};

#if PHOENIX_LIMIT > 6
///////////////////////////////////////////////////////////////////////////////
//
//  tuple <7 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G>
struct tuple<A, B, C, D, E, F, G, nil_t, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G> > {

    BOOST_STATIC_CONSTANT(int, length = 7);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <8 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H>
struct tuple<A, B, C, D, E, F, G, H, nil_t,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G, H> > {

    BOOST_STATIC_CONSTANT(int, length = 8);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <9 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I>
struct tuple<A, B, C, D, E, F, G, H, I,
#if PHOENIX_LIMIT > 9
    nil_t, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G, H, I> > {

    BOOST_STATIC_CONSTANT(int, length = 9);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i;
};

#if PHOENIX_LIMIT > 9
///////////////////////////////////////////////////////////////////////////////
//
//  tuple <10 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J>
struct tuple<A, B, C, D, E, F, G, H, I, J, nil_t, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G, H, I, J> > {

    BOOST_STATIC_CONSTANT(int, length = 10);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <11 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K>
struct tuple<A, B, C, D, E, F, G, H, I, J, K, nil_t,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G, H, I, J, K> > {

    BOOST_STATIC_CONSTANT(int, length = 11);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;
    typedef K k_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_,
        typename call_traits<K>::param_type k_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()]),
        k(init[tuple_index<10>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
    K k;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <12 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L>
struct tuple<A, B, C, D, E, F, G, H, I, J, K, L,
#if PHOENIX_LIMIT > 12
    nil_t, nil_t, nil_t,
#endif
    nil_t   //  Unused
>
:   public tuple_base<tuple<A, B, C, D, E, F, G, H, I, J, K, L> > {

    BOOST_STATIC_CONSTANT(int, length = 12);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;
    typedef K k_type; typedef L l_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_,
        typename call_traits<K>::param_type k_,
        typename call_traits<L>::param_type l_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()]),
        k(init[tuple_index<10>()]), l(init[tuple_index<11>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
    K k; L l;
};

#if PHOENIX_LIMIT > 12
///////////////////////////////////////////////////////////////////////////////
//
//  tuple <13 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M>
struct tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, nil_t, nil_t, nil_t>
:   public tuple_base<
        tuple<A, B, C, D, E, F, G, H, I, J, K, L, M> > {

    BOOST_STATIC_CONSTANT(int, length = 13);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;
    typedef K k_type; typedef L l_type;
    typedef M m_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_,
        typename call_traits<K>::param_type k_,
        typename call_traits<L>::param_type l_,
        typename call_traits<M>::param_type m_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()]),
        k(init[tuple_index<10>()]), l(init[tuple_index<11>()]),
        m(init[tuple_index<12>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
    K k; L l; M m;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <14 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N>
struct tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N, nil_t, nil_t>
:   public tuple_base<
        tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N> > {

    BOOST_STATIC_CONSTANT(int, length = 14);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;
    typedef K k_type; typedef L l_type;
    typedef M m_type; typedef N n_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_,
        typename call_traits<K>::param_type k_,
        typename call_traits<L>::param_type l_,
        typename call_traits<M>::param_type m_,
        typename call_traits<N>::param_type n_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_), n(n_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()]),
        k(init[tuple_index<10>()]), l(init[tuple_index<11>()]),
        m(init[tuple_index<12>()]), n(init[tuple_index<13>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
    K k; L l; M m; N n;
};

///////////////////////////////////////////////////////////////////////////////
//
//  tuple <15 member> class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename A, typename B, typename C, typename D, typename E,
    typename F, typename G, typename H, typename I, typename J,
    typename K, typename L, typename M, typename N, typename O>
struct tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, nil_t>
:   public tuple_base<
        tuple<A, B, C, D, E, F, G, H, I, J, K, L, M, N, O> > {

    BOOST_STATIC_CONSTANT(int, length = 15);
    typedef A a_type; typedef B b_type;
    typedef C c_type; typedef D d_type;
    typedef E e_type; typedef F f_type;
    typedef G g_type; typedef H h_type;
    typedef I i_type; typedef J j_type;
    typedef K k_type; typedef L l_type;
    typedef M m_type; typedef N n_type;
    typedef O o_type;

    tuple() {}

    tuple(
        typename call_traits<A>::param_type a_,
        typename call_traits<B>::param_type b_,
        typename call_traits<C>::param_type c_,
        typename call_traits<D>::param_type d_,
        typename call_traits<E>::param_type e_,
        typename call_traits<F>::param_type f_,
        typename call_traits<G>::param_type g_,
        typename call_traits<H>::param_type h_,
        typename call_traits<I>::param_type i_,
        typename call_traits<J>::param_type j_,
        typename call_traits<K>::param_type k_,
        typename call_traits<L>::param_type l_,
        typename call_traits<M>::param_type m_,
        typename call_traits<N>::param_type n_,
        typename call_traits<O>::param_type o_
    ):  a(a_), b(b_), c(c_), d(d_), e(e_),
        f(f_), g(g_), h(h_), i(i_), j(j_),
        k(k_), l(l_), m(m_), n(n_), o(o_) {}

    template <typename TupleT>
    tuple(TupleT const& init)
    :   a(init[tuple_index<0>()]), b(init[tuple_index<1>()]),
        c(init[tuple_index<2>()]), d(init[tuple_index<3>()]),
        e(init[tuple_index<4>()]), f(init[tuple_index<5>()]),
        g(init[tuple_index<6>()]), h(init[tuple_index<7>()]),
        i(init[tuple_index<8>()]), j(init[tuple_index<9>()]),
        k(init[tuple_index<10>()]), l(init[tuple_index<11>()]),
        m(init[tuple_index<12>()]), n(init[tuple_index<13>()]),
        o(init[tuple_index<14>()])
    { BOOST_STATIC_ASSERT(TupleT::length == length); }

    A a; B b; C c; D d; E e;
    F f; G g; H h; I i; J j;
    K k; L l; M m; N n; O o;
};

#endif
#endif
#endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* tuples.hpp
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
*/