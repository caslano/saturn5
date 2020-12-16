/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_0903)
#define FUSION_BEGIN_IMPL_05062005_0903

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category, first_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
4XaLPtxk8c32T3fp8nWOKeNfHKMyb9JXd3A6/fHY/hrRtY1IIvunIilDdnJguWy+zz6dcpuXyE2iIihzUVGfPXQov/8B2Rb3PyD51pf026Td13rQdSbJ5u3y5p7OVtP3EKdqCrQBecZCXz9HP2/qecsL9N++OVkld99nyvzRlKQvLi8sNnRycka09gzmVko/dA4dnj80P5Tut+ZGtNvZtLuNaHe0aftGtLvatLuPaHe3aftHtHvatAMj2r1t2j1GtPvbtHsSbfe1rjM7vnygdcsH2rjygdYtH2jjygdat3ygjSkfaGPLZ9hUv7GhDfrqdQyPX/WGhrb+mKP32I83HtY8+XqFoRl6EQjIf+520Jf6Fm36apoGPib3dS1t8SjoLG+vbdO183Zbo1+/pueRA9nV1ZUFWYa77TtoABFLt7p6b2qEC9rxjLdw55/N6Y0Ad3WdPG89UDpzNt/13Yth/X4Xy8bdq4FF/YBeTzF6p44uMjprP8h/FeisHlkdvRIYOfZZHTHcKwycVZdI8/1THRxQhMHaxjGQxPJ+Chjet/D2YXK7AHP64MT26N2I9rjHaP0/e005PoA55FZHetcm2pqk3VzSDtEE7SBvF+nn5RNk4g3JFGGusB+c2AEs63+3RCwuRmflhK55jYkYpFfqu5JrmvpTIf2ZlnnlhleqPx3desxjSH9ic8jLeu6DwvkiKJolB7SbTJm0x26uP8nYA3RozXLfM2SvbjMxSg1Cvf3Eps33j5u8j9iu6Zt9+QKsb6zh95mWtEGfltFVqiRCqH9H9u7X5P7YHDdMk6IQZm5te9T6mrYNc1CXkZ+JbhE79mvLJm8h/DhyfS9MhVE6+GqRdwFH5XmneqdMiDHvlBeJ/vqPgz7xnfJLR++UJRDvlK9BuvHXSZ93k6h8UNHoynciHd4tZQQEzyVW9g73JZJy5F53v9v8kryq68vwhMf6qkGQ3vFtJo66eH9Teh06svGEkawj28dhIA3t9+ppiTu6Nn/cTHOlp2OnX3j0TG9K0o9trc7LreigB9qpamdDW1p5ImjGuvNiSl++HFE0oz/FUy2N+Gza3LaWdmy9w/cv0CgvFu3k9pZGBnUj2m5V92f/Q/6UKZ+y32xtzN9tbt9+0L5p0Q7c/R6gXeC0fXP7D4L2D067+9w994E2+19G2z93r5HM23PaPe62f5QXwWkH73avfdRODe0IaE1Trm/O3+1evR7oG136gZ5BP9ml79Nn/nen/ngadNQRHilKzM1oHOztTdl1xTAHSM4FYFBnDHPzmxJmasquO4bZS5hHb5+y65BhbiExO6bsumSYW0rMzJRdpwxzK4nZNdWt2wYFzHIXc6CFALPRxSAxrBn/6bE3hGVRFXVc+Fe8ZqzRjxWj6YV6vAyesGnqY/XhnRi7GIfG+N2YuaqiS76Wtqlps0nLS3w27dSs5qOxZtHOX/XqI5lr8mxrFenNvXQGNOmM8+jCQdBOrNm0/aBd2HE1RZPP73UZbqZpVzfSI5uRrc0BzWBqH4/6OUn1I+nmmrZ3G3238nkzxBACjclEjKadOj/rm0Smq+P1DTNGk2BtnAnXrYIwjfL/t42vb6wLL5BlWB0srzxmaJyPsO93M88vTm5raZuc5+x2fAcPYhX/lcolaQ8MvFoel7Q79utr+u6m3O3nw7q8M1af9h0ZdSWt/9/yyrXxPmptRA7YPub5JgVxIHGOBLqRd9BP2XSuA1EBbDptA4z+8mpJ12uWdKFs3hNsJ5oegzTWGu8Hm+uLRrzdH003GIOG/nL+37z+kiIISr++4nfFbf2xunqeTOvo2lAeBdPJPHtn/+iplg61YGmwQINgbbEPGQe3t5iNQX8=
*/