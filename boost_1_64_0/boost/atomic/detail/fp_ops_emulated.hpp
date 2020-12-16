/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type fetch_sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }
};

template< typename Base, typename Value, std::size_t Size >
struct fp_operations< Base, Value, Size, false > :
    public emulated_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

/* fp_ops_emulated.hpp
Q8oODyvLazs47z+vabVy5xtpMi/nB8qPaqZXOtnazwzG4cbKMXaoVMd6MlOnhXV/W9mHs6CEWQZ6TstKpTsPO5vpNkTC9JsXdQZl2RxpEca8KNlrT9oJdR7o/MVujiu79XvjD9QxsYtjWXr/RpVWv3Iw+tn2fZVyKK3tW1q+SBVD0HIQ3fbijjIeVO6WbuUi+l3FrfXtZaLOZ9v0s336rmUh+a79KbfNX5al7bpLfOj6/XWXw7r+zuVg1I45KgqnHND1K4euuN3LQfR1OSh993Kw6Wcr/fDKQfyJW/lzLIetYTybv65y+IxjlY3+e/Z2qOseDs57L7jNvfn29mR4Wc35aTtt3Yac0Wf2+/LgCqP/5nM6uM1xcpsL9O3t1eA8d+j07eHgNpdJr0VlXluwOVJqW9vqBcscj+wgenuta1aJXhcHvae0HrLXPbwKi15ZmOFVBdF7zKKXFiTebRa942GGl7zfXe9ua3h73OPdaM3nMMMrDaJ3pUXPsNnrtnZZRZjh1QTRW27R8wSx12PRizkQXniZQfS+Z9GrDhLvemv6wgyvPIjeRdZ8CRLvJGv6wgzPeNVd7wprvQ8S7yJrvQ8zvLwgeg9Zyy1IvSq3Xr9hhpftGh5+rfZKeMkOemOs11uQeDOt9SpIvCOs1/lr4YWXLXo9HPT2W6/fMMOreC28+1/Na+Hdr2IOhnd/yTwY3v3AczC867f8YHjXW/XBMK+PQ+HV57RD4dW/vEPhlUfZofDKo+pQeOVx/FB45ZF8OLzyyD4cXnmUBtEbZa1/h8Mrt5rD4ZVbTHV45ZZZHbrcCvU3Pe+fomddc7q7zDVOgWfBQfA8OBieD8+FF8I+cCbsDxfBs+BSmAGLRE/WrpVvRL67zL9ta9deK2sXl8oa4GuhGqcEe8AbLeEY+9zDmS7hXCzhXCLhXCrhzISbmnDtzWEdOaQSqUGaX8Y6ckgOsgbZclnTkOtvvobOh0ge55vkNjU6IxnIbKQUeTS3aZ3m7cpanA7rcLquwanX3ZyNuKy1Ketshje/NxWuS2psX0eTNTT91860r5l5ErGtlemwTqZ9jUyZE6znBSNpem4w61/qucF67cvFiNM8YU+rxnqu8JHcpnrty2PQad7wqTSO4Ye1LtUc4lTosL6l69qWMr9Y1rd0n2dcbJlrfDypsZ5vzFqWzDmu23qWwdeyDL2OpW1esm3NyvDXqyyDnWHtGpXhz1u2rkGZicRn6XUn/eYzl+K2rjV5nPKMz+PaQnKQEmQTshM5ipxCes5l7UhkMVKGVCBvIsY81pVEcpA1SDmyC3kfaTIff8hExINsRHYi7yPR+ZxDhiM5iAdZhzyKVCE1iFGADpKFFCObkErkKNJkAfcDZDgyGylFtiDVyHEkfiH3GyQHKUU2IdsXRtavjPy+nt83Mv9/3qJlufQmqOn/DZz/b87Lfi3F0H1l7IfHD7f0YfRGLjf7l2vbzkeNVzMi9FgMtzHMot9RuSfhPle5E3FLfyfz4a3r0Z2jzif4+p+1e2ZsI/NVmjROiAvdt6DWGrKNU5Z2VOn7VPHq9tHkqLq3Xzq3V7m1/7m1I7q3d/5NtRd++lTK7yZfecanHaMGv9BkdK84t3ZBt/ZIt/Y8t/ZU93ZB714vqkykbpQZ/nu9JMh7bAfYGybCdHHn4Mnh3Uyvk74PmeiwhorTuimfQeu7lKyT4r42im1NFN55eNdR7za807iveyLvHtb3Dd4zZC2TMNcv8b0jOL4XyHPff22S0iDP9nj17PY9s6siz7HIL/KL/CK/yC/yi/wiv8gv8vtWf9/A93/6QJA+sGD56Vj/31wTrtCcZ8GCnI3VOm7pA3OLipfnLif2ZUs=
*/