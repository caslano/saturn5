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