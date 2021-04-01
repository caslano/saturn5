/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/intptr.hpp
 *
 * This header defines (u)intptr_t types.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#if defined(BOOST_HAS_INTPTR_T)
#include <cstddef>
#endif
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_HAS_INTPTR_T)
using boost::uintptr_t;
using boost::intptr_t;
#else
typedef std::size_t uintptr_t;
typedef std::ptrdiff_t intptr_t;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

/* intptr.hpp
4zAsK812VVt8J3r5g8CYx4J+jNprj7uHdxBOpxjShyac2lyrhkTY6FkJ5YzhXIgTD45SvARxABezJCkoRt28jqySkgt/BurlIXHTBg1VLEx5EN6utHR1zl+0lokzX8awAC8Ek343lCXw5vaNnF34eVk5PtomqTouIOgZ3RY2weLDiE+W+EnW1/oNfdTqpW1JIX0h2Kyitqq1cfGVLBMyeKndf3aBgGFjw7ttulQIVr9zjFDFg/d+Gx+2vx/juR03YFDVVWlRaED7c5AeMYoK8mbWogU+wiCHyen3OGKQGzuNkML1IQl6OBKhT1hFWp19e1R4PsD1+S5NilYxHHc/woLivEqtL4BjtqYBjbUJRR7QReQRJ7HqQ5KyXF7ukJFQQsPAT7bgSN0brDWV8h43tyyvNFowYEuHdwKedZ4w9leYMs8tU9GJMlbzonOF+bJy9l1ILxYGbUsCDJxRqufsIUQXTNtJ4QclV5Uv1aXhfDXQj8ssGl8ukUAQL3YE1foUOpS6MrcOVMSikHpyld6Gvf7+rTkb/Q2QSUrOLBtKiFFnF+ZjwV0Jmqnj3g==
*/