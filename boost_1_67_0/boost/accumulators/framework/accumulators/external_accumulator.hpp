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