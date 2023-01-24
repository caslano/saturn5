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
ztEfNZ7r5vFLXgLq5nv+nqFV/D2XVPHe9+F3AH67q/iug1X8hx8FjvmGiTsFMSxE/gxJ+e3HDIcNeyI1AfJiywf2417gvQHCpc1I3qIyBoqQcS8kHeXNkWfvgslyjA9EAaudzjEDRIDR4BxsJMQTlRn4BA87OJ5AadjxyGUoWze7l3qBzn1nCYIfmYhsomMDSauBXD+96kI69kJ+8EljnBDrKzP21a0oqi/uFu/16vhV6/8HqpJWE6o38VvMuY2fJiAeVXuuICrOrf5JDg/eKS58Vc+pRMcLmk6Ik1WFSN0Ox+6RkAYIVH+xf8XZyG8ZuOb/hUrlwM7+Ab6pBXjgwHEA6RHU2Go4+3vv3fJf8HnhoaH8jrC484DhgEQRkfBBmBSfn2lGfkl6FrVI/j/KvgW+iSr7P6+2EQITtEBBlAqoaFEKVaGERwukgFIIlKYtUPCBpQYUhATwUSgkA50OAV3B1RVWXXUXXXXVn1BU0D6wLY8f8lpFQanK6oypSwVsC7SZ//meSUpB3P399UN6586d+zz33HPOPQ/HAWHdl/tpP/7rn1faqj8+CZb9vHaFV/vwqhOCt8b5ayx6D8RyWWxoBWqB9oggte6jMmm4BeZs9Wd6Vh77A2V+gyvwvRb1mi/w16h2pL8r92LNVQNnmdTmz/E3UW2gv8NThMAtB9GXi5WtpcrkSnXgv8LoT+C5t8O6Dom67m2oKrM+
*/