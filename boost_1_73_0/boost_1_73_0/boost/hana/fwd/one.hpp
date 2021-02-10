/*!
@file
Forward declares `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ONE_HPP
#define BOOST_HANA_FWD_ONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the `Ring` multiplication.
    //! @ingroup group-Ring
    //!
    //! @tparam R
    //! The tag (must be a model of `Ring`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/one.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename R>
    constexpr auto one = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct one_impl : one_impl<R, when<true>> { };

    template <typename R>
    struct one_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename R>
    constexpr one_t<R> one{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ONE_HPP

/* one.hpp
/gHkv8nxdVcbKZKv83dnFYZKnYh3xrAYYaY5uHjRSR2UV+bh12Fku86wNf0mfsk92xmXDvZeMtj8xom2nZ0/f6zFIxgcOc5EyXngTwJrRlgBL5CqA3s6WoRsy8JtVfy6DKWQB4YBGLNTtpjjOUNsAIzwhRvVljJnjPPI9tZ+s/m0ebm1Ly1H8bDdbDYv43lmq50/sQy6F4lufX4y6HXM/tuLwQbzxYBHoTZJzPkI+VsZuru0XBK5CVAMgNnF4oHPgUHQzo+PwT4IxdnT+Ngp14+aUi0JdHm6KOhWtS2yQvM+fxVQchj4H/kbTPdjFR/iwl4zI9K2WlIizwjHt0lV7VnqiWhL2nMp5DSr7r4yaFDgd5YeC659IY8HxwstNCUXHjlyrGCywOOxsGbzMZnBtRPGx9gc103BwfryBLPExyBNGMMQviF7EYgztqBz8X0Tvv7KU5CMPq1UjYn4Nec2xTm04kI6ObaSP5jxL4G3EbeZGK3Pni31n46bFJFlwF08gIw5IODXydmgpxtJM9/mq9EBbbnfSEG9wLnOH49j3g8UaMt1LDzfDTOIy8PVsD3f8kLHpGrpNl6JZXlmRGdOSODHC29EkxJov8iPbudVGkNIVD7TlPBCsNCfaa2RY2FsRZbLYAr1gwrwZ+HE
*/