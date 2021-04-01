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
eyI5Wr9Eawh2OF3dninODhK7XOQiH4/9aUezSgsckSCwIxaP9MLbPvLXHT31ZMAxRIfc1gLGixRxeOFq6IR/Uf0RPEhEUaNzJz7Vdm1mVdENK+HqMv7ZY2wW7AXzLiEhCDPMfPkGCg+9A+ahmBfFEkmVYO9WGx04n8qDBfU+694qHJ1R6nVfWo3WWx/V2FkWb71X4XNljpYQ4GvVnQxAkxCmZ6vs03CAdoc3SD3xBugbsGQqVKlHjyhH6sG/DOzWuo0goGR0hUZBvk/v/8YugCTA2RMiWJCOp7jIo19ItYtoALw/2J5RyXdVtAs+9eu5lSZkauAWoiH32c/l68AZzi5OXrwcNb1uHFGhUuPVRD4LiNLOZWJPBqg64Mci4qmkbWt17b80nSDCTvjoE1blDfKBq6OGouKyqfTcIy2WRxQSjZFY1MWSfyrdjGK9NnYnOsntvufwVg2djSOMTdnhr/xPiTGShF4e6zN1JFDFbm9FO2gntVt5bW2Q0NDvb++dcaszJ8U11xD/LOSHJiK5pmxbDMs6DwniarwKB1FKWLCzTB7832GY1pGG0Q==
*/