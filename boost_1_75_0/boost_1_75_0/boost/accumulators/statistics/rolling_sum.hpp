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
ZoMrS2kYHbnuDXSkjArN5Ar22t7OkY46ehuoLTV3mx7kQrvzyYej3iPht6AhUha5rBcfNSEd1pnQkNldaPkLgefg1W2Y5FQnmJn6q2P1YtdSsQL/yBGC+HkntkqFtkCzJ6bQ9hd42f77/dEPA9fRyQVXZ5z/zMX8a5AfVziA859oyxdXc32dV+6FWaja51PQwQ8YHtD9mBumGTIMtxmGtksPMtxlmMien5E3yTDBMMYw2TCWc0agDm/HEYY0Ix3KH56Gav2NOGJHGPmYNhEAqvsoW8qvb6xME8RWePhzNn9A35b3rcA9U5oQWNSJazIQ6/M6lfWYwWRoQ5St/wi37QxHJ4hR6j2m6Y5Kb1d/s1kQuxGcrzx36qNPCI7/l76DoaeBcsJsurcLOee0MLpRT+msrKlUZdPPYa1vJaFNrvQHG2Lhhk1qAXWraYxNp8t/8JgMpXxjxJc6X9Nj0n712h9wTaPG0x92XqhWpFOPqtTd1Zrm+EYQv6/R9Fjb6jeUUky0G9X594IJV4/BP83SXtrnmP7KnrQzdtjMtLrLTWOIokyApd1yC1H1sFNXt9KzlqJsoJMhz9Hs7Ruy57jp2RqILKD3O10FwF9lW3lh1w6jffkJeSvu+wlGCifuNNJij4JYZucdrBI2nHGqJI7VFasCS6hlXZEnZsX9Lrful5Ndd7qUZYVtLthX2KB+gY/M5SNiQYj559pwNV8g
*/