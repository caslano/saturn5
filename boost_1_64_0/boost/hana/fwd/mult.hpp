/*!
@file
Forward declares `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MULT_HPP
#define BOOST_HANA_FWD_MULT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Associative operation of a `Ring`.
    //! @ingroup group-Ring
    //!
    //! @param x, y
    //! Two `Ring` elements to combine with the `Ring` binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mult` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mult` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Ring`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `mult` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     mult(x, y) = mult(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mult.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mult = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mult_impl : mult_impl<T, U, when<true>> { };

    struct mult_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mult_t mult{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MULT_HPP

/* mult.hpp
5RLkG1Gb8vwPacC4ASgYdbYoD64gWAdXsn1jZK37Mz2FkISa04jiyzGX61bRgaMS/At+VpnxpRuBQA5PpjIzyz0zVanIVd9WK1Jq9px3acXbytxs92aiyjWfdF30npM5qbQvibTckaZhrzo+ozsCMzPbnR4mG4ishtwtRxHCZCaDSe4GSQgb6n0r0UqEELF5jYnNodD7T5xUa0+eyKBfSce2MbqKgA12cgsJ5yWhdreyeRY8we2SMtaltoa291MQhOC00LTUNJrDPem9kR+IlOMBc1opS1J8yZjkhBX9qCzbVi6rwKOMnXCS5ShlE5GZ8DeW895N6KtnSVR8k7l85W52KN+qPPQbicztvUKilw3JlLtjTITIeFXuk7iciIm1IxGdR2kWimyktOsRASy7z4oQ5SE7hb+qlqWqTSBuApSN0XsToRmJ3fbo9IsmIRAOdO4wIeVaBbHKzDR1pzIRkzNVKcIlPiAqigDiEvUkEkusl61LIpAD9A8kD7R2txLIA+rdkY9uQyTwXj+bkGTghiImA8rtxWoz4IAXBgkohu1j5VHCMeVZwi1Nw1n5MWGV+rLyOCEiSMTOfiCe6jw0tFVzlquW5yr3rscD01VbK7f63r9RQBMIZtDOxJXJvXLvVi5aktRxWbhW5M9W25XvvknvhZnqbhCG7Q5adV4neAAL6Bm7K1449AXFJtQW7pdyayZ3TVmQpTaif7JrZdkYonf5Zaviy6XRbpQzRzjUdcqCSuWF1QbdLpur3L2dyTMR9IeIUjO5UHzzlLv/zp1Q7mtl0kO0Sbl1pvIHotJUVpndtp7uU90nKOA9gJ4mYi/lD/+gfLda1c2hnYnqHpoOvUizMyQSaZwT6RnpQu2JtlDovV62vQoCaIVR1/DIo59K6VTqeZcyckZIEHGdUqER4mmcG+vj+wAMgGULEYFVHqyXhPJ1kGHZOSoUVNa2TalboqkOqx2SYAJIy5nsIgk6ha6BNmP13J6A0h5cySVRdqXuL/S8BeOqrZEYf4zwk0RaledXMcHdzarxPFtIkE9DQ2mCn/LE0eYRSjAmTDkuNgU7mQzXHcQPax9N+Xfb2Pn67+u//9S/454//eBg15HnT/1xIKVKN1cuOoPC+dP1Fjp2AjW0IguW6WEmPowawjtTvMbqD2b9oYd7q/tq/Oob82Hx+kNP9w1s1RGlWvWwM/QHm/7Qy30DHT65kMquh/XWHxzqaJcbEml+J0Gd+wZ7cLiTZddJp3725Dzx2ZPr1KScR549pdDZk53PnlLorO5U2+U6LXHiROcJzp6OkQafcpv09qBpp9impM86e0oxpOZfKZxSTnT25OSzJz7xSCUVHj57Sj3VVqWeXqvSTnT45KLDJx1aGQa0UmtXZ341TQOifNb5U2oOdNS086fM4x0/pdLxkxUYYcMpBB8/AcCWI8+enJi++tETBkI/e0qhOVt8GjP29GdH0nEw+z9sxkbPnqLnYaeJ2affprQTnj0dO1eNNmlt0av4stuUeTw4GZitwyrrK4dV9ufCKpcgxYdPcBic99U068TnTxKnjfOnVKZCc+3QC5HnT3hz8jo30/IvP35KNY6fkr8+fvr670v5q4V2Vwy7C0pqvjDG2X5DR1eEXh6nl+cvOsYeZwWlInXiE33ENz7tIm1VfT6ecv7eFxz4Qvkv6//F8s8ZdOL8DC+nCens+qeqp7h1P/XY3ihK5EP3rEhiJQmZh9OvJGOeIiOOdUWjyT4n/acfdZ0wPakQkn7gNaQfCNU8MlZov4b2N5VnXbOafnpfE2PCT/wquuAJtWVcranqLY2V3U3Fkz5xbStiuLwTwSv5eB8xPJ7vfhtZjfs/NAYgWGyhyys=
*/