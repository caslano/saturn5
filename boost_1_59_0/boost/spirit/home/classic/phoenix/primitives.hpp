/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_PRIMITIVES_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_PRIMITIVES_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  argument class
//
//      Lazy arguments
//
//      An actor base class that extracts and returns the Nth argument
//      from the argument list passed in the 'args' tuple in the eval
//      member function (see actor.hpp). There are some predefined
//      argument constants that can be used as actors (arg1..argN).
//
//      The argument actor is a place-holder for the actual arguments
//      passed by the client. For example, wherever arg1 is seen placed
//      in a lazy function (see functions.hpp) or lazy operator (see
//      operators.hpp), this will be replaced by the actual first
//      argument in the actual function evaluation. Argument actors are
//      essentially lazy arguments. A lazy argument is a full actor in
//      its own right and can be evaluated through the actor's operator().
//
//      Example:
//
//          char        c = 'A';
//          int         i = 123;
//          const char* s = "Hello World";
//
//          cout << arg1(c) << ' ';
//          cout << arg1(i, s) << ' ';
//          cout << arg2(i, s) << ' ';
//
//       will print out "A 123 Hello World"
//
///////////////////////////////////////////////////////////////////////////////
template <int N>
struct argument {

    template <typename TupleT>
    struct result { typedef typename tuple_element<N, TupleT>::type type; };

    template <typename TupleT>
    typename tuple_element<N, TupleT>::type
    eval(TupleT const& args) const
    {
        tuple_index<N> const idx;
        return args[idx];
    }
};

//////////////////////////////////
actor<argument<0> > const arg1 = argument<0>();
actor<argument<1> > const arg2 = argument<1>();
actor<argument<2> > const arg3 = argument<2>();

#if PHOENIX_LIMIT > 3
actor<argument<3> > const arg4 = argument<3>();
actor<argument<4> > const arg5 = argument<4>();
actor<argument<5> > const arg6 = argument<5>();

#if PHOENIX_LIMIT > 6
actor<argument<6> > const arg7 = argument<6>();
actor<argument<7> > const arg8 = argument<7>();
actor<argument<8> > const arg9 = argument<8>();

#if PHOENIX_LIMIT > 9
actor<argument<9> > const arg10 = argument<9>();
actor<argument<10> > const arg11 = argument<10>();
actor<argument<11> > const arg12 = argument<11>();

#if PHOENIX_LIMIT > 12
actor<argument<12> > const arg13 = argument<12>();
actor<argument<13> > const arg14 = argument<13>();
actor<argument<14> > const arg15 = argument<14>();

#endif
#endif
#endif
#endif
///////////////////////////////////////////////////////////////////////////////
//
//  value class
//
//      Lazy values
//
//      A bound actual parameter is kept in a value class for deferred
//      access later when needed. A value object is immutable. Value
//      objects are typically created through the val(x) free function
//      which returns a value<T> with T deduced from the type of x. x is
//      held in the value<T> object by value.
//
//      Lazy values are actors. As such, lazy values can be evaluated
//      through the actor's operator(). Such invocation gives the value's
//      identity. Example:
//
//          cout << val(3)() << val("Hello World")();
//
//      prints out "3 Hello World"
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct value {

    typedef typename boost::remove_reference<T>::type plain_t;

    template <typename TupleT>
    struct result { typedef plain_t const type; };

    value(plain_t val_)
    :   val(val_) {}

    template <typename TupleT>
    plain_t const
    eval(TupleT const& /*args*/) const
    {
        return val;
    }

    plain_t val;
};

//////////////////////////////////
template <typename T>
inline actor<value<T> > const
val(T v)
{
    return value<T>(v);
}

//////////////////////////////////
template <typename BaseT>
void
val(actor<BaseT> const& v);     //  This is undefined and not allowed.

///////////////////////////////////////////////////////////////////////////
//
//  Arbitrary types T are typically converted to a actor<value<T> >
//  (see as_actor<T> in actor.hpp). A specialization is also provided
//  for arrays. T[N] arrays are converted to actor<value<T const*> >.
//
///////////////////////////////////////////////////////////////////////////
template <typename T>
struct as_actor {

    typedef actor<value<T> > type;
    static type convert(T const& x)
    { return value<T>(x); }
};

//////////////////////////////////
template <typename T, int N>
struct as_actor<T[N]> {

    typedef actor<value<T const*> > type;
    static type convert(T const x[N])
    { return value<T const*>(x); }
};

///////////////////////////////////////////////////////////////////////////////
//
//  variable class
//
//      Lazy variables
//
//      A bound actual parameter may also be held by non-const reference
//      in a variable class for deferred access later when needed. A
//      variable object is mutable, i.e. its referenced variable can be
//      modified. Variable objects are typically created through the
//      var(x) free function which returns a variable<T> with T deduced
//      from the type of x. x is held in the value<T> object by
//      reference.
//
//      Lazy variables are actors. As such, lazy variables can be
//      evaluated through the actor's operator(). Such invocation gives
//      the variables's identity. Example:
//
//          int i = 3;
//          char const* s = "Hello World";
//          cout << var(i)() << var(s)();
//
//      prints out "3 Hello World"
//
//      Another free function const_(x) may also be used. const_(x) creates
//      a variable<T const&> object using a constant reference.
//
///////////////////////////////////////////////////////////////////////////////
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

template <typename T>
struct variable {

    template <typename TupleT>
    struct result { typedef T& type; };

    variable(T& var_)
    :   var(var_) {}

    template <typename TupleT>
    T&
    eval(TupleT const& /*args*/) const
    {
        return var;
    }

    T& var;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

//////////////////////////////////
template <typename T>
inline actor<variable<T> > const
var(T& v)
{
    return variable<T>(v);
}

//////////////////////////////////
template <typename T>
inline actor<variable<T const> > const
const_(T const& v)
{
    return variable<T const>(v);
}

//////////////////////////////////
template <typename BaseT>
void
var(actor<BaseT> const& v);     //  This is undefined and not allowed.

//////////////////////////////////
template <typename BaseT>
void
const_(actor<BaseT> const& v);  //  This is undefined and not allowed.

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#endif

/* primitives.hpp
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
*/