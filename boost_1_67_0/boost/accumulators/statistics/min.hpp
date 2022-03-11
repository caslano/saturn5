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