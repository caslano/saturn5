/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_20070527_0943)
#define BOOST_FUSION_FOR_EACH_20070527_0943

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each.hpp>
#include <boost/fusion/algorithm/iteration/detail/segmented_for_each.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each
        {
            typedef void type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }
}}

#endif

/* for_each.hpp
ezUK/gxHw87kOwYeD8fCU+BpcCw8HWbA8fA3cALMgb+Bl8GJ8DWYCdfDSfA9eBasg5PhJ/C3cE3z4LvCvp/xfgJZeBR74EclRX136PW+0Onz9n/f3+3ueD8Yy7vBeN8LxvI+MNZ3gbG8B/TwcbvT/m0Tee8Xzzu/XeXL9n/Bj21ZUtIv4st2oxHwIZV3dMiw1KZ3a02fpk9jfXbV8z92oqWN8fz/K57t8zqSyUGGfftJJ44febLxxMkj3onEGR6PSex5WWVlwef7s01/f8TvMZ9b2+q5NdPwB3K/sbZzZhTdNlE2anp2PYO8iIFve0Z9WWW21A/2QlJZYFbc61FmQVlUHxkdqH8aeaQF6l9YjNkiP7P7PmF5pTVsMA5qF2QS+mV71ZU4qLHYEFvL4Byp1r+Km45MpoyKYBm5PH87yomljFB7nqn2DO0DTA/6NSmy2J9D+b7w8CHYH+mIHImcTX51Qd1wcrBzup0Rods5+yvWe4St8Hbpkak2MgrJ5rdV94b2lBLTQ3aIjn0K6SP9Apccaa22+vLhF7GnU9jcfR8p5YFfbh9pW3OPWNUP7Jp9pFAfbZafv9u1j3QLzKH9ku/TPpLrOI6+l2TYri5eHrZdjWtvqYNtbylQefaEvPaXnHtJGfYxEN5L2rIb95Lc927i3zNqionb0N6Q195c/Httu2uPqd8xxt8vGj9o8ahHOww4Z/O/rsvcfHZ2YntMKYju77Jnsu/xHG6NwXSvYqG6pOtljYWk/LpHy0/pjo+Srk7p+jeQLg3hnmGz92oBByhdqvagjoYDYD84Vntn44PpVJ7mdM317A95x65Sut7e6dgb0zyp+bMqYm/sWOl1nGKunaBYa7/WXl4anAJPkt3NybIPGAZXw+HwTe2hrdce2rcwHe5HeSPh/nAUPACOhsfAMYqxdiq8VHtpl8MMeA0cB2/WntotcALc3Dy2c/Tt2DdLOzoprj2x/4c4UP/L+2LR4j91ffY/d3+sseI/OWM/Ne2V7cxe2S+xT5bPvFSBrEQ2IDuQlH7smSG5yHzE59st/v9zSgtyd9r/f/jZv4Px7MuqPDevqKxgWkFeycn5xQVT83CVE3j276F0fke60vD+QDelyegYTDMup2h6Xvh/zf+v6RjK47QSI40KCewvpB7pC/vxaaPn4STYEf5sxMxtzz8uMe6P9gzO9cfuP/AJ8uBZM8viP1B/m5IVeiYYDLsG/6Zn1ND3nIB/uzTDhgy9jHtuTrmhT6QP7RL5CzR9ezI1OPZLfkWeFZc66mPslER9Zg3p1UV6Wcva2sxtnwQ531EWWx3R/aOG9khq20fukZhlpic590jaG75LnfVjdyT6M7nVF1aaninrmwfbbgvsSN6+3ylv58DNKSouKpijZ9xVvoZ9L9ZeHnyuzC0uygv5wqqBfxoUeIYMZOmzjCH1cR5UP5jPkN34nq+zB8Y4Ozdndpa/cGZpFnlbn5/fbRs8wxAojzE1JilYrxS4yaiX0s43zzEYeclnky1/jWNLuoIiPQeb6fhbQNdsjRnS6flX3zW2B6DDZmQ0Cjwyzxzb5fDbdraxHdZ7KP1jbGJ0vtzUu8pFx2oXfRbZx7Bt32llC+c108mIKTLfo99j9ImsPqN/zXJHhPxuybf9o82CZS6Hxljze5ZZUKrhxmURLLs6ynhLuto53lZ4jLe0GMZbegLjzYjh2pe6TkORTlea/eZ3GW/ZLn2Z4TLeMl36tzxivM2293dYl/K9gv5Cb73Kbeyb5Va4lJHvPYaYBN3nwvrzPfuzLBa/1eF94w7e+8a5LZ1zYmdjTrzaq2ymxhj2K21xNVo6r5EDKcO3wFFGabx78O06Oe8t6Xu7t6c=
*/