/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOIN_200601222109)
#define FUSION_JOIN_200601222109

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename LhSequence, typename RhSequence>
        struct join
        {
            typedef joint_view<LhSequence, RhSequence> type;
        };
    }

    template<typename LhSequence, typename RhSequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }
}}

#endif

/* join.hpp
2tcUdMF4rIiLsRIuwyqYjq64Bu/DPKyKF7EaXsda6Eod1JbrOfdjU6yDwVgXE7AeJmF9uc7TCJ/BxpiJTeX6jge+is1wLzbHA9gCP0BP/ARb4klsjUXYBm9gO7yN7bGSC9sMHsJOmI+d0bki7QB7YhccjF1xNHrjw9gdo7AHzsKeOA9747PYBzeiD76K/fAs9sdvcQAWoS82pL0MxGY4CDvgYOyB/tgPh+BQHIqjcThG4giciSMxCUdhMo5Gee+3jH9JH2fy3u84pquP8eiBCdgDE9EX52AkzsXHcR4uwWTcifPxDUzFPHwUD+BjeBAfx3xMwyJciNfxKaxFeZZgB1yKfXEZ9sNn0B+XYxD+BSfjCq3fk/EvsYPJdjqW6erhOGyN47V0Mm4l9DBJN1H62UnYBYMlnYUIlHQHJF01jJR0IVJ/U7ENhko/HY4DMRKDMQojcBo+htNxGUbjNpyB+3Cm5FvoJGNAytiQ5Gvtz04U7xfkve2/YwtkQvbjgOOxAoajC8ZiZVyA1XAzuuGrWB1zsA7+hvXwQfKrjx2wAfbAhjgYG+F4bIJPoweuwOaYhS0wB1viYeyAX2JHvISd8EfsjMpyrq0oY0rKWJMsJ9c0Wf/yrsiB1dTlHISt0A/742AMR39MxCGYisNwCQ7HVTgC1+NI3IKj8GUci7/iw9iUzB/BUTgVYzEUUzAMV2I4bsQI3IEz8QTG4k2chVUpexzWwgXoh6n4MD6KT+BjuBofx/X4BB7AhfgtLsKruBiV860nsSU+hR1wKXbBv+IQTMfJuAbjcB2m4AZciDtxJe7C1/EVzMV9eBDfU/LF/diYOn8fW+BBbI+HsB8eRn88giPwGE7ALzAST+Mr+CXm4Bn8CP+Bl/Es3sZC9KKf+gZ98ByOwPM4Cb/DZXgBn8WrmIlFeAR/wk/wZ/wFr+HveB1rVmZ/iPXxV2yMN7Ez/oZ+6OTmlDYRK2AoumA0VsQZWAmTsDKmYxV8GxvgAXwA2Qc6NcTa2AgHYBMcik0xAJvheGyOwdgBI7ATPo6dcTF2wZexG76G3fFd7IEfYU88if3xWxyAv6MvDnJl+8AIHIqv4jB8C4fjfhyBx3EknsQA/BID8RKOQ86xncZjewzCbjgB/XEijsJJOA6n4DR8CBdjCK7CMDyJkXgWo/AcRuMFjMGfMR6rcgBmwTo4G7tiAvphIj6CSZiI8zADU3ATpuKL+DjuwzQ8gk/gJVyEraqx3eBwfApjcAkuw2WYjk9jNi7Hg/gXPI9/RWWs21Wo9E/RTjJWKm6R/p9s5Kt+jqsq0c6wUmXWN1bBSeiG8Vgd52MNfAJrYga641q8H5/HOijnQTL2Kf83OQ+aJf1+InpiEvbCOTgQ56EfJiPz43l7Gd8UXGU/Ut2aTsa3lPm9ia3xbeyBOWi9ZwjDcS+m4n7cg+9jDh7FX/AY/obH8Tbmowv5fSjlyHSWMUpl7NJMQtnPZsj3kv4uajmGoCcOxQ44DPvicJyAI3EaBuBcHIVP4mjMwEDMwrH4Bo7HIxiEJ3ESfoPB+AdOwcZK/48tcCr2wFDsi+EYgBEYjpEYg1EYh9NxLkbjcozB1TgD1+JM3I2x+C7OwvcwDvdjPH6ACViAifgDJuHPOAevYzLexhRUjqvnu8h+BhtiGrbHJ7A/LkRfXIz++BSOwSU4GZdhDD6Ns/AZF7nO5CxjnMrYp6wna9u7LOvpbWd1PeVgQ3wXm+M+7IlHcQAex9GYjxPxQ3wEP8JQ/Bj/gp/g83gC38OT+AWeQqUQX2AT/BJb4j/QF8/iI1iIUfgNJuI5fAa/w134Pe7BC/g+XsRDeAk/xB/wY7yCJ/FHPItX8QoW4VX8CW8=
*/