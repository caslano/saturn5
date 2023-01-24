/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_fwd.hpp
 *
 * This header contains forward declaration of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool Signed >
struct emulated_operations;

template< std::size_t Size, bool Signed >
struct operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

/* operations_fwd.hpp
SzghRaLXxiM8lHXFqfv9FS6H9Wg03eSunIAjjUnVsLbkF39lYCRd8EZyZnLCmAs8w8c7GhQi/0A6mlc6HfHKWjSBl9WMyk2x/tuy/itOD6TcyjJul+JeVMubLmWjUSlp+J/WpCeW+kHZpJMEJ58mc5tSQqq6DF3Zc1X2QyNrsHy/1dRw+/B6kfh0t5DThu2uf29RY9Yq8EQPjbNXUmJSJQJcMP7Y7NWenKXnnazGdV7N9NB/5zLCevnGWXIXC7KpAzxmm+ImpNa919dM0yOy/q0syS+uQ25tazfHJzjBcY9p493IHXGfw5vAKwjELgLyZ9YRcHQpRRXuhGjuRNgY4Zh8t0tkObZu7rTz0UwWbS2st62o9lTX6WtCzx6tNGvgeD9b4nEVQYglNVE2emKm1wDYQ0wNKCQnq90beG1Z2XRuMIrwsOg0pAqJU85x9bn1dVba3arvze+v2bpiAuOkUMpEz2RQ2Muk0V/PVq5fL/bjHh46+TajWfhzrrwOFMc/9C+ghrLG3NAyjD8VapG8MydoiAj0NyM4cmOfJpWt7Z8fovbNwIPh5noBo0t4iwyaas4+f6snOE1Es/XLXpO3ETVXbsjw4FyjDtWqcYLeLztwa29L6ujZtdMtKkICzzfQjV8LebUjf2iZYPwmL0ykKnSFLD8GquqlIwSnFCFP5xsNAEyfhgb6sVudsSlzZ2M1YzFPFwGgqAcTkDJr
*/