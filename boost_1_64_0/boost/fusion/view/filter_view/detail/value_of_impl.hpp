/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
BmGUxbHoDWmbST1gQkth2lBflcs/mnzKFY36WXiInk7gzGtgxrVQ2oGTemmo7hab94r7t6vtA+c/Ldeuzx72KhuqVXrUWs0XejT2pCWV3rWWrfotgbvKtzi68t0f1c7w4fE4Q7fUdw339TVGLaF1D21dy08rDj+QNe3nZmocJ6gdyD5tFhhradi7AVePM6+QtqgNIInhTfJ94FDG4HsE6Yv9GsfJ1Bg70MDWx+WanQOmClwpemdcbuDGQZlpp309ws3xW/dXGT7ZZg1z/Te82fyeOXYYeJm6VeBmcrpPf2JPZAZ7j2/m653Y8fzUjz0xf/jIgx+ycPShiw/rnVyhbcvG9/Dim/nYZsvLK1559e9UV30Bd9A6bzHic32RO3ls55Y/uTPQCikZVh8A9Q+76hb5Y2XZEKcw43QCub+YlV5Y7B0n+TSQ9a66WqbiVMGbAnEOWJyuNBDxPSu3/5l83lO3gYqzKz9zG2K+8R/ZHGreeZP34FOHew8+2j/SP3l45SEPPrJq8L7Eef294rts8h5CL03swbvCeIf7p6r/+pqndanz1op3ZnNTLDaK0fy3nBqY36nHVjZWO6TQp8x++LQpjQ23NIpvzbTGnqUhYGszwLQg/Da7sxKjMW+wM/bNMyfD2nc3wuvJ8N7JYZfOa2T8mq/CV7d7g50uec+QTzgj/q9cX2KnNkfkTgrx36gOUz3WuONxkzqcUjbDf3NQhg+2n01PgJjhGzeV4Tvbu1urzzL9oZVmf3xobnmOHwey7zv+/EPOVPsN2h+anv8+2ZR5cC4frsvjUhBxQZMXNHfN5B5J8jD0vERyEe2Yu8G4oVVEcRI5Ki8r+q4X7OXZ+BOJwIlCyyojxR42su9mS6XleEvHDtN4tiTHM+zA6O/ga8z4FhLfjwvX8qp6OHKC+mRtK2L6cV+u9lZ2Nwdj/XnklBneXTlp2nhy7JRpX7YxzTAYW+Id75kJeBU9ON+cncChZPj3S3PoId96W5n5jtkv8bY+/0qFq0kzu7t05gDCVUp6XvVBw+eTT2d6vVFGp6O90/3Hj+fAwpg3rY3UHnj/TlrewOQpuJy49citn47/dWzepuxfWvO2s5yjT9qRxzMGLpcmIBhxDHgcMgVFgc8oV9qEn+6tyypTs4HHd+5bY5fvV/t6gmeUlr8n2Jaf35vbwRuWv5Vzr2PyuyCOHT52jKUqxMPEw8bf2bU3NeacVuD6dlle63dWx3fuTfw8PHPyzA0yd/L362RvnX+3Uu34L9bzAJY/V9hZ5vh5nIrH96UNws7p7VF1OLNGLyRu9NUjgPp4mbY9lU0N3vEx43IL4YZuEEV2NClv2C51eELC+K66bHzzSy+y0yQUo/o1V/BCxiucNA0SLxS7qxUP66ybYp31WLeUulXfw7nNp7ntfm1ai7s4dyAcd3FAYbdx1Dz77jTml87S8nH5Lan98WgtknPx69f+uaJ8WeE/Jbw0CHc17vMscR2srRrGnMFUi1MduxljzK9aHNW9gL9puokrw2GkccOZFq4P+cB5Kefw/qLLIzn/sP9V3DOzE7nKKh1rX8aBWy/gT9vHcNQL9sA5rurknlg3MExbD2CEhk8z8OCjDtjGAYbJXROU78ccG/RGazpucNI5xtnpPRvNP7ZTv16To7IA/ActXK3BUE73+gyv7CJQTOM+F3gNf3u6rm8AfLK/Pf3N5bxm+6Pulm+oeLCKNXXjwk00xg0uO+b666aS0/bBe0WFm1bdxv7zzSWmvzq0I9UbYN/tbbeQWLvvm37Z/sI4zfHBmAvfkniNb9StaIz5Ao0D51+q/LyfqiOHzEW1HrJ9tRSm5007jTtFj5HY9qmTRx9CLwKqjwY=
*/