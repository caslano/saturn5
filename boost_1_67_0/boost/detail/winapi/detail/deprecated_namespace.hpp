/*
 * Copyright 2017 Andrey Semashev
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See http://www.boost.org/LICENSE_1_0.txt
 *
 * This header is deprecated, it provides the deprecated namespace for backward compatibility.
 */

#ifndef BOOST_DETAIL_WINAPI_DETAIL_DEPRECATED_NAMESPACE_HPP_INCLUDED_
#define BOOST_DETAIL_WINAPI_DETAIL_DEPRECATED_NAMESPACE_HPP_INCLUDED_

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace winapi {}
namespace detail {
namespace winapi {
using namespace boost::winapi;
} // namespace winapi
} // namespace detail
} // namespace boost

#endif // BOOST_DETAIL_WINAPI_DETAIL_DEPRECATED_NAMESPACE_HPP_INCLUDED_

/* deprecated_namespace.hpp
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
*/