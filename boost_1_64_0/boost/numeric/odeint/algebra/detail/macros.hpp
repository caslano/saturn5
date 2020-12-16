/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/macros.hpp

 [begin_description]
 Some macros for type checking.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2010 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED


//type traits aren't working with nvcc
#ifndef __CUDACC__
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 ) \
        BOOST_STATIC_ASSERT(( boost::is_same< typename boost::remove_const< Type1 >::type , Type2 >::value ))

#else
//empty macro for nvcc
#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 )

#endif // __CUDACC__



/*
#define BOOST_ODEINT_CHECK_OPERATION_ARITY( Operation , Arity ) \
        BOOST_STATIC_ASSERT(( boost::function_traits< Operation >::arity == Arity ))
 */

#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED

/* macros.hpp
2jfgbH5ZDqfft+LyPn+/Q8VTODt+oXitHN//gHsMX6MlMrdtfP5H/P4GcDY+JVLiEyU+g6/TFpnBNr/3U4xvgs9t8eqLjmzJ5ld92ZFWi/SfNB05v2X//eJr9P+x/O8btF/iYua35N/Bj+gfatnH71Q/deRpkv/VP3fkUsQHtv6FXzvyDmnfj/5A/xDun287fsvj+2e0PZkQf4SW68uHe3ImGZ8Uj+nx71fxHL4w6z+C70/6z7OxPOklz78e26Pr3/rjeLR8VcGnJu9POJ5H+88TeEXS/7TPk9lY+zS8ZPPbHE/2JPvzZa4nq7P2644nyxOP4auw8RVw2j6seKO4eNyN4r7iAZzOL4DT+QVKfKbEF8r5lcrxa358fLQ83ofT+wOn4+vhdHy54oXiNXfMr/T4+AXFE8VzxSs4HR8KZ/vXBRNwTxWvFPcn9GRO4jF8Wba/B3wttj7rRJ7MytYXgPey8Tvwq1r2/UPzSTx5mvQ/FpN68hhpHygm8+RDkr9Xk3uyERu/MQWuv+fv/skZhirfTu3R8olM48kRbP9JOJ0fCKfpK5zOb5yWuw+n/VtwOn5LOX6ieKb8fqHEV/B7SPtAOZ0nPtv/ZISH/Qnt66uFM3ryOFm/NZzJk2sFbqmf+jN7sjQ+gJEWL+fg8fmcnuzWtr+/5TyeHEPaZ5r5PdmO9Z8v4MmiLZjFzUL8+QRwOr5b8UQ5fqbEF4pXcPr9KL8vCyvfj+IhnK1fkcCPJe4vgvSV7T8I72mJrGhJP4tFPXmuZR9/Jot7UgvibfsTLeH1t19sjv/8IbyCn98evX7VUPHLeHIiy9/he5D+w3RZnJ+Q+t1ITzYn49P85Tx5p43jWK6vXJE//xpO09eVuPtwWr6C0/FtyvETxTPFC/jSJP8yK3vyscBt6eMqyL9Z+1bEyw8ZfF3isqonU7H0R/EY/qjY14eLV/P4+DT41Cx/gk9LvFbcrO7x8XfwiHimuKzhyapsfXo4bb+B0/kN8CmI1/B72P5Aa3pyNVvfby1PtiXrs6TreNJpi/i292993F+yfliygVL+V7xSXDbkHsBZ/1+mxJdwuv4B/EZy/8uNPJmLrc+3sVL/hrP4SImPFU8UTxXPFM8VLxQvFa8UrxVvFJdYqd/D6foBSnysxKdKfK7El0p8rcTLJjzeh9PrV+JjJT5V4nMlvlTiayVeNuXxPpxevxIfK54qx8/h07D+GTidn78Z90DxWPFM8VLxRnF/c+6R4qniBZzOz1fcbME9VDxRPFe8Uly25B4oHiueKV7CIzo/xZNRbH45fAlWPxjl0flDBTwm7f/B1qg/kPJNto1S/ofP2LavD59s7/H5z4pX8K9I+6Ls6Mnhw0UiW//5nqhf/DV+x9I/lh3gyQbwYyweHebJbaR9Iz0C7aNs/034Faz/+UhePi7h+7P1547y6PrOFZwdv4FfyMYHHc09O8aTfXGwPS3jx5oM9QfS/hWf4MkKZP8qOcmTr0VkpOX5BCfz9ucMvgGbv3iKJ7e27OMLwtM8Scn8V/8Mpf0TTsf3K/GpEp8r8aUSXyvxcqZSfofT9j04bd9TPIFPzPJfJb6AT0C8gu/UIuPHzvZkfjb+Hb4meX/zcz15nXy/5Xnc6xzpNxv/eT7ab0m8ucCTJ9j65xd6cg2Znx1c7MlSLP+Db83W57/Ek7nJ91Vciu+TvT+XeTIdK5/BryPXH17uyWks/7gC9Vty/g1887aIb/OrUXptkf2Tr1Xef8UTOG3fVuILxSs4rV/yePwAjzcFjw/gM7D5ZXBaPoTvTN7v4Dpef4jh97Tt68tXN3qyAHl/45uRf7DxRbd48hYZX1LchvERLXv/THyHJ7e07V4=
*/