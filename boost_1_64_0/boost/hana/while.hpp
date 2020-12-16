/*!
@file
Defines `boost::hana::while_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_WHILE_HPP
#define BOOST_HANA_WHILE_HPP

#include <boost/hana/fwd/while.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pred, typename State, typename F>
    constexpr decltype(auto) while_t::operator()(Pred&& pred, State&& state, F&& f) const {
        using Cond = decltype(pred(state));
        using Bool = typename hana::tag_of<Cond>::type;
        using While = BOOST_HANA_DISPATCH_IF(while_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::while_(pred, state, f) requires 'pred(state)' to be a Logical");
    #endif

        return While::apply(static_cast<Pred&&>(pred),
                            static_cast<State&&>(state),
                            static_cast<F&&>(f));
    }
    //! @endcond

    template <typename L, bool condition>
    struct while_impl<L, hana::when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct while_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Pred, typename State, typename F>
        static auto apply(Pred&& pred, State&& state, F&& f)
            -> decltype(
                true ? f(static_cast<State&&>(state))
                     : static_cast<State&&>(state)
            )
        {
            if (pred(state)) {
                decltype(auto) r = f(static_cast<State&&>(state));
                return hana::while_(static_cast<Pred&&>(pred),
                                    static_cast<decltype(r)&&>(r),
                                    static_cast<F&&>(f));
            }
            else {
                return static_cast<State&&>(state);
            }
        }
    };

    template <typename C>
    struct while_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Pred, typename State, typename F>
        static constexpr State
        while_helper(hana::false_, Pred&&, State&& state, F&&) {
            return static_cast<State&&>(state);
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        while_helper(hana::true_, Pred&& pred, State&& state, F&& f) {
            decltype(auto) r = f(static_cast<State&&>(state));
            return hana::while_(static_cast<Pred&&>(pred),
                                static_cast<decltype(r)&&>(r),
                                static_cast<F&&>(f));
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        apply(Pred&& pred, State&& state, F&& f) {
            // Since `pred(state)` returns a `Constant`, we do not actually
            // need to call it; we only need its decltype. However, we still
            // call it to run potential side effects. I'm not sure whether
            // that is desirable, since we pretty much take for granted that
            // functions are pure, but we'll do it like this for now. Also, I
            // think there is something rather deep hidden behind this, and
            // understanding what must be done here should give us a better
            // understanding of something non-trivial.
            auto cond_ = pred(state);
            constexpr auto cond = hana::value(cond_);
            constexpr bool truth_value = hana::if_(cond, true, false);
            return while_helper(hana::bool_c<truth_value>,
                                static_cast<Pred&&>(pred),
                                static_cast<State&&>(state),
                                static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_WHILE_HPP

/* while.hpp
PT6MyyxV4rtMlxdvuzUrwWsDvCSOWb38iNFTzxCYfPqllIS8ZWj7bNrMS18W01I27ZS00ZyU45bTd8LRXd/LcR5zMY3VBpnOeeqoNswY/SjHlu5++BU/vlo22wGcldqIsXS+0UsV6HdFLBDFARlTMOg3H7Lpg/Y7W5L/Hft71pGKDl3m0iHfiNkd4j7KKavHsSDoiQ3cMwZxxNbB3bZx5lIUDBF7HMaBIfxNbZzuSzFPDlt0aXDBmfqkj4l9GGwaH+61rOCMOGdjkAxE4WrijHhjr4XDPhRzy26L1hNc2CWMhz12UeyUOR4THfuPZwhc5iUQcexfbDpy6DzFzGGbbr4jJSp/nwFf3BHadGvaALMHGC8TM84KDsacukB/hktvtay4fXzvZoQW/gkC42YbRw67JzsY9QKuyIM3eQR0HRs3YOeB1ZbYO0y6GPWmAIsS39oPhK12wuUHiY/X9euSnx2PJ8+z64i3e7qNf7nRKCLu7eQzXQxv+XFIluelWy4/1jDqSKG3Y4SFrgpi4/7bfppL128eDON5k59wMHothK7wysBlCh1DRGycyyfqqQH0sstHpXmgDSNs+x4dC0ILvj4eBuOH/rvhYlTXyexuImZizqtzpXC6CJ+kIe5onH58qRJBkkUq9x24Xw1hoik8MHWEPk/Gti+SqsJeSdjzdBynNj9s1RuEw/0Y+AE36vTqal/5cupFNj7BTjUGq+2Jsb0sCcu+1oP6WmsQ63IXy+3hio7Qj357+B6ESCPo4EkXo3ioDfKgJe8hb3s4Fkwu8Jjh5ZVn2w0nvDobgaoNpN497+H0dlT4nN7z61NJL+Tm0+yVp+KJhO/oeOxqfZ3x6/B7Gos/ZeIogb87Do87O5GjfQc8j7TA73vaWDw/aDMr8Kmd8LNkJRH46bF46HXg70zujJd28nPJ/Fk+YKt8KJxPJo4mrRVzb0it47y0Iz5VxPn44FhsprwYY/OPHotNr5xLFWHfGcs3lUbOjKS6imwhUkauj8MjiDnG5w8n42X0/SuNTB1JwgOsvGvplUq1l+JnavZAvg7v/C2h6sgJm4xHhLn0nZlOrBv6aQA/6WTsGW83IeP8njb2uxTG4enjcC83OSzeCFmfGItH//cS+6SYq1Yy6VKulslRgp6KCv8vZnIyp+qDJyZ9i0wAse4bgxWjVUOOzXH4M9Z4rcB2mfSNyA6AfMLjsGJ8ITvj8KIBiIc4lIhHFgLkRxiD1dBYNz0+CUtHfCMFMk/z0QS8yPFz5WAwH5YMnt+CPXJfGAv1JbDbIaxUX4SFffHwGCyNMWycYZ62OiIc2paED4zZvmAdbPUAm3aYL1TDy8wceVoYF1YLqRzuSMd+lyrhPj2IwzQvmXpsBNo2bprjLuyJwe/kFM/BTyoZKxVyBWvRk8J4d4rjzHcoiJfTe4jzVBgrpxTsMfnHh7FsNSMZRc6R/WEckSqwqdtyQeJr/B6BHoKf3L/Mn8kuzERRbG0Rt301jDHn0VXkc7dwOTDCmdCmSyYt5K+zMXFtBOZDDkYwQp2nhW+2tqKYyysVaBTbE46FcdK+XHqan3uP3vSfGQ3XZqWeyyfgKMITmNIeH0Mac7PRi/f81/eHMXSEjH1CQnwuwA8rxk0EcYON9trQqnuYX28k8jrOJWC6PdvvdSqI425fw/iEMXT6JdzmZny2C+Lss9S+yRBGO2iLvph8ajCHork4ie9sDvq4jdY2DcEMZTcWeQafFMTRFVB/Rlkr8e5QoA3Ndtxfl3065xvpDGLMXEC2SK5mSL5iX5S9PmYxr0QnSqKBOJ+nBnH9Flm0WxfFOIZxNEYi91YQo/1tZIxNEGeP463DApNhx4ROky5xtU0=
*/