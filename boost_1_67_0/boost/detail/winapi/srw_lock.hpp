/*
 * Copyright 2017 Andrey Semashev
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See http://www.boost.org/LICENSE_1_0.txt
 *
 * This header is deprecated, use boost/winapi/srw_lock.hpp instead.
 */

#ifndef BOOST_DETAIL_WINAPI_SRW_LOCK_HPP
#define BOOST_DETAIL_WINAPI_SRW_LOCK_HPP

#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/winapi/srw_lock.hpp>")

#include <boost/winapi/srw_lock.hpp>
#include <boost/detail/winapi/detail/deprecated_namespace.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Deprecated
#define BOOST_DETAIL_WINAPI_SRWLOCK_INIT BOOST_WINAPI_SRWLOCK_INIT

#endif // BOOST_DETAIL_WINAPI_SRW_LOCK_HPP

/* srw_lock.hpp
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
*/