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
3GEATk/hvfkPnI8WmcplOyS9gMHWzoqLY2wqP+XfVr7Jv1Uj0rRp0lJr0Y0uNdj4uQctKierC8vDzddnRzxyUbe47RWlDd2MhjpGOMzAYeZt5msRPfrfNYRSoYQmm2GL/xW3X9Suz9+cxCrXBMifdKL69+Oyp27efiv2K80rHAe6HoTEJz7+z+Osu28vOY/jspd1UmPlouc7ezyWj7fx4uUl4ZDkMk/qHmeKm2eAqsAc3DFWONCyLCy5aKwixBx/elRvVmMIpezFuTPb2/ws2/KxCXn5rCU4e93nSosSpf1WaRxUrT/cCd+JY8Q2YFS/L6pb4yRvCpWKUazBR5vxl/xUNM6Yam3eKcLzz/02bR9dIVnzEKxb8bvjLzmfu2DB9nXd5KZetyn6eRLV2aO/SrZJVbI6yewrrtICVk9jzH2Nx4gBK4w27le9uMDJ1VDg27DfrY999u2Jz3LZDLKQ5H+2uWo/tKNHI7LF+8btv/h3Ylt9lfV9X8vK42Swb4aTavaT7TKfhohXKrRG67s0YzHPzXWGxz63sAu7Irzbn+Sx0+dlm+oiKSWEEICH7E3wRx7Ky8pUFNjXydLbbBLc7WHTHLT4xa3RPfYW+zLOJx1ElqS5VrLx8agsUhDaPj540dvsLgmVk3Pma+AT+d81HTrQK9HbHuNBd5abHRDmq3r578X7T9tRfEX0K5vxTXViCO1C+M3KM8ymWnBeKhGySSF99DYmMuw3KEB7dBR418ftFSanPYPzka3Im7TDdPt32fh1vfH9KFZGm5QDtlYJuyCymSKDvkmMTJSPMB6Gtm9J8pZbRtoy0xPfGxc4HJwEAWI54ZGb2Y9FfCB+ZUWpysbGQ4qhYJzfVYCKCXzED/h4StEXRdsnWPx0Edgla1Sz+OAZiS/MY35RBWw8OZ9c4VyoS9lVfsqRBpA36RB1Cz+uYhFF7/bgE/nuNE0iC+xBi8Ycbhp/HzY3OyyGc7CN/GG8frO6aaEzKvCBueAdezXb6cdtRi/P44wNokJT8J+NHYZvFYdPnzvrzuvrc7oU+0dJSBCVYoTTWOjrjvbQhHboWtUOilcah8hjtsVtRFuJSuGg0V3O4t5ZMGNjlSHBaOozt8p5yES0ZZFWjezY/oEpcWfIiWuYn97Tzfh5ySArPDtqC8X1bzQa07OYXdPgdTM21m+KeCSiSooK+0c0FpJ9ATeGn4roMiFL6Gy0VDEdH0Rvf4PNP5IRqyarydBL8Bdu29CjjubKMU2TtNUg+8q4BsdER70/F6e5i5Zlk1S5ciEoJ7HReVksT6hh+yTpeoMptXIWo4kqjG+3O92Oj2yOz9z9HxrV2yeyGYpWUr0hSoc7k09H9SrR5lU1kEPHgKKP3tpZ3a8yhoPzuHhcSpV3g8w7qmx5A9tq6Gnwm3o6p8m0SAdIe5g8MaaXiYzhfNL91sRs+t/G+QwCn7AvhkKNddPRdeHO1tntyf78sahuyPr5oMnlaWlrgzYa1ArLV3OBX3EXjEdsjj5JOPnYPSPut8yzLktVP9YNAcI4JZh+r/i75a9imW/oqn4oi1p00LPByRALZaQze/jD4BJqB19PsF84n1zibMvbrG8yv371wXvxpgh739Oj9mSikTJN5CBwT3GAw/ZSH2M/vJjTYdvoccHSsmpDHGxDFkfA9mbqwryvWhmE8zqcll0/FIXwd9Pzrs5vRnUqkTVDrTUOxgUDZGuupw43bDFbsl6wKxu7W9SeFaY3uvqvo3hzOsdnSBM60r2cvun9xFE2km3aBhqrugrn+Y5rAHo3W//qWrgjSM7rBG70Td0OLTq7sXUhnUtunXhcF14+LUQ2ZE1bJJCrYPwLGhdnnF5SOQaKj+c=
*/