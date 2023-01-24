/*!
@file
Defines `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ANY_HPP
#define BOOST_HANA_ANY_HPP

#include <boost/hana/fwd/any.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto any_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Any = BOOST_HANA_DISPATCH_IF(any_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::any(xs) requires 'xs' to be a Searchable");
    #endif

        return Any::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct any_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::any_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ANY_HPP

/* any.hpp
5DU8c4UtRtx+XZXo2r4IHtLAROA3YuXhEDcF34anXyg/fcSZfScsqvutGKuJP3+zp/CtVYJIbIZexcHX+UcOeJC/DEJKM29hS/xYmjc2Y3Oos34mLI2zau/nc/d3n8gd1z6iGpF9gLGPzWvSRRLnedQSDduo/6xXpEVWSRZP1kUUZJgd9IqzxtP9IA40HfJCeVQUjEN9aZvCz+bhpgPH4CfYJh9m/Xb7onhZX89ARTcTBS/EUzLM+hZp8aeznuyiuSfs1SSxTPzbGSFlmRS3mBp5ER+bg9UaWLQGGKD9Fa/S58jwwWsDki4ksJdyV0IH+dijeI19JZhgGV+TKBT7gjbKM6rDAKHRTReKveXywhUc3dPec2KA0IItrsmvT+THQCmjNxPaDBBeQ7NrvZsS+Ry4uoimepdRZvL3txUmcivci38Qqv/5Jze0BjuZx4JXmYTVvHSeyXiQTVjJHuAdLjzhLbpfK8Qrg/KoYnc1lHL7BOocrey+vBQ+0KJU6xezo9n5c0tqpOL1ejK4Arc0XuvT3mHsUBAL17PT0NhAht5bOzVjyYpAUmPDpjQx4Uvzz49tHyq2WCp/SJlkO0379bkvfdOP7OKf9Z7/hnNi1hifUTY4sfT1LC1dl3qY42DJojlTMFo+UkHX1SEoV4yWQmqCJvMTI5Nw44dGI5Kww7k9aVu2R6xGMrNkR4bwsAvC20+10W61FN9LMLfo
*/