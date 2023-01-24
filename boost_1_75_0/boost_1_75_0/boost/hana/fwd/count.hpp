/*!
@file
Forward declares `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COUNT_HPP
#define BOOST_HANA_FWD_COUNT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in the structure that compare equal to
    //! a given value.
    //! @ingroup group-Foldable
    //!
    //! Given a Foldable structure `xs` and a value `value`, `count` returns
    //! an unsigned integral, or a Constant thereof, representing the number
    //! of elements of `xs` that compare equal to `value`. For this method to
    //! be well-defined, all the elements of the structure must be Comparable
    //! with the given value.
    //!
    //!
    //! @param xs
    //! The structure whose elements are counted.
    //!
    //! @param value
    //! A value compared with each element in the structure. Elements
    //! that compare equal to this value are counted, others are not.
    //!
    //!
    //! Example
    //! -------
    //! @include example/count.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto count = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct count_impl : count_impl<T, when<true>> { };

    struct count_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr count_t count{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COUNT_HPP

/* count.hpp
PgcTRoz8vJhmO3IswbPVEKXYVgq12t5D4xJuNK0EK289y8tEYTQvjm5QjHjLohAmf+tTX5MmQjuIhTDBkYnyp9AgwObRuRUP9Cpvtpbvwi9nVrlytFjWNcoaxkWT9V2ji1d2iokW1vxt1ndn61z8D0qI79ZmvMUMQDYby6OBe63vRl38Xozc3KcirxtSWK27qlx89DkMqqtwdm929oo2GSqcvazvQvgnHWh+brOze0nAMH5CTDfey/Lacjc/0Csno0nKawO4oXO6Db+P6SEI8GV5caikgoXhLsCorKtsdWb4iLX8GF66e3dvsWR4tOVD1GhV8dwPH5v75FbkyYgcGogrOwfIPaEid7xDoLImgVy9EnL/rccJuUKZkFtEyG3suAy5O+IqcoBT9AuDC3Lwi2cvw6ygLdfslOdsLpSlgrbQed2G11lhOyCWis/mvSObpjcJE9EJFPoJFMpKsjRQ7pWQGHAZEoZLkehOQeL9swoSFxNIlHcqSFxMINHNpypIXLwEiW5AorsnEmTpKzBqs1MeOcv6bh02RVWTsbhXHZBg5KziqpNGKBk+iyXLo9CMiNuPEOHYCJHzWshZ1jzM+u6BK6Se5zhnfXIW6otcD0lvQZVFXewGRt6/RtAUHxviOFdiCMsb0wBy0Ipb2RBgJE3IR+cl/VOp/Xf1hav335uU/jtIeIJMxghHZIZEF6ZTa6ULh1qHpGpK29xk
*/