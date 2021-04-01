/*!
@file
Forward declares `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SECOND_HPP
#define BOOST_HANA_FWD_SECOND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the second element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::second` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the second element, where
    //! the type of reference must match that of the pair passed to `second`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //! Example
    //! -------
    //! @include example/second.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto second = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct second_impl : second_impl<P, when<true>> { };

    struct second_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr second_t second{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SECOND_HPP

/* second.hpp
8XpJMowDT4nnv3YOIrPjl2xLGTdI9ikK8QF5DOsOX3ZigdsbZg8ggvSnUuzfgJhjCQC7iJNDLY4I93+uR4k/ws/bK8MOr0ItczxdZKLRtxSXThWJnW8kRmTlDL6FmXK9IQtHB64XamYRhUQtvZzQRQpOXbAxn2a5ZgmkyjlXHR/mQd6G4Mgcc4XRKVBIEqgyJT3tHvUTL35LL4+2Y2U/bAbHidwbJvLMFcNwU+E9mjXEIvV7mdmmGI1nOOmL5TsbSbkWPvEb4enK7swoTerRbo0KMuQPbccdDlT7MSS7v9qPmINAAFHHb4AhNuXuE/BL+gK6gTGoxXYuTTH1+IG/hKBpiQEXSpk7TShzUmPATOtpFI33tEtTAMLl524+eA9c8jSR+IzBIejgEK0WzPmski6D682Y3L38uyQOrS07+Fs228wz19qYwlaaaqF+elBEil3bM1O2FqjCq7Di7RdWrKxGW0NqNvbQ8yUqI7aoJj48LTUR/FSHVicnhenm9DWagrfo1Etk7gkk97QJyZ5xT3VzCADY/b2dkhuLrGRj2OZ9iB0wW3l2YukzxA==
*/