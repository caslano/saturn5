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
dJU8lamr19MY3ZeZvyf3Ug+CgtV6vgVkF5UkuoM9U72455RQq+JXHAxl4j5siPebEcdNcYK9+T0fI/t+Ob0/nJuYbmzC+zb8vhd7dk9VW+Qljc9ICpSV4UiH0fkkLoDGdWsktCMhygEe8XYLakWXzrXEvgfANXJBaN5yqrG0LBlPggSjGJF8huAmpXpOvYHl7heii8f2kiF6Gvyg7r/U61qX283rP2YbkeELDj/2no0YuvVwhvGZ6T6sJe3xw5eYdW4kVzxWwzUmI2pkBG2d1sa0J0kwOMxCm9H+PZZcHNSWPvIZ0gu4K1b6LnmTugKLPrhsp04+s7NY/4qP+bz58q2yqqJrcN+pz5NdGydm2VzIcrgqZoWxDTvYToTQiaiKh82bITxvV8y+UEhudDumGr7LG9YHrhAPSbXZDkxt3sjcFC/244V6HmybboyxwfLL/ksOzleU/7cIr9kkZ6aMAhsGvquAhn/YkAjVJvfXoSKeBGnWS8370gFyGVsjtN6/fh9eZBd5jJwpoNdBCYEZlEOx7U0Ri9pOOTyZOtaCw41G/F5gbPdrxJ++QZjKIT1OsW2vGECgDDccvBAXKuY0Med4VoE+lblqTWkpDX1jP+wipb0TuL1TuL24KCPKAzXfC63gxtOl1CnNdaPX+dftQ3j2Oo8xZgYafV9CYIqp0Ri9OEOJHyfsgbekWsQm+zwv7mhG0zMC1YurU7TSeDwak2asIBVxdWBqRkVMrXg1gqnO31TCVLHPQJ24ruXRlXqOLPu09J/Yq7dZIijcfFCfkIE5rM/4yWd8qfLfr4zWBsmfCr0OiM6v/cOYzfLRtZDlMZv8KeP292bcBi56MxO2qK3B78rjNQF4LX6F8GpLcgcuLa1DDxqt7kAN4rNXm5F7gUZu9isR5O4hHWngor2BpyhK6ZVew7aXL05B1rHb4qjLqDvrBy4praufaxpw/E4dV4fv1XTTnfloR4VW/vJt5dPIw9ds0sJc/VZ1mQ+9TDfV7Nl+MOwf5QXAJk9f4CbPIYQPv6g3sA9i1K63oUEMnLvBbV5NPJHfOMriGqgDz+oEit7/3hiuz1KpT33KrG+0Po0q1Af+DiL1Wbkxsji5Dfc8ifi19CXY+9rxrJ55JPwaduPGViTd2hyZO5AKKc5nj+QQ9ZBzpNbJHwY7x6rvsBEvbox2wQLylx6sqcr/74bofPC8g9vdhKp2z0em+eDC5lXPB/Wa03yAbCLzQY0FPB98lVRuPnhvTXg++BIv1Oytv+58oPWf68P99/c63I5bqawnt0X6r2dSRXrqkaT7D/LdopUNYlTvN6mi1ZohnLryUlonCDG0xJ+65CEabNVs8jrnMn/HCUgVk3MxG4SsU2+/eJAE0wS/KyanJvL5tBmOkH6NgnY3o6psYdx8hmeU95c1KG/XG1ze/GbR8t5M4PIK8afeeJDLm90sUt6wNebybqhQ3pBweX+m8q6U8oZKeTVWo7yRUl6aqbzrpTwvlddJykvS5bXyd9y6isprlhdHFy/rUje9UL7UQ01R6j9Qko1KXQQuqi6IZwvrH5ty0cfxp46/zkWvaxoterXQ22b8qVUzueiX5XXO1f6Oa/AYk3MZ7HPLld61Qukjw6VPplLaoXQeImd49cG/5VPO/rs4fCbROKqGYoxXOPiNVmMB90ltNCZyBlLenG48bF8r0tEbKAGI09NaHk9regxgHqsgF8w1PHmp/OoM6//HteH6e9GAG1AWDJmkLLdrAhVW/maESkViunQbtxSkEkPoQOvp6zKMSevCM+TFmMZeeI5u1qlhrJTDNaa8EOo2phWwFBJnrDzLY9dV2IuT0JUYFrpmg2tFHIJo0evOtdTAreE=
*/