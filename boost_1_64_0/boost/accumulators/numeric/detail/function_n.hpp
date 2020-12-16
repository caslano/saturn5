// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// #include guards intentionally disabled.
// #ifndef BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP
// # define BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP

#include <boost/mpl/void.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace detail {

# define BOOST_DETAIL_default_arg(z, n, _)                                      \
    typedef mpl::void_ BOOST_PP_CAT(arg, n);

# define BOOST_DETAIL_function_arg(z, n, _)                                     \
    typedef typename remove_reference<                                          \
        typename add_const< BOOST_PP_CAT(A, n) >::type                          \
    >::type BOOST_PP_CAT(arg, n);

#define BOOST_DETAIL_cat_arg_counts(s, state, n)                                \
    BOOST_PP_IF(                                                                \
        n                                                                       \
      , BOOST_PP_CAT(state, BOOST_PP_CAT(_, n))                                 \
      , state                                                                   \
    )                                                                           \
    /**/

#define function_name                                                           \
    BOOST_PP_SEQ_FOLD_LEFT(                                                     \
        BOOST_DETAIL_cat_arg_counts                                             \
      , BOOST_PP_CAT(function, BOOST_PP_SEQ_HEAD(args))                         \
      , BOOST_PP_SEQ_TAIL(args)(0)                                              \
    )                                                                           \
    /**/

template<typename F>
struct function_name
{
    BOOST_PP_REPEAT(
        BOOST_MPL_LIMIT_METAFUNCTION_ARITY
      , BOOST_DETAIL_default_arg
      , ~
    )

    template<typename Signature>
    struct result {};

#define BOOST_DETAIL_function_result(r, _, n)                                   \
    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)>        \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A))>                             \
    {                                                                           \
        BOOST_PP_REPEAT(n, BOOST_DETAIL_function_arg, ~)                        \
        typedef                                                                 \
            typename BOOST_PP_CAT(mpl::apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<\
                F                                                               \
                BOOST_PP_ENUM_TRAILING_PARAMS(                                  \
                    BOOST_MPL_LIMIT_METAFUNCTION_ARITY                          \
                  , arg                                                         \
                )                                                               \
            >::type                                                             \
        impl;                                                                   \
        typedef typename impl::result_type type;                                \
    };                                                                          \
    /**/

    BOOST_PP_SEQ_FOR_EACH(BOOST_DETAIL_function_result, _, args)

# define arg_type(r, _, i, is_const)                                            \
    BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(A, i) BOOST_PP_CAT(const_if, is_const) &

# define result_(r, n, constness)                                               \
    typename result<                                                            \
        function_name(                                                          \
            BOOST_PP_SEQ_FOR_EACH_I_R(r, arg_type, ~, constness)                \
        )                                                                       \
    >                                                                           \
    /**/

# define param(r, _, i, is_const) BOOST_PP_COMMA_IF(i)                          \
    BOOST_PP_CAT(A, i) BOOST_PP_CAT(const_if, is_const) & BOOST_PP_CAT(x, i)

# define param_list(r, n, constness)                                            \
    BOOST_PP_SEQ_FOR_EACH_I_R(r, param, ~, constness)

# define call_operator(r, constness)                                            \
    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(constness), typename A)>    \
        result_(r, BOOST_PP_SEQ_SIZE(constness), constness)::type               \
    operator ()( param_list(r, BOOST_PP_SEQ_SIZE(constness), constness) ) const \
    {                                                                           \
        typedef result_(r, BOOST_PP_SEQ_SIZE(constness), constness)::impl impl; \
        return impl()(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(constness), x));   \
    }                                                                           \
    /**/

# define const_if0
# define const_if1 const

# define bits(z, n, _) ((0)(1))

# define gen_operator(r, _, n)                                                  \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(                                            \
        r                                                                       \
      , call_operator                                                           \
      , BOOST_PP_REPEAT(n, bits, ~)                                             \
    )                                                                           \
    /**/

    BOOST_PP_SEQ_FOR_EACH(
        gen_operator
      , ~
      , args
    )

# undef bits
# undef const_if1
# undef const_if0
# undef call_operator
# undef param_list
# undef param
# undef result_
# undef default_
# undef arg_type
# undef gen_operator
# undef function_name

# undef args
};

}} // namespace boost::detail

//#endif // BOOST_DETAIL_FUNCTION_N_DWA2006514_HPP

/* function_n.hpp
FMMfKWWTRjYUsqWqB6V/P84qYzcXc6GHi9p0u0gDOqLZtp59LaEZV+AJiQ5tJ1TmmqzQIa+aQ6ge5dXn44riHZGhgfIP4Mp3bowMzTeHj4oMHWUOL4wMLTSHF0WGFhGwmt1tlecpyb3YRBMADtnvQEbnRoo84SnNjZaikVz8vQt1+38JB9fPHr9Dsh60eh/r3LvjYrEG6qA80MRHbtP1IgsYPLOiI/1GVVvrESzVFexA1B8rr/numxpad0P9VtZqqvCUUIUjX48Tj2r14XwazX2+4kTNDkSpc7ao9YsZ69+Qvipu1lffPCEdWcX9NHOB9JPkfEMtlpy/3Fcv/+EJ3ZrrUVPu3POQWxi9KxD0z3xXaj/3/+6S9e4dkSXzK/u7iAvBIdoID8mHspZKa93gFxHKs/MV1VWH9gDPyaEltKeILZHQNsyVmbUtLuX9oLkj50UnSv0YX679ZVMsVk9HR7Xffz/Eerr4o1/pBZ1P1D8399Kza2eqX0xGsL2EH49p8tdNwpQ7adN3F7JGYaQ0OthQv4PAo7GAlmsWtH3yjKzhVZOsY6EQTPqMLsElRD/112IRbXemXlpxd3xx8EIGivx0LJRK+dtPlv3rUZgTPO7mukP6EK5F3z5cbtPr+vuZTKeqF8SRpp6Gg85A4Um36HXavuj11MVyQqquEEe6Kl7899HrkXZ9+FnzbhbgNA1Y6HUyfPvOf2Tz/DN/q/NPg4MrdiUcON5Nsiv//fT5hTsZptyNAn1OZdBn3LJv+jwyDe8dpqnOEh3ajpB0hKSrJB3yqjkog3PgdvhBE02Z72dZNbkgvS4XdWOJ895HNZHguf+972noY4aPfykzP5bHT2gEUbGyIMZ4Gg04tJjViMVS3Xx9Cr5EdyXRv7N0XF99LF6GODX7bj1EyNxFJziSApBgDBLwzabIjAyzruWb5ivv0TT5ChEA3bDBxeorRtT/isrHOS1nQD9TlkPzDOR+3r+FNC3x/Vv3J+rSWxhh6dlE9YrQABIxr/w10YAgaIDvSvXIz1lEdSOBKFtB1R3GvXD5fZz3JErMORdJ++56JVFH52rO3TjEDwlcD4h6UgnvX1soHXi6ezMfjvyGvO9wfBrRhyd1vAvx8H6DkvjMtNnL2Yfw1Uy9FRpjFFi2LR64w+JaSGK5EV0J6VMDn1a9pbIw/pBVAz1cVL2esuodpyXLtxSRl3hrVFfu3o8dB4YXjxiILFkf4WP1gAyiY4mQUn3iRbpK2EbJhou2Ok+xvEJNA6VkcfPl/GWZhDoj7vGoXnFPoTo67vGrDtpj7lSxy9hJ26yvLOcO1UBOskDBVXieZTl4EzZ0Sh40jHj3r36yQK/eKxCL4DQ5ee4gwY09A+RFBwRMVMwS4qsxv5Bd0VUMclYGy80KQ2fkmQWptENYH9VQL0ACBKbxHoK2Lb+TGNFdajyRzVbi4AW9zpCp23ffIcA7IQXn45qiDurrWyXmQe5EmIpATorMV0VTJeZth8R4IFKkzaNXh6+2jjrWae2gLa0PJH7V/BjlzWbHKHN5V4jbijIX/nqNwL0SwUitQ7fo0FGcGP3eQNIw7lE0UJ0t1a84EtHUS6N/IX6nfcJjnYRI/eJVoxRoK4KpUVejGNGSOECFNyYl1myAzrIyqVkzTtTB93BwHfqYdocuHRpNOOdZo+v1euIxytXIo3eU75QyroxFC3TIixIylPaYyyx1qzp7lIc+zNF96AV1Vps43kpIseWQFZBtUnsXuikCHyHKbyaIZOvJB5ACeQMmMImrbyGXYKONoT+yLek/9a8qh+0/LGEayIfJQXB3b8+Fv3xNTu2B1l9hKq6UrNjFCF+hdposABnG7ErF7ewx+MQ=
*/