/*!
@file
Defines `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DUPLICATE_HPP
#define BOOST_HANA_DUPLICATE_HPP

#include <boost/hana/fwd/duplicate.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) duplicate_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Duplicate = BOOST_HANA_DISPATCH_IF(duplicate_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::duplicate(w) requires 'w' to be a Comonad");
    #endif

        return Duplicate::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct duplicate_impl<W, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::extend(static_cast<X&&>(x), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DUPLICATE_HPP

/* duplicate.hpp
37MrDhbNQej0ShosCgJOPC0sv6SdSZ7IjImyAxIQXqMdXnbLTsw/mMfkpqCOVidk0mPqM5ABw3dxZsGSzWNnJrclFAJb8m/p/T0vWOpJMEM8OqLGEo9PIxW1yvwDcmwkno1eRrjB1E7o8+Q4Gm+tcZIvcqAlCvgSL9L9J3/yYSpCjVRx2Di46A4pJWmNex+7p4PLsQZyJV2VKqh4m8JMEeQj/zTuzw6cGjQNspzhNaFMhnylrtiXL8kqK82rP7I3RjXreqOetKFIw9fGQNpBpf+/MAtgB4ZGyIER+d1CyggsAO9BE5wlsOBG4Eslb7seGFcFVmROKk5MDOVt0VkpNtFdHgwpnEU0fIJhgEsuMbVyA9jg01JX/tERo4uxJ6X8ojAIvLe3/nXcbTqLEk5VF9waksyi5JhMoSa5buQ7NrT4114DNHZL4PMQeEgXi5lrJA4yi4fsdQqrwFNHXMkCyS0RebGsuQjwRVtf5nFpDsr7bpH7XeIpb3sYT+d6wCtdrEKGM/lkiMLSuWaPovT+l8n4FsbXh4jmkLnDRCUV48XTtHwr2CgOXgEdJjPGpQTl9AKOoIXQ9U264+pG9KwYS3FnGAMToe0LmxiSb6srBgAayQtBzzuU4KMPOPElcHmnh+3Jt/SNSbnpC/w2
*/