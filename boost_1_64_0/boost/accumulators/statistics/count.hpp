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
t7SzAgcUK7zOoj6figcmVSkev7T4WmtkjxlBPumDaeX6d+CS5I0PAI/LfzpHbYo7tazKYuPcEAQKs4+DUIe5zF/28e2+TVCPhZ4AKL7dhkx6b/IMfEozYHkIHJxns9rr3E6H77bdTQ9P429G5p23OnXTWowoL16cWAuIkqT4mPXTMpbv8/y26KLFfvei1EB3wwiybto1vGgZiubUnaf/wKyDZOt2Uo+r+x8T+ap6aJi2LdaASCH/mouU0O9sqNSzgliY/LHuS135Pa/ivMmOaiY8vd71COoZPmI1KtoKtx0MmXKmvBbplfwEHpTSvJFOx3QhYGdRZnBLF8d2gAwyMW4oSX3o2fgskfGEx2Qs/irsd39VaHMctMWZ0SZQBbAjmzh63kem9LgjHPD+zFcu4SOSQzwkUrsJduMn3rXTSZyIV69nCdgUj8LGo741co1+Nny87DQqrFTGsMZrvwwn+WnScc6RferzrLUKFem21L0AXbqqTt6ncsf7TOvuoJlWrXYoSiqivHkiet541ZQEPvZu/MqxVHz40BJv5vGvHD38qDtbtXPdHjB8bQ==
*/