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