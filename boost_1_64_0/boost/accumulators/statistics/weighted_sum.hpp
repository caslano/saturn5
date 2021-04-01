///////////////////////////////////////////////////////////////////////////////
// weighted_sum.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()]
                  * numeric::one<Weight>::value
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->weighted_sum_ += args[parameter::keyword<Tag>::get()] * args[weight];
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
        }

    private:

        weighted_sample weighted_sum_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum
//
namespace tag
{
    struct weighted_sum
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<VariateType, mpl::_2, VariateTag> impl;
    };

    struct abstract_weighted_sum_of_variates
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum
//
namespace extract
{
    extractor<tag::weighted_sum> const weighted_sum = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates)
}

using extract::weighted_sum;
using extract::weighted_sum_of_variates;

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum.hpp
4vx5AxDi65R2f+UDVuO8sN05S/qp7FBiSUdbPeqyHkaN00C3USIXtZrxviKTRaRnWM2rPqNZWZQ1aMs17o+llS3tnJOWatAfS/7QtkInCfEWIqOD/t2ApyKM2JLUrrdZ/v8Nw1NdEtH/k8Kenecq/HHe//is7g6Axyc3U338obc0GU/aSDPVlQSx4F0cZlVkna251KPtnuMtBQBvLOYLEbT2O2kKbI1dsOyThI6fZUGTX8MIsgy9nnoJD0yBwGxblJUV+y9g59Vn+pbn4k7KMDh7KD4ervat6/n/2qtJrNJGKmI9BCRB2jFAkFbXVAq8x6HWuD9eW/BOrnm0/fNuwriDikL36SdLhbkbnAn9lwniqv/ZQcCdXHZH7El/a0wTnA+WnqPf42u/R1FLcd32uW0PaQ/4I73Y4HqInYKjlha67fZsnNd708amPsjRXfuiEeSFHSKiotkvQ8z8ISGCjUZ+5ZfoYE/1Ua/mt2MSTOaqK3dtMZmAQBl+xt6exC1HHHUV2r2wx9av2jfTxMpAvzMXOzagNGpV9zbmzjZEUgPj/59RUmD9vQ5+sA==
*/