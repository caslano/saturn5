/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_lockfree.hpp
 *
 * This header defines lockfree atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#if !defined(BOOST_ATOMIC_EMULATED)
#include BOOST_ATOMIC_DETAIL_BACKEND_HEADER(boost/atomic/detail/ops_)
#else
#include <boost/atomic/detail/operations_fwd.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

/* operations_lockfree.hpp
NhX7KO0T1SJrP3qeBLHisD22CS2sFyALS+tQsbhi4Ya1UiDor8rTropdBx7uO7d/0nymKCqJg8v5FCOTvDXeDYBZLoIJJ8doK80CDp6vKAjhRHKyI7Np2zy6de7OWh4wQCZou6qFtNZgVPFRKV1MmUfcAqa72+mvfg8WtdxrvbVx0+KitRG9GwxFgYA6FzzyaRxkx1GNAD9VmWGSaZLjXlQhdBHB6XZu9tir/tB50/FoWozj2uvD2MhVwSNYyIFyBV9n6UWUaACmEo8y/1GRtH5qnOTr10uQhmxDF4ELUMvP70wdkShaTG+tKwLitgrfq0HgZ6QO6T0Lag2A0ktm3DrjWiNFgSgaYZQeOFp/2QSRJVMXsq2NnFmGr38PiiOhqYjw0YUu0JoNU9QvjmptLuxATWSxlZMV39sHoFyaLODcESM1JUxSGb93nUJU6HIyPzEOyLW+RcrkSjioZhyat+J1EVeRc9eqUHxqezvw6N7/6Gbc7FbrMVC9foZmXA31igrPkmBj6rOVIxZ+pVZLkxK+DUHjOpHOv0l7WQNJRV6tg3Jd+Xo3ZN7wjg==
*/