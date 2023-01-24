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
aJiNNgI/g30P2jlvItjMoI3TY8Mgq4mDrr82wrtMpvpL4zw35g2rEMRHa02GoZMJQmdRQt46E6qSu6XgcPpbEhzCNYzn37QwO/IKDuA3M/h3Ov8+zr8e/n2CfsuMUjARPf0yQ9hGvNa0aA92017HGY6MPGL/YyHTmiSs67wDlj6FQqCaE/OFwLOcWCoEXqBEuKqU2ygVUXvgmHdLyc556M3mOTwP6LOsz8lOL0oQ+XA9Ij8F+3HPOQJxF3+FRdIzNqJ9eSM+G7y7JLiMJ9DXo9Q0PEsI/EJcZTU3pA0fIwS+YyZzmP+zRL/2iHeCX3tACNyBzmlPCIEkLNRWxHAMilgMl/JXuHfnhcnTV4mwIPcyz38BTB7EgdywLPJ8BtFfrMkEaqd4J0Zp8F3LrYQ+QiuLqQsfRZr7khMLhHU9d0CTwa8sFAKTYgx65PK+5SbD+PGC+D8VVAh4adUuJAgvFVOiVMQo/TuxLIQV3qQswAw7AhOx1sU7p+uvbq+mz05lNJ24Vuu7EyvvnR/t10BNHMpdH96+rg70QWlwHs+7HOS1DhwiYloyljK8yjsvrk+4fJwOxBJn8pzkUdnSOJgduVtRbTK9IHA01vDVD0wir0OEkJ12Pf88FHQZ6OWK4p2QMRi8RBpYUB004aLWQnNKwIP4tWWRYPXaQj1YvbCtyqWkrdM9cGZhOgPnEaiCBzWvvIMmYtD+8gPmKv9O
*/