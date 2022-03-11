///////////////////////////////////////////////////////////////////////////////
// tail_variate.hpp
//
//  Copyright 2005 Eric Niebler, Michael Gauckler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005
#define BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005

#include <boost/range.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_impl
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef
            typename detail::tail_range<
                typename std::vector<VariateType>::const_iterator
              , std::vector<std::size_t>::iterator
            >::type
        result_type;

        template<typename Args>
        tail_variate_impl(Args const &args)
          : variates(args[tag::tail<LeftRight>::cache_size], args[parameter::keyword<VariateTag>::get() | VariateType()])
        {
        }

        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            this->variates[index] = args[parameter::keyword<VariateTag>::get()];
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            // getting the order result causes the indices vector to be sorted.
            extractor<tag::tail<LeftRight> > const some_tail = {};
            return this->do_result(some_tail(args));
        }

    private:
        template<typename TailRng>
        result_type do_result(TailRng const &rng) const
        {
            return detail::make_tail_range(
                this->variates.begin()
              , rng.end().base().base()   // the index iterator
              , rng.begin().base().base() // (begin and end reversed because these are reverse iterators)
            );
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variates;
        }

    private:
        std::vector<VariateType> variates;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::tail_variate<>
//
namespace tag
{
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::tail_variate_impl<VariateType, VariateTag, LeftRight> > impl;
    };

    struct abstract_tail_variate
      : depends_on<>
    {
    };

    template<typename LeftRight>
    struct tail_weights
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_variate_impl<mpl::_2, tag::weight, LeftRight> impl;
    };

    struct abstract_tail_weights
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate
// extract::tail_weights
//
namespace extract
{
    extractor<tag::abstract_tail_variate> const tail_variate = {};
    extractor<tag::abstract_tail_weights> const tail_weights = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_weights)
}

using extract::tail_variate;
using extract::tail_weights;

template<typename VariateType, typename VariateTag, typename LeftRight>
struct feature_of<tag::tail_variate<VariateType, VariateTag, LeftRight> >
  : feature_of<tag::abstract_tail_variate>
{
};

template<typename LeftRight>
struct feature_of<tag::tail_weights<LeftRight> >
{
    typedef tag::abstract_tail_weights type;
};

}} // namespace boost::accumulators

#endif

/* tail_variate.hpp
+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
*/