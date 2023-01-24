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
bQrEC8DmJnbVxMiGRHHiC4hIYb40TbbwvjiWAKyHOHE1Ydc49gjuIFESI/nP41c+D81gxlGwZiY+A9HWdutp6yGYWlrRKF4DCiEla7gf3i624DL1o8sf8Wadd76hxGh4wIhpbfS+plOG9Lbv+SdDzyNCl8Y/Dld/yBcvXYEhKQmpHemKBrg2LLPw2KT1SFOM34hUEPDoW7BXxuATpwr0WoIlqawVD5o9kIoyp0T8aO9Dkc5mPadcz/J3oGAcCKrW0TBJd1+JnJhcZwoC6E8oRdkCEL1Ey6FI2vQugb3u1oJeIFW9PKQqLcMTcd+h1m83bpr0vIOD28r+CSXFNmrMqnWAHdv0XCMw3aRmuREe6Jy7op6BkQtntxmRBeBybXuABieBmhvTyhmqkGOcKiNyKE6TtBz9UMoALMqA7L80snoXwRIor1S+xcxOJHIczpUyeT9rT4ZiDNxVXFmZG6p6oKxMWr4U5UpJG4GHlZYv06nAbwEUodYzWdmC7HWpR8fG/Bc+a6UqAJTQHC9XrnWqNdQYboJUBCha+vcGYE7Hi6GrPMYwixuILxj0Smx9hT/Vl8Ish6XDbn4HiRZB2zuAQdj0OxiEvCtwEOh8MhDOjMeNmzqTAz4GjxVCLBBAbQXdJAXTjYEoPr2V909vhTXB3kOxCBt3BRHXKqNLbogRBvgEWJrOIDBUa8h6NLCQGVCG+CLq1KKmeU8bIWEq
*/