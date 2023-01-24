
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
dLa6wq8W+wlLXFnZ18KiDVYXmFYaiWAr5+ZmrTLlYH08UD0h5+PziYD1w93NDcD1DgDQb3dq7G4ooWZhEaIt/sjX2tla1t7ONeU+GoefXaWxXzr7wKhO6d6u+qP8LxlJkTsbG9PRLv+gAlwINACFhNCEBlMjvBvIRZnNEcxHfq9Mdq1GzocNOMhbXdBssteHnK2hrNfINZZvTkwENDWhjo93oqEJubpmNzZWqatXzdXOcRdnV0RZElp2v3ds0m/L0ksqGEWOZRHEMhdMyHLkl2Maez1EkiOpin79BUsTny4W3IyB+NzEKvQ3fR8eCAhocHTsc3UVd90fbHJuDGrkgp+bIyhn9FIort7aciuoo6Er4Raqqmk9PNrYKAKD48/Oem9vofMa9a6/7zQAWbHWAgTL33G0Eou5HgAApmgp3QydFBLSHw685QdMCre9wPvhr0X1vKzVElipTImHgUG2up6vHPaK2wwIyLp3Z3cbXEGanEOfxRQ5Z2I7Z2B6J3dOz2wxNgmvaT8xajM6XKrE8wUfX4eEqHV5XemksyLTRkjoUyeB57WntgmZa/xPrvi59NFfOGTZm3i7DPxVVEKfqSZFOhzsTS7dXCfAwGAQVWvHF41qQe+W01U+bc03f6e6tBljbi75zOX0bj/TVD/NVBtYV2vbaKMt/T54yIb7m/0RyyxGY7MexUk7eMGjqvlFS//ppneiAi27czlF
*/