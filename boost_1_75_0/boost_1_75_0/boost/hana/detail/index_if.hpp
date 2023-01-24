/*!
@file
Defines `boost::hana::detail::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_INDEX_IF_HPP
#define BOOST_HANA_DETAIL_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/optional.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <std::size_t i, std::size_t N, bool Done>
    struct index_if_helper;

    template <std::size_t i, std::size_t N>
    struct index_if_helper<i, N, false> {
        template <typename Pred, typename X1, typename ...Xs>
        using f = typename index_if_helper<i + 1, N,
            static_cast<bool>(detail::decay<decltype(
                std::declval<Pred>()(std::declval<X1>()))>::type::value)
        >::template f<Pred, Xs...>;
    };

    template <std::size_t N>
    struct index_if_helper<N, N, false> {
        template <typename ...>
        using f = hana::optional<>;
    };

    template <std::size_t i, std::size_t N>
    struct index_if_helper<i, N, true> {
        template <typename ...>
        using f = hana::optional<hana::size_t<i - 1>>;
    };

    template <typename Pred, typename ...Xs>
    struct index_if {
        using type = typename index_if_helper<0, sizeof...(Xs), false>
            ::template f<Pred, Xs...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_INDEX_IF_HPP

/* index_if.hpp
Kg97ZKYwe0fiDGnVM8oM6S/l1HMua8l86Cb5DxHXgK+DT5c6Xok1Xeor9BZVGroczt9IdCK97KJc3RDyocXz71KT/Vc82bEdmmSlFyUbUtp98WTPs2RXYVFOM9GLBgJcssh0+TKvjSdeH0tcernEeBbiSCEwrGjwPzYbT0gvMhG7xWMWF5mtgdXimrQzr64T11hIY7m4Jr1+zVhxTYa4ZpK4JrN+zQxxzay40Tu03tchovdfEe8LWcR8yIDacZsv5uNllgJLPRpzi1lymy0WZGtTC/dYdMI96TolDzPNIw1truVnAAMam3V6Eozd+yBFaWiJE5eKyYfU2dRo/7+j/Wr/7Rkvu1a9/LI0SaZePIR7N+qEe706cfEGmCavExc/RJrw0lzGt81nsppPKeRzN+TjYvncFc8H+jxxmMhIbpfOJZHvUDdazdTIDBkpbzTJ2ZIJBuSyJk3M3RDzFywm5XBN3M55LC4TJbllad4kkBXJ9LqjWSyzlItl6fVlY8WyDLFskliWWV82QyyblZPBJ7c4LPTSYTtFJLsKGBsoNwPAaEUkbJQdWA4NHM0C+Z7X9XTbl6w01+bO5Hy1dBarr82Z6d0E6ai5Doe5Nud63pzX7BirRzN4h6SZN7EzBbgJB5+f3EI3/GsX0Met81jgUgh8cOWsNOLIzHlO37VWZ+F/dFn0WxxpyLOhq/CQnANPbevQ8k66NQBoFXLb
*/