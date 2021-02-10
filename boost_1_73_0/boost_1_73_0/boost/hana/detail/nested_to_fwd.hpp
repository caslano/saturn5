/*!
@file
Forward declares `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.to` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `Object x Object -> Return`, `nested_to<Algo>` can be used as a base
    //! class of `Algo`. Doing so will provide a static constexpr member called
    //! `to`, which has the following signature:
    //! @code
    //!     Object -> Object -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since the algorithm will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_to { static constexpr nested_to_t<Algorithm> to{}; };

    template <typename Algorithm>
    constexpr nested_to_t<Algorithm> nested_to<Algorithm>::to;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

/* nested_to_fwd.hpp
0V+m6nH7ow1xeE+YXmaGhAfGXNl0xK3ZhhpS9l0a75zuc/DOX9qr6K6ejXQV/aUGMBINLEG0Mdl7FC9TPRqrtpGtkrzMUFUYeVYyJKpCj/dQpkrUMEov3PncRiTyXZpItLObzITrL9OdgfTleAGIGGk4+YG9eJdfC5TVmQviYMNSS75L1+ZvI2fuR3Eanfq7dD06S0F6WsWZMWrvMutHsHnbJCQvodJXTCZKXkf46hqvzQk+hm//L1BLAwQKAAAACAAtZ0pSbmC9hkcGAACPDgAAHwAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL3NjaGFubmVsLmhVVAUAAbZIJGCtV21z2zYS/q5fsRN/qO1RrDa93s3FnkxZha3V2pJGlJN4JjMYiARNNBTAA0DLvsv993sW1OudXd+HMhMRXO4+u1zsswsf6dIUqqTLNHmfzsTwZnYlsuFlMh6nV+Kyd4R32qjnXg9O/7yrR6f04iXif4EL92gxdfZ3lYentYX4St0/WH3G/SUnA9qZfBUn9LLJVzqOJmLt5YLXQrzk6DPHxj8DtvwseAkJzNhyaJtHp++qQMfDE3rz7Xdv+nQtXU6XVjn/RZk+XWhT2h+XEL6u1sKzQr3rkwok67OnUeg1bm++69N7abSqKQvKLJS7
*/