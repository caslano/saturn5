/*!
@file
Defines `boost::hana::eval_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EVAL_IF_HPP
#define BOOST_HANA_EVAL_IF_HPP

#include <boost/hana/fwd/eval_if.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/eval.hpp>
#include <boost/hana/if.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Cond, typename Then, typename Else>
    constexpr decltype(auto) eval_if_t::operator()(Cond&& cond, Then&& then_, Else&& else_) const {
        using Bool = typename hana::tag_of<Cond>::type;
        using EvalIf = BOOST_HANA_DISPATCH_IF(eval_if_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::eval_if(cond, then, else) requires 'cond' to be a Logical");
    #endif

        return EvalIf::apply(static_cast<Cond&&>(cond),
                             static_cast<Then&&>(then_),
                             static_cast<Else&&>(else_));
    }
    //! @endcond

    template <typename L, bool condition>
    struct eval_if_impl<L, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename L>
    struct eval_if_impl<L, when<std::is_arithmetic<L>::value>> {
        template <typename Cond, typename T, typename E>
        static constexpr auto apply(Cond const& cond, T&& t, E&& e) {
            return cond ? hana::eval(static_cast<T&&>(t))
                        : hana::eval(static_cast<E&&>(e));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Logical
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct eval_if_impl<C, when<
        hana::Constant<C>::value &&
        Logical<typename C::value_type>::value
    >> {
        template <typename Then, typename Else>
        static constexpr decltype(auto)
        eval_if_helper(hana::true_, Then&& t, Else&&)
        { return hana::eval(static_cast<Then&&>(t)); }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        eval_if_helper(hana::false_, Then&&, Else&& e)
        { return hana::eval(static_cast<Else&&>(e)); }

        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto) apply(Cond const&, Then&& t, Else&& e) {
            constexpr auto cond = hana::value<Cond>();
            constexpr bool truth_value = hana::if_(cond, true, false);
            return eval_if_helper(hana::bool_<truth_value>{},
                                  static_cast<Then&&>(t),
                                  static_cast<Else&&>(e));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EVAL_IF_HPP

/* eval_if.hpp
qROi4j6PbHBtxqhW7lUhnvP2yL7z87EpWrndQnxe8cheTXO9p42hWYi/62Sru04/p8m+MP5oU5O9O/lDg1qdkD2pG8PWnz/5e1UW8RrK6ercs+PUq1qdX0Jenax/nfiqKgttEWKzrs5jex5qVWUt+4Ww6PpS8YPPLpKyKjEC2SjHbhDlwuvg7+ZpsteF8BUe2dvW6bFSpgh3y2bK3P968+tfve/vqswK2eaHPbLp/TuSVVnvj4T4rq7cr+ZdjVZljT8W4oxOdt/lr2jt5XVTlyh7wfy3DZoMhep0sq7SY/tV2QhkHYpH9t6D29aosvafCtGiK/etw6N7NR3sEaLTV8omCCF+sNjboOngeSEms86J7ljt/CevaetwQYhsb49syo96wlVZ7YAQjZOkDFWLolCfl7Q6h4V4w8sj+9q3T1BW9mznr4QYnihlfsJVcHXKZ6gTkQvafydEhI+UTRKlVWtf+to31fEN/VGIK5RNFl7iR9mfWiFlQvTeEmKUMn8hxAnlWKUm+zti5clS5t4IT1/5yhPjMnnPTNOJ+4TQ6YQQ5ZDNu88j+83u7Ss1HZyuiGxdubVPNHxYyvB5UBH3Kx7ZU7ndw9p8flQRXbpyaacbJ2n7CLKHWe5D7vjqO99cps1niCL2TPDIfvGz44dUWfujinhWVy7vmYfPa/tvpiKe0sk+Er1xija+WYqY7e2RmXu3ae21zPHMS4DILtPPSztk0YpHlv2N7ghtDHMVkakr987urVs1HfwY9Jc6ESiEeP+F915XZcYFivgiy90vhNh+p/WCKhuCLMbgkT3wl6W3tfn8uCLMikf2/Nwz39XGF6WIT+hkTykfKNoYMIDtQsoeENBV/0v1Wl8exxgMHlmdpfj32rw8qYgMjmGqEOLTrc/ukzJ8lihiBtubJoR4xvb2mLYOWIQhL48s0esT67W1jVWEt67cD1uDd2nji1OEQSf7WW2Wp854RSz19sgq3vxFnjb2RMz1/R7ZyWmP5ms6n6WINF1ffvFExIg2L08r4jFde2PP+jZr65CtiD/oyl2d9LdCTZariA+ER/bc962arDNPEft1slMfzTml9dOG8VHm3kCr2qff0M4XyLYpHtn0D//NT5uzfEUs1skmf7BfsyvWAuiLrs5fBgf3aTYHsg/rZIufeqRFGztkf9fV+bXPvDhXkxUqIkxXbvAv33lOGztkD+pkE36T0i1l+Kz/z+2FQubQyTYEDjVq/YRst0426y/bOrV1L/rP5VogW6QbQ/7p6Dytnw5FtOjK+bRfzNfmeoMijnt7ZAumiyhtP5QqYqKuzo+daUjU5rpMEUd1dd6575UObY3KPWfIR9z6Yj/ziDZ2yPJ0sk+n/jpe68t/KdcIWYG3R/bWMykhUoaPUxGf05ULXbIlVZsX59113nWeQfaOl0c2b/lWH629Z3lOUPbQj8u9tDFUK+IJnewrmRUf1fYYZL06maX34GZt/Wr+89gbIXvR4JHtH/vtBK29FxQxX1fuU7kZ57R1gOykTvZGyeBVbR0+qYgMxSNbnZ6U6fExFfGArtwvhj/2da0vkP1YJ6te8tbz2vi2/uc1KoesXTeG7v1dM7UxvKSIFbq+bLj6wTxt3T+tCCfXIch9lm+asVHK8HkZY/DxyPYl/c3Tl88qot7gkfWfGNqh2aNXFTGBdU4f1+tUj53eDZuqeGQ33sqJ1PQFTvK73h7ZCz8/4PF7vqiI08Iju3/XB3/U1mGvImw62RsndmRr5yBkMVM8sg8/f4E2Dp+vKaJP15fv+AlNz4beUMTLujprp3xyoTbXhxTRxH4+6D4jn5yl6URAuyKyfaXMrZitf3pjnVbuuCL8DVIW7O7L918=
*/