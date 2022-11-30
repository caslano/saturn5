///////////////////////////////////////////////////////////////////////////////
// variance.hpp
//
//  Copyright 2005 Daniel Egloff, Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_VARIANCE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //! Lazy calculation of variance.
    /*!
        Default sample variance implementation based on the second moment \f$ M_n^{(2)} \f$ moment<2>, mean and count.
        \f[
            \sigma_n^2 = M_n^{(2)} - \mu_n^2.
        \f]
        where
        \f[
            \mu_n = \frac{1}{n} \sum_{i = 1}^n x_i.
        \f]
        is the estimate of the sample mean and \f$n\f$ is the number of samples.
    */
    template<typename Sample, typename MeanFeature>
    struct lazy_variance_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        lazy_variance_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> mean;
            result_type tmp = mean(args);
            return accumulators::moment<2>(args) - tmp * tmp;
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    //! Iterative calculation of variance.
    /*!
        Iterative calculation of sample variance \f$\sigma_n^2\f$ according to the formula
        \f[
            \sigma_n^2 = \frac{1}{n} \sum_{i = 1}^n (x_i - \mu_n)^2 = \frac{n-1}{n} \sigma_{n-1}^2 + \frac{1}{n-1}(x_n - \mu_n)^2.
        \f]
        where
        \f[
            \mu_n = \frac{1}{n} \sum_{i = 1}^n x_i.
        \f]
        is the estimate of the sample mean and \f$n\f$ is the number of samples.

        Note that the sample variance is not defined for \f$n <= 1\f$.

        A simplification can be obtained by the approximate recursion
        \f[
            \sigma_n^2 \approx \frac{n-1}{n} \sigma_{n-1}^2 + \frac{1}{n}(x_n - \mu_n)^2.
        \f]
        because the difference
        \f[
            \left(\frac{1}{n-1} - \frac{1}{n}\right)(x_n - \mu_n)^2 = \frac{1}{n(n-1)}(x_n - \mu_n)^2.
        \f]
        converges to zero as \f$n \rightarrow \infty\f$. However, for small \f$ n \f$ the difference
        can be non-negligible.
    */
    template<typename Sample, typename MeanFeature, typename Tag>
    struct variance_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        variance_impl(Args const &args)
          : variance(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> mean;
                result_type tmp = args[parameter::keyword<Tag>::get()] - mean(args);
                this->variance =
                    numeric::fdiv(this->variance * (cnt - 1), cnt)
                  + numeric::fdiv(tmp * tmp, cnt - 1);
            }
        }

        result_type result(dont_care) const
        {
            return this->variance;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variance;
        }

    private:
        result_type variance;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::variance
// tag::immediate_variance
//
namespace tag
{
    struct lazy_variance
      : depends_on<moment<2>, mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::lazy_variance_impl<mpl::_1, mean> impl;
    };

    struct variance
      : depends_on<count, immediate_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::variance_impl<mpl::_1, mean, sample> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::lazy_variance
// extract::variance
//
namespace extract
{
    extractor<tag::lazy_variance> const lazy_variance = {};
    extractor<tag::variance> const variance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(variance)
}

using extract::lazy_variance;
using extract::variance;

// variance(lazy) -> lazy_variance
template<>
struct as_feature<tag::variance(lazy)>
{
    typedef tag::lazy_variance type;
};

// variance(immediate) -> variance
template<>
struct as_feature<tag::variance(immediate)>
{
    typedef tag::variance type;
};

// for the purposes of feature-based dependency resolution,
// immediate_variance provides the same feature as variance
template<>
struct feature_of<tag::lazy_variance>
  : feature_of<tag::variance>
{
};

// So that variance can be automatically substituted with
// weighted_variance when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::variance>
{
    typedef tag::weighted_variance type;
};

// for the purposes of feature-based dependency resolution,
// weighted_variance provides the same feature as variance
template<>
struct feature_of<tag::weighted_variance>
  : feature_of<tag::variance>
{
};

// So that immediate_variance can be automatically substituted with
// immediate_weighted_variance when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::lazy_variance>
{
    typedef tag::lazy_weighted_variance type;
};

// for the purposes of feature-based dependency resolution,
// immediate_weighted_variance provides the same feature as immediate_variance
template<>
struct feature_of<tag::lazy_weighted_variance>
  : feature_of<tag::lazy_variance>
{
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<variance_impl>
////  need to specialize droppable lazy variance to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename MeanFeature>
//struct droppable_accumulator<impl::variance_impl<Sample, MeanFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::variance_impl<Sample, MeanFeature> >
//    >
//{
//    template<typename Args>
//    droppable_accumulator(Args const &args)
//      : droppable_accumulator::base(args)
//    {
//    }
//};

}} // namespace boost::accumulators

#endif

/* variance.hpp
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
*/