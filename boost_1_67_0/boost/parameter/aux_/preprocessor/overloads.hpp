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