// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file generates overloads in this format:
//
//     template <typename A0, typename A1>
//     typename ::boost::mpl::apply_wrap1<
//         ::boost::parameter::aux::make_arg_list<
//             PS0,A0
//           , ::boost::parameter::aux::make_arg_list<
//                 PS1,A1
//               , ::boost::mpl::identity<
//                     ::boost::parameter::aux::empty_arg_list
//                 >
//             >
//         >
//      , unnamed_list
//     >::type
//         operator()(A0 const& a0, A1 const& a1) const
//     {
//         typedef typename ::boost::mpl::apply_wrap1<
//             ::boost::parameter::aux::make_arg_list<
//                 PS0,A0
//               , ::boost::parameter::aux::make_arg_list<
//                     PS1,A1
//                   , ::boost::mpl::identity<
//                         ::boost::parameter::aux::empty_arg_list
//                     >
//                 >
//             >
//         >::type arg_tuple;
//
//         return arg_tuple(
//             a0
//           , a1
//           , ::boost::parameter::aux::void_()
//             ...
//         );
//     }
//

#if !defined(BOOST_PP_IS_ITERATING)
# error Boost.Parameters - do not include this file!
#endif

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_open_list(z, n, text) \
    ::boost::parameter::aux::item< \
        BOOST_PP_CAT(PS, n), BOOST_PP_CAT(A, n)

#define BOOST_PARAMETER_close_list(z, n, text) > 

#define BOOST_PARAMETER_arg_list(n) \
    ::boost::parameter::aux::make_arg_list< \
        BOOST_PP_ENUM(N, BOOST_PARAMETER_open_list, _) \
      , ::boost::parameter::void_ \
        BOOST_PP_REPEAT(N, BOOST_PARAMETER_close_list, _) \
      , deduced_list \
      , ::boost::parameter::aux::tag_keyword_arg \
    >

#define BOOST_PARAMETER_arg_pack_init(z, n, limit) \
    BOOST_PP_CAT(a, BOOST_PP_SUB(limit, n))

template <BOOST_PP_ENUM_PARAMS(N, typename A)>
typename ::boost::mpl::first<
    typename BOOST_PARAMETER_arg_list(N)::type
>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, & a)) const
{
    typedef typename BOOST_PARAMETER_arg_list(N)::type result;
    typedef typename ::boost::mpl::first<result>::type result_type;
    typedef typename ::boost::mpl::second<result>::type error;
    error();

    return result_type(
        BOOST_PP_ENUM(N, BOOST_PARAMETER_arg_pack_init, BOOST_PP_DEC(N))
        BOOST_PP_ENUM_TRAILING_PARAMS(
            BOOST_PP_SUB(BOOST_PARAMETER_COMPOSE_MAX_ARITY, N)
          , ::boost::parameter::aux::void_reference() BOOST_PP_INTERCEPT
        )
    );
}

#undef BOOST_PARAMETER_arg_list
#undef BOOST_PARAMETER_close_list
#undef BOOST_PARAMETER_open_list
#undef N


/* overloads.hpp
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
*/