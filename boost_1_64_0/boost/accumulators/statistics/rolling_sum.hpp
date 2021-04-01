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
yjHBs1odPGBVnHXHX0KcbJmmBh4Yplrv4HVvZYaHbpUAJhZDyHgR5/S8r1itLTfw23gaG89li9fLQQf2+jKgJ7XbSWV4FgNkFW0b6b3zORIdhBk0fMV7r+61ez4rRyE3mCkIURD+wPWiz4UXesF/Oz97SivaFeF75ixYQlVS6vpRE4nzE/2IazuBUxEdDNIUgKpyDCod8Nf9GlH6FCGVfbxeBXN+WgaftGuy9K5uDUEOTMDZ66CWa+9kSz4EB8BeTBOcqPokGpdpJ4eiyMQRXfjUQD6HYAEw9/aKpZsdGPPtpubEN/9FUalgdnHtrtK20KU9bdVKkN+mKq2uBmQIL04IjUeLlaM0WlV5E62LKzlBeSfArHomIpK6zVdeV6yrmcTP3w3+bfy38zeS0rwnPJcUpk7duIJotu1vIoY5bu6Xao0URbQXY5q7Rs/PpImH0Erm7YHsmsHk1laoIc5cfLfrONv6YQvyHKpngPVmbHCUXCDs210os2krE9CKqJ7aRizr2+5kj9AEyRdnnkUAZQ9QWNQX9yg2UYAzDpoT2wjLp5Orc2lNPQbItQ==
*/