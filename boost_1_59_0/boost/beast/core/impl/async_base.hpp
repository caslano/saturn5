//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_IMPL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {

namespace detail {

template<class State, class Allocator>
struct allocate_stable_state final
    : stable_base
    , boost::empty_value<Allocator>
{
    State value;

    template<class... Args>
    explicit
    allocate_stable_state(
        Allocator const& alloc,
        Args&&... args)
        : boost::empty_value<Allocator>(
            boost::empty_init_t{}, alloc)
        , value{std::forward<Args>(args)...}
    {
    }

    void destroy() override
    {
        using A = typename allocator_traits<
            Allocator>::template rebind_alloc<
                allocate_stable_state>;

        A a(this->get());
        auto* p = this;
        p->~allocate_stable_state();
        a.deallocate(p, 1);
    }
};

} // detail

template<
    class Handler,
    class Executor1,
    class Allocator,
    class Function>
boost::asio::asio_handler_invoke_is_deprecated
asio_handler_invoke(
    Function&& f,
    async_base<Handler, Executor1, Allocator>* p)
{
    using boost::asio::asio_handler_invoke;
    return asio_handler_invoke(f,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
boost::asio::asio_handler_allocate_is_deprecated
asio_handler_allocate(
    std::size_t size,
    async_base<Handler, Executor1, Allocator>* p)
{
    using boost::asio::asio_handler_allocate;
    return asio_handler_allocate(size,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
boost::asio::asio_handler_deallocate_is_deprecated
asio_handler_deallocate(
    void* mem, std::size_t size,
    async_base<Handler, Executor1, Allocator>* p)
{
    using boost::asio::asio_handler_deallocate;
    return asio_handler_deallocate(mem, size,
        p->get_legacy_handler_pointer());
}

template<
    class Handler,
    class Executor1,
    class Allocator>
bool
asio_handler_is_continuation(
    async_base<Handler, Executor1, Allocator>* p)
{
    using boost::asio::asio_handler_is_continuation;
    return asio_handler_is_continuation(
        p->get_legacy_handler_pointer());
}

template<
    class State,
    class Handler,
    class Executor1,
    class Allocator,
    class... Args>
State&
allocate_stable(
    stable_async_base<
        Handler, Executor1, Allocator>& base,
    Args&&... args)
{
    using allocator_type = typename stable_async_base<
        Handler, Executor1, Allocator>::allocator_type;
    using state = detail::allocate_stable_state<
        State, allocator_type>;
    using A = typename detail::allocator_traits<
        allocator_type>::template rebind_alloc<state>;

    struct deleter
    {
        allocator_type alloc;
        state* ptr;

        ~deleter()
        {
            if(ptr)
            {
                A a(alloc);
                a.deallocate(ptr, 1);
            }
        }
    };

    A a(base.get_allocator());
    deleter d{base.get_allocator(), a.allocate(1)};
    ::new(static_cast<void*>(d.ptr))
        state(d.alloc, std::forward<Args>(args)...);
    d.ptr->next_ = base.list_;
    base.list_ = d.ptr;
    return boost::exchange(d.ptr, nullptr)->value;
}

} // beast
} // boost

#endif

/* async_base.hpp
LN3rCdtsCObWSze0G/fddqTpfHjdvIMQm6dvZSQQW8wbLu0Czc3xDt5JPgoS3/t7UMxjV9F7qy2JWx81DVyjket44na17lu0h6l+whkLPP3Vhls+DLx2kNp1dp0oA0biiVuRSby2yMvm9A8zrTFtQ1O9eTXzlbI9rrBleU5LKHkD28dLX3vlIwJFOMG+dO1uZozzq4Y9lfT5uRzA4WED+nbDqotMnxAJJdU3fOtK4Xy7YP4Z1VEd2o2rnlb+xFDa9N+KqhD8L6nUVLZqFr1+2XlDU/Sey73161wUSLPhHMNVpQsVFCyEDmHCPfhgyS4sEI04wpYs/UyvPTqzU6kfPj12VDlYnpsS98+YYclMNYhcCJEVcaLTy6DAYIMCBZ83Gay300jCYKyMf2BoOUFD0/L3AvVDkix6IlafFptVlwSjTCRBWeNUR5PkUIx1UVLeWrsA8QHw7RX/te1P4dfLHzjtcQ0vHaHWFfcXuNLTT1wg3p00FVeX7Cm9fcjbvKceYSW3jNxNtwFq9VapJEYtnDf5oxg9PgwFOzWuljX+KKL2kIANmca8D3CQxLa7eW+Ga1jjBF+k499wikQfnz0ty87FvrT1nTw1xh0ZkLsx/a2k+/gWTYBAt+0RwZuLdBs/+VeamzjdSgGKlFh7Z+ZVsJqdj8uMck9V9qLnJ4p67hwzXFTNP/W5AGagfzj5XsbeB4BpgO/+bD52TwB+KIewThE7CAeJfxYeI/1sSi7wYsUMcFv711M9lddNh7qMZV2zXfdDVKlt9eWBJnZO6Np5L2EZuGcUc/b1ZIDbBFDFcr6z3qJ8dAfej0DAoO2RT2fZIFeWUGDRBzlnDwKcVSmbK3HQpZ4lFguS6s/FYs7atEwMfBnFKhqW9M5x1Bjx7g28hY/AeYZ6aly0GV8XR8sRI8zZz6XZn6eZuENdf+5ZTMjdsS705IstWzfpnftCET+F+ZPrIovgxq2rwfZ7enxYIqUR5snmSY8+OtBKUWXkjkxRjJG5ik5Ee8qjoPjxnVz17M/WKnU0mghGydkrpqx+CEnu2/t2Nqx/d25rdqBDkhMXUI5nxE6GxtOattUpvjw6Pd/3bD1FluQFV2ZFG8PmvV83Bo/JpdowyIbJy7HIcVizKvkcoaCNDjEvBT9579AAfRsRdCkTip4Jg7Pmw3WAA5IwKOeUhiUjLVDT//6tvSX6RdECyRYDH/wVnKUZusLrJg6+o97BZQTLrbvRlpmHIBeGIuRS2K4nL6vVKkEKj9fBij9YXsGFdk+MAmHFYFFhtoSjAHwyNAU+ndLEmZhAujWdMfqmnSsh2tzBGE5ABAjBrG0LBRRnD3AMGrWeKBNrtFGzQ5DHv4LlRmksi+Vm0Ne7rFu+v79Hq+bklsIMt1NK/+0IT2YDpv4N7HzFbFZYKKpBhD+9BHTAsbJOnEHHQynxZTLVFWYE9jcOiZHZ62j1v8QFptSHJX7MR7DezEUHeZGanchnLsCrgpt+Zw0lglvxZzEmYnK1gQbeX9TJ7P0NhJIptmcYkHKkXHsILjaEHktSWN6xeA7FU2WAQvkhLB4mTBNrGx/jzlRlatO6CNHIDJrLIBA2/3jeJM/M17ZbqI/8RmBg9f6HcBQgIN+uY6v7wSOQGVQ8p7dp/I4oXzAndpqsCj4TT21xZvShLVhSwy9S6hp706wQ+yyCuczPJGV6Lq0/m/AnNu3fcorJAS9xxyab72Y7lxwZj8s7ql0svQVxwBpou7YnIVdCtnrUYm4RB4+Pht8gmERwRjqYPMBF2308VVCe2JWoE91YzdvZGk9r1P59PnDk/mau2daKWqNxQysWK4rn1LHo6EJfNa+47URwBPQmTpx/gzP+x6RBTfkZPfCKTxFHYzU3yQcTGclfbH18fYWKGpGH776lQhGCs3+Jdzc/MiunvuJhKjpueopQFsd06JxrDLSW8y6OUsR5y3pMAtE/VaDyBaV8eINMPrM7UjY96oOlJdODxxivZvcpyXDmcpCdeuMVy9VE/tIEvIoT903oJikWCkr+JaauodDYF//6+l2OfCIigIJgkq8hBHNySp4ajsZcfOsRFHdk+9Ekw42Qd3d2LGiFLWsAaraiTZypKy3YbA9nRLH+/WTSHGtM01aD+BL3+dDj34s/pApl+PBKYnPDCMIG9GEjJQusSgRfMnvlwNMBiEtnnNWgOG44kbYgslx6R3ip60NmZ7wwsMkgkA7SMjgf3jK6DM6AdWluRL9hHeENjBMag105aXigS+qEhOCeTeJZaGTh4gE4WHajLw2JAUgpQI1AS2ZzS5SdpIiPMPEijrVnJGkiHN/cdqIESZzBDZ6k0orE8zeUVPtgRtBpm8oRNGcqMdQsXh5avFlxSYWUwHDmX6TamFOLpiMIYXPL91h1m9i6TpxMctfMa4gmyoCGKtEzjpbUhhRl38yEbty7eL0T5k/UcmuUunnskWGt++ktPRzFs5jmJfezDVm37u6ZZFc5aq1m/7vCTis8tnwS3/UY324Q5eAfVDpAKJ/dSX++EHyV4es8xsQHd6sc6o6Bnwefw0f7Q4bAuHh7zPcG04l3HJqnXBrfsYMrSZn0vag95FBp4dVxkrKncawsD+DgCaZZzazfHSxJdI1lnPKMFwyAn8N8k6qMPMIkooVhACmWIT9K2LFAkRB2ClqH7qkDmCMfi7wEvP5+1vmUr2v2ulh7zqxPyUwmnFHN/V3SJQlzEx0cAt3IH33Kd6UxBasag0Ug0Q5s0Uv9bXCzBvUNq8L5EP2tZFqs1mnIP0A8ctZ72xXddBCmslBJ0w9QHdrUwYiEmSIp59X1M0ZF2/wVWX9zONmMKITWiLYNGJwdBq4mGul8EymQwkauykt0F1J83KoWMYJMRU2LbVa8OTcEiWz9hq55xfitRIAhP1nMtQ1FuVcC/H7wl0RLAI2lzmV2dmTq3l+e3bKpGAR/hs6rH+hwsZnKUaEt3CTh9g2obI1JtqoujwyswysounHljYkgN6PGYN290EPh8h+hgqv3GSO36TyBkWqwwzqSHRrwubwNQXQ9/l3y6xRnnh/5X7YueOIsfNhFf0HiY2TAN9nxHhI9VYShZtNgINUkCcxvY36wqAxN4vw+9H4WaHreKRO3cTkTcVgD/0HkHwpAAOQbZ0hbe/B3BPM0cVuqbgDw6tJdx721fn4D1gJzG7SFXO866nT8QCRRD5RpJKR09VmRiv5V4nQRWBnUCQ1aUIBibecdRGzd0ME4jyNHwR+mgdq/zlxMe7IHSLGuIzY/UnMncfng8XqNcV+EBaVpHGJJja4kqIIzn5MFxtu7nNViPiW9XNJwYTZX6UC6mLqaum/Dcbv0zsZWBRzWCvCzUiCcBY8gQJt5iRv8slUbTCz1LwXUQawGeoXiaNxnEQlKw1AxiJ6VgvxmniTSf3C6aqaAACwdoblh4D9BbxB1QEC5Syl5Z73jQERgyPspNRHulKkbd7eoaoqUw6mQHPXvvmbyqPXl4G8nfDhsbAzwDT7nS1Tp+6EIHuxJWyaQxO2PUkKsX48Gir66c8rJioktAmKuBk3NuH1RUiuDGFrWyJ/x1Djm5nMpafoQx//KKzmwE59yZnYWx7f7N9qydkLla440M4/qVvJBlrAuuCJkPxHNL/etFrZwXWXA//kjhhByVltKw8vO0vm11GAkMRVGF11sFN5H3j+iFDTe/24IJ0bj/gElxfpK4o7PectGQUyM+Y6s0NU/lxuZXdABML5p731P2LuYc62Jk6gMXR5MR/ih1SxlungIslRFWcCREOgbbuu+8IoCr7r13HKsynmvZc6HPnWpgH1hMJ1nPx6IfUbubCHMZ2BRzK8oQSw4LeRdHqHA1D5Lu6sgNkHwbNYGdTA/YmWFm/9Fp+5NORbAGbIdOMFP19UFBevUGIw2XFVsUzdlthzBNqd3rM6LsK8FCxsrxgJ6Ss6q57dKzwQUYHlvbwhPPsXfL3haw0xVZdVh79aC4qJ3hrF8tyDIC+Uwh7qvY98sFn99hBj6BoVgqzarde4gaPNROk5UlgF0GHDcFx/fTQxHoR3aht4f3x5aGL9SlXBy67t/o63mCzAAoUr4yCQXhEklLySUduCAI/84Tm7zUKOPRT7v0U/J5pAsNTPwrePut8tMlB/3m/fgGZNnTZubsfhgXDRd8NlzZLY19m0Q4NIOEq2Nxn8610LeOgwcvkUPIN+vRQRLs0eBP12OHmDhbQLuNUBK2EBjelAdwTbMSTmEso3u/gK+xGgnQx4J0KkWrgWWVIoP8hmkX+c57i7RFZ5DUrTqD+XEWdTQrZmnJ4ac8QIkF59p8MaOkSPzGL6jOyT1MYDRex1uqjhy1Rf/QdNoV+4nkJYmgSk2AQKECpZV02S7bssaCEqFxbsMn2QwyR3LohBMx8cwGhMXjm2fLACjCm1efKJ16GpOkfDigms2ln5hYVHRFvms/nQyNoBEdhi1i/gT8frVPzX1BUC1vrJDjeHnzykxbWVJyow3Qd6frUjzYj6kgy0hrreKEJN1MHL2fbT/is7CFA0XAaCSdhP/QDqJj5+jgUV22CABlegzioHffWDqHqvwHEL9brgGUYkinkehDBioGsZsf2ZFA6M7eXRdNamA72xA8nm750hwsIt8pe3poZ1nAG1kYXbTdof7W0YsZqmcyx2f18zC9FIH8/GcOUsgDR74qS1JExvD6PyNhwEGG1ekC4bB9ROakZ/FVYEpkOetHqMWIdxrBVf6mElfBAQCpBw0PcilrtUf5rHqS6chtCeOw0GDf4eVlJAa0GoyDievwjQ3wgWSFAnZfsiUHJKq4w4O+sqpW+VCxj/2ePTIJA+mWHVA8y+IATV5hZw4MSEOVHJCv3twLuvrZj7DXY+VbopA+8O72/eAzyZLOythV1UyOVBk9GN7AUlsNMM1naykSLuLhohKnPN37C8zeMrrIfsYvnA2oIi45uwzjiGeVyYEKi1YpyfOiVGfTkkBwVznnLaMcZBocKCLjZS85lD6cv82ua/nBPkAJhnB3r7PUwoE8RBk/JKAvlp2UISwObb3gvsEYysfOxcsIEwQ/nsCmaUsgq46mN5rkmeiPCrUFs6/EIumuksfchBb+uUC3X9kMAqP8howHFXNIno+/SljJXTnCV0afm/TG/uzg7BtVXPEjv63q+s35EbEc04jpa/iah37GNnvEs9w1t+rXO6AYJzFn07IdcG/JQXcoCBtCYlB0z3c5nXpXTNdnlTZnlQhVgP1g0LBNB7DCg7KDb4ogaHjWMI5v1rNPrC/T9Q3xfDOdXLynQrS5Qb9UhF4+VZmrlOLALxgZlTQ+jYXpXkwA4u87fyH72GgE1TmPQteu0voV1V5i0KQu0FXdTlet+p8l6GM4rvDdjmpVKJN9LT9DArntbcnj0jFlbyej9y70YQ+7msDagR0Mm+vhlJVjXytwY8s7YtCpRZqGdCioEop0SPOwXbNj5SXiadt2T4sfKufUUAuOqHcjoXt7p9oeuSDYO2CHaiLeodKW2Mz6uxVpT+Z82YK90mpRi8GNJvkuB3E9Q/QSQMAQJ7GL/HH0JnRRXo4iv4Kk6Ws4AgQgFbtFgWCjQwbMG9/IBCCNdH9hU0kJluXYs9l4AiuB0JcVT2Cqkl14A3tWirk17/VVy/q/IPXiaCzVanrICW8bjiv6cfzw6ogDk6noZob+LBDwjHT0sOrovIUvMPz87AV+5UWi/vCkfsDfcNQhjdbhrtwV7n5VzmGYxJHTWK3ORoYCJFTalyIWNTn1RZQyAhxOIcYUMNqJDqXbS+XDLUsdVdwOjwI14obBYz2XKujqDynF8s4Gjs2tSj9hLkCMtLZEphfJ5I8pwcWYpqwqOYgk/6Zv7sbJovemdiTXp7vKgVHJZJBqGAxE6+YwTCj2pps0sDRudhPPdhgwcK+uWQw/GXEXu0AJo7AnzHlSASg+sxX4J4kwWs2xUA3CUkftuBvcefS6uUWOkmEF7dWuhmOnuxJtYz9UyqaVPtkl1N6XvJ9Z9GSp9Z0h5DJOYOB8icgtdtr7AoodpDsNkAn/onXvv4VQiFkH31AebWsSxDDIG4MsLjqa9SliBxuEgf+FI6wq72nBydZVRDGH7OIXf4DabXcAHbYcH7Sp+9QXdW15uzYupl8bKsY3LPKAISKEEq97iiFJHaw/BurW26C3nOOcab8CMYqdB2qe/h8XWg7x5tLMY7bvqF/e8TqBBKNBLJXCW16rxn7g2jnrLooRC2Ek2BIzCoqQJuOiN7PRR7sz7GWkj0taBk+jhw0vEo5XaccCOL6AjttLJk344gxTcNMceYz4bsGNGdLTaNSgJaVnLFfEgYkKlRVmtMXNvurtnYxF14lR7WWzg1NhJXu0k+AtnfZ3E3+zevS4W44BV1c/f5p0VyijZVK0Q4sdYoy7FVylyZGqBd3QWMC8xa+Vd/qaOjJw4+189r7G8fmJxxBmqWtikp6PSHE9VL8n+s/2rtSOg12MXRZA8ux3VFVsDEE5SuUEMoz0mWzwZ5CAS9xTXo1XxvcJZEDROv8BsnBbBCqIqPolYieM5b1FBo8f9/BaRZ0fY8y3lyuvHfErFP2oamf08tjDIyTtRK9+iyOasPrE20h1LJeV9+HqhY4fTKk3YXtl8VaCqVsWd5rf+y8SRgIqzpx/1z5E5NtLQ6/KbZm3G5+qmrA7G+3/itDCpOboUHoTTFbYLWdCuy+veD2ZFq3kuyk4HT/JB/9tLv4683sqx16mSeihAxrCwLLl2/MgQiz7pFkED5mA1T8KazlZCeyQ1jRh/pzDQwhDeidev0JbUVbq8zoq1GE6qqqsBa6MXTWK//Hwkz8Ox4/OjRTuJ7d+68nK9fE0TOw+CNJ2XrBF0Wo3jTK47bBdhPTPudAzaxK07uUItLTgtupblr6q4Nwhg6o5A+rDJ70w3q5BYK8allQ9wtzMgs7MZwuArlb7/xCsxR7qSWh+CF8mtHpcx52P42YQ8FnUMXzFaMAQamaqqq1VJ3HvJmvwHC3ZmZmYAmCh/K5QiRLD6SHKie8aEfuLA5LFxqtZ427dd530w54rKbgPe3BqIBWDWqCtClQLkOvsPhaz0Q/Tb3N2v2K5dzld/asmGnDc6QGLQ9GhGhchwjiFC0rg50FLm4sYl8e4/VL2aBheBNsOIBHtPrp+dFVJ2hLrvOk61Ef1CKpxUqaYvp+DR56deQhTChyCkJMWZIckaOznhYNqbw1a5reXCJl3fFymNQA819eGCHi4dUPf0YJf76ItOrpGh5AKj+vrt4yjRvgQBwQS/vLDo8kS7fZsz2H9ACatazhMQE6xckowW/eRFELf+6Est1oFcK+2Q+hkAb3VeTeQC0uTCdDVtXqrPbE7+A7JUQGmWEvTydeccSqpOcVhXMK8fRC+dpL6HTXiFHAPndbUfjiugo5k70xAZimNZNOyARx+KRacba2is03SzGKaYVRevYS1wdt7REQmi6qnh7H28AK2nos2k+wrbW+14kj279XDA7pDOMP8vN0TVNo3FdSsF7ZgGmO+WffcwZNeW8TIezg0chsWX+C0d96eoM0CEj+vt8V6YX7Ibd7NXqr5pKP0ilesh1T5V92V+iFh4HaCoRgp9dTR9HboOZ5AQ/SOHE43l+TB0JHQtkVgz64i4x6DRzu
*/