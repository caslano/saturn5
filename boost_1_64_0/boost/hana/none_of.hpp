/*!
@file
Defines `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_OF_HPP
#define BOOST_HANA_NONE_OF_HPP

#include <boost/hana/fwd/none_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto none_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using NoneOf = BOOST_HANA_DISPATCH_IF(none_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return NoneOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                                           static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_OF_HPP

/* none_of.hpp
THjfvcfGRI/aWEetHXDjzUIgy6BuDyRVi8JPyf2+og6k9hGWw6m8yG0t7VRehuNJd4P9V3DNQJU/6KNp0lRHejk9IFyufKG6bWv5ExibUrtSsvzK4c1HQWyNzFnyWmwPylMzYcpVs3xgFZ8WsGFL7oxx6Pm/UUk3W+3Ihgld+fK6j11rhaFl6xZUzikJoZT5TbW9aNNtl69LOHrp8xHNUcCnsYpz0TEm6Nx04LOfjVRhtLKA5BzPjRyGm5KcBoVYyZthZFaCFjeKxFK9c7tKbaoItAZCkvangWNUxRfLpGYcBueQGy2t0VnSos8WXBFyBvsdMhae0FndZAHpv910Aueh26kkBtAh8ArmBfuW4TUOi3TRU7L2EA6IBHyaFkynLzt+zxvzDOTsPQbsQM/o7SximI+s83iJS1KvIVt7kVpUODnG0k5jxsr0gI5zilrhtxa3Mu3wt6SfbVU/XMcD6ODVMeis52RXlUJwFpx4KegWyN921zy395rFXEg3CjqyoSGjz0ReaNrT/RR9gydWAk3gosY+yWbdmcWvFB7Em5QqEx7MENYUQLlBtg==
*/