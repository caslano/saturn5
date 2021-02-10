
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_2 1

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
        cat_to_comma_prefix, tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(cat_to_comma_prefix, tokens)))

#endif // #include guard


/* is.hpp
J5GTrDxKlUEdqu1bl27J/664sXXT5bpcMtuKrfHdNPCce0TjeT8axYNRPKVO5yg1WiS9kUXjXyEQ1wbtWdpfF+j58ZDXuCX+mVCB54W5mxeK141AiJeVtGIlWxsULa2ikyXOA4nJudyBHnioLrmHHlPkpuZHii/cjZi30CFYJ+dNwU/OHMzT9v/Tsw5OwhRxuE6qfVG4vcxqVVA/4EQUVm5aLnVlF5rQNHx2zRHWIfe2GTTrxg2zTCv8U3FX0wrtlRWIGSP6WAMp9RqhlzwTODCdjLHzPCOWOPxKn+Jt6gITCQvHCEJuIK5QNa7lXSpb6hxz8019tMmOoBhOwsEBl5fNgHJqU0y2Do3VJVtwr+Ckgs0uHVwthKpL7fAobUl0bpzikKDTwhIPrrJYEhrdaO8d2jeTBs89w4sCp4wuqX5bzbaaJGk5fXV5sAjgWa71syNP17PS8PIenRSsThdZ9hFAjc1dQEoDz3N6H9BqJxFT31RoQpIOvF5bLirQjmPnyHCEO9e2cDsOAPwvN963zm2rgJ1Xi32bqqVOwX2hjEW97Tr/BnEpTvYnnO8gxv737vJwf/IMw2ncfXV0l49RIzPXRLuy2GrWiiVS45LWCrW+ZK6ZOEgUDJLTDAiNgUqR1ZXFi+Je6MoQ+eZJ
*/