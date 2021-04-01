/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations.hpp
 *
 * This header defines extra atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/extra_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(boost/atomic/detail/extra_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

/* extra_operations.hpp
eNb6Ql1067WR6XSn0c/ChObGIKeRE01zlVvSue8iJI5clTa1TtypRvlALZPiSjRYmH5PQXuFUc32LQ+IiiwMENcCoGCq87mPOBTZ0gFWOwuZ5GS8p2hf5CmIPh93hqEewZLrqKLhMcKNhVL4Qtt7YeSEAuSrmEhjaDG0kbzV4+CaehB/BkRsQ2GNyV33yef7MlcLD6/qqD6UJ6lrHVTDP9pHfEWAwxFqCOAyvIuOI3707CooCR8BV19AqwjP2dz/5draX5M3W60J3Xjaq9go9jAOtG/l8hQ70+J9Uft7WXkwzsmAprpjGODSCGYnR39wnLfBwHzFK3huqCJsBGQkA7kZMp+HD6gYPyw7UfXt89X9wc1oym7jJ4pBrO56DQ8bK7O8HyOkSLflT337orJKupfIpfLUgUHtZ4P6x/ATNydI5loldmY/J1gemyjmZblmCYLMCxi2ijR3Ql7KJYnKk0iZyxMFBqaCsghElY9V9CYBKIsI8NNdFMLm3j4nWV6tlgq5wJhYPnAPXphIUIe1QVtvhEwh0m55DigAYGW+Vje0F+RrG99B1rtLHA==
*/