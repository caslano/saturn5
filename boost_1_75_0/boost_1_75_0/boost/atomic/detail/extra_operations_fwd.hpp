/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, std::size_t Size, bool Signed, bool = Base::is_always_lock_free >
struct extra_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_operations_fwd.hpp
yZrdg3Menu+FgaoWJYASKI7Q7+kFqbt2fte5AKvRRIL6BtXNrVygxen6YKfJX2DVa6qqNvh0j9MeXuXHjbj+kqqmdvvjWk+eNCCOQoqdlG+yaqrOs/Lcuhh1FMztp7eeSUXTPJFTswV9I026vxQ4MdXFgYQ7TS5KqK5uAhPlJzPcV2oUMIHrheGjSas8nSWt6seTq3UZ3FlKPsKYmQHNoADVgKeQfN7+xzGRRBK9QHH/AbpltKpen3c6UWG0Vgu9qlnYWi0SmQRNn9yAcwstBgedbKuCAlzF/lV0GAPyG2A4b7bhKd52tbEMEb+NEattIbyQBID9F8wpn/QJo1rdo4wCy9HkM/7Uw91E6d+GkMQk/GKVkvf4txRuBIOqQGr5UI2Typdhv17VlyeMRM6oTqoP15xTAYM56+C4t2vVRvkxZ6qTwMvJGnNbOWkOFP+8eBeaJ0gPVn/nAH5FNtWGJdei9Cdclb23dgBr4CKWQbMm0hFR1tecLzVYx15ftRf3lowMe4NRrOby4JAHzL4C6PfEX4sC05Vv45E9ZaCQbPZ7Gnyzhl72g3/che0XNXDrEjEgppdNxItNTsaVmO3LMmReKYPBWMaB6jnTCoPdwbquBJeGwjmOfMZrL382fwdoylwo+vOINwv3zA6s90E3CvPmilnQdbmcwrRkzohhzUdy0KvGu9e60l/9GrsFoq4dKYBZPjL1Bzt6YEhu
*/