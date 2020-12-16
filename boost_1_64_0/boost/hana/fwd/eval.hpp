/*!
@file
Forward declares `boost::hana::eval`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EVAL_HPP
#define BOOST_HANA_FWD_EVAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Evaluate a lazy value and return it.
    //! @relates hana::lazy
    //!
    //! Given a lazy expression `expr`, `eval` evaluates `expr` and returns
    //! the result as a normal value. However, for convenience, `eval` can
    //! also be used with nullary and unary function objects. Specifically,
    //! if `expr` is not a `hana::lazy`, it is called with no arguments at
    //! all and the result of that call (`expr()`) is returned. Otherwise,
    //! if `expr()` is ill-formed, then `expr(hana::id)` is returned instead.
    //! If that expression is ill-formed, then a compile-time error is
    //! triggered.
    //!
    //! The reason for allowing nullary callables in `eval` is because this
    //! allows using nullary lambdas as lazy branches to `eval_if`, which
    //! is convenient. The reason for allowing unary callables and calling
    //! them with `hana::id` is because this allows deferring the
    //! compile-time evaluation of selected expressions inside the callable.
    //! How this can be achieved is documented by `hana::eval_if`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/eval.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto eval = [](auto&& see_documentation) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct eval_impl : eval_impl<T, when<true>> { };

    struct eval_t {
        template <typename Expr>
        constexpr decltype(auto) operator()(Expr&& expr) const;
    };

    constexpr eval_t eval{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EVAL_HPP

/* eval.hpp
NmOcx0nVKSklpJS8WqBHeePPlDNXzRm+xorF8Gsb/fNEnhx44X0/Tr8vANiVww0OP2TBpBsFLCsDQjAfXNhWYaMgb8ylfE/olJbD7uIfo7l+rwbAUgDw5msC1A6v8kNWibZ4eOhgWV15exvnY5NtX9MB/zIDfjfyeZRfsBq4UwUX/4QV0Y9F3D+Fjzc+gkPe10ZwikCgsds0BDpXXk6Lbm5olc0QPBNdRrBCbDGoGJ0WW+FUVkY4aXOv8jhPvL473tPqGyjqexSFaAbs+ylfpDuL+/BoWhAhNTcb7FgjrRk26QlHc9mO2kZxg3ssNk6hY2bV8cYxnHG0G9TbASE8ICdyafBGn1S2WAwI4QuIPxYeBiayt2seJp9yH0ijfImVNkbTbKgBF1Yo6WAkJXsKcy4U9/gy2koYUSgFGYWeYRVPzvAMpxyvr30+6Sg/rxXvL8OexKXcsR91XGsVk33bVuByk5YittImH1GyIQ5qq+QKfEQrXqTeKmibzlJ19SqsehMIlYXLCQy8tWEzQuSQ/qmJOQFXhAuibM+fAG0rcVIkYFDKu6n+R88mVd/I6qbO5OqbzdqNJul1vXnTuHlPvJrQvNdbu5Y/Obn8/Bf05sXbpWnQnSrz/i/4xNH5xSMaOucJdH6npZMV2Cy0YQ2tttINtGkUb5kBtIr0Oh/DWoFB0te0i0JvauGJJh9BKg6ob9EojQk6wJeoK8kLezt7da2q1neuGDaH8shbOn2EiGC0NppLMJonmCnNip7jVQ4+CtECV60e8KjUUvnwMQ3cLP8FKhhzBRjEtPbqaU58RKOewJ5GoE7LoWQuhWY9UfZKWHsIlHrkYSWYYV665XskvsLm+7/IABDfvWsPgwCR8DP+JSpYD4mw6A4YgO0FKN5viEV7HaYxMHXuw8mL9tf2xBfto4+KRXvIO7RoF56ku/2nij83vc1AsfhX9MLvUFoq1+UTFX0fUeyAHAvTCGgdX/Z7HQtqIiLJcpFbPka985139N4J+sUZdtrUSss1Xn19VMYdjg//mckrXedLPPwYwppIzwtnsL9XoUmOWhZjAkdilRbKcSqjHv9oaP2Lp9QGBXK1zt2oBQUdIs3tQtERjI1g/j5q/M5LQImHd2koMYiwR0eL23f1vi2M91csqo2XM7m3dr2oCbtBiw297Le96oBuBVaxndZjTCh1WB2ASZ1hNI7GZ5kM93xgCH/HcZSqfCtOQWIaBZn/sIoX8jBanWDzHvXIFXxhDNtYB8bVbGBDXc9EX3uqt0/79AeS7SeMOJL83u9w8vvFzyS9xy6Y/cGZDiVrCwNFhwcSBbiVFdiuSvV4xLUDP29dHd2NMo+va69PJs5tCJ2Xh1bhbCd96pQAJLcyFuJWiAejfE0gtMoBW2IIm5oetIT7wwfOLKf0C+rtltsHosrb/xQnmrE5FnQyBpBeREiF9RT8JZNWvhXXN+Z4ZRcdu8C1c5YhOEiuIMLfHwIBPsr38FU3uc7pH8V1446wqFs+ign9VI1/NAfDyKYI7ll8xedtjDjqbgZSpnzalKv+WclKY7C/eq4bNuIGViwdt1bl3ejqg70vD1Q+uW+1sjRZ2N25DJI/9t51GW7V8rXFDugtZKB9U5duRO9jk4WeNgTPQDhkhehpONhGCIcDGojSRXjf0FbaewCSnad8kivk5zzWgErUF7RAy8amjfVhTDzqAJzghwfIM1gW2bPgyz8APc37knFKd7JZ/wQRn6PYFaEGBPBBoTU9grCJTzVKLVxNqZWdKpTa2krZvK9sDJc6BfZMAzS9N+8pL/cxzqMywist4ZVEAGdxn45F++hcPWwH3s5xStvjePvWEww5xcoZ0cFyhTPKIxA=
*/