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
+PX6hGamODpgDPNQTVt5ldNF5Vt1qx9giNMi/4SbMcSFwD9+HZLAThIKess9icxdP0J7SIxcBElpiboF+J1jKPwM8vaBxECpOtsmIsh25UP2a1X4NJ8x+iPSAavjNuYtK0n1AQrbGddUk0Yu5b36hSCTqcPR5lNmJgvNfbOKgBOPCdjLqWfw79fiI9f549vFebP8Plg4it55mV53dCO6sCQHPi6ywjQGkLgs9vFlZ4SKRniKDF8cmecmGv2MK+/wgha+6HgALW0Cf/QEwniEnG/SALEvu4mkDuBaInawEHAicW4TJ9M8EVMpXThNaD7BgiTR7zUaYYTLhb0Tn54KkVhvlVWmG3lybI5jaqia3h7eLz5++4awxLYxFSV4SfkPllhCi2DUnjVIYWpXI9i0Yq28vBUERBwsuwaJiUcwblf1jR3MZKeDjJ9jHBHTP2ppbaoCdQNAqAd6irzHctu1yuReek+NvJaEkb8ixWYjEJwq9FLOWPUwSYGT9B5VszEYRA3JaSdC+DkB0OMnV28dPBkRWmgehT1idTemGv/8JTZ7WCVUCGjT5wySpg==
*/