
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMAprotected ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTYprotected

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `protected` (this can be
//               checked with `..._IS_PROTECTED` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PROTECTED(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTY, \
            tokens)

#endif // #include guard


/* protected.hpp
VltYsCWc1HeoVpasp2Nqyv8/4VanMExv7T5i/49aIFlDXWqGvGcMFteGj/Xh5Faa+zxOrSSH6a1tr9Pw9fiMufCcVmwJ7898FZx9gTsHedcOYruLN9mk5srzrrXcl58tMoqGGKAWn6NZOplfBbxN9/VLkEslccF9Hm6XnGmNb/Rl25vnDDg0II5HU2trDtMW38G9YbB/JV95nnbub69ajHaP01tuw8PI2/HBswEXzVkuXeimnnO6f2f6VQyey2Tt0nku3/fHlYbp76jldXAOXhXlC6PM81CI/++rn1ku5PdMwsrbsPy0e8uB7TTGPP5mxlzXyKA//6y4fkhPrqLLCMwNL+JL8//2N1q8l7zur/c5RHzLR/He8qKTWuZzW9ORPcW9Ju3VTW1V8rMrpZyDWaXfMRu2THR/GvCU+u4x1X6C/KmcHo82wF80zYQT5sTDFh5Djz2UZ3309Uvxdni7LG2xk8bsybeHYEf6LdZTfQe/W2igvsaJtP5frj04zluuEm9a9PR8vqUfLLSOD9ViNnpjGV2f81kYktJ3XrdfJWd2D6c71G8sTfxfIf5Jn3Rnfv0/mvdBvP4k3r6uTioaV077iZfE7DyNteFV8QlyYApPVpBmoqW65YJv8PwC/h/5AT2XxZ4Rru16XQ9ObY+9w/Oax8C3YHwG55Ia613xjMlpsv5Lw3y5vZd8uP0k3fcNPnqbBlPfKz7BaSX121yrSy38chKuneGx9Ac39afpaJ9nr/K21m7yVThRLswf8Vl9rb34/nzHOSQ6+yQ9WDXa5w7h9P1wdh7tAY8vj9DzWs8v/Oo+cr/7cuOvS6Oqoas0XfOqcjF4huUCjzaOTmpHJ+2k2fBdir/tEcwLw02acmtw7kGvAs9lnSSnWjjrM95cztHtcnnB177zP7r/U9r1T2N2/Y07YElLWL4PF4+0XzFVfTWhfemg9W3pjwfqcBje9Pcn4c8yeqFHF9rANaf2wfm99TP4+j433Nvebdw/crf44z2hD1vhlyXmu4d+cb9ytMkOddwlub2qUXALfm4eai34mKb1aDY6fHA/e3hq4b3Rxgjbh+rFp+isNviezieM/Q0981PyaI99UzW8g9a5IcYXU8CdxnjAWndaThs+q+erDpYOpmfG6rlnkuuwoM5S/cY8anmZfnZw5lPfvFF3vaI2sO5buoumm0Hf/yzX3i+vpjLSa0AsphSvFKMWXrPPMpemw/1SNqkX2bGV+vGZ3XCw/Nigz2uM1qOQeW80/qNrxHqcfIANwdm72sWdwajk+zx1Nx7ljyvOzNFny+VA1nzqTHyH4rgDPtvpWijp3SK5zpuLsa4Qv6o9IrQAndrMWK/Qe9vVCX08U2zmj5LT1d2Dj5/cWs23p5nMayyunnRYjW43hm106DznouDNNJOoeF7v51X/bt1icURwHrJObRqztXH10g8T6250QrMVvENtGvQJen+gfrN+f9WCctJ65aADTn6pHvaqffXYdQEus78fQ582VHsNY50NC84Abwz4Rv/7D3sVh+Sn+mr2sfk94mP4+d60S+sU6ryEusxF18D/oqfDSXtSyxa5d124kMN6Z1IXW/FEbnWRzhi30DslabiX6EXr/FbwbhweJLGIcfjMn8fkaAz/hJOSV9Q/tI7J/Jm2O02irufRw9Ppg2if+ftpWkLf482atENOOtd3CtNwoYzm8R7NUNW+4Zd6B57rKuo7M2jMVji5fX6aX//3wk359pQ9+YW4EoeWgInhubhLH/1BHuc1UsGM8bwSnF+HQzKvow+NYft3cqG33jRNOfqs+vD9E/pL61f4t6vwA39dWqz3+j3sEcfjeiyX+unNVhW/N9VZfvr0TbUDMyo=
*/