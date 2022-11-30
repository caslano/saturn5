///////////////////////////////////////////////////////////////////////////////
// weighted_variance.hpp
//
//  Copyright 2005 Daniel Egloff, Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_VARIANCE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_VARIANCE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //! Lazy calculation of variance of weighted samples.
    /*!
        The default implementation of the variance of weighted samples is based on the second moment
        \f$\widehat{m}_n^{(2)}\f$ (weighted_moment<2>) and the mean\f$ \hat{\mu}_n\f$ (weighted_mean):
        \f[
            \hat{\sigma}_n^2 = \widehat{m}_n^{(2)}-\hat{\mu}_n^2,
        \f]
        where \f$n\f$ is the number of samples.
    */
    template<typename Sample, typename Weight, typename MeanFeature>
    struct lazy_weighted_variance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        lazy_weighted_variance_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> const some_mean = {};
            result_type tmp = some_mean(args);
            return accumulators::weighted_moment<2>(args) - tmp * tmp;
        }
    };

    //! Iterative calculation of variance of weighted samples.
    /*!
        Iterative calculation of variance of weighted samples:
        \f[
            \hat{\sigma}_n^2 =
                \frac{\bar{w}_n - w_n}{\bar{w}_n}\hat{\sigma}_{n - 1}^2
              + \frac{w_n}{\bar{w}_n - w_n}\left(X_n - \hat{\mu}_n\right)^2
            ,\quad n\ge2,\quad\hat{\sigma}_0^2 = 0.
        \f]
        where \f$\bar{w}_n\f$ is the sum of the \f$n\f$ weights \f$w_i\f$ and \f$\hat{\mu}_n\f$
        the estimate of the mean of the weighted samples. Note that the sample variance is not defined for
        \f$n <= 1\f$.
    */
    template<typename Sample, typename Weight, typename MeanFeature, typename Tag>
    struct weighted_variance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        weighted_variance_impl(Args const &args)
          : weighted_variance(numeric::fdiv(args[sample | Sample()], numeric::one<Weight>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> const some_mean = {};

                result_type tmp = args[parameter::keyword<Tag>::get()] - some_mean(args);

                this->weighted_variance =
                    numeric::fdiv(this->weighted_variance * (sum_of_weights(args) - args[weight]), sum_of_weights(args))
                  + numeric::fdiv(tmp * tmp * args[weight], sum_of_weights(args) - args[weight] );
            }
        }

        result_type result(dont_care) const
        {
            return this->weighted_variance;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_variance;
        }

    private:
        result_type weighted_variance;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_variance
// tag::immediate_weighted_variance
//
namespace tag
{
    struct lazy_weighted_variance
      : depends_on<weighted_moment<2>, weighted_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::lazy_weighted_variance_impl<mpl::_1, mpl::_2, weighted_mean> impl;
    };

    struct weighted_variance
      : depends_on<count, immediate_weighted_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_variance_impl<mpl::_1, mpl::_2, immediate_weighted_mean, sample> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_variance
// extract::immediate_weighted_variance
//
namespace extract
{
    extractor<tag::lazy_weighted_variance> const lazy_weighted_variance = {};
    extractor<tag::weighted_variance> const weighted_variance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_weighted_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_variance)
}

using extract::lazy_weighted_variance;
using extract::weighted_variance;

// weighted_variance(lazy) -> lazy_weighted_variance
template<>
struct as_feature<tag::weighted_variance(lazy)>
{
    typedef tag::lazy_weighted_variance type;
};

// weighted_variance(immediate) -> weighted_variance
template<>
struct as_feature<tag::weighted_variance(immediate)>
{
    typedef tag::weighted_variance type;
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<weighted_variance_impl>
////  need to specialize droppable lazy weighted_variance to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename Weight, typename MeanFeature>
//struct droppable_accumulator<impl::weighted_variance_impl<Sample, Weight, MeanFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::weighted_variance_impl<Sample, Weight, MeanFeature> >
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

/* weighted_variance.hpp
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
*/