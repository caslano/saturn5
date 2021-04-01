/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_10022005_1619)
#define FUSION_EMPTY_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct empty_impl;

    template <>
    struct empty_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::empty<Sequence> {};
    };
}}

#endif

/* empty.hpp
w7O2xBPPPxMT3vsZ7Fqrcfjrzp7hW73Lexj/D72cloFivt3/ywBBz63PB7nnvX/8SttFYiiUaTeVdPzAkbDQJkfQDPb2jNxXc0OAlp+s9AcS2hBqnW7esbhNW3RECOjFPRkwpdqjWHkq9d6E54aIdTdMWbfqDzkGBOX+rP4NzlOG9sn7sJXfdzYnNEKB03L33GVED2wBJizluD/e3e1E8tWBob+xg5Esu1dvvdcTT3MKakWeRXWwrJ0bAjxcbzcMJt2sU3zJOI5Yi8xQiedEodkGolsJdg/wETCCpUrrtoRxjmxviz1Xe6TC5V25heFN5h/GNl2T+9By8i99Dwok+iJ+c0+fjRx13xK0nVwV1wCTBLgbkxAaaB6hEyY9lPhg+hkwYZTcfWox8WDqi8T026/zV5wwipI7bVS/kfwuZfxMpi+6VXrgPoMsjnwu9fxpNTuucdlKAMSAxunFT0sUE95M34gI5qxoI9ItGXqUVzGP+UeeJXq167jE9Z956tiw/P4S4UBzFtA/Iahg+ZYKIUA/1rcrBe//qJUAQsF1skUz6e0C6D+fJW9XWg==
*/