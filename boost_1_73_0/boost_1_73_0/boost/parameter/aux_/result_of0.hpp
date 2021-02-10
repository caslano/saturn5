// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_RESULT_OF0_DWA2005511_HPP
#define BOOST_PARAMETER_AUX_RESULT_OF0_DWA2005511_HPP

#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/parameter/config.hpp>
#include <boost/utility/result_of.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A metafunction returning the result of invoking
    // a nullary function object of the given type.
    template <typename F>
    class result_of0
    {
#if defined(BOOST_NO_RESULT_OF)
        typedef typename F::result_type result_of_F;
#else
        typedef typename ::boost::result_of<F()>::type result_of_F;
#endif

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_if<
            ::std::is_void<result_of_F>
#else
        typedef typename ::boost::mpl::if_<
            ::boost::is_void<result_of_F>
#endif
          , ::boost::parameter::aux::use_default_tag
          , result_of_F
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        >::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* result_of0.hpp
5xXaT6Zgb0EhUFeZnNSYnZXRCc87zhmZgOdUOJwKVukPKQQ7TePLQro5s4jq5802j6vK2wac0rPNSMeJq0NrrmxcwY6p1S4D0qPLEBRUdIKJB+h58M4pg+Y4RmmhLLWfzYFVXZtENKRg2KFHyPdH0xnDF8eHGOu+OjxkoQca/HWGidDeBmBdGrx78wY4PWwk+XYbCe1Cq0nHk9dofEnEXoD7oVDYTr+rm1ejvW8Lr+XSWYD9XV2Mnb1G1euVWUCpkZnvEx6g4hqbr0IIAecG87lKcgMb/8Z8PGGGE2yxH+qymeyZNtiJU+5Ppsw/87mICf52+9zFzm1Ygq77AdaMOtNsOdwBUAIQfMTgBBHrYjSHrWc5c+4I/85KuaVOvkjIF02r7082Z/FH4M2duRhNOPgY7IOxmdSlCJOUV0ttwmlSuWZOooN9n8wk1/MOzcTPRcHFQjGeJShRYgICp4HVXXjNPF293uJc1WzKT26GKAsJIxgTgKTqEkdnhm11O2PtfouTX/LAau1NyMRMmO4mkLrAqS/Q1QATYGx78QbcXS/VvHR2eML9Epp7Q7ZeE+a3Tj9ssUC6gfgiRl487lZiJRwdaYYjIE6mAM3ThXOgLsJ5/DvhWdSQN2TrcXjfMNRvpbrmUbjqn/Oy9wYM
*/