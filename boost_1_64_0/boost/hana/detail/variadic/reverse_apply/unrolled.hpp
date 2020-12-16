/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_unrolled`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/functional/reverse_partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct reverse_apply_unrolled_impl {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const {
            return static_cast<F&&>(f)();
        }

        template <typename F, typename X1>
        constexpr decltype(auto) operator()(F&& f, X1&& x1) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2) const {
            return static_cast<F&&>(f)(
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3) const {
            return static_cast<F&&>(f)(
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4) const {
            return static_cast<F&&>(f)(
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5) const {
            return static_cast<F&&>(f)(
                static_cast<X5&&>(x5),
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, Xn&& ...xn) const {
            return (*this)(hana::reverse_partial(
                  static_cast<F&&>(f)
                , static_cast<X6&&>(x6)
                , static_cast<X5&&>(x5)
                , static_cast<X4&&>(x4)
                , static_cast<X3&&>(x3)
                , static_cast<X2&&>(x2)
                , static_cast<X1&&>(x1)
            ), static_cast<Xn&&>(xn)...);
        }
    };

    constexpr reverse_apply_unrolled_impl reverse_apply_unrolled{};

}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

/* unrolled.hpp
1mE8VuqMu9TKl4GhDMQ4OC4XhTVFPLYZwSt4zG47LlVxY7jNCIWxnsWjwiu+cTRqvm1CdVjxqKzHV8xhs7xmJ8/w6uZ5LWJau3QgLTHCbVnx+K3QF/y9MypXBC1NOpYqRXmdy6yyVhmzR3b+8Wq+2Ssbh6eZ+S7f552xhs8y3nw04kFLJBj+OYOwxocwXrvSa33ZQesoSlbnRejdIR7LzuyKExezEGxaPk/B49MRjJyQCM79EWy5mcn622sL8oOt/7b+2/pv67+t/7b+2/pv67+t//6//i0+ATGXjtWE/13EI9oV9purdbHb6/A//M0nXrgVd+JD8JF9G+eJD2si9QO8N7IC533H6uL0RsRHuUoXR12pidohmtjjRNzg+U4Xiwt84uhDhHi/HWeOL0LrrcKbbXdBp71VEy9GdPF4P9RxmSbKZ+AtjYl4i6OfT4zM1cTU24Q4Mk8Xa5/1ifB2eAdvvE9chF3ytyPxHuZq3GvdE7bDa4XYMU0Xe9YJET5SiJ9G+MSpj+jiYDx2WHiNJto+wVnUgT5x14+aGHC+LjLf1MXkX3TxxunYswC+rLdPXP8YPIJn4fexsMHX6+KjiZp44yG823KSLr69XRMPAw+/vaGLVacgNtE/4TP8AmyRE/Eu5WkaznXxTtyHuhi9oy5K18F2fALuWAAv11zhExVTEGOhCGf8j8PfqB64vNknjirF47Nf6eLiv+uiGjh7/jafuONl2H8O94kdAPv6SZ/47nHc/L0UuFkL/F2FvUiqLro/h93DPCH2fV0TRd/5xIHrfGKXHzQx8RJNvNlPE/ftBx/TH2DT7A68AZeDcuDHtgxj+Qo4Az7Pf0wT5wxGP+/GG7MfAn+3YT4A36sVMa66w/67HO+43ivw5pcunn1EiM964Gx2F018vj/KXAq7ZCNe7vjYJ669Vxcvoe2l3+rihr01UbCzT9QO10QOrFUFwNu2Q+Grh3EPm4i++nXxKXD9HOYsfaYmvlqgi/m/6qLP8T7xzgjccdsGduZddfHzg7DlnoL7ZR/pYs27PrH/sagbc/IY6O6EmzXx/G94r+BpzB1w8W4j9qjA7W5TQRuP+sSO7+piCWjr5X/4RHwt3jq9Hn5KlyBm1zSfGA9cDXjGJzZgPGsfgf8+cPXWatgKXtDEFwWaKL7IJw7I18WUbeEjdCX6/irO2Yf5xPJcXez+PWxXj4K+9tbFhQPxnuNcnzg41ydO24Azw1108dajutgWOC84EHPRjP3oLLxysApjLwSN7AYbO2jnwRmYt8nwuQMOh1+hiXeKMMfFoOVbQAujNXEh6CB/byGega1ne78mzi/RROk9mjgZdD21WIiT1+jidzyqtvxgn3h4OfzJbvCJfV+CXegY+ImMw/xtCz+ReZr4+ynAMea6Yx1+Y257z9fEpTG8I/S+JlJuxFlmf8zdDbq44DKMa4NPTDgH95I6NHH52Zp4rEkXqT/oYtelPnHkMPhTnQ17O/r9r2G6eHQm7lNjbtuRd9b1uvjxc5+4LqYZa+yWu4WovF4TH9yEucd8LfgN/OEE3GF7Bni8ySf+fhjiPN8B+t0Pb8qs8YkrmnziwoPx9326yDoW9hXA952Fe8NY33knIk7SyVi/J+qiV8wn/jFVF72xLl+ahLLLAbvYJz5sxryNEOKINvCgPjgjXI8+gH7eQv9TikEjd2M+D8O6OcMn5lRi7S/FfIB3nT5ZFzr68te4Jpr38Yli9KH4K8QMBc+4ZQqsaEch9tmhiBoPmr5htg6HL/hWFWO8ZZoYg7Fd9yR8AyfqYthzmmjEWcvLgO36gS5+AZ72Al/Y+VJdTPxQE0seAE98RherByGe2l7gN7fg7HsE4kM=
*/