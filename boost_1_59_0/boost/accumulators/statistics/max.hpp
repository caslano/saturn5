///////////////////////////////////////////////////////////////////////////////
// max.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MAX_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MAX_HPP_EAN_28_10_2005

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
    // max_impl
    template<typename Sample>
    struct max_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        max_impl(Args const &args)
          : max_(numeric::as_min(args[sample | Sample()]))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::max_assign(this->max_, args[sample]);
        }

        result_type result(dont_care) const
        {
            return this->max_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & max_;
        }

    private:
        Sample max_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::max
//
namespace tag
{
    struct max
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::max_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::max
//
namespace extract
{
    extractor<tag::max> const max = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(max)
}

using extract::max;

}} // namespace boost::accumulators

#endif

/* max.hpp
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
*/