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
QvLdbkC/i84Pw/I6FwtjqN8gEX0j9IRAJILf4BbIyxPk/lkriIATkY2fuk1h40rsqi3btDhvTuZrb0v01paXlbCfqGEtD2mv2PRUdymCmHZUaYM/Y1WCG/AycPww3ioU9MPTP0FkL/BGGn9aq2IbG115bw5yyDYEAr2BcGCUUTSC4JnQTsytCfZX2qoDOmZl2mxNWUs7bky5RXOTuIZrvGrRNuGO0oVsS2OC51jc+m55GvWBw9/xbqT5c5huSehzbdXnsH5YMm7fkSazYQqj7LMFFEf1hqioEdYPiesVxfn1l9FYMNa0MEYHpiqVvQMqGxt3Of2QiZQu6de6PfIUFQpMSele/jm6aYkNlLfh0KD0ZWsG9tx1MMFEXqvE4Lz2+yXcCdOQK5K8VvuHfERxt1wPYyxO4n4z3gw/zYvOIo8eWgE56pBLQVJhRkkbyTFLfRIzPlphwcRPo5fRJTNwwbPG4mIHyUYVM8bSImhg6bLkK5TkBjV5nysmF4kXrBB30UxKjA+5kO89JGRjPPuywLLBGPFq9Q2OhtIHHZ+UPsAWGhyHN4wlUXnWRg8ssjGg5Ds/yEcgaqxV94oDDrxsYgT63OrINZTcCPnG1TkWGjaOwLE+HxYjepAAltm7Ze1Me5QNQLN2C82zawwZGuWUS0zYKGnTqkGRttP3KdL2elji1VfLwS65//MwJtUrYrktkRhmzRP1lyVGh94v
*/