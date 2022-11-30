///////////////////////////////////////////////////////////////////////////////
// sum.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_SUM_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_SUM_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // sum_impl
    template<typename Sample, typename Tag>
    struct sum_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        sum_impl(Args const &args)
          : sum(args[parameter::keyword<Tag>::get() | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->sum += args[parameter::keyword<Tag>::get()];
        }

        result_type result(dont_care) const
        {
            return this->sum;
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
        }

    private:
        Sample sum;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::sum
// tag::sum_of_weights
// tag::sum_of_variates
//
namespace tag
{
    struct sum
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::sum_impl<mpl::_1, tag::sample> impl;
    };

    struct sum_of_weights
      : depends_on<>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::sum_impl<mpl::_2, tag::weight> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct sum_of_variates
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::sum_impl<VariateType, VariateTag> > impl;
    };

    struct abstract_sum_of_variates
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::sum
// extract::sum_of_weights
// extract::sum_of_variates
//
namespace extract
{
    extractor<tag::sum> const sum = {};
    extractor<tag::sum_of_weights> const sum_of_weights = {};
    extractor<tag::abstract_sum_of_variates> const sum_of_variates = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_weights)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_variates)
}

using extract::sum;
using extract::sum_of_weights;
using extract::sum_of_variates;

// So that mean can be automatically substituted with
// weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::sum>
{
    typedef tag::weighted_sum type;
};

template<>
struct feature_of<tag::weighted_sum>
  : feature_of<tag::sum>
{};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::sum_of_variates<VariateType, VariateTag> >
  : feature_of<tag::abstract_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* sum.hpp
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
*/