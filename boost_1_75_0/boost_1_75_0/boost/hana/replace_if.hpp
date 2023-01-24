/*!
@file
Defines `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_IF_HPP
#define BOOST_HANA_REPLACE_IF_HPP

#include <boost/hana/fwd/replace_if.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename Value>
    constexpr auto replace_if_t::operator()(Xs&& xs, Pred&& pred, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using ReplaceIf = BOOST_HANA_DISPATCH_IF(replace_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace_if(xs, pred, value) requires 'xs' to be a Functor");
    #endif

        return ReplaceIf::apply(static_cast<Xs&&>(xs),
                                static_cast<Pred&&>(pred),
                                static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename Value>
        static constexpr auto apply(Xs&& xs, Pred&& pred, Value&& v) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                static_cast<Pred&&>(pred),
                hana::always(static_cast<Value&&>(v))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_IF_HPP

/* replace_if.hpp
uNKMlOKXOtvP8LyHWvIx7l3G2sKMySGuWF4uFXFvM/Izb17dcwr3R/jJ9DpjvWavaUk61u/KT3ElGQsf+Air+2F6uZWmlxndDm384flCzH9yVRybsft58b7Sv7E+yD+bnmeMffk2xNOI7ZtrddyzjJwDS7NyX3XE8q82Pc34dcXLYZEReD541pieZHRtfSKp/yXcv+yauMcZ14+2kvyyH69vyZ9NjzLuhh8d0uwRXi+Sq02FGVerm0uGxDTB8qgx3ctQPmoRkKCyxvOj1nQnY/dvg4oPG7H+l9aa8jJ41z+fHXR+AK7/xZSbMb+VqMnzaO68zxfT1YwP6uFLJ030JeWXMs5WPtE8noPl4Woync/4wXFUgXEu7p/YZDqVESbPte9qiflRmUw/Ztg12xwUlIbtS6N/LdP/mJUfl0W/DZ6z44fMVX6zT+p6jpKmMdZD540c7nGH4WrVny/4xqv6pyEtS+lT19L39Ji5VzRTtdJvT+9SOtRmWpA6calBE7eIdR5eSi+6vLJ1u8OJBoXGOS81pJSOOKk88mS5XvSw4kGP+UtKaXfR8SePtmwyZO9Vuki+LaVN8SfGZmyYKVKXXbzit7+U/mZmP5do/y0iB23VgilppXSTmYVjPH7YJfo0almvrTml9NIJT1oWdkgUHbqZ1//101J64pq/urUaLBa1zfvye2R1Kb3m3PisN3vnGwKnOebyWrynB+0d
*/