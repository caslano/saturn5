// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_DEFAULT_HPP
#define BOOST_PARAMETER_AUX_DEFAULT_HPP

namespace boost { namespace parameter { namespace aux {

    // A wrapper for the default value passed by the user when resolving
    // the value of the parameter with the given Keyword
    template <typename Keyword, typename Value>
    struct default_
    {
        inline BOOST_CONSTEXPR default_(Value& x) : value(x)
        {
        }

        Value& value;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    // lazy_default -- A wrapper for the default value computation function
    // passed by the user when resolving the value of the parameter with the
    // given keyword.
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    // These compilers need a little extra help with overload resolution;
    // we have empty_arg_list's operator[] accept a base class
    // to make that overload less preferable.
    template <typename KW, typename DefaultComputer>
    struct lazy_default_base
    {
        inline BOOST_CONSTEXPR lazy_default_base(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };

    template <typename KW, typename DefaultComputer>
    struct lazy_default
      : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>(x)
        {
        }
    };
#else   // !BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    template <typename KW, typename DefaultComputer>
    struct lazy_default
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };
#endif  // EDG workarounds needed.
}}} // namespace boost::parameter::aux

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default_base
/**/
#else
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default
/**/
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <utility>

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Value>
    struct default_r_
    {
        inline BOOST_CONSTEXPR default_r_(Value&& x)
          : value(::std::forward<Value>(x))
        {
        }

        Value&& value;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* default.hpp
zX1gWPL5pdNmdXKfP8t7yZfJ76j3muL+/r0nDgxOTntk+feLZj7X8gn8Rql4dtxz0/2d83amfNLkl23n2rfoSZ+g8vmGT6PdcT17vn597U79bmo2LIS+QZXDyr8+9O5nb4aHL39zQk7aXVtOY49YV3MP9EkaefiG03M7tnng9iULnzyn2hzui/wfeO21m4Inlj06+4WKDlN787xU+d8+MKryYv/e76z98pM3E90SMRhqp8p/55Ht7/0cMmLxGxFZh/f1fP1uzhNVPqfzwh7qsjfj4vKzhS/eUtj8KfX7N7jbgm8/t/yGB6fc2nHSw749657EZlu5W8vm3nbuTLsD79w3JLTzib6U802qvq55L9E7fcboFf+oe5u1dYdojGd2KffHH0gZX+LxzUd7Nrf97cE1qzer9wzgfv58vQ1F1969csDB3OzAXp+2xGZC5b/W5rSWrZed7xd8Idiv8Qszqd8Ryv9NzTuElTRZ8+xPC3esPnz7We2ZvsrPuB1FYz/+7amR3z25bn29rW02qXUWuD/xyONDV3i4/zo4sc+TGZ/2ScBuS9V74XsN+93qPuaXEW0b7nm77ScH1HpTi5wUqn/JFxtc9c4LR18u44584zsvZM2txufFZugFWbu7R2yFXoH94FF4nawNmCxrARbAg/BR+Dd4EB6Gb4t/3JRt/zHZ1t/lu/rSu2vyq6xtmC/54Z+ymb0FNpQ10QFwpXEtlMQTLPEY14TMM64dEH+eyl+VdzJJerdLencY1zxJOG+T+G8Tf7Fu0i9Jf5Uvdl1RbjJmkPjDZK1FC1lr3VrWRLeDnWEHKe8uska5u6yF7ilrMXrBRNgbZsA+sla8L1wJ+8majP7wQXgdfBwOgNvhX+DL8Hp4AEZIvQyCH8Oh8CsYCc9p+Zc1yWNgABwLm8No2BHeAK+H4+FEOAHGwxg4B06E8+GNcDmMh7fBRHgnTIP5MANugpnwr9AKt8GbjGvA7nBeD00tBts48Xet+DPast0l9XCPtPP7YSjcIPWwCaq+CJa5K9uzau3ZYjH0s6LVqAgdQ2dQQBbPURH2a2Kvptuq6XZqhcjENk3s0cxs0Jzanun2ZtEoB1WxLzPYlhntyqrajhltxqq1FRM7sar2YVfaha1EVWzBDHZgRhswc/uvaGRDVe27xLZL7Lp0my7dlsum7LfM7baM9lrYZ4lt1pV2WaeRwx4rApnbYRltsKq1vzLaWul2VlFoCSqIuXqbqir2VAZbKrGhqmI/dRw57KaCUBS60j6qOtsoc7uoaciK8tBOdExsn8TmSeydzG2deqIolIqMNk0lKJfzx2jLFIqMNkxG+6VK5DGD8IQpQRXINxs7FWRFa9Du7BqbgppPzafmU/Op+dR8aj41n5pPzafmU/Op+fzvfDzQzD/x+T9PVLXH///Rs3/tWX5pCPMPHbV5VB5Xaw/64lLmZSTassm22v8q+8vDjfuzyE5mRrY8E/+qEfOU8kx8mpus9XX85qU8xyy2PxMfNn68/ZEiMemPL/15JuSOv6/xd1rTVTwXWu/m7PmG8+ckLVPU840GEUnb0l5KuGvq83e9MXvkWufPZ8yfPzh/HmL+HMb58yjz5zBX/5zqap9L/FHPbZw9L7LP40rdS5sIN87jym+yOX6Dzl9+g+4a+Q26zvLO7G5wG4wlHY9TrENBTudiTeZhjXOwxvnXNfq8q2HOVZ9ndW1+dX2V+dRiVIHC1Zyp8/lS2xXzpOZzpMb50UpU3Vzo7mjTOVB97jNX5jktxrnN35nX1Oc0zeczjfOYModpnL+sbu5S5i1dnKcMkrnJnVXmJM3mI41zkSXoONLnHI3zjTLXOPRUzXxizafmU/Op+dQ=
*/