
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#   define AUX778076_HEADER \
    aux_/preprocessed/plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
I7AcJmItHIlNcRQG4GjsgmNl+VVd5XpXrn+V5Q/UXLu/Jn1AE9ELJ2MZfBM74lTsim9jX5yGYTgdEzAZx+EMnIIzcRrOwSX4Dq7AuZiK83Arzse9uBhPYwr+gEvkuSLLsQCuwIq4EuvgKmyEqzEQ38dIXIOJuBZfxXU4HdfjHNyAyzAVN+AHuAU34j7cjPtxCx7GrXgKd+BZ3Ik/4C68iXswZ05iBjEvfoRFcD/64AGsigexDn6MTfAQtsFPsAN+it3wM+yDn+MAPIIReBRj8QuMx2M4GtMwCb/Et/ErnIcncDGexA34Ne7EU/gRnsbj+A1+h9/ij3gGM/As3sfvZHy5f2Jh/B6LYTo2xR/xeTyPbfACvoAXsTNexl54BfvgNQzCDDTgrxiON3AI3sRX8BbG4e84Bm/jq3gX38B7OAUfYDI+xJmoxHzNxpy4CF1xMebGVZgH38dCuBaL4Cb0wq1YDGVcOa7xHY8rlyTH4wT0xIlYHCdheXwDn8XJ2ACnYCt8E1/At7AnTsUgnIYhOB1NMUlynY8DpXxtTFIHKb8TFtfEwLyI1bEL+mEgNseu2Ba7YRfsji9hDxyAPTXjzaUvczzeXAk5T5ZGH/TBelgGG2JZNH+e1JbljLfzedIvh8RUoRcGY0UHMRPtMBQ7Yxh2w8HYAyMwCofgKByKYzHS/JwgV7nmlmtw6mH8bsE+ZXzNlHachV44Gyviu9gO50k7zcd4XIDv4Hu4AJfjZlyBe3AlnsJVeA5X4z18H3NR9hosg2uxCq7H2rgBG+AmbIabsR9uxVDciZG4C6NwD07BvTgNP8JkPIDv4kGch4cwBT/Bf+CnuBs/w/14FK/gF5iBaXgXj6OXcl7BkngKK+FprIXfYD08izH4PQ7HdJyF53ALnsej+BN+iRfwDF7E83gJr+FlvIHX0Uc5L2B1vIG18S764T3shvfRgA8wDHMo2x1dcTbmxkWYB5dhXlyDbpiK+XEHFsD9WBA/wcJ4Ej3weyyKf2IJGY+yJBbDUvgMlsaa6IN1sQI2xorYAp/B1lgZe2AV7ItVMQirYSJWxxlYB+djXdyI9XAb1sfPsQGmYUP8GhvjZfTDq9gUXdnPm2MpbInPoD9Ww1ZYB5/HehiAzbAtBmA7bIcd8EXsiIHYGXvji/gSBuIA7I4h2ANjsScmYi+ciH3wDXxJHa9TvivhKDvn1Wg5L8RhaYxHXxyONXEE+mMitsWR+AKOws44BgfjWIzDV3E4jsNcOU3j3nncffS4d7V5TyAp8u7//th3ptgO0t18Ty2+42mMfefT1C1L49+lUO99pHSSyz2epUVqRupBiiRNJC0kbSal3cuO48h+Zb+yX9mv7Nd/9+vf3//PL7qVrvqn0P+vjP9XlGVs76fcD1MWHD8yJjQoIioi3qUaf4tX+jeMfwuJDtL9OSia2tK3E8/XZFOcQD1v6iJ92hOl7/5VUkG5pjxDEHlyitqnPZisdJOxsJDQxKz0D3mb61PAXNdB0QlR3G/X9F2wwOGGSP1zBG9JXUqQXEnepFNKn88StS5Kaxr7C7MyDph5XJmTLINaDOOfunEDY6Q/P7+U5046zXsDrcqjAfTP3nuCss3tft5O2d/w3mB7ZdMxF5+FGI1HldnH1bbMb3lvjL0yWc0naWNzmUdc7a9nkp0yZWCnJy7TP5dtmWd4b7KdMklxT2M9N9sp8yzvTbFTZkzC0ymzam7765lqp0ylb/dplLnQTpnf8d59NmVKP94TlFlXyqwtfeot5RzVlPQ9703Tl5mlvnxzWfEk5RQJzLP0G0YZhoVqxyZxdO44LHXylHZQZp7jveX/oa9T3FM6d5SSOj7gS7z18rTbJzA=
*/