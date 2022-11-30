///////////////////////////////////////////////////////////////////////////////
// weighted_covariance.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/covariance.hpp> // for numeric::outer_product() and type traits
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_covariance_impl
    //
    /**
        @brief Weighted Covariance Estimator

        An iterative Monte Carlo estimator for the weighted covariance \f$\mathrm{Cov}(X,X')\f$, where \f$X\f$ is a sample
        and \f$X'\f$ a variate, is given by:

        \f[
            \hat{c}_n = \frac{\bar{w}_n-w_n}{\bar{w}_n} \hat{c}_{n-1} + \frac{w_n}{\bar{w}_n-w_n}(X_n - \hat{\mu}_n)(X_n' - \hat{\mu}_n'),
            \quad n\ge2,\quad\hat{c}_1 = 0,
        \f]

        \f$\hat{\mu}_n\f$ and \f$\hat{\mu}_n'\f$ being the weighted means of the samples and variates and
        \f$\bar{w}_n\f$ the sum of the \f$n\f$ first weights \f$w_i\f$.
    */
    template<typename Sample, typename Weight, typename VariateType, typename VariateTag>
    struct weighted_covariance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<Sample, std::size_t>::result_type>::result_type weighted_sample_type;
        typedef typename numeric::functional::multiplies<Weight, typename numeric::functional::fdiv<VariateType, std::size_t>::result_type>::result_type weighted_variate_type;
        // for boost::result_of
        typedef typename numeric::functional::outer_product<weighted_sample_type, weighted_variate_type>::result_type result_type;

        template<typename Args>
        weighted_covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::fdiv(args[sample | Sample()], (std::size_t)1)
                      * numeric::one<Weight>::value
                  , numeric::fdiv(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                      * numeric::one<Weight>::value
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::weighted_mean_of_variates<VariateType, VariateTag> > const some_weighted_mean_of_variates = {};

                this->cov_ = this->cov_ * (sum_of_weights(args) - args[weight]) / sum_of_weights(args)
                           + numeric::outer_product(
                                 some_weighted_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , weighted_mean(args) - args[sample]
                             ) * args[weight] / (sum_of_weights(args) - args[weight]);
            }
        }

        result_type result(dont_care) const
        {
            return this->cov_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cov_;
        }

    private:
        result_type cov_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_covariance
//
namespace tag
{
    template<typename VariateType, typename VariateTag>
    struct weighted_covariance
      : depends_on<count, sum_of_weights, weighted_mean, weighted_mean_of_variates<VariateType, VariateTag> >
    {
        typedef accumulators::impl::weighted_covariance_impl<mpl::_1, mpl::_2, VariateType, VariateTag> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_covariance
//
namespace extract
{
    extractor<tag::abstract_covariance> const weighted_covariance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_covariance)
}

using extract::weighted_covariance;

}} // namespace boost::accumulators

#endif

/* weighted_covariance.hpp
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
*/