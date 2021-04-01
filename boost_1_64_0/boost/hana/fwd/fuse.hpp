/*!
@file
Forward declares `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FUSE_HPP
#define BOOST_HANA_FWD_FUSE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Transform a function taking multiple arguments into a function that
    //! can be called with a compile-time `Foldable`.
    //! @ingroup group-Foldable
    //!
    //!
    //! This function is provided for convenience as a different way of
    //! calling `unpack`. Specifically, `fuse(f)` is a function such that
    //! @code
    //!     fuse(f)(foldable) == unpack(foldable, f)
    //!                       == f(x...)
    //! @endcode
    //! where `x...` are the elements in the foldable. This function is
    //! useful when one wants to create a function that accepts a foldable
    //! which is not known yet.
    //!
    //! @note
    //! This function is not tag-dispatched; customize `unpack` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fuse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fuse = [](auto&& f) {
        return [perfect-capture](auto&& xs) -> decltype(auto) {
            return unpack(forwarded(xs), forwarded(f));
        };
    };
#else
    struct fuse_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr fuse_t fuse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FUSE_HPP

/* fuse.hpp
x2utAXpiwPZmTZqzBNSm3asEcBy7t2WllY0jki0QQx05aBhQb0DAPHA8KyrV3uvoe0iGSWqkLtZRcPBN/bT3hezmx0q82tAF6c+OJjCDEK4sLLkPn4cN0V6EpFfOUf2dWd7ZCieDmA9QFiID0qvb3R72GZFlu6CqTN0agRzPQTH2N4jMu5h9ceR0KoNUp22wEIQZG+HkPuhLkY1BHSdUvjp4LH8ZQe15uyIvKTOf2n08kLxMWA1BOl+8XmuBcfQiL0xj2ezdIre+RVbnkf+4LGfXVJugp+5RhiFJaeQ8E7RFlXah0syTTTetjWGmaIxA4vGenUY2BiMdOf/JFdT+0lMJc5vFPXge5xw2JpZ/Hmbqx8gwaQi/U6FKV0WU3Ee3mwptmCoj59ysM4KEzVk906dfLlysiVnOKh9zxi4tBSXGzc6Ew4bbbW00L0F//9UJlBtjgANCTXbIQnyhU7vuVUapRRqln++OCeSMtks0LggTPBk6iRShrB/P6diU07uFYN9Q3+Xb58+Lr4KejQOA3TWAToGsCIC1o7wdvcpsu9Rghb4aIj2KGtRQOA==
*/