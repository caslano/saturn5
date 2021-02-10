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
oX/tZOxglmwOS1nJ5rOhoKge2BcbR4s3K/xnRm9Y7zk0sqEod8hbm9TNcu97qQeBjDmuHQuJbnnmQkScpjCRXNtLT3tkGXHEYwB/x7KK0do42KpnAEctj6nemYcDgiV23eKnzSfREnbdmJ+jwJ0rewuRX+dQgf8ZG5t2KKt6u3ZDxDOpsuI6sNk3ZIQnZ6MK/5xoIJcwlrAGiNc38NWRBlmhNWpy849D0pyFzTC9Xsarq2uamnT6jz7wk4l4qJLfgOm8GjQH72mD1QnSHYfwE261KlSpUjA41izG8MWgzSJsMPnbSxJrY0vnHIXk3qMzJKOV69++1bs1Kxt+pus9hW3KwePmZAIdohFzdkku6A79owJriPVa4h3sMGAC934CZ4j1racDlSqlb/+WBmbs/5qWpfZ+E5tvCZqaQBk1hSSdbB37VseukgMyRA1HrRxOxdQylIrpxRhVkHeCVJH2e0CpyIeOUQVrGUilrimGqJhcBaBSex8enjI7heCUuNgUmtI7k3dBpdR1pZgUSWtwtLRA1y6A+72jRA6F6mWqAFA9Py5fXIdCnviniTs3hJ00CFsHnUTVhpwsvFIwvgDcJPmzwCYxgdYZ4FChTPqoYUz8240wOWfHymmjS25pGbUyZElsl+FKmUFDlSQH
*/