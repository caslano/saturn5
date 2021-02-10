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
Sfy20UwT2miWacAcRDI7gP6OUkzb5OmOW8YZ1tQIglnGGhbHK5XeYmilGTMsqzSCBiCVMgBATmnC2UEpoeIOKzoIJczoCD4pkQQwnZRBdLNJk7GRZNJgaXAmc7CCXOagW0q5qjdaNZ2d+cxBREZz4OeW0EzlAJSrNEgZgjODlBEXy71CLilQwDqIvWNIay0qmziIzicOAjKKg7B8xwCdVRzYCV83qcFBR8nBQXh60Aym6a4CUzXw9TW6JVZ7Q5H74NyYKhx80zuK7F5QyVmWi4j7iqweA7m1aAXGf3F7jX+rXeDFv48LvLztLnB7veDlN/AC4JYKuuQKsOk4QOvkqquOSET4scmgw4OTQUyQa3MA5OHJIOj4ZIA+QPHUcFsXeIji9IfAY5RB2EHKAHxlltZb++IsPVirG4Nen2WKFlyXaLUwBVylpY9CXKilL8+Ia7XMWrxAafHCrcWLUC1eorR46dbiJey6L9vKEXH8NsAlTY733nVz/VetRD68clwBdpvO4GSNrekSClBYsoTW/MaPf9GR+FIqRhltqTbKGFDDpUmYZ9yhszhZ704P41QIwxM1vD4mTUNroPlVNaOhKRoqf9tO5IyQB+d2ZOBRmZ0o/O/oqZx1GnX/yFegdY2tBDzyFW7dsNiF99dF
*/