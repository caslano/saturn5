///////////////////////////////////////////////////////////////////////////////
// skewness.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_SKEWNESS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_SKEWNESS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/mean.hpp>


namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // skewness_impl
    /**
        @brief Skewness estimation

        The skewness of a sample distribution is defined as the ratio of the 3rd central moment and the \f$ 3/2 \f$-th power
        of the 2nd central moment (the variance) of the samples 3. The skewness can also be expressed by the simple moments:

        \f[
            \hat{g}_1 =
                \frac
                {\widehat{m}_n^{(3)}-3\widehat{m}_n^{(2)}\hat{\mu}_n+2\hat{\mu}_n^3}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^{3/2}}
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.
    */
    template<typename Sample>
    struct skewness_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, Sample>::result_type result_type;

        skewness_impl(dont_care)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::moment<3>(args)
                        - 3. * accumulators::moment<2>(args) * mean(args)
                        + 2. * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * std::sqrt( accumulators::moment<2>(args) - mean(args) * mean(args) )
                   );
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::skewness
//
namespace tag
{
    struct skewness
      : depends_on<mean, moment<2>, moment<3> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::skewness_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::skewness
//
namespace extract
{
    extractor<tag::skewness> const skewness = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(skewness)
}

using extract::skewness;

// So that skewness can be automatically substituted with
// weighted_skewness when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::skewness>
{
    typedef tag::weighted_skewness type;
};

template<>
struct feature_of<tag::weighted_skewness>
  : feature_of<tag::skewness>
{
};

}} // namespace boost::accumulators

#endif

/* skewness.hpp
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
*/