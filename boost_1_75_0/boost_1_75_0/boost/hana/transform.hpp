/*!
@file
Defines `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TRANSFORM_HPP
#define BOOST_HANA_TRANSFORM_HPP

#include <boost/hana/fwd/transform.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/fwd/adjust_if.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto transform_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Transform = BOOST_HANA_DISPATCH_IF(transform_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::transform(xs, f) requires 'xs' to be a Functor");
    #endif

        return Transform::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct transform_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                                   hana::always(hana::true_c),
                                   static_cast<F&&>(f));
        }
    };

    template <typename S>
    struct transform_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename F>
        struct transformer {
            F f;
            template <typename ...Xs>
            constexpr auto operator()(Xs&& ...xs) const {
                return hana::make<S>((*f)(static_cast<Xs&&>(xs))...);
            }
        };
        //! @endcond

        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            // We use a pointer to workaround a Clang 3.5 ICE
            return hana::unpack(static_cast<Xs&&>(xs),
                                transformer<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TRANSFORM_HPP

/* transform.hpp
oSVuHrPPOsHJJxAiPo7FSRMi/shqfB+GPFxzYcuGhV7ELJTwsRVptQisSHcBsiJRYEUOhoFvZKfXw6lXXayw/312eScuCqnXF8LhqjkI3Bhrkw5PBKHP8SalZTo8j5VyR2Xluc2B5YLuILsCfEAZ8OROUIU9j7MhQ8ZOGgq9ciWnbZGLTRAaGI+vn3y8ws8V8vEJa/gF1UPtsrXm5wpSeE7JnWDEmvU1ge+5BxOcNmK+lmC+ejTgyyDmc+80QDXuHK6UtQlFu0XdDWysPENB8pAPz9Z4IP2cuoO7poFszGy8+VcI/uCVdGvcWipu7Wy3+tbGc62ZmYYxir/voMmCpc2/JSxtvcVgZuNNCnu2sy2cu1IIUnkl/P5G7oCyvgi/tsJ+w697DAkPMeRsSzjKX8QdaGa5FwSEs+CZEccQd8jcc7q5XxZ4gf2f+nVk1r/2q7Il9Oupe32/VtCcFDmt8ekIawSMLtsH3W7MZB9PRyoqd4H16wxoXrdQWL+ESPnUR0G/KS22HVjz8CoFh6lsWClnsqGXp/Bb/C4w4EXY1vxTJ2GysWPhqaS+ED/NGi5NCK1hF8LTyHNQCF3FE6i41txVzm6bPNk/ZnIdHk7oyDvwifZgj4S8KKFygb6/gAUVE5Gxq/1I3zGWCGGVOMhZFxjMMD8YzP731eeKzDO3qK5hJJYr07goxMElfrBHVtpojMpguRTenXC2A95y
*/