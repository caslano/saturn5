/*!
@file
Forward declares `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSECTION_HPP
#define BOOST_HANA_FWD_INTERSECTION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct intersection_impl : intersection_impl<S, when<true>> { };
    //! @endcond

    struct intersection_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr intersection_t intersection{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSECTION_HPP

/* intersection.hpp
bkYLti2ToDBjKV+BxD7RigtLAZpOOM02PzSfz+dB4qVOy2fwaVrlBBN9Wo+1fP54NyHIaZ7l42Yfi9c4mLVnrETcmXpOcb28XiBoWbkCUmYl3/bGeIOhMBhX8Nj3nYvBDy1jrGQF6u0OnxVkSAtbtiPlq3UfW2WzWc/jvQlDEttw6kDC6gtJUGES1WjIxuRvsPQuCEQ3MjHJLW10NFlRvzz+B6LXY2hh2sJoT8/JUyPZkI6SPbmk9lcHhlI1hO4ejEfuoLLFXTRtxXfOe5SCIL0L5j8Jl/dom9n7hLcl4v4gzpg8BXdvU9LJtR6dU7a3nJ2RtvldLNhUk9+5d9a3PUyKxgCgdAJSXmXYvQ5KChKsTEskLwQvjJDswahYir0LDnv9rXWilJUjlf9PiqISSk1E+0wmwORPlRsYMPhDne9/eHPxYLAVM12qBl+V+JlKgMA8FfatEU4fgwYXl2upRKNfr75NErPZ1agowvt78/3UP+chwNweOUD3aoXR0s3bCsgfMqQACoVuBhKLfFx7hs+SGpewO8LPmrkbOP7oSr00p6w7ySB4mEZ64w==
*/