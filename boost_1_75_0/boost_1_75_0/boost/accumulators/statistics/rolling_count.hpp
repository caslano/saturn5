///////////////////////////////////////////////////////////////////////////////
// rolling_count.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_COUNT_HPP_EAN_26_12_2008

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
    // rolling_count_impl
    //    returns the count of elements in the rolling window
    template<typename Sample>
    struct rolling_count_impl
      : accumulator_base
    {
        typedef std::size_t result_type;

        rolling_count_impl(dont_care)
        {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return static_cast<std::size_t>(rolling_window_plus1(args).size()) - is_rolling_window_plus1_full(args);
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_count
//
namespace tag
{
    struct rolling_count
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_count_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_count
//
namespace extract
{
    extractor<tag::rolling_count> const rolling_count = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_count)
}

using extract::rolling_count;

}} // namespace boost::accumulators

#endif

/* rolling_count.hpp
LVnw0BzuDlMX/voEncCoVfWt7b2NWChff50GlZ02RCYK3EMvXYUtz3KEd2VQRECCThefyxMCI1X9gAk6mwkKsmkfNRGflwbhoSCm0ks8JuIuMksFULVwWD/rLMkquSztaR13qSEH3EAZFRt+15PW4anCullIzxYCbnzqi+dTCA3RXLqUgw9hfYtH3ipsKHcF9YlRErl/iexNYHdVYeJzJrsci8geGZZOHKPZeZYNLfXiEeqSzTdA1HxK3b8JKtIm6XpCZLM1Q8Rw4aLS6EdbHrHZs1LKU7ScglfeWchRgVltFCas0nUDdLXRRwtSR3rnR7U/c3LcyoN8RLbTG51KdMAI3MMuHh+05Zp3m8sdtYtGTOGr8Strj/ZhLaD22qO92mmPngk9FdUenTKFOs9icztrDMPOJEWTHLrOMAREUjd/tUXy2WqcVlobOAUB2vf0yS1IJb5+dBwrDhPG/pS3PPt2xDkv9gE77vsC8n5vLKT/vr0EurHQjBkdlosScInezFL2MkhFy4z6zUBynH5XIARuQgrv4cG2fU/QY1+zZvDMrHEiAqtB78rtcdFueWYSd38qljpwTBAT47hf3KntyCOk9RLuE4uaDV4oIccWSCZ/pUmLo66nHAu9XiAb9Rz1Nv3U08mjP6wwsTTSqlzjJfy+zEhUoPLTeJrno5BeH/NeS+9yspSho9vE2Q+sgBu92TN0R1E0NoSzVxKJ
*/