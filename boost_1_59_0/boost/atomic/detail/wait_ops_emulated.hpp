/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the waiting and notifying atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/lock_pool.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Emulated implementation of waiting and notifying operations
template< typename Base >
struct wait_operations_emulated :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef lock_pool::scoped_lock< base_type::storage_alignment, true > scoped_lock;
    typedef lock_pool::scoped_wait_state< base_type::storage_alignment > scoped_wait_state;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = false;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return false;
    }

    static
#if defined(BOOST_MSVC) && BOOST_MSVC < 1500
    // In some cases, when this function is inlined, MSVC-8 (VS2005) x64 generates broken code that returns a bogus value from this function.
    BOOST_NOINLINE
#endif
    storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        storage_type const& s = const_cast< storage_type const& >(storage);
        scoped_wait_state wait_state(&storage);
        storage_type new_val = s;
        while (new_val == old_val)
        {
            wait_state.wait();
            new_val = s;
        }

        return new_val;
    }

    static void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        scoped_lock lock(&storage);
        lock_pool::notify_one(lock.get_lock_state(), &storage);
    }

    static void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT_MSG(!base_type::is_interprocess, "Boost.Atomic: operation invoked on a non-lock-free inter-process atomic object");
        scoped_lock lock(&storage);
        lock_pool::notify_all(lock.get_lock_state(), &storage);
    }
};

template< typename Base, std::size_t Size, bool Interprocess >
struct wait_operations< Base, Size, false, Interprocess > :
    public wait_operations_emulated< Base >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_EMULATED_HPP_INCLUDED_

/* wait_ops_emulated.hpp
c0BMyeD58D+BO+S3BBdSQphe5sqnmpOTgz8qSc+B3NoIUbIgutdInfr1U9STMTehGB92cbGyA7H249J+V3qof26s6ws4WXTMXhTt5vmR2bOb20RgFO6zyTF7Y3SiA5BrweMG0cejqKL9IVg8l1Q2OBybQxgRr5xODtNa5s/pXvwuNe0122quQwdBH7p5UnX/HLZF0TbheQVHlIVFcSpDa+dziatNHELnk/QvDXfXCYYbKywaiWNMfbeyR3Yoadyo337UGsLIic/E2sg0ao7k7YT5uJXyeY9Zp+H54RyYVa5Tb7K+gZWBRql+X6b8pmkHKv3QV63GDoNo9A38p4ZhnA5Kz+1degAlGCZ+4M/x8OoZIrfVK4107ZQ6Mc4fHnPAAy+N86lwS4bOu4nBtwhFcPec+YSDI25WuFV6zO4loUEIPgbb2DU/TAchonvtZiKsWPlxVSJWFmI+7dYbZqOc7igxSmvgq9nZO8XwiyOn+BE0XcEfuGevFFjIdiF6sUm8vKl7N+Sy+ss6S380NMhFohbvmSkiSOxcmOIdpga5sSsKd3drwdAkVMB6LZdVidtwh8//SvUsBBFt86rPv1xxsrSuOnDHHf0kz6ftL0pqhaZUbjBQXq2PHqNPZ4rVXmHFQ6wSMuFyVULhVQPpJHmq1bodx3CVKlkLY56sJm8ThCbIa2uDbxm/2m8ebIPORy1VKf/GNV9huD7XmQhZMJ8MOPFPjBmnSMzfEHNOqS+qUUk6dfe3PclMtWQiHN80KgnGe5wOENZ6mlNrlj8g1u66UbvStOt7+ayk/T/5bIVj7ZVaFVHlIV3A7BHckJnOcoOHeS+I/yq67EO7FiJRfkYcyx2S2Ij2r0BZSJNFn68X50gj5vrOw2CVAwDheTddF3Ybr+WdY/Ui9ZWx1g0sNCue/0OwcCuflsYZl84hCBXdyWAk4wAUpP1XSdvm5W4u61vJGzr4/XkeLDOaXGjPJJLpU3cgdKZEtFBZX7QMotot7A5JqOolH44tINONMIT8rENyXklQQw6Xw0o7YwzP2wmFdwgb/fSIjbewxkZaHw7AUBoZJAxPkB8FGsNn02xmhppQ3pwuNWeIjyyTD29ltymuf+AdgYkmZMCy4S9zUJWuPy6KsjMGoran/dXTaZ/ieguTxhiKXV04YpSmbYbZPkoTyhItO+nckDyJON8SlW6N7jrtpv1EV9mFxNsn9swWBEs/kU0TRa+PUUxc1bR1EoCuLb8KTtiQ+v7+onCJz9RkYFMQOTIP0yrzujQveE9ePWqeMOhhTDsiGFlnJ6uOHBORDogrnDeQFRL/atQ2V7+j5BjIg1Fg80Oq8TWbJunNV6WqNQcokEkZVBPMDSW0Y442Tq8ECA2vlOKNiDtBWqGjtMoafONYGryoV19ge0kluREOiv9bIcMiS4X4Ozs1wOqqZPhAGNQ3gAl+MvaExY+i4/iUtINKCItt+VktVsusPgTbyNB6oRWDm/z2k4buNAYhM7yeCfm85Nq9l562piHAFGrmzBhK/vDK13HIrQQWL/4IEVAFE1pyJJF8UqgvjikChNuHq5j1jTGyQWSthDWT6OpAcpJFmS2HzCMKHxK46eNQPmT65DGnUJuy9azc7UFDcaJCk+FPJnGKPjKGel4juXJeWLLioBR8VkPQ75D8ex1tT5LJ3KWv8XGoxj6/2lZI+C2oaAgizzxzBx4LE9gsGofbg5iko87eZ0YCFvFfWnUF5HKMLZVsJZhJCULL0juc0W0BbbUabUgyd+hVJGUhHyCOzumaDLL7RM5GsxwfMjKSfCW4pvQlnfEWWaDeY27pYxbVQtkXtkTecW91BsIbYzPjWYVlc8EJRvcaTeA/lLrm86Nmwi/TifeOxg6zyaYNsVyIXFGsYLPImAmm99Iho/UxnRdvfADtVBa01SlGE7Ml5/M++2AsVumpKJOkr1r6OrddjE8Ut2AVDmL/hP8sBRjeKGAtklAz1fmBgZdVca8U4ZeYcZZbj/+bE8HfaBAqyfbd3ZP9hDaPpqdLE7fVZRR+EwPLchGQEyTHEsUzFqRxy1/EbpbsWOVvwQFM0T0SdyDUG0K0H1aGfEAqJVRT19NCCF0GC/vM5peZL3N5Kma6sb/Ot98eMvxdGLGmFk5ydFxHJo8Cs5tgRaeIoll9zx5p0fC3eJllKoqhsi4HwNn6aoiRkP+nEBk9nvvSSSTOkCk8zn7ZYnJJeVgulhKsKohMrTA5FNHiNPMfuCOimmXfax4dt+HJ1gs/nJS1YeqmrlXwWSUaPsPRy2157RMMBqMHFzLVseaAEb72XsAFJcewKqfrsNlS3xzYGUg0tZCXMJI2QjTNRwnGGySjJK6wb92rhATXyCO+aSfJr3StioCGBBpUFW3vByoCId1AI/NVVsHHs8xrYsajhrx/CTQJTn3imOHtnMsboG5YI8wpFLHcxCdv5dTdeInyurD/vkAG2dOT+l/1btkRyeYZASi/1H+zMNLVZXS2FKJXil76JB9R0sJZvwmLpHV/PpheiXjGMNJiO4+wgwoYoyB+pOVa3GqnMTz53XiAw/I1vdvrOtNeWX+4uijWKY1ZY/84S06P+qf8G0FTPsQZT5IpWp+wifeDaCTCPoxw8J2qVKv1kQcin1kWtGt5cXZgqXFAW0Z+3FTT8ytwS604ey0ULoZntF3Ak6XxhpL7j639pUCvkGJW175FyUzNBFnRf5Rftti9plO7FjYaRwgMe0A28Adj9vgTTA5qPllA+Md+dHKo8bILOxbSlRKjJaqKkxiNu9xUJYM71irnbCULmtgq6h6JZ4XBFC4yazmegWoWUR6ZLdbDksqCjnehFqWCS76DwPSn6Etw62CV+hb/Mc/sNU3AGAl+DBZUQrSlF/H00YU7EYo5WmEPde5mRroZCBx3toUUXgqgfNW/KTXsAUR5gYBEMUUn4YEqyHscuYK3kYwrfHi/y7ECj7QAbXmI8nmI4rX2awwI5EDKFs2dEAUMu+wBzV/Qb/c/3RYlnp0a1Z/6Y50XXKk61fWFo+bZ1qLSJooVWxwwW4jpKYbu3cxhdRLmpmbcpk4o9Zw0+GYxaa9OE1k2i/3hFXIDR4igR3G+IKXxXjLs2pm2/veO39gfm9WD2lYbH5oLXfUqKYEZFgmbERKSexGkQVM7TC3xGhLCmJ32ELX6YuN9ELSaxKXBBx48Qg6HG1PablHQzLbKt3CttlT6szHNygwJPYhN0i7OH7bNaiRfOE4e9PQKygUt/dVcQgJHVeHVlK8cOX0ky7YI9pA8iH0PUz2WyYsKOqlphUbbnZQpIq0OkWfOCTDxGsb7F3qmKeE1foulAl97FBgdEQlFDrXnMXPSs34C0LXJxBEMLVeQYtufgnRDBCO8mrlKIF+MfZEkdODH/2B9Bqq8BUo67nbTUOsY+G9tcbqnj5aQKGY6wEfsWtjYbhYqFBoQx35j2rFIK/ptr/b6a0M6kidS8hr3YzJoJswlQe3myYEStnBJnLaI/4F9p73Sp2K/4j3dtDJI1dZBOUXXQDTYlRAJB1c8Qc3ehqTUqHaA4fco3w9BOjsjOnzcP2paGd7MIQE0xJ2/Pwkc0EmqQjb+59DRQn1vAG1SJrrx0rhvEI66IWbVaVfrSxXMtWsHdO2Bd2IVA2CnaeH9Hu5i1MRq8V/XeF6sIlaVeQ8VfKJNHV1zmb1o1wriwIWuapjdYU6q6DEB9FNcKHycZ/F9kDU8ETMNsose5jk+DqS7RpGI8YtIjEMgDKiVJlm8BUNtcYmes2CBPjnTHgBrWEUF6zgCSnsxLOrW5JAuI474YvMDHGyXU3Id0u6DPDyNE7vVYy1oXQCO/4Ma1sH8MOjmAOPjvMjiEkFJvJLqP/ONEDnOn7WQ3fC6C5MIh7Ig/4JfoiwlZtsh6VxGum/EWdjCAnTtW/LX5BOz8qnsW5BgUPsw84FK4wZ1U/OUyrD3kzOtullxlzHTYDNABFdYeyn1mZmZBfqCTwuclrU0gSZVYCnumncQtttuvhjzIVB3b97nVbTPF9NirdM8LF6tywNerfKVIjn8n4So/TkEZP0Y2jEGbBY2byFTWPC50sJDVUkqPYLKScO+tvEFscj4fD4I/g5J2kd0t3F0tz58a9Ql5ftRR4hoOrS7wjKmt39UwUJDQh1WWKpMemWSlnznMbUT5vPsoXkiST517J0xD/cPK8FFLcOv7xklinss35zKkFDQuE9SScpjTaa4+t++W2b5NBocOa84dnvD3tocZvyFm3qjsLbwrnoRZG9gDUaIhMIDwF5PIcD4EHFHNUYcnPryOygR/0n1C4RaTZbqoECvnt3uIjFQjAzi2Fl4w3U/5tils5xTI1a1BanyNGPxYnwRBLuuZkKhhtkmsIKGtZDSlxY7sJA6Z3Sug2HZHVxeZofhFrOn+odRoS8feypjA2DmpJAWkfk3OE7QX10sV4Zvxn/o+K9LHj1xTNxNVJRNjo+6IYbpZcjhAR9u4ghbx0zSz0/gIupsGPw2JagYvZk7/fOlIlQr2s+Hby+lserYcjFpHek/6R1/d17OGNWRkC4x8lsiGRI37Zh3nJpE0cf5B6auKxd7tkEkJI0txziHJL5qjHMfKMSGQX00/L0MTqVhMio6+710YFQL6KDIrgaS6oixvLGP+m4zssSfDK7iy4C/vjX85E/nN4SYGCLlv/OsqvMEKVXDPhuLGCUDhpyj8qSHc8P9PUR6Xrth0lvHyHhQ8VTPvot9rg9dfE53LE4gMv9QEL1ec+FNhT6MbRF99J9I9NBmWgtESucxN8TzWTA883XnmGnPvw1Zf+0ywlxQYXT+h9Eqhk9ptGsWpuqnAxy88lJNz06R7GuXnJNzUBSyIC51wKSpC9WUAEBK0wmC4xAd/Uhn3Wye3hrFUrW1vSElUnFHqgV6v+LVL2SoqpSiam60812LQGoAgKA/wX9C/oT+CfsT/ifiT+SfqD/Rf2L+xP6J+xP/J+FP4p+kP8l/Uv6k/kn7k/4n40/mn6w/2X9y/uT+yfuT/6fgT+Gff3+K/hT/Kfnz35/SP2V/yv9U/Kn8U/Wn+k/Nn9o/dX/q/zT8afzT9Kf5T8uf1j9tf9r/dPzp/NP1p/tPz5/eP31/+v8M/Bn8M/Rn+M/In9E/Y3/G/0z8mfwz9Wf6z8yf2T9zf+b/LPxZ/LP0Z/nPyp/VP2t/1v9s/Nn8s/Vn+8/On90/e3/2/xz8Ofxz9Of4z8mf0z9nf87/XPy5/HP15/rPzZ/bP3d/7v88/Hn88/Tn+c/Ln9c/b3/e/3z8+fzz9ef7z8+f3z+ANAAADK7JWUWnmO/TS4u03V2RaHf3Fq5haK29xyofPmom9KnHFpYxGqbG1NIXTjJEPSn9+3xqDFA7nCh+7d/XiEcOvGqUx8dFiFKpIn2vu7YbEIeqJx+1Ng8bJUrDJ0hdl+dqjnn5tgiZhz8QfZw8NA+iYssd4UrKe6DhQHg0c8M1iFzoSwT4qSE5ozcJ9M385DOcHrEZ3Js1hISHsBT/AjVDt5/dI1tPiZHp4O4vMpH0d15ZoLSHweZUx3oeebj6+jX9MvUSpF36byHjUmu3Oi1BtiPpP1OS+tAt/6uTJtXZ2oxQTof/Qe3M54qrD4D9FrpPY8Ggc7eILaGwwjPobeUlhWnYllBdqPWIi4aTWhtqNtcQIcmrwOtW3+O1T2mqb8yuoChIBU1t56so3tIu5p8OJaiZey0r5LeYARQ86GRUKoEnxQAOPJROcowkUgtiqnqCmOAp2TcBUabyIu9J6EctfwNJ3HeQ5eEOqfpLkqhQ2h1dwuy4DnhslnHYWl91+QIPdJkXBbLxdg1IbmmoT6X1xO7fIQ6pYaLIzWGeGKUcvYXZh4SoKbR0cpN8UjtLrhIft1a9ge3LN9UeXYDuPdQluoNkMEAhGwA80MpQepmLL3oOEXVkR1nxn3WicFNXNHP9daRy8/gXqXXi2WqCMA1IJuRCkJuFILLpMx1nX8Ov/7SZRM91WGPTUiA/EK80eBG4B4i+JFPnxpI5D2KfnoJquDNYloE6cKRMoht1tnDJHg5m/bNJEkSXIeRoGOto7oOz4bAi9seTki8pIQj55jTPYUSR+iVahPjKn/S1WD3v1pMSIA7yG79bdxAuonPOi+CYVYC8IjPsl8v9q7oZfPfl7lVPA7BV83VuehTLtUDS90cY5dPkLRD/e+YCVNM7GoCmMih7U1v8UrXqxXk/kZbWQN6QEa7217xsPS8pNj0LaOKodvP60l47OtVV1DVIOIP50Ci6W8Il3T3kBWYkVwdkOYKgxsltw6ZWr+lY1J4Q+UAQUZF/NGblilA+50IEzcusg73oI1iZCU2i6+9lPs0HA7GR6jwz5fk9omFsKBFRZiNXSNDSSJqltUDobRnkqaaHeu6btSCGchlLSh2bHvWdW9AO4p4YDVKRAR9koboySuQ8/2Aaus06h//6Z4NL2hXaG2VHvZBvFK79jhQJzSM33hp5IJhodn7gsT8B3YqkTMyXjJrEjoorA3MBjkqTQao6HHaNBEVDHSILRGu2qlTq7cLKF5+THf8RkuoR95uo4SqRS/Skfr1T2rwtFtGhAaDjh6zFmHZMISQAu0yu5Z59RWeApJ6CpZFl4CWuHFhtD8bvssk1c84e02HIY1wCayGhm5T8XyovbXTC0J2TwCxPW2S0MUixBC/jYKf6GHRoJ14JKxbCmByRDsrj5UpaiN+/hw51oK7ldqZlYh257wZcrvlyaBWYZ+EKTX1d56CF6ExaK4Zedt46AxXK2VjJEk9ZtTwGmkQttxxGaOultpvHGGqr/kjLIqTFaLO82laCCENFy/1uE3jODeumVD2yb33qs8fwk977fwmT7Me7tmf1UpcrRYz37O2xbYZxaCaZkjbFC9sh4yFOt+tL8vGj9nMwj45FCI1+xBL5si2iZXfM2shv+444dqF2QdQ6TSd0UJRSeOf2kkebpnoeY1VwXSQw2CI5qK7yCxik/43Ho36eC8VKIoWPM5pBQcij3jZiV4LBPRZhHz/BNM8eHNK9ZOnYJVPkj4nojAGJCHpkwo+9iF+zZ1MbnwycLv/zZblDvDsABduCEmmRzhLiXsTDcdXOjf1eiXngIAASMIAEu1k1hQMHT4rS+orboTYquEyahsLaVzc4AxqY0LmH/hjWQGAxKJopKJzI1ImBUEsROkMjLtZ/f44QSElJhVuSiJNG3H5kSHSkcPuPi2okGEMzuYB8MwA46DXWH7zUw4EANjSgUTs5+2oHMyOI6VCCqHiEqJdWJw+N8KULzRKoD0J7aUJtQU0rtiuekeDfivdiimAiIuSgIsipnjZuSxdM+yUZuDAcITe81oiBr4uJmaRry+doZYsXOJTe05072m5YOtlH7L7UuktZYKPb4DFYys7+O9sWslabhSU5Ebj8Vgi47Vdweq2T3W39bv2KfcwFNdmPn/bbSqQahM5IVkhyqpXmNMYBdSrFuymAShQ97Xv1AR5B1N4ZJ9/CIg/094Agi3kQjL2p19aRCwM3kgdxvArrUdbccMuAPSofCPj1Jc2MB45TiG7Q4pdAP4sTJK3CUbGUiWbtg7ay8Evguu5//0V5Ipyv/nOo0SzUfNT+FfHaiBwfGdapLUpVE93mLe205OjUhmi2a6UR1fPclcEu
*/