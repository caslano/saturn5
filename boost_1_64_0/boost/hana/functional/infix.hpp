/*!
@file
Defines `boost::hana::infix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_INFIX_HPP
#define BOOST_HANA_FUNCTIONAL_INFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return an equivalent function that can also be applied in infix
    //! notation.
    //!
    //! Specifically, `infix(f)` is an object such that:
    //! @code
    //!     infix(f)(x1, ..., xn) == f(x1, ..., xn)
    //!     x ^infix(f)^ y == f(x, y)
    //! @endcode
    //!
    //! Hence, the returned function can still be applied using the usual
    //! function call syntax, but it also gains the ability to be applied in
    //! infix notation. The infix syntax allows a great deal of expressiveness,
    //! especially when used in combination with some higher order algorithms.
    //! Since `operator^` is left-associative, `x ^infix(f)^ y` is actually
    //! parsed as `(x ^infix(f))^ y`. However, for flexibility, the order in
    //! which both arguments are applied in infix notation does not matter.
    //! Hence, it is always the case that
    //! @code
    //!     (x ^ infix(f)) ^ y == x ^ (infix(f) ^ y)
    //! @endcode
    //!
    //! However, note that applying more than one argument in infix
    //! notation to the same side of the operator will result in a
    //! compile-time assertion:
    //! @code
    //!     (infix(f) ^ x) ^ y; // compile-time assertion
    //!     y ^ (x ^ infix(f)); // compile-time assertion
    //! @endcode
    //!
    //! Additionally, a function created with `infix` may be partially applied
    //! in infix notation. Specifically,
    //! @code
    //!     (x ^ infix(f))(y1, ..., yn) == f(x, y1, ..., yn)
    //!     (infix(f) ^ y)(x1, ..., xn) == f(x1, ..., xn, y)
    //! @endcode
    //!
    //! @internal
    //! ### Rationales
    //! 1. The `^` operator was chosen because it is left-associative and
    //!    has a low enough priority so that most expressions will render
    //!    the expected behavior.
    //! 2. The operator can't be customimzed because that would require more
    //!    sophistication in the implementation; I want to keep it as simple
    //!    as possible. There is also an advantage in having a uniform syntax
    //!    for infix application.
    //! @endinternal
    //!
    //! @param f
    //! The function which gains the ability to be applied in infix notation.
    //! The function must be at least binary; a compile-time error will be
    //! triggered otherwise.
    //!
    //! ### Example
    //! @include example/functional/infix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto infix = [](auto f) {
        return unspecified;
    };
#else
    namespace infix_detail {
        // This needs to be in the same namespace as `operator^` so it can be
        // found by ADL.
        template <bool left, bool right, typename F>
        struct infix_t {
            F f;

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) const&
            { return f(static_cast<X&&>(x)...); }

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) &
            { return f(static_cast<X&&>(x)...); }

            template <typename ...X>
            constexpr decltype(auto) operator()(X&& ...x) &&
            { return std::move(f)(static_cast<X&&>(x)...); }
        };

        template <bool left, bool right>
        struct make_infix {
            template <typename F>
            constexpr infix_t<left, right, typename detail::decay<F>::type>
            operator()(F&& f) const { return {static_cast<F&&>(f)}; }
        };

        template <bool left, bool right>
        struct Infix;
        struct Object;

        template <typename T>
        struct dispatch { using type = Object; };

        template <bool left, bool right, typename F>
        struct dispatch<infix_t<left, right, F>> {
            using type = Infix<left, right>;
        };

        template <typename, typename>
        struct bind_infix;

        // infix(f) ^ y
        template <>
        struct bind_infix<Infix<false, false>, Object> {
            template <typename F, typename Y>
            static constexpr decltype(auto) apply(F&& f, Y&& y) {
                return make_infix<false, true>{}(
                    hana::reverse_partial(
                        static_cast<F&&>(f), static_cast<Y&&>(y)
                    )
                );
            }
        };

        // (x^infix(f)) ^ y
        template <>
        struct bind_infix<Infix<true, false>, Object> {
            template <typename F, typename Y>
            static constexpr decltype(auto) apply(F&& f, Y&& y) {
                return static_cast<F&&>(f)(static_cast<Y&&>(y));
            }
        };

        // x ^ infix(f)
        template <>
        struct bind_infix<Object, Infix<false, false>> {
            template <typename X, typename F>
            static constexpr decltype(auto) apply(X&& x, F&& f) {
                return make_infix<true, false>{}(
                    hana::partial(static_cast<F&&>(f), static_cast<X&&>(x))
                );
            }
        };

        // x ^ (infix(f)^y)
        template <>
        struct bind_infix<Object, Infix<false, true>> {
            template <typename X, typename F>
            static constexpr decltype(auto) apply(X&& x, F&& f) {
                return static_cast<F&&>(f)(static_cast<X&&>(x));
            }
        };

        template <typename T>
        using strip = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        template <typename X, typename Y>
        constexpr decltype(auto) operator^(X&& x, Y&& y) {
            return bind_infix<
                typename dispatch<strip<X>>::type,
                typename dispatch<strip<Y>>::type
            >::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
        }
    } // end namespace infix_detail

    constexpr infix_detail::make_infix<false, false> infix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_INFIX_HPP

/* infix.hpp
f1Xvb36KL91VO9jjpsZvp7r/dh8tXz9pedXyFHjtnryr8qExqj7/X7R+ntJ631X9H8xeaN94t9P6cU3Lu95blFhWVPketnpeAW0vE2zFJ60vlTOp57xZ1E+1f7T6P8cezY/Wmt8t1fl6tDpfPaLl7Li6b1AT3f/56vr2eloPc4iiq/Fkv6DuXzl1vWgpPd5avzJ8oPul9e7Up/o5J9T/bU6p541rru3jN9puNNF8PaP5Gq71VvO7TRlVz/Dn7smhKLq2uwU1/2IL+qtxeEuPy1ltzwYo+o1gLV9vavmaosqF9lP0vbr/wc10e7/V/Zmk+j2AOb3Pz2i53Nte1Vv9DfX/rgvafmzScqfvrx2p7XoFUeX0+OT4Xd3Hb5uoM+/w+Np/V9td9kf67suvnnO1i7YL5HN97Wmi/ZK/ou9Nr/VD27WS2dU5S2Htt/r6qXoLqfLBzHN97fnOR+f9Ry33PbS9Zn7r49du7afraL2PVde3an7Omaeft0zb85yqfMGD6jzzNa3fwToOyOCvnptD3Z8jn+b3CVU+wwhNLy+q3Unq/qt51PVJSdp/n9LjtljzS/uvMeHqevXpip7YRvv3u7o9e/2Uvcqs/djme/KjzlkWqvsHWdq/l9ZxwieWGl/tv6+OtJRdrqXua9NTy11zzd+mmt/5tN7U035plfa7cXp8bmk7MU/z/Xfdj2fUeVdlfX2u1oMS2o9213wkhvONW3dd7zF1X7Nwdf1CE233cqnnd9+ryrdsoP3bDHVfh0rq/9i+qtyNRv7KbhTSdraLjjsuqftHaXmb84UoOe2jn5dLt/cLbXdf1Hycp/1kLVU+mP2+vvbo+G/qH4rep562Q2GqHbmL67hG64ml7cWn/bT90PK3a4amv67otYtoe/OLtivjdbx4W/OnnK3GI1iPa4D6H3eu5HSy5sN1VT6pla3K9VX9HFBF0ffO0ePeStuJrDqe2qHloqLma5SiJxXW8YWOd7/X4z+gu5Y/rV/VZ2q7GKLtcR5FP9XCX923/56f1PbtDe2/jqrz6ra6Hcu1v9fxRd1qqvygQB1/RGt9iNH80vJ/dZO2L1e13LXR/Gut7VAOVU/LNloOtb0NHKL1/Yoqt7WsHr8/VL3PjtX0gtoefKDtlo7zW2ZS5ze1H2mj7VfwNh3Pav+UpJ9fdpHm1yZ1PqDjs13nNF3zO1HTG7ztp8Y9s3rO9p+1Hajhr9r9nG6npeWN9Qsff7SexG7V8VKS5vOj2q/o+gYc1vOU3DruDtX2WsdrfTao+ouu13K1RsuDrifU1n5mux7vZaq+xEpa/+J1v/LredBwHc8M1fbuJT/1PB0/Ti2ux7uBng/5K3rgJX3/ID1fmKX1Yq0ej4vq+qClWn8+Ue3KnVmdt2o9bEYcr+rV4xqh+zFNnQO1vtQN0XJwSseX81X5omXU9ZlV1HlOZq0XOXV8s0PbER3PWjruKPu4lrua6pxFy3115nMq3tF8jNT+o7bWpyuixlm3I+lzbS+263ggWNu9EZZ6TnrN30Gab9qfddd6tf7vmm+aT1NX63EYpP4fnle34wfV309L+qvzIR33XdP2r6DWt9d0O+uqegYk6nnHS9pO6fhla7ien36r4z8d149poecnOv5t8DftH3Po+c8OfX8hf9/3X8oARIekOnvf1/lJ/zCucuSvwppVNO/nRLM3/kV/H+0LMJDLa9OT1+acj3eX+ru/neHm/d11yAiuVWNJOhd/Mw9pWoP1KPebhUV5xzon60fE9icXUmcv3tF2v+bkrjsMhp6BvffZKA/KlKVedy2SOrYFsWefc0hTyhbnGfXIxxNHlYjhNTXKvhpAXZS5xN/vc89a7o0uz/MLUhc=
*/