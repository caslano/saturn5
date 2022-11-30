///////////////////////////////////////////////////////////////////////////////
// sum_kahan.hpp
//
//  Copyright 2010 Gaetano Mendola, 2011 Simon West. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_SUM_KAHAN_HPP_EAN_26_07_2010
#define BOOST_ACCUMULATORS_STATISTICS_SUM_KAHAN_HPP_EAN_26_07_2010

#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/weighted_sum_kahan.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

#if _MSC_VER > 1400
# pragma float_control(push)
# pragma float_control(precise, on)
#endif

template<typename Sample, typename Tag>
struct sum_kahan_impl
  : accumulator_base
{
    typedef Sample result_type;

    ////////////////////////////////////////////////////////////////////////////
    // sum_kahan_impl
    /**
        @brief Kahan summation algorithm

        The Kahan summation algorithm reduces the numerical error obtained with standard
        sequential sum.

    */
    template<typename Args>
    sum_kahan_impl(Args const & args)
      : sum(args[parameter::keyword<Tag>::get() | Sample()]),
        compensation(boost::numeric_cast<Sample>(0.0))
    {
    }

    template<typename Args>
    void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
    __attribute__((__optimize__("no-associative-math")))
#endif
    operator ()(Args const & args)
    {
        const Sample myTmp1 = args[parameter::keyword<Tag>::get()] - this->compensation;
        const Sample myTmp2 = this->sum + myTmp1;
        this->compensation = (myTmp2 - this->sum) - myTmp1;
        this->sum = myTmp2;
    }

    result_type result(dont_care) const
    {
      return this->sum;
    }

    // make this accumulator serializeable
    template<class Archive>
    void serialize(Archive & ar, const unsigned int file_version)
    { 
        ar & sum;
        ar & compensation;
    }

private:
    Sample sum;
    Sample compensation;
};

#if _MSC_VER > 1400
# pragma float_control(pop)
#endif

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::sum_kahan
// tag::sum_of_weights_kahan
// tag::sum_of_variates_kahan
//
namespace tag
{

    struct sum_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef impl::sum_kahan_impl< mpl::_1, tag::sample > impl;
    };

    struct sum_of_weights_kahan
      : depends_on<>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::sum_kahan_impl<mpl::_2, tag::weight> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct sum_of_variates_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::sum_kahan_impl<VariateType, VariateTag> > impl;
    };

} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::sum_kahan
// extract::sum_of_weights_kahan
// extract::sum_of_variates_kahan
//
namespace extract
{
    extractor<tag::sum_kahan> const sum_kahan = {};
    extractor<tag::sum_of_weights_kahan> const sum_of_weights_kahan = {};
    extractor<tag::abstract_sum_of_variates> const sum_of_variates_kahan = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_kahan)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_weights_kahan)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(sum_of_variates_kahan)
} // namespace extract

using extract::sum_kahan;
using extract::sum_of_weights_kahan;
using extract::sum_of_variates_kahan;

// sum(kahan) -> sum_kahan
template<>
struct as_feature<tag::sum(kahan)>
{
    typedef tag::sum_kahan type;
};

// sum_of_weights(kahan) -> sum_of_weights_kahan
template<>
struct as_feature<tag::sum_of_weights(kahan)>
{
    typedef tag::sum_of_weights_kahan type;
};

// So that sum_kahan can be automatically substituted with
// weighted_sum_kahan when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::sum_kahan>
{
    typedef tag::weighted_sum_kahan type;
};

template<>
struct feature_of<tag::weighted_sum_kahan>
  : feature_of<tag::sum>
{};

// for the purposes of feature-based dependency resolution,
// sum_kahan provides the same feature as sum
template<>
struct feature_of<tag::sum_kahan>
  : feature_of<tag::sum>
{
};

// for the purposes of feature-based dependency resolution,
// sum_of_weights_kahan provides the same feature as sum_of_weights
template<>
struct feature_of<tag::sum_of_weights_kahan>
  : feature_of<tag::sum_of_weights>
{
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::sum_of_variates_kahan<VariateType, VariateTag> >
  : feature_of<tag::abstract_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif


/* sum_kahan.hpp
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
*/