/*!
@file
Defines `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTRACT_HPP
#define BOOST_HANA_EXTRACT_HPP

#include <boost/hana/fwd/extract.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) extract_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Extract = BOOST_HANA_DISPATCH_IF(extract_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extract(w) requires 'w' to be a Comonad");
    #endif

        return Extract::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extract_impl<W, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTRACT_HPP

/* extract.hpp
g1LB91wdbcr/9fg7tI3zvcomeMa+luimnN9SrW2qsuUVUySiCfiKfrHxT9tqKBg61S6EEo3SL/33m+iW8rzoE9f3UkHMH8Yjz+KU5ORl086TP+RGWsSmprVmPIJNWI5KtnZIXM3yaG8PMoiJOBJ6+QIACut3oRLPGQoKKC1JSPZbwVl12gpxjsAhDWeq111fGek7hBxq/Uw6c9TWDnyf2+59DHNbvEerXcIezNcmbpzsPuMggxLDnRuiabMbCRR3l1ckLUjmZWdh4j3/+RWII5avgOthcjbnKtJoByrilkJhJEseqG9wTbhMMFe2IrUCBg3J0Ikg9rcx/HnqPYUytAKXAQj/OpYrQvO6FxVGdPU3TU3E/k7jveWwFJnj40cdKSwKmw8KtY+DxeUYzyYpWORK7RzkXXv99W469Y+2H4yoAqJV3m5rXAe3f99Vd2kazI6ZmMrtw2YkCXcL5+Osxn0sSX5aUvb7n9w+9cqAb2hrLeW4vHQbbEHvRx8bXbaRVodmOGayiQgII1RqfDS3vDe1nsh233lgDKU05wpF1+5baWBkVUxdbMS1hg==
*/