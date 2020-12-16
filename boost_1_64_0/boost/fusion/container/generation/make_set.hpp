/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_SET_11112014_2255
#define FUSION_MAKE_SET_11112014_2255

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/generation/detail/pp_make_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <utility>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_set
        {
            typedef set<
                typename detail::as_fusion_element<
                    typename remove_const<
                        typename remove_reference<T>::type
                    >::type
                >::type...
            > type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_set<T...>::type
    make_set(T&&... arg)
    {
        return typename result_of::make_set<T...>::type(std::forward<T>(arg)...);
    }
 }}


#endif
#endif


/* make_set.hpp
ae8rEqdC9141+twhi457uZv3cLL2M03yE+mMISHxIIzf00sMzne6dv8Z2bbPSCUmSDjnWnn/5r7kjCWywLFvi5UDkM9x1PRr4npx6cext7azLaG5tCUcCmE7r9m2q7xZ1A+rJOV6qzxmhO4anWyqOL4/I03mOcslJXcSavOVWcc4X2XOfKVlTDLnWf+kfA2UfMXWVTfaSPq9NMAg5XtbqS1ftm+OSanEWkoyF2TkWfkOKPn04LuFXD8V3mPpuutCf2/gyjD8/Ilxc51FYl/b/Jw8MucSY2i7HF9ruW4CSPU4vpLXbceXN1lalcZcP2TEoNFJ148YPFIJaeJxjIM6oVL+unKNr6cu3UliTLQjNWDZskvsd2pKZj7t179p367nXg02oy2HLZKfpqT6UhbvtGKLb9jzk8D3sqQBsUNGjk7KNk+jEDIzPciLdh8xbFiZOst+OpB2s49Io31YcixJE3PNVTlezbXuuIeOts1TNqS0Lrrmp7R+xXN/pfKdSpef+PjR1w+8IX6Q7cRXIT9dm0l+dPE9ujSouN8PKIcS1/2Sac9jafysOXbtfaWwQcXzuph9lbnsy3FGK92f9jjOGBzHfrZt2uaybUrN8zLb28q4zKxXVLx2lrBsiOu+LPl56R7vS1tmzJPvr/J5oivH81dUfL8eZP8Wl/2rb9GqXCN7W1X+Hj2De6q7ixfiru3692uLjrJtJ+JcUMf4H2bet37Izc1O1npgFvdOX2X+tg8Svlmb2fzEr4uKoj9uu4kG4Z9s80uO3dR6afK6OvfU3VWtyQ9rXqS/jK3t2nr1/WfvGLXs5nuCxz7mH1b7eNXjmhi3gbuLa+Kurdtd/JKqt6Ubt9X/8fFObq+hzH/ixn/51L/35w1tNu9vE/TY0P7u4ta4i6NT9Xg59UYo8xeeujHy313WtZ5zfs3K/KKn/d312XTfV4JLhfgK9jogrKHGKgzh33OVGdInsjWWYSf8DHvgMeyHx3E8fo5mPIEF+BWuwK9xJZ7C7fgtnsBy/A6/xybs6wz2w7M4AM/jGPwZs/ACLsRfcDlexCdR6Tv5KlbDo1gdT2IN/AF98BesiY04tlrYGf0wGmtjLNbFG7EeJmEDvAuvwDXoj2uxEb6BjXEnXoXvYxM8ik3xZ2yGNSjP5uiLLbANtsR2GIgdsA1ei21xCLbDYdhe+nAeJEndEXVK6vnhY434Ker0gpyfLRiMWzECX8ZkfAUnYSnOwNdxFr6Bi3AbvoDbcSu+hUdwB57GnViT/b6NwfgOdsHd2A3fw2twDw7ED/Bm/BBT8ABOxoOYjx/hNDwk2y80SX0QHpVYmQ1wpv2LKocfgNHYDgfjtTgEUzAGzTgMp+NwnI8j8QmMwzdxFL6F8fgejsWP8Cb8BMfhaWxWTep0pK6nkBTIv+vJ+2Gq9HG8HdvhLIzB2TgS78IJeDfei/fgPJyDK3AursN5+C7Ox324EL/ERViXfT2EDfFh7IeP4HBcguNwKabhcszEFTgXH8fnsAg/xpV4FFdhTYl74o9rsDGuw474NIbieuyFG7AfPovXYYmcrzKS1OuwT7V8/ib9vZm4NtXrMQB7Ygsciy1xPLbGKdgGp2I7vB/by3nriC9hEH6KnfAYdsFvsSsq5dINQ7E79sQQ7IU9MRLDMAF7oxn7YCb2xbuxHz6A1+I/sD8+gtdprgOpy6GOp+J1YJHjnILBmCvHm4eD0Yq34lQ53un4CM7ArTgT38BZuBtn818Z3oGf4934A96DyvvvXqyLhRiA92M3nIOj8QEci0vxOfK6DDfjcnwTV+C7+BgewsfxWyzCcnwC63KcT2J9XI2NcQ22x2LsiGulfGJqSD2P1P8o5TM=
*/