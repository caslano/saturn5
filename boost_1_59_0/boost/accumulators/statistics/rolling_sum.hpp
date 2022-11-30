///////////////////////////////////////////////////////////////////////////////
// rolling_sum.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_SUM_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_SUM_HPP_EAN_26_12_2008

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
    // rolling_sum_impl
    //    returns the sum of the samples in the rolling window
    template<typename Sample>
    struct rolling_sum_impl
      : accumulator_base
    {
        typedef Sample result_type;

        template<typename Args>
        rolling_sum_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {}

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= rolling_window_plus1(args).front();
            }
            this->sum_ += args[sample];
        }

        template<typename Args>
        result_type result(Args const & /*args*/) const
        {
            return this->sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum_;
        }

    private:
        Sample sum_;
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_sum
//
namespace tag
{
    struct rolling_sum
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_sum_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_sum
//
namespace extract
{
    extractor<tag::rolling_sum> const rolling_sum = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_sum)
}

using extract::rolling_sum;
}} // namespace boost::accumulators

#endif

/* rolling_sum.hpp
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
*/