/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_LIMITS_07172005_0112)
#define FUSION_LIST_LIMITS_07172005_0112

#include <boost/fusion/support/detail/pp_round.hpp>

#if !defined(FUSION_MAX_LIST_SIZE)
# define FUSION_MAX_LIST_SIZE 10
#else
# if FUSION_MAX_LIST_SIZE < 3
#   undef FUSION_MAX_LIST_SIZE
#   define FUSION_MAX_LIST_SIZE 10
# endif
#endif

#define FUSION_MAX_LIST_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_LIST_SIZE))

#endif

/* limits.hpp
kNkwiD6hM126miNr04ciPHQPzQWc+rurf4RfLVz5qtVE6YIJy+tVTCT6M1YL8F6qvB8MIIgxvx8QRnlL7t1Ika5jfiuijN5Es999MpdS8KxEuyK/wwap1kJ6DY80hIo4qB16ezBEUzejIMaXJ+oJ5ytChBSHUIk5Chfb76xbzPy+sn86LuaVVpXWFT2ynJsuzmsna2pCKnlXsUBFwFK6C781dN2hsFlT1tylfAmk2rXLbeFJXuyscsRW9XMj6KuOAGTvXYMAHUcVfDU2yRrqU6Z5LCraOKUA/4i3SQlfyISCKLoBT0Vyp0yQ36/hc4g37BjewYjmczpOidirPx+vzHEK3sc1CE9vc0E6HUrQlFfMQUopGdHrVwzyLZM053dXeeCu8aahzvjVExmbhtFds7WTzZDQiH/IdRb4GmgndWTxEbxKwFvmpEov+C4/oMppOM71IqVzMevSbeFMC1if4Oz4Nu8JSIQEanqaI9GKSUyJADfEoueD1Hj7Lq+12EfYhUPcBmtrABtB1PR6mJkeHoNJ+WwbCQfv2attfH7AXW5t4QAeq/FlirEOofj5v82h1jGEpFPf7Sl3bLP+D1eDcV/d7hr2Lvsbh2WF924qXvniKZa+63C4dJJ0gJ9URZWuhECr5JVKjJa+riCe
*/