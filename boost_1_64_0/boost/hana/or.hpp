/*!
@file
Defines `boost::hana::or_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_OR_HPP
#define BOOST_HANA_OR_HPP

#include <boost/hana/fwd/or.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) or_t::operator()(X&& x, Y&& y) const {
        using Bool = typename hana::tag_of<X>::type;
        using Or = BOOST_HANA_DISPATCH_IF(or_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::or_(x, y) requires 'x' to be a Logical");
    #endif

        return Or::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }

    template <typename X, typename ...Y>
    constexpr decltype(auto) or_t::operator()(X&& x, Y&& ...y) const {
        return detail::variadic::foldl1(
            *this,
            static_cast<X&&>(x),
            static_cast<Y&&>(y)...
        );
    }
    //! @endcond

    template <typename L, bool condition>
    struct or_impl<L, when<condition>> : hana::default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            //! @todo How to forward `x` here? Since the arguments to `if_`
            //! can be evaluated in any order, we have to be careful not to
            //! use `x` in a moved-from state.
            return hana::if_(x, x, static_cast<Y&&>(y));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_OR_HPP

/* or.hpp
Oqe5bVnbsi20j3pZbvuQKkHei+WPJeVxYFdKauPLP+So8id4+eN1Uxfaqs6XX3/4XiDgcrVKdRWYUkWLPSfE16aNF8fGqPs4WKMr2BbuOnFtn1KpXCql1NUwPtHBluPWOGnHH885TmuI9BJqhjvS51WjuwyY5P6fc6ktgHV6uL+/bR4+cnNzJ74ciike6WdvnLSjxI22sFVDrMJxdmy+jr/N6W4viz7r5FASWb/5yIkmj3sSp8klzg3dl5mO75IoPzb8iJP/gfF7PYvLN7etTWOb2vRU74K/6etVqqcalDFYJ3DCpZWVqtrXH4FLnZcRvd1FH2V5NZOPmqaqrNZ+9t711n5FYAKPv9FaWYhk+eC4z/4kmXeN1H1RdHXc0sbCy1E/k9Q9iEZlZa1tJpjSe8s/j7kph31nayMiGDgrE16/jDyvrFOeNY5wkyvG0l/Q8ewAxvgNtkYujUCzOFOKK6tT/YiUyi3Y/J+2MwBOEzOmVzipZ+dtZqt2aBfYsTjvjBOzmdHpPbIYFDRcfR73W2dC5fdbYszYMB3L0zifE8a2VYb5KwrT6igXEw35gOsES7PqlO5NAQuuU4cP3w6ieyz7El72trrAbaGpXNm9U9GRmsq+KimrmrzwMWU831iW8Bl0eqcynVbGYU/sj5f+4/eciwPTPvVena7ZymHQdlUuJvXiIxIZhNF+Vc/uv0XhIDvK5C5ZZKa9+7Ken5G/0Knerqggvuj5FXx+FYtcCMsBxpizN9QMjIyxSRtgKZ7lrVmptJrL6pcukvgvTZUPGbrib8Dz+XHlIpWHJDYI1WfiISykXaAxeTzfirR9Uuaq1RXJAlhruxtcecbuQnGcRZHuTdCeQ0Qp+rRi/pHYnbmYxfSTTS0dVpwdA+PQdZteRw933fVgxEJn8foTPlpYpQ2EhgExFSGKY3GyOxHv1TbEfK5jfXXCpwAf/CkwV3GiMAZoDBgmbRmfaui9tkjvOl2WVbmTZFsfZnVidRuuq6XBneZhMcMW7rrC9GV7NB9SRBMjFx/4UdfEvdP74x/sT2bczlgfPtjI37sg5oHP566TB0uXRMzQx1wT6T5+723p9/P7389dumL4/QL+9/GpxptDh/QL+vTBLq9OaRfyaXfvzcklor9wSGux34Cc0i/i03tifM2QfrGx/DDA9fEea2M0YFZviEuMV/QQExVpIQaxD3jqo+Dyei4zlofLR2GXu4nP5cf2ZysrE58rUNk16LRMz/lc0eepasiWs46lX2lMjxUQ/ytP6VT2KmNao+/F24L6x3TXGEq7GpWd2nd14kkNpLxrIy+kymzIViuWdx2XF8YyZFKbrjt+BwvfL1npKf16Ph0KjzGD0q8fx991gX23G7A64AEDUqcXm9pwQ55/t7sbvTrl3SjEnzatWujXTXm/3GnI8m7GeIZMGr+bj/3KjZ36dAtKW1vFtkzpt/TppuzXtC0Y/1uFsWFZxP/Y+C00omZT+Vv7NNgkYdjGnKnuc3wezoLVu68ssXG7DUt3Xcmx9/P827J8H47b3n11ibXxOM+HzRdv47k+r1vh7bhdTHPDxcqeGNu+nElNdd8+rCt592Wzeq/QWXfshfw7HJFPfWC870ht1JR2J5pHU7k7+zQ/OSjtLuPcWDa6oD7cNX4XVfl6rhvSRUyHB9bdO72mh0p3ejlrWf8zXwYP6GuV6dnelcd0NrZqbPfycHfsLStaK9YnHeKo34PxLtneBTM3Klv5dHdxnujNuK+u3KuXVF/t06K/nyn5PGjGvKE1bsR7tVYsZyVrazt+1+zkGu77GrutXqF2daGtmcIiK6b22jhfgUzE97phSr81/453o/QpbXlcB0ic0lYo7dY=
*/