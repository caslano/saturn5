/*!
@file
Defines `boost::hana::partial`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_PARTIAL_HPP
#define BOOST_HANA_FUNCTIONAL_PARTIAL_HPP

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Partially apply a function to some arguments.
    //!
    //! Given a function `f` and some arguments, `partial` returns a new
    //! function corresponding to the partially applied function `f`. This
    //! allows providing some arguments to a function and letting the rest
    //! of the arguments be provided later. Specifically, `partial(f, x...)`
    //! is a function such that
    //! @code
    //!     partial(f, x...)(y...) == f(x..., y...)
    //! @endcode
    //!
    //! @note
    //! The arity of `f` must match the total number of arguments passed to
    //! it, i.e. `sizeof...(x) + sizeof...(y)`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/partial.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto partial = [](auto&& f, auto&& ...x) {
        return [perfect-capture](auto&& ...y) -> decltype(auto) {
            return forwarded(f)(forwarded(x)..., forwarded(y)...);
        };
    };
#else
    template <typename Indices, typename F, typename ...X>
    struct partial_t;

    struct make_partial_t {
        struct secret { };
        template <typename F, typename ...X>
        constexpr partial_t<
            std::make_index_sequence<sizeof...(X)>,
            typename detail::decay<F>::type,
            typename detail::decay<X>::type...
        >
        operator()(F&& f, X&& ...x) const {
            return {secret{}, static_cast<F&&>(f), static_cast<X&&>(x)...};
        }
    };

    template <std::size_t ...n, typename F, typename ...X>
    struct partial_t<std::index_sequence<n...>, F, X...> {
        partial_t() = default;

        template <typename ...T>
        constexpr partial_t(make_partial_t::secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, X...> storage_;

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) const& {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)...,
                static_cast<Y&&>(y)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) & {
            return hana::at_c<0>(storage_)(
                hana::at_c<n+1>(storage_)...,
                static_cast<Y&&>(y)...
            );
        }

        template <typename ...Y>
        constexpr decltype(auto) operator()(Y&& ...y) && {
            return static_cast<F&&>(hana::at_c<0>(storage_))(
                static_cast<X&&>(hana::at_c<n+1>(storage_))...,
                static_cast<Y&&>(y)...
            );
        }
    };

    constexpr make_partial_t partial{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_PARTIAL_HPP

/* partial.hpp
G41B085O6i+XyJi8yr7jQF6ESRaTm/sDvTPIjPutI/xGcL5A0hwnfuMP6nR8RbWbn0NrNBvxwAdNRZqNUrnDlHpMmddr4rXDRNcQu9Gb1iwAxsQSou4Je4dbPLGvQOhG1chfWaDzaOy329j7xKPGcO97LLPX/F4VMH+t08cRj6b3XWGDD4j46T0hphDibI5dtrKGEPUr4H8h8jj6Ff4Xhs55j8Q4gvlq6Mr9sU50TQ+orCjjHJQocLG2OM8sK9EWP1G1r7cFEodjHxF9zT9FNfrjJU4exXzsUuNNXETskV8k650kwWeO0pEH1Xj58+IXzI1zzkNlhc7hL85E/8Nh1asE94eH1uTzWHH+PV4pa2Ywc5emtlJJsVrURqkdXuw3uGyAJC9n00z4RZG9A2LWc/xXZBcAZh8Wl9N3JFDsNfzFEL8rRTyvE/FQD3VhBmv3wTSlut1zlHxg98eqbmnMNJOFyqY3I56SaNB8QHfgEvbqb1XL7KWeT4d9q9zW4tdO3SpK3GqDucqCk9GHUA3qnRSrS3c5D06rbjpDtxvNaPQtMSiCah+L76HJH5iPFNWIZBbmvhbou1N1y9c0Fz/GeSaaR70D6ENNhA0L0RIozMops0nYELbfUrzsJ3C7rv6h1Du6WuCrmkxyxN/uLkRQe/wlYeK8YrgQV/Ff7eoqMVYewh+B+W91nnijvbIVl6nn975xXrEl+8QoFUkU7/MDgZGTLPHXqVvd7hP/sMgh+W6p+1+HiP35LcrGGwv4oxr0Z0Ir7lVrZW+KJLo5/hI6kzVMJHlWir0jOtyP/PaSbyj2mxHrj6Vyp4tkztmb+TguhJWpSJ4niTj5s7CxF9T4i45O4kcwohw1dqAabNmhJgvuUGvdfIh3d+T8S1OPxpvbqr8dJL1bQxGvddCu8Nwn0Yr0FdM9L1Qtc6Cqbb4s4jqArlPURsNmAgU5QSzemIhfF8k8xYj94UZ/x3Geck9b+Srr6SkJem8TtnY9tTEAW3IzRmGdGHXGj8twS2PGb4Ka/HKI82C9SIZVx7+RQySdtgvRtrH4TSDuYhoqkstD1EtnG7EPKcd5SpN1RmDPOGXPr3rpzT4aiIbSEf/f2ziJsaujGvqIP6w+ysnlnAI3PxBv3MV6xuPQxUdlLs8FXrPQX8YRr32K/8qK+HkI9sdN/H/lRDK/oaQy2WWi/gZwHx3lvHon7LQVavzebqVupSk1nS1eoIQYmM9gfpeoofJcDnlfiou7rdqIwn9/yVopX1zAp4gKWg1Qjf418f9lYF9uFkk12k0glVVFZdXbiM7oHP6/GtiDbLCtHIwbY9RGxG4J1OkB/kQ7YXenC/R3Fti0LYf4cZiHLFeNSknYH/bYCwsErlfAXrgj7KsbppqPnuLSxpPzqo1SVYj/xpdX9lso/iEigKeNJdWeK8o24QR+l1PYK+yUsW6SpfJ4sWqNMvEK/6Qx70YqsBvzRauh85MF2qK8T7iJPywF+3cX5wH6czSh6c0PsS+7i/NntKoZnEOTrYV1bWKn/cZWi8ohkjWAWffFpT66QI/aauNCDtW421vrxXqLJsoMBoafQtz3V92YB+rMIVeJG2SH/4o3O4GDeO/DkXHHQXS+MJj6XiD/WtGFc6EFPBT2+1o1lJnB+wjmY30PpZJYp33bKuXdUiCYLX5uv8T1QWtuzqGfuEpMQzlVejRQ2Sc28aaiomuJGhDta4q/UyRZViL5w3mRVGY978MnfZGuBoYLUcGH/VZH2Fl0+tRHcbkcgT5pKew0LrTv1YWt1lZZD6yOIVTrCljO1ig/RG2MWwC/4cTz3gnUzMIfexj/VQzxjxsiCedlQ8Z10a0bhL21RaP2+B367nE=
*/