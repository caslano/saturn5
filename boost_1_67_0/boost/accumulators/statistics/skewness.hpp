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