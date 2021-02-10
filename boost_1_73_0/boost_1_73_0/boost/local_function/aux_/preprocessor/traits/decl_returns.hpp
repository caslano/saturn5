
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: pp-list of result types (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard


/* decl_returns.hpp
+1edxnBYob1MhsgXmVjWbU0/wAjmC39hkhWtUQr48SWSfFlfSz/+UZYuTX1vhsiXCot9rGSxtIzaPNXmHoRznXaV10Ns/zC8rqRuC5iNfICdpmiQLlzYxmIL8QKsTi59P6Tu6mBvDZNdPpe+cmfhigUTYLqUweR3U0KgN2KuMuysdXPpHpOnGNQ5crRXZJLjRcAGNCOy8rorhzk4VJ9qgZ4Zb/w3oWsClishyPhlnR52Fhbx7MzmwbBmqIrkYoFNdepIk0HQfNEckCjg/djpWlm8LnvqsOETEVOq03TUahvwLiYRnA409giovtRsIBQGISQR4dgjBlgoVZfWMTXsPsHb9lrBLDrqCpP9/OGK9Tof1agfiJ9CN+gzm0GP8RFDfPa0hsK1CUZjVCsz0NO+wR4we3XyknkE4HgvY8+Z67zIu/ZTk8t223d2NWXXt9felGzbBedaZHs4DTMaX/U5hSuIXD1wzIogcaY+ScwJASiXj4AE/n0tMCISbtz9nYOoBeTMEatRj4XIa8TH2S1EBr7diehyD3lwYbmy0TWYfCgg+J+9fBldhHlbKgt6uYNXuXzTJUZfFUZDUXx+cw156qzpqwfkzzAo+FA6jvGYoRudi9rsm1cimIUSdwVBIuFRkxvteoH6cPw7JGRH
*/