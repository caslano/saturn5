
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/this.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_EAT_(elem) \
    /* must be in separate macro to delay expansion */ \
    BOOST_PP_TUPLE_EAT(1) elem

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_( \
        elem) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_EAT_ \
    , \
        BOOST_PP_TUPLE_REM(1) \
    )(elem)

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_( \
        s, error, elem) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_TYPED_( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_FRONT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT( \
                    elem)))), \
        ERROR_use_this_underscore_instead_of_this BOOST_PP_EMPTY \
    , \
        error \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_( \
        s, error, elem) \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT(elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT( \
            elem), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_VAR_ \
    , \
        error BOOST_PP_TUPLE_EAT(3) \
    ))(s, error, elem)

// PUBLIC //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS(sign) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS_, \
            BOOST_PP_EMPTY, sign)

#endif // #include guard


/* this.hpp
JpwBwiB7cX/VeuaJj0YBhf7vP5lD9grTWM/nZg15Pnvc0igt/Lnm2x7nC8LvSMHsEs9TYORQMe/MZ5+L93Orw2WjZkeAe1TK49z+Nt57sj2GOssaKuezQn52+eWPIKw5zj0q2lKEU41z8Nu69kS6bmMb4se5iN+tjWsVewk+Dr9O93Lx2Rf43nIIb87vlomyifA+9w90nmL5Ylm+MlE+puExflcr9g78PfzXepaRz9DW7BtYK5UzjW3IOJTlrD3NcqaxHZmGWx/dYfd+Fs9GwnWe5TSfxf7LVzc08Gex5Jd2CPPKl2tq+z/0az63z2/Fc5t1onpu054J7QEyfbkvbGqr7gv1nnXk+SwPoK7qvfqCEYe6vurPSF8w03B7nixs513OOvhvdC8n3wn8j1WNXv1AhFPb4TrFcrm1J+OXy5RJm4FDGMlgyF0okzbMs0zFBYHw91zhLF7c5A7ksYSK62mCE6cqJ8ObfbjGcep9WObqyuNzukPdXzO8yoxu0Iq9PxHeo6+K8L7GZ/g/tTZ176tmGm7t2ouFG6qxfdmuue5l5LuP/3bN9WpXEc5s1wJxfZDPds094+0q0nfjWm1lmZMZSQ/IXpR5j6vMBWU5pnn1/J/RaJbBp+wTh3g7BWaPyBj3UvWC62HpoTf5bA0+08sp0w3gwpuwtbwNsUQijgRd16DZ0qBZsIdpnnkKzDay217sHWnD28g45KV0/DnLjcdJ/QwojRIH/SPRtvnL4FvVDxgHWPrIfzryXg9JRP7tbUbYI22a2b6RMcw3/SUhT92FjeLwEGt0eKg9NNQe0rbZ/3aHJtK/MJ28tZXN3MNUkWZX0xbrdOaBdqgRv+sdNEnUI7Q1bVw12QHXesE9F9JDz2NYGzO9/9C2eiB1a3BK9brpxLqR69veibYTGGgq6zvXZ30Lfn1A9Z0r1fcelCMd9ZqslyUC9d2muf6OOljf9Fcbo6hvW2D1vUWk2cWs731yfTP+V2LU9b0V7g0x31V9u+7zQ6zvRH7fJECcKEe9sr7zl1FFaJbXwvIaesInRbg4Rf0zTmnc2hHAN46Rf6SF/DMt6PCeEnGJcrnr8GjnL42RDDRsqCnLI7aDEHXdiEymI2ySuP9c9Wu4Z8O9p+7errkNUsl5Nc7bwh/szAqdbfvFcAl309ma/eETkY/2fsdr+fnTjTbu1rGN1vJdKX24VCbRMDlVlcUlSv3tWcLvai1W6FAZFjH2gWWfs7UxZjvxmsyrxi990C30ZccR/hV8e5Z30XBXecMk3v584TZfQ2360P367RvTfT/L+X4m5dmDpy/6z6bhah3wE6xr+DX5+/lo0wa5rsWzHqa8c0qrSko89OUs9yvCv1N1HyCuU3tXkZ/PtV3YvxkgFfIh+qlzhMgnOnbzTbuiEB0QR3N75pcXQhPia5xEHGx/cMFRH9ldjDGoS/MY5Hc/DVcbxcp1z3Q9bXMujOc7BgMmQU6gzuu8y6IPAAGN9XUsg2pc7oCzenE9WhrD/b+v+BpLpxht0tXUQ5n4X6Td6CpHxc9y+Ko4MXPy+FnzsnKmZU+eiTGoArviaxxTj4oxteJnvsrV6FEu9LHKcvV9Cb+qb2P19y79Su8c/vc5MupDz3Mn5pnvlRyvkTe62eXvYI96i+zmXW+fIHxTi/UGnRvvP7NPBrA3k1u6Cd7pfqH3lZEtpessc4qxNrD20qR1oauEXz2s/hmkbjP6l54z/sukaAdzLFwl3Mw03eyXn1SU/zP4d7Rc/qqKFYGV3TEy8L7q8Cj30QDaMtD+92NYB/GGWAehvZRY8K9pe65/JGrx1dsqdm0MroMIroMIfB1EgWEXmOsgpmmu53KkRXBmtWTpd08=
*/