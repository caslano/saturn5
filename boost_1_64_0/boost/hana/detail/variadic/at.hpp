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
w60bsbATqWayZOmzyrQxlOAZ+TjCzMLGe53d09r04HtuqwPaGDDal13HlnTqxNh9Y1Yty3V9QAjtqE4mCuwxHkraTvCMKsASnfdW6/hAuy3qjbgZWp00N0q+Ms6zZLIEOZd1f8Z1Ja1xUBr/9onqFAUvZif/FmGHRRW9Zg2tfIaPOnZWATi82grl8tpWHDdZ71CsG96T6fkxQTwi3WuzwSUipwOeolp8K+F6/amk8uukZAFIBzVSIYsb8a64qspzEoiYnOUTtArl7XvjxkJiYOW8yW5+EltX3jV/eQRpfPCGdgcqW6A164KqBzGhIfFxZgUAslARmHCGhxdRe6SkZmi4ayPP/ecdGRkwazsUbP/C0aM4kAShFqVs2dIgqYvWAOnHfRd6uN1Zp8BgRnWObu9rWxmxSUC/ergOeg/omqiSJ2BZ2z4xPL+2R8a2a0BpGzmvqHacU02PZ1O3kwCpdK77Z9yFtfhDI3j6gC7toK+pDHxIl50ezkIhDrBbYHdseqAiiX0/3PfLOnGeN5m51vAnSI+14Fdc6bSGKnLISX1ELfPXrOJaRDE2zw==
*/