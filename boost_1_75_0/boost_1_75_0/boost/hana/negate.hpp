/*!
@file
Defines `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NEGATE_HPP
#define BOOST_HANA_NEGATE_HPP

#include <boost/hana/fwd/negate.hpp>

#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/zero.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) negate_t::operator()(X&& x) const {
        using G = typename hana::tag_of<X>::type;
        using Negate = BOOST_HANA_DISPATCH_IF(negate_impl<G>,
            hana::Group<G>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<G>::value,
        "hana::negate(x) requires 'x' to be in a Group");
    #endif

        return Negate::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename T, bool condition>
    struct negate_impl<T, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::minus(hana::zero<T>(), static_cast<X&&>(x)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct negate_impl<T, when<std::is_arithmetic<T>::value &&
                               !std::is_same<bool, T>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return -static_cast<X&&>(x); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NEGATE_HPP

/* negate.hpp
Mk2prySl9cVPT38ZV04/pqay/Y9/LH01deY/0+X9Sax8WTKmPFcXcaSTnhZvb/j0Xy1kuiZZvNUS4BNz1u9oWq8jtXvE97tdsH5jkZvcubPmuaz1FzTny7dYM0pGy3rdL0JFGcEVmfSNNRwv1iYY9ZseCaYGmP06wF7ffcdoT1XEGzs7Ljfs2sPDvQ/ym4/UvI+ZZcFJ+mY5NZzQFu24NuIti7t/IfNsDUNZ377f31V3tv8yQ1qU8Ziqe3OhH512/Cb0o2SjIfPujxo+uKdgoKv/Ywq/n49XOW30Ib2MJcVLT0UZV7tE+fLbPFj2Ql3Eipp/fCwpVnR4ra+APf+3sBDlswtJKGlqaazPAMTvlxQbHNdlAJJ7DPSGVgOEqrkx9vqQ9UgDvWyWzgxAyx0DvaCCrgwA0Sk7zdgSmgHoKS0pHgt4WtKctFFSLFLYlAHYrSlpKpVkeIAbw99XylKZipRRfC3v/K5GMKIs4NnYm7178Lv3k1URqhvPz2LlYOJuhL/tkxtemq1jfJkV+Hz+YGQFgLMN43U66nBclkdTkje695gqPGq5Mc/h0li5BrR5bZea2NVVOLzrrT8e6U3LNjVpkqkizMfPrZK2ahCtagvsLbPkHHayTdcMF913L6Kf3ihSjnFmvF1Pd6lRPTNf6VJe0EX53X3YqIV1XJOGb0+2eqFmRv7eJdVZSgNL0/2oOYaTssksIH7oUhCd
*/