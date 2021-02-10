///////////////////////////////////////////////////////////////////////////////
// min.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // min_impl
    template<typename Sample>
    struct min_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        min_impl(Args const &args)
          : min_(numeric::as_max(args[sample | Sample()]))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::min_assign(this->min_, args[sample]);
        }

        result_type result(dont_care) const
        {
            return this->min_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & min_;
        }

    private:
        Sample min_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::min
//
namespace tag
{
    struct min
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::min_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::min
//
namespace extract
{
    extractor<tag::min> const min = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(min)
}

using extract::min;

}} // namespace boost::accumulators

#endif

/* min.hpp
TXBZ8ZLrAKcLnnCQhRz5XAK2C5N9BOJ4xgDFx3RWAURYmoGMzkkm8MvVnKqTZLGxNl2gAjzwspAgy2gdji4v4V+YHo5WIQ+ZOgs8x8tJiC2CXuXGhnpTvRA61fsYQdXQUK729sDrxcBFyCAaBJv6EjSvR7Q4PG60TjvHj7lGziPHS6yrpBvjqMASHE28q+hTOOeMaA1/pC/HxMPnYLbAM4PrGPZ/0oKp5+zO4MMPqBvPWkhcTlAuYlhG8Bc69glmPLHpxAK5ZSK434veIg2IRx8N9+MU9KFHYsXGdgZmvbc0LtgYYopNQokcszFowWm4xKO5A9ecx7kh6iUztT8cNUedY5g2rllCNfhcvY9s5icItTjfJqlhELPIX6Y+eZ+iJMIkFIZVulileKrGfTTX1rTp7b4YP+qFuRfOFumtTmg1n6I1ZPu95u6hI2U1qdJByl5RQAyk1vzy2DRIFIwSdDsuSyEe4aBiDHJDB4Co3ymzjyaiM1C20IjDixAeA5GkIVbD1Um16N2OQDPcJWR8eYeIxmsEmIoFAOlMfagEdTHOMI/rNWWWGbT/dtaBNRfX4Fb7dHg0j2vKoJdLBNpGg+0MuVUeRbf97rTbOe6MVK59Zv/zjl0c2MNh2NN33YiWzmX4GO1gN8Etzmxa
*/