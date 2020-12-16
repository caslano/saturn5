/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_msvc_arm.hpp
 *
 * This header contains implementation of the extra atomic operations for ARM.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
#endif
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
#endif
    }
};

#endif // defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

/* extra_ops_msvc_arm.hpp
G2Y/9z1yf7R7XG/GoNu+lnWVfuNddZ+mek7jEvspll+e+qPYb+3OU6Z+ukPun2TyFGMwyVe/dOSrWzRf6TXrHDVPNeA7n52niFOtvdsmn9RaU050NZ/NNXWzSXd1Xyv/mL7Q/OG1Zazvsusey+8MDDlVQdLvub61xhm4O/YzFfAvel5Uwzjy5Nph3G3ncf8w6ikEvuHEbZ3nEHD/2M8heK5v/ecQmL6oR9xew/1Gy/+sDl6AhHuvR7w2foP03+uT/ttH1A7jG9jd5htG8wJ8w7mtnvTf9g3Sf28D0t/MIYz0Pk9kn3X054ns+wZp73eeSO4oz7M3ePjRn72Bm7rSHINjT/OGnL0RzvN7POJ0pC8+uuI0Y8a0cSefMmNUQdFimkoz7nXHS92lOr4vNDzc+OeZ5/NH1w7jzkzGWH5hNKddWEd93kU4XQ57PPPWDtSpvs8kP/qnC+6OPT/6pcvuMbXD+KktyNgvjOVl5SyIKi72HhcRTnWr59jNkPu2g7MWL5rn6Gu44nLqUcTFOYZJ1bw5Q8zMc6LeQ/XY2nH80q6TfePICST+8VN3qZ7fnibI/WM/g8RrfJZnzm2Jjtcj42rH6zO7HveLF98aLf944a6eOryOeOdH3Du+z32zeJv6Rs3y6kiLdeNrp8UvKGv7/NJC6lb/sravnrTY9w3q1i5t6q9b9ZwZn/NP/nfOn/E+d+Xoz6XZLue0/Pa5WX+7vbTtga+v3DjypU73fkh+F/PqN2Z3vHbuHU0uavpMIPXj2x7yO7/F73ybf/05Nn7n1cyU82riMgK/GFNW0GzmPeduOZj8ge95L/+582e+zXNmdjrOmck158yYa+bUzbwT6wjMtcyF7sNOzxiZUzfmxzuucx3XAxzX/R3Xnbg+gj9SFh3X7fV6CNcdHNd99bnpFmVcr2ej+uj1IMLzIffSjPw0kccm9zJrzg3hh/2QtbIl7AvbwYFwCBwET4LnwAlwCJwOT4Cz4FBYCUfBpXAePB+eBa+EZ8Mb4Hx4o/qzCebBHXAkPKTumwZId5gIx8HucAIcBCfBSXAKLIJT4Wo4HW6EM+Dt8FT4ODwNvgNPhx/DAvgVLISpwZpwtoXnQD0vQGV11aTlPtd5ARUxnF8AK2ESrIKtRB9xX12H+1J1v1DdL1L36M15AzvV/evq3nneQK6e93AC7A+HwhPgMIiy8uAMOBzOhifDYjgCng1Hw2VwDFwFx8LVcApcA0+B18Jx8FY4Hu6A0+BOvf8h3BcKyxISWUsSTtvfXZhben5Jf1gMh8ISeDI8B46GpXASXAinwDJ4GiyH82AFnA8r4Y9gFbwUngt/CpfCLXAZfAAuh4/D8+F2uALuhbfDT+G1MCZAOgTJ13AkHAhHwRPhaDgajoGT4Vgoe8LhbDgeLoRr8Wcx/ClcBn8GV8F18HJ4FdwEr4Zb4DXwGXgt/DO8Dv4VXg9fgxvhe/BGGE8+vAk2gzfDVvAW2BpeDDvDS+B0uAYuhJfCCng5vADeDdfAX8GbYDW8Dd4Hq+H98An4APwTfBAegI/AQ/BR+DX8DYwP0abBdPg72AE+CTvDHfA4eD8cBg/D4fCPcAJ8FhbCP8EVcCf8MXwM3gEfh/fArfA5+BB8Cb4KX4GvwLdU/wHcCz+H++BXqg/E1OiPh7a9EfBNOA++DRfBz+Al8Au4AX4Aq+GH8GF4GP4Zfgyf1/v71fwj+A8YZ38Qtc/3gAE4HobgPBgHS2EjeCmMh+tgE7gJNodbYQv4NEyGL8A0+BZMh1/BtjBAW9gOxsD2MAV2hG1gFjwJdoEzYTasgD3gubAnXA57w8tgDrwK9oc3wAHwbjgQ7oCD4J/hYHgAngA/gyfCWMo=
*/