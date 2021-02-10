/*!
@file
Defines `boost::hana::detail::variadic::take`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP
#define BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/split_at.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct take_impl2 {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)...);
        }
    };

    struct take_impl1 {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...xs) const {
            return hana::always(
                reverse_partial(take_impl2{},
                    static_cast<Xs&&>(xs)...)
            );
        }
    };

    template <std::size_t n>
    struct take_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return variadic::split_at<n>(static_cast<Xs&&>(xs)...)(take_impl1{});
        }
    };

    template <std::size_t n>
    constexpr take_t<n> take{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

/* take.hpp
nSYNNkRca1rT6zRE3LoUN1qH5GoqNWqyGe7sZZs30Ax7FRVqm1qD8GoqNWqyKfrWoL1RW+KrqFBH5m4YhS12/uoajRprIgGUlW09miZcqLpS8zHV8yFr2eYNNORE5RUqmzqE8Y/+8pfB5ODDuF68LC/dshH1pGJQ9bVsjT7eFM7CO2xxGIzGTuf8cOjs7T570ZUaV2ewRFf6EF27+foBOqeuEr5MA61/2qPLF94CyrCNnF21g2C7a0j70Fi2DqExItqSUVWVLUUgVtK36AZtVBSva6bNUCqK1zQzajmc8vK1DbUbUHn5OsRl668Z5krLVzZk9G736bPGlKaVbUVpNW1UFG9FafXNrDmaUcvhlJdvR2kNGlp3fkzKqcdcafkS9qnbNnarbBtSy61X6FW5lqpwHWS9YDv9tA6yVm4N/bQOer5wsQk0iulVaZ/Ndlz8Z4PMYXZLF0z9V7J0VWym/90H/7sP/ncf/O8++D9tHyx60/O9gn/9K3eDw8ojR8OD8YC55JMnL3eLXBIKvJ9QqWqFq6psJW7ylSrs4zXFWzVTp6g2qdOqwQYMpqZK6+ZqqKymSm1zozZ0YS3crokGlFFWvl1DTWmjslK7JhtSR1Wd9g02oI+qOvX0WHsKWF6yBfAmHKPVsVqxVmNu
*/