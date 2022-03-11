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