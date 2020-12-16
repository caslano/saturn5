/*!
@file
Forward declares `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MIN_HPP
#define BOOST_HANA_FWD_MIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the smallest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo
    //! We can't specify the signature right now, because the tag of the
    //! returned object depends on whether `x < y` or not. If we wanted to be
    //! mathematically correct, we should probably ask that `if_(cond, x, y)`
    //! returns a common data type of `x` and `y`, and then the behavior
    //! of `min` would follow naturally. However, I'm unsure whether this
    //! is desirable because that's a big requirement.
    //!
    //!
    //! Example
    //! -------
    //! @include example/min.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto min = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct min_impl : min_impl<T, U, when<true>> { };

    struct min_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr min_t min{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MIN_HPP

/* min.hpp
mc0e7lcLnU862YRKhM8DvdUUdBZ6q/1/YnjFWiNPyFzk3n8C9vIRECrt5uUfEcUFUGVVqV5Ss/WI3zzEeWs70WSCARBkAbWr/WYoO3n4QvjF8/WbALe59y3L2Tt/CuUNmNgjV4WRv7KE8vE1VGQ1kqSJkdEkl5H5SSo0EOsVf16k35A/pyD8G650NxmdADzZaVg4jh7dH1YQN8uQB+c8h/NMIg+rYDxuYJIHTYpvRu9x/ndcOzD+aIwDPGb6R7gePJGxJMP/3jrcvPGR6/AI/nSfNuLQHawRjYNdcW6FNmgLcZJVpjvgS8NErXPyqnPRQgbZNYyyZzwXSyi6L4ZiemkxQF6KYeR9k2P2LJAxQGKKsVBMA8e8psVcKGN6UMxvOOavWkyDiWPiKGYpxzyixUgsf46xfI5PLNWCy2QwY/tUqMVowRkymLF+lE9M1YK7YjiYsX8wTN5owa0ymKlAX58YLIOfI0JwDZGEZyQ1wKW4SxbrV5ITArFwGn49w28Sg64WhyIx/kr/Xx//GEb8n44HfJ+QWzjGm/1oEpn1qG2JrYmsNLmc894glXNQ1wtUE1mOuRxfjrqNSAbRQUkgAsRYr2Hl85rzllIyFKEKEl+HByEVXkXkOxYjbfj18knaQIqrJmKYOSm5drgDJZQy41oqXvQhhow/Cb9YhWc/eWAVf/Axf677Ok+j8S8VSapxz+hshARMpaL2W0aQmUv9o1+/mt5Ln2Tt7TGcWHexKM77tr6yJvN5TgHK7okw3aEDWT6QOhFJrBwhFCZXdt3IpLgFN8QUlEYBtG33g+Qt+qFOG+a7I2Suw/CnWsqanhc/pFcwJWDikDyjyuvonZGJf8nrJJOqHVYio8lEh9KIHSUyJWlUvkibp9fXqzDnwLwfU2/56JmJe+W5XrG7VF6rhmZYDN03Syvj9ylMIpdD+KwiCwJgzfb/xJMf/gx7xENxriqVokt1B79iwH0IE4MmdLNe8KJUV8P6ZGKalwJdl/GGvYBHNEXWFOgHsP2fG411TUEUqWw8cp8+TnfQMkbGRAMmvxghhdhhG+01+39TT0P2nl4gnK05TGg5/1rH03HYWHRU6LhbmQW7tbN71DbHht/0Iuvfv6Ff1WydVF4qDnp5WO0YVjJUrF+aoah3ukWdtu3iE8Pzo7u1+5ouIvJSHdW28JyK0ahfMiEZvV1O8dRkbi8ZUfeKx3+IPCIEeBpGn2MJ1XmGPopgvqpJ+EhD8T4tqtt5KehREfWgrA1QUnDkXhojQKvBYwzQnwj//CJdJxNVM7CP9iw1cn+PyozrSYxPxSQdHRd6xWPXoXJLHY0BmZ35lj4+0154Njo44+Tg3MCxPDgjo4Ojog/UHjQLaS43mlR3C+tk803nseONIZkyKTpaWmxmt9h/pUcT1ndh23LUXii63DVOv5U99uj5mCW7/K3pRpeTo13Wso/Qs1c1kd1DmMor10zklZ+UmSdpf/ini2k++fh24/PZz+JKeIQMgbgcD+WnJmrAJSugm8cag+2RCrqpz61Eg/nQL/214HdiHU9b3B6muCtvii6BAxE/XYkrRMtrImzT9FWqCrUsHEzzr8ohfj0KydcQzUxfH3aJFXhlf6jquk07OHB0zmbH8J3UKvcbi+alJsZUjuepeytSEpOMRKp4hsBHtexnCM52PD0k59Cs2wBI90ZzY0cH7mlZEV0bokmDouB3mv13vzX7sXYX5gqdCHEZWKx5v6UVNAjLOqSGTw9CIftqu0yzrUhApWyj7Cgl5y3H3dNRQHsbeFQqmaDm9YlWXX5cOcAnNlZJn2B0jbbFUfdrJDXEF0jUKA0XfiV2io8a/7uM+9+l+nZN1NAmTiwbK80=
*/