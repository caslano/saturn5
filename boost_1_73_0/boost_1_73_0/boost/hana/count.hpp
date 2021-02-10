/*!
@file
Defines `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COUNT_HPP
#define BOOST_HANA_COUNT_HPP

#include <boost/hana/fwd/count.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/count_if.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto count_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Count = BOOST_HANA_DISPATCH_IF(count_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::count(xs, value) requires 'xs' to be Foldable");
    #endif

        return Count::apply(static_cast<Xs&&>(xs), static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename T, bool condition>
    struct count_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::count_if(static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COUNT_HPP

/* count.hpp
bW/aMBD+nl9xKlIFVZr05dtWVWWBDdQOEKHrkCpZJnFqb44dxQ6lUn/8zgmsassGH2pE7Nj3PM/d2ee0RKZSlsGg3+31pyS6nd6Q71/6vdlNTGaDKc7ejKNrMvBaaCUU220YHn1c8+AIdjZS/wk27GvEpNS/WGK3WxPyDM0PUffY7xIJ4QXyTDqwG/IM7RpC1ioXbkzILqF755t7hA55T9wQZxDmkJEunkrxwC20ow6cnZyewzF2Zyc+9KgSTEJsmVqw8sGHi7SeueJ0tQoMu/SBWaAy2MqDBAMtjgcaIk4VgrkWXAcJvlw95FTIINH55dqLGRcGjM7sIy0Z4FiKhCnDUqAGUmaSUizwRSiwnEEmJINoPJkPR998eOQi4Y7kSVdguK5kCpwuGZQsYWLZcBS0tKAzhCN5KoxFwsoKrQLUZmBZmRvH4eSpNBroEl2kCxSiFri1hfkUhklVSgw8THViwmQTccBtXifBEczRiZw+gS4sWA2VYT44Sx9ynYrM9ZhLnCyqhRSG+y/eoJRKQ12CYVI6LsQJZhq3GcTr9PjODAr0WFjXGa2Mk3rkOn9liHl0LFlVKhTCPKBRqjHNPlRYnWVtXEe+kVjntE5w8K+tefE3Ba3QGTjoxjCMD2BBjTA+3A1ng/HtDO66
*/