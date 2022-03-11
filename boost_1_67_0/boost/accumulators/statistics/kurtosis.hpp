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