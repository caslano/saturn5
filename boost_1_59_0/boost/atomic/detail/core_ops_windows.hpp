/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/core_ops_windows.hpp
 *
 * This header contains implementation of the \c core_operations template.
 *
 * This implementation is the most basic version for Windows. It should
 * work for any non-MSVC-like compilers as long as there are Interlocked WinAPI
 * functions available. This version is also used for WinCE.
 *
 * Notably, this implementation is not as efficient as other
 * versions based on compiler intrinsics.
 */

#ifndef BOOST_ATOMIC_DETAIL_CORE_OPS_WINDOWS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CORE_OPS_WINDOWS_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/core_operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/detail/ops_msvc_common.hpp>
#include <boost/atomic/detail/extending_cas_based_arithmetic.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

struct core_operations_windows_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }

    static BOOST_FORCEINLINE void fence_after(memory_order) BOOST_NOEXCEPT
    {
        BOOST_ATOMIC_DETAIL_COMPILER_BARRIER();
    }
};

template< std::size_t Size, bool Signed, bool Interprocess, typename Derived >
struct core_operations_windows :
    public core_operations_windows_base
{
    typedef typename storage_traits< Size >::type storage_type;

    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_size = Size;
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = storage_traits< Size >::alignment;
    static BOOST_CONSTEXPR_OR_CONST bool is_signed = Signed;
    static BOOST_CONSTEXPR_OR_CONST bool is_interprocess = Interprocess;

    static BOOST_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Derived::exchange(storage, v, order);
    }

    static BOOST_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return Derived::fetch_add(const_cast< storage_type volatile& >(storage), (storage_type)0, order);
    }

    static BOOST_FORCEINLINE storage_type fetch_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        typedef typename boost::atomics::detail::make_signed< storage_type >::type signed_storage_type;
        return Derived::fetch_add(storage, static_cast< storage_type >(-static_cast< signed_storage_type >(v)), order);
    }

    static BOOST_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        return Derived::compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static BOOST_FORCEINLINE bool test_and_set(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!Derived::exchange(storage, (storage_type)1, order);
    }

    static BOOST_FORCEINLINE void clear(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        store(storage, (storage_type)0, order);
    }
};

template< bool Signed, bool Interprocess >
struct core_operations< 4u, Signed, bool Interprocess > :
    public core_operations_windows< 4u, Signed, Interprocess, core_operations< 4u, Signed, Interprocess > >
{
    typedef core_operations_windows< 4u, Signed, Interprocess, core_operations< 4u, Signed, Interprocess > > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE storage_type fetch_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&storage, v));
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_EXCHANGE(&storage, v));
        base_type::fence_after(order);
        return v;
    }

    static BOOST_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        storage_type previous = expected;
        base_type::fence_before(success_order);
        storage_type old_val = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&storage, desired, previous));
        expected = old_val;
        // The success and failure fences are the same anyway
        base_type::fence_after(success_order);
        return (previous == old_val);
    }

    static BOOST_FORCEINLINE storage_type fetch_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_AND)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_AND(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res & v, order, memory_order_relaxed)) {}
        return res;
#endif
    }

    static BOOST_FORCEINLINE storage_type fetch_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_OR)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_OR(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res | v, order, memory_order_relaxed)) {}
        return res;
#endif
    }

    static BOOST_FORCEINLINE storage_type fetch_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_XOR)
        base_type::fence_before(order);
        v = static_cast< storage_type >(BOOST_ATOMIC_INTERLOCKED_XOR(&storage, v));
        base_type::fence_after(order);
        return v;
#else
        storage_type res = storage;
        while (!compare_exchange_strong(storage, res, res ^ v, order, memory_order_relaxed)) {}
        return res;
#endif
    }
};

template< bool Signed, bool Interprocess >
struct core_operations< 1u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations< 4u, Signed, Interprocess >, 1u, Signed >
{
};

template< bool Signed, bool Interprocess >
struct core_operations< 2u, Signed, Interprocess > :
    public extending_cas_based_arithmetic< core_operations< 4u, Signed, Interprocess >, 2u, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_CORE_OPS_WINDOWS_HPP_INCLUDED_

/* core_ops_windows.hpp
7aeq6FwxrDu7JH0XSuWl/KTzp2SEYidn/9Su69EgRs2Zd9D9VbrCJX29Mpb3ocZDZSujMIKieBCFueC+7Y6EpjEc2lqMz+snlMpBmZTujPp+bXBVo2tG5wsH6WdjxF217dlUVteeb8oer5KjA1dvx/Si/V489kDrI3T0zph0XU67uRAJ5S8vNJYkwIFjzVSkG/cstKLyuHfSvd1UoBu4sdEpSGP+Ov+acIbiJazDSyiS1O0ilE+jUvaV7N+fKG0Pz/u3VR0Yncwu1oPtK/dJ8SyKW5XIL+C7Mi4sR7o+rfGHub+ezSeceO3U3+CODu/Ln74dDzzoLkQjamMvM4eMBcA1FdcGI0/bJy6OzJZWR0eRF05upuh+KB83fYEnPym7/ImL3zDJey6c21etqr5g6PlyjW9UuDvp5DeuHCnfRvnTahaPyzQfkp75cr2vVP/0Mkzof9J2v3u9/L2zGK/Vi3XI21mI8GK5Ao4rCj1tqjs3La6+1ETybXo5Eewgl8S1ruZ0zbxOExDO3oK9eBm1b2Bhyb+Q96S9t/wPwGAd+658EwHW+8D4ugDa3UA99+69Bs58w1ZeQkqvgXS23+1sa1tXJuwn5UfgyOxbUTF8SA3dGihmcQN2Hlb4o3u83rryHpsiPi+JX8eUNKpIrGWUlZ/HY9Wv0fhzhbKTHQZw+07JETvWhr5X7/iRuRne5QavR2baa7+jdkt6XAWSCm5ygcMqAuYuiFw7IIGvCIDCogLmDnyHQ/xdEfwH3npPd3q+pYVeNKbIEUHWAwDhRoChYzYq7oZ3gxb9hl467sGxRADe6Ik0ISPngGpmZHfRnYBYwqEC88DKamR3zfBH6Q0M3JmJrhinZnD+APuOAtzvCN7iA9/5gQ9Dd35TJtewAn15XadIOpq/e+HyFzPEOcMm7hy0CZia7166HA44RvXpPPCn6uvVuHfgF0Gsfox29EQARekKL4yUvw01Bi2Cfwbc6ij77FMRpHfyCxzC/WUUWqKt/hBfbxzQsy9rhhUpVMuBvZfv9TOxuPM02TvFEyuhBPMMD4aLudIUP/8+Cr2B68q032H6sE3cUdPwcythzhSgJgRE7BBfWOOkngT3/LnBSy/4fFv9JG2H3jvjR/jx42X7AVhbevAKiXgG7S4+8APHv35nlwvH2Kn5iYD4Rif/8KO05DpDnwPP8Vp6YpDTj+6EHT/rvwH6cX7mCf70Rex+JPM+FH0cD7xMBPZCinr+qgAALP/TIPCyyYf2LPn0EzdU9VjR6/b/Tgmw6PoB7P4B7PyBOBj01vVuMYT5Ae994e99tusdtJdWe3h4aD11kh6+9QNnfVxhENHxQ/f+KSdk3TG64zrLXmD4Zi+dsYX8+boQIn8l2FyCdoeNehbtLEb2Rse8Dvxkl8uHH9Dpul2pxdALteKamw7YI4smZ8mnHdCpsq+pxeAOtUrnz9KXj3jVkujQ5O8q/P72PdbjQHWtE/kmmxX1/lYkiLqluqQK8ZQcHlXUVgq/ReN5R6FRQ4Vhz+MhRbKlvLb8LQ2tKjqnfz2xwunNVuwxbOEH0oxe9ESNcMCWwt3e0n0lWlRdixvbUODd8m8ThzzAlg6mJOhMWUB2Cql8o3xjvFZHLZxcw3jV7r6wceh2cI13jDiWBJ5fXh6LupI2/bDUandqPYSM+eDkW8Tmbd5z2oZfdpihe0iLo4B5olNWxUY/W1k+EEd9JaEC1C7+8HKC5ItrYrPZDOrlGPjwW2YsoTefnVF1f2rlSPPzutYCMuNXzz7BAd/9KIvFIisK79XsEj+6ZwjXKwIY3c+24jiu5Wo/2+X9iDyPyQl936mjIVBbzoQzMRDFCpEVxsFR36sF2pbkbtEZ3txKoiiMDqLM1/2IfWOVfZFEUhj/gTpb/GGHmOemTP62VdYGbLM2pOsYNsOnEPoRSt/qBwBIn20lclyb1HZ9UeilG9Ib2yEiPawPabukzDGh+EkLZv03kfyd1vyB/ueDnLEYKqaCIMVm0kQP8ovdmMSq7KdlXc2PF1Ad3z5UfNHXJ6nm25K3QynPX+ypRhaYP8Ni9t3Gsv4s25fhFeF960CqZ0GsxJ69QBFeZE7K1viOFChSAXr6qPTb3eaIO/xxxPQJB04Xom9D3nIUHADI/5F/3c+jBcXsddNSqD2UtWoHokqB5lhEd7/duArQUXQs1sk4hP2v401Nh+KEQCnc0JIQ0Vc0eZ8emKq4pIwy3gjVapqb2yYQf+6gj2ORv+upLiD+ia+3jJh/mUOuoJdlZx5WzUr8nj8T2c0/GMgS8hx5/aijmEFS9o8MwF1m4dZNqLfNu8CeyheGNWGZpwN74huZNC4BgtEifj1Fj1sTx52raIqvvFBDxsAefe7OZYyWghuYRQwnZr6QKQOQlygvgKjp/tmR/b8TXUGzyUzsSF9cQSyH7204EfD0Cw9Oy6u2Wmrpn2MSAyf6FDcuTFIwGE1q/1Kiadh63Jiq26Ak7304HC4sMjoviuUD8FV6CmeZkWgRwopbiBW/R2Jcf9j+fjmg1C2L8o5UMogPlTSh4pttORzU9Mrnh5zs3kLFvnetvhbKq6qeldVuvYKEtSy8yoioNj9b7yplEv+DTapcmjWZs2hlKhnsCvW+Bn1rKETNagBmYTvK6xyU8ONynfOPxTBqwKNjucDzqvT5kA8mWsm85Jys5oyVX2yZkNdSd1baTYt9phXavQVC3/LJT4NDT18Ai+/qf3IVpV1vFx7jn/FBErw8o+Kg59YdY4ZLeZvWyH22rS+oHRsmlv9ZcEy0kOcWI/i6lJCGYBEHBYpYHsqbrA15IR9V4xmMN5yrzcyk2K/auF+FiZzmq+v64J7MkU1kQi84TDHgMzCXoWijOPoBfm4t3y3Q+P/b26tOUG1cjWZ2z1sQWKzNrdhdNJzAjg5wtxSETUIEJBoQyL4t4D5I2z6dQO6+K9x2r+IOs/fnyY6X7rQ335sKp3JLtSqdjubK9YueZV2vnwX0FMVhq93wVwlPyGWaz3eG9bXVntCYFQri7wM6moCRrVgS+9LbpHyYIf+A1Cw/V0VQuwCnutN7nXkD3u9jaErSF8lUg68CwW+IXfTPhNGVlD2Q+beKPUe0+l3nXf9LXL6ifPtTaPpxHVELlOoVIcJYpDC+0VAuj3DEBDhf1pMiKVL7T0qepuvtoTO/za9D0vDCFwFEssS5PaVicwbGg2oiruGP5+eYAWE8X3xnGGDH+I2yf6KUmvZYwh7uusk0jJk0/NVrUny8zYGvHVNabXr0PBhe3MqJ5sxEAuLlETevDkEPhXY8f7hGs81upWDhOHDimon7Cp8IOWr5bMpWQK05dOKmep0h1c+ldhXIYw8uRLrHWJijDSMAlmfdZE32MkSwxOsQIvMlcIF8BmYM5kN1bK+HU7VuDqR2b0Sxa20ZmrPxoY4YeIuvBr5w/Y/4yjeL8ijyoblgqSYgoEyEu2V2/+7DVRb4RWyd7CA1IDj3P72fPjwtaU9xe/Wp3rSSCSy2md6TBDG/5kbVuJ90qeq0ip7FFa2Jby64+CBaBF1c6Vs1olH5w8HwUGzxHg4X0QFXw5hBMudi6MNToy4ybdcG3UIWw03VLrIu+oQYzyPzoK3ZH7qaD6yQiZrTe4KtAA5sIRvbIOSCYARRAi7m8VacLuzvAVgDWCPQiaWrdE+jsU7rr66rXRshovasMGSclSE4rYfeLu0cPfIcsyeHJMEUxXAk9XmIxiH4xAifKFT8cNBuBze1W+OqR2l16XbKFBCvfzfSlhkKRzKkvLvMedahoOqjWuGecJwrz3joNw+fFe0TsE+5Wdo7PaZaDbd7eK9ExijAv3XoFDLvoD5a8e+MP7loObRDhWSHCTnqHWy+NUH+sU5k7TrTO/ZpHHxT+J3TfzYTv0WJ57e6PQpY9p428CFeby9J+BFrDGRm/NuNFipz8ktYiCT3tIrVL/hUi/EtH2hLnCH7bZWyDISe53X4g5fkF/D0FId7vEiTI+lMNIfGVHS5PbhhwQ28z0Uh1ly1IcSKnrUYFqIMnIab7Rq9TJvlvNiuTGp6urOOnIYtQe04Mne/7wvrgEOyZhHqREFuXxc8/NVomIVwkwlHmKn8SQOuMSZPdDb9JXuBlkgJMOJgg5yap63UMbeVpzUndN4ijFwVctaf16QsTOqnYPPcrNQshkKvYM0tGHp7w6vMyWW5+ovkDM6ypCdUe10y7DoFlBqagt9O5HkaRlF94K/IYUbBvIMXQgjp6enOrTiuxb8aj91xCOPbhr1wcH0E9uRyDnLtbI1fUvmc6g2uouFDu21tuyJIMd26DplN+0Gm3hz2JqCW30vaRyOqeYFa2tNEmVwPEuFHpH1PHfgdLtJU7zPnzyd6+dbTr+7jPeLMn9sju5Dy4Mrrn2f8NF7Ty6jTuDPz099mSNGgHJQc+7KBdI8rH4jGAvvHGNuYwNOYZDIKkrQKprUKGOi0YOhUCz2Z7yq96sfcC9rqjC4NhmFonODKCY7K2Cu7+yq7DSqH1phmWwdhVWQ8N9rw1w9Tq05Qe0T4W6osv6H2bfKEQ/jdt1TuaKSpH0SsIDuKr1Boc+myGCWMA1g7bWLVSqpvqA5Ql5N3bfyk0Iaqk0fylk3DReEpAULdlKQZN/aFA4fCBCRwuS61HplYhPPMBmeAxJ+YUliLyQhdzPiZERx6aQkM+K7QEJ6mEDIqM833Kf8J3Dw4Rpl8lKCXZaGOerdd1wszGdsUZfwx6jSSOqs40zRQcXWM9aSRJogyBBL5PmEXj8nLGcTEXngM9gghdRmgJ9L+2vI8GbxkTajhnUxK7QRpTgUmE8N7OrwHaTyBGeePiYqACJ3IuwdLXEqpjPRg2DhfS3puUO7i/lpeoh88SXGgXKENe29KlGc4qF/7emqQbPjyZyGRezheK0j6PrTiNrmPueXkzDTo/MOLfmIb5jI3T3mXp09Uvc/3rYFIdDvLxt7SkHPYFPwqhR5khVNgje9AhR/zUGAn/9Lal2RyuuFk58FXxdQZNDAuSle/y6KHPsQ3zKRS2xgRs4ezgesMPYwmuZVptcDve53W+4PT9XKQOakP9NrRifzHx7Y/DKcYEGcOEefOHceA2JjUpiMcONm33EAtWRsd5UxATRt725k2pp3yTX24lIVSKEuYOKOMy2ibaETDNG5qZL0guV2HU4XIvvoP/8WIeeBzjYl41txETsyfFbridhT0cRIev8fObIXndpYvS6v1kSKQe+wi0soq/S1c3wqQeiC/0nYYOVdaJw5xA+kjPzWTDeMyDmoZgBQqCx7DfKvuQcX2IoaMLkr8KRSsrPeq64PV9EGMIyku2tAnsweWl6vMAHw0NTJVut0NvH8rzs0X9lrCbWRDfIGXndkjJo50Gp6MeFpQkadxLu3DLOqtUk0YsYV99uR06ds3tOSRpCF9aRagkIMx7YygzDt7eiRnpzKqwliWlaxYJhGr99Qf3Sr4rI8+cv7MTo7roKjk5OaXgVIVj3okGohafFvp/dH2ay3e7wbymvWKUo6mAajK2fQmvZfK1fWmmZFZ5GbD0hsXDmIbJw5k99cPX2mBrQV8Zdv5Pw6KvnTXznStQqGQ+nBzNbWNGVfjoOy0ymrz5/Y+f4/dbs5XHE3nVPD3ji0KM/dM9zeWM552wNYplTey4IcSZ0tHnanNH1RSFNkSX7G3Yq9VrauzuuNFkP7xWKZqDg+9xJwnzUoK6S/7ka7riP8xCFM8QJyslEfkbFtcHh8z7XSqo7SJqZjUs3sHal7MB7yLZNdyNrQxMYQGtSh2Uy21t0svLB467tBfDs3ELSSKlwBgUOwk2EbRKDQqZVK0xkvB+8OdwEivvPr3RLT5lsfZzac9ob3xTXhsgip5n2K94061vgb02eQW0+XioMXI2AWLOT3dfSjEuTidTPjvVbDE3I2A6tBk/kcpt2TwCgs5nSwdFR9XYhJGsVkSAZ6bsY18K5Fv07TAT5DXIFw6e+ukaV2RR9+ZKtBb2ZeIN4aIMG2r4o0BvLuOl5P6agK1kBC2JxywDmEdMgs37TH2zsHQHxb4+cBqBCeUO7mBWtT1Uu2ig7avtJjuB31UuCedHWCETI6byUuZLJ3MyWjrf3mEXgfoowJ4jq73YQD8/BkUibuGJnbkpoeGYnL0w9CGZieAgQKbAgzByCAGBie5RmYlRq+c6V3InLxtDCyQzI6i0l7oXmbSXuCOiqgQbZn/IpK2BliBMzK7zmokAdfW2tY4/TcJELjDQ3Dvnf5Eyj0XV5OZzjZ+s1E6nUL7ykop3NK/gdb9pOuhUtMzOyLEya5tb4fgQHTVTJLZmNnKfyul5Row4voayCFCgJcEQ6CDs6OLiERrBQdFJeASwe3FIxzvAwQIBB5+EjA6UGASjQMfoiCeoCEegQQICsDh2cK5IioiOjA6CPKyqciDM7PJmjA7scHiEnCG45SOkFmZmu0ZSk7DBphepWCBCrBjAIA9QvjBA+/6tQZnXwEyMKQCYHBwnvrC+gfAA/USVAHrx+kAMJSSAmBEMwBMJogCwKiiA4BxAwIEMQP791WB9h5WAOlD7QL6rehO04nJ0eHJmR6PIjCAQwTKCBNXEwgWUJD1ARkfCRVraOBiCYN9a4pGiqGZTh/u5pwflPwJx2rDWFvV+tTM291p7OmqwG0kWjOulMly4cDLfis65S+6vyDG6eEjujwkMrzJe5il0Mc71YNPD8+KSsuKYuY8kadPcq53c/EXSyRzc3BkNUp4eyvsLz43Nj651D80NjXbf3uQ9o2kpBglMzO1NHlkj6DiE3F+K8IZN51+rpYjm3V0+NKsDqP5Thee1nN6lRYWXPVYJam01p7MXCWxzpWhNDU1tLN8tjrwmFztPla60RdHXQlHHn0L/ymYv0SJLx2X+Uv2N9zXBj9lWufuekvhNU577i02H3uZnqJh1A3IuqE7u1tvvWZa1SpFSNlpG43Tv6+NjftBVar8IG7v7XOkDZIurdlUx2seBelqL/tMMJSbVXGHo7/IUCkb7ASEq+yh3fRdJdHYDH758fVYxW/xVNQ+k3NWQTeleMFZrUlsc4MfPsX9B3Ajwa8reyjXruBGfaYw41YTiRQYswb0hvivItK2mRs1EOTVtCUOMyaH2gkIaeQYCVRZnFsqntATDkfEeFB4PHBa+rgU6Eq+xxLxB2FPZ8SyEveqJRnbZ9Mcd4qA2hiva3PaG7D9Aqrl+4rKLsLsAHRsTnNSSvAAsfQkZciN0llLzcvSJsBsjOSzReHnYAX6OXg3SbWiU2ysja2s2du/M+sGZmS8tGmcQomoueKe6GlXjLp+yMUX2H96wGJNT4uHHtdWl0gpQZACB9Nf0kXhcP882VtRzXIn3Pr76YUCC02oPpFD8Ov0d7OP2rK9rsLYkPW2dKy2AbOTdxQ/t9B7n6w2Ir1aJcpbBbSQsZKVAYViZ7MPAvpA8jaETwzzDY/zB8C+uFaVp3i0Vwtt8rSJ7h8kH08SGvEyigPvoJmRU8DJmkzIT77bbmpB43/mo1aFetye9QL1HXfpv6Jpg3EgPCH4Os/pNQ6+Wa343TD5SyaL9y0v7+2/FrDXRCq1M1GnMkWubHAvr/BW07Hf51ZXucs4MNJS6yLS2jTSUimlIz9DdIZEVPxMl3tqmTg5U6My
*/