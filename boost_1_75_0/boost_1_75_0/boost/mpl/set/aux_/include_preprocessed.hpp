
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(plain,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
Zm64VQHBTd8V7hdhij8XcWNaPTvXwfTQDlj3pSZl3pnc0lbMXf+iEkNctxELkLnQynMz5WDyt2AXxllvWyIZT1QzO8Wzch2Uu4Dql6T/7ex2Xwy9mar+qYs4lRFnLn+czvos6deCziaZYYRTr1bxCwIZoG7AX6nrnWih7TAyKiMeIeI8tgk2XWCXXvbwfFAZ82J7UO3I40qezl7yl29neVwTfo6zldBfH9GB5/uwjuNjgqZr4XX9Yw+sG6O4G0vxILjlqSXeNvoo15v9icndvfoTB1Pp7ytPOGPorLc6Mahe3JVjxFfoGoDRg5HOotBVoIB1UdtvtU01PKr0UKcfVdahbZsqd2R/WNe1kd3xVwdEXPZsrx6NpUd/sHeF+y+pJVe+sYZaJ2bRnnVoikU3XIxjx8iRHF1S+nx7D+zt9aPclO1hYryL8zI6dQXsiJHptc3AAtQ/wyQKxafdA93N4bOTccqt8APtl36ORxsw8pw0FioXR3nQSM/PgYz1tgzhfr+8r029OBnCOLA/f+X7IYhrFSKFaxXkgrsfJE0z8aT6RZhJHGfL/9wB9wGEtiV+gUYz8QZBNtBhViWf3d3SAyq97jeG07XnUacFiBSUDcVCYmhxSPlF2YpERYkpFvj0BCroq4/bHYfTnr4BzZuOPW48mrewblD9orv7HYskNvqx3i1BuZbjnaO/gwOH4HHPpHUuqaKMElMsqair
*/