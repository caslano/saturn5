/*!
@file
Defines `boost::hana::on`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ON_HPP
#define BOOST_HANA_FUNCTIONAL_ON_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/functional/infix.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking another function on
    //! each argument.
    //!
    //! Specifically, `on(f, g)` is a function such that
    //! @code
    //!     on(f, g)(x...) == f(g(x)...)
    //! @endcode
    //!
    //! For convenience, `on` also supports infix application as provided
    //! by `infix`.
    //!
    //!
    //! @note
    //! `on` is associative, i.e. `on(f, on(g, h))` is equivalent to
    //! `on(on(f, g), h)`.
    //!
    //! @internal
    //! ### Proof of associativity
    //!
    //! @code
    //!     on(f, on(g, h))(xs...) == f(on(g, h)(xs)...)
    //!                            == f(g(h(xs))...)
    //!
    //!     on(on(f, g), h)(xs...) == on(f, g)(h(xs)...)
    //!                            == f(g(h(xs))...)
    //! @endcode
    //! @endinternal
    //!
    //!
    //! ### Example
    //! @include example/functional/on.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto on = infix([](auto&& f, auto&& g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(g(forwarded(x))...);
        };
    });
#else
    template <typename F, typename G>
    struct on_t {
        F f; G g;
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return std::move(f)(g(static_cast<X&&>(x))...);
        }
    };

    constexpr auto on = infix(detail::create<on_t>{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ON_HPP

/* on.hpp
Vf0EDjyWkAvBhnw0E79iKit3U6k8HVWt6CwJOXS6ysbNVqcDW6rMZ7+a7H6B/dFTrOyfsd+KqNMz52vR/A4WvxMl1NVotuT0FhLj/nOD+ktrZ/uKwWSyA/OJ5EMrCfSwurH4jRLWt57AkttikGoqgW5m2Ws9V1LZOlg1qaCysrTh1VPVjp4Tq5FPtLH3hQhb45FSM9nddhxz3dn2nV4LLPmlaj16S77ZHUSX0dFaXNY7Sr4fQlRihIZ0V1meB0ot/yK6N8bs34sS3DhDkr5tK6YR6Wrt2QIJ9Ku4Gm8xV3SrOHh6W6ra4PdCDPBVdtk6sbo/TMR5svu7UsQbygm8ilT2wy0Rt3FTNgXssz7iMrWfBvZyKvtjnbDXfklma7Z4k3NKjSgmSa90k+B/GCfiJ/m43wB5l3Efcaf4pAnMH6omq7BJfhXiPH0lgW6ukixLwS4co7pmVYRd1kdt7I0TGMv19P4y89FZ/e0WrIb6Ldes7odkPoiPPiorXI37I0GgarqYVvyDymIbqQsvoDsDqMOpsoMmD5UWq4KHVTYuTTUCu6jdq/0kxqXVImkcIPDHNQK1stTQ7LvqeYNIpWLrSsgukySQx02N+Ouq4uJ3T2Xv2RAbEO3LCIEbgeJXyEVDd6eeUtseS4zQJwKpN9WkZ2shNjXQvH1vqrolKTM85fzLUN1SBSXGcojrApoBAmFQDxBRUU0++6IRf1RAdPmPSJbnIE4nC5RdpNaauCp1MF7jMuSaZG76Rv29flcNFTyjEa9hL6z7T+43aqy5KjF8eyl1igWSSlnV86r7u7F6tJCBWL1EdTd/EausU2KQp5vaqMwaj+stMC9L2H69VaNNbonWvJewYWuYj/lCLKjBfZkouowJIpm4VeJ2aaXsiEPidz9JNY5eFUlDFlfd9qo27ryR+psmmfdXsJZ8mzVWo96o7vC+IvGvyvrjhviNpOsAcwAHGYP17BRzsh2acN57CHTbIOKOrGwfRIvgNh0F8XAUjN1rBC58k6Tthqrxnt7Czumv1hIuC9EKVkcZzhl0oa6pk8bvnBCHqbYYbOmy7LdzasitvDpz2VV0ucLEb5qnsHs2CRHdRilDK/Vj0Wzuj9sag5NTxaogB+i8MyKZSbU2B9R490MiruKv7reFqf8IyRy+VdkMF4192jkJGXLHTvPxQVivvqrR9akQ1+9wnrZUGxYDVOPpA4PamKA2mq9Wa88sTCVfcZHsfiREVXZZ7zil0mLEr1qyUpsbCbsXkrGOYloUWVpfV0OuuVTm1EusNoaLLl+UwMrLjuhDjN8k0XnaSuaKnHDW3Zhfarzjxo5syXnAXVZ0KfxsmF8/ybI1XmUPN3A+76e/TVT2q5NqHEf7qpop4oxcyjr3FzZ3Z9Ety6HRrVNfA9v0LPv3ihi8aSm6bmzdjhlqfMp17jd2vMkTG60/TuoyN420P3aJbhNNxtYTgwHd1FqfRCEmdVFqrJOanIGevc9RoNl+ERfLbSN+9GhQd7H/OEh101l1LbjPq5YV5wywtRFjTg1VO2iNfjVbqbkc5ofms9/mmEm+l2pjpqOk/8kk1xwhBufPqvFTIPI/she/G8o6lJXgEz2VCmmiuu1viMsQJzXetbuyM76rbuto1oujQLFb4rexEvxqiF+VWiJJX6tUrS+s53rMR03VnVhOJNFeSm3OFOK1B/cv+nPDzmo8rpoQwRtUzf0I+lBBjfOaGM35KCT94wCR3D0sMUx9xa8d2Z5zRTKnF+fzC87nueL3cpDKil4U+4KcKhYo+YeTxMWH82/8cJX5PrcXP1dVWztLWU+O+mtHVGMd8zGnriR4V0LY+5gUSUPEz3G+yt78EPEXPw3i1jY=
*/