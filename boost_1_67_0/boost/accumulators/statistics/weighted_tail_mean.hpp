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