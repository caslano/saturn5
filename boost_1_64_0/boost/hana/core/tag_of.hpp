/*!
@file
Defines `boost::hana::tag_of` and `boost::hana::tag_of_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_TAG_OF_HPP
#define BOOST_HANA_CORE_TAG_OF_HPP

#include <boost/hana/fwd/core/tag_of.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename T, typename>
    struct tag_of : tag_of<T, when<true>> { };
    //! @endcond

    namespace core_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename T, bool condition>
    struct tag_of<T, when<condition>> {
        using type = T;
    };

    template <typename T>
    struct tag_of<T, when<
        core_detail::is_valid<typename T::hana_tag>::value
    >> {
        using type = typename T::hana_tag;
    };

    template <typename T> struct tag_of<T const> : tag_of<T> { };
    template <typename T> struct tag_of<T volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T const volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T&> : tag_of<T> { };
    template <typename T> struct tag_of<T&&> : tag_of<T> { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_TAG_OF_HPP

/* tag_of.hpp
5+FtlUXCHMmqBtQ5pSwGxv28bB48TFk8jHesfdM7LZXNhfF3vmGrYlfJ/GD8Gbdo0aUcZakwSzKLHDeD7DSsBNkLL6d7MiMYZ/7avGH1ZA4w3s29aQUyB3df48+x+XuH+UmuYdwXz3qvNkquYS68Rye+nFY2DcZZMp+SZ6IsEVaP83k/P1hqgFmRFb//8BfJGYznMOnHdbWlPhjv36fw33YpM6tgnKW5dn9KDb4wbzKbQwvWS+0wG7I/wy/FS+0wztLZYVNl7nEwB7L6ZYc0l9phBrLPjXq/VpYM40z8NK/iZtlbmA9Z3KlUf+kLjOcQMqdNZ9mxisY1HDs81UWZE6wU2ZpFAzxkx2Ccs9iFNaW+EM1SlrXbKj3Trnm6+7AI6RmMa+/ZKGua9AzG89ueNfGu9Ey75omTJ84rS4FxdtObO8u7IAfmS5b1Ivix9KUSnoU+i6+mmBdXZoCpz/6vPb+0+4LUHgZTn2NfbeOdAUOVRcHafLPwb3ajIKCH7DTMna7ZvGOElWReu6b3/ULtpAaYL50784tbitTgh3cdWecqk0wk8zBHsozpZQtk32F8v2HBG4bJPsCC6Ny4kOtPpT5YANnO3C2lZEbas3h2MJMdS4J5kH3x6C0ZTId5keV+rnhVWR6sGtmMIZ1spAZ/vM/IOnXv21ZmBCtG9fk1q9BNWSSsCp0rqPa2u9QAsyCzen0gWHYTxs9yq9nZRzIjmCtZT/ci8m59BStKz/Jh4MhAmV9l42cJn17RTVkQzJys168H5igLhfGz3PXZ2UDZeBjXfulwwn5lCbBKnKW4AZuUpcF4Dqv6mcj+5cJsySzHLC6rrADmQLZn3JiPskcBxjnrGN9f9s8J5k3nss4VdlQWArMhu+qTHijzg9mTeZsvktnGwDi7MeEOV5SlwIrQsxw29z0huwnjHatX+3SBzFY7d/Do2b+kLzAfOvd4rP0L2b9A/L6AbPLWEQuUBcK4vgZrKp+W2cKqkh11HN5WZgvj2ZYba5kss4XVo3OlhnuMUpYB4wz+0bSFvJOzYbXpnMuYmlnKLKsYn2sSfuuTzA/GWYr4K/Ch1ADjPapYZcZdmR/Mn2zl4i7HpAYYZ2Jb57rmMiOYJdn0W4fkvZQO8yOb37DddmX5sBB6J3f5fKSjzKGq8Xu+8/nhcZIlGO/fTWsnB2XxsFJkI5LN7ZUlwbj29heuXZUMwmqQDU/8+FayBOO8jL17yUuyVM04Z1/Cq0+XGmBOZEMH+IbLHGDWXN/69/YyB1gVsncnO3RSlqid21owZ4ayZJgH2RMX10aSM1gJsh4lSqfKHsFcyeL6DU5RVgDjTHjZvOqlzLe68T6cf9imhrIoWDua7ZAtr8orS4O50bnXS9195VlggWR9p25uKb2uYTz3phV6h0jmYaXJKv+jbmVlQdq5jPT2ZWUOMGeyFQtfSK+jYZzrWTld3imLg3EmXGqc3iBzgBnITs2IuCC7ArMlu9TPb53MSLOK85qdlQzCHMh2eX58LjPS7ue2tWVx6VlN/C6IrOzZS5HKXGH8GVBjWfJcmS3sBzoXPOvkEukLzIZsVZ/pVWX/tPu99Y7yVLZQu1/hPb1GSM9gXN+7ZlV3KEuHtaAs9ViVKLtiwH/SuiWZk5lNkGQQ5kLX/NS9Y5Q8J6wyWWy/W0NlRrBve+v+H7s83bqLzAjG+zen6yM5lwOrQPavYateyRyCjDNf51LiF+k1rD4/5y2PM9JrGNdQ5udrj5UlwLzJakae/ktqgHE/93YO/JfUACtD1ij33Etledq5B2YPZyozqW38vbX/xt/lfk4w3lu/RV/+ITsG8yDbsSBym7IYGNe3re6WYcoSYfycbeJn7Zc=
*/