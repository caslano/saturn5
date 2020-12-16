
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_sign_/sign.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>

// PUBLIC //

// Expand: decl_traits (see DECL_TRAITS macros to inspect these traits).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS(declarations) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_NIL(declarations), \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN \
    )(declarations)

#endif // #include guard


/* decl.hpp
ICwDg2AIVHoCuswnyNxKGqyHLLQbyDlbOnwOloDPwwh4GNaHR2Fn+CLsBo/BnvA47A8LEc946AcnwyIwWc4rmQ5fhzPhm3AtPAU3wn/CffAteFD8Hxb/R+DbmL8I34FvSjwfif3H8DTmOgl/HxaCH8AAeAaWgGdhBPwE1oGfwkZi3gKeh93h53Ag/AJOgl/DqfACvBNehHPgd3ADvAT3wSvwIPwVZsDr8J/wN/gvaM/PZ7AIPAePYE7Y3Mt6tWNsDXtarFcPkvXqIdAPDoX+cCwMgLGwDIyDFcQ8Ao6A1WECbARHwpZwFLwDjoE9xL2cfyVjYNwgaS7nX7WTdHSEpeAdsCzsAiNhV1gDdoMNYHeJtwdsD3tKvP1hJ9gHxsAYGAv7wZFin/m8yDgU1rB4XspJuw+H1WF5qPx5yThKxpZpqizwJ99pJUr5JcMwmALLix5IZZjKfV04VcprGuwGZ8IBcDYcBufB6XARnA8Xw03wbvgwXAIfhcvgW/Ae+Bm8F16FafA6TIc2ErsKloDrYRm4AVaEG2EtuAV2hw/D3vAROBbuhIlwF5wC98Bp8Gk4Ex6CG+DzcCc8DJ+CR+BBmAEz4FH4T/gCfB++Aj+Gr8HP4evwS3gK2mw8r7AEfBtGwk9gZXgU1oPvwqbwNLwdfgB7wg/hYPgvOA5+BKfB83AZ/BquhBfhOvgN3Aq/hTvhd/Bx+D18Gl6Cf4eXYQb8Ab4Kr8A34M/wLfgrPA+9qOdfYCF4HRaGIbQNPxgGi8DKsCisAv1hPVgM1oclYBQsCbvAENgdloI9YWnYH5aDA2E4nAwj4EwYCefBSnARrAFXwLpwM6wHd8D68FHYAD4OG8J98Db4LGwED8PG8Bi0t5f3YFPuP4PN4LewObwMK8MrsAr8FU7H/e/KXvQSbPKuK+/sabCTQ9dd9KECYHsYBjvAWrAjbA47ww6wK+wKe8FRMAYuhn3hdthP+vP+8AQcAE/BgfA8HAS/gcPkfLNYWBTGwVowHnaCw2F/OBIOgqPgEDgGToOJcBacCB+Ak+BDMAkehtPgWTgdfgVnwAtwJrwCZ0P6aG0OrA7nwg5wEewGF8PecDAcBofABLgPjoJ3w0lwBZwLV8L7YDp8Eq6Cz8P74RG4Bp6B6+CvcD0sY69XWBZuhhXhQ7AufBg2htuk/W2H/eCj0t4eg1PhbrgGPg73i78MuBe+BJ+A/4Dj4btwCfwaLoXfwGXwO/gg/BHugz/DHdDLm34IBkC7eSC0uysv95XgHbCq3CeIXsbBFn9ML+PtFr4e3YybPC/sv0EvIxedDOqHr0xaonuOtEBikERkIbKhpUcn42auP3v9PznZLrFJyRNvfv3fvsY/PlwzvsXnt0Rdwaa1+EmB9HFz1ZxT+969iXfsxNRYUjApOSVv+z/PdV4LeSck9/Xw7Pssi86ApPOsvIv+jkQinyNPV+TdyjqdsSOGayqt+3Cja9yZ5iKvKT/Hrb8NdKTdWGueYsxHfq/sTlnNmeHPdc5rVGL86BTl9uK3N27YwyPdXInGvGyZeXY/G5ltn2bMyx5QZqVVOPGR8o1SQ9m/+rsbN2T+jksdYK/Mv//WbD6Kepa1CjF/JkzC0SQcMU/NTM/YieL+iphfVHNwqWMTTOuAmkrXEWMdr1pp6op2NBFZHcj/ZV6pZJBmXP5CrtsxpkybqbmvEE036ttePyFSP7JfgKzXTrG7oexk/lTKEzNVDvayCZGywUyVgZqfUuUic68OMykT5RczysNp3+4rRhyqLNQc7VJ7fiV95na4XybOaiE6UhO5RHkFzrduh2htqLo8W1L0TKyfGfy76pmg8mMq//LKvpyxd/emwMznaktg7us=
*/