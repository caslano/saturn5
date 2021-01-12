///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // error_of_mean_impl
    template<typename Sample, typename Variance>
    struct error_of_mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        error_of_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            using namespace std;
            extractor<Variance> const variance = {};
            return sqrt(numeric::fdiv(variance(args), count(args) - 1));
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<>
    struct error_of<mean>
      : depends_on<lazy_variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, lazy_variance> impl;
    };

    template<>
    struct error_of<immediate_mean>
      : depends_on<variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, variance> impl;
    };
}

}} // namespace boost::accumulators

#endif

/* error_of_mean.hpp
uuZmqFUzmmoL9KlKk6/hs5ID083mTrOZzXVtRQR6Btn0ncwY4wQhv59BRpCdhcqTzNbl77BqMfdPVbbaNuvL3A7qkIPe+K+zq7GPtaGpxX5FQDvePqXZLHu4Sc7w9xApglvXrW6ubKllRu3L/Ma7g0+ymMBNeq3Ydz8pKJSjXnGz6YWKkFawaRx6AoKJbTn0thbE8Vfv0Cqn68l3+1DB9HFN3yaCYUlwhYrqoUS50PXQrgX6
*/