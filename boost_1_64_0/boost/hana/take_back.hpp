/*!
@file
Defines `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_BACK_HPP
#define BOOST_HANA_TAKE_BACK_HPP

#include <boost/hana/fwd/take_back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto take_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeBack = BOOST_HANA_DISPATCH_IF(take_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::take_back(xs, n) requires 'n' to be an IntegralConstant");
#endif

        return TakeBack::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_back_impl<S, when<condition>> : default_ {
        template <std::size_t start, typename Xs, std::size_t ...n>
        static constexpr auto take_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<start + n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            constexpr std::size_t start = n < len ? len - n : 0;
            return take_back_helper<start>(static_cast<Xs&&>(xs),
                        std::make_index_sequence<(n < len ? n : len)>{});
        }
    };

    template <std::size_t n>
    struct take_back_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::take_back(static_cast<Xs&&>(xs), hana::size_c<n>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_BACK_HPP

/* take_back.hpp
b5kcKlM5oYLaEYGLaN51nFNFnQ3ztVRO1HViyrm1pznfz8M5NeEX0nOrzZAHdFzrRuva1ulWFnBe1gv2Cn7JhoZXfcMTO36bJXPGeqG8q94oWVlZsfFsXI7R1k3yHkp5btU3beuNcAmjYFbiZTyP0t6mFta7XqgSn3M8bpZj+jLKd77mlWjrtmOZZzkzjGk4M9356hlrcg32hvAbfZvWUvbW9Dz7xGLyVzhjwXP0eVLar8MftpFrfk3bhD8J5QmfIOz0+CxhFMRHKP/K+Rn8lbEDbgLPL3fl0MYwfxdj/8+/ILQ3lo0HtSuk5+LK8DztUfld/OAR9P3ZqvJ1ZQJO4PbJwXTt+DWl5QPrtO7FoE3cE4CeGEpvAWa7c7PTlJEx+3uyeVz31R45sX90lZKOZz356H7BRAeND/9EKSA+XgKdnJsFW0q2sT/n+zTPxOyBAEO1f7/TFYtY5LHcd3z9tvFNSTHm6sv7/ltIeSjIfN/4Rrb53331Frfb5Gt9vDVFuVf5ZiiPZSEaLKXJXLE3zDrPN7N9HWnQw5LG234t02EpVjj3i71V+Y3WtWrDFdsSGzXH7O/EL9g/cpK3SMBXPrQmYfgAK0mhOS46u8S+PUO9diLHdAN8WqrNcnADOd3Ly/YtisWSzIH3TWQJOYRjGqe4Qv9JVvh2RPDfTj6G0Plo55DwzF8pfCMwMc87fuD27Lb4oVyP5N67WMxxG+fXZpikWTmFfLGI83YxIiN+UPTu/yGlfqGdqnv4iso72GhiWoTAIHIeV8ixzLnO9FxaRrGZFiEw0AMcx5SV9g0vVSe8F8zjEf0/HCDnsl5XtAm65PtG6lYzGGSoPW8LVDIG6k99vb5DZfUgqjN1xQ62ZqfnjgECI9P7PN9/XdStmFDh9OT7MXdf4LtL4EuheTsYm4Z+8w8tMQCECoAVDYM0BEWNuO8/tKzP9Uo6J9VYH3CdUd9t8r5P+R3zTnV131VxaYThot6ixZm0LertmGsa3w+aGpLS2rpwRN7FHI6e2ijUIDsp1MCAK+EjJGxI3O+LOmvGYWw632FewdjegnXl8F+UXWmMZc8Ub/u+RhD7vi/jz4yx163l3qq7VJXuti+tp7tHP3r6tX7d+CPiAyL4IAgiiIgIiYjggw8iIiIitti3iIiIiCCIICJO1a0679R9z/afzL+n71lquXVrOXXO7+C5gMrKmg2ibnzjOibmp6fnJ+ndhIPgWZrGjyIYdtJa+NZ+geq67J3wvvU9C8mQDo7OdlfwTL5F+UXPatOZqmlq5oIRK5VwNo/w57CzD0Crs6tXMTEWvXcCw9sUk6MZxCA82odAGZqF6JwYdn+wX0R7YqGnZ95zWVs5/K968vh79ivL8de0PnqJlHqmZieSyzDJI5aUbTqpWvSdmJ8TBwr88DPMSIm9/J5XTjC8G81NWw1JV7STTHyYzvI7/SuVvayE5tXgOAsiO/P83ZA7pZtfX+7f22EYtGix2iDyhMXZ9Wn3bwYZfrRFHQofKhbXclyvx6MpPM70uqSPxyRC73+S7vLLNR/9D55dysdb++VstDHPfC9cw7ecRZZr//4KH8CJLiD9OPRR1vWSNbpwJMA+IttRTkq+MPixX16OtBFwNPRf+K5zPV4zoecXBqTTzPOm1bpCi3Zgg7RxivuM4n02bOhty109PR+n8Tw2FT8MtrGL/sqFnpq1QjvXqOY/6aF2Y57nmOsncfu28V5IyQaQQQW4mFFHMvRd+3mho2JdayXXvGGroiWGYyHXMWmbvvJapjYQvKg43xU7N8S3o3vunnnOvbZahcndjjM0es1hXpcHUJlLnfNOVrqP2S6ss4rm5ECZy1RmYMaJtq9Fzcg=
*/