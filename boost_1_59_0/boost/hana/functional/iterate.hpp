/*!
@file
Defines `boost::hana::iterate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ITERATE_HPP
#define BOOST_HANA_FUNCTIONAL_ITERATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/partial.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Applies another function `n` times to its argument.
    //!
    //! Given a function `f` and an argument `x`, `iterate<n>(f, x)` returns
    //! the result of applying `f` `n` times to its argument. In other words,
    //! @code
    //!     iterate<n>(f, x) == f(f( ... f(x)))
    //!                         ^^^^^^^^^^ n times total
    //! @endcode
    //!
    //! If `n == 0`, `iterate<n>(f, x)` returns the `x` argument unchanged
    //! and `f` is never applied. It is important to note that the function
    //! passed to `iterate<n>` must be a unary function. Indeed, since `f`
    //! will be called with the result of the previous `f` application, it
    //! may only take a single argument.
    //!
    //! In addition to what's documented above, `iterate` can also be
    //! partially applied to the function argument out-of-the-box. In
    //! other words, `iterate<n>(f)` is a function object applying `f`
    //! `n` times to the argument it is called with, which means that
    //! @code
    //!     iterate<n>(f)(x) == iterate<n>(f, x)
    //! @endcode
    //!
    //! This is provided for convenience, and it turns out to be especially
    //! useful in conjunction with higher-order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a function \f$ f : T \to T \f$ and `x` and argument of data
    //! type `T`, the signature is
    //! \f$
    //!     \mathtt{iterate_n} : (T \to T) \times T \to T
    //! \f$
    //!
    //! @tparam n
    //! An unsigned integer representing the number of times that `f`
    //! should be applied to its argument.
    //!
    //! @param f
    //! A function to apply `n` times to its argument.
    //!
    //! @param x
    //! The initial value to call `f` with.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/iterate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto iterate = [](auto&& f) {
        return [perfect-capture](auto&& x) -> decltype(auto) {
            return f(f( ... f(forwarded(x))));
        };
    };
#else
    template <std::size_t n, typename = when<true>>
    struct iterate_t;

    template <>
    struct iterate_t<0> {
        template <typename F, typename X>
        constexpr X operator()(F&&, X&& x) const
        { return static_cast<X&&>(x); }
    };

    template <>
    struct iterate_t<1> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(static_cast<X&&>(x));
        }
    };

    template <>
    struct iterate_t<2> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(static_cast<X&&>(x)));
        }
    };

    template <>
    struct iterate_t<3> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(static_cast<X&&>(x))));
        }
    };

    template <>
    struct iterate_t<4> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(static_cast<X&&>(x)))));
        }
    };

    template <>
    struct iterate_t<5> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return f(f(f(f(f(static_cast<X&&>(x))))));
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 6) && (n < 12)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 6>{}(f,
                f(f(f(f(f(f(static_cast<X&&>(x)))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 12) && (n < 24)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 12>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 24) && (n < 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 24>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct iterate_t<n, when<(n >= 48)>> {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n - 48>{}(f,
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                f(f(f(f(f(f(f(f(f(f(f(f(
                    static_cast<X&&>(x)
                ))))))))))))
                ))))))))))))
                ))))))))))))
                ))))))))))))
            );
        }
    };

    template <std::size_t n>
    struct make_iterate_t {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const
        { return hana::partial(iterate_t<n>{}, static_cast<F&&>(f)); }

        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const {
            return iterate_t<n>{}(static_cast<F&&>(f),
                                  static_cast<X&&>(x));
        }
    };

    template <std::size_t n>
    BOOST_HANA_INLINE_VARIABLE constexpr make_iterate_t<n> iterate{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_ITERATE_HPP

/* iterate.hpp
hC7bFvTJoNsrQuIWSHcSfer/tT+mKb+a8XwIshK1lXrbe0hHciEuepO9f3/5QcAS/++hZM3xdlaRyGk4UdO+rk8vo8Yj7QxmcoHkkMzUU05WoMfHLzdCm9KZz4VeSHnTD3+xwdqTIVnPcOOBhlQju4zx/8K75Z9LWxS5/43FsEjnuI9+gqCKZt8W3eO0Hw4UaUNeXCuPzuug3PM4j5+CXNIL5Da/jyZZPSGvryfS4zn+uWZeu3HxN0bp0aiqXMGfb2tubZP29s5piOuD0P3bCvFvdJS/bhovJsI/dc2QgQEBNlbdIHKuJPb30at2K5J6dJ1PGp66Lvp6FWGW/ksshCAH/ImJPo+wElsM2fX4xyJEFJMNUwlDNsQLBxR+rInp8e89ronZFRwrEvLfhwQrDJpfONTYmRirrWUSf5+b4u+o9LH2ffvzCrem7/aVFPGvp1/RiZ1qmRp9dUxnn0UxcjB0sOQwvvT9HyD6coDS6BA6LG3MOpyTEOx/LODUy0n6uRPzlL00NklFtpPm9HupKB2u0X9JYChhiIZSSWU/nZLo4OSjOP2GgeXo/8IJcxkjHRMHwwYrBr4UIVDwdP1ajOojwcd/SKHegvud8h+XELpir5uELoqUbIV1bId1k3DT5Vx1E5reQWbr1WRfftsKHPKt4SWOFxx+dRoCwbjisdjhCCJKDu8Okr+6F5y4VBbyJkErk4F0XdeWJvNRNhcI7bLZWTnwN96/+1rOyvv+WywTetkTCTTYI4v7+ugQFWBycXavz9GGFfeUoXaRiWlRAbqR7OgwPi6Q7IqszyqEDQOEyYWZj9uN8Z34inqHKMQGY/YJgP/S3ySNG0dHD/W5pFvXrN7CdeLSoePTDhL39Vl5dmvEWqbb1hOg8Y7L5AQdexvhXPfFGF3h3BCsBOg0PPkLwP/Vt/iCC2x0iOile7eny0PfnPG9/KdFxy9pvwg5ifIgz9Hnw1rNA73pbUEvfEwmJ1//aBPCR5dIyJjkfqC5HzomBFzUXhn0HnNDVDeWBI/MU5/b9+X1wlgo5foD1T/Y5nbv6Hrj5mFp6Fiknu4CCVaSfkZMMtRYiZlm4DXTJeZQxyjBAMWgrMFWF9iJOwo8HFaxJSPORthisdsPyOu45TCzwYlrZH/5US6raXDqRsg8DJDqsiE0EVy1nXXa+D2H4q4jY8ALr0XLk3YT9wZ9WeyxRWUX5w8nvhdBQJ4buFWEZHaedJW0lvDuiKbkT4DOmKKOJtqvYrdFVhPwiRAcO6jSWSRDDmNiT2d10I1kFRabwXVe84IqHUO6Oq07VfCDJfhFIk3zzG5jBXdvXpQyYXxG77gHOLdREmtDe8c46Y6zc7BfHH8DZ4c2xcZRFcNmmCQfy5nG1YWW/uj2ZoUIcLHuFEzF4HwgonA7hGMZ6m2lC67YJv8H312GhiWDZXOFDw1GdQFFULkMMhMCdkFyZ3a99+Q1bBn8jvujwcpVPz+73GSOAyCus+1qP43eHgkh73uGPahxB/Yr5u67A4D7o/eaTc0MWXEtfPw+LRXDshs9Z42Bv5b+LiT1drbzSJCwkLYEoYUcvi3dJfR6II9UNgQXecKltxkaA5WN3es7dTKtrZeBnmpoi4JrMvlb+3rGmiVoxsD9httJIPdAWp1NjWsPA+9HJQ/rSaTCdYg9Hj9PmRDx8LOTF4H0ppKMAUvIrJ8scRmnmDziansSBwOBustlf03XnBWOkl7kvA+FD/Cgm2/E6bdLbsRZwJ4TiNSvXVZwm4leryzJp5mEb/VkuQk15zsL2IEy893fyim+IIZfAb8Cbvn75uJQhD++A7/MNytCfXKm0FmlEOLoYI29ikuuo4FsXrDmH/cp5PgfOnLX/Vne2Eufe8oFl6XvwSkjsPxfD98mU2/SqcdQdMgfTySfSIpf3XJ9gAfCmQOzajobgqVEfdToJt7Abqc+NfJ121r+DQhN5JOzUJ7muB46vdUHrYsm23iWzxvddvnPiIFNlO7hMJjPMSYMhs4l86v7kahuJBpERjoWFivHJfLpqD5IpVRwk3W+bHsNkDN/ha30vRPnMNhtUrPtK5Gtz6mkDGX6qSq0MUCmXFIWJu+yFXRrdj6c47OBgO1AudqjJfMwI3xGNE2+24uAA882KhJq2dFDyzZtPdOrufgyyiL772jSLrKp9TGEqP5gKWAlh2hLvXBlNeXcYe7jkxI3FSsk78PoWkj53IXh8sT7iTHmOYYjriOWGMHq8+8vGogbaK8s9II4TMlMsXfs+8pChkPEpHBfYMzgDGFWPCGs9OqtFqKANGPw/quw7kLwQvTtRSNQmAYYVBgO/3wz40k6hhyGbx+GKWYh7q+nQ5hmfdEhayEl/2y8NcQo77VBBTOQ4JS8T65PpE+xjyyEWIr2I4YCljVmufdzpI5WIz1k1uaaf8ZlsJsOkg8Jv5k9p8rlAaebB3FmUXfeTmYqLW42GmJcMAxwjcc+iqLpPf140lDb1FkP7y3QNndtgRaKto+tmp+cqQaRiP1Ypigou6RlQd9vzcMv6DXEW4SkgcQzdD3CcTXYfkyxeuNHBOtkcq0g+UW6E7r/OHwWOFlhz1VgP1shF1Tz+B4kMXHCFcItR778bEdELjgpt5EjDsXDhBB37FwL8e5TS9M8tmREzMmGOGBK4ohhPrCVAHG/BFOFNgqEXK63EERhlQtBPFWCewSE/xKXsv2a10OSKajHGcX/tVDw4cym/v25E4tlzQD0bweaZ2ecySguFeFMwxIdX9uXIol+rVHMGx1wAzRIUpGnlFcMsidngdXZMOTFeZJMpBDljcCLFAR38gI2RZM04kxpNG6yVt6WvauReXQrpjpN4iMs9Rw1FZ7P+rdSINVpOWfJMu1tzDxvNB8baNQLGnCOTos0B9QYfMognzjMXyLsjnRboT4bOW9/CSXZeS1GQo1t1O0ArPKPwD+0IZ+AjPi//OXMlIdiOOlnXYvKARzymTZ1eUPWPnMTZm9/NFWNf72hEZd9lGz+tIWc71dw+182Az0aQIFgvEf+9hsXySidrw0FKUCR1aD866P3YN/x1pXgVb/8XtTW52GPi0Ai2qBDQ7/e06XpRGrUJNP64ILP1kMKomIZsYOiarmyOO4WvB0erDsX+nsYO3hsBD8QLMaNh5/NtW2/DoL3pjXqZKh02p/K+kRARO/aquk2Ux5Wx7gKnlEROXbtqSrROnbAs/mT7kwozx8Pvpgg/YNAeyN3s4awc5BgN/wGe1uUwW9BaZDLEQWeK9AD/CVpLPmk2dsGjiqiuNx+UDk/BAG6r+8z0K6PsO3vLV82EeB6mpbHKDaiwN30o+izVLyysozUSLq4tjs+Z+BFdooK7DxP0o9/yRsUe5zrjRauMAzaX5ld95g5yxNU3v7VexdDkjq63YWomWybETtmc0H3ov23V+9GmCBdvgvCs+zjrRIPF+ByE+3NDtP9qVcEyN1pIhfyAh+qGdGLPiaX8YXgLsqZifwbw1Gd+knlzofaSBNxbiXxv7B8Fkl/BBdBIk3AQVP6oMHyVjDIgWB3SXLpL2gUifihZOwsdNlyF38MfAAd3iMvEwmAAZAe+VSrKPZ1BPKCoMAOiaBbF9jqQlBxia9e3cVXaSo2RoEhyOULglnodg+itJwu4G+CfIbglNBN6PHKduAE9eHNLVVqHW+wWz9N1XDK5anT95vW2QAvoD8QVTYOGaG05tt4rEhxRh4UcBne0hGgO6DlF+Dm2Bw6/3KwRxbXZRts7G9x7H2A06mdif/xwefZ2am4mbUG6CJD781DNEWroQ+TP2RcM7+3xQax63P+fTd5ib9CrKGmyg1dENTsOQBJFIa135Yjj8a26eD6e2fNKvrIQ39BT0kvsGy1C2q8cZYIcfILJAIkEb21KdLjJQFJBiI2EhaJ6N7k+i5ltVYLiMEn0cNbBqNKTghkyeTuM33CoKtw0fe8KZY8JP2bm5s9QsObre1KbopFtm5saob6Le1dn6/hKlA1W/jFrdi9VzBQ8rIHGNHcNW6dkjR7zJHyBXAPAvkvzPby12jfXS9Dn2PxyqaxbbbMwUMtgp8VrIpe33VTHFMLN0r+HSjmDX7j1SQ3GCs1OZUHn/X/6P3A4XZQEf8Z652xCMKqu1oZfsRBNbpRIya0ftc2iyxIRoFxTIK2epWOHy9yliAnyJmrAtEH9NUgPDBJ6F1oEDUsn7Ke4OpsV0KopkAQJTwzqN5d97iX794v74ieIYQ3bnWBBq26AUNgOvQqZ3qiE0ZncI1LxDE1WpduL5GAos+PaNseEQXxhYOv6Jb9jb1WJYecXJGLwXrAA5NlF0TGHRxthcwK1guGmyyjQ+8Sm2WxOwOuv8Seq4eOmPyEWAiXPBEH6tb9YmL9yL5325TMMlEwCTt1i5TD3osIMu51ksF2D2hE02SVPFE8n510e5L2RBZrGOsDVhqW1lUvo37v83w2U6c3NRx/baIlPSZRfUGSnE9CyUJvUA53UnCpUSmSj+q+i+UeheHo8wsaq1gtcnjCiAm+jBIVIpaQFO87sO1uhTxa690TxZ9Pe5+L/bywKwla1TkFthlgU4EqV4/MpgQisAiwLp7EI8WDYVIkZsHEoWtvkaLcIHJpFqoSy4LLb69obKNXVHRvLk3mXxWgvOLEOaFJLyd+O7w13rksGHVIXL/7CXO2YZct2QrehEjeJ334QwJvp2tO5EH5GOzn9EMEB91zMv1LA/RWVLgviMkpEcZ4wHSaMCRtzm4HpX6rRH5s8TFrSdsE7oRZx/v82OG/U8t/5OkkEjl/IGBnI9Qf+K5U6wUZh0C/eRRX5rjsPM45dAeSde0jeXCf1CKcUjEGC06BAgTfP7CSKITeGbO13kFeLBA6aRHWO1mc6WDXxxPjpTWWlwVnZNoGgxNW1/2dH2RVvxcMP96uyl6t4G3fTSzuciG13tQTqE+kBxWkD1e3afk7btKW3S0HJsyGPdQ0AitUUJ20xgb0KpJ0Fdl0RHm9q8DnXuU7iQ/1W1zmw6PQD8heKOAuYesoVt/vGnX6E3a1wsgoUFEsaVEUkV1csyUoMZysU3JUWUshjDakoNGNkQxjYMOkHQMDNa8pkCYAKwlgXb8jvLteBaWxkJkJibFxSajaX6kImPLmsDi7rRJfR7bdTUSJxWIPXa13490Ucif8tSoIXpPsvxhENSK3DYzuDAyv27j25J340RKf0XEyLhLulXR6NMjv4B+zVKgPEnuRxkQc6p2uZT+u/RjjKNoM4Tv1GHIU53+KLIlrrrRHpvNbTSOef4i1nKZ1kveJmaFFnOafo5gKgv0mTaCCiaBWs5wdwjBQ8CPgXs9FbJcI7XY+Oxq/pjzlknigGW4SpxcHDR5kgFfMP0huEm8UVhgr8L/hkrnNpuS94dGIO+bHV2eoV28otDsxLKv5CM4T/z4FpDkIhr3bI7+cb9RfSDABzB0/D2QdLCA4p9tbuI5phay2203hopuxUEqnFiJvH8DRaOPkdjd1NQgTQw9d9MWO0cI++ukpMIDpIT75QsTTcVvou6SjormfwHeTa9OVEWoQBLkT/61n8nXP9hmes2HD58GEvJ6ur0/bLpHbEYob51sEOBMtjqQk3uJ2cwPP9/Xnun9UWxuPfOnvxu4wO+LQH/pm21gcUWl+tYWOa0K/tCkIjjnUrAw0vjX5EaZRqdZY/PWdLz4FZ+WR1bRn+krpjwMtu3dGXANZvz/eQuagwwloQeoTyeGNjDQ4kNgbXWKB8qdBid+gjPPRZleBqHU0eL/e8dBc65O53Me9kZPZsNBZC8rgldf5T5VpblEWU7pynm9tqbsPrzJnxYJYSSbvX6P8XAJYVW2v1lNUJ/M+h3uoSnDQ3cywBDXmsh/cBvUcRr/bghQEG9OSMYShDAmJ3GcqDi12uS24uCcLZiwQIHfLH6NyBRk5Mk/rs2AFQZIO5X0mfCgKdyRdIg63ExVZcy40drYb6XtB99gG+Q5uto65k5QYSc60OIjWm7kdttnqHTBPIIa13QVvVfyNPfwQClwWFFmWhDg8Hpb470gGX05TsRM/bEC2LAyn4DTfxcOBfh+8harcD1gbS0fD3S7Fy+BRmRfZzmfejTrD+9HHBeG4YOtN2F/kCLqpdxxYs53PxHN7QqYXEwCyvCaV6JaJUPWiPJ3h6jBD3CSX+CSymFxsnrl8elIw4peS4SdXR7bV6T98ZZn4yXw0Ro/OPdAf4RuVnYoW0Jy/c8KVTXd81byV2xRvYwAoWpya501HPdgu//jBDTZJCzaUWJopK6sYUQry3VlyjOgOVVJlIVNyrVqf/Bsfg07lmdnbZstwTLrTBHVPe4ErrlPwVVg/C6ZOLAdHUTYbV7+C63WUVMc4bqULqCQPnOfSXHEVwBc4An7bDHCll1w/2hUuGkATcu5iD59gqnYFGkMph1EGX01dgtqxj2lxtyFXFuwPqDi6xP77ROTq8977RzH2ox4KwU0LKDiNw6bQvSNsWEl7fKVDuQTNmo/SEbtBKH1FQb7LICXFlrc9rtGqie2hA5Dwr/iR1cY9jxWAnzsOyaMnvWcF7hy0iTGor6NL1RVxsOFNW/6CVxdJlnzQuUazUdpV1YE+Exm7u7G+7aVPd2duO7+fcAP5N993qifaQi5T54zCf79dH6tghpEqLxRTeSfUJRDE8DuRKv+1HX6ZzckczxgzsfeB4C8wv8H97uwLVsfnJ8RL1cEAACz/0wPf67uNt8ii9aCuDV/fCtlcLTAguJync6J0h+mCr0c41h+da+zedkFwe5JiE3rZXiREB1DG/4QiteSDwTu60W1eouiturnv29icvCdronAJHpE/F6oUZ+K4bS7o4e9qvVJiiOq9RF/Pa/EToFMWUzl1PsML2toiiHY4CN1K3p+Uacvu6wXju9yBAeXQRbRPJsl2VGLho8w/tH/vAG/l+mJgkN8PkDBID0QWV9EXyBU/z4TKcKs7kVIHYoNwJZCVN3TBVCnPlhtigZeaVWEWkgTA1/9cfZTzBvbhvhf0sfyCEk4ouKriZLFevos2ffFeN5sQdUwTsL15NEvMUd9D9TgjsVrRT24bdwjllidIOP2+/8w4cH047mUg7MKbmz8GmojcXpqIjQYC0gXzl/9yzUFXXhOkQ+uJHwoSNWjrpxF3xuN2UkS2wcunwO3ejwkHPWgxDZ3x+tsKAJzPew6vVQGcKOO3r2GEcMeZvO9wyTGrmi74gE512DJOebR4Y4TUdjlt822U5G1YpUjKwVAHkQqTIxPdpr4z3x8Tc9fzwRC30ZgFokBqfoRkIvr2p69Ujf/968xa9m8CrAapNBO0ZWWP8X7KPdW9mljvU4feBY6/5Embeu8x7vMea1pOuNUWU/8HZ3n1KV527qHZjy/aP72sedcCALnIsfzmFn1Gjja5FhH9lvzPsxVUnSUUy0pnh3f1d9x+nxgy5vpP7F9wy1Hhxm/HkxpeTXRTmEwl3mR0J3fMbFjTfuTKWpkSPcK67YCNIEwjox/okxQ452MMi9tPmP1+qpvnZjKXx7SFjT9v6nR8BxozsaSuLlyapbSPb+Q0WKl1FZ2fcWxrsQF9yeucMT+OEdyhocmNMpHK+j2lo80MT4UrirUWdSoE1kUmax4w+qq4L7icmOn/8jK3WJURiC+b710x
*/