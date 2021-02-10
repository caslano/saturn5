/*!
@file
Forward declares `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_EMPTY_HPP
#define BOOST_HANA_FWD_IS_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the iterable is empty.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs`, `is_empty` returns whether `xs` contains
    //! no more elements. In other words, it returns whether trying to
    //! extract the tail of `xs` would be an error. In the current version
    //! of the library, `is_empty` must return an `IntegralConstant` holding
    //! a value convertible to `bool`. This is because only compile-time
    //! `Iterable`s are supported right now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_empty = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct is_empty_impl : is_empty_impl<It, when<true>> { };

    struct is_empty_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr is_empty_t is_empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_EMPTY_HPP

/* is_empty.hpp
lyzAa0KwaBzBJ5b0kIQAQVOt0sQsSpAaz0CnckyoSqK/oHEQZ2CNG/VNvXJEMkMNilKBoC11j8cpbDxjMF4Z7KWHxNyapiBGVjNw3DxaDIXmysfFfuXdy+QKe4UgG0KxuX0guwutMdn5skEBLHOZSzQaatA0ya09DEntLIEoe6InonTuQah83pXM9U9ic6kFTnMQQ6Dxf2wqYjKLKuLN22FFjsy0hgDvP+YEcS77JpVcyOKa7oQ5GAWdGJdmpmSuo7mbNB42O/wl8OsZf43hX/KwuZXwd6XU+yVjx2sddtWP/WWl4fkTVbDdqhtmrrQWcehbUWnKWRi65j+z0kpAoTpSAr9m5qRN0SCeDY+WG8K/NoA/++OjyLLRgNOrqCQsZmR6V9TLA5YsZXK1xaV5IksN4UoveuFAVU2lkEbCY6etRSFutSp5A7uWUVxdS3MAliqjWxd3TF00VW8ttVtonSsoHl8u07hOC+DzZCnybG+zVje1sJOp43It3K9n6gicKC3t0qGCCql1fF9Hg3BWJI1Rg5avINbzjdlCGfcSw/waun5sTu7GF9J5hXFXL2E01yk84DaIejR7k60GxYECZ5HwNi/Gmo/9yTPcVpwR0bvEeXKsqoDeOy/57t1J97Bv6YleNqRXqtWzFWg1
*/