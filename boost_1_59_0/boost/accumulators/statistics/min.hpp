///////////////////////////////////////////////////////////////////////////////
// min.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MIN_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // min_impl
    template<typename Sample>
    struct min_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        min_impl(Args const &args)
          : min_(numeric::as_max(args[sample | Sample()]))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::min_assign(this->min_, args[sample]);
        }

        result_type result(dont_care) const
        {
            return this->min_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & min_;
        }

    private:
        Sample min_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::min
//
namespace tag
{
    struct min
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::min_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::min
//
namespace extract
{
    extractor<tag::min> const min = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(min)
}

using extract::min;

}} // namespace boost::accumulators

#endif

/* min.hpp
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
*/