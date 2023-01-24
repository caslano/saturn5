///////////////////////////////////////////////////////////////////////////////
// kurtosis.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_KURTOSIS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_KURTOSIS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // kurtosis_impl
    /**
        @brief Kurtosis estimation

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
    */
    template<typename Sample>
    struct kurtosis_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, Sample>::result_type result_type;

        kurtosis_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::moment<4>(args)
                        - 4. * accumulators::moment<3>(args) * mean(args)
                        + 6. * accumulators::moment<2>(args) * mean(args) * mean(args)
                        - 3. * mean(args) * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                    ) - 3.;
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::kurtosis
//
namespace tag
{
    struct kurtosis
      : depends_on<mean, moment<2>, moment<3>, moment<4> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::kurtosis_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::kurtosis
//
namespace extract
{
    extractor<tag::kurtosis> const kurtosis = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(kurtosis)
}

using extract::kurtosis;

// So that kurtosis can be automatically substituted with
// weighted_kurtosis when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::kurtosis>
{
    typedef tag::weighted_kurtosis type;
};

template<>
struct feature_of<tag::weighted_kurtosis>
  : feature_of<tag::kurtosis>
{
};

}} // namespace boost::accumulators

#endif

/* kurtosis.hpp
A9dCd1IpWleezo8H4B8YmoByr2DQAm/Ia9ib+RBSxsUrSZmatPCDmxHgYALrafkv+Jr8tVsNXPo7aVhg2yzUeUJ9gTVP4naok+W8hxA9ELqXj3y1CODw35thOF4fi266l35nG49ytdr/yp+Ez8XJfeJXV4W/Aoj7LLaK35GfaRQ7dd69Tnb1e7H9QPXdaXgFX1ow1qCBICcbxanOuAdStvVE2UZqFhEsa+6+HND/nG19ys8UI4DGv5o+QArgR0nvjPsCfZXC7EnFlkKn3QT3yOVwkfcDgIWRiMbBYBjM1IERj1vB/cAzMMZnLj4jmhtoRuCcieKO4Z+ki+0YPopz9Tp4tR7VEVjXJyinvPeWyK8fUE/TqivL2b+0srPRXvBvOHJLvDQdIXqitqDM61IoJJJSBAC59nrcHhbWWdQErUABvcsjw/nGQxzncEQm36LtWlygloeET9/XaAgAetnTjpjABhSQiHHydEHWy02kAtDO+y/7Ro+u0auNaB/OozhJlFo6lV19i+rI0gIcAqbbDVmzis38g6e+RmhaP87TaT0048wpMaqrSRPDpsazSKzyyz/GKsLsIFoBPA5s3JA2w969MMwt6HsU5fYdahs8OlkPtZb216lswiZNZRuLSFMPp+62r1ExEL/h+1b1yHh3GVvRTPZpgwu658wiPRfGHh9gWQKdJnazJRCFAk4N06E1ecj+c2XO/g3OHbEN
*/