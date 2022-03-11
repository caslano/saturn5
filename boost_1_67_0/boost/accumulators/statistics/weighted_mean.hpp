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
+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
*/