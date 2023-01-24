
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>

// `is_front_macro(tokens)` is 1 if `tokens` start w/ `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT( \
        tokens, is_front_macro, keyword) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_front_macro(tokens)), keyword) tokens

// `is_back_macro(tokens)` is 1 if `tokens` end with `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK( \
        tokens, is_back_macro, keyword) \
    tokens BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_back_macro(tokens)), keyword)

#endif // #include guard


/* add.hpp
zPh/OBKf0b82qTucfS9EveA/6y6a2Y7WubiUaxO0tOioXVa2VtMfrckOLDXA9xJXNG1ylyOdTzj6WnkTUzS00GdYVfKhtXTQ18uzZAuWsophO60D5A2p9u1LNnUT4Cq0WuqjQLxLXlFQ6O/5cIlj8RZi7IjmexbCm5bQOtKpYas5flHgKE+arTIfspE01MD/q3kgsRd7XIG1/U1pDLkpMLPO8XimFmA2RE0zPKz80cVWIVFLbiOP6WF3istRm8/NKpVitFRPll1s0dP3rqN17tT/MFPhZ6sfA40Qfx+yGmdMTSj3FOIGHqd0xHpDnmFTe6WtQzaT+xDOM8uk+vefX0HKK0y7g8wKulpFB5d8AlVXVXizixE+1S024c0t3uZTwFpWtGjGFwdWIPh2t3M69KFdIP4ot0tCkEJr46bPU3GPta5thnGL+9ZfXAR3v1R8m4dIlHKevPXaUZVEWzf5NtXmIEM74miOdu1LSwdSx+4XA6GzuGMBS8ly6dx6pIIxk4X8oObjncPKHiSDN1ZI29KMXt4LUi6z/uIb9/fNC5KE9zYzajz75m5ntoy1++BPDWHV5M3l1ad3+kzcvQLRfbACZR7WffnAnSd/pQX3948Iy8i8e2sf1ZJ0RDeWW9nBLj4diIWVJdtsQtr33XA8Z8EMt87km6G/AVxXf7HH7DHHdMkFa9X+pFtqF7CWLncZucC9O51RIR/SYVAj
*/