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
nClnu0CgcDB7s5cLMtiK6H7O8VoPKd9RhOrab747Pe/YXJ2R2lQJe5ao74KYOfdd6PE4Vyv0DKZ31IgjWxTN4mCRpnHzpTl1k0JLqO8qMifwP7iNaUn4izQokcvuiLsenIsXVgJbcv0KEeHExkTx7+sQDAocEUPEphHs6Z9JtZnbiVepql0GvzHmykvG+mDVkdZFR0qVYJ+h/TXqFbN8hFREV4SZIoMVw5ZeBKi/IeIpBrT6XjiISvE1U1/EK+aofICq3JGYovyhL/0ZNnE4UTixCpEKMUsEJdEQkdqI/8uzost7Mpg2i5litlx2yg5BVUWAEFsdTLYzZlgVxtmpJylIPBsRXS8Z7k2bUJPo2/JVMQsa77RN/VSbMWmHKCsAjEduN8z69Y//Ka3XkUqrj3FYfd+gwNmuPO68kh/+E8RfY6eHjABoHaVK+R8i1FhctNm+WltB6etdxqimVv8OAdBy3FFmTguirsjAqCXmWHFp2HHB2UZXu4tEmC/eMUPSMStTuMFvgZ62nu1S7643Y31rs/GBSohHCpC1cLwkF/hNsYG9TqMZYKu4OGTjevyKS2s/wyHD++Fkbsz/mCTqT5qqtF2WnlWymgCwePrdwl9d8doiX9Wfw+LbtYfwJYokLrfCUhpy/vKpJ39HwFW4sKDgA/T1qaxHUXuKAiC88VjRLGuakFqM9oR4waN9f2Aac45ltxiq+ie86FI6
*/