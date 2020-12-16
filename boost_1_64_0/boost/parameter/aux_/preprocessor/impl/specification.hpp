// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPECIFICATION_HPP

#include <boost/parameter/optional.hpp>

// Helper macros for BOOST_PARAMETER_SPECIFICATION_ELEM_R.
#define BOOST_PARAMETER_QUALIFIED_TAG_optional(tag)                          \
    optional<tag
/**/

#include <boost/parameter/required.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_required(tag)                          \
    required<tag
/**/

#include <boost/parameter/deduced.hpp>

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_optional(tag)                  \
    optional< ::boost::parameter::deduced<tag>
/**/

#define BOOST_PARAMETER_QUALIFIED_TAG_deduced_required(tag)                  \
    required< ::boost::parameter::deduced<tag>
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/parameter/config.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/use_default.hpp>

#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , ::boost::parameter::aux::use_default                                 \
    >
/**/

#else   // !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/parameter/aux_/pp_impl/unwrap_predicate.hpp>

// Expands to each boost::parameter::parameters<> element type.
#define BOOST_PARAMETER_SPECIFICATION_ELEM_R(r, tag_namespace, i, elem)      \
    BOOST_PP_COMMA_IF(i) ::boost::parameter::BOOST_PP_CAT(                   \
        BOOST_PARAMETER_QUALIFIED_TAG_                                       \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(elem)                               \
    )(tag_namespace::BOOST_PARAMETER_FN_ARG_NAME(elem))                      \
      , typename ::boost::parameter::aux::unwrap_predicate<                  \
            void BOOST_PARAMETER_FN_ARG_PRED(elem)                           \
        >::type                                                              \
    >
/**/

#endif  // Borland workarounds needed.

#include <boost/parameter/parameters.hpp>
#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

// Expands to a boost::parameter::parameters<> specialization for the
// function named base.  Used by BOOST_PARAMETER_CONSTRUCTOR_AUX and
// BOOST_PARAMETER_FUNCTION_HEAD for their respective ParameterSpec models.
#define BOOST_PARAMETER_SPECIFICATION(tag_ns, base, split_args, is_const)    \
    template <typename BoostParameterDummy>                                  \
    struct BOOST_PP_CAT(                                                     \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    ) : ::boost::parameter::parameters<                                      \
            BOOST_PP_SEQ_FOR_EACH_I(                                         \
                BOOST_PARAMETER_SPECIFICATION_ELEM_R, tag_ns, split_args     \
            )                                                                \
        >                                                                    \
    {                                                                        \
    };                                                                       \
    typedef BOOST_PP_CAT(                                                    \
        BOOST_PP_CAT(                                                        \
            BOOST_PP_IF(                                                     \
                is_const                                                     \
              , boost_param_params_const_                                    \
              , boost_param_params_                                          \
            )                                                                \
          , __LINE__                                                         \
        )                                                                    \
      , BOOST_PARAMETER_MEMBER_FUNCTION_NAME(base)                           \
    )<int>
/**/

#endif  // include guard


/* specification.hpp
MBiHjOjb/15nRrbd6vS56j3/Pxq+/vOTqnz96YH7BpBve2dFCN+2N89lx3VmTt1+a/W8/z3yOULktZV+bH1PwhUh8jVV86n7nEFzBprAhx4D7pVUdzk0/3mCKXL/dih/6d6n1PD8K5JHu9PKd69Ic4746EDeE9Hzw0fq346WXz2U37uzrG9H+6wRbdO+Tn3t5mXfNpuz5gIhPpHh3Ydue/Tls9zHpKU2GrP2onGmUH710P7qZVJvn6x65fXHJyj9cn999tKiCsuGyP3twedHhPSfk9+b+jv1x8v0NSw1/dBNyQ9N6dBfQ6dLpnStKF1rcGkQv/We3Sbpux5QYqrTf51Sbqqxz2M3hNXmw34EbPRj5w/y+7K3Bfiz5yKe6tNOx/NUv/ZCSDb+X4rwR8pNEfm4FyD+2nIen2QwGAwGg8FgHP04DPv/Y789yEirwxmFOQDq3HUvnlFxsZy7riDXDMXq9VpxQL5NiKiMEQxLUst4rNRBGv2MH0z2zdWQiW1hz+xRbZ97qGKK3FjQ4XFZvRm3wEa60PwI4sQIhxP7Dzgz7AJh/c2JUr9a2hjk1c8MM1XGf1TGd9utnhwngvT4cQHx4yn+YxTfY3ffhorr8eMD4ifgOgnjBWq+VtRrOCQDYgtj7CBJNJXlQ10MNUFeCFfzQZn1EiOuzAvlMpSK1jSQLtfSJgn7IPHEkxH/nhq6lM1q93ioZYWoU6f31NBpaB3FUXyjTpsjfmcwer3Vka3Wp4/U2Ssy3kq0fa4YJdJk/A2VlZWtEf/JtgKoeWZEc6Q9Xh2f2aumbU3XMUKR18fKsk2RabEnpdPu8dpt8rnr8NyeaKtmuGNPQkkgWZBbIA7IrZARkGzISIgTkgNxQXKpPduJKiRA8t9Q26C3bM8moqd5BfJIkvppaL5Dlieh44CrunQXFHa7DBNq2NlaWG5VWDctzKmHde1cM6xLVy3sjKqwc7Swj/Zo+XbtIkL1MwqPD+hT1P9kG3Sm1qK4Un/Qa5VWaRzuJn8ZxN2W6v1xIS2ueRASTzwN6d/fG7I/2uzUH1tTG8aouamvRgfegnhTCWHsl9qz9H4Zsu1LUPZUtD3i6O3uhnggXogPcpvezoPlO3DydPxpVPMd2AL9zQz+UubdHM83yb6REtA33gvoG0WGvtF7H7UR9YPmCLton9aWPWScLvp1F+oD1cK6UTpDWHcZJ6kqThctXRn1Ra2ftKY+AV0Fali2dUnNtpZtey61bWmckKigtt0NeQnxrfuMbRv+O9u6r+53tvo5Twa7ZNx3je8bpA/nHd7H3FKts4w7GfVpYHivV39GAj3DC5afDl+2/Lc9vXtelHFfxhNaitaQLqKXcKHV7xUd9f7WCf2tMeKOQqOPhuSR4H8ZpvHtkGD9Z3Ut/eeS/Xobn6u1cf/9Nd8ZJ1eFda0Zhr4Qpe+hFtRnvLq2/P2lq/Y930RIdKL2TqXv+Rn7q/UXt3VU3d9FM/bX3Vf0viHjh9M39H6gx9e/3xF/HOILk+IaZB3VLzv7SpRV6N9Dc2T8lBrf97GH4ftefd8ukflhLLct6Zj8HuOb+jNrLH9LgUnHK/w6VvoOuka5/KrLrxFhfN+viFDHKyLUsTF+gsHnMvoI/m7qSXorJEdRB9JbW9LbGtIbNTjUN9i/21UY+lsTof7WRKg/Y/wEw7rPO6C/MUdQh+T7CuFjOfrWlF79tPR9/XDd9uXfjT2pz1dFSZW29iN4TanfxxX5WtDa1nyma7YS2Xdzqa8PEH48QPu2PQhuDX4c3Bb8CDgVPAHcGfwQ+ELww2BpH5KPLC5GszNg69DzLfSbRMWJiBcPbg9OBneg558EPhmcCj4dfDLlcyq4B7g=
*/