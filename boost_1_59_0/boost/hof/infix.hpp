/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    infix.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_INFIX_H
#define BOOST_HOF_GUARD_FUNCTION_INFIX_H

/// infix
/// =====
/// 
/// Description
/// -----------
/// 
/// The `infix` function adaptor allows the function to be used as an infix
/// operator. The operator must be placed inside the angle brackets(ie `<`
/// and `>`).
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr infix_adaptor<F> infix(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(x <infix(f)> y == f(x, y));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// * MoveConstructible
/// 
/// Operator precedence
/// -------------------
/// 
/// Infix operators have the precedence of relational operators. This means
/// operators such as `+` or `*` have higher precedence:
/// 
///     assert((x + y <infix(f)> z) == ((x + y) <infix(f)> z));
///     assert((x * y <infix(f)> z) == ((x * y) <infix(f)> z));
/// 
/// However, operators such as `|` or `==` have lower precedence::
/// 
///     assert((x | y <infix(f)> z) == (x | (y <infix(f)> z)));
///     assert((x == y <infix(f)> z) == (x == (y <infix(f)> z)));
/// 
/// Also, infix operators have left-to-right associativity:
/// 
///     assert(x <infix(f)> y <infix(g)> z == ((x <infix(f)> y) <infix(g)> z));
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct plus_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
///     
///     int main() {
///         constexpr infix_adaptor<plus_f> plus = {};
///         int r = 3 <plus> 2;
///         assert(r == 5);
///     }
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {
 
namespace detail{
template<class T, class F>
struct postfix_adaptor : F
{
    T x;

    template<class X, class XF>
    constexpr postfix_adaptor(X&& xp, XF&& fp)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, XF&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(T, X&&)) 
    : F(BOOST_HOF_FORWARD(XF)(fp)), x(BOOST_HOF_FORWARD(X)(xp))
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(postfix_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<T&&>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_RETURNS_C_CAST(T&&)(BOOST_HOF_CONST_THIS->x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class A>
    constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<T&&>, id_<A>)
    operator>(A&& a) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(a)))(BOOST_HOF_RETURNS_C_CAST(T&&)(BOOST_HOF_CONST_THIS->x), BOOST_HOF_FORWARD(A)(a))
    );
};

template<class T, class F>
constexpr postfix_adaptor<T, F> make_postfix_adaptor(T&& x, F f)
BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(postfix_adaptor<T, F>, T&&, F&&)
{
    return postfix_adaptor<T, F>(BOOST_HOF_FORWARD(T)(x), static_cast<F&&>(f));
}
}

template<class F>
struct infix_adaptor : detail::callable_base<F>
{
    typedef infix_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(infix_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts>
    constexpr const detail::callable_base<F>& infix_base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(infix_adaptor);

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class T, class F>
constexpr auto operator<(T&& x, const infix_adaptor<F>& i) BOOST_HOF_RETURNS
(detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(i.base_function(x))));

// TODO: Operators for static_

namespace detail {

template<class F>
struct static_function_wrapper;

// Operators for static_function_wrapper adaptor
template<class T, class F>
auto operator<(T&& x, const boost::hof::detail::static_function_wrapper<F>& f) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(f.base_function().infix_base_function()))
);

template<class F>
struct static_default_function;

// Operators for static_default_function adaptor
template<class T, class F>
auto operator<(T&& x, const boost::hof::detail::static_default_function<F>&) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(F().infix_base_function()))
);
}
// This overload is needed for gcc
template<class T, class F>
constexpr auto operator<(T&& x, const boost::hof::reveal_adaptor<F>& f) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), f.infix_base_function())
);

BOOST_HOF_DECLARE_STATIC_VAR(infix, detail::make<infix_adaptor>);

}} // namespace boost::hof

#endif

/* infix.hpp
w9NDIKALWUnVth/0eHwX+yrbAfzxDg5y1se2fy9Lxu9/8DawhPEjW4vgQ0tVcqDja7V85zJswWBsSVR8WRpNpRjwFANjOwyeXSo2yxVbgb2qeMC3wgkJIn5WdSiOLOS3zsJQzwSBY3U4A1VHK0gnrLsLWCIAAQ84CNZk7ISKneiXcg1mgsKzyzKoyT7/Hk+KQ/7uH0yLLcZQjsbdoa8gBzRDqZEHMRDzaaEc05oBObFCfpsBobyVj+xKowruPJ7sztob6uds+wHvZQvJ/tCnnEQRq3Aa9zpgHepHEz8oCgumJesQRscFimSddqEpb/FZ1L/lUeegSCMP3QY0GnkMj3vKkdULqtmx0/QWQwKUAGeyX23JTvqy+u0uOYBtzRRR+UQSAqF68PC7mEfCGVsBm9/SCnNo5FXtRtAc8zfVeVaj77+7PU7fZ/xXkID/sMUpyAigOKEfoOPLk+RPcCCcHMyzj9Qvkmb8IsnZdi+bwwafl6v+Hh18ogyhQ5p3TFp5Vt6ByJfAQFphPvJAoay+UIRj0i9bQQxo1orjdwbXYRi/Wm5Q3zh0TuKQT78TG7+LW9PU8+bBH0zh3XO98sEUUb1C0cJ4F6BgdzoW6l3yf/qRjhYQ1dBoHT3GRlW1hFc+olZC1weHp0d5cecg4jkwsDoeTaB0Axm3Dy+nyddvOYOfOTJzg4FGe7vJDjJLcqJLFItUykmlvFRqRpv53RF3E5MqVr1UskAqmS+7QDgu5Ml+ubGHniyZNbt+UF3VsVbH++V+zXh/+HZavH8x3og+QRfqSVi+713AqLPJpvMOwQCqq3ZhHqhzvDOrmAv1GfxBF37eAblFPdQ03kGA9Th6gJG/lhntpDcHyX7PKLT+yWgOBrwFnqQ201U9l7aZhJ4xZDS16vGUQHqbKYvtsLO755WRmXlO2cE+8FhQPSugH5UtDc8FqgraDNnCDqMv+KyvL11YwyVTq8r8P1pF9xNWWNeqreoK91vNqWW2/MjS2PkSbLtTYTFlhjTQWAW02WYYL3+C87I4D1T2qCApYIIED73KKgIz7dSFwktAZxaOVqFJYB5+ANofPolWKH60GCHePLKyGhjjvZORyKTSsysbSPF8qXgBKT0rFc/Hg3tYVPP5ppvHe65358cj/ho9wrVezxDfsyTmQC29QnYE0/CYchlUWzbYVzXZ213Hy1fedCYev4Et/AVbeH80tSNE02N5wZKYGRPaxNrlMKyFwo5CvS+4ydeXJqz5bZJOJ7y5dhcQOpIZeA1+mh4yLBP8viR0cGXEfq+A/7YZdOHF8AuZCwR/fSxzLs3UhyujmbfEMm+imYbwjSzzdsGfjZnTja/dO3m34B8LL3mFnOAfRcsZw8Pgd2cQ8Cc/vJWiw+PPH14S/H0c5nLhXg4r1uf/wuPNv88zKX+54O+mSYb8X3oFqLV5j5dvM/DhdkjNXyr4d3JRTLbQOlLC6IR05zbWQpLSAgKZwr/CnC0sh4u23UDhkqkX052vslw+mltLc5PCTsx9OR4Wa00N52POiwNrvZLCDQlfyiFd9EsA+0JDcxBBzOEUBHlmMIpDw98ZafEVgv8L+j/DYsF/xBjt4wEj1josvBt+dz7BKjBF2/wbzRXDrxgVKiLJDIxkw8NPGDFSjuBfT3MNWN0qCpAWfgCrWz8YnxHhOsxZy3KM0Yaep9Nkvv9k453knjzyT/nZHyIRW+/KKjKTA00zwA1ryhvv+flA3r1Sr86O9ZmvGjBG1b0xrwHPGNBq9hpYuYH/23SWC0+BK7CaamUKYDW336uZAgacAl/CkrPTztBOHoD2ghja8vf/DdrXYHvprL1Xccodv0eDNl5ylpdvV9AeeWG0cba6Px/FqkFd4pV7Ymg/Qw0Qr0O0u0YNGNYjeInOMCqMej/wxi+8qYyVjG2G0fB+r+bdisN+n3ckMM5dmvkyJvxrPRv8R/XRwW+m1V4UbtAzbmFgCzRgF4cx6Hi+V/BX06YNiwR/uT7KjIW0gvSwTa+y27gou10SxlGCpIGoXBo2Y8Z9gp9jdQJSp3XROr/DBdIwlsZ6gL7BDO/WRTE+SDMzwu+xTKgjqFMnyZuxOv5Mi10WRqvbnR+MGsTVPwtLmPN+PJ2997cZLu9ZunP3qPg5ntRmyOyZuzM4oB5IvqKnaOf2AaUntBmu7Llm52uj4gSc9+I2w7ieUYizF4XvUhwyIxuyq5smZ3t/7l4xKo5ZfoXMUqNhlpV3xzxJPEOtjg2w/uMKKH8GC0rcmvHYTc9bxSPw9MPz+AtWcS88l/3eKt4MT/glq7hY+cVn1B+s4j3w/BUeA7yPVdJL4Lkfnu0vxcric0jz/0ueY793wW8NtPUAPBvheeN5lq7j9Jz6z0D/Gt+Pj9++bcsI6FzTHuhKsRkP8lbytj5yHOPhCYF3h+LZdB7ojIH0ZNQc+rKENc8MpWpDzg6rGCgvkou/o/aj/hewbPmM7ql9vrDYdYlqvpkkrLsbcrqn8oePds/hw7VYzFnmPwiwQvOL+KYccvj6DMIjj9PsGd3T+rprQLGrPo5a7Qy0l+oq6PPJYnc1H754KDUTmNGLDUOuZ0J3QZ/cD1oJ1Ek65csRqHFGd2mf7ztR/hTSL2/FD0yw2JthiQ8fMQOnlvVCbU39Wd6LFJvgAl7dYHNv6HtSJxzpMTX1XyU80YqdPNCL26QZ7EgkPwY0NQb0mr4nZUKwJykfYILNR4TmXQb83rjtKurcfTu8bMOt7Vp9eK5ZS4JO8wAStJvjSFDVy0jAug+EOPwDEmEUliov8+8JNEIl7+FbKdO3aCVvYQKFko+i1rMf6DKkV0MXNkLdpTwzox0jv4XF9h46qqXU60N0urihfA4SAEZezwrLg7UoBHsQSiHVxn/DWONOREZtmH1qk+/dB0pkHZ6Nhadj8doi0AL7jzGAX5pVXpJ/RlsiffJM4DMo8iYUsfUJj66EIgFLnu/0L4TAEiy+O2u/bbcQOJ8K/+8Hjs0K0Y+KJWXGdlQwb/qBqsRm2IXgZ1az94vwoVSGpk9p9fYozYDShyNI5deUIvOVIl5tT+TVO+n5TJRcj6RqB7Zp4MDeFz+wDd9GFK8b2FX0MREWo8H2fp5K50wX7G5w1oxDPBqLYJ/yrx6GyRyGLGBqJ/vDxriWPQNbvpMVXmenTH86y/tzYHeKxKlvKGOzWYtIKBgwtiVpSTG2fRGEadNpnBFy6BvKk+okgrTQ+L0nD1+0p+lTuSl01Vo+fH8KtliGnxYvYYOZtRt2i75+g7DejAkHAquU8zFSI5pJg8gbW1aF6EnZp5zxvXWiVJOZv27MWiuZw0vVPJljlqrNa4fDLi9feoCXHOawJUXb52+HDOhz9xB1NGlHh32jYX7sqPxMJ+XA8Ps8G+OGrxlljwwZzK32D6Pc+jte2+wXA5v9YEjcIP/6mIa+XZCC1NUz6jZvMcaoWxJX7bsDq90S35uCRNVOVaqdp6n2u2StmHh2yAAxsWFIdKK9tV0RE5/3UEpB5/H6wF+T2Yz/DWQ/feqMlt0fT1aZcmqYkW4563zTg72C19xdyMsLttMZkg5lAlBteH4yo7WoADSwbjWt6L0K+w2sVY/8fcQzC/br3UUC30Wt++X07fTTQLp9GtqbToNdOKmF/LG8bICcAuCidWarsbWpf7zgr0MZVcDL8jus7XCPia5i3UXJvHxITfyXSUW+WWa41MZo8Zd3FFp0Ak9g/6CIrVMILKX9K8tqLcNDtBaceZJJO25rB47b/fHssPbrROMW3nA2EkGy9H/FUFkxJOFaOhW2cya2ln5zeM/h4ygZhpkYRXcooJ4Lgn6exECPqaCHkrSoLx2I+u3xLPfPcALUk8KH8BgtymALBjJYZYyo1W8rRPWFtevz1LcZY82OMdbkOMRKByJ2YzxNJ4ZjOkKZqiOc4rRV2AZWMX7IAIGYqwrEL+WfEIgPJqnz6tdcVBhukS8oDK1NIQGE4UKOjdFFX7Ix+k+qdqE5iviWKkVOfcGKnEqlQmhdaS/QiCocMAdHvZWmO3VAOwVF3IULwpMt599r+sza1CKsHR0+a6Tq0TVfxalHH29T1SNO1pK/BdKHxKlH243/a/Xo9a/+t+qRNwVUI6SlJ4lSFkhaZFRn5PefMyJMwJ7slyuh9vCVRlWQ1cKACkieQg2fnU+J8lkvnpDvxR7JYxAvyinyx1sVPSLpK/RDLaynS+Zeuf5zpk+cSMEvTMKGHQZqI2n2BxuSnz4VIS09w091wn/8B4XmFzCvPasFVrUNGzFaT10EVim0lzXjfRjKA8SOg4ofFWZkZgBt8D4LFMiWz/0HT52ONI4nfXgefSirFbqzrmZSr3H/2jFkTp80Bxa5szAkt0pzzN7/4MdNLDA7MwNlDVoGj1uLYemy8fOz3RyZATrM+rBgYHyz8z+MZAtSNIsXm/64hDE1T+8d05U0PxsGBpa0lTEF7D3Y63RdoWZ8sCua8bqe1X67UvuUFC3jnkfG3aAUuUkp4ki5wDaA4K04lD+nUfagz4bY/KxMGTA/p6XEyR7HFxoduGtBJp3iFqXlXZ+xlosv3HXoFvRe8KOVldz8z2j/OujnP9lA+c1zg8JAm/+uTpXDn2unyq8hPbdVVXhxqvyPTqfTTP3/crb4Po+fLRMGzRbxNf2EVrxVm2nlhLX6nuwJwbj3dDqL4pJSKrHqapzbsHWDvVwpvUyWLqy3fY+7U3q6zzNXDG73GHWbi9+03PYxdJv7Aagg8saa2NHKLh6PVi7+c9ogsDMIlqeAoVFpXU3sKGXXMDxK+fyVwWBjDRowPMgZVxPbVO9izsITgGVpwVLx/GeuBslUev6TAOxmg6ZveEz19lwNkvSY6uYEYKVasDQA883VIJmGSPIJwMoRzKqAGdH7jxZJIyLZ8afBYC5ta7AqySO1SA5BJH+TAKxOC8bh99DbNEhyiOSdCcDu1lISxK/8x9s0SAqIZHYCsAe1rcHiLC++TYNkEiL548uDwZq0rYHSL0/SImlGJHckAHsawcwKGKg3skGLpAmRXJMA7EVta8MBbO8cDZLDEUl7ArAt2r6Beio/MUeDZDIiOSYB2HZta0MBbN4cDZJDEcnP/jgYbHcUbEbmbPnqOTHTgSK7/HoCgA+07YjQzo/VGvRERO/BBGD/0fYKBKO8o1qDXgqiV5gArFcLhqdea6o1NKRHpOYEYGcQ7HN2rkzd6ts1SBbRef3hS4PB8KxMbW02TtAxGiSL6HH0pgRgAoJ1Kq3hTPvMFUMStQi7fFcCsJHGGCVn45T5s0uDJJ0yOQnALtMiibzvcWmQTEIk+/8wGCxHC4ZMPEWLpAmRbEkAdrMWSeRGkxZJyo0kAdh0LRiK8f1ODZJUjM9OADZHC4Zc8pRTg2QKInlJArC7tGAoj293apBMRSS/fHEw2MNakqCoG69FcggiuTkB2BotGEqRH6o0SJoRyRUJwP6mRRIn6PYqDZJDEcmpCcB2IFhQYS5c2fxVGiSHIZKpCcA+0yKJgrVci6SASB76/WCwHi0Yzu7RWiTp7H4mAdgPWjAUdUdna5Acjkj+IgGYkdOQBFe2P83WIJmGSF6bAGwEp2kNT4uXztYgOQKRPPVCmu7yl63ibfD8Dp55f7KKL8Bz0ytW8R54voCH/7NV3PZ3q3gj/D4Gz2vwTH3VKr4Iz2ZIPwa/F//FKi6FZw88V/zVKlbD8xk84zdbxfvgeQWeL+AZ/5pVbIQnBE/561ZxCTzb4fH8zSr+Cp4/vWEVk7dAOXhu38LqfxF+v9rCcMB3dl8Hv+pPO4oKWR41wPMsiCmieq+LvNc0abzXjv6t0L7nKCqK3h9J+Wz/Ho+blFTjDsTgD3pq3NkXAamOqURbuMz9wRjFQKywMs5AbO/zQGL6aSpW+l73E2rpkZWxj+28Q/4dlK5l0b5aB9lH/OWNwZ5DTrDApGQLjUvrIv1OUAOtcu2Qs5HcYOC+ie3JaNIlNWfiZyCpmJOKeanYHKgrkgo5qZCXCs3rSrOb0UclFjB4f+5+EXu24iKVHV5A3c990fVqyGL5zooYF1GHK7L8HGy2YjHS6T2DPOUGHyCj3OBjLUQv8RFTlQu9WJlJGeegQblOd0ci9E4hK8nJt6C1xgK8X9pFT3MX5560tUXrSbHL056mJhn03pMnczE8HnQZJx999EzEdl7tU8wTLFmfybFLx5a44HR45WagRQr7XuI7ll5JDpPCMmdgWZELzeJgC2hGk5IsRCD0lGIGx6GBTaOZFHL+IPRZbFxMitFwp5vr8++BTU1GvNkXsNP1qrmZ7cCyK6glSCPvcFIHdmhF87t/aaxoQMcX1buIVuUuovkw0KSQY3q/2PAYmZ4XNcUozKc126lfCuOXUPAhflagVO/r44T16N6TzDSHZAOhjpdCn3GnOgPcmsCM/l56zVzx71xI92NzROpNxDMSDcXamdVgCvzfF+xFW6rCjO6pYle6GMhn+74Hue7kHhHT6njVpXMpj7Uo1fH/1+r4rhqxN1pfUndpL1bId9X1RSuk9bAKx7D6rKSWJ61qjSZfa68ECTBU5KGMbn1XzeSjrDpTd9Hkoz3DaZKs1lc0WYZ6FAT7/osKp/YB+IFYjQd60lhaJ6syGdI6sSr0axXO8H1dUEYdh/n/eJ5u2ER/pGE5Nc2jBGf3z6bjbpRUmbvTT1PzRM9ovGXRQkdSNdWEhCozUok7jbOqK11v3K3SXQ9k4k53zYnSfSqPVUGxWbDx9Efw9vnKp6Nbw9gNTtsnnkuo/a3vWzT+dZL98sPP/Rix/eD9llqBo4mthRnxD7T3RjDRdsozEmuzVuJ9dIBE+9xT3uNz67QW1cw+riORfRwGuRLxU2TuETTJ9B6T5p19zLbS7JkmeXnbDzQAGDS1T375WVr52nlnJS/aAvd8TLzHyErEYBjK62jb3+ceqayU7c/gF9sTA252tWrxOX4hfKC9leY4fM4sL5S8ZgWdIaQYhZ08CjCapaLEK/jwCj7Ss/H4BH/L8EmATUze8MQhYvvdJlfXRerYGnpGdJu6blOGNql7Gt9j6DYRR1737Eye2ujhtJ+aT1eywIpI7kFfhGsoIEvKoH3GX11OOn+SHprdNYr9p6DLybP/Tepysun20ERfCxcoPedry7AdaHjf9tHKK8nUsoDnAP+YCjVymq+Nt33U8F3PkGk9vK/F0GP0tRihVFfmgQB3oLuAJ0uquzJIsZnckvdJP0gX4/d2GmXe+F53Cd915Sd7ukz0mCfV0Bepq2XcOICfRII3UCd1fa3Sr662hY+XzyCWnWQZmjRf7gLxppDcFAMB4WiXMx6nArqutr2Qo0bghcz0v9BMB2DA/YZE9tQfnEtsTx1+KBKJxK/P/Jb/F3vnNxYmsHf+1pvQ3rnx6QH2zuMSNJkOvEnvcwLz2gMzO4GB5Xuf+ZHam+6xdUgzz8bsnVuYvbOtX2jOhB2YrcMTNfVktsuHFVvnS9DWeYAxqHE/egkbRUMVdITV8qqtcyhR8WVpUW4tYXqXaussyvXr0nTMctmB5q6cs7LCLs2TpXlmGgnynTNaa+fOChc1kL4BDWmreFjQYIgqmLnzbrSVddjR0FeaaZYfORMzelZMpxPYPltB2lagO5dl56hprV3+/DHVFHqgHW24
*/