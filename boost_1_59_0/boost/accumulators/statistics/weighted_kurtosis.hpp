///////////////////////////////////////////////////////////////////////////////
// weighted_kurtosis.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_KURTOSIS_HPP_EAN_28_10_2005

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
    // weighted_kurtosis_impl
    /**
        @brief Kurtosis estimation for weighted samples

        The kurtosis of a sample distribution is defined as the ratio of the 4th central moment and the square of the 2nd central
        moment (the variance) of the samples, minus 3. The term \f$ -3 \f$ is added in order to ensure that the normal distribution
        has zero kurtosis. The kurtosis can also be expressed by the simple moments:

        \f[
            \hat{g}_2 =
                \frac
                {\widehat{m}_n^{(4)}-4\widehat{m}_n^{(3)}\hat{\mu}_n+6\widehat{m}_n^{(2)}\hat{\mu}_n^2-3\hat{\mu}_n^4}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^2} - 3,
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.

        The kurtosis estimator for weighted samples is formally identical to the estimator for unweighted samples, except that
        the weighted counterparts of all measures it depends on are to be taken.
    */
    template<typename Sample, typename Weight>
    struct weighted_kurtosis_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, weighted_sample>::result_type result_type;

        weighted_kurtosis_impl(dont_care)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::weighted_moment<4>(args)
                        - 4. * accumulators::weighted_moment<3>(args) * weighted_mean(args)
                        + 6. * accumulators::weighted_moment<2>(args) * weighted_mean(args) * weighted_mean(args)
                        - 3. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                        * ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   ) - 3.;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_kurtosis
//
namespace tag
{
    struct weighted_kurtosis
      : depends_on<weighted_mean, weighted_moment<2>, weighted_moment<3>, weighted_moment<4> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_kurtosis_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_kurtosis
//
namespace extract
{
    extractor<tag::weighted_kurtosis> const weighted_kurtosis = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_kurtosis)
}

using extract::weighted_kurtosis;

}} // namespace boost::accumulators

#endif

/* weighted_kurtosis.hpp
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
*/