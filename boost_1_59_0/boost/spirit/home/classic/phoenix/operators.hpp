/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_OPERATORS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_OPERATORS_HPP

///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_NO_CWCTYPE)
    #include <cwctype>
#endif

#if (defined(__BORLANDC__) && !defined(__clang__)) || (defined(__ICL) && __ICL >= 700)
#define CREF const&
#else
#define CREF
#endif

#include <climits>
#include <boost/spirit/home/classic/phoenix/actor.hpp>
#include <boost/spirit/home/classic/phoenix/composite.hpp>
#include <boost/config.hpp>
#include <boost/mpl/if.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

///////////////////////////////////////////////////////////////////////////////
//
//  Operators
//
//      Lazy operators
//
//      This class provides a mechanism for lazily evaluating operators.
//      Syntactically, a lazy operator looks like an ordinary C/C++
//      infix, prefix or postfix operator. The operator application
//      looks the same. However, unlike ordinary operators, the actual
//      operator execution is deferred. (see actor.hpp, primitives.hpp
//      and composite.hpp for an overview). Samples:
//
//          arg1 + arg2
//          1 + arg1 * arg2
//          1 / -arg1
//          arg1 < 150
//
//      T1 set of classes implement all the C++ free operators. Like
//      lazy functions (see functions.hpp), lazy operators are not
//      immediately executed when invoked. Instead, a composite (see
//      composite.hpp) object is created and returned to the caller.
//      Example:
//
//          (arg1 + arg2) * arg3
//
//      does nothing more than return a composite. T1 second function
//      call will evaluate the actual operators. Example:
//
//          int i = 4, j = 5, k = 6;
//          cout << ((arg1 + arg2) * arg3)(i, j, k);
//
//      will print out "54".
//
//      Arbitrarily complex expressions can be lazily evaluated
//      following three simple rules:
//
//          1) Lazy evaluated binary operators apply when at least one
//          of the operands is an actor object (see actor.hpp and
//          primitives.hpp). Consequently, if an operand is not an actor
//          object, it is implicitly converted to an object of type
//          actor<value<T> > (where T is the original type of the
//          operand).
//
//          2) Lazy evaluated unary operators apply only to operands
//          which are actor objects.
//
//          3) The result of a lazy operator is a composite actor object
//          that can in turn apply to rule 1.
//
//      Example:
//
//          arg1 + 3
//
//      is a lazy expression involving the operator+. Following rule 1,
//      lazy evaluation is triggered since arg1 is an instance of an
//      actor<argument<N> > class (see primitives.hpp). The right
//      operand <3> is implicitly converted to an actor<value<int> >.
//      The result of this binary + expression is a composite object,
//      following rule 3.
//
//      Take note that although at least one of the operands must be a
//      valid actor class in order for lazy evaluation to take effect,
//      if this is not the case and we still want to lazily evaluate an
//      expression, we can use var(x), val(x) or cref(x) to transform
//      the operand into a valid action object (see primitives.hpp).
//      Example:
//
//          val(1) << 3;
//
//      Supported operators:
//
//          Unary operators:
//
//              prefix:   ~, !, -, +, ++, --, & (reference), * (dereference)
//              postfix:  ++, --
//
//          Binary operators:
//
//              =, [], +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
//              +, -, *, /, %, &, |, ^, <<, >>
//              ==, !=, <, >, <=, >=
//              &&, ||
//
//      Each operator has a special tag type associated with it. For
//      example the binary + operator has a plus_op tag type associated
//      with it. This is used to specialize either the unary_operator or
//      binary_operator template classes (see unary_operator and
//      binary_operator below). Specializations of these unary_operator
//      and binary_operator are the actual workhorses that implement the
//      operations. The behavior of each lazy operator depends on these
//      unary_operator and binary_operator specializations. 'preset'
//      specializations conform to the canonical operator rules modeled
//      by the behavior of integers and pointers:
//
//          Prefix -, + and ~ accept constant arguments and return an
//          object by value.
//
//          The ! accept constant arguments and returns a boolean
//          result.
//
//          The & (address-of), * (dereference) both return a reference
//          to an object.
//
//          Prefix ++ returns a reference to its mutable argument after
//          it is incremented.
//
//          Postfix ++ returns the mutable argument by value before it
//          is incremented.
//
//          The += and its family accept mutable right hand side (rhs)
//          operand and return a reference to the rhs operand.
//
//          Infix + and its family accept constant arguments and return
//          an object by value.
//
//          The == and its family accept constant arguments and return a
//          boolean result.
//
//          Operators && and || accept constant arguments and return a
//          boolean result and are short circuit evaluated as expected.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Operator tags
//
//      Each C++ operator has a corresponding tag type. This is
//      used as a means for specializing the unary_operator and
//      binary_operator (see below). The tag also serves as the
//      lazy operator type compatible as a composite operation
//      see (composite.hpp).
//
///////////////////////////////////////////////////////////////////////////////

//  Unary operator tags

struct negative_op;         struct positive_op;
struct logical_not_op;      struct invert_op;
struct reference_op;        struct dereference_op;
struct pre_incr_op;         struct pre_decr_op;
struct post_incr_op;        struct post_decr_op;

//  Binary operator tags

struct assign_op;           struct index_op;
struct plus_assign_op;      struct minus_assign_op;
struct times_assign_op;     struct divide_assign_op;    struct mod_assign_op;
struct and_assign_op;       struct or_assign_op;        struct xor_assign_op;
struct shift_l_assign_op;   struct shift_r_assign_op;

struct plus_op;             struct minus_op;
struct times_op;            struct divide_op;           struct mod_op;
struct and_op;              struct or_op;               struct xor_op;
struct shift_l_op;          struct shift_r_op;

struct eq_op;               struct not_eq_op;
struct lt_op;               struct lt_eq_op;
struct gt_op;               struct gt_eq_op;
struct logical_and_op;      struct logical_or_op;

///////////////////////////////////////////////////////////////////////////////
//
//  unary_operator<TagT, T>
//
//      The unary_operator class implements most of the C++ unary
//      operators. Each specialization is basically a simple static eval
//      function plus a result_type typedef that determines the return
//      type of the eval function.
//
//      TagT is one of the unary operator tags above and T is the data
//      type (argument) involved in the operation.
//
//      Only the behavior of C/C++ built-in types are taken into account
//      in the specializations provided below. For user-defined types,
//      these specializations may still be used provided that the
//      operator overloads of such types adhere to the standard behavior
//      of built-in types.
//
//      T1 separate special_ops.hpp file implements more stl savvy
//      specializations. Other more specialized unary_operator
//      implementations may be defined by the client for specific
//      unary operator tags/data types.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TagT, typename T>
struct unary_operator;

//////////////////////////////////
template <typename T>
struct unary_operator<negative_op, T> {

    typedef T const result_type;
    static result_type eval(T const& v)
    { return -v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<positive_op, T> {

    typedef T const result_type;
    static result_type eval(T const& v)
    { return +v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<logical_not_op, T> {

    typedef T const result_type;
    static result_type eval(T const& v)
    { return !v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<invert_op, T> {

    typedef T const result_type;
    static result_type eval(T const& v)
    { return ~v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<reference_op, T> {

    typedef T* result_type;
    static result_type eval(T& v)
    { return &v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<dereference_op, T*> {

    typedef T& result_type;
    static result_type eval(T* v)
    { return *v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<dereference_op, T* const> {

    typedef T& result_type;
    static result_type eval(T* const v)
    { return *v; }
};

//////////////////////////////////
template <>
struct unary_operator<dereference_op, nil_t> {

    //  G++ eager template instantiation
    //  somehow requires this.
    typedef nil_t result_type;
};

//////////////////////////////////
#ifndef BOOST_BORLANDC
template <>
struct unary_operator<dereference_op, nil_t const> {

    //  G++ eager template instantiation
    //  somehow requires this.
    typedef nil_t result_type;
};
#endif

//////////////////////////////////
template <typename T>
struct unary_operator<pre_incr_op, T> {

    typedef T& result_type;
    static result_type eval(T& v)
    { return ++v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<pre_decr_op, T> {

    typedef T& result_type;
    static result_type eval(T& v)
    { return --v; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<post_incr_op, T> {

    typedef T const result_type;
    static result_type eval(T& v)
    { T t(v); ++v; return t; }
};

//////////////////////////////////
template <typename T>
struct unary_operator<post_decr_op, T> {

    typedef T const result_type;
    static result_type eval(T& v)
    { T t(v); --v; return t; }
};

///////////////////////////////////////////////////////////////////////////////
//
//  rank<T>
//
//      rank<T> class has a static int constant 'value' that defines the
//      absolute rank of a type. rank<T> is used to choose the result
//      type of binary operators such as +. The type with the higher
//      rank wins and is used as the operator's return type. T1 generic
//      user defined type has a very high rank and always wins when
//      compared against a user defined type. If this is not desirable,
//      one can write a rank specialization for the type.
//
//      Take note that ranks 0..9999 are reserved for the framework.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct rank { static int const value = INT_MAX; };

template <> struct rank<void>               { static int const value = 0; };
template <> struct rank<bool>               { static int const value = 10; };

template <> struct rank<char>               { static int const value = 20; };
template <> struct rank<signed char>        { static int const value = 20; };
template <> struct rank<unsigned char>      { static int const value = 30; };
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
template <> struct rank<wchar_t>            { static int const value = 40; };
#endif // !defined(BOOST_NO_INTRINSIC_WCHAR_T)

template <> struct rank<short>              { static int const value = 50; };
template <> struct rank<unsigned short>     { static int const value = 60; };

template <> struct rank<int>                { static int const value = 70; };
template <> struct rank<unsigned int>       { static int const value = 80; };

template <> struct rank<long>               { static int const value = 90; };
template <> struct rank<unsigned long>      { static int const value = 100; };

#ifdef BOOST_HAS_LONG_LONG
template <> struct rank< ::boost::long_long_type>          { static int const value = 110; };
template <> struct rank< ::boost::ulong_long_type> { static int const value = 120; };
#endif

template <> struct rank<float>              { static int const value = 130; };
template <> struct rank<double>             { static int const value = 140; };
template <> struct rank<long double>        { static int const value = 150; };

template <typename T> struct rank<T*>
{ static int const value = 160; };

template <typename T> struct rank<T* const>
{ static int const value = 160; };

template <typename T, int N> struct rank<T[N]>
{ static int const value = 160; };

///////////////////////////////////////////////////////////////////////////////
//
//  higher_rank<T0, T1>
//
//      Chooses the type (T0 or T1) with the higher rank.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T0, typename T1>
struct higher_rank {
    typedef typename boost::mpl::if_c<
        rank<T0>::value < rank<T1>::value,
        T1, T0>::type type;
};

///////////////////////////////////////////////////////////////////////////////
//
//  binary_operator<TagT, T0, T1>
//
//      The binary_operator class implements most of the C++ binary
//      operators. Each specialization is basically a simple static eval
//      function plus a result_type typedef that determines the return
//      type of the eval function.
//
//      TagT is one of the binary operator tags above T0 and T1 are the
//      (arguments') data types involved in the operation.
//
//      Only the behavior of C/C++ built-in types are taken into account
//      in the specializations provided below. For user-defined types,
//      these specializations may still be used provided that the
//      operator overloads of such types adhere to the standard behavior
//      of built-in types.
//
//      T1 separate special_ops.hpp file implements more stl savvy
//      specializations. Other more specialized unary_operator
//      implementations may be defined by the client for specific
//      unary operator tags/data types.
//
//      All binary_operator except the logical_and_op and logical_or_op
//      have an eval static function that carries out the actual operation.
//      The logical_and_op and logical_or_op d are special because these
//      two operators are short-circuit evaluated.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TagT, typename T0, typename T1>
struct binary_operator;

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs = rhs; }
};

//////////////////////////////////
template <typename T1>
struct binary_operator<index_op, nil_t, T1> {

    //  G++ eager template instantiation
    //  somehow requires this.
    typedef nil_t result_type;
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<index_op, T0*, T1> {

    typedef T0& result_type;
    static result_type eval(T0* ptr, T1 const& index)
    { return ptr[index]; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<index_op, T0* const, T1> {

    typedef T0& result_type;
    static result_type eval(T0* const ptr, T1 const& index)
    { return ptr[index]; }
};

//////////////////////////////////
template <typename T0, int N, typename T1>
struct binary_operator<index_op, T0[N], T1> {

    typedef T0& result_type;
    static result_type eval(T0* ptr, T1 const& index)
    { return ptr[index]; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<plus_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs += rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<minus_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs -= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<times_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs *= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<divide_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs /= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<mod_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs %= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<and_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs &= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<or_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs |= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<xor_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs ^= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<shift_l_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs <<= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<shift_r_assign_op, T0, T1> {

    typedef T0& result_type;
    static result_type eval(T0& lhs, T1 const& rhs)
    { return lhs >>= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<plus_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs + rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<minus_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs - rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<times_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs * rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<divide_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs / rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<mod_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs % rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<and_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs & rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<or_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs | rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<xor_op, T0, T1> {

    typedef typename higher_rank<T0, T1>::type const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs ^ rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<shift_l_op, T0, T1> {

    typedef T0 const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs << rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<shift_r_op, T0, T1> {

    typedef T0 const result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs >> rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<eq_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs == rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<not_eq_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs != rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<lt_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs < rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<lt_eq_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs <= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<gt_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs > rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<gt_eq_op, T0, T1> {

    typedef bool result_type;
    static result_type eval(T0 const& lhs, T1 const& rhs)
    { return lhs >= rhs; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<logical_and_op, T0, T1> {

    typedef bool result_type;
    //  no eval function, see comment above.
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<logical_or_op, T0, T1> {

    typedef bool result_type;
    //  no eval function, see comment above.
};

///////////////////////////////////////////////////////////////////////////////
//
//  negative lazy operator (prefix -)
//
///////////////////////////////////////////////////////////////////////////////
struct negative_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<negative_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<negative_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<negative_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<negative_op, BaseT>::type
operator-(actor<BaseT> const& _0)
{
    return impl::make_unary<negative_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  positive lazy operator (prefix +)
//
///////////////////////////////////////////////////////////////////////////////
struct positive_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<positive_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<positive_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<positive_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<positive_op, BaseT>::type
operator+(actor<BaseT> const& _0)
{
    return impl::make_unary<positive_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  logical not lazy operator (prefix !)
//
///////////////////////////////////////////////////////////////////////////////
struct logical_not_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<logical_not_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<logical_not_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<logical_not_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<logical_not_op, BaseT>::type
operator!(actor<BaseT> const& _0)
{
    return impl::make_unary<logical_not_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  invert lazy operator (prefix ~)
//
///////////////////////////////////////////////////////////////////////////////
struct invert_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<invert_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<invert_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<invert_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<invert_op, BaseT>::type
operator~(actor<BaseT> const& _0)
{
    return impl::make_unary<invert_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  reference lazy operator (prefix &)
//
///////////////////////////////////////////////////////////////////////////////
struct reference_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<reference_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<reference_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<reference_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<reference_op, BaseT>::type
operator&(actor<BaseT> const& _0)
{
    return impl::make_unary<reference_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  dereference lazy operator (prefix *)
//
///////////////////////////////////////////////////////////////////////////////
struct dereference_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<dereference_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<dereference_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<dereference_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<dereference_op, BaseT>::type
operator*(actor<BaseT> const& _0)
{
    return impl::make_unary<dereference_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  pre increment lazy operator (prefix ++)
//
///////////////////////////////////////////////////////////////////////////////
struct pre_incr_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<pre_incr_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<pre_incr_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<pre_incr_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<pre_incr_op, BaseT>::type
operator++(actor<BaseT> const& _0)
{
    return impl::make_unary<pre_incr_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  pre decrement lazy operator (prefix --)
//
///////////////////////////////////////////////////////////////////////////////
struct pre_decr_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<pre_decr_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<pre_decr_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<pre_decr_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<pre_decr_op, BaseT>::type
operator--(actor<BaseT> const& _0)
{
    return impl::make_unary<pre_decr_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  post increment lazy operator (postfix ++)
//
///////////////////////////////////////////////////////////////////////////////
struct post_incr_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<post_incr_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<post_incr_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<post_incr_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<post_incr_op, BaseT>::type
operator++(actor<BaseT> const& _0, int)
{
    return impl::make_unary<post_incr_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  post decrement lazy operator (postfix --)
//
///////////////////////////////////////////////////////////////////////////////
struct post_decr_op {

    template <typename T0>
    struct result {

        typedef typename unary_operator<post_decr_op, T0>::result_type type;
    };

    template <typename T0>
    typename unary_operator<post_decr_op, T0>::result_type
    operator()(T0& _0) const
    { return unary_operator<post_decr_op, T0>::eval(_0); }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_unary<post_decr_op, BaseT>::type
operator--(actor<BaseT> const& _0, int)
{
    return impl::make_unary<post_decr_op, BaseT>::construct(_0);
}

///////////////////////////////////////////////////////////////////////////////
//
//  assignment lazy operator (infix =)
//  The acual lazy operator is a member of the actor class.
//
///////////////////////////////////////////////////////////////////////////////
struct assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT>
template <typename B>
inline typename impl::make_binary1<assign_op, BaseT, B>::type
actor<BaseT>::operator=(B const& _1) const
{
    return impl::make_binary1<assign_op, BaseT, B>::construct(*this, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  index lazy operator (array index [])
//  The acual lazy operator is a member of the actor class.
//
///////////////////////////////////////////////////////////////////////////////
struct index_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<index_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<index_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<index_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT>
template <typename B>
inline typename impl::make_binary1<index_op, BaseT, B>::type
actor<BaseT>::operator[](B const& _1) const
{
    return impl::make_binary1<index_op, BaseT, B>::construct(*this, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  plus assign lazy operator (infix +=)
//
///////////////////////////////////////////////////////////////////////////////
struct plus_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<plus_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<plus_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<plus_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<plus_assign_op, BaseT, T1>::type
operator+=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<plus_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  minus assign lazy operator (infix -=)
//
///////////////////////////////////////////////////////////////////////////////
struct minus_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<minus_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<minus_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<minus_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<minus_assign_op, BaseT, T1>::type
operator-=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<minus_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  times assign lazy operator (infix *=)
//
///////////////////////////////////////////////////////////////////////////////
struct times_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<times_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<times_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<times_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<times_assign_op, BaseT, T1>::type
operator*=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<times_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  divide assign lazy operator (infix /=)
//
///////////////////////////////////////////////////////////////////////////////
struct divide_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<divide_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<divide_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<divide_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<divide_assign_op, BaseT, T1>::type
operator/=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<divide_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  mod assign lazy operator (infix %=)
//
///////////////////////////////////////////////////////////////////////////////
struct mod_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<mod_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<mod_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<mod_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<mod_assign_op, BaseT, T1>::type
operator%=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<mod_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  and assign lazy operator (infix &=)
//
///////////////////////////////////////////////////////////////////////////////
struct and_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<and_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<and_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<and_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<and_assign_op, BaseT, T1>::type
operator&=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<and_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  or assign lazy operator (infix |=)
//
///////////////////////////////////////////////////////////////////////////////
struct or_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<or_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<or_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<or_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<or_assign_op, BaseT, T1>::type
operator|=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<or_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  xor assign lazy operator (infix ^=)
//
///////////////////////////////////////////////////////////////////////////////
struct xor_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<xor_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<xor_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<xor_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<xor_assign_op, BaseT, T1>::type
operator^=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<xor_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  shift left assign lazy operator (infix <<=)
//
///////////////////////////////////////////////////////////////////////////////
struct shift_l_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<shift_l_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<shift_l_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<shift_l_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<shift_l_assign_op, BaseT, T1>::type
operator<<=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<shift_l_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  shift right assign lazy operator (infix >>=)
//
///////////////////////////////////////////////////////////////////////////////
struct shift_r_assign_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<shift_r_assign_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<shift_r_assign_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<shift_r_assign_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<shift_r_assign_op, BaseT, T1>::type
operator>>=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<shift_r_assign_op, BaseT, T1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  plus lazy operator (infix +)
//
///////////////////////////////////////////////////////////////////////////////
struct plus_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<plus_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<plus_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<plus_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<plus_op, BaseT, T1>::type
operator+(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<plus_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<plus_op, T0, BaseT>::type
operator+(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<plus_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<plus_op, BaseT0, BaseT1>::type
operator+(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<plus_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  minus lazy operator (infix -)
//
///////////////////////////////////////////////////////////////////////////////
struct minus_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<minus_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<minus_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<minus_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<minus_op, BaseT, T1>::type
operator-(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<minus_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<minus_op, T0, BaseT>::type
operator-(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<minus_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<minus_op, BaseT0, BaseT1>::type
operator-(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<minus_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  times lazy operator (infix *)
//
///////////////////////////////////////////////////////////////////////////////
struct times_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<times_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<times_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<times_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<times_op, BaseT, T1>::type
operator*(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<times_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<times_op, T0, BaseT>::type
operator*(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<times_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<times_op, BaseT0, BaseT1>::type
operator*(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<times_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  divide lazy operator (infix /)
//
///////////////////////////////////////////////////////////////////////////////
struct divide_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<divide_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<divide_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<divide_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<divide_op, BaseT, T1>::type
operator/(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<divide_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<divide_op, T0, BaseT>::type
operator/(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<divide_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<divide_op, BaseT0, BaseT1>::type
operator/(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<divide_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  mod lazy operator (infix %)
//
///////////////////////////////////////////////////////////////////////////////
struct mod_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<mod_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<mod_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<mod_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<mod_op, BaseT, T1>::type
operator%(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<mod_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<mod_op, T0, BaseT>::type
operator%(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<mod_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<mod_op, BaseT0, BaseT1>::type
operator%(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<mod_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  and lazy operator (infix &)
//
///////////////////////////////////////////////////////////////////////////////
struct and_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<and_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<and_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<and_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<and_op, BaseT, T1>::type
operator&(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<and_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<and_op, T0, BaseT>::type
operator&(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<and_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<and_op, BaseT0, BaseT1>::type
operator&(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<and_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  or lazy operator (infix |)
//
///////////////////////////////////////////////////////////////////////////////
struct or_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<or_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<or_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<or_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<or_op, BaseT, T1>::type
operator|(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<or_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<or_op, T0, BaseT>::type
operator|(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<or_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<or_op, BaseT0, BaseT1>::type
operator|(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<or_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  xor lazy operator (infix ^)
//
///////////////////////////////////////////////////////////////////////////////
struct xor_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<xor_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<xor_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<xor_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<xor_op, BaseT, T1>::type
operator^(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<xor_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<xor_op, T0, BaseT>::type
operator^(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<xor_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<xor_op, BaseT0, BaseT1>::type
operator^(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<xor_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  shift left lazy operator (infix <<)
//
///////////////////////////////////////////////////////////////////////////////
struct shift_l_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<shift_l_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<shift_l_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<shift_l_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<shift_l_op, BaseT, T1>::type
operator<<(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<shift_l_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<shift_l_op, T0, BaseT>::type
operator<<(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<shift_l_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<shift_l_op, BaseT0, BaseT1>::type
operator<<(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<shift_l_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  shift right lazy operator (infix >>)
//
///////////////////////////////////////////////////////////////////////////////
struct shift_r_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<shift_r_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<shift_r_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<shift_r_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<shift_r_op, BaseT, T1>::type
operator>>(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<shift_r_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<shift_r_op, T0, BaseT>::type
operator>>(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<shift_r_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<shift_r_op, BaseT0, BaseT1>::type
operator>>(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<shift_r_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  equal lazy operator (infix ==)
//
///////////////////////////////////////////////////////////////////////////////
struct eq_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<eq_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<eq_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<eq_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<eq_op, BaseT, T1>::type
operator==(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<eq_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<eq_op, T0, BaseT>::type
operator==(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<eq_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<eq_op, BaseT0, BaseT1>::type
operator==(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<eq_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  not equal lazy operator (infix !=)
//
///////////////////////////////////////////////////////////////////////////////
struct not_eq_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<not_eq_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<not_eq_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<not_eq_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<not_eq_op, BaseT, T1>::type
operator!=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<not_eq_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<not_eq_op, T0, BaseT>::type
operator!=(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<not_eq_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<not_eq_op, BaseT0, BaseT1>::type
operator!=(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<not_eq_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  less than lazy operator (infix <)
//
///////////////////////////////////////////////////////////////////////////////
struct lt_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<lt_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<lt_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<lt_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<lt_op, BaseT, T1>::type
operator<(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<lt_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<lt_op, T0, BaseT>::type
operator<(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<lt_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<lt_op, BaseT0, BaseT1>::type
operator<(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<lt_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  less than equal lazy operator (infix <=)
//
///////////////////////////////////////////////////////////////////////////////
struct lt_eq_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<lt_eq_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<lt_eq_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<lt_eq_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<lt_eq_op, BaseT, T1>::type
operator<=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<lt_eq_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<lt_eq_op, T0, BaseT>::type
operator<=(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<lt_eq_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<lt_eq_op, BaseT0, BaseT1>::type
operator<=(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<lt_eq_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  greater than lazy operator (infix >)
//
///////////////////////////////////////////////////////////////////////////////
struct gt_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<gt_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<gt_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<gt_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<gt_op, BaseT, T1>::type
operator>(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<gt_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<gt_op, T0, BaseT>::type
operator>(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<gt_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<gt_op, BaseT0, BaseT1>::type
operator>(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<gt_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  greater than equal lazy operator (infix >=)
//
///////////////////////////////////////////////////////////////////////////////
struct gt_eq_op {

    template <typename T0, typename T1>
    struct result {

        typedef typename binary_operator<gt_eq_op, T0, T1>
            ::result_type type;
    };

    template <typename T0, typename T1>
    typename binary_operator<gt_eq_op, T0, T1>::result_type
    operator()(T0& _0, T1& _1) const
    { return binary_operator<gt_eq_op, T0, T1>::eval(_0, _1); }
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline typename impl::make_binary1<gt_eq_op, BaseT, T1>::type
operator>=(actor<BaseT> const& _0, T1 CREF _1)
{
    return impl::make_binary1<gt_eq_op, BaseT, T1>::construct(_0, _1);
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline typename impl::make_binary2<gt_eq_op, T0, BaseT>::type
operator>=(T0 CREF _0, actor<BaseT> const& _1)
{
    return impl::make_binary2<gt_eq_op, T0, BaseT>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline typename impl::make_binary3<gt_eq_op, BaseT0, BaseT1>::type
operator>=(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return impl::make_binary3<gt_eq_op, BaseT0, BaseT1>::construct(_0, _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  logical and lazy operator (infix &&)
//
//  The logical_and_composite class and its corresponding generators are
//  provided to allow short-circuit evaluation of the operator's
//  operands.
//
///////////////////////////////////////////////////////////////////////////////
template <typename A0, typename A1>
struct logical_and_composite {

    typedef logical_and_composite<A0, A1> self_t;

    template <typename TupleT>
    struct result {

        typedef typename binary_operator<logical_and_op,
            typename actor_result<A0, TupleT>::plain_type,
            typename actor_result<A1, TupleT>::plain_type
        >::result_type type;
    };

    logical_and_composite(A0 const& _0, A1 const& _1)
    :   a0(_0), a1(_1) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        return a0.eval(args) && a1.eval(args);
    }

    A0 a0; A1 a1; //  actors
};

#if !(defined(__ICL) && __ICL <= 500)
//////////////////////////////////
template <typename BaseT, typename T1>
inline actor<logical_and_composite
<actor<BaseT>, typename as_actor<T1>::type> >
operator&&(actor<BaseT> const& _0, T1 CREF _1)
{
    return logical_and_composite
        <actor<BaseT>, typename as_actor<T1>::type>
        (_0, as_actor<T1>::convert(_1));
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline actor<logical_and_composite
<typename as_actor<T0>::type, actor<BaseT> > >
operator&&(T0 CREF _0, actor<BaseT> const& _1)
{
    return logical_and_composite
        <typename as_actor<T0>::type, actor<BaseT> >
        (as_actor<T0>::convert(_0), _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline actor<logical_and_composite
<actor<BaseT0>, actor<BaseT1> > >
operator&&(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return logical_and_composite
        <actor<BaseT0>, actor<BaseT1> >
        (_0, _1);
}
#else
//////////////////////////////////
template <typename T0, typename T1>
inline actor<logical_and_composite
<typename as_actor<T0>::type, typename as_actor<T1>::type> >
operator&&(T0 CREF _0, T1 CREF _1)
{
    return logical_and_composite
        <typename as_actor<T0>::type, typename as_actor<T1>::type>
        (as_actor<T0>::convert(_0), as_actor<T1>::convert(_1));
}
#endif // !(__ICL && __ICL <= 500)

///////////////////////////////////////////////////////////////////////////////
//
//  logical or lazy operator (infix ||)
//
//  The logical_or_composite class and its corresponding generators are
//  provided to allow short-circuit evaluation of the operator's
//  operands.
//
///////////////////////////////////////////////////////////////////////////////
template <typename A0, typename A1>
struct logical_or_composite {

    typedef logical_or_composite<A0, A1> self_t;

    template <typename TupleT>
    struct result {

        typedef typename binary_operator<logical_or_op,
            typename actor_result<A0, TupleT>::plain_type,
            typename actor_result<A1, TupleT>::plain_type
        >::result_type type;
    };

    logical_or_composite(A0 const& _0, A1 const& _1)
    :   a0(_0), a1(_1) {}

    template <typename TupleT>
    typename actor_result<self_t, TupleT>::type
    eval(TupleT const& args) const
    {
        return a0.eval(args) || a1.eval(args);
    }

    A0 a0; A1 a1; //  actors
};

//////////////////////////////////
template <typename BaseT, typename T1>
inline actor<logical_or_composite
<actor<BaseT>, typename as_actor<T1>::type> >
operator||(actor<BaseT> const& _0, T1 CREF _1)
{
    return logical_or_composite
        <actor<BaseT>, typename as_actor<T1>::type>
        (_0, as_actor<T1>::convert(_1));
}

//////////////////////////////////
template <typename T0, typename BaseT>
inline actor<logical_or_composite
<typename as_actor<T0>::type, actor<BaseT> > >
operator||(T0 CREF _0, actor<BaseT> const& _1)
{
    return logical_or_composite
        <typename as_actor<T0>::type, actor<BaseT> >
        (as_actor<T0>::convert(_0), _1);
}

//////////////////////////////////
template <typename BaseT0, typename BaseT1>
inline actor<logical_or_composite
<actor<BaseT0>, actor<BaseT1> > >
operator||(actor<BaseT0> const& _0, actor<BaseT1> const& _1)
{
    return logical_or_composite
        <actor<BaseT0>, actor<BaseT1> >
        (_0, _1);
}

}   //  namespace phoenix

#undef CREF
#endif

/* operators.hpp
502Qzgh3Het8grZmJBbpTBaRDNDUvlIs+NEEByroJ0XpC1r+SglW+6gL1VNqKmay1u56JUuFfNlaW6Od0tIgV76nH9ef6UWNusje5+BSRc26qN+rZg7eicdyPyTIj0W8KGLVBSekQT9FgX1TO/mdOnC6xQnnXt7K4OXbpMT9+kQL0pH0JGPIQnKInCaXyGPi5z0XLQfunYgrvCAFek8OFyHZXadpZBmMPwU1EycnR69PUbbD40uoI0BZx9W8rAZ7Dx2YVCNaF209cpUEsu+PvrgMb4swZhnbjHQmNWuZI+Haqb0T3StgnofCvW7CZeuDeFYKw2qBKutpjQE13rRygxingmxdqs3ozWEBskq6JZWkG+gjmkPuDP6aiatJo1RQRkNtniqN1C/V6+jMIFYYBN0ZqXMdO8sCtMracG011MDduzlXvwESK290MCYYa40AHizh08tGVrO02Rk+ewxZ3UE29wkLqj1XZLAaIHW7a9Ij7GPImUUwi5+6dR6QcC0OKnwlqLEQ9LGzNE26IhFo8Xx6lgYgAR+TbaWxEoWrKqzOUvertz2yWoJOC9DKaDO0LdrXWl69m/6RvltPaZhGA1xLUrMykt9c1GsiLvFm/AN4+0WeR1QWfcQScQGp00G9HbTy2NXtaXZLzyszehnTPYtzA7kNrX4btbUd6SQTLUl7wJ8PgPYKyRXl4cjkX8h+SgEwWg8lSC2lRkIt9quP1GKsDrziEEurca0FSPWUllSvqPeGnz72vh+5wCgJRVhlXjCr8iwij6giZorrIsTqjfzRyh4DguBwpKHOCvcdDZIwN8FkMFkKri6L/DRL2iZdhYZXpVNRR/5ycbmXfFkOUhoqs9DnOdW6UK6Tamk2GteQXCuq1UVC36Dd1vLrNfWF+hd6KuMdIwWIqAv6+oj5Fh/OF/NnvBgqZqzYIx4KGS42AwSRBB621D4Dj63gDHKf14Rm9NYpA0k58h44bJ83P1W8e3UYdE+QwqeDXx6DhsuBW2LkF7hnbZQ9yk2liRqnurtVW7EV7Akrpr2tTdeua/56cb2dPl3fDG1OZ1QyehpTjaPIQprZ3ZwFAi3Pe/NpfBOuzoRWLBdHRSKrmNUKenkAKbUhqsjdD1kbrOELz+itt/sIJw3JSLIWtCWBNkZIn0iFaEVkjYVIh4rcXP5U/krOqZRT3lVM9R11ElQ9hEWyRewFy6s1RrLYpF3RsmCmBunL9S/1xMZQIzvquSUq+kNkslzosvaoo1X8TVFbRIu9YoI1zl5vn7eTQBfectohQbjfutzq3ANTJFyTTEpJLdD/O6VHUmFU9ETkhgyyKreQP8TVnJVTKDIoPwbck00to/ZQp6jb1eRMB9PPZ8dwVaW1cdpn2jktvS70HvoePYfR3BgGrr0IrZ6JLkuGa2rOx/MN/AI0q5HYKYKsylYveMph5MQa9kD7kp3Hqez0c/dudMz43TtylDQiA8nH5DzJKDGpi/SRdFJKRkuDCY7QfHJt5LDPkWgqg8pcf3bnagrI85b3jKo/m80OsKesEGorUluuHdUS6wRk1A/qtF2/pqc2ihl1jChjF9JlQWhUJbOPOR15thgfCV39nO9HDviGf8vTgtOChOalgQjRGioxXIwXU8UK7zsCp72vWPpZBaC/86w9Vlu4/jBnkXPA3QcQmdFbly1DxpNNUNo8UiWpn7QISfOJVIy2oz7Mb205CtngmpwW81tTiVW+VN5Um6rvQT2OgusikJc+YldYSnRIL227dg3VaOkR+nh9k/5Ql4323r7pJEjlJcx3kJD2mbfMYOSDZfwcTyeCRbhoDne4KHJbFa3hqMenlmk3sEeCLC/YaeFUU9Ax0LaxGT3myk2qk+FkF3lAJGmKtAN6khMZ+D36DQ2SS8ld5bnyTlnyvo23W5mgblI1do9t1J5pb+nv6w9AQsJoBJpY5n1bRTVrYz7nm+egagp/F/M5SIRa7aAeh6wK4Fv3FLhqSLQx7h7zmRm99wKyklpQkE/JPZLFc6OpqMbk1K3G7sjgO2hpZI0J8l45NZR/HCgzlWqqnXHHC7Mt7A34z2Otov4ViHeFUcY8BM+vyqfw7GKduCMKg2NmW6nst2zfMvzWJD5feTIPpLsa9+UQOY76ukuekSRScimPlF8iUgmpjBQuNZa6SwOkUdI4abq0UFotbcH17JOOed8i+FZKStNR92Q6mTq0PByzHo3w1mA7QYEH0TGo0Xkg9FV0HXxrGz1OLyCZuPT3kD6naeWscrBcCN7qIFlUluvKjZCi3Aw1WB6L3+ieGLMMpPa5fFA+I19FCnomJ1FSKGmVjGCmQt7XF8OU8ko1pZHSTGmv9Eb+Hq5MgDu7X6r+RNkIPTukHFfOKFeVeOWBklhNrqZXc6r51IJqMe/LtA5S+ltquFpTrac2Rt+0xUy6bxAOUoero9UozOoMOPwidZm6Wo1VN4Mq96mHQSlx6K7HajIWwHKA0CgTrByrCk5zz2Xtx0awKDYTDLMad2Q/O8Xi2C2WSEutZdFyanm1gqhiTSulldOqag21puC5Xlo/bZgWBZ1dqK2Cqu3WjmvntXjvvUl/PaueVy/mnZ3xlu5+pT5Cb6v31N/Vh6L+p+kLQPfrwPfbwfen9fO48w+ghMmN9EZOo6AhG7YRDmZqYXQyuhuRSKAfQLfneXv9thg7jEPGWWhTvPHQeGYkNzOCJ/OaxUzZtMzy8OPa4MpW3okMg83RyAvzzOXmenMn2PiIeRI1fQ1M+chMwtN5q+nu9yIkznlZXolX5bXh4R3Qg/1AkWP4ZD6XL4QSb+K7QZSnoSm3oSlPeWKRQqQR7lcdc6FPCwv3KQoXoSDOCqKGaCxaiI6irxgqxnlPUj4GJa318uwucUAcE6fEeXFF3BC3xbfiKVJdCsv9Ck0+72lRCfR6VasWOMZ92tvTGgSeGWdNt2KsBdZSa5W1AVn4tHXZum09sHy2v53VzmkXsGU7zK4M8mpud7T7gGbfs0d5X1ScZs+x59tL7FX2p96K6m5k0mP2l/YN+4GdyEnmBDg5nAKO7NhOKacSmLOh09Lp6vR3hjsTnJnwmLVwmYOg0CvOjYR1v00ZfdUTu+t+yUgAyUEKkBDCSElSmdQFmbYlnUgP76TPD8g0JInF8MitZL+3NnGd3CQPwaoppYxSbilYKiaZUgWpBrq0ndRLGiKNgV7M9Pp0M7r0sHRGuibdlZ5LKWkgzQ0VYVR4a9cVaU3aBOrbGYzblw7wTpacCeddTTfRQ/QkvUpv02fw4UxyHiQWA8pXRW4sd5IHyB/Im9GJD+QncjIlFdJLJiWHEqTkV4jCkYPDlMrerq62SnclUhmpjEG6m6LMVBYpnyo7lGPekzb3BO8s6puqrJZQq6gN1DboOffp0ofqTGSAVd5u9cPqGfWqegN99kR9ofqxdCwjy8ryMYk5rBKrBzrpwYawcaC3j9gykO42dNoJdoldZfHsW3CLD/2WXQtBp5XWqmm1tPraO1o3bRAYb4b2MTx6l/aFdlm7673ZlE3PiR4rqnNvh3g9vYneEf01TP/Q+5L4Jn2/fhgsdtH77o6/d3Z7EFxTgA9ro7O6GgPQV1OM+eiq5Uassds4gWx2Fx2VwvQ305s5zSLoplpmc/RSezDue+YH5gR001xktM3mAW/t2P1mfADPzt/khXgxbqCHavAmvJ23SjCez+SL+FL+CYh4Fz/gffvoOr/Ln6N7UqJ7AuHMuURB4TuY0edDTbnP/sbC0ScZ0cZMI8a7rmXGKjB2rLEJSWSnsdc4CHY7YZwxzhtxxjX0/y24/0PjqeEz/Uz3qgPMQGhBDjPou6eHBDlTN4UZirRZzqxohiNz1jbrmxFQiJZmWzByV7On2deMhFIMM0eZY80oc5IZDeaJgfst/pfnjgfNo+YJJNPzZhxUJB5+7T6fe4p86uc9oQvggcioL59NhiCnKlxHUg3lYciqFXk40mptXh95tdl3zxa7IrP25ZFIrcP4KOTWKCT3aMxcDJ8PZl4G7VkLntnEt/GdfC8/yI/yE/wMP/8vTyP9oEj+IsCb1RwgnmDMbIggQhG6EFCmMFFOVPzHE8sIJOOWoi1UqqvoCaWKREYeJkaBzqPEJDDnTBEj5ovFYplYBeWKFZugXTtBogfBxyfEGehXnLiG3Hrru2eePssPKuZvBViBVlYrhxVkBVsFrRCLQNN0S1ihVphVDspW26pvRVjNrJbQto5WXyvSeycAzJ/U5ysohcC7FUmXhBQqhYEhKkodkUV6Ih1FSoOlYfDysVKUNEmKhlLESPOlxdIyaZW0Fql3E/LKTmmvdFA6Kp2AdpyX4qAf8cid95DZn0o+6kdTUH8aADXJSnPQIBpMC9IQSqhCdShLKA0DK1Wk4bQ6rU3rgwWa0ZaggY60q6czkXQwHUZH0bFQm0lgg5k0BqlxMV0GQlhLY6E92+hOupceBHefoGfoeRoHXointzxi8Ml+cgrZXw6QA0EOOeQg0ENBOUQmSAu6LORQUEQ55L1wuTqIsr4cITeTW8pt5Y6gtp7Iy5HgimHyKLBFlDxJjkZ+jpHny4vBGKvktXIs0v02sN1e0MZR+QSI4zzy9TU5Xr4l35Mfyk9ln+IH+vBXApRAJaunesFKQSUEyqeARIQSCvUrp1RUwpEzayv1lQhQSUsoYUelq9JT6Qs9HKwMU0YpY5GNJynRUMUYZb6yGKyySlkL6j0KSvFTBQtlYcw9Sas6q83qg36bgSvaso5gi56sLxLQYDaMjWJjQRmToH8zWQzSx2Ko4Cq2lsWyTdDCnWwvO8iOQhHPsPPgj2tQxVvg1IdIAj7NT0uh+WsBWqCWVcuhBWnBYJIQjWiKpmtCC9XCwCYVtXCtulYbuhmhNdNaam21jlpXrafWFyliMGhllDYWxDJJi9ZmajHafG2xtgzsslaLBb9s03Zqe7WDyBontDMgmTgQe7x2S7unPdSeaj7dT08BrgnQA8E2OfQgPVgvqIcglSigHKGHgnTKIYWH69X12np98E4zvSWYp6PeFdzTV4/UB0ObR+lj9ajvdkLE6PP1xfoykNBaPRZ6vU3fqe/VD+pH9RP6GTBRHHJOPNT7HtLCU91n+BkpDFfHf7h3QjF0qHqoEWaUMyqCm6pD3+sbEUYzo6XR1ugIpe9p9PX2V/xQQ+95yvl6KqarhPe4P5ROQNXaQsGioVZ7oUxPhatBihVuVYfO/PMujJngqPnWYmsZSGqtFWttsrZZO6291kHrqHXCOmOdt+Ksa//YqfEUhOVnpwBlBdiBIK0cdpAdbBe0Q2xiK7ZuCzsU3FXOrmiH29Xt2nZ9O8Ju9i+nrwwDi421/9udEoFOVrBakFPQCXGIozi6I5xQJ8wp51R0wp3qTm2nvhPhNAO/tXU6guF6On2dSGcw0uwoZ6wT5UxyokF0Mc58UN0yZxXILtbZ5Gxzdjp7QXhHnRPOGee8E+dcc+KdW8495N+n3tpjRt/eJO6ahx9JQfzBfIEkK7gviASTgmA/QhSiE0FCSRgpRyqScGTQ2qQ+iSDNSEvwYEfSlfQkfUkkkuEwMoqMJVFkEokmM0kMmQ8+XEZWgRFjkeO2kRPkGrLjQ/KU+JDeqku1pfpShNRMaim1/Qkf+DUu8J/U/z8pe4KiP/1O0101/75inlCuKfeghgFqkBqiCrWcWlttprZEQuuodgUv9lUj1cHqMFDjWOS0SWo02DFGna8uRlZbpa5FWtukbgNH7lUPgiTPI7FdU+NBk/fUh+pTtSDTPY2t+A+VTVDTBN2Mg1KmgDoGf08R3Tcf/xoa6KpfMJSuOlRtMChxFdQMHOipiqsov4ZIXI34PpV0Rerq+y/7t14n5XipGN/XCp8v0Fc/sbtX+cf69Od26U6ylxwkR9GtZ8h5EoeejSe30LMppECv0/zRWwJ91NZ7t3cVOicO3RII2gkD2XQFxcSAWI6CTvxAIgqooxkIwyWLxco25Qx65wQqPoAFIjXlYEEsmBVkIYwwBZX/kjD+v/r7gie+zxLxIAWXEoJR/9W1V+NEP4fdFdTb71FrbnW59eTW0MvaeQjfSHCMgq/KJwICfSLpq/CJHFKQFCz9WFb4vmf8NZLDS5/5YXaoj3TgJoMopACf5zXBakH4DVEVVYfrhKphcJ6KarhaHf5TX434ngf5WAC6ZS14+ygo2yXsp973QQrCN8LAzy47t4VbDINHxHgrewfhBfFwgBT/Vvf/O9X/77j331Hvf15Z+G3WFbp6VPxTRPzU9Ie+FISqhEFLIqAgfaEbk17rPO8q2m+hYn+UY/44Ywe/WsoOCvSd8ful2vnzFfOnPPsla/tJKSR/KQD+nVX6uer6U0T+7/WVQC0rQiNbQhkHe+u2rg7GQv1ex1WRH66CbAK/7FT2KgeVo0gBZ5TzShyyQLxyC0zzUHmq+FQ/NYXqD7UOVLOqOX6hZv+S3HBUPfEj2cH3b0nqz7ta83pkk5/rU/9+feY/O9WrWAN3OfmW6RJxwX9ZfR4MR3npJi+9IxSa3BfK+33V3Qad9ZFAXzlkDlePFkMNXg1pvVSP6lCMl/rwYxn3X6vop2vonyvo/+vHrZ7/rx23cl7WTULVfL9mfm7FvKyVlzXifpn6j6uG33d9z6Wf76/ivfTJ73lkaKDvxC/2yF+TL16NW7pOuQq9EIe6D0SNh6Geu/7GGeH1cdL/9Hzhz++sfiwF82c/tmpREb7aFx66GH55xvtSaLDmKkl9uM4oKEUslMEP/f/6ukWCPrh9748ed9+cbMsH82geKNzd2aFIKfX/sGzyW6+2/NY5xRce6NuUxOf7M2vVzyH7f+/nrodXhFv3hb4thpadgW75Q6ME9KgttCcaOrMXmvJUDoRqhEEhukINYv7xZDEH+rgierYv+nMxerE6eurPx6n/zYr6v65sn0en/tY9+nt5+PdWRn/wJC4QnRmGLuyKjluLvvq9O+rnJv9//5Tt564A+CICfSm+45IcYJA/O3f8nF7e+Y81+9eZGVwuCAQDhMHvu8LbY+DjR+HZfvDnv55+/H9icdNECNihPjhhFJhgr+f+v6fzvxJV+afnLS4H+MPzhfd0fzAcfBXcOg46EgjNCIM+uOcexKDv3X5/2d8FvV4O83r4N1/B8/k6Bvqe/qH55FWrxO+b4P/7HOQq02Jo0BnojT+0RUBH2kIzoqEPe5EffqgOLue7bH9P9Qe9C2hE2++ejfzZOvyPXNf6Z2WJRbKIN/ygIK5yuIrhKkWUpwevSgt+3rPXP3bf5Jkf1SuXgVz2cZkn1GObV08vv5H6RQb6Il6J9p0BDflD0wT0yz1f7cfWUEZBM2KhD/HUT84hKyCYZt89J3WJxCURl0Bc8gjyVKGZRxT/iSZe5xWIn7Pa/4P1CShZW6hWNBRqL9ToqRYIvQn73ppFvO5n5PBWK9xVCnd1wl2VcFcjFhvb/ok0fool/mpd/r+yYvH7K5SrToOhQ6ugOd476mMDfbWTuO+EhkBB6kMtRkEZYkFA8cQPlKOAaJqBXqJAKttAJfd+Yg+SSwUFvX1ICXvo/tNzr/81b/8zPbNye/6fO/1lb//d2f+5s90ubouOjUZ37kUnuudEhaDD6sPvR8HbY+Hj8d4ZToE+JYn7HSp35aIi3LgvnHcxEsYP
*/