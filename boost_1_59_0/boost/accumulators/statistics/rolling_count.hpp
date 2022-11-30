///////////////////////////////////////////////////////////////////////////////
// rolling_count.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // rolling_count_impl
    //    returns the count of elements in the rolling window
    template<typename Sample>
    struct rolling_count_impl
      : accumulator_base
    {
        typedef std::size_t result_type;

        rolling_count_impl(dont_care)
        {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return static_cast<std::size_t>(rolling_window_plus1(args).size()) - is_rolling_window_plus1_full(args);
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_count
//
namespace tag
{
    struct rolling_count
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_count_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_count
//
namespace extract
{
    extractor<tag::rolling_count> const rolling_count = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_count)
}

using extract::rolling_count;

}} // namespace boost::accumulators

#endif

/* rolling_count.hpp
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
*/