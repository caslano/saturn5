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
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
*/