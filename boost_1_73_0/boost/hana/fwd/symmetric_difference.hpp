/*!
@file
Forward declares `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct symmetric_difference_impl : symmetric_difference_impl<S, when<true>> { };
    //! @endcond

    struct symmetric_difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr symmetric_difference_t symmetric_difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
NradYVcU7WcdlgKOPz2Pru7R9vPKFxiciD4HDZa+A2uvceo/hTznHMhdkwWQwdARMw8UgrhUS6FEZOll7veey7ViuPOAa8Ww86/sXQ981VUVf+/tDR7jwR4ycOLUiaAoqCiY6DQHMpvI7G06JKUEBf25UAneUzTQjYHtMVZYWFSYVJSkVJRkw8yGIqBSopFhkk4je/OtXDpz5nJ9z/fc+3u/t8GgP5/q04f3YY/77j333nPP
*/