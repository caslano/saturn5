///////////////////////////////////////////////////////////////////////////////
// weighted_tail_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_tail_quantile_impl
    //  Tail quantile estimation based on order statistics of weighted samples
    /**
        @brief Tail quantile estimation based on order statistics of weighted samples (for both left and right tails)

        An estimator \f$\hat{q}\f$ of tail quantiles with level \f$\alpha\f$ based on order statistics
        \f$X_{1:n} \leq X_{2:n} \leq\dots\leq X_{n:n}\f$ of weighted samples are given by \f$X_{\lambda:n}\f$ (left tail)
        and \f$X_{\rho:n}\f$ (right tail), where

            \f[
                \lambda = \inf\left\{ l \left| \frac{1}{\bar{w}_n}\sum_{i=1}^{l} w_i \geq \alpha \right. \right\}
            \f]

        and

            \f[
                \rho = \sup\left\{ r \left| \frac{1}{\bar{w}_n}\sum_{i=r}^{n} w_i \geq (1 - \alpha) \right. \right\},
            \f]

        \f$n\f$ being the number of samples and \f$\bar{w}_n\f$ the sum of all weights.

        @param quantile_probability
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct weighted_tail_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Weight, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef Sample result_type;

        weighted_tail_quantile_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
                }
                else
                {
                    if (std::numeric_limits<result_type>::has_quiet_NaN)
                    {
                        return std::numeric_limits<result_type>::quiet_NaN();
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                        return Sample(0);
                    }
                }
            }

            // Note that the cached samples of the left are sorted in ascending order,
            // whereas the samples of the right tail are sorted in descending order
            return *(boost::begin(tail(args)) + n - 1);
        }
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_tail_quantile<>
//
namespace tag
{
    template<typename LeftRight>
    struct weighted_tail_quantile
      : depends_on<sum_of_weights, tail_weights<LeftRight> >
    {
        /// INTERNAL ONLY
        typedef accumulators::impl::weighted_tail_quantile_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_tail_quantile
//
namespace extract
{
    extractor<tag::quantile> const weighted_tail_quantile = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_tail_quantile)
}

using extract::weighted_tail_quantile;

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_tail_quantile.hpp
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
*/