/*!
@file
Forward declares `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TRANSFORM_HPP
#define BOOST_HANA_FWD_TRANSFORM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Map a function over a `Functor`.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor, the signature is
    //! \f$
    //!     \mathtt{transform} : F(T) \times (T \to U) \to F(U)
    //! \f$
    //!
    //! @param xs
    //! The structure to map `f` over.
    //!
    //! @param f
    //! A function called as `f(x)` on element(s) `x` of the structure,
    //! and returning a new value to replace `x` in the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/transform.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto transform = [](auto&& xs, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct transform_impl : transform_impl<Xs, when<true>> { };

    struct transform_t {
        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F&& f) const;
    };

    constexpr transform_t transform{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TRANSFORM_HPP

/* transform.hpp
iGYxe1twXkt4SVAKKQIoR8mVtQEbwpeW7kL93fDfWGdvyC2ynL5ZSs15XCbjOSd24xEbA8EA9v8v94nRcps9tqjj8v/fAxcy3F9B8AYuXRnWjL68/z8BPM2ysfp0shpvtzMgvIsQLtGf/tzoygZWzoD236HY23A0YE9oeamhTvh8BLMevF4PF/IYLNs2u+tCjxIQuMR/mbX0Jm3TWqwwsPSWeKCSObB8s4+5xQXavDIZrlSlo1MIGhNhcqIMOpXcsj7u2t8ALykK9k2oLI7B5L9YYzTJuhlYxp+UiRJagEXWIa+s3UwQxl9be0X2V5pfDzGwEsURXYEfw0pWg7igjGyTBCCVVZZcQiyb3N7s4Z+2imQBJSJRlGUs+xMddvt/uCBiHaEtjienGfB5iqrUVX1QnGKjn4Uyx6NrI7kDk3Ujvy7ZDrT31+IfMKFjtAxGgJvDFHNW/E6t5MzXo2jUb+M0/jaezG6nYRxkmXMgSC2KBDS9w3lWzqtfRpDqBtBEsyLmS5T3qiDOt7RiKGZc8GhoQO2Bai8s9lz+6WUrwc9pOqVtoXSvrN66vQ==
*/