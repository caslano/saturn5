#ifndef BOOST_NUMERIC_CHECKED_DEFAULT_HPP
#define BOOST_NUMERIC_CHECKED_DEFAULT_HPP

//  Copyright (c) 2017 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// contains operation implementation of arithmetic operators
// on built-in types.  The default implementation is to just
// invoke the operation with no checking.  These are overloaded
// for specific types such as integer, etc.

// implement the equivant of template partial specialization for functions

// what we need is
// a) a default implementation of add, subtract, etc which just
// implements the standard operations and returns the result
// b) specific implementations to be called from safe implementation
// such as safe<int> ... and someday maybe money<T, D> ...
//
// What we need is partial function specialization - but this doesn't
// exist in C++ (yet?).  But particial specialization of structures DOES
// exist.  So put our functions into a class which can then be
// partially specialized.  Finally. add a function interface to so that
// data types can be deduced from the function call.  We now have
// the equivalent of partial function template specialization.

// usage example: checked<int>::add(t, u) ...

#include <boost/logic/tribool.hpp>
#include "checked_result.hpp"

namespace boost {
namespace safe_numerics {

// main function object which contains functions which handle
// primitives which haven't been overriden.  For now, these
// implement the default operation.  But I see this as an indicator
// that there is more work to be done.  For example float * int should
// never be called because promotions on operands should occur before
// the operation is invoked. So rather than returning the default operation
// it should trap with a static_assert. This occurs at compile time while
// calculating result interval.  This needs more investigation.

template<
    typename R,
    R Min,
    R Max,
    typename T,
    class F = make_checked_result<R>,
    class Default = void
>
struct heterogeneous_checked_operation {
    constexpr static checked_result<R>
    cast(const T & t) /* noexcept */ {
        return static_cast<R>(t);
    }
};

template<
    typename R,
    class F = make_checked_result<R>,
    class Default = void
>
struct checked_operation{
    constexpr static checked_result<R>
    minus(const R & t) noexcept {
        return - t;
    }
    constexpr static checked_result<R>
    add(const R & t, const R & u) noexcept {
        return t + u;
    }
    constexpr static checked_result<R>
    subtract(const R & t, const R & u) noexcept {
        return t - u;
    }
    constexpr static checked_result<R>
    multiply(const R & t, const R & u) noexcept {
        return t * u;
    }
    constexpr static checked_result<R>
    divide(const R & t, const R & u) noexcept {
        return t / u;
    }
    constexpr static checked_result<R>
    modulus(const R & t, const R & u) noexcept {
        return t % u;
    }
    constexpr static boost::logic::tribool
    less_than(const R & t, const R & u) noexcept {
        return t < u;
    }
    constexpr static boost::logic::tribool
    greater_than(const R & t, const R & u) noexcept {
        return t > u;
    }
    constexpr static boost::logic::tribool
    equal(const R & t, const R & u) noexcept {
        return t < u;
    }
    constexpr static checked_result<R>
    left_shift(const R & t, const R & u) noexcept {
        return t << u;
    }
    constexpr static checked_result<R>
    right_shift(const R & t, const R & u) noexcept {
        return t >> u;
    }
    constexpr static checked_result<R>
    bitwise_or(const R & t, const R & u) noexcept {
        return t | u;
    }
    constexpr static checked_result<R>
    bitwise_xor(const R & t, const R & u) noexcept {
        return t ^ u;
    }
    constexpr static checked_result<R>
    bitwise_and(const R & t, const R & u) noexcept {
        return t & u;
    }
    constexpr static checked_result<R>
    bitwise_not(const R & t) noexcept {
        return ~t;
    }
};

namespace checked {

// implement function call interface so that types other than
// the result type R can be deduced from the function parameters.

template<typename R, typename T>
constexpr inline checked_result<R> cast(const T & t) /* noexcept */ {
    return heterogeneous_checked_operation<
        R,
        std::numeric_limits<R>::min(),
        std::numeric_limits<R>::max(),
        T
    >::cast(t);
}
template<typename R>
constexpr inline checked_result<R> minus(const R & t) noexcept {
    return checked_operation<R>::minus(t);
}
template<typename R>
constexpr inline checked_result<R> add(const R & t, const R & u) noexcept {
    return checked_operation<R>::add(t, u);
}
template<typename R>
constexpr inline checked_result<R> subtract(const R & t, const R & u) noexcept {
    return checked_operation<R>::subtract(t, u);
}
template<typename R>
constexpr inline checked_result<R> multiply(const R & t, const R & u) noexcept {
    return checked_operation<R>::multiply(t, u);
}
template<typename R>
constexpr inline checked_result<R> divide(const R & t, const R & u) noexcept {
    return checked_operation<R>::divide(t, u);
}
template<typename R>
constexpr inline checked_result<R> modulus(const R & t, const R & u) noexcept {
    return checked_operation<R>::modulus(t, u);
}
template<typename R>
constexpr inline checked_result<bool> less_than(const R & t, const R & u) noexcept {
    return checked_operation<R>::less_than(t, u);
}
template<typename R>
constexpr inline checked_result<bool> greater_than_equal(const R & t, const R & u) noexcept {
    return ! checked_operation<R>::less_than(t, u);
}
template<typename R>
constexpr inline checked_result<bool> greater_than(const R & t, const R & u) noexcept {
    return checked_operation<R>::greater_than(t, u);
}
template<typename R>
constexpr inline checked_result<bool> less_than_equal(const R & t, const R & u) noexcept {
    return ! checked_operation<R>::greater_than(t, u);
}
template<typename R>
constexpr inline checked_result<bool> equal(const R & t, const R & u) noexcept {
    return checked_operation<R>::equal(t, u);
}
template<typename R>
constexpr inline checked_result<R> left_shift(const R & t, const R & u) noexcept {
    return checked_operation<R>::left_shift(t, u);
}
template<typename R>
constexpr inline checked_result<R> right_shift(const R & t, const R & u) noexcept {
    return checked_operation<R>::right_shift(t, u);
}
template<typename R>
constexpr inline checked_result<R> bitwise_or(const R & t, const R & u) noexcept {
    return checked_operation<R>::bitwise_or(t, u);
}
template<typename R>
constexpr inline checked_result<R> bitwise_xor(const R & t, const R & u) noexcept {
    return checked_operation<R>::bitwise_xor(t, u);
}
template<typename R>
constexpr inline checked_result<R> bitwise_and(const R & t, const R & u) noexcept {
    return checked_operation<R>::bitwise_and(t, u);
}
template<typename R>
constexpr inline checked_result<R> bitwise_not(const R & t) noexcept {
    return checked_operation<R>::bitwise_not(t);
}

} // checked
} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_CHECKED_DEFAULT_HPP

/* checked_default.hpp
0796/tcaowMC23+kzoexJb/u6F/Mz58vch0uruPJPpF+8F29eZuaAuvjKOSJm+n/JuwPkqO8D/MXfepfQpAW/87XOyLzL7Jah2fnNjP/zte/sLpta/UVZExKuxppmFoUcPXIZAviDubIVsF5mQ1RStHOZJbx7sj5WP39ko8L5qGSMTh+ZaNc+yntgQEboOODOPP54Y7XFRnBJK3ay0XNzz2k0rb+EBqfLgud6hbggDK5utd6ttsuXzsOJInv12eAW3y7dxSmx0DOhWS14v5n6SntKbSb5Wd8oXxsw+IvHhaOPrJiifnGvsiM9XhJSvFZxyduPWIOEhhBpKA1818vMZOl304w2wZ9Bg8WviMxSCUFV815x51qECDrpTaFqBC4fjeD/RJvmFGtLG1Of1E/+zna1f8T1wl838A//32W3u/YbwRtjG+DXmr8cFIuXOmzzclJDQ0f/16ErdN+MvOTeuTRrh+xG7s8SR8nvnzKC/KeglxIAjMqB0fhGZT/tdozaJ6gW2kB3tATdTIg5G99SPQp8hPZAlPjrkU7iecJnSpCYf8XYowIf/BE9t4Qpv9B3JakM/l75o9O6iW9sxYL9K7xwuk1SOf+3Jtm7vqNcqHA8KHZWB8NlKNj9TrnIdtXx0jut7L3usGxX3EU6FCfyuVZSGAazwqKoiBthjmczvAEOxSQcNmrihQUgqf1sAJ7YBAIhJNjIM4qlPW6inTuD2+D0P2ZJw4EIZG1V+1lO/bcXEHS1vobB9J1NHI+ULjUqvZ69frOs43gDbp63Y6p3WVih7qtZpWWQKCqsuqT5OMqGiBaQ6zre7+VSIUyf6iJBc0sl8fkzYNQPFdV+G9MfHzUglogRDCYixs69+tmaywfEKiKX2cBW3tifn9OmwQ+RGCC1Jq//AL2Fhufe520jl1nQ8695EqAbnkBnT5VK3hi1wLf2NfzwyFaLNnXr3tQ2O/y5mwwG3W+vFMsz/S8NwfnNTX2S5nJjtQXmAh54ODXhHEzl26vqo6P9SQBhyNREJxmHsF3XaAOlPyf2Fum/gBK/rPV74q3hm64dkZqJwzsQbacRO8kVucXT4098cO5zAf9xq6/QI4Nu4x9lUh+HOkleC2rKBn5Xuj77eYWLi1Vr4PsjFu2Q6yqyOYuWGPigr5+bHuoZ4uiwO9tpMCzmE7AfJejSrH1rMO8dDvhm26CM8VWAm7JpFvEn5cJltgC6IIf8IgQTj6hpOGhkRFrqIGBmKQkqQEwYGH7AEnVzZEvjnY2/SpHr48NglR3eITgnuRwPvwXVlGuelSoX4wT5/h5nhIUDYfHL6iJHGFrPG3hjs3UlCQphVJzqMsMO6OWKzf/ui2zd4FBbMA5iQhZK3ghqoGtOD5amNSfIJ2uTM2upzRd/NQ+6A2+JIkNmEZOAAiaWNUVCXSON+tux1QAb9WyU1M7QrsB2B6eEf2nbHytNDvC6BDP8cMT6eD94Y4YT1x7FOfWmjFOgK8wLOpyvTNVIq6rLaFAGGFj7Bu3dLGLsCfzrkC5johJiSJWswdTWOSZIO9bIDgvbWAvVUh0gRAmTuIrQQVqJU49JR1+m3XVGlJeFK9eThTG2h/0U3sPiNW30aSCghf+lv6i+fU9F1WrNCnLLpforS1roB4Uyb5c8ZVNjez+Rc/mQs6PCw6ESgGuY5sYHO0XL8YUuXBNc/2t8z2Juuip2uTXvpupJU/rq/3Q7dz0M74INpZ4br1I5wg3Z+bnZG/GmFWCVOWogb5QEg6K/h/U3XVUFN8CB3C6Q8mlVUIUWFhaOqQblF5qCUGUEAF/pCK5K7ErXbJ0KiEpSCy7tHQLklI/GgSpN7x+57w/3r/vHP6YA2d3hjt37r1zZ+7ne7uf1ZnENYEw+UnkTWDPQzjBFr03c0M9/dRf3iEQt3K/+NaZZgrHyjBV817u6rDXxvd/FX/2NduNvyAjhRLD5d9zSA5qUhTyLD9BRUMIqLQ5QTqmI8S8AgBbJBcY/f4OF78hJF/JrbF+uZe40RjL17CaIP40JWhVE77BpqOvP56dOt8mFjf0M85T73dgvv+FzhI3411jgViSPOIyPO9HqkOf1Lb8+X02w4LZtqlnj8+74i2u/sgnS0GkplU4vtF+j2feQ+b5xhZyE0olAk64xp8BYRna56wEgICHead8/n9aXfB3j71Uc3wx4pJcszaXgLprMEzDrS8vdmV76Z1feBT4UivQaP81UZyfqu/X0Rmjjw00EL7hzgbtyodmFHkgZo4bdnmPZECZaLjAYz3mey/dRcfoYC+0WQkFb/XWHJTvEFYXrRbY9W1cSP5p4evi/3ilRg644B6E1aRk3d6HtKBOagLdfcUgSehcHaYwoODf//UyMdb4GC+eko/ES0wDG41rwp+5xpRUiCcyLuJpr/3pR+eqpFMjYUcila58lMHiKimSju9aCSVM41Bfe8hUvQ2LJXJxjxF4DTa+j6IQuaPNTSySIJ4ANk6LBT/NI3ZJpXluQRQw9fW3EXiSsqppk+LqofAutiGmrOKtO2oVNh256VmBVi47GmaxtIxCN3gWENZqjQh6YXyPC/PyQiHBzlmvAI9/BYYofYRUSqZKcbAG3MxhTZnGD+LDIEEdYlAydLjVWAltZq2DMpe3d1K24BO+0iNiO6dmxv46XtLBuydKkiF3IUXsnCptV0/ztncv3xbNvEYtIMDTeqdEYD0FxTTCfaH7Xv83HZh0g0nGlQK296x5GUZNTU2JwTkCdsl9ch8t4w9pBIhqTB6pu/aSic8DTVY82SqX6M8K1HwRV8TuPrrn9Q0VPxD4D/blfxAVWdcKtuNXhFIu/XH2en5BXkfa7vDPeppUNk16FkIoHt3wIwNrzkcp2tVhDTz9z9cRzL7a6Bemfb003Og41zVt7ntY3mE1bZdhPHXtiaFEBYVuCeiwoO+T6OYLe5yJEbgN7z5fKhsenkdXDs4E35yqiQgcKdzdhMdYRkX2GsKO6lqUO5dSrmy+eL7lgszpPNaHRLDgb/CVUd1QIUphFsMGUcHYvzUXTrUKVuabzN6L1hfEfksukmC9SwpRN3RdezN8u11Lz0zmbwEo1/0HoWT41KEWvKKCx4r76RtP9jYKXhcq6QWVSWbwbWC6s4OEpg2ER6gSXRax2KMULrbaDeI2CJu46Xxzy82OLksdYYQffmb0fZne4CTFmURmJ49Xwq8Vh3mxE+Wyml3zU646XQ07fDsBTCySKK3DlI9H4oQwcF7DAyrZnpBea8QHAucUsg+qYYmuaeK7oQpCMa/xz94UNlC+RGkSZvtQzXlKDID+kDxnzvanc+76AXCHClk9ZyEtKSSTzrXusmJ9BWqW3rB0LA4jdvA0EDuljMgXCFVmGV9jbciwjy6lQsaCjWqBqJ1UzbSPrlxrBK6SJS4ZxixtbGsEIq108/xgrx8hXhyjgzxOsUq12Mx3qwQPWU9yBDyxjgb0ppK3LlcyEpwJgSSC9xFM10kEkjt/SyIgFIS4AkkEOTq8HHZifO8+UDhWvOmDjKDUEbdRhQu/H8lICLja0T5Xx42eH/DSvNePZWdo//Amce8xjQJ5fnRhRGW4uqVb0MH6SOFprEdaJlJcYWnrB8KpCD8dmQY25kNFVPTtaVWsOzin19yoNVRfoZNUe3nj7YcDZsgSrihlFvPQSIe2T25qK1TKvWawzeWDNI1j72UgRAjxyu7tPq87tbrGOxYZcVKt6ohUMU2dpslPg4GCL06MC2LBBMB5JzXnux43rMgNO4AeONzjcak2ly82GCFj0vB8A0nzjqFmq0dLSC13uHu3AWEN9sZKvawpHsPWyFlkQdLcCYyJznX9M7VL2daJJA4OA2D7G/matCmmFNC8sr1uQQHA/hR/Sm+A06IvLVT/JBEfoUKe4R9A0nl0fMCCH50k6ynBX5KvteMsJpAJpAaoPwYidmRAIzvWp+vfTOS/l7kIPj3UTooVaBShfLi+RicB7XOPXz3BvBjXAmx9UsS4h1qfoe+pN6mrcrMtf3WJr/3vFCrkLXm7PHcOKGU20N4/ULH0t7i9M06XuGIxqpEASRXXSemXAdo17uGqAbMXXLmZAhoaGj+/4w5DlaeS/roHZ/003r5VpLileC5ai96gX2dD/84z54ikoG2CXxCRiEgQov9jnNOLDKK/RifBQ6ewW9WaQKMfJa7EO26IlOhbTa7J6HmxDAPInK3tbRsyBT76/PgCIBeDJbuvkigFpQmcCOrhMnvJzTyL94/7CgymqbQLs2pm97WnBVP0VfUKx23JFEhW4n2AMQzbXaCbpIysKUr4upz0ePB5IjCao/MrzbDlWvLxsiDaEtMD9nzpprkkW8KeKCl0DwAhXe256IAvSBLzDXel+DS7p4Wk7nPOBMriQijemVoMpwWAoQ+pbR/8UcCgQILV1tbGBM2uDuG8cfYWVdJQtIK8a3e5XoJasY/IZp5QPC8NKUQnpSVnig+ANMMlY+7bWWWg4oZMNWAw2IuGyHpQBsSCHoUUtC+4LVTCLyHiwGWmhGnZdacH83QmMbppdjD6thxdvGVdd2r78VDY2juqmSh1dPqt8EjfBcQpvB6j6JCtnLZ0LYcC0Dxj1v3uvj4ers0//wyPe105NR3n3ZgqliQF6XZKrrlx7OzPRiDEqgoY8f0XCltHT26E69CUBTOwmPl+b+JB8x/dOHtLdgkPYAWTvixeDZZ3vbca3LU3TM57dAz3mEuBuI6LpOsMY/58hOnvQkfkB8nFZctZ2NjQYC2trNomVXYhN0U0NGeatgY6rJjyayWdfgyZMZiZPukHBOcfdkq9Iy+JLVjAkQ1aO2782uHpQ/j4TB2mE17kFVxmJvcIInTIVi9Kud6VF/u8rVmeuwyzYtLKFlj/cwIWQUlI14yR8u7jdR3JpNnleOxzllApHxUJZmZk7rgmJwEfiBor0pbhx1XdlSIxLMpCXhRXeyYOR+CrsedKE9ANgBQ1zcRI8u+13C2vpExpm73FtTKiVVtyl1CwttFbsWN4JgTVOZyKseGkU0Qju4pe+EGVPQTQUgFKh+QE8q4JY4knwlwjCkYjlrUv34p7dVB6iYmidcZbHwIrrQIR2dc0PYmVwQBA05+Os1w3W68aKlLGfVqf7dDZKNn7LLsyscAZQNzE1cNUgiM+aigy3c+PxBscLOj55YUHTyw8hvFAFai8L3DZ0AtjFfhcpXMChK75tp7wZXeTgQHrs5dt63R5c9H+u8bvX+XV10sLCFAihNgBTtkXQq9F6CxZQMikRaiGAZmr5GAuvp1BNo697HlgcQXZadF3gyj7yR5iz1Pl9yP0aM1vBGQmzGk9DZC50fWBQjFL27Ydhy4V4FgfCZwqJAycIn27NLRPXmUk8zobsDgjfwkueATVKAMhESqqyfU5LgzXfPw2S5XXfuWrQwg4UqR6GOgYtz61m5MJvPcfjJYJ1CpXYHbR5RHKOnI/AZunSu+NihTc7o+7EN6ZcjeQg002/X7d41NIeNjwsikojUQkOMAr1yHgrPzVNWr6x4wsvkgL7nfrQ6LRuSa7IPfpPItsf0vHrU/GAq7ge75Pv5gSiKQxr0G4BSh7JaMvrwtpNe9EmHaCMW29kHpYifJ+QYtVtR7rrZw4OllR7ltYa/O4yOfvFCoGFDPQBLqTRmrNXKlVpJUOtg/N8tCTNAc+Bgqro5+wk2UoktZB5BBEqCAaEa6ZDZs8pM1u2oAh+kFWIrUO7h2TsZWES/SIzP80HPGpmBFhoEgRGhh7m2enZ4cnbrd1F7Pbvovdbdvt3O3YxZG1kmHI2smwZG1knWQdZDgR+4d2Dx0e2j+EYewwDhh7DIzHjseBBzhXeXZ5Dnn2eTBHO0cHR3tH2LLdssOy/TKMvZO/VTrCKMqLPZcsF7REhNVCmACEYyFkwO69w3v797B/AI7XbKM6o7qEOrW6EMA3yiD+QJAg1BF8CGcEE1V0Z9PV6Quzz0v1hLn0uZS5bDBQLnMHYihyKA4SComCvB2KgLyBxEAiILGQ117kS6JYxvWfMOujOGnsjtahCirr2cHY7Y2eU4KSZ3HkDmbqtbIcDCttac+bcZO+rJeu3nuBit1b5Rf1Ivy9eZUsh4ay4QY2yPknaT5tdu8v1oj8EjprlZi/81aFyKFD5KoqOThRmZnUcW0HM+6SJhzX/rnhS3ffTD5Vi5guI77AgOTv3c8iTK28FOmdxzVzn3OMaTkiYhglDO/AcqaMxd6w5HxW+H7HNbisWt+UqW5QKkdLg9YpXdxne7sMqyIunDdit2saJbWaZ3icIxWywvGR3+n8+0c6Zwpo5K8vCwt1kEZcmZ3vK7cRO/XkvNfADRYeUxtemEO6jD8HvYGC1NeXW0V62MO8/DqJToZ8b6ejIxekz4s2a9O2tTl1ttil+qp2TJq2FJZkDe1E8khSjmktArNYYI8w5Rh8HD2ivLHyCgVGquvQiMjMpETnhVdrKFaVxbfkJUZk9mwQ3HZ5Jy6Dwq9QXXTJQBtcbLDkGggWm7K+pTZAp7HyKCTPaflEBzSq0wJ+LdGOA4FdQQvE5OVFN+ruC2/vjc1N5tjr17fDAJGfwskolNQ6/7OkMgbUPMkvqr662pl19kOvevfD+ogWXoSp+Z6qofiC640QV01HXZ53IqqdowakEirfaIbvTLmwK7P61U5u9CitsINOhCut6kxlTN5/gxOK6R3xAE2FBzw7hh4/NygjkF7Oi8M8VdNMcIYy01cjjvXREG+xhyCBaBx2QmJES1zibna6Hxc9MGHyLg7/gdEtivx4pnWtwKmsNfTEm6KHd0Z6H7ZcpruLqFNmMBFviAOpZ+vAoM7Z4XFKkoxvlesdEZ0nrsOCcuaBr7sc1mc79B8V4CPgA2+VXQTj8eh9RxdkhxrcL6krlrJZwDtsuoAFloAmwXKTEjX+sFs14kdXaS/BAIiMEocrUEtTC+fT0jGBbHHQD6kVY8zlAmzSq/QypOBvehMKLR5plx7aB53wNIdHUgZlOkMeP7pvtY6TUk9mdFslzqjEjPN9jQqKjxw2TdjNdzb+4EIF/rnyNXoD5pkUnW0YM24qJKq+WfwE6Ph8MBdrbyhRXuFBpVwLoZ0l6zGcoDhjhilFpiHhEd5iP57KDfQc7kQrnQng9aNSJYBUMt1WKu2S8rx1JXExilh2kV7Huc+oZhvMM+o7udVdID2mtZe34VURLPfvCXVYWS8O+7O6oeuuCiZZix9GMOsx6kmzxXf4KKmyNl92yAaCraPaKTLa35o4FIE213M5Xo6mD0Fj17eJochfnDqxMJ9OGn0MP906ALgT2iUE5d7U5TvQ9BcWZzcyDt4YLZ6dtRYxtbTUBgYtXTh2r6yp/lqWdBZXOypGkwx/bDJze640zAGfd6eK/ylivZDQVwtuN0+pGua0DnQzucNlqTTxX1/Li7u/TZ0bMdRCTboy+1WFBzrExRZHUHz2FoYUzMTpT7uPdPiFOea0sJGJ6DPjA7M4jENSdPackNRIveYOe/mObpfSw7uEWR9R3/TuIxgnHd2d81wdvaLDvqmW2/MhIyzJW5/c105jcn3SdyistqEli9HVgj3/QKmwitN342/hKxbOrCdYWwxKOxZ3dufmcBCsKlGZhOjOCUjfEmO/CnfWnaYJ8ryTpEWgmwPH
*/