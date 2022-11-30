///////////////////////////////////////////////////////////////////////////////
// weighted_skewness.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SKEWNESS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SKEWNESS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_skewness_impl
    /**
        @brief Skewness estimation for weighted samples

        The skewness of a sample distribution is defined as the ratio of the 3rd central moment and the \f$ 3/2 \f$-th power $
        of the 2nd central moment (the variance) of the samples. The skewness can also be expressed by the simple moments:

        \f[
            \hat{g}_1 =
                \frac
                {\widehat{m}_n^{(3)}-3\widehat{m}_n^{(2)}\hat{\mu}_n+2\hat{\mu}_n^3}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^{3/2}}
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.

        The skewness estimator for weighted samples is formally identical to the estimator for unweighted samples, except that
        the weighted counterparts of all measures it depends on are to be taken.
    */
    template<typename Sample, typename Weight>
    struct weighted_skewness_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, weighted_sample>::result_type result_type;

        weighted_skewness_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::weighted_moment<3>(args)
                        - 3. * accumulators::weighted_moment<2>(args) * weighted_mean(args)
                        + 2. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                      * std::sqrt( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   );
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_skewness
//
namespace tag
{
    struct weighted_skewness
      : depends_on<weighted_mean, weighted_moment<2>, weighted_moment<3> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_skewness_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_skewness
//
namespace extract
{
    extractor<tag::weighted_skewness> const weighted_skewness = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_skewness)
}

using extract::weighted_skewness;

}} // namespace boost::accumulators

#endif

/* weighted_skewness.hpp
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
*/