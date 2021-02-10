/*!
@file
Defines `boost::hana::detail::variadic::at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_AT_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename = std::make_index_sequence<n>>
    struct at_type;

    template <std::size_t n, std::size_t ...ignore>
    struct at_type<n, std::index_sequence<ignore...>> {
    private:
        template <typename Nth>
        static constexpr auto go(decltype(ignore, (void*)0)..., Nth nth, ...)
        { return nth; }

    public:
        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return *go(&xs...); }
    };

    template <std::size_t n>
    constexpr at_type<n> at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_AT_HPP

/* at.hpp
ydKb+nN/CrMw4zrQaULI8fjxeHzsBO6dF287JxGXAIQ4n9Ig2Z5KIvQ+wSCn2BJUBkJAAPDvfBVOkfISHC108E9+OA1WAGEDyWuSeOlquX29ob+A5zM3deGp83hT9sUZYnHPTe5ghcz90EegCDEHEGbFe/YEIWYvYAbT6MZ8tlgFqe/PRdNzgOl8HI8m49HwAqZxfKaeTibTwA2vgAP9aRm7sJgd+g2E4V6FUZICzpar5Lr8rQ9fYqCeja2fU3eVRkF05QOetpaRHwI9bgFngPXqQee8ENYMjlm1aaLs+8CHVZBsX7/RH9JU+undY/kF3wOQQ1xb0QI5gwurBlmHF8LE+cHMhx4iXoEmeoTcaBECjSfOtefiUnEvI+Aos8ijJRVGqSNby9HN9jWyG1hPSF3jgx+dp9v9bWNWct3Tq77RSg0BRYcRLFQX5/Wx+TNfdLGIwmF8t0yjx/zjwL/yEoKIA0cWJ1t15rG78G6j+Aa4ZOJMrwGtMBdXgJM0uHMuvfTWA6zIxQH4n3uxF6a8TB7AxgJknSD9MiO69ZxbH2g8je+QwSSrJY4FkQCs/k5wlgX+hpJT4BadSxf2hTRCUMdeBDM9I0DY4tOuc3kHawWnA9qLo0S04d5sBX54A8+3H2DFo9C58kIvdoMe
*/