
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMAvirtual ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTYvirtual

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `virtual` (this can be
//               checked with `..._IS_VIRTUAL` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_VIRTUAL(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* virtual.hpp
PYt9dOdhnzuIQ+HjTTqrSj+69aG+Wx0/HyZ34WupzbwMDXdF3F7Ki5P62hvrAStowryd+BIYUpiGnIBjUuH8s864l5Vnb+cK3p/CF+1Utz5ffR0+5L0yhPjpOP4jv/r6DFf8To+X5lvEbGsl141SC/q6K3FgHRy8jw4dz7dsLyGOBaLoe71q2vzjaTi0Ab9MT+xqrJ/1oj1lmjwhnxha33gcOG2ynHlZ/+ek+JvHqmDu2fB8Wxi0CO9UoTP1msLWYrnvTa6th3nZz6+JYYzzYfB2HQ3SX/33i9YDwUfzTsAn/f3GwXn2FHLhGXWQQl7V5glPwNUYnloMp5nTL3ijor2lKbx3EWOpMhIf0Vxpw3rcFY05Si1tjvAr5q133HkyPlkVdjZJ/X6Ib2vpIS2Lwkn0e5Q+US5+WmweqrG4zM6rTjbfO4/P+u6my1adpH3fNJ8vccYFvH5C7m8I9hGsgbUoIL/LdQgnPZdz6ik8JsceNPQ8Fz1fvw89JkfzZQ3TeXrQPeCLv9dar5bjaTCfiahZlwwd4V975Y2ib/Q8/b2GOB7upI774ie4s3edXlNQ09v1Omn0tIfoopC9uAb++0MPYYXasIe36BRso0PWqJ1LxyPmr3c7xHyPPj6fnT+fnsw4enmgPZ4JtLm6WYLP/80J050RT2Wcw1Pytbhr1FD5p3dQyz0eqNmSPHjvYjB6J47awb/QtF3/1GfAJxf0Ugp3tVeh37Mx8Ac0e//5MBIH3cHvFaYE75TyGfngXfHelWkMwb5Eapyt/vrV4+fwec6iOBLvJrfPljENzBxIX6aHr3zYePx9+Wn4ofbGw+8NNFqNFThqojpcADey8lPi9NcTdDc/VGl5yLuY/TuMWafn4H239lRxy1pa4VXXpav/kpeVL+P64Ky02K7uyaPG0w1ngudt8NnTeLk9DntkD/Sod/Tds64w5mPr/AEserdq8A5CXGb/8xOYc2WiOcDpmlvwX1HjNY7JxfQ8rOG0NnBc32YyfD/2AmzRA4qCocv+wRs4+0A7+lDfutn7cu26NbxhH8819zYzz278yw58uhjmb4ejRdU57CqkZ5KwEhdbj6L6ggUuwp2w8XwXEUdewjVKPKEmzbuza21tZp7NQ/Y6zDE9nhTj4LxO/1R82xS6+wrNYz3K0OzlxkWSzqvUo496q8mlPPMQ2mnMANgDz0410A/hGy7exzm98Os9uXMf7s/Sw9sgxgvtzV2nucroowxXV51oZ9id+4I6yK/uD+qTFIINvdXMKPr3uOf7HrkvbfXi28Yjly/zaA3gQHvznpBO7LeI4f+sixzIQus27RdRa/QiPK89ET/xnh8+S7/p11SRvzvD+p4/2P+gY/Zm45fq+DNRDwCPfkDTPKXee/IdmQpZN1j6nXlNKEhL0AQL1Mbq9+01DZLD1c2D7jj9FEyiu+qKWVXAOoYOKGtNk9NVny/jfwdZNzq8Bw59I8Z9ZsG9eHneU93RWZWH0o617UHnxgmBVn8Gn/4Cv+jRXdvwbazevd7IIBj0q35UyjJ0mGf648Xt/O8wIXgPrbx5m+4uKXeWL6RtaOjc+OS5NvB4Efzz+bfwUi7xTLEy5Ew73ivkc9E4NwEW/ktb0GXtad2KOKlDXNjzrcaZ12fF6HpF+Vke9jzg5RrS+NY5R+aooOee9G7SugvURBV9dZhYTszTlYQXm+V1C2c4aLhn5X7D7upOvTW05sVwTq92UfyQPNZrr/cOzRPgLX+XUS28QXcsomWuFsABtOx1GNm4O308WJ4N4YvXyxnr0OxlHK9mf6ZdOtH47arAtY/lMw1Tv61a2Gvtv1L/Yp+ronWgRVr8Jj/Vct+5YlmfpxKP5ME=
*/