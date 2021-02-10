/*!
@file
Forward declares `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_EQUAL_HPP
#define BOOST_HANA_FWD_LESS_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_equal_impl : less_equal_impl<T, U, when<true>> { };

    struct less_equal_t : detail::nested_than<less_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_equal_t less_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_EQUAL_HPP

/* less_equal.hpp
kk4cPpJpLKZVcSGBe5AtK71sEumvJbDur0ZmLTIXq69D7BTfxvY6W6DglkRj4vVriaFGdC3i6Fpr0KR7MwuAnKsQRc4bfyWaGIiuQxSj2hpUMVIH+bU6S/WybH54qXqWVvpqWurq/jpEd9UvUD/Lruaap4UJiq6PnDRa1aouH3GyRU5fS88VBl9kA9eQZ50jet99a7r9+owcOsfmBePNr98b8WJQA+dmbhngfUFdoQ6nIb8E1KMxbkl4BEGaohGjbLEqi9KMDCufWK6mGrM5RtqtHeAyBTMKkmuCxTFFVCJI5DF5Dfy86r7p9cVR93TIMU2X7n6IuMjzqXcj9ncFU89o6aUq0XT9IRjd/usSuByGAWc6T8DBgv7Dd5X/QCPyCEj49Vh09il+pS0Wcr1vYJ3qCI+ybfEgKEBS6RUuF/U7JuirRRBOCmGjIpjGMzdPi/s6KkuoxxvY0In/ladof0WPHWJx+PH4BfTMOJunAJqPfoF+wI9fuZ9LylVKSS130c069skwFpX+HIXHxY6osMCKFSJLqd2ysESHLwo5gruNjb/hu1kuaG+Xeq0oLliXbxNVP/kloupKvjVUXaqXhQp+g6nrRaXO+W1aep0/gt95FM1SRXce4F86p1WW3bFnsQQffgPqDEjqKfAj
*/