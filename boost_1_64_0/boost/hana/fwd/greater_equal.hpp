/*!
@file
Forward declares `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_EQUAL_HPP
#define BOOST_HANA_FWD_GREATER_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater_equal = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_equal_impl : greater_equal_impl<T, U, when<true>> { };

    struct greater_equal_t : detail::nested_than<greater_equal_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_equal_t greater_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_EQUAL_HPP

/* greater_equal.hpp
c97PLWN12BYhtQP3We6v1K8ghtDRrl3Ma80ErEcHEZJ5k8ZE26A4q8MmtJPfaWinQlzY7rAtGrK21DIVQAq5oJuUsaGWo9Rng88kM7yO1W0+6Z5WFF2EEsHcfZLhALeo0X3o5d3Ua0B1PTUkKoZhgNTvRTTzEkguq2K0aoBbtZV0JLfqysytWmy2aglzihLwh1b1s/T6U6XXatUlVCS3aj25BbhVcQfU4Rfa9IA4jTjVYJz45O63H00Ukegn9jCXCfZ6UrpllFqQwfeI2XoSZ7n1DuIO2hA1eTFDsznMZlOcCVSlZmNExTX028NpzYaaSUbS1gSSsqotZlWbaDJDzd6bpnX2Si3RRBCK8h8yhxOlUHB1zJsqICBQIvdL/XeCe6ZkcY5EUGYxAOZkrtRyqH5ZVgZmT5kI+lwWBCVm0xAU1Svh05RUC0E1Ku3AYAQ9bKrYE0JCHWs8iSms86wOuZz1awUaup4HMktSuyJpPea23MRO1nQyUzAti8nYrMVms5Zk6Y0ZOJVqzEBQWaEJEKWSwWzGlr3PaFnuWYYqwDtLWBlwjlOY2XoQsZQ6CoSdQGw7yPEDNgFXYBCpkLKo4DCKWkoQJnbwKJFZlYUQglroyWNDA7W5zp80sJNQXuInoSdX7FIJnYDQOMFnAjxZ7V4EF8n6HWMZsJkOnvmnWdVGWO0s5wEpU7SUhqTJmNmSBTPxVvB5gsw0wKQJg2z3cmIteCRN36isb1iV20LLCxIvU9ByoxxcH2cB6iHYzAyYBGpyvO/CGEqj0Yoc6RdAf2bEyVbGyZUpOEm1KPZZOLnEwElkkaxOhRxNg0s5lnYdKNiVDJLMXukQ6nSapU4tkIQ6pVIPBHelYQaKgzIhAWRctgbxnmR4vNeCR0PnkHJN7ZPpCpZVK3K1sLElbTCrm4PZp4c7mF1qaNgNXLup05XMXRFGA5bOJpccRCN1S4EcRkPsowSlEhm1KHcMtJwxFg9u5v7OCInnrGHTgbHJAEaUkgEVt5ljup2OYaBinYWKTcmoyGOdAPUoHu/EBSmP08zqs2CVRXwPFJ1sStmM6ai4ZDAqUnOJfTyyqEmgog2gyIyK6UCxxILE+hytBYlM1iXWmG1typhNZaHk4QrN7u5nOZD6jHnjSSV1QxMSob9wNiARGRt4iIIMHsFh0ojiAWMibx8M5UzEwsPVufEw/zCP1x418fCQVC2tBhjemwkMm5jHOuLRhEHZAVPBMEjZ4LeF+OZE0oKGdrPvPZix7zEO9lDfA4vgNKkpWy0YvDc3DBqtGeXWbGH0lUMbwt9kAFwKmkgPZ8VAcJ3AQcIxAweRLVoURQxGQNSJNfzeYSBuyuwRefLUEaUxBsYzo5+ltXkmTwgY3BE8n4J+rEMjhsQ6JI91PHSU6GcZQi4xABaZABiwB4AZposg7L4kAJTQF9xPyAcAJOjLf5iNQlKR0czERRqPkE6qtAL0uowAWA8Vhb6fFf2aLPRbaqjN/B5wZ45c2AIxXPRrstBvac4pojFIe9ocpOncA0nQMOok5M4wPxSwc0hdY1gykEB2RnTKI1kwsM7AQJlnGgxuMrviZqMr2hyUQnotrboko1aNZrLpbEibbPSnmDgGHFmmiK0MgGA+MUXczBqAx4a4wWAoczXQUJaV0cyx14TEh3JDIuqJhm5GB7JQsXVIVDwtoFMyoaJOfHKbp6NiUxoqWjN9G3PFfhMVBwahIufYkwkxuK6skcy9uUcy6dqUO6QxbefhhcRGVqghw+S6nGWjLhUVM04UkaWFitEUHtOtzLmNrElmDMvCGiUkpBJMGwbbWI+I40l4CCBcZ3a1+sR8KcLaOx0PmbtWw+RhAxLrLUi0zOk=
*/