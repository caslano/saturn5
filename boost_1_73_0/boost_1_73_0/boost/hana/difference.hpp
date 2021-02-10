/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
mlCLzBIRXxzVlMGQxrgt7tke2ktjp8LJUc0VDWwK5gRfGqRSETg3Lux1d1J9Up2Ou4DtR6BsDOvUXKQkoJS9Zs/xcf8NfPk1ofa70df1LXsygenDj7+eaCzs9tvvzrtW7+Lnl2bTl2nbl9AWTNCdIl+GscnnWSAi355z9pomjortjayL4eCXz7U6e8skU+iXAIQEd7BGocMB9WjpSl1CzLr/BsNOyFoe92FuwBc81HRpHdaDHOtjF7bwU7YX8n8BCESzYAKt+5fn50hLoj/IAhBXiniK1UpO8DUjKGnBycpFK4BZvTZlDjZooW17POIZe0Zb6VqDD5oKAcag38cfZ733NbVlWHP7rs6evab2FjT6uTsc9QZ9QqP+oN+tsz+I7BR8ummN7Int6u0fjBbM2w9gKvFiEYTkt8HmBrZ7587jOQqkCZbO1Gi79ZMij5qzbmcs8Q/bPCDbYulGzqyK9bpkDVd3gXt4vH3RqqoFjm6PVtdah2vqqf/GYkF4fnFw2MBlz47wAXZJ+XxUKpT+YGy9u+ydj61e/6SKk9PuWfvyfLyG0+OWIm/Yo6qxJGCp8ppi5Crk9k3loLLri0qiLx5DFPV1vK1Eb483tycAFjv2opIhLn3Y7oJrH1b5BGMdWMzg2MOTQD/z1rWJ
*/