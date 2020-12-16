/*!
@file
Forward declares `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_DISJOINT_HPP
#define BOOST_HANA_FWD_IS_DISJOINT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether two `Searchable`s are disjoint.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_disjoint` returns a
    //! `Logical` representing whether the keys in `xs` are disjoint from
    //! the keys in `ys`, i.e. whether both structures have no keys in common.
    //!
    //!
    //! @param xs, ys
    //! Two `Searchable`s to test for disjointness.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_disjoint.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_disjoint = [](auto const& xs, auto const& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_disjoint_impl : is_disjoint_impl<S1, S2, when<true>> { };

    struct is_disjoint_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr is_disjoint_t is_disjoint{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_DISJOINT_HPP

/* is_disjoint.hpp
OAxgQH4X1Lq6VDOGOSKbTuZVQxP2xH40YZ9Agr5T+g9+a0ojcy4XsV0BbHteH2Lic2FVCdvjmMciUJcDS3OqNUFaXTvTtV0B+cGxNptBkAIID9bYEYLUHPhiJtCHQMhJ3N8lH1aZAlRf3Tbdomo5nEkWZ7KGM/lRJpO39qXTf3bQtqW+qaF83jLOZw3lg+xUVp/PZPUnxA5G+uQ0NZPTLxFW4a9vqntiGmzzWm7t3iv2gErm46w+UIs8JZfHZxoUE/G8ixamMPNofk1tM9o/w2z+F91WljOQJQRmS0hHYtjb+Lag2VYdAwFYlVi1G4HoXNZjYAEqqDCUJMqkv6duTSDYpxO7B9lsmAZqbEaorgtSY5HfxWZ+0f6NuxcuS+Wgfp1Pf5hOIwGNcS3XNgAUJ/bJSIE1lHciCrAxc6c/xfua///+Fb8Vubz/G6vkCYVKnsBSUZadsXD7TJNnG1E9DyvdFC3UgkhOOi0jWshN0lZ3dFB+7jMmVc2vvkyzqConONZMMItTxL6t2UO1x4oc30YSzHWPEXxHTMpJPu5IFhqWL51q7u7ykGNJUE48gwEs5+ANoKKxFcMNGjuHswZZ5c3haAPcpcAkAR8e4pBhKiReZjeCUOY47MxWQaAXkpvTe9Mh0SU38LNHtuGJqQtqC3ErSaV32RXz+waeRH53qMu8SmglMDv7abkLPAheeb6vQzCVW4w7qT6X2fqR6BQdve8xagPxl7SJci+ZjE9lf7jVt9F931aR7N7tb4leEY7ADOlMOWuYtYW5xMjXC/nIF3Ks5TUTYN8qyix1jjzXaUUvplqiBVyVCLCovGJQBiFQIJIQSyz2Ps5Vehdy2FxVAEq4+gIr8i5DDsT79/lDzDmyyH0fZAC+jagxWoM6X0qbWNS7CfW+fahVEWgqrHr/cqBV75/y9kEvRb3PlN/JtqJfZzuw3o8dYyKeS1R9BcoV78bAn9sFdaLeBPzGwvF9dvd1NyED7r158kSzFtExZg1GmDWInqRA3Ko7TXkTi5SwO2I5d4mt9hi0CTzNhxcoUZk8a9/eNEmFWcykJpNc2d8s5elMpTWr0o+IvambUZ1lPE9HyyVejp76/pr/qd8K4txk1ei+8qdnWP5kCp74GcLdXrTbhPyJn5A+8bNGi+jYXuvoexY5QbKJkRrFeOv10zN46yFbBm/VAw2JAlOK1JtFEqcFnzKRDJntjQbWOc1EMt4aW1BhmFchOIDwqDWLhEdB+Sx9dnUSwxmSN59HSOP2vUAWhKnkrXgj+8geTBgP7TEvdl83P0thDNppxCEogFpAGWaRSDBaEGb9TMeZ1pyvQDx22RIw1OKprFAYCcdBwdLD2SPW0pOpfJaXRuStp1sLaSC3a2ov4nEzPGiGHKlEH51sjoK2GkKfJ1noEwXe/RyEPgzpZ0JGQeiDb838zvM1oUleiH2a4lqZIcDJjfXYr/6m6AqhdmMDkQjhBfnZ8yxcUU9a7mlplvdsep1707+vodg9Aj33rT17Vdc/dDFF/Tzhszh0LjOUVPOhS2HvV2zl5EMwbfZbSaDK+UWmkTPVICqXJycN5vZx+xGW6reM/cwwun9mkCnOGAX99XGqqiRGiGdy/4tNaRxX4jlNRwmppCnQ+JAFGkA0V0+gm7emEX/FsRd8Bg6Y5g/KyDXWi9ZDyDUqpvmRmOUao9CB+SzXGMlyjRNJqGFVZ5/fRBEXUENfNgPbPwxAqnEpYrxoxSikXjAkGn+m6uB8CvKmmrt1O/hYE21RJvKGD/amuRh5BSg00VtUGeKKVzLiCu9oElds/t8RV6y4k/mfor7459cK/9yv8A+eCv88ZeCfJgP/tDH+gWSYtNrc6aNZLIg=
*/