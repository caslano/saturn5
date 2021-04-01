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
xDWOgjP26c8GyXw+7Iw/kKdpESTRKJHuDkGpcoAjRnYMl0C3iIE+FL7mFxl4tCKRd7mb98+BgWXLPYpYyaCdVerxGdq0O+MFNr+3BncvDMm7LgHYZN5DQQKr4b/jjO6IuelTg4tVJUEUb0VxxsVOfUdBvi7q604JUQMhda1xl6zU9Ib1JCxBGSj5v0oCg5fIdiOR0N5g2/DHFADZqdWE2aLgUmH9RNPEbN86XYQz5zsuEorNF5+CsoJWExXlLjBVjzdjj856601pVTjbGt81LcBxUCu3yj6WimDOElSnBV6amrJ0FhqfTv21Tst8whsw/fiKy2uqiOcjqF6dAugl7vqDkrGsi1Eak2M2qZmAF2MX6YTD7edN9JFooN9K3qdM57qsuq0avcEVko2hWy/N+iA3X5iTqHdFku/wrOfzjec34fpcxKnKKI+DEQQFK/rRtr2gGEys7VeRk10TZVaWURMhhPJ10/y+e17w+4vse7DHKFzMiIl4G1lY9YeluJpPpmv0HGqVr1r/LA6W+B1v/Acf2NQfEv9mzuBK0QRqp3jpjWSLhqQiqmvn1w==
*/