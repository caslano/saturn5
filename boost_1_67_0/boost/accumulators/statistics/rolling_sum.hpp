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