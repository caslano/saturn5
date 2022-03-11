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