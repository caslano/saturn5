///////////////////////////////////////////////////////////////////////////////
// weighted_tail_mean.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_MEAN_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_MEAN_HPP_DE_01_01_2006

#include <numeric>
#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>
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
    // coherent_weighted_tail_mean_impl
    //
    // TODO

    ///////////////////////////////////////////////////////////////////////////////
    // non_coherent_weighted_tail_mean_impl
    //
    /**
        @brief Estimation of the (non-coherent) weighted tail mean based on order statistics (for both left and right tails)



        An estimation of the non-coherent, weighted tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$ is given by the weighted mean
        of the

        \f[
            \lambda = \inf\left\{ l \left| \frac{1}{\bar{w}_n}\sum_{i=1}^{l} w_i \geq \alpha \right. \right\}
        \f]

        smallest samples (left tail) or the weighted mean of the

        \f[
            n + 1 - \rho = n + 1 - \sup\left\{ r \left| \frac{1}{\bar{w}_n}\sum_{i=r}^{n} w_i \geq (1 - \alpha) \right. \right\}
        \f]

        largest samples (right tail) above a quantile \f$\hat{q}_{\alpha}\f$ of level \f$\alpha\f$, \f$n\f$ being the total number of sample
        and \f$\bar{w}_n\f$ the sum of all \f$n\f$ weights:

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X) = \frac{\sum_{i=1}^{\lambda} w_i X_{i:n}}{\sum_{i=1}^{\lambda} w_i},
        \f]

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X) = \frac{\sum_{i=\rho}^n w_i X_{i:n}}{\sum_{i=\rho}^n w_i}.
        \f]

        @param quantile_probability
    */
    template<typename Sample, typename Weight, typename LeftRight>
    struct non_coherent_weighted_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<Weight, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type result_type;

        non_coherent_weighted_tail_mean_impl(dont_care) {}

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
                        return result_type(0);
                    }
                }
            }

            return numeric::fdiv(
                std::inner_product(
                    tail(args).begin()
                  , tail(args).begin() + n
                  , tail_weights(args).begin()
                  , weighted_sample(0)
                )
              , sum
            );
        }
    };

} // namespace impl


///////////////////////////////////////////////////////////////////////////////
// tag::non_coherent_weighted_tail_mean<>
//
namespace tag
{
    template<typename LeftRight>
    struct non_coherent_weighted_tail_mean
      : depends_on<sum_of_weights, tail_weights<LeftRight> >
    {
        typedef accumulators::impl::non_coherent_weighted_tail_mean_impl<mpl::_1, mpl::_2, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::non_coherent_weighted_tail_mean;
//
namespace extract
{
    extractor<tag::abstract_non_coherent_tail_mean> const non_coherent_weighted_tail_mean = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(non_coherent_weighted_tail_mean)
}

using extract::non_coherent_weighted_tail_mean;

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_tail_mean.hpp
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
*/