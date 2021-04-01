/*!
@file
Defines `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_HPP
#define BOOST_HANA_REMOVE_HPP

#include <boost/hana/fwd/remove.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto remove_t::operator()(Xs&& xs, Value&& value) const {
        using M = typename hana::tag_of<Xs>::type;
        using Remove = BOOST_HANA_DISPATCH_IF(remove_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove(xs, value) requires 'xs' to be a MonadPlus");
        #endif

        return Remove::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::filter(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_,
                                  hana::equal.to(static_cast<Value&&>(value))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_HPP

/* remove.hpp
SxAt4th6VZ54xWRpqwaOarqtiBzHX1jRJnC9+b5LP8IbBRYkggyxqPbGR302E9TE/EXNXee0e/BcNArx1DhXMphoqEJI6BMKuL4LOAWyQHUdDJoYobSDS4Ht1fkjuTHPFHmfDjK6IieM2g7Ks9iJ1cZBQGh1ljpY0eZhFpyRSArWtQTeIr/5I8pM9M/xnsmzKIy+a4+NMUzXW6v7H7E8XGlzUJoOLxf2+HrEZRSKtpgoOEntPO5JI6Ak7v5mMl7kHGoj+FdTZPkWZu2ypCgiWaOr/1a+RK5n0EGpB94DhgQsvffC/RNs1z6OT77JfCgbloJciE6A+H19xG0dCqCrEe7stHkVYyLbLuIi0h94x4h/vHu2MSKs+BNsza3PuU8KKaVX6AhF07Dpi9pWUsvTtBXPmU9NGJgZyYXfVGOVOFgDQlW5KwuzoaAayPFcLpyPlLAftkbh0aPq18yknm5Xq51P3P0gNLzde4RSFlwf/yyWDBcgyja7FhRNasegU4J5Hq/0o/GIcx2fTbEpCV8IuxydlHn6jbpcHrl30hk/c/G9LAR1UY1dNGs+Qw==
*/