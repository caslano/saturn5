///////////////////////////////////////////////////////////////////////////////
// mean.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // mean_impl
    //      lazy, by default
    template<typename Sample, typename SumFeature>
    struct mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<SumFeature> sum;
            return numeric::fdiv(sum(args), count(args));
        }

        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    template<typename Sample, typename Tag>
    struct immediate_mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        immediate_mean_impl(Args const &args)
          : mean(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            this->mean = numeric::fdiv(
                (this->mean * (cnt - 1)) + args[parameter::keyword<Tag>::get()]
              , cnt
            );
        }

        result_type result(dont_care) const
        {
            return this->mean;
        }

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
// tag::mean
// tag::immediate_mean
// tag::mean_of_weights
// tag::immediate_mean_of_weights
// tag::mean_of_variates
// tag::immediate_mean_of_variates
//
namespace tag
{
    struct mean
      : depends_on<count, sum>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::mean_impl<mpl::_1, sum> impl;
    };
    struct immediate_mean
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_mean_impl<mpl::_1, tag::sample> impl;
    };
    struct mean_of_weights
      : depends_on<count, sum_of_weights>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::mean_impl<mpl::_2, sum_of_weights> impl;
    };
    struct immediate_mean_of_weights
      : depends_on<count>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_mean_impl<mpl::_2, tag::weight> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct mean_of_variates
      : depends_on<count, sum_of_variates<VariateType, VariateTag> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::mean_impl<VariateType, sum_of_variates<VariateType, VariateTag> > > impl;
    };
    template<typename VariateType, typename VariateTag>
    struct immediate_mean_of_variates
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::immediate_mean_impl<VariateType, VariateTag> > impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::mean
// extract::mean_of_weights
// extract::mean_of_variates
//
namespace extract
{
    extractor<tag::mean> const mean = {};
    extractor<tag::mean_of_weights> const mean_of_weights = {};
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, mean_of_variates, (typename)(typename))

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(mean)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(mean_of_weights)
}

using extract::mean;
using extract::mean_of_weights;
using extract::mean_of_variates;

// mean(lazy) -> mean
template<>
struct as_feature<tag::mean(lazy)>
{
    typedef tag::mean type;
};

// mean(immediate) -> immediate_mean
template<>
struct as_feature<tag::mean(immediate)>
{
    typedef tag::immediate_mean type;
};

// mean_of_weights(lazy) -> mean_of_weights
template<>
struct as_feature<tag::mean_of_weights(lazy)>
{
    typedef tag::mean_of_weights type;
};

// mean_of_weights(immediate) -> immediate_mean_of_weights
template<>
struct as_feature<tag::mean_of_weights(immediate)>
{
    typedef tag::immediate_mean_of_weights type;
};

// mean_of_variates<VariateType, VariateTag>(lazy) -> mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::mean_of_variates<VariateType, VariateTag>(lazy)>
{
    typedef tag::mean_of_variates<VariateType, VariateTag> type;
};

// mean_of_variates<VariateType, VariateTag>(immediate) -> immediate_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::mean_of_variates<VariateType, VariateTag>(immediate)>
{
    typedef tag::immediate_mean_of_variates<VariateType, VariateTag> type;
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<>
struct feature_of<tag::immediate_mean>
  : feature_of<tag::mean>
{
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<>
struct feature_of<tag::immediate_mean_of_weights>
  : feature_of<tag::mean_of_weights>
{
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<typename VariateType, typename VariateTag>
struct feature_of<tag::immediate_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::mean_of_variates<VariateType, VariateTag> >
{
};

// So that mean can be automatically substituted with
// weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::mean>
{
    typedef tag::weighted_mean type;
};

template<>
struct feature_of<tag::weighted_mean>
  : feature_of<tag::mean>
{};

// So that immediate_mean can be automatically substituted with
// immediate_weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::immediate_mean>
{
    typedef tag::immediate_weighted_mean type;
};

template<>
struct feature_of<tag::immediate_weighted_mean>
  : feature_of<tag::immediate_mean>
{};

// So that mean_of_weights<> can be automatically substituted with
// weighted_mean_of_variates<> when the weight parameter is non-void.
template<typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::mean_of_variates<VariateType, VariateTag> >
{
    typedef tag::weighted_mean_of_variates<VariateType, VariateTag> type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::mean_of_variates<VariateType, VariateTag> >
{
};

// So that immediate_mean_of_weights<> can be automatically substituted with
// immediate_weighted_mean_of_variates<> when the weight parameter is non-void.
template<typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::immediate_mean_of_variates<VariateType, VariateTag> >
{
    typedef tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::immediate_mean_of_variates<VariateType, VariateTag> >
{
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<mean_impl>
////  need to specialize droppable lazy mean to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename SumFeature>
//struct droppable_accumulator<impl::mean_impl<Sample, SumFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::mean_impl<Sample, SumFeature> >
//    >
//{
//    template<typename Args>
//    droppable_accumulator(Args const &args)
//      : droppable_accumulator::base(args)
//    {
//    }
//};

}} // namespace boost::accumulators

#endif

/* mean.hpp
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
*/