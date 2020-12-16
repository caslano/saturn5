
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_

#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/this.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_(sign) \
    /* using PP_EXPAND here does not work on MSVC */ \
    BOOST_PP_TUPLE_REM(1) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign) \
    BOOST_PP_EMPTY /* always trail EMPTY because bind type is optional */

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_( \
        sign) \
    /* using PP_EXPAND here does not work on MSVC */ \
    BOOST_PP_TUPLE_EAT(1) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign)

#define this_BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS_ \
    /* must expand to nothing */

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_(sign) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE( \
        /* can't use `THISUNDERSCIRE_REMOVE_BACK` because `sign` contains */ \
        /* multiple tokens (and not just one token) so */ \
        /* `IS_THISUNDERSCORE_BACK` does not work (but we know `sign` ends */ \
        /* with this_ if we here so we can manually force the removal using */ \
        BOOST_PP_CAT(sign, \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS_) \
    ) \
    /* do not append PP_EMPTY because ANY_BIND_WITH_TYPE macro above */ \
    /* already appends it */

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign) \
    BOOST_PP_IS_UNARY( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT( \
                    sign))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE(sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE( \
        sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_ \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT \
    )(sign)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE(sign) \
    BOOST_PP_IIF( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE( \
                    sign),\
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#endif // #include guard


/* any_bind_type.hpp
D+NnMn5fJX6+Pr5+fWLGHwy8Nd49P3BUjBuo8gJc8QLX5Vq+3eUDxriA/y4u4K1HgccH8dYnG2MhVZAmyMOQVZD+DTGORGyLbbEttsW22BbbYtu/ZVt//H/GERSA7nEABhpe0bG/HB0s8UboFGbyweGnITz+nu54Lb7jh/NnQKcZHTXN4jsC9SNLyqv9VUg7i+HXmuEjc3goFCdxCPoqxDHYjW9VVvC7A98OwDxy9gO/F8f+I/n9o9ALfv4eoh+4ZNY0fz1mIEwrqTFEH+4MHPMYJQcFsLrgDO2aGIzLPt8tfEJ/77r6GWUBXb++Tf+3kH5eHYYqKnVri9n0/QlCf4/6I/KwZKGhG5eCvnXdjdEu1t0wvy0atHfjDntlPzPsQjjtUsYQkX+EM/8M9wGRT4TLfIqxlyORL7GOWI71m6BL+d2AryEeyCrIVukol1CZHB78tHlVZY0f5az9xvGZQu8j432nNS7pj72NIpG3ufhzGmQ+5LI+iA9sRx1ZAPwOuBryPWQNZEAm5kwDf4T8BDmrC+Nh6jj5QiqPUtb0fB2ptewZNh9GXjWYECPWA18GP5Ui/s/IR6ondXjqOHwrfAN8zx924ZBoKX7BsXig01rLi8V5tjT64a9YG5JxE3uF4iW5+NaAusbMCC4uswXt2RzyZdDxe6n20BTDOV/JQn+wMQB/w+2J/P1tsXYsfVyVxGubCkMgdajXY0N54hXu/vpGPP31rV7Xih6veeU72SWTKhuwkLeyTmqJ0E0Q66LmJOI8yPPTSMiLzCrXrSijTq7dPbty7QavxcK95LVoKU8vuwMmsjwnQPaHjj/kOxYkm92GyGOAfsV3eWJtoVBUHJLj/TOFznijF/5uBhkD0bWbTEvUod1z5HcFdG0mdPXrk2fQ/2eK41sj/z1R5/TfHWAasj7+OgDtHeT3LnzD3CwL+AD70gdybBz2yPXhOTaurJ9tLaNs8i1yecJ92F62WsuoohIfUq47JnIZheJ5RBvjQyYXQv6Ajd6k7HgfmpiU5I46+eeAUJ00dZ+C/CV0U72JQjk1TDeDuqsgcBzWSzeCinLNWc/AkF60Y6CW7+ikcM1w1tsdIHvApznjrD6pPgJecVFvEU/W25+QP48honItfvKUhE6OqLeb6uss0nFfZ6Grq7Paukldud5vHPIYP7Dr9RI2Yj9kY7T1crRZBhxjzxd5FmNKggPWaC0DlUChrJeGW4W+/UV8Z56XXOda6OxmbK0vB6QRHfercVxkPo29TBqV8pvhC32HwFC+D36zOD4U+YlT+GFBL3SsMf2k0PHivEXCDw8h8d+R1gUZeB72uV+bmeUb9Ola54GdLfKIcd10a7s0lGvSn8MMnQ35DPWnPVT+AVQt3jjEBy9s14S27BkX15d5L00otaczfPTo0u3wx1/XYK7hDhwfjNdL+L439keK/TEISRZ1YLTIMdth5b7wpzjfwWgf+uPK7it5eoNE/ESWS+g+cFFflI3AyPOVWS6268krbHpYvLPgmxXYyULYLxhUu1GEqd7q0F8sjsFc230hwDXzq3niKvq/Zbz0PxtA9/5HXJ3/mU6Y/6W/X+rwtzhPuVj3F69kyjc5HhU628DXfdmOhdqwQzO65s+g74qH4Z4k/MMc2nzXKn3dEbZM+tPanuUyB/N44tMgg/GAO3bvDn9a3kL5zId3VLVuyWt7sohXJ7me7/aHO2FvIiQJ0gOSDMF9E7YcJNJ5rdCDg5azyGfI8SI9X8Q2X12f/GFq9qVCJt8/2h1s6niKUJ8BOi2fsPU2T++l96NvH/WcPGEEHw7fx70PM2w+5Bmk/zbex73/zLWOf+6l998SjS3Sed3wXUVvvl9J/go=
*/