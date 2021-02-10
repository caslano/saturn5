/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  for_each_n.hpp
/// \brief Apply a functor to the elements of a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_ALGORITHM_FOR_EACH_N_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn for_each_n(InputIterator first, Size n, Function f);
/// \return first + n
///
/// \param first    The start of the first range.
/// \param n        One past the end of the first range.
/// \param f        A functor to apply to the elements of the sequence
/// \note           If f returns a result, the result is ignored.
template<class InputIterator, class Size, class Function>
InputIterator for_each_n(InputIterator first, Size n, Function f)
{
    for ( ; n > 0; --n, ++first )
        f(*first);

    return first;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
ea9ioDKDd7UT1hUfK1gVE4K/vevdATOnUIe5sw7YMJXngHY9Y7LKqZqg5ep/n73yGIzXEV22htcksIRcsbgUuCSZqP7p3cR9xg1HD4cJm+CAkYN7zUxlU4u7MAITQjN3gw4j+1nEj5iD1mGq4RhHB3K5LORidvfPOzB7hR/3JGC3S4pCKOYxIbgebTw5GLu2+ioUjKR1TnwLO869/3K3STwGe1EkUpH0F/H4FJAHXN8ojE/z0QH5SQv1l6J4tuZT35K/zi7lE7IlOTQy5jQCOdI0D3QEdiSaT1VbA/acAWYxhMfeH3s8b0WsUlkIcIOYwFJU1kCVbFnFXVnerYwSO4DHjXfZehJq8IEM+YdEv7ZpRq53RTnQX7Ee/V42RwuvFUuUvFnUoe+VmnZ/ffvzp7fvtl2zE7sos+ZoTxokZm4lncA2Z3D65BKEwxm8NwzIR8qlYoOiVIIBi5Foud8eqnuMSMwAGlPnM8YQmCJdATIU1KKmDZO7PyDDcXdlzedreqcikGSUQpg7zvNmHuT7r5Lp9uq1zKvVmkAZwchb7pnrgm3vkfwHAKaHLVsPgljrK47y4cO7RJtI6VfMm7OITgS/hfaZ12Vpec1AK2CYtCCh++HHj79IgHz4/pdN3l6Mpz+VVcKIZYVuqiXG
*/