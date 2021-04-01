/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/conditional.hpp
 *
 * This header defines \c conditional type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/conditional.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::conditional;
#else
using boost::conditional;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

/* conditional.hpp
pN7xF3sdXiXvmnucAzam9kJQY9SFZ1V9UTgh1lBr03pdR5QirjiDI9PAB9qmDI0rR/2AomHm3/meqj3SnrkW7X87UKp3CqoGdDe6A/M6cRkPR0tyIWhiqyGdS96VddaNlgBNSRpam7lpdfST+QWBitVLEtEjlA48LOEMlYYKljGnuukw2i1af0S/etFH7PLMsbgoXG75WOw/PAZtDxmFTE1kWuRiT+e9bV/6HoY7dXc/PbdItK6bLfqr5ko2KdMbe2Si0SyGJohDzvYsqDUWDzHTi2PCuNF+4Tih/blL0w8zCvToqrloCqx+K3xls87NrVlIZ2pZ3P/DxqP41PTIOI4WPSuiCv4nmezbfQmza8Va9yjJ3Zt9k2A5/wQfT3/qndIMAEbEtVXqx4mMPA+VBb6BKMgPQuiutdl3HdELgczYrQWeC8nxNOD2g1JzLotMTWNnhUBEzGotwxrrvj5CXQKAc1Gxq2c6aAVnEQwtYd4ozeUpqZKT2kYwY3kmhG66X1kLip1mS0UYwOZcXHvu9Q+G1PRuDi8Cr7a0XKAkdoNr2As2a9TGryNuUw==
*/