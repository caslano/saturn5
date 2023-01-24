/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BUILD_CONS_09232005_1222)
#define FUSION_BUILD_CONS_09232005_1222

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_cons;

    template <typename First, typename Last>
    struct build_cons<First, Last, true>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_
        call(First const&, Last const&)
        {
            return nil_();
        }
    };

    template <typename First, typename Last>
    struct build_cons<First, Last, false>
    {
        typedef
            build_cons<typename result_of::next<First>::type, Last>
        next_build_cons;

        typedef cons<
            typename result_of::value_of<First>::type
          , typename next_build_cons::type> 
        type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_cons::call(fusion::next(f), l));
        }
    };

}}}

#endif

/* build_cons.hpp
GbJLpjIbssex0Y95ZNfYirco1jhQscY7pJifNPNhyJFSbxqKFIM75ya2yxFglzuPxXa5vWKXvQzgJSGD/HMPapCzwiLtDfKjnopBfpN4BZq5I6AJ1HlknM0ZWgRY+ZYEJ4Tr4f4vlxDotQBXs+SlN+2xgd8RGnUwLR+BZkIcMcbBwDF8drNNt6IfOVFYk49PjfOZHAAnNydq8+NVb/ikoYsF8d5oNJIikASLfSTMzSn+RSB962AsvSX34+oOGCJ+Q20jsM9EzmF81A2mq4sUXZ2h6Oqriq4+j2tg3I1zyd2pYxBnKT/xOHdkjOtxLjNaYGuUyFb8gR3M1u4GZZzL9kdDbhGAvWoWHu0ytGCC/0Yewy+XgKPAWWBpWlz+E5iteIRr1Rebpd0KQwfEE4bmRFd5IS7ge/7ongFxFFrpYJADw3Az5Ny5xPzHwrjKrpSoysql7ExBcyjV08H+WE9ziJ5GOuopVs5LF5menrvI9PTYRaanB3AS63QJJPfRc8/ZmedDJfPaBXdhietiBv7agc+t7dS1zkvBKmlEjnIsHD8fCWzA/8VaOt624TO+NQvI11dQFvC1o7GjjR3urLBoZL9MPxNMot4jlYXTFjULSlSkRLQE2v099o5u9AXnE5x51FpSnFy2BaBn0zUxCMNARwVajyvQ6qJAC3+Tw4xihrT874fhNLLzaT2ywpKyumGjeQdpg2aTJs1k7Zpm
*/