/*!
@file
Forward declares `boost::hana::front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FRONT_HPP
#define BOOST_HANA_FWD_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a non-empty iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty Iterable `xs` with a linearization of `[x1, ..., xN]`,
    //! `front(xs)` is equal to `x1`. If `xs` is empty, it is an error to
    //! use this function. Equivalently, `front(xs)` must be equivalent to
    //! `at_c<0>(xs)`, and that regardless of the value category of `xs`
    //! (`front` must respect the reference semantics of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto front = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct front_impl : front_impl<It, when<true>> { };

    struct front_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr front_t front{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FRONT_HPP

/* front.hpp
r0qESV0lgh3lOcMkQi3a7J2O6xkS4YloiRA1QSJ8PVAidLpXJtwDuA9gBTwISAbMAjwKWAHYBCgFHARUAyT3yYQugH4AFWA4oC0srTO4kMBypUKoIIc374BdV4jQkT2vBsXCMHeeK3tuzExXRnZW3r2pmZlCTE5O5sKJzhnDszNTnbmJudk5zlxXhjNPGJbunDlneDJPR8UlDcvOdQrDcp0pLif6jM3OduUJcfNSMt0oGD82ofnFyKHNLkdlD0/JyBTuT3GlO3PROzE7OzNPvBzrnJWR50JxXs4opyuAAF7dGmmNNeMyXLhsjkEYm52ZOSNl5pybcjbO6UqKGXt/XFJMYmLi6NEJTQUjRoxLjEmKbyoYNyIpTkjKnjUr0znKmZLrzHOJvAsT8lITUtxZM9OHZWelZjB5tmZE/43//LbyYY8vYkf9Gv2pv1xyk3b+v4gb7nXTvS+6Jxx0k/YMZ8T/HI1BES3p+U/7Bd22Ff+LTxNa7EFvzAf+Vaqa+43/6rX/L8TQVF6RLijiZwuKqhSh1bb0pwCeKq1MMQz5oTPBQ5CMpkHYiMVi+hMLn+grtnv7R56+/hZPl75Wzb7mFP14Pks3oX3Jm8fejLjJOEuv8zRaTD/5D9vHiOk2tP/mjVNv9BR+eaPmjYdvjv/x11luDBzxmGNTj0UI047NPqZu2f5w1Q/VlwVB9bi/53/1T3HTP14fcdO//3fG
*/