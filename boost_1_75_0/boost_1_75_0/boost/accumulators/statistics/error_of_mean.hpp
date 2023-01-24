///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // error_of_mean_impl
    template<typename Sample, typename Variance>
    struct error_of_mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        error_of_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            using namespace std;
            extractor<Variance> const variance = {};
            return sqrt(numeric::fdiv(variance(args), count(args) - 1));
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<>
    struct error_of<mean>
      : depends_on<lazy_variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, lazy_variance> impl;
    };

    template<>
    struct error_of<immediate_mean>
      : depends_on<variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, variance> impl;
    };
}

}} // namespace boost::accumulators

#endif

/* error_of_mean.hpp
nCH0OpkL4cY96PARCsLtWgBgYXIhywfyJgDplqo2IliEZ14wGLgZgm48v4huUArMSNY72OxvYrL1gM1Ih7mgw4uMkkkqgv8paFdyqVkqEs47ODL/7Whdb5WM54w26rwGj1C+0eg1iO2mjSa8GTcKeNNvTMWbbqPeG9/YjvqmZU5+S7f8wduI9lzv4iIcfZgPZFYZuMYvUTMEEDj0re2Mj9LroOtC26hPdvKBwir0F4MnTuQzZz4YfWp027Bu2yk+MAHixYkII3X8StxoaPzqKoPJwL9a0QP4xNruD92LDXyJtJiwjS+h4iw18yVUgaWWBnZSS1/C9RprrHzgbfQcii0MVKGntDE50NWz0lu8xdeGHoB0N6W38P712Ky20XWmMwdGh4e12cJ84G8YFba2Dtv3ErQEBmrKHYZ+P+ztCHsioxXyzw4rvmsn3fVd2+TWruMkN0HTVI2fAmmsjA7jZsVLnb3dvXzgk/kGDnEnygDPQpj9uY+8aKA6h1TRE/ns676BmqsfvwwcRQNHQ42k38u9JGyi/ZfAMzcA8Z+IuwUcanSxHD5Qb4euw7ndwD8eQmc/j0J5nkT3pjthFW54kCRz8ieS7wQWPuGvuKyyCsz8s+R+dmcWTjG5TtAWKO/fBDGR6/+q5wavo70XrKOvDXGCi2VuQCknsjtzIZuLpanPfbzfQc/JG3BJu8J9cWw4BMXOq8rDnfEG45vI
*/