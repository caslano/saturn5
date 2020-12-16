/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957)
#define BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<transform_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };

        template<>
        struct equal_to_impl<transform_view_iterator2_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first1_type, typename It2::first1_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
E+O2nBrky5nBaL3f8fikfGY7smQY1T4Bj8NH73zMmYlxE/E4+Ltlb97LzcJ9xuHx6+zI42QGGJ1BmPbL+0fV+OzCygur3ti9J1k6LLtIQWaT8OfYwaGLyZKyNS2hRIFNxp/rfV54kSznK792g6G+Vl5ZnAuujKrCKpRu2YosFGb/s39TlJ8xMnyjOQvsnEm5MWTrYPTdJpgW0CVkKPcPZi7GXfZfouf6YJbC3pybxtdt5rfCPkzF4/ottT3IzL8X2jQ8nn7Weg1ZIIz2OR2PI+aNsuS+i3HxePwzflUb3ics4+dr2pka1i9e6xTPaWfC95c5eNxeelUwWTDMUdim7LT1ZOEwa2H/WLXayXuB+f20uXj8UOGkKe8F5q8r2Ms8/LmW5wQf7p+3Cf6nwJZq+P9evX1DltDCRMvSCmw5Hkv3eJRI9kdLE+pRvgV1LX2bLAlG9yWY9lfSlgXcIxj93MsKPI7a0GIy2cFWJvR8m2+jy+UeJfsbVkTagZM9yDKUcY5zikTTZ4eZMLqHrMRnhxr+I8uD0fX3fztoXZn759PahO+7q/AYlrU6hPunmLvFtNdkoTBnYeNSmnblHsHshcVv/WcdZw0zFFx/+fbHkE8buH/hJpqDGNc+7kQw1w6Tc/p6dXpOlq2MMzMtHk2WB7MRtj37wQ8y88EmmqWwui0b8vXnBKM+wLSUPTPPk+lh1mJctkn0Vc4T5iKs50L7wWRBMJnZywzv7WThMEdhad0j+XqIgxUXe6l2fTCfpXiYrM+iQvHjZIkwnbAjVZ0KP8OFyd5+9CjanrNWxr1MuebEWcOchC0vaVaVs4bJHoX/tvY+mW6I8Zx3Wo7h9Xxgci/zbffEkwXC5HrxIzprZKEwmfXAK3fmkMXA5F42tjllSpYAsxWW3G3mMLIkZdzLLbotZGkwvbCnJ460IsuCyT48X/EtiywHZiWs9uw+0zgzmOx7Gf+U2ZzZUBPNVZjJ9H6fyPxh1sJKfe32kjODmQsL+VQ8lCxYHdfzUAJZmGL2NcqGkBlgskf1ktbXI5sKk+ezy1bPMpw1zEbu5cEwd84a5ias2IcrPGc6TCcs1zKnOWcNsxR2ckVTT84aVlLY3I9bTpCZDzPu+9FuLg/I9DAXYRP/M7AbWQBM1uBVvzevF6SY94zw92ShMNmHjjdDFpGFw0oIG9fBdD5f0zC9sPX/9uxDlqyMc3rxuCZftzBnYf2KRu7jXJR97hkxeTufQZiFsHJBnT9yZsNNNHdh+65s8CXzg8l75IT2Ho3I/GGyfwsrlHnLmcGshf3VrAX3NhTmKKzLgNpFyAww2b8RbRLukMXB7IQNH/O4K1miMmdpq0u9yFJhMpfKjxIakqXDPIXFH/ruQPYQVkzU3t69Lp+XXJi8bje7Vr9Lposwvr+M+3zPjcxHsRa5LaLIAmFynwuOVy1PFgwrKvby5ffxvJdQmMy6bJtNQ8nCYTKzFfoDKZwnTGa2sZ57Wc5TmdPszoj9ZMkwef1dm/3AwOdTqW/QnU/NyLJhMrOv7dIXkGkjjM9ZydprZpCZw+T1MKr0+x6cJ0xmdi6gwT9kATA3YRfvHD/NmcEshf2yZ2UbzgxmLmyYp8deshiYi7DPA8YlcmYwZzluTxrnsgsm+zfNs9s6soOwYsIu1x4TynnCZNbd7mfxPnNgFsI2/FGW68uDeQmr26FVTzIvg3Eub9Mf8F4CYTIXhxMBq8mCYXo559qc1mQGmE6Y15dfJ5LFw+Q1lrd55ReyVJiVsN/8vX3J0mFFZGZ9/DM4F5g8E1lVskZxLkp9g97d7ERmHml8f1ltf5n3ooc5CHu3P7krmT9M9miTb/ulZAEw2fetXeeNIAs=
*/