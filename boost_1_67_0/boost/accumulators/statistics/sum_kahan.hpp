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