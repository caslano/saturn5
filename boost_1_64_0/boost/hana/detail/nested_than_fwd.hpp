/*!
@file
Forward declares `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_than_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.than` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `A x B -> Return`, `nested_than<Algo>` can be used as a base class
    //! of `Algo`. Doing so will provide a static constexpr member called
    //! `than`, which has the following signature:
    //! @code
    //!     B -> A -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since it will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_than { static constexpr nested_than_t<Algorithm> than{}; };

    template <typename Algorithm>
    constexpr nested_than_t<Algorithm> nested_than<Algorithm>::than;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

/* nested_than_fwd.hpp
fCx8Sv/6IjZGjhVj5LgwPmKMHE91+I6mtXMsfw93AqtfL5tPThL8Tw7jI/ivJ/6nsDXiFLZGNGdzM926N6wrUNud6qaXZAd7Pb/Oaap/j2CNtDnxPN3lMeTMpLt5Z3D9lvBXGFvZI+arM6kuZ4l6nxbSH17vHxLt2Ux3ezCf62xhl8+lss4hu3we5T9fzCHoT7TuS/neG1fofm59Ohfyuo7g3XiRcwk82i9Q0Fb4ZtxTyLzLIBBDffAiVuddhG/5YqrnAbQO+ynV82dsHXcVm2svZf3tMqH3n4fxEf3tcuL3CyZDi5DhCsoTJf/mlZTnV+ESZz6fYg19tV1DcTvexUNhOAp+jd4L5XyMHG898Gu5lmccSsTYKBFHYCRv07D+YW1Sy/ad1zHdXi/W68p23BB2kPav128kHd9k1tvivF3ULfgWjbhDcwJ/O8f6yS2in9waxkf0k9tIntttG5UzPWGbrG5rKNPKN88Syu4C3+m2kabdh+zNXazdKsCzK78Cwlsebt2GQcGzxNo/3hGzb1gtgK/9/sDWfvcwm35v2O9nuY+1YW358HPRB4S+HqR8DxXZn4XF/uwRon+U6KtBX8bm0lHDzv3LnMcpzxOU5wPfXlftFAcyvfzuvgvzzv/v1+PInkdOQTqk86XXUL4syq3R+ezbsN+566Le+gzRPOyuhzL1pqznIPMspPOUXgD8XCdv6Y9Geh7wqyn9GNILnNUW/yTS7cAPsvxLnUGLV/o4mL0XUO2/OZT+FOs/K0b4rjPB5v9nxDh4NoyPaNfnSOfPi/koKvweLxLdS8wmZJmdfkXkf5XKyZGdf43yv87y59n4fZON3z8Kuf8UxkfI/Rbxe7uUzd7IMxn3LVzYH9vgXT2ucdDtTnLk69NnfF357IDpE+/rc+NECx1FevdMenMpIkW/tO8n3uN70hH4aQP9ExtlL3GuZnwzQfNR+2B6WWatK/dfyVdlefCztc/op/og7PdTfcjnto28Rxm4d7B21jOvI3i3mdUxfigXA/G+8THrux8zO/uJ6Pv/pL76D1rL/Yv66r8F3TFifTmqStONrvLbzDr6TAir/zxPmVNGecZSHvW9i/nuxlX5x1JFlf7wsTSeeGxCtPtt+I7KRt01mFBVwpc0gvNGxWPzKv++agukHTrLRM9l4zK9NufervDizISqeB/rTMYSughTIIegRLF3Y/FL7Frb/u6CXW+HeRkjiMvSUMxnX8xlL3Gk26uEj35ilb9PVVPbTmL9I8f6cY714y2rxDkO8ZpcRec4xGtromso4Z/4uhrnwn9AvgYe/8WepW/L9Fezkff/ZxSRw5RXwcuj9prC22uj791j9cLmrqlV3njbToy37avwEeNtGulxB0/foQNZO+zI+M0Q/Haqwkfw25n4fbHK/+ZxqouP04/pOu8ZWIWFLcgsX2HjXKBKbcuW5dMFfpc0QjBFye44gbZdb/rYGgb3g2Or6T5YPZ277sL0XFv67HT4ORZ8nKbPN0U7omxQFEPa9jmXrU3qmT53FfrcrQofoc/dSZ9zxHg4WKyJ5hLdnlUlfKcjjCmg+Oxd5T8rXxUy85Nj485VMH/el0AfctbqK+rUNq/Yc0h73sZiIih4X5r7y+aysWHuvn6Ztdk8bcv4CRwDQHY7B7LzIqHjeVX4CB1HSXcNQsdP01n5nbQ3byK6GLNfr7Cy5ouyFlThI8qKE4/9GI8449EieCyqwkfwaCUebULeycLefoXoEqysm8W830F5TqQ6dlKexYJ3TPS3pUS3v6CbJ9/MEd2Bgm654HcQ0aUE3YmCrovoulmdtmRjqlfoL12Fj9DfMuKxXJT1D7EGyhDdIcw2TmG+hz6CH0Q=
*/