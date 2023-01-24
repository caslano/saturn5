/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/memory_order_utils.hpp
 *
 * This header contains utilities related to memory order constants.
 */

#ifndef BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE BOOST_CONSTEXPR memory_order deduce_failure_order(memory_order order) BOOST_NOEXCEPT
{
    return order == memory_order_acq_rel ? memory_order_acquire : (order == memory_order_release ? memory_order_relaxed : order);
}

BOOST_FORCEINLINE BOOST_CONSTEXPR bool cas_failure_order_must_not_be_stronger_than_success_order(memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
{
    // 15 == (memory_order_seq_cst | memory_order_consume), see memory_order.hpp
    // Given the enum values we can test the strength of memory order requirements with this single condition.
    return (static_cast< unsigned int >(failure_order) & 15u) <= (static_cast< unsigned int >(success_order) & 15u);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

/* memory_order_utils.hpp
LyyxmE/lNZ3r7fyEOg7Ozv4zJ7KlRey6Rlkv58Olsu198EbKW1Fnx+IANW0/7zoCjxD4k0z3FqHMDr0FKh2bZOizKUrm5Fz1j2esfuM99H6/PeKfwhopby9yis5yOfjkfKRivCcffgxHc7PxyTW9NkPl9T/usbfd3C1Sc8BROwBrtwDYq7GfRxWRqxV0xZsrzONSv7neVOM3Ji1xr5poRqXtGORUafl8EFqI9qInGofKLmLIUTx+iR6betx72aKYNWj4ZM11y+3akKOacFxkla9Itxia8vWR27XJq8K55VPU2kTxg61iReEtXyfIN2fG3b0juVO1Kc28a9jjDzuyxtVD90pDruIZ5cjoYq+cbG5DUz09hhIXb61FZCfYFvUc8y16MrAcT/iIkT3yCfvvUDjzGs7Qhv03pHv1fwvagoL/IWjz/UvQfga/7nPP8nx86qFkG6w66r9OrWMbqGNaXT0Ll1RiQuK717RNiITFcg5MxxrHONIh91rFNGo27vfkIempCdvSqrRb7eTfJxlipYoFcAmmuQguie1gbF/RnWMoHR6kpgp41ansnUzEq/mb60Vjbeljnsz+uDhdyMjwvlgdThMCu4CvwU9NV7swv911mAXz/osSixs8wt+zWrKkHg7may/HbvCCv2oZ35rcG+eroTHslKqMWhKe+I0eBvj8QrPDTA2wWQOuQc3iPqPN4jklOtevPQUMP3P7
*/