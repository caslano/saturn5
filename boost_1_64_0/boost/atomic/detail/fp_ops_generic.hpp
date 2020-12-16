/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_ops_generic.hpp
 *
 * This header contains generic implementation of the floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct generic_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type fetch_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val + v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return old_val;
    }

    static BOOST_FORCEINLINE value_type fetch_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val - v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return old_val;
    }
};

// Default fp_operations template definition will be used unless specialized for a specific platform
template< typename Base, typename Value, std::size_t Size >
struct fp_operations< Base, Value, Size, true > :
    public generic_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* fp_ops_generic.hpp
i9R8eHQWoVO13KazYMXS+cVFqg3hQIqhx3V6pA1htBr3xXFkWHv871ZtCGOnTs1dvGxufq4vJJJUZOixhK8Qys9NCXP+tXfN4L7TzO/X3DtWbsmvXvri4C6Hbqp88xdD3cYD1f27v67jY5zHwbh/x+ep9B/beecNoz/4Iu1I6dVdt39e/rDbd3ndx9M4f/efvnFOshejlDP5Yv5t+O/FOEP6jS6FXeBM2A/OgufCy+AImAt7Yl/2ctp8Ebf+nY2cq+3j+ebXZa1c3rRea7MexZ9tfVbaJE7/uqzhrMn6374Wq1EUaQOJ/CK/yC/yi/wiv8gv8ov8vr3fN/T9z2fziuLFp+H73/x2f8XS/3+skaF+f0W6IUdMmvN+X1Df7sy/nDxt2kR2H5g/cMXSRUZtf77q/+eQr/9f9Pvr/v+jyr1L5nqJfu0yEBxTe0mJnysYA9ndMo+TaCTcbB1uH70/1dvKvac23GaiL+HKXC3xk6Lcl+D+pXLvVX6S8WOYfoqXeKzzwnq8aOpco/exQodQfftYxarzN5HSSbGVuPPJt7vIh+hG6c0aRTdp2qplq1TzjxaGNY9o6jDdssfhByodZ4o7ymiqwuyk9FeoOGVtDsmf3yv97mpvKu/8stww9xTLhKlqTERtOSX47TMlZSG62XqOK/kiujmQ/OWY5K9tjnWmrG9/AGkne8N8msaY2xf96g2eB6oE+PY95JCv3oh+opEge9WdVO4njVj+vwzR9cdWzsQpftsrv/G4P1fuzUZb0jkbMf16VHmTBEt5T40io14ydQt1+IatfibCRKVzHe0frYy65n8axF6/PM1Q+e+ep4WyZvtwIoqBQ6DK05cC8nRF8YIMtzwV/fZ6/7/PlbtXVDSxueen+EMjTvLzhHL3UTvqO+VlnOxteUeVqedhPcdo2e8yyoh6mWOUREudv4t0viYr/TJsXGUkmcdwpaljv2b8UTOOtjAehT6/l6syNjNptNK7H3/foc2ol9FdHRf/1MZ2nBmI7Zdx5h5GozxtxLuWcQLsovzdTLmcoY4txZ726th+5l88J/vcaXtEJ8qoUDozuMs013tq7kqprR8/TzH/Dt2Wqa5Th3qSFaKePNpS5oaR1jPhbdC8Z3te9q8n1BF103a5Z4t+mr63liu3J8rpni11RPycpevIA8pdGNXa6Ox2Dxc//ZR7Ou77lXt1lOs9XPvpqdwX496o3NdEOdzD9d6B414xde4yr1Wu7K5yPMrIVsd3czTJWGPOLdZhLC9Q48XkOTFC6b1gePCpjuH3x+rYVJ7z41U96q5ynqwdNHB+4XJfvhhKrwfuUereuUml99ooW/1Xz5I71LmsqBHGGVEJck0cVsfiolaR8s9JY+3xwLRbr4k4uSY+U34PsX/X7epYIbZcofytNEYTUoJcIzVKr9qIR3OWUSS63jj2cvXeGPD8S5Dr5KDyOyCqHTu5vsfRJPO4DrNv1PlGE86sM943hlqeZ4V6T+A4eK0ZD3EzOlyO+eJuKs9eeQ4uU+UqeVuodHKNZPyNk7JpZ/HbiHt0V57LiynTUy1qn8uNM3gaN23UqlntY7ml2zP5UZV+rlTl5s1CuVcYA0in03M5Hj6udDqr57L32n87Rl37iutTwntGZDs8o3NcntF5Ds/oQvsz2hJGdxWGrqd+ayNPl/X4O0uCOiF/oYBKf67uH7nkEKENSjdc3mW4d4huZ8c8ioVr1fmOspZv8L0im+t8UHH4pfVotMzfk76le5Bc8/20Nq3zlnhyi5epWx1xyzPKllbRbaef/T9X7g2W5yf+089R5ydo/XvkWrCtmabPxyj3ItxVyl3mfH8QP8eUTr64o4y3lLu5vc7rdRA=
*/