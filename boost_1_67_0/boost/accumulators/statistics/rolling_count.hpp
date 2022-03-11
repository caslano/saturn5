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