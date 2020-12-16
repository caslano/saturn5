/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_09172005_1127)
#define FUSION_CLEAR_09172005_1127

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector10.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct clear
        {
            typedef vector0<> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::clear<Sequence const>::type
    clear(Sequence const& /*seq*/)
    {
        return vector0<>();
    }
}}

#endif


/* clear.hpp
Da3krTH4mWe28WeP85U1t5frs9qseymntcwfSUbqkKuNa+/m3zoKIdDeRTCfIOgaUE6WeMX6rbiyYp2ugRk3y0w/eD6UfJ2re2Qm8lXjHu3j4ithPiOtJ6lhno3Z+lZ+kcpoeZzqqJtdY0JWhHbdymaXpWwSVdescRdVN1Vnqwq4KGoNgtvUI/J9lt7FMvUu5k0N43ueZ11BaVmb3imC38V86QS9i+k3XsaC/dyuuQHj5eco+dkUxs/j+c4Y8DNT8QAL5OdK5FoSSu0bzs9Sb1v7BPJTMTxJR+eZfvIbXgbd050U068cGSQfv0Yi9a34mFdQVdhKfO4ZGKCfOBGfDNsd1I+y+6z4pPKZZHWPBfls9i0adF5FTXVQWW9TPkp13xUpH+n9wuXDuG5HV9YtdcI2r0lPusQOfn+6wDoU9obzx98nLPVURR4PMqhPqLL8FIP8prRC5uTZ45mbcRWHmL8V8WNwfjoqjl6S+j9nIl836vIAt/y07V3Tmh+j3Uow/bYkZrvPtrr4lunqW/TvgkHXPsgvX0LB8xwVV2+2/JmlvmK+qz9H937o0k80r92exNDy2WrUxXD+GM1lO/hU4+JT9umKjS+feiA34VOzq09te4+Nxqe35VO6ymoY8g18ShgYxidvTSURViPaG9J1HMesS0rMVr+9+viahpwqv7ahlOPqV/Tv3FafuqqcKA5+C2pnqTzOZVQX1pfKmqN99vrLx5dQ0DUrs/jTRf6cQXk1ufjjH97yjc6U13hb98kaV/XQmc5xVRMGHdu4qhNlf49R4IZNfcPfh9xC4dT67ZeWV+f5Bm59Jed7oET+XtmbMqPMjY6POUe2/0nmbzhjPnPwObg/lGs+q/nNONOSv3hfGgwF2uZ3bk32O/FnHE+F78PtRl4GO+ZFDVJVlM9FhrBDYuquqygy92wIfacrcXinSwzqbxRWeDfyTGWmcMIQfOX3NSOC60nnlJb302S9n37IXw4P9Z3vz1Lhuoje8wLrHo748lOgWLeBf68KKlOvz67eN1RHz8e3zLMDc2anLVk40ohiPGvGUqPDw/TgsrLW58xa6+DbKaFzge8Zw7PNyUaUcWp3jnGeC1zd3X/2MOVtEJJLvuocbXorvL6BzsjtftoyB9lsj0/xla+RTnFNeWFwGXzi4M8K/Gly9qemqqRtviQGj/HTRgT7sblH6BzpXZRhwjAHP6KM3btzTOvzowMxltN7hsZYvt14Ppl+LMqZtXDJkuy8JUsXz104h3cvjzfPuI8iL5e0waHXaHBC4H40rlFLnywlIeTamXWpoWdo/R1K2vUuvrY+Zh7sZw/Tz+AySugVem+ezblNLnbN2zMC29b8bekVmr8R2DnsZodbNJp582ku+et1Vug9kc65qWkudrlNj6ZsVQfCX2sHn0aRRr6rT9yqbfRH9wjPCN2rtvIZ0zv0Xq3PQExfQl5V/FHRo2jHqjMijIneO7Rc7uLk5jC+FLNfQTT1BF9CyuYesx0Lvk6ZfULr7I4MUhzu7g+3R6u+JMmXv/nX1/BJmq/eNtt7HGw3GG1XGNvcMq3aDpTD3WY5qD8tuzmpodfgXs6tDWNXt0xU61y4DiH3zFOhzzazbjSnOteNveH84rZpq0+hdSPYH2/f0Ptmt6Ewwt0f40kXTbtyd0brz7oR8ueg/BmBJMqvQQnUYflTXel7sEX8Xqd36SAbGf1CbSRzXm2LDS5e5Gtm/W1SVdA7aqNsjNR1TkPuN66z34avlxTtO+ou2zvqLod31JX9/Yrnyu5EZEwC/zkn2G7e9CWzpi2ekZU3Y0FO3uyFEfdjTkrw+ZBnGR/Xb6vyrHueyDetnzV9D/L1oHxdiGOJcC4=
*/