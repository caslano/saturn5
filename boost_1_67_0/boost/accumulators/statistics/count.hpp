///////////////////////////////////////////////////////////////////////////////
// count.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_COUNT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_COUNT_HPP_EAN_28_10_2005

#include <boost/mpl/always.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // count_impl
    struct count_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef std::size_t result_type;

        count_impl(dont_care)
          : cnt(0)
        {
        }

        void operator ()(dont_care)
        {
            ++this->cnt;
        }

        result_type result(dont_care) const
        {
            return this->cnt;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cnt;
        }

    private:
        std::size_t cnt;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::count
//
namespace tag
{
    struct count
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::count_impl> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::count
//
namespace extract
{
    extractor<tag::count> const count = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(count)
}

using extract::count;

}} // namespace boost::accumulators

#endif

/* count.hpp
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
*/