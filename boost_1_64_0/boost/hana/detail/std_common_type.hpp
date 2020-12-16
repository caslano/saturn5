/*!
@file
Defines a SFINAE-friendly version of `std::common_type`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::common_type`, except it is SFINAE-friendly and
    //! does not support custom specializations.
    template <typename T, typename U, typename = void>
    struct std_common_type { };

    template <typename T, typename U>
    struct std_common_type<T, U, decltype((void)(
        true ? std::declval<T>() : std::declval<U>()
    ))> {
        using type = typename detail::decay<
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

/* std_common_type.hpp
bEQjZb+G4VcF4H8j2grwYWX8VtjfK0HTULrtvJA3pt0k3PgQRb+7EenJYb/ObprI9lRsjoJ+h935VDQFsba+BXS8TU4T+NtYmyC/r653MBzy+nB3MdwHEf/v3//BjBXWLoVy/eFj5V7GA3X3vau7n/pVQewzH5w4fP/wkOUDvOjfjyCt5yqbV9p0O1c9ZvqDoOX94QlW1l5iDntK2KZVQs5ngOe/EfNRyCvv+Uptc+Ta9XlbH7sOYjHqhA0iGV8CTZHz35JnSK8IW/GqaPPXWN3PE3V/Azg+x04Se6GhKrYGqfJkPobG4ltMd4D5+wrw74h2vZL4Xx82aSObXLvAElJf+otYMyn8jRFNXyf2tn+jPB+w9ftuAXfiXvP6F3Si63UA/n8fevhR2N+/Pmb6M79TX0d8PgGOp+Wana8fV9Ea5N+mfcRaAXgrc4G+c16jq5EbH96vy5BmfRc0vCy8l6im9wlCh4a2QvEsZ3mgw/GU52UmzxiaJ+qQfxxb65v8m1ZrfhN88o1zNmPyJWl+5nZyCyorhP+mrI8jfK1q18f2Uyj3t08VlQmZqA1o7VFt1xZWj4AF2odJTM4w1YWP38kCP0bgv1Bt+wjw/vbdGmlWF+jI9gt8/HXZlvQBm879JLwvWR5T8OF+krrqDc5xag3CA0FLsLUp2+n20PUI+9aTwHnrlB00na37dC4T4DsyvQFn7cfV5LvYieFRzjDb+0WG3x7ff4N8vP/sovUeKmP+lNlCpnoh066UZzTLs7vIM0fk2UPI+XexntqT4ccC/10h597A87G3vRh7SLtj78um3BDzm7DxPUbg5wm+YwTfAo3pBqrzDWyN2STqHBN1brZ1Ao61XTXZ/gWiX08p0a/3o359TmS4X7GFyn2V9liLkOa+IpC/p/DnRex45n5O0AS8WUGdv0Jl3hwJHEtW1mS1lRc2T4+lDjuegRd6Wcx0bvJiTQGdMx4of6mwzbCRHh71OMDysXi03XA+B9p81BfFex2ZByknRXV/nfn+u6i9uUzdmjdwWqYe/De8u6hucm2dNu1uaYrYf7T7cqbHLmEXMyTj75mMKwNk7NP5gNMy9jN9yLW0gq0UtjlnZQBOyDAo2qBPtMFKGpcFkjXJZI2KOdroag2Vsbpa62stpaNMXoOX8itYVNjAw4SM0SD/JmQ8nPW3K8LgxeUAnyNF3c1vwx7Fbb1jfa+W19Ryb3zU0rruW8gzkt/eo8PM1rYmemldDEt7q2PBV9qH47jcKPt4smXHsnnou8KWnSDG7IlMN8BZ3R1MY/Hkav+YOjhgfX6KpbHv6izNYhp3p1abtG1bu2ZazOwO1r/4bz7+NdMZ4BF8R6j0/Sr3LmB18XOgs4Dj/eUH1KfHMR/Ensyn9COh03Mo/9n4r6jOZfoALPBc4Xw29s4W/e9CKn9nsd4Dnc+PdJGwKT8xbUm0Y8Se46eAka23chWELvi66ZJqaqPi9ID52+gy0b8utHUz/iQro/U78T78S6p7ufAlXAm43Cf/yuoZ+CLr16uFbv9Ae4rX2N7nN9UGZ/Jy2lGgZTHWRdtfT/yPIx43CJsEeWy/5nq4icZqkvH+fTVrb8p/M9N7rWlPau9bWB+6Wej9NtYXgENev+7usHOV3dvL8ytbzl2M1tBNpbOIM8V65g+m/pJW2OR7TdtZOkmDuOEBulyMj4y1+6Cgg+9B+/xFmQ8zutXVRewM6B4VujPzTpRs4uNM76tF/3rS5g3wHSPv00yXwOPj7dcniP31szQWnhO2/7SAt9AvCL6gKcr3JbOPJb5c/sW0xmzD/6ma/D1ferQ8n7R+Fdtub0geY8CDrVuMryVs7tWYdrE8td7XCLv8tuQ=
*/