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
NypwqmVEIj4D1xYX1VScW85rO7e4V9+NqfAcWct5SzoQ7ImliNkiQ7PbV0xsyTAb+OUvPq7nFoamOdg3m7SDTzUQox3vG5D6H//4x1B++bWUOtnBQrHU0cf6U2s+KmxnvIloutWJRqkll1FOkEdI8RKveqNg+s9hvody1j91t6oLhePnppF1so8/UUsN3PMIAFndE3q0vsa5r1k/RHAvpa9z4FC4byTH5rfNm58676677rmddH44lQT/7SYytooA8BBw5FtRJiwXnJCr3ahRaD0tWUltfvo3RAUDC4xgM3Cji1Ip1W4lKZnwGzz5eLnI3XiW1m3gKTQqMsMN3Eg1KUCeOJ1TDVzOIqjjdNxcaD/Mr3nw4BnOnl2NXLyvV84zrp8NrZbzTOvn4l1EImj9DAzuk4o7xbNxdUKVnH+ruUoyFs+H6NwuRm8azyK/XTd8Rf7I5KbG5DJ6I/k6G/uQwKgTVvivRHFE00Op08yCvesLZfwM0i9L1lDzZCdw2ldgnNbeQeT5tnPUzFHYzBZ3j2+INrfWV+OQOJFr4IgFczI3fJGT3UPXxXSto6ufriFaz8lzWlSld7lXpeHiYD25X/uGE9j4QAJXvr7DpenjnoQBdbrRqLZHx354LMZZea91KuMxEbsO06PoehRpASIsKleS8vFk3RSjIsVbQ7BI2Tc/GbnIRiiLbT6n1pi6DkYeJdA4dy6Hh4gNpuV6
*/