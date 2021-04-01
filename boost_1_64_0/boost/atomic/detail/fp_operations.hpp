/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations.hpp
 *
 * This header defines floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/fp_ops_generic.hpp>
#include <boost/atomic/detail/fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(boost/atomic/detail/fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

/* fp_operations.hpp
Ue8ZHbp0zUJZo4c9M/UnAP+SzEYihTA8li6QAKAKO6SYlao1HbI1UDwTB4WSH1hA9lwMdiJ6IgKpFdQMoZv2wqyePopfIN5NfhArtuVcQ7GdtI9XOOby78WRAQ+0AdQDxgz7KrkPnin+ubbDV8iSsSVJGSXBzuB978xzLJP5wRPXC+Z59ypmLPOgprXUKxlUf5ptSFTWcszZ1A8kMGtutl1/OGGIDubNM99o8tIt+0ppY7PCyYs10X8I8uWOiSz0V1x/738cuS8U07HD8L8sdgWiXKG9K2OA8QelufDroe82xTpsqaZfhXiQDipqAAmkRpwlj5EopRKIQHqercftjATAnDnIGRHQ5REJ+zFA4A4yFsD2h/IV4IG0fdmDfkG+ptExw6DRPjly0etSs5DZJ/vQrrw5VFOmVK9fRPHqRhXDAgWV2zgSnGMLDqFCrBRkNKT42mKZzfJNFsa01uQ5VbGJIuAdW30vBUa9Q8bTCH4n4CRrEZ3MyUay3msbpgCqjspqSAeaksnfprKyxVj/RgTIP58ifg3GDOl9fIjwr6p9Jm5I9WtXiBhZZw==
*/