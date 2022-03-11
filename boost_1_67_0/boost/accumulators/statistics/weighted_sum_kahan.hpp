///////////////////////////////////////////////////////////////////////////////
// weighted_sum_kahan.hpp
//
//  Copyright 2011 Simon West. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
#if _MSC_VER > 1400
# pragma float_control(push)
# pragma float_control(precise, on)
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_kahan_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_kahan_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_kahan_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()] * numeric::one<Weight>::value),
                compensation(boost::numeric_cast<weighted_sample>(0.0))
        {
        }

        template<typename Args>
        void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
        __attribute__((__optimize__("no-associative-math")))
#endif
        operator ()(Args const &args)
        {
            const weighted_sample myTmp1 = args[parameter::keyword<Tag>::get()] * args[weight] - this->compensation;
            const weighted_sample myTmp2 = this->weighted_sum_ + myTmp1;
            this->compensation = (myTmp2 - this->weighted_sum_) - myTmp1;
            this->weighted_sum_ = myTmp2;

        }

        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_sum_;
            ar & compensation;
        }

    private:
        weighted_sample weighted_sum_;
        weighted_sample compensation;
    };

#if _MSC_VER > 1400
# pragma float_control(pop)
#endif

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum_kahan
// tag::weighted_sum_of_variates_kahan
//
namespace tag
{
    struct weighted_sum_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<VariateType, mpl::_2, VariateTag> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum_kahan
// extract::weighted_sum_of_variates_kahan
//
namespace extract
{
    extractor<tag::weighted_sum_kahan> const weighted_sum_kahan = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates_kahan = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_kahan)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates_kahan)
}

using extract::weighted_sum_kahan;
using extract::weighted_sum_of_variates_kahan;

// weighted_sum(kahan) -> weighted_sum_kahan
template<>
struct as_feature<tag::weighted_sum(kahan)>
{
    typedef tag::weighted_sum_kahan type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates_kahan<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum_kahan.hpp
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
*/