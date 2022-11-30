///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_HPP_EAN_29_11_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    /// INTERNAL ONLY
    ///
    template<typename Feature>
    struct this_feature_has_no_error_calculation
      : mpl::false_
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // error_of_impl
    /// INTERNAL ONLY
    ///
    template<typename Sample, typename Feature>
    struct error_of_impl
      : accumulator_base
    {
        // TODO: specialize this on the specific features that have errors we're
        // interested in.
        BOOST_MPL_ASSERT((this_feature_has_no_error_calculation<Feature>));

        // for boost::result_of
        typedef int result_type;

        error_of_impl(dont_care)
        {
        }

        result_type result(dont_care) const
        {
            return 0;
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<typename Feature>
    struct error_of
      : depends_on<Feature>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_impl<mpl::_1, Feature> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::error_of
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, error_of, (typename))
}

using extract::error_of;

// make tag::error_of<tag::feature(modifier)> work
template<typename Feature>
struct as_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_feature<Feature>::type> type;
};

// make error_of<tag::mean> work with non-void weights (should become
// error_of<tag::weighted_mean>
template<typename Feature>
struct as_weighted_feature<tag::error_of<Feature> >
{
    typedef tag::error_of<typename as_weighted_feature<Feature>::type> type;
};

}} // namespace boost::accumulators

#endif

/* error_of.hpp
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
*/