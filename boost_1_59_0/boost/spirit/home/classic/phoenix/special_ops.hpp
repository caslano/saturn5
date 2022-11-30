/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_SPECIAL_OPS_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_SPECIAL_OPS_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#define PHOENIX_SSTREAM strstream
#else
#include <sstream>
#define PHOENIX_SSTREAM stringstream
#endif

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/operators.hpp>
#include <iosfwd>
#include <complex>

///////////////////////////////////////////////////////////////////////////////
#if defined(_STLPORT_VERSION) && defined(__STL_USE_OWN_NAMESPACE)
#define PHOENIX_STD _STLP_STD
#define PHOENIX_NO_STD_NAMESPACE
#else
#define PHOENIX_STD std
#endif

///////////////////////////////////////////////////////////////////////////////
namespace phoenix
{

///////////////////////////////////////////////////////////////////////////////
//
//  The following specializations take into account the C++ standard
//  library components. There are a couple of issues that have to be
//  dealt with to enable lazy operator overloads for the standard
//  library classes.
//
//      *iostream (e.g. cout, cin, strstream/ stringstream) uses non-
//      canonical shift operator overloads where the lhs is taken in
//      by reference.
//
//      *I/O manipulators overloads for the RHS of the << and >>
//      operators.
//
//      *STL iterators can be objects that conform to pointer semantics.
//      Some operators need to be specialized for these.
//
//      *std::complex is given a rank (see rank class in operators.hpp)
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  specialization for rank<std::complex>
//
///////////////////////////////////////////////////////////////////////////////
template <typename T> struct rank<PHOENIX_STD::complex<T> >
{ static int const value = 170 + rank<T>::value; };

///////////////////////////////////////////////////////////////////////////////
//
//  specializations for std::istream
//
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////
template <typename T1>
struct binary_operator<shift_r_op, PHOENIX_STD::istream, T1>
{
    typedef PHOENIX_STD::istream& result_type;
    static result_type eval(PHOENIX_STD::istream& out, T1& rhs)
    { return out >> rhs; }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary3
    <shift_r_op, variable<PHOENIX_STD::istream>, BaseT>::type
operator>>(PHOENIX_STD::istream& _0, actor<BaseT> const& _1)
{
    return impl::make_binary3
    <shift_r_op, variable<PHOENIX_STD::istream>, BaseT>
    ::construct(var(_0), _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  specializations for std::ostream
//
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////
template <typename T1>
struct binary_operator<shift_l_op, PHOENIX_STD::ostream, T1>
{
    typedef PHOENIX_STD::ostream& result_type;
    static result_type eval(PHOENIX_STD::ostream& out, T1 const& rhs)
    { return out << rhs; }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary3
    <shift_l_op, variable<PHOENIX_STD::ostream>, BaseT>::type
operator<<(PHOENIX_STD::ostream& _0, actor<BaseT> const& _1)
{
    return impl::make_binary3
    <shift_l_op, variable<PHOENIX_STD::ostream>, BaseT>
    ::construct(var(_0), _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//  specializations for std::strstream / stringstream
//
///////////////////////////////////////////////////////////////////////////////
template <typename T1>
struct binary_operator<shift_r_op, PHOENIX_STD::PHOENIX_SSTREAM, T1>
{
    typedef PHOENIX_STD::istream& result_type;
    static result_type eval(PHOENIX_STD::istream& out, T1& rhs)
    { return out >> rhs; }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary3
    <shift_r_op, variable<PHOENIX_STD::PHOENIX_SSTREAM>, BaseT>::type
operator>>(PHOENIX_STD::PHOENIX_SSTREAM& _0, actor<BaseT> const& _1)
{
    return impl::make_binary3
    <shift_r_op, variable<PHOENIX_STD::PHOENIX_SSTREAM>, BaseT>
    ::construct(var(_0), _1);
}

//////////////////////////////////
template <typename T1>
struct binary_operator<shift_l_op, PHOENIX_STD::PHOENIX_SSTREAM, T1>
{
    typedef PHOENIX_STD::ostream& result_type;
    static result_type eval(PHOENIX_STD::ostream& out, T1 const& rhs)
    { return out << rhs; }
};

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary3
    <shift_l_op, variable<PHOENIX_STD::PHOENIX_SSTREAM>, BaseT>::type
operator<<(PHOENIX_STD::PHOENIX_SSTREAM& _0, actor<BaseT> const& _1)
{
    return impl::make_binary3
    <shift_l_op, variable<PHOENIX_STD::PHOENIX_SSTREAM>, BaseT>
    ::construct(var(_0), _1);
}

///////////////////////////////////////////////////////////////////////////////
//
//      I/O manipulator specializations
//
///////////////////////////////////////////////////////////////////////////////

typedef PHOENIX_STD::ios_base&  (*iomanip_t)(PHOENIX_STD::ios_base&);
typedef PHOENIX_STD::istream&   (*imanip_t)(PHOENIX_STD::istream&);
typedef PHOENIX_STD::ostream&   (*omanip_t)(PHOENIX_STD::ostream&);

#if defined(BOOST_BORLANDC)

///////////////////////////////////////////////////////////////////////////////
//
//      Borland does not like i/o manipulators functions such as endl to
//      be the rhs of a lazy << operator (Borland incorrectly reports
//      ambiguity). To get around the problem, we provide function
//      pointer versions of the same name with a single trailing
//      underscore.
//
//      You can use the same trick for other i/o manipulators.
//      Alternatively, you can prefix the manipulator with a '&'
//      operator. Example:
//
//          cout << arg1 << &endl
//
///////////////////////////////////////////////////////////////////////////////

imanip_t    ws_     = &PHOENIX_STD::ws;
iomanip_t   dec_    = &PHOENIX_STD::dec;
iomanip_t   hex_    = &PHOENIX_STD::hex;
iomanip_t   oct_    = &PHOENIX_STD::oct;
omanip_t    endl_   = &PHOENIX_STD::endl;
omanip_t    ends_   = &PHOENIX_STD::ends;
omanip_t    flush_  = &PHOENIX_STD::flush;

#else // BOOST_BORLANDC

///////////////////////////////////////////////////////////////////////////////
//
//      The following are overloads for I/O manipulators.
//
///////////////////////////////////////////////////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary1<shift_l_op, BaseT, imanip_t>::type
operator>>(actor<BaseT> const& _0, imanip_t _1)
{
    return impl::make_binary1<shift_l_op, BaseT, imanip_t>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary1<shift_l_op, BaseT, iomanip_t>::type
operator>>(actor<BaseT> const& _0, iomanip_t _1)
{
    return impl::make_binary1<shift_l_op, BaseT, iomanip_t>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary1<shift_l_op, BaseT, omanip_t>::type
operator<<(actor<BaseT> const& _0, omanip_t _1)
{
    return impl::make_binary1<shift_l_op, BaseT, omanip_t>::construct(_0, _1);
}

//////////////////////////////////
template <typename BaseT>
inline typename impl::make_binary1<shift_l_op, BaseT, iomanip_t>::type
operator<<(actor<BaseT> const& _0, iomanip_t _1)
{
    return impl::make_binary1<shift_l_op, BaseT, iomanip_t>::construct(_0, _1);
}

#endif // BOOST_BORLANDC

///////////////////////////////////////////////////////////////////////////////
//
//  specializations for stl iterators and containers
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct unary_operator<dereference_op, T>
{
    typedef typename T::reference result_type;
    static result_type eval(T const& iter)
    { return *iter; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<index_op, T0, T1>
{
    typedef typename T0::reference result_type;
    static result_type eval(T0& container, T1 const& index)
    { return container[index]; }
};

//////////////////////////////////
template <typename T0, typename T1>
struct binary_operator<index_op, T0 const, T1>
{
    typedef typename T0::const_reference result_type;
    static result_type eval(T0 const& container, T1 const& index)
    { return container[index]; }
};

///////////////////////////////////////////////////////////////////////////////
}   //  namespace phoenix

#undef PHOENIX_SSTREAM
#undef PHOENIX_STD
#endif

/* special_ops.hpp
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
*/