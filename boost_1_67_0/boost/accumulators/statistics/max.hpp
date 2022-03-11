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