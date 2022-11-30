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
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
*/