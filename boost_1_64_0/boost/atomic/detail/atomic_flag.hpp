/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_flag.hpp
 *
 * This header contains interface definition of \c atomic_flag.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_

#include <boost/assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/operations.hpp>
#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
#include <boost/type_traits/type_with_alignment.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace boost {
namespace atomics {

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT) || defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
#define BOOST_ATOMIC_NO_ATOMIC_FLAG_INIT
#else
#define BOOST_ATOMIC_FLAG_INIT {}
#endif

struct atomic_flag
{
    typedef atomics::detail::operations< 1u, false > operations;
    typedef operations::storage_type storage_type;

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
    alignas(operations::storage_alignment) storage_type m_storage;
#else
    // Note: Some compilers cannot use constant expressions in alignment attributes, so we have to use the union trick
    union
    {
        storage_type m_storage;
        boost::type_with_alignment< operations::storage_alignment >::type m_aligner;
    };
#endif

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic_flag() BOOST_NOEXCEPT : m_storage(0u)
    {
    }

    BOOST_FORCEINLINE bool test(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);
        return !!operations::load(m_storage, order);
    }

    BOOST_FORCEINLINE bool test_and_set(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return operations::test_and_set(m_storage, order);
    }

    BOOST_FORCEINLINE void clear(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);
        operations::clear(m_storage, order);
    }

    BOOST_DELETED_FUNCTION(atomic_flag(atomic_flag const&))
    BOOST_DELETED_FUNCTION(atomic_flag& operator= (atomic_flag const&))
};

} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_

/* atomic_flag.hpp
q99xbVs8eXRdFi4YJfWReXFPqbKrPXL+sPgo3NCx1d5V6bcYN6k2YZul3EHE323uynHTg3jAZvzd+kd7XtilS0J8P/6JG5mQ3T043tZM+qok1mU8l/0sXWo5D6er/RzxhBwrKsZvAuW/ifxY7eOfPaf0/DRhflPj5Lqrztcuqar80OuAbterVfmjaNWYsHal15NMmUp5FGVcT8fdjJjlzhPZyb6fQazbNmXY5VnSW5P952a+EXl+3afut9+X+NjO+cW5yvkl4471+pqij33bOfymxNMrj/FfU74g57DxgPUc5pLvfA7rMdlMlf9Wz3x+yzYicv5KOZn6/D3yL/bOA7Cq6gzA5773sgOZhLAhiSRMkxDZI0KAMMQgqNGCzCDBEAIEBUXFVVFRqRUZIiIiS0awDmoduCoOcNTWFbe2aNUqVUTU2u+e97/z7nt5D7DVznfh5Htn3nPPumf+d5OtrwquvwFrscU6ZrPmOutpjg6nxOUvv8innDBTv4dS5ftYi7WbwbSPHbS/+Zh10GYDXP4yM2tSRQ3xlr50S20/zFVBmb8VFVRndbzyYXC9z5B6X6L9R1sD+LsA5euXlmy2zbMD67Tpo4s9pT9EfTTf9xqu0+qw6APClHpGhkoaLXY8a4O6Ks/RMyB9q2Y5685Wfa8hDfJpMuW5qaM8r0N9TbltlRJYbp+g3P4W9STqU+59DyoaN5eixL2uv5cYvbes18t7qOwoZZ1nP2JZl/enyDj1lqlUKf88L2Y8rtSJ+aYvZMqQedeRbpiTZhLmYuc7Wfz3NO5M+gb0mRfLDsc3UGmovagn2vIO3hJQp+ZWnl2t8+Nga4X5XO9zSH60125vQNZUI6lLPv8Z4oaRk9ZPYt9lqTpSvbhBu8smpDhdVkox66rNHm5Y3+T+u7R9Zqh7BdcFc068u3ZzL+M5K2QZLYPdtJv7VRblSsuEa4acOJSvXD2V6ysfR5dv6stz0o+8mGvavNIw+VsWkJeB7WB6qjfg9ZJnKyXP8u8MyLNzK+ZUTqMbFJxvph0cot0vVv0Je7KRUS/h4CpcP2Oeth+qkMKkuur+DeaYnK/NowL9FSqTjyO0/VUN2yfJk1Ha/grVh78TwuaLCUf6sJIv0o99hjy54R/Mj9SA/LDjfvS8WCuLpBuJfxNZE92AP7XV5AWPaPfa5f0vz27Js0uai/vm5v3dXOuvseZYzr4Z1ZAqTDroNiVHu7nMCvUemg/baPvFjn4Ub9VamdeQvKzTbnIYl0Zrf9ODwjXvA/GTCYdq+/FWicU7SPZ4xSqez9EmuLfhhhO8l+nx4qAUSSbVVPvdrlprMxxyPaHNXlHp1LT+yCl4BD8y/tVlhD9mXiVXu73YmkY9D/fuyIfDKRspsHlQ2z+jhVe1xnxxFvtAcmnzKDdsW5B3Anpp+/fB+mOUH1CzraH8gA9kLEI+a7Ma0xbrfNRm84Pb/IC5F8kvMc8P3ZabsriwqZyjJyJp0ANXpRH+raYsVtZWzPQ25lIWl6X5ZftKWRT3LQL3ppk9esZep3V5wJ40jjGJu7JAd6RHUF+1QJnxyGna3SFVzN8zUHf4ZQpLGBmBfgsDZZHjxsgirzH9Bm9755Rbnh/klmcO+y7Cu7pZu81itJMQvm8l5f0s7Xay6sybaySufX2Tq7V5TMC7q8BRT3Zr+6vIwyP7KXT07d+Qe6Vyr46U8zjsmkk5t99Jdyfb5da8m4RHL8e+to4yIfKJRfZ6iD1+E80eP/JczKY720keUsq8MSPfgso8+dNgz6HJh8Cy3cwb0cvlnTcDtZwfS9cElG156YUt2+I+w/QDNmj9TPYwWeHKu/hpJ3sqw5X3QHeko4x7pRzy+M4=
*/