/*!
@file
Forward declares `boost::hana::count_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COUNT_IF_HPP
#define BOOST_HANA_FWD_COUNT_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in the structure for which the
    //! `predicate` is satisfied.
    //! @ingroup group-Foldable
    //!
    //! Specifically, returns an object of an unsigned integral type, or
    //! a `Constant` holding such an object, which represents the number
    //! of elements in the structure satisfying the given `predicate`.
    //!
    //!
    //! @param xs
    //! The structure whose elements are counted.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! structure, and returning a `Logical` representing whether `x` should
    //! be counted.
    //!
    //!
    //! Example
    //! -------
    //! @include example/count_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto count_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct count_if_impl : count_if_impl<T, when<true>> { };

    struct count_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr count_if_t count_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COUNT_IF_HPP

/* count_if.hpp
e5VO7GvNLRhhgpq2pL45kkRj/CaN8TtijK3X8xgTzdiEpChD2o00ZHzyPn5bGxG49qn647ms2JkITm4cOLU/R/e2plCZDVymKp/obtHZWsnKrAX6nmwg7RdAwtHaPlQ8GWE2NNYfx+3INBvkcuvazQTTBtCPbtqLBJLCS0yR4Q07kK+bJiP22itRWXiJUQy/DDk9Dc14gSKP3CFmqGJf2UrqMprWqnliHmPd+Ft4uKhbUX0exNo0or5ibThHrOyIRvqX8RiSCk76kKItSvsSzid9dT4Z6FwAXKPzU+hAIfnP+vdN7e/l0zrn9kR6Me2OxPfDtya+2xbHvWv3GV8MY/5y7va7Zoj1apwyL6CushivvNr9WK8GSZK+Xr0rRuHJepVwzqQbhMs8WK/KQUAKlZdu00lAgZn2UcrPAQioTaFOi/J0WpQraJE8kY7CTwlBa0+bJu1Ik3LPDFXch5Jzoe3IYGv7wTO5BoEgdHUiTX+ytP3jDTHSlK4tUWIddSrDY3ANNkHegvVz9y0qPXpWo0cv1w8QRnDHMCkJ/ITNT2ma6rewOwlOQM43sd/OSjg6NNY1TfKHdJq0pSua1Mw06RvRj6NC5iTIaucR/YgaiDwdF8nL1opVNl2u06UBgi5losW9qNz7BF0i+7JuU6bXdMp0HGZsgiwVEFlS15duE6e5gjiRkppGiBgHYtJu0RmHfSpZyiK9sjjACLx+9DcaWRrWJVm6a0UCWcrXyNKP/PFk6UlhqYI+G2bw59CRQro8fKyYOjfcrMOwEWK6ilmCeeEZ5nMKJNoTNwfPWhHTq838zi7y/i/9iPtmsXFLlkdjG5qt/Ppy9aafgb7+0mdirDaJjmur1Tuuucw3MFxh5QRRl+L7hXD4L7z6lzH/vuBe4ecpBePe03eyKGtBpBeOaQEPhnQq+2ZRNl+/CsVDD68y/cc8rNN5m4fwFAo3hUZjV3tcN9Amfth/M+Czwbl99GyW/eJLJ9aqVDLIHoR9hQwf0LVFwHdYaPmP6QVF6K/OWk38JNlie7DV2gWOpBz6WbkcNVxCbI9VbiflDxlLzyaSxyykvY4Ey0SAyXqCPHqOwy85VgVBTKYTmSuyieg5a19db4RAyWeMLs7ylCutVv2IcF8qDDZgrZ8R1KboYifiB6Todr72678wqCleZsVDZhlafi6k2DnNwmd+QakVB6tpsyLNljFxbsQfZfJcYZRTaqE9BnFa0cX4T5ndSl6AW5VPs3xWeksyC76vii52ILm51AbZ1shpupq7qmpolYPq9ycZq2yRi1pKhVIv2UK5RhXMSpdftF88OX3KVK9ijss2gfLkvGuEMM38+tAqOC5LZ2O3QHJLskncjeEkIYXop+t2Ax199nLlUp7q1pjhCwWOQ2C58r6s33aMnru4XaisKM3qpX8yOm7B93l8M9DVk9f/++S5LJ+ZWqZ5fzc2s5Dmo4s1poTvU9nggWdtlZ5bi0C6D+Vsck8lIwjlClBl1k9+XfmfTO1U/mMhrXzh2wDncq+M2V+Yaf6Xe5V1yEZsKm+DwuM/H0VGFfYVf+Edbl3+BvLVFc7YIPxqz5xeIRtDpVnkw7zUqXozpAi5FHHkqtNZAQcweoSeI5tz5CbkyBY5cuNy0FgitLQwds01Uk4uRCkhq5oGWFISHG0K9PMl+5Kii7M9XuXhJHXy+LODo5MCfX3J0cW5CH8faCxMd84Ijk729/fZcTC1lrFpJpEkLuxzonn0LS9Tiuoo0oHIWc3YJzzSZHQMwXc0vl58F+AbwvdmfA/ja0j5T/kYTWZLUvK2/5CPx/djJjy+IuX21XGXf/gWiuB0pT/tS4lWkXwkv6XUmk4EpDTDwD+ZFiY=
*/