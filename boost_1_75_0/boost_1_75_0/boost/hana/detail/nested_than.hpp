/*!
@file
Defines `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <boost/hana/detail/nested_than_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP

/* nested_than.hpp
WazcSiWKKpJYbVldQ0EUT2d5U0Mw/HcQldFvlBy/xmnjpQTkr1DKHf+2Uq5j3jdKuVtltQiNlEOrwSgQbpXZsH8lXLGP0AO/qmjntuLESxXkcRGOhTO+YHWR5s9DQR6jWahtkIrL7XFxmcjEoUg5mL0zKBOfrUx8ppAoG1zDZnJefP5kXGx2gN6znYpNGZBEee6jOfmp8AyK7Mv0ekx4HlSF52nO10qFJ5VD/mI9yyf0Bp3ggDSmEoMcQirhsUnhbKW30LYfxaZfEZvNqtikMSmyxLS1/2Usw9hCRaZ/fSwCCst8JddzhBYG4nKHTwZxeRZEH9qChfxHqfn781Vx2WKV1ZxostFyPohLTNNK+YQpZFhTh62f843AtmoUtw8Tl0P67c+yKd+oElMVl1wd8iWhnTSL9inWYTnfao3I9Npj4pLz1VN6XYr1hhR4Xbam87DigLK+HiqwQgl6JZOLeuCQTLpvpJnMC4SQfxX5FJNM4ftQ0L4C3e+1b8PSj2hZunL8pTpjCE+LoHoUr5vrUpW740YkGur1aMPyzR1UOVTOtf33l+oaxQ9GQaw6Jiwpj+i4vQGvMQ8dDvhvl3E61kqoUi/66WDqx0kBJ1w3iinqUzH9XqqFngC2f76bqfvPP30O1X2qe+7FWQL0arx+ijq+SVFmnqRkfg91e1Dh6vb+EJL0f0ZVOHyNq3CE5gNNfDvxYb6qIoexCC1p
*/