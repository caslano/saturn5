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