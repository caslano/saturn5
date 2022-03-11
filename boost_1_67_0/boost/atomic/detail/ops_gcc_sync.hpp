/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_sync.hpp
 *
 * This header contains implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/operations_fwd.hpp>
#include <boost/atomic/detail/ops_extending_cas_based.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct gcc_sync_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before_store(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
    }

    static BOOST_FORCEINLINE void fence_after_store(memory_order order) BOOST_NOEXCEPT
    {
        if (order == memory_order_seq_cst)
            __sync_synchronize();
    }

    static BOOST_FORCEINLINE void fence_after_load(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_acquire) | static_cast< unsigned int >(memory_order_consume))) != 0u)
            __sync_synchronize();
    }
};

template< std::size_t Size, bool Signed >
struct gcc_sync_operations :
    public gcc_sync_operations_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        fence_before_store(order);
        storage = v;
        fence_after_store(order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type v = storage;
        fence_after_load(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_add(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_sub(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        // GCC docs mention that not all architectures may support full exchange semantics for this intrinsic. However, GCC's implementation of
        // std::atomic<> uses this intrinsic unconditionally. We do so as well. In case if some architectures actually don't support this, we can always
        // add a check here and fall back to a CAS loop.
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
        return __sync_lock_test_and_set(&storage, v);
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) BOOST_NOEXCEPT
    {
        storage_type expected2 = expected;
        storage_type old_val = __sync_val_compare_and_swap(&storage, expected2, desired);

        if (old_val == expected2)
        {
            return true;
        }
        else
        {
            expected = old_val;
            return false;
        }
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_and(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_or(&storage, v);
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        return __sync_fetch_and_xor(&storage, v);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __sync_synchronize();
        return !!__sync_lock_test_and_set(&storage, 1);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        __sync_lock_release(&storage);
        if (order == memory_order_seq_cst)
            __sync_synchronize();
    }
};

#if BOOST_ATOMIC_INT8_LOCK_FREE > 0
template< bool Signed >
struct operations< 1u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)
    public gcc_sync_operations< 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public extending_cas_based_operations< gcc_sync_operations< 2u, Signed >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_operations< gcc_sync_operations< 4u, Signed >, 1u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 1u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 1u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT16_LOCK_FREE > 0
template< bool Signed >
struct operations< 2u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2)
    public gcc_sync_operations< 2u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public extending_cas_based_operations< gcc_sync_operations< 4u, Signed >, 2u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 2u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 2u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT32_LOCK_FREE > 0
template< bool Signed >
struct operations< 4u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
    public gcc_sync_operations< 4u, Signed >
#elif defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public extending_cas_based_operations< gcc_sync_operations< 8u, Signed >, 4u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 4u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT64_LOCK_FREE > 0
template< bool Signed >
struct operations< 8u, Signed > :
#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
    public gcc_sync_operations< 8u, Signed >
#else
    public extending_cas_based_operations< gcc_sync_operations< 16u, Signed >, 8u, Signed >
#endif
{
};
#endif

#if BOOST_ATOMIC_INT128_LOCK_FREE > 0
template< bool Signed >
struct operations< 16u, Signed > :
    public gcc_sync_operations< 16u, Signed >
{
};
#endif

BOOST_FORCEINLINE void thread_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __sync_synchronize();
}

BOOST_FORCEINLINE void signal_fence(memory_order order) BOOST_NOEXCEPT
{
    if (order != memory_order_relaxed)
        __asm__ __volatile__ ("" ::: "memory");
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_SYNC_HPP_INCLUDED_

/* ops_gcc_sync.hpp
lls1V11uYRM5Sfywbr5Al2iaIZaZJTY4ims/irNr2+dq2wdqK8DVsuPQipNIbiiW4JgjBnUYjWcCyVPlh2LBSf6OWjBPXD1LDDtP3OggBqMVJ5XsUCTBxaRak2pUhXtWLxcayYKkLgz2lPCx4ymvRiLKhOjAg+jRp9xyARKyWgpEtn+MRLtRlB/IaXXEg5d1sThcQYM1kBUMlh1s7ZJ1BgyX458FxuyGQ+GKQyEaeArgYwawDgADOABARLYJgeGV6CkVaGHjA/h1NqfA2EDwVifZQXpEmVmu5dr1OmtnCSuR3HE+nPy6U6nqcwTUXxs2Gn68lT0wNRJir9IvxYKKlSsHxBhLJRalm40VbSt8/L8AY+xJZAtzAIBDS829BVxczZYv2kCABEII7u4Ojbu7e3B3b9xJCCG4Q3ACTXC34CS4u2ugcXcafeQ738x3zpwzM/fed999d//YVbWqaq+ytda/qti760YwpDCEvjneQJJPRFo/6qb4MtCjb07BSTf73FzKRN6HYpc2aGactf/rfJA4eEZpO+EqPOQBLKiHPKe/GgArkNwkVCDdg73Q5WOr3pN9KDx68+3BEgEye5g95LVao5Ozz+4hOrKgiHdc3864Mb2SjtXnTW/FDl/bbYbjn+tPu/Fr9iAXpyNKb8Yqw+qrIt52PckXtopW/zyBgI0LXRkssGVkf2oG28u9iNrsOFUVZHfHAdyxx4vIgFM16Ax7OvAs51WjSzU/R72eb7qNlnTzz9Mfw25Koqje+QKqxHSI5upHZFYDeCDExswlMZtvYDpFTPFxTMk4TFETJFVd++hDlj6qMXcmMAey7Ad3LHu+KB3t73NKMfSRr8lQhqEqXG72aEQLlQ7UeHydkyeLc6XDGgSCjaJD9Lkow5/iv26E44s1inMPVrGh/Fj6inJWOEldnncxIBu72JHs8M18qWuYw9LCYKL8q85pF83LfEWWxtzMkGZDUDdYlrJ1+ifMLlzapRN+tJSSc2r07JJZ4ERMHj9HKSGfh2ln2psEfIWIz+5fOGp/NVVl0WFk5wiPk8iRK4+RMHHYrGO0CD8UmUcmjd5JUyviN6UqVQ6ioT6gDbzvubdOUTc2rh9Ai5lgMzxK9mq09yIecK9/m6iuGe+QMqil2ZwhUgbat+VPkZhxP7JPsTkkq/NIXZgh9kydrf6q4FFv8G0a/SzNYKtOS74UiPJwSH64KB4XfXhIXstk44Rjo7y4IElNyDBBEKG/hdk4tNW1WwU83LBQu6IZAB+EAhufDrPPcpf0m74eg1PV5QZq5L5ZJSXCKTh99/uVcfGJil0gy52dRodbAEXA6jYy1ZVRX3eFla5EYIKVnWFdZ9Zz4JWjcpXj9XB4KYW6XI+iPnd+jkB1m5PoanzpRB8YBU4aGtx72jT0a5PE/cOAlE4SlMkQLpjmO1GtI2qtFzyToWjEbMeH91wspvs3hWH7mGocRV5yhE7GTQi3fK0GW+BcLRvk28WBRW72hxYPPeP6M8C4Kw0nro4kCh1gpiwrRBC5TM9YfaaMOjYzvGFidD993hHZH+CUL+oxWUoer6dtpKc8IU9PfhpYd4JYvbfH9L63orHu6QLxKIkDM1HKdv8l3sKY/8HYJ5g8GmV9msFY/mWf/E9CYQIGLPOEi9ijB/Cp/qUKI5kftAyFGZQ1q9ZW79qJXaos4OXnEgisRaV1pW1pTj9Fi/eyOcNvUHc2K6UKuCAP5Zf++uqB3mLMNJxfF8ZXOd/YSJlFPcNPk1NOTJcoSbR+k3Ai4yBGOUIi/64xumsP5PpE4m6i/c3C0dzVDWRh4oD0HHIytUUCspKykv4OCAiwiD8nuNk4OUqYuFmQ0krwAVlZedmAQB42dg4uIAcTKycNKysN3d+yOYFIaUlFn1lYkKpYO7k5uVo7OZOKq3OQKpqY2Tj+pulYFJ3M/2LFxsrKw8rJxgPkZWdlYuX4GysVkJO5u5nFM6//yMryuYC/WAkJ/Xt92f6qr7qNjwUpEMii5uTkRvo7Xo1F9hkASf9o03NYQk+AU4KdW0pKQkyUi4eLg1eCm0dcQlRMCgjkleLm5OXk4hQiFeDiFmPlZOWWZJMUZ2eTZONm5X5uNK+4pCRQjEOKl4NXyIBFw9vZguWdmoUli7YeGymQlM2ARcHC0crNmpSH57lqf/Yo4PmCAaA+uy+eYAACv8ln3wkAA4MGgIGTer6fADAvPgNgXkoAYJBmADAorwAwqGMAGLRhAAwGDwAGSxwAg40KgMFRAMDg0gFgiuwAMMUEgH8aM1c3E5CbF8jCEomDnZODG4mKSlJZikpFQoqJjfmZWt8YnUT6u25SMbGycCVl/6NP/miJuImbib2T1V+dyv53MuDk7vjcmSzyNuauepy/n/mz+X9w+esRzr8eEQW5iTl56f3udDYuUg4Og2cmjm4Wjm6upFx/FKpoYW5j8h+yqJiAnnP8WSs1C1cnd5DZcy25/6rl7wL/Ko/rr/L+7Hp2Tm4WKRt7NwsQi5T9s5hJWJg5mVv8NRxeCw5qzS4QldclIoKFHzifspfCxKWZjTFofLmPhHljWQTk09BClV+8FBGeHe12wXCs8Rc0sh4XNwASRiEWVbmtsLjxpuWjG0wrFIt1l+eSFf6spvXsoU/Yrl1ubDze5pQxIBZaNmXJDmcHvx9BhX3LxKWNsDbqiZfBz8SkANyJ+4YXXJ64jK0eIjujMQOoXiandW6ZVLKpXhozoxJgL+rKn6Q4i5++zD7avoyCcs2AVXVQ8ED3fYyK6Yr0TdWhwrgpypoLXRwFSioNi5vW6iuZtR3EnWlI2hbu7zg8iDKcka8Of+BlCraq18akx6KZChpEQm6pzMUGN7a8W7BBxZIXaqGevYpy9t5eOer2bRd7Ob9kXd+v/ZJ6IeM/pRJaQMiNpcCxk0RIE2GeMckTGvhiJhtpsvrpx412p6AstxeXkbQ9c3qA6BV4AvKS/XhVIJuxrVx4drE34ui6fXY7ZPv8FpG6N9zgn2ST+69xkvRyk1Z3ex6Z57C0Otuz+6zXbiD35zESEvqt+mbqFm56LM9yy6Jh4eXGIuvwPOJif/PE/+bJGrC8Uza1tTBze35a1oGVlOe3fPx+/t/K4/mrvL9p6d+ys6i7m7r9pv9gwyJm4+aqYgESd3JwdnL8LXc8zzJq7wRSdzYxs2CRsPCwMbNQkxb7N3mSENf4mzT9m6yRkgJ5eFi0bcyfw2xcLDIWNlbWbs9y/Je0Pc09rQHeyknJPus5zG878Ow8LQLEAS8REBAR4F8iIiK+evUS6TUmymtk5Nd46BiomET4JMRE+ISEpJTMNKTkjBSEhLTcdIysbBwcHCQ0vII8QAFmdg7gbyYwr169eo38GhcFBRdIRkgG/J++njoAaC8BjIC3cDDkAFg0GDg0mKcuANYfVf2H6+VzNObb/xgL+B0L8y9j0f45dgHwGg7muRQ4NIAwILvjOQrxaf6fBIX3v8Idtt8X9zNgsHNw/w/hDiepts0zX0/X/4g6vy8eNjZ2NiD7vzP6n0cdNtb/gDpsbP+EOrz/DjockhJAKSkeHnZJDjEOdnYxXg4gJy83Oxcbuzgrt7iY5DPocLKLAXk52NnYRcVFxTmkgM8oJSomxi7BxQWUEuXm5P4vQefv5e4/BR3AKgAGNvT5vn4GnUoADLzBfwUkbOzc7P8X4Qg7LykP6z/hiDTIyd35tyH4w4qwyP/NU2fRAJk4ujr/BhQz778V8kfOZyPzD8jzJ9P/98jDwc7z3yFP4mD0FOtbyfaOpzWqyp2iszziRTTSKkI69PR5eLKPE8GfnowU5iejDcZ2k00zwXuGRoveKBVkdi/uXl0sBqCgrpa/FX6qknb+QRlCL/W9sDjWugUfSwoGEkIsVUcpNhGyDr+g+ZWtZPxjlsUImPC6Ui1HAyb80o2jqvqiWL1AuJtQWzr4cOQhZ5hGgxrD+dKj4du6G7aH65SPEt8SSdbKVuNepMDRZmOo0a+7gpMJ017sO3VUoVdAVycZOgwX1Kw4TjsdawwrNOqtEF3SkErjQPaU0tfRsjjK/mIJ5NS2y6jS7+HRaMv56im/sHZPjxs3uwpb76e+nUo0EJzRbwyfTLXn2Yvwnvj16Ow24ro3JPA46ooitIy8opUZL4MqlG8b4PKVejgNtNcsTa9C3ZtxmcC3TzPdlV/r+n3HWrUofOU26jCAYcl6FUmfXsOI5VU4pgtfQmOZs1oDlhLfNq+7JfGg1veqB8esXjxf4iphx/cbV9wCfockn78/1A4IlLuoLV6O4t71+5EsFmpgl/sHJMkUQb7Pn817OtyhCQks+o4GXbA5tnemlPHSHr85eMJcAaQ9PI7+r0OZ1LOYPkdJsf0bPP0vgtufFsSBjZTtzxmsw7Pa/2liHNhJ2YB/BjlI2dj/CyAUM3G1+F0nFiU1VXVVXQZRkI2JvaLGM865mj3nNnF0+53qqsf2p15KOj7Lr42jFYus+bNm2Lh5M8mwKJk4WDy36N9x9LdisLJoOGk62vwW9t/TuH/Xl9/c/qoI7/8hRGbn4f4Tkdl5/w2ReVhZ1BVNXO1I2Tj+1j9/B89HgDd/mHuA+d9g6n8LOP+BqyoAGjjA8xwf7Rn0foMi7rP1hftHXIR9gYD4nEL2DK2wMC9g4P9KgYGDfQGPho6AQcYmavIHdv426LCAZ+w8Pno83lso61TMqw+vGC333J74vrGlWaf3KV3aAcsoW/94NN+ld6jEtgGFK3qBvl2ocTVbbiMmVUdHBwDAyyY9fbfCLfimhMC+d7yhLg5bwdfl8nYIihjec9q44/5u0VIoqrX0c7XZYkzFjFWfgBZ31Kh4cc8i24XDoblkAvGSf0CtuzaWZpTX0JAZoTT70H9FfUszBvyXl/C/mAH8Paj+fyopXFzs/0JS/n8SDnzAb9mA+/vOgYN/AQP7e+ZF/fZZOmARYGH/kh4YWLgXaM+ywS6KrgZfhenyVfUfZeQcun0+uvY7p21STQjl3cE0gxWS7PV8uUc5ZoLvlQUw9ff8S3dyqAJrYjq6riDVkCG/hMRGGbj+7NPquyQy8wxwC0jEyxI+58szU+5JSF8xkiTAD+DIWDm7pfPzF8ZXcvIWXluMZmsgNCvnCaOM5wEQ9jCDVPUa3g+ZbnNiNXsR/mR2/U1asql8CJ9nRGYL/4ip1W+s/1GDNLdeHsaT0PSIp1vfBV2W0hnA+W7yrHjrKma+uCc7SZu7NmA4kER5oCR9geFWlTbxOVf49w0Mly5ZyrgOQImdMvPHwNkS+oXJwa9Yi9NJh3Sbi92CK6XOv9bLf3MM+75OGS+zQas+XIZ7Gd3+NZFuaybSp1e1/uLcrkfQLOIBa2AzFoDl0kO/EanYi0YZL809p/4TWHg3TnBA9wtPw38nnIRI+eVA3rGEPRdBEECzF7ckmo2bUCIx3YZpnop6Qd5DRrY+fjmZTlS9AJc5zjQRi8/lwy52kaha/jO5dOQJgNEmNC3n6VpywTjUcJ1MmOBL+De/DDOQTE4ZnkhOp/KKzrJzriBTeR7BXjCYi/jHP4RefS/DeU1+aurIINn5suVdevi482lEd/a/Uhi2/2OmFfh/j8LgPa9Sfl9/rzAwsIgvnpOI3/6O/3t1edYXNHQ2EzgyUZd/1JPTgqiW9ylqOiz7zOBqoxkDhXmW4091OQBY35u7fe5sLOGE9ePSFT+NNuWItnPvdu3jQ2Uk5cLSDKU/mM64Lt7s8x7eu0d6nP8aTCEFPBP+fCO+Rko1WbMTbVgntbefSaEdjq4LDbyHehlXJbJd60w0GJ9r45VIOV+Q8JvXnxLQcH+eZ65A06HMkDSPd8GOt3TBnwn6mLFCju7q9Vl2eJ0p4zLCStB0fvTdTC2AcFvQqoF3VOdwxHXG12137N/bh/qv5AL4f8qQcrL93ywXsC/gYOB/wyzFbzsK90zB/J0dRWNzgQOyi2KSvX+Bgf6PwgFNt6Fvi0njine48LusTTKSQr3qAcrfL9+yBtazxRttHX3OfJzrkVU7+jw5cFn7+559vrcT0/Oi3njLNvGMCamB8qJQUBRFS3oZ4bTD3yFUEFZ614w/JkSUXDzcCfTvPAFku6dvAx6yDAu2H9Nik4wKjuflNDTo5MJDbNQ4kNvHmt8v1TlIji9U6tfn7J0OwkyvJ8M9M0OT+ETJ1lgh1Yp/gRiY4wnXaLtQaUBUAj9o2+HutRm0dyoPM72R/DJXHB13aTbPMMoHrn2M/zerd8zR0x8264z5WkDPOfOfcw6+UCULe+1oN/7MDWZ1h6jjSLe+FEfa9gdooZLIkPc5p9pvnh9oY7s+cXPuPHMLOr54s+bJpKeFnFdn3Ojw7s1zq4gM6X7z/IEpYypOkHbxzE3E8xbRmT+5rAT+j9qXImpHP+fE/INnOCUbWdSwzzO3HP4HuO9Eg1rTH3YO3zHraf1uHOJzT/3mKYmOGye19dxEmzGix/dLqC621X/U3twj6cK9uJgo3x8m4B23R+TsZrB7iVQAI0GZLkkEkkFMdwhz7/rPFJPTrzhG9kIc5PuHoT0fLYzsxfH+lZKw/5/aKQL+X2Q8sQEw/3Hf5o+J6L/a4/kHlRhL69QCAHCK3eVesSb/Y0DmP5/m/at+5/gf6ndFEzc3C1K956XP742O/5FRkAaZeP+LZfhfA0H636CY14KZMa5SkKyK6MfUSqBWAiW/488BHv30D9CXdOuJ7INpqrYlfSFGqUGKtk9NNo0j5BpsUTINaIfq5J0OmJEfVFmRpH7Q4sLnGWNG8gAAPi9f+/9z4zn/+1WZuKyEurerm4XD712k53zKIHML0PNqjFSAg5eLg4uTS5Kbg4uXm4Obl5VViEXNwsrmuQzv51S251QpLiAX5+94dXdnZ3sLh9999dzE30w1nKRlJRRNnP99VffHOu33GhBk4/x7H43tb1se/zYOz4/8zvB7jID/al3H9s8bIUAg+3+zEWIQK+rYSfpWUpnV84tF9WfnlvrYBY6kFmvd6UMY1kgDMP4YLovfXbQsRFLa9BT6FCVUKH83gZCt6u9cS2RB6Oes4Ko/h37FcQvYxs9sgH5NJF3ms0pbYJWwxlfJNh1K1RYQaJybRJvi5zclkRLwM+IbX46fYFHEBGrlcPLgm4+ny3KzoxV/yNSlaRvdl8VdwjCyIy+NEFplmNuxVupBT2dF50iK7NnSlIKDvx4NVHkwDnzt9ItBpql4z2osvm0VxxH46lrNwyRZaHMzv0/rB+KCME33RzEHxEfAD1W7jX8e7r/bMhD9vdZ2e17Js3KxiHpY/U0QObnYWMRNnP8URm42rj/X5G6kTOxAzt+daOVKyvFHx4v93rZi4uLi/COJFMjKyvoHM4M/Up973QJIyvbHfsMfEX+s1/+DZMm6mdjbmIk6WtlbkLI+a5jX3yoBfGbKov4scFqkPDx/jfRfksHy7s8KcrLx/t348/yLf8FwPrfubwQb6bN8sv53/5I5fED8gimJwfPG80uWnzNk6DCOvaHGlwDwvnVRD/QGNtfZGZGQ0NMLpuszmsRQOB4bxTeKws8wrtgU1G9ZETWGwiqf0uYXGk26Z68fHh5XzwVXrwFTGu7KytrK7r+vUTFaMjCMjhRPKq/5T/CHGOZM3jegNirwcJ0Z9UVddRlGySsbX2LIcEZrpdc4b7bjMfLu6Mt+A3Zfl6jj5PrjQwrzNd6PfRjbjGnNJ90b5SF3p56v0FZHmYz4tvc9y9NE+06sfkEZtpKwU1qu161i0IGmQLD4OWmeS868iUzFB7cCb2Q7JeghGAIjM4uG7lfQAvJgUx3Rke0DrpH4BZqc0kXgx2D6vvR25ku81sRkYWzd9t6VkslWksn7FkFfYkct0LRMCoEOvmz0msstnpDMXCWqixp7RfLWVED0wHO6H78p6/N68bpOF7evjSZvKk9DsRsMr43hbik9sL3l+7cPGbD5O+BTl+flnQxQFtNLiQLBRiItlpEf3pt+6htGAgdllKx6bI4cJa3FKhmz5CtXGynzWLYpftC6CgAILPfTiUBCE8svQdFq2Zr5Ghxm8sGMffgR9yRXg0P9WZ5Zd6pNC9f+Hl4LrG7zCFf/3NLc0k8C+/pGzCXljDROPLOeX43Z5jf1hWFkkxMqMvavkeXlB/pYRi4r6L8rhrkmfU1V8j0ZIAr/Me2Y6SehJCj5a/iwZKsRP6tkr9HSuzzcVXE6z7ec2pAgTgmM8yoehlJJKj7MnI+ObBP8KUNphKKkTxMiBeKPKzLwkCwernVBGrTia1WYvor9FsRP1oa0AlMptNAGu3JQm7K3iHYs9+vgim7JnEIA8bskeYjeiPz05JnsGvxlgx/cZPYvPQ6EnbUTx5fxJmN7qh9pHxIDlIqrNCimg0wz6DPlCt1C3KhMbN/zZcnsYboj2XzLKs5SSiuxKrJK0Npr3GsElzXpt8bWqrOoO1EKubffYuw6uHH7oLfHWUHick7LTpn6ubM5synIzuHP4dH7bROnMyRqdC3rKINfYp07ROUSvYulAdOBmXalkfqcgVkKFDV9fmqSSlTbQRBmitn4OnOiIgrUOJq+c3N+75QD6uwfO08hhGB0zqTQl9pHmkfqxB4nDwPYiMI5AutrfBYMa3dBPlM/rulieG8CNl1+R/96jiYwCcr+OPWgckuHuFogcLh2l2RFeB90Vhq8n7idc/EwcB7rA5BrX1u7S8Qh8ms/iw8mUTH0cM48Q0oMEPHGUnNXueV8ftDe87mo/TfPUZ0/3AfSVZqYxcnP+8hxzwcfGcJaNlugrQOLtKmeKkB+FeBxrvkKnNA1/XGen5BIo99n0HwYaD4EHfqSqpqAqhqRqhqH6qyKIk5ZhTw7V0JIPMwvGh0KS3WWTxFXoUJulCfRJhp28BwbgQ49MqKsTisl84y/e1IlX82TuMqTCBAJu/+MDn1FdVZDEWekQt6e23P/KR5KRHWOKLelLG32KAYlFIESSjQSijUSSoVRqqPDiG/ISOTThRUyUqElLaKr5idKaMTFf6YvoMylf461lSMvvhKWgeic0XuHHsCG+YkHkAeqSrlrKstKcKqhqw4nSkyVPt8Iz3lRHMIK55/9qOd4gufnuWRlJRzS4j8vDCV/XhCgQquTlCO3HUzsKSxTi1fVK6DMq6/ilHJIj49ZeLM5SbyZEAzatW8v2hNvhOTq8+Xo8z27+ZAzYXmInjY=
*/