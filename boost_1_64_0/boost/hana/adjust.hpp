/*!
@file
Defines `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_HPP
#define BOOST_HANA_ADJUST_HPP

#include <boost/hana/fwd/adjust.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value, typename F>
    constexpr auto adjust_t::operator()(Xs&& xs, Value&& value, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Adjust = BOOST_HANA_DISPATCH_IF(adjust_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust(xs, value, f) requires 'xs' to be a Functor");
    #endif

        return Adjust::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value),
                             static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct adjust_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value, typename F>
        static constexpr auto apply(Xs&& xs, Value&& value, F&& f) {
            return hana::adjust_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)),
                static_cast<F&&>(f)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_HPP

/* adjust.hpp
tYhJ18mNcthzaAgqTkUM2HS42OqzRFPPVYdQWMILprIcqnm+b2y7i0/T1IKCuVELoVczsw8u+wj1igKUjDgGOalQgd445kwyOZPVotGSgZFU2XG4tEKgsry2DM6XyM4r9vIUOlh4Xd68DFCgwQdFq3OY94YEzqAkdV7+Mv9TCY/PNGBvI+ZmP5rO/HTeBfyLpUs4fM/yjSw5TJC6P5LoKRJH0K8OwBlkPjOvFbiQcEQxe2tZQzklvN99xzC9H3rvvZZgPqTW1zU5oBp5/aUJYNU0jCy1Kg/AWD4buR3ZqQmqZq28nT4aLbrRYmd3RtHAxygElvjWejGuskDyAizwZGrGVUckC0Vgpk3nL6cn4SbAkaepogW7y5OiwTf5LDi4OUZwBo+lzqE/gLl1rKOdHkGzt6mJyf6QutM2PSgVR0AV+q9LWcVpJRrFbq+whk6VagriMAWWyXcu8baGKJlhYXmPgWvZPtC3TKLh5eQrD2idzWncPo69/KRE+F27l6CnwBZtUIOxg7IqGbrp6x+gbG+RZdhcrMgZYjrcnN3CyqGuOyu9Bq3ehyQSkA==
*/