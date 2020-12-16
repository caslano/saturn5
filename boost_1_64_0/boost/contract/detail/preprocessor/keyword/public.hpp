
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMApublic ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTYpublic

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `public` (this can be
//               checked with `..._IS_PUBLIC` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PUBLIC(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* public.hpp
78SvyT1/bg0uvBhKwr8lPFWDHnLiRXXcja8/oRdSwHh+sXat9P5v6l/3dJ++4lpdzGDscdquSCX/zyOkviHnjj1+nmIrvfA/Xv3zOvSWNcpkXsH7PqtZ9/Mt5be1GLjUvfXmWz1nj/GBGLjXT93sHcKBWn3pavqvVT97/P1xnFhG6J5hveD/c/RTMvrtJeMc5NyAeri82B6583np8GJ4mh7pRmdIR4i7vJxFex6x19cAJpWg2w/up1t5mdzj1Sk9uDoe/ohVpveNOXi3DixrPRCn8qcz5exdtZMxi/03vYJnP+V5p+sLGvvqmTRJPevaXP0Odj18HLZ2e5bAq5flwd/WdIa6y6VPG9R8Tz3EeeZ7lDZ0n5/psuHGtlkc88OG4jPVeE3aD5ecet1Y4UstejZWPFbkEK/hPPxVuVefVqc5lsPiGzVobxonbzHn0Hicp1e4f7DH30OMlqpTXB4Vp9cxyfjnW7uacodG3F7Us1+04zc9PWvVFzbpy/UqTX/cVrf79JP6w+k74kqnjJL7E5/3mTOhpGclj9uPeAH31jH21/n/+Px8SjMY9xU8epk/8bN6M9VyvBrCK2ODc8FyeDiuzreWTuMfu+H+KhvEQG2ul/tV5+ESufzkNbhGe75xUf3Lp4fT6RBj+3sfXSJX1tD7h58S02u0dMQ5kX/pHvqxSmFcZV/+aX3KITzFmQv+je5L00eO0yU76YqRaeDivcea+MtmEfvidMkUWmIRz1OVF8LbI/Rmo+XHOHV+1DyHFjB/+Fdwv/HwW9kO08yjxGES/DTv92iIj3fy5XTiwd9dfwGNsQOWBO8AWqs+g94nzjiaMSrpOYk5rjOR5m/8RvA7BM2Vvq2jP9/6TzlJ+2ehGy6577Xf+ZcPg+c3je0Z+VydBrH3+N5p/inof8bxf7h5C98fpX+SXIyrwPSDB+SQ9X0mj7ip+7e3qfdusC+fzz3Ck2LeZC/sMI61tWml/vidfml3Qf8K1v2d0Z7ch3r0dWlxtdaKDls/g9ftbU40zFT//pnaSv01bFwon2njpr+ol0E86w2YtV1OFQaF8Lhf3aikc9yftsUrdKB9DDVrjJ15PHz4azaeC2fX4wt6/AjD5sDNvGq/AqyXk31e45M70zjvyOfCenkl8OcTehnq6WQinDqmVtrRru4VWY8v4+FBNblXlkZ+Q/7dM197jQPLB88Fm3cx+7cnaPJZvq9eqo7xTsnecktd/cm/5KWtCiWD/+6/mC5pP8mc6KQlOOcObLnQSU97BF2qz59KLZwsbx7n6B5rmcb3gjNYY/WdvmqMT5+j8WnjlLf0r/VxHuKsyvJugTUrOdh1Xb+U6w/RI01WhK/NRDdUh8vG9/JM5/da4fj1uLstn9RTrvOfEX2Fzr/ANR66Ji371kU9Sns993xmNM/4/PP6jmqoQh5YvAImwd2pPM+f8KOJ8R/IG+yDWU/nAaqc4b2Cfm87eUWHTGgJi+fALRwU/W7wzCBvc5HWfdH9Iv6Uo9tbwO1gLz74vZP8wU971YI1OXSIDnpdPVTFC/R/t9L0Op7v93Xw3i55flqfY6++56twvhMdBffa+W8fbL+DJz/bRguNwYdyu8IrYvGr+BWkH41xmN5Gxp/Nn7fbMjiS9HzCMOtXfoa+a6IewmL1kE4Of+M+pXxObAo3oWefVH+XYNxueIZHrvtu8/3qTk00UH9Z1MrrYlKilHWHN/Gdeaub8l9ub5Pr4VfoiQ/55UVqOtirz6JPKedvwt18L4vNULm/Bs9mCCW9m+JQJ3ON0QPqr/+TR12XdmZnKUym9U+qv5vBc6iwLmeVkHPFYlROv4RXPJGJpt0KE/ToBnRRX2rkW2s7eoM=
*/