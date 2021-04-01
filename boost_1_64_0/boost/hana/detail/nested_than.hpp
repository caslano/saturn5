/*!
@file
Defines `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <boost/hana/detail/nested_than_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP

/* nested_than.hpp
6xJegaIgMmVkpgtd1/rz6rEu6Kkp/zhgwqTj7WEpFWBieK0v58EV/YnyFE4tY+TpQDzw4FHmpzkoOLztHqjLZiI/MVWPMtW+Cb9jW9nNT7s6ScTiRzBY3RGr1C/JzqFSWqPkfd8AlVraXVuh8Qw9p1jUcwIhWvXBtVKSjtkRQ1XQbVPcnDvB94xExINZyQQG/9K/uwNS0Jrfm1QvhqUPTreLsf6Z4UqXdxYT1IKNISxYQiVN9Slf9l+bC7yQi8HsG1V4lxsmpUlNGw/SzPF+85DJwpOYK+K20RH78p8MComHVxYFMb+yijPYB0ID5TNwLYoPosPMo8Qo0UoLIB3HfADNiACGrEKu0Sq6Br9y7z5Ph+shVefJvftJIr6dN1nMsGKDKsfJ8GhO9l3MIGIBmaTTHitU/HFESElm3b96m1mqY60vzv4crMPISTFHHq0yZHf0ZewKhG7wL63x8rZG0Qj1wCHp2Rfi4QehxEr05lOHDV5rNcxR99bvuKO2WxPE8/2+B8Arbsg5F6tRwxlES0uk6kpIUHHA4/Fa1tWnYCyZm38EQg816+GJvg==
*/