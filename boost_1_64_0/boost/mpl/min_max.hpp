
#ifndef BOOST_MPL_MIN_MAX_HPP_INCLUDED
#define BOOST_MPL_MIN_MAX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct min
    : if_< less<N1,N2>,N1,N2 >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct max
    : if_< less<N1,N2>,N2,N1 >
{
};

BOOST_MPL_AUX_NA_SPEC(2, min)
BOOST_MPL_AUX_NA_SPEC(2, max)

}}

#endif // BOOST_MPL_MIN_MAX_HPP_INCLUDED

/* min_max.hpp
WJ9H1UsEZ+v7hNdW0T4qyrmk+i0djrZiL9H4srhYdj8iG3UoIjZlWl8ZqDtdUJsUVDpafcQSx7lncmFOQGyxfb+J5VaN+U4vpKNyAAkBvQBIwYyEVCQEeEXUKb8Mehb+2mRhLJykZlw7rsTsPhG9LPptdoASoxfFI487i6LvLLUohkzWk60XRRUWBZ5S/EVRYPv0dc7gBgpz0vnpCASMq54RPFpvZnwiPZynlJWBgsk0MqOFSRdMvcQTguBFGLwihwdoTRUNv6R6m+MPb5p66jOcfuwNdbDONfMPd+Yz1fyXaKky07rQQCxyQTwsEL/6GjD7ufhpR7955S01DmqtQn7oOgPhdEClFqyDov8opUhcyzw1nG7t8aje0Cn5SurHhw/pno7FmzEOUmWTAKifqok+ONGrSw1BqUdNqeMhbVYtNvOvnnitDJjQO1gVjz994G/86jU+Y59y6X9n12d8kqPGJ1nGJ8PrjM9V/P7pwZrjszgldnw6OeODUnMejB6fBc/Gjs+VKdHj89ntv974iP9nIvJ2yu3OQz1fuJd2FGwPvd15QHe4OcAMnG9S3UFz5xTvh+Gq4/9vhTM/JQVR88PtaR1qRf+nhdgi11HOV9L8OEYKlTQ/G13zczWf/x7QI51hwu5cQMrb/YuCH8//5wrwT3N/d34xPBNR6x9YYG7WccrFE8S0fO2LbbrqWyqKZVrX6hbDR6NVIPTjqmXCYU6zt81yz8mA2GBLdhMs5oDMjXHrfOeNsXMD4Dlr9mNu9umPKuMJZ74qZmr2Tn1FXOpy7KfytFB6uK/LprPUNVsV1JfactpZW1x06Boaj9w/asVBJy+EBWU3OEVXvQvnCEeT43bXVkFLqonW4+T3okaKSfabTVwaHMbWfaZS3exiDWNE+Hj4BfaOJYZr9u/HmtkItbbf/AP/sosYgY0wKjb5IYVwnjkRqKyPPWbroyPzl+oFORrm5uV3RPvkHJq4yZMkSgmxjG/cJDpI2aYJKIAVDSmxlGLvNj7wFX1oP677rI+mO/YTtFqVLKC++XNcJkDTx0HIDdfjBsvRfyw3+89e+ZB7i/QxZOtcF9nKMGTrw1ed1Ibud3N//+P+bw6jD2m63NkPu6Y59CtZ+Is3lEL/+1JmsXha9p540GuVdwkVYY/5w5PhXErWVZaxfMZtzF3TzL1gd2PYBQ/d5Xjhkfco8k2hTUPFmDc92FkWnhW0aOG1gJSaqtW0E1F/H2XOFkoxmGFiUCOCE2VDPksmtH3caFff56BFpQMkdxxyl0punWGgDtkH8jBiXqFj6j7XvP/LN0uyqRqvIQGKH9xRG7YepQHSCEBbdNdnXcac7+w2YAJyoyi6mwD5I1ceruLyv4dd/O8mFBZloawf8L/KKP6XypTS8D8//0q3Un0O3RzD/O9eTW6Gol09pIOOc9x0XcDiFwYoU3aPKsP7Aks4J/lASYrj/7nE6d+GG6P4BTcF/KKqTahDeLDpH9kdLHEtbTQklSQm/IKo36ZGvp+i+v9eBuAPwbHUmXTpTLjhgZ3KHP+vrvYn3qhWSZu8CfbfgyA+mpy5jzHp1jSX4DeN9d+LjR9rw/AMyYcoeKu2/XtPxCjGezr4ok96kGHd4sg4QDpAkB7oFMXn74OoHVgxZ0s7tKM0njI2W8WqpPCmX4EdV5LZ6olPwmwV/Q/Yv9DCgy2EH3G6UtVLtlKYGqrBItLf/1pNjI+QxBH2zHv01tk0BJSs7Akv/fdH+k+9kR4asG/PRyx91FdOy4KEDUY/kyHzGFJFNiPIaxgygqIR2oPEzBnyfDRE9jgrzZ+20BB30hLLOdB2ZfCW9lBRmwsMzUuht6xhVLt6zIVEgHbZaJc=
*/