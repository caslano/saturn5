///////////////////////////////////////////////////////////////////////////////
/// \file repeat.hpp
/// Contains macros to ease the generation of repetitious code constructs
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_REPEAT_HPP_EAN_11_24_2008
#define BOOST_PROTO_REPEAT_HPP_EAN_11_24_2008

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/proto/proto_fwd.hpp> // for BOOST_PROTO_MAX_ARITY

////////////////////////////////////////////
/// INTERNAL ONLY
#define BOOST_PROTO_ref_a_aux(Z, N, DATA)\
  boost::ref(BOOST_PP_CAT(proto_a, N))

/// \brief Generates a sequence like <tt>typename A0, typename A1, ...</tt>
///
#define BOOST_PROTO_typename_A(N)\
  BOOST_PP_ENUM_PARAMS(N, typename proto_A)

/// \brief Generates a sequence like <tt>A0 const &, A1 const &, ...</tt>
///
#define BOOST_PROTO_A_const_ref(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, const & BOOST_PP_INTERCEPT)

/// \brief Generates a sequence like <tt>A0 &, A1 &, ...</tt>
///
#define BOOST_PROTO_A_ref(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, & BOOST_PP_INTERCEPT)

/// \brief Generates a sequence like <tt>A0, A1, ...</tt>
///
#define BOOST_PROTO_A(N)\
  BOOST_PP_ENUM_PARAMS(N, proto_A)

/// \brief Generates a sequence like <tt>A0 const, A1 const, ...</tt>
///
#define BOOST_PROTO_A_const(N)\
  BOOST_PP_ENUM_PARAMS(N, const proto_A)

/// \brief Generates a sequence like <tt>A0 const &a0, A1 const &a0, ...</tt>
///
#define BOOST_PROTO_A_const_ref_a(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, const &proto_a)

/// \brief Generates a sequence like <tt>A0 &a0, A1 &a0, ...</tt>
///
#define BOOST_PROTO_A_ref_a(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, &proto_a)

/// \brief Generates a sequence like <tt>boost::ref(a0), boost::ref(a1), ...</tt>
///
#define BOOST_PROTO_ref_a(N)\
  BOOST_PP_ENUM(N, BOOST_PROTO_ref_a_aux, ~)

/// \brief Generates a sequence like <tt>a0, a1, ...</tt>
///
#define BOOST_PROTO_a(N)\
  BOOST_PP_ENUM_PARAMS(N, proto_a)

////////////////////////////////////////////
/// INTERNAL ONLY
#define BOOST_PROTO_invoke(Z, N, DATA)\
  BOOST_PP_TUPLE_ELEM(5,0,DATA)(N, BOOST_PP_TUPLE_ELEM(5,1,DATA), BOOST_PP_TUPLE_ELEM(5,2,DATA), BOOST_PP_TUPLE_ELEM(5,3,DATA), BOOST_PP_TUPLE_ELEM(5,4,DATA))

/// \brief Repeatedly invoke the specified macro.
///
/// BOOST_PROTO_REPEAT_FROM_TO_EX() is used generate the kind of repetitive code that is typical
/// of EDSLs built with Proto. BOOST_PROTO_REPEAT_FROM_TO_EX(FROM, TO, MACRO, typename_A, A, A_a, a)  is equivalent to:
///
/// \code
/// MACRO(FROM, typename_A, A, A_a, a)
/// MACRO(FROM+1, typename_A, A, A_a, a)
/// ...
/// MACRO(TO-1, typename_A, A, A_a, a)
/// \endcode
#define BOOST_PROTO_REPEAT_FROM_TO_EX(FROM, TO, MACRO, typename_A, A, A_a, a)\
  BOOST_PP_REPEAT_FROM_TO(FROM, TO, BOOST_PROTO_invoke, (MACRO, typename_A, A, A_a, a))

/// \brief Repeatedly invoke the specified macro.
///
/// BOOST_PROTO_REPEAT_FROM_TO() is used generate the kind of repetitive code that is typical
/// of EDSLs built with Proto. BOOST_PROTO_REPEAT_FROM_TO(FROM, TO, MACRO)  is equivalent to:
///
/// \code
/// MACRO(FROM, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// MACRO(FROM+1, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// ...
/// MACRO(TO-1, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// \endcode
///
/// Example:
///
/** \code

// Generate BOOST_PROTO_MAX_ARITY-1 overloads of the
// following construct() function template.
#define M0(N, typename_A, A_const_ref, A_const_ref_a, ref_a)      \
template<typename T, typename_A(N)>                               \
typename proto::result_of::make_expr<                             \
    proto::tag::function                                          \
  , construct_helper<T>                                           \
  , A_const_ref(N)                                                \
>::type const                                                     \
construct(A_const_ref_a(N))                                       \
{                                                                 \
    return proto::make_expr<                                      \
        proto::tag::function                                      \
    >(                                                            \
        construct_helper<T>()                                     \
      , ref_a(N)                                                  \
    );                                                            \
}
BOOST_PROTO_REPEAT_FROM_TO(1, BOOST_PROTO_MAX_ARITY, M0)
#undef M0

\endcode
**/
/// The above invocation of BOOST_PROTO_REPEAT_FROM_TO()  will generate
/// the following code:
///
/// \code
/// template<typename T, typename A0>
/// typename proto::result_of::make_expr<
///     proto::tag::function
///   , construct_helper<T>
///  , A0 const &
/// >::type const
/// construct(A0 const & a0)
/// {
///     return proto::make_expr<
///         proto::tag::function
///     >(
///         construct_helper<T>()
///       , boost::ref(a0)
///     );
/// }
///
/// template<typename T, typename A0, typename A1>
/// typename proto::result_of::make_expr<
///     proto::tag::function
///   , construct_helper<T>
///   , A0 const &
///   , A1 const &
/// >::type const
/// construct(A0 const & a0, A1 const & a1)
/// {
///     return proto::make_expr<
///         proto::tag::function
///     >(
///         construct_helper<T>()
///       , boost::ref(a0)
///       , boost::ref(a1)
///     );
/// }
///
/// // ... and so on, up to BOOST_PROTO_MAX_ARITY-1 arguments ...
/// \endcode
#define BOOST_PROTO_REPEAT_FROM_TO(FROM, TO, MACRO)\
  BOOST_PROTO_REPEAT_FROM_TO_EX(FROM, TO, MACRO, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)

/// \brief Repeatedly invoke the specified macro.
///
/// BOOST_PROTO_REPEAT_EX() is used generate the kind of repetitive code that is typical
/// of EDSLs built with Proto. BOOST_PROTO_REPEAT_EX(MACRO, typename_A, A, A_a, a)  is equivalent to:
///
/// \code
/// MACRO(1, typename_A, A, A_a, a)
/// MACRO(2, typename_A, A, A_a, a)
/// ...
/// MACRO(BOOST_PROTO_MAX_ARITY, typename_A, A, A_a, a)
/// \endcode
#define BOOST_PROTO_REPEAT_EX(MACRO, typename_A, A, A_a, a)\
  BOOST_PROTO_REPEAT_FROM_TO_EX(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), MACRO, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)

/// \brief Repeatedly invoke the specified macro.
///
/// BOOST_PROTO_REPEAT() is used generate the kind of repetitive code that is typical
/// of EDSLs built with Proto. BOOST_PROTO_REPEAT(MACRO)  is equivalent to:
///
/// \code
/// MACRO(1, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// MACRO(2, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// ...
/// MACRO(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)
/// \endcode
#define BOOST_PROTO_REPEAT(MACRO)\
  BOOST_PROTO_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), MACRO)

/// \brief Repeatedly invoke the specified macro.
///
/// BOOST_PROTO_LOCAL_ITERATE() is used generate the kind of repetitive code that is typical
/// of EDSLs built with Proto. This macro causes the user-defined macro BOOST_PROTO_LOCAL_MACRO to
/// be expanded with values in the range specified by BOOST_PROTO_LOCAL_LIMITS.
///
/// Usage:
///
/// \code
/// #include BOOST_PROTO_LOCAL_ITERATE()
/// \endcode
///
/// Example:
///
/** \code

// Generate BOOST_PROTO_MAX_ARITY-1 overloads of the
// following construct() function template.
#define BOOST_PROTO_LOCAL_MACRO(N, typename_A, A_const_ref,       \
  A_const_ref_a, ref_a)                                           \
template<typename T, typename_A(N)>                               \
typename proto::result_of::make_expr<                             \
    proto::tag::function                                          \
  , construct_helper<T>                                           \
  , A_const_ref(N)                                                \
>::type const                                                     \
construct(A_const_ref_a(N))                                       \
{                                                                 \
    return proto::make_expr<                                      \
        proto::tag::function                                      \
    >(                                                            \
        construct_helper<T>()                                     \
      , ref_a(N)                                                  \
    );                                                            \
}
#define BOOST_PROTO_LOCAL_LIMITS (1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY))
#include BOOST_PROTO_LOCAL_ITERATE()

\endcode
**/
/// The above inclusion of BOOST_PROTO_LOCAL_ITERATE() will generate
/// the following code:
///
/// \code
/// template<typename T, typename A0>
/// typename proto::result_of::make_expr<
///     proto::tag::function
///   , construct_helper<T>
///  , A0 const &
/// >::type const
/// construct(A0 const & a0)
/// {
///     return proto::make_expr<
///         proto::tag::function
///     >(
///         construct_helper<T>()
///       , boost::ref(a0)
///     );
/// }
///
/// template<typename T, typename A0, typename A1>
/// typename proto::result_of::make_expr<
///     proto::tag::function
///   , construct_helper<T>
///   , A0 const &
///   , A1 const &
/// >::type const
/// construct(A0 const & a0, A1 const & a1)
/// {
///     return proto::make_expr<
///         proto::tag::function
///     >(
///         construct_helper<T>()
///       , boost::ref(a0)
///       , boost::ref(a1)
///     );
/// }
///
/// // ... and so on, up to BOOST_PROTO_MAX_ARITY-1 arguments ...
/// \endcode
///
/// If BOOST_PROTO_LOCAL_LIMITS is not defined by the user, it defaults
/// to (1, BOOST_PROTO_MAX_ARITY)
///
/// At each iteration, BOOST_PROTO_LOCAL_MACRO is invoked with the current
/// iteration number and the following 4 macro parameters:
///
/// \li BOOST_PROTO_LOCAL_typename_A
/// \li BOOST_PROTO_LOCAL_A
/// \li BOOST_PROTO_LOCAL_A_a
/// \li BOOST_PROTO_LOCAL_a
///
/// If these macros are not defined by the user, they default respectively to:
///
/// \li BOOST_PROTO_typename_A
/// \li BOOST_PROTO_A_const_ref
/// \li BOOST_PROTO_A_const_ref_a
/// \li BOOST_PROTO_ref_a
///
/// After including BOOST_PROTO_LOCAL_ITERATE(), the following macros are
/// automatically undefined:
///
/// \li BOOST_PROTO_LOCAL_MACRO
/// \li BOOST_PROTO_LOCAL_LIMITS
/// \li BOOST_PROTO_LOCAL_typename_A
/// \li BOOST_PROTO_LOCAL_A
/// \li BOOST_PROTO_LOCAL_A_a
/// \li BOOST_PROTO_LOCAL_a
#define BOOST_PROTO_LOCAL_ITERATE() <boost/proto/detail/local.hpp>

#endif

/* repeat.hpp
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
*/