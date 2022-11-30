///////////////////////////////////////////////////////////////////////////////
// weighted_mean.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEAN_HPP_EAN_03_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEAN_HPP_EAN_03_11_2005

#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/weights.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_mean_impl
    //      lazy, by default
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        weighted_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Tag, tag::sample>
                  , tag::weighted_sum
                  , tag::weighted_sum_of_variates<Sample, Tag>
                >::type
            weighted_sum_tag;

            extractor<weighted_sum_tag> const some_weighted_sum = {};

            return numeric::fdiv(some_weighted_sum(args), sum_of_weights(args));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // immediate_weighted_mean_impl
    //      immediate
    template<typename Sample, typename Weight, typename Tag>
    struct immediate_weighted_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        immediate_weighted_mean_impl(Args const &args)
          : mean(
                numeric::fdiv(
                    args[parameter::keyword<Tag>::get() | Sample()]
                      * numeric::one<Weight>::value
                  , numeric::one<Weight>::value
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // Matthias:
            //  need to pass the argument pack since the weight might be an external
            //  accumulator set passed as a named parameter
            Weight w_sum = sum_of_weights(args);
            Weight w = args[weight];
            weighted_sample const &s = args[parameter::keyword<Tag>::get()] * w;
            this->mean = numeric::fdiv(this->mean * (w_sum - w) + s, w_sum);
        }

        result_type result(dont_care) const
        {
            return this->mean;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & mean;
        }

    private:
        result_type mean;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_mean
// tag::immediate_weighted_mean
//
namespace tag
{
    struct weighted_mean
      : depends_on<sum_of_weights, weighted_sum>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_mean_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };
    struct immediate_weighted_mean
      : depends_on<sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_weighted_mean_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct weighted_mean_of_variates
      : depends_on<sum_of_weights, weighted_sum_of_variates<VariateType, VariateTag> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_mean_impl<VariateType, mpl::_2, VariateTag> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct immediate_weighted_mean_of_variates
      : depends_on<sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_weighted_mean_impl<VariateType, mpl::_2, VariateTag> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_mean
// extract::weighted_mean_of_variates
//
namespace extract
{
    extractor<tag::mean> const weighted_mean = {};
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, weighted_mean_of_variates, (typename)(typename))

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_mean)
}

using extract::weighted_mean;
using extract::weighted_mean_of_variates;

// weighted_mean(lazy) -> weighted_mean
template<>
struct as_feature<tag::weighted_mean(lazy)>
{
    typedef tag::weighted_mean type;
};

// weighted_mean(immediate) -> immediate_weighted_mean
template<>
struct as_feature<tag::weighted_mean(immediate)>
{
    typedef tag::immediate_weighted_mean type;
};

// weighted_mean_of_variates<VariateType, VariateTag>(lazy) -> weighted_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_mean_of_variates<VariateType, VariateTag>(lazy)>
{
    typedef tag::weighted_mean_of_variates<VariateType, VariateTag> type;
};

// weighted_mean_of_variates<VariateType, VariateTag>(immediate) -> immediate_weighted_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_mean_of_variates<VariateType, VariateTag>(immediate)>
{
    typedef tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> type;
};

}} // namespace boost::accumulators

#endif

/* weighted_mean.hpp
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
*/