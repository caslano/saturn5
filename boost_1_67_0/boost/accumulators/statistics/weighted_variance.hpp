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