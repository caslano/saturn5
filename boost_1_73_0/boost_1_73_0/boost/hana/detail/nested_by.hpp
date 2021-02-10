/*!
@file
Defines `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>

#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename Predicate, typename Object>
    constexpr decltype(auto) nested_by_t<Algorithm>::
    operator()(Predicate&& predicate, Object&& object) const {
        return Algorithm{}(static_cast<Object&&>(object),
                           static_cast<Predicate&&>(predicate));
    }

    template <typename Algorithm>
    template <typename Predicate>
    constexpr decltype(auto)
    nested_by_t<Algorithm>::operator()(Predicate&& predicate) const {
        return hana::partial(hana::flip(Algorithm{}),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_HPP

/* nested_by.hpp
K2MHFRZQOnnMs4brhsyMySVdNt+WSi4uBu3lDWNX7zG3kG403chKqkRem510Qw+px26PDzeQZpyj8aFMWifuY9QlhmTMnSeSJEuF8GwfQs7c2syx9p1My6tewdaGi5PWiuCtHnmOkNgmEIocfbym1FExynVQBFfGyp96fMuMQmEepVZ9EZgKw634UINf1JHrECGxDEh4lIsm6NWvbPcQ1s+BLUZrVnfW4lHl3bnZjNduHtXV+rGFetUCu4oBb2gKwHg9DSYMARWw83CM5GKhQsqrnPs8W0VBrTY0gaQiXGWDdelpoUStrcJ4Qzx9oQSL1rowxolEbY+hCwvOjEYfcOlqy4yQuY5gOwGeIO0oPt25UQkbEq6Ux8rReyoVRa3M0+pJsQbNmaRyEhQACGL4aqS01OgBOd83jLhsR76eQ1XD6h5ikZri4UspvJc0TIkgYKBhoHDKr9jfAnck54973CymIReOg/BO2WeSEPPCTyQ3cFseRkRseofuWfIgVnjbksYhQ/SrGKsqoAHdHJqCaIR+G0lofuSU4pJZfhIOkYADeuFqoBG0f3dXrD/zsRmwSXk0UeRvFaA/uiDnpdpTXpdy0nJ/Jj0/irpUqtJGfNWQQ7OpcCOR+k0JxkoyuLZAzX2MN9iLg8PjxBsM
*/