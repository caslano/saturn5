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
ZiqgZYecWSc5yykhpcpFOyTn+7LzOKSkQw3yYCHQSCSZRsu6Xd4fUatzK8bBbWTIRhbeHNeSldcfYPfLkI9Wm4jFslAdEA8jHpnLpVfQIVJB+aBIBb5c/eP59HGe/rUnMY8hrDO2+UdPZRke4ygtDxoeNkw1LKD/vdSklBGGP/VkDGMm9RAuIGzTiPePl/P3qd2nsdQc/6m3IK2FFJlmfcSr7C0J0b18A6Naebpibcf86BVl9FrparcuPRQCVjc7MmghgLNFRPFKuJU1WmFedIvGrA+bnQ1EqCKfTW5Q4qkBeqHYBjIfxjdOYKeaIxebrODKykurDbhyLEgVvCvYLMG7jOdsEY7Oh7M8M3OUmtlhzTMwRz6q7JzddrY/RgMDwd+F/vozz2qe27MUXJjo5O4j03C56lZmDo04crpN7zj3sqsuF5SPOpoEsUs2BD+IMVulXANJ8Vsgwvdqoe90ThwQnbI7R8pskc+hPYHKw7lMIDabRaRsTi7HUo/noMezlf0zWAfUeVbZBX16X3zKblyyWiWrgitEuQExm33N0NcK/EzdVDbPwP1NqtXXQfkDvs08K7E/xbt5BVro+JmInVrN205ZQEXUv0xj3d72UqJJWsQvKMsF3cqv92GFJ9nk5saKVURfTzcZGiuIdr2BElkpxxorjIJ4O6WJl/PXnfLXmoiVk2ZZXod7dN/NyktPwcNkoqOBuHgqpTzF
*/