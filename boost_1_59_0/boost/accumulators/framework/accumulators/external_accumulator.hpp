///////////////////////////////////////////////////////////////////////////////
// external_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_EXTERNAL_ACCUMULATOR_HPP_EAN_01_12_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_EXTERNAL_ACCUMULATOR_HPP_EAN_01_12_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/accumulators/reference_accumulator.hpp>

namespace boost { namespace accumulators { namespace impl
{

    //////////////////////////////////////////////////////////////////////////
    // external_impl
    /// INTERNAL ONLY
    ///
    template<typename Accumulator, typename Tag>
    struct external_impl
      : accumulator_base
    {
        typedef typename Accumulator::result_type result_type;
        typedef typename detail::feature_tag<Accumulator>::type feature_tag;

        external_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->extract_(args, args[parameter::keyword<Tag>::instance | 0]);
        }

    private:

        template<typename Args>
        static result_type extract_(Args const &args, int)
        {
            // No named parameter passed to the extractor. Maybe the external
            // feature is held by reference<>.
            extractor<feature_tag> extract;
            return extract(accumulators::reference_tag<Tag>(args));
        }

        template<typename Args, typename AccumulatorSet>
        static result_type extract_(Args const &, AccumulatorSet const &acc)
        {
            // OK, a named parameter for this external feature was passed to the
            // extractor, so use that.
            extractor<feature_tag> extract;
            return extract(acc);
        }
    };

} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // external
    template<typename Feature, typename Tag, typename AccumulatorSet>
    struct external
      : depends_on<reference<AccumulatorSet, Tag> >
    {
        typedef
            accumulators::impl::external_impl<
                detail::to_accumulator<Feature, mpl::_1, mpl::_2>
              , Tag
            >
        impl;
    };

    template<typename Feature, typename Tag>
    struct external<Feature, Tag, void>
      : depends_on<>
    {
        typedef
            accumulators::impl::external_impl<
                detail::to_accumulator<Feature, mpl::_1, mpl::_2>
              , Tag
            >
        impl;
    };
}

// for the purposes of feature-based dependency resolution,
// external_accumulator<Feature, Tag> provides the same feature as Feature
template<typename Feature, typename Tag, typename AccumulatorSet>
struct feature_of<tag::external<Feature, Tag, AccumulatorSet> >
  : feature_of<Feature>
{
};

// Note: Usually, the extractor is pulled into the accumulators namespace with
// a using directive, not the tag. But the external<> feature doesn't have an
// extractor, so we can put the external tag in the accumulators namespace
// without fear of a name conflict.
using tag::external;

}} // namespace boost::accumulators

#endif

/* external_accumulator.hpp
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
*/