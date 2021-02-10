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
YnVpbGRjb25mVVQFAAG2SCRgU1bUT8rM0y/O4OJKTc7IV1DS0tJScMlXyMsvUSgtTlVIKs3MSUnOz0vTU/DMKy5JTUzRUcgqLQZLWikklpbkF6WCpBV00zKVFOzUjLhSK1KTFVSqHUND/INcnf393Kx0EcpqQeoUlFSqHWqVuABQSwMECgAAAAgALWdKUpIzSo0LCQAAPB8AABkACQBjdXJsLW1hc3Rlci9idWlsZGNvbmYuYmF0VVQFAAG2SCRgzVltU+M4Ev4+VfMfunLFDplKHMJ82eGGuc2EDFAHCUXCUexxpIytxFocK2vJQG7n9rdft2T5JXFCht2rOihILKmfbrX6Te2fmBcIEJPJ2zcxm8H7P+8nBYQXf8b6b4w/+JlRXcTiF+apaorx+BuYX6S8xc9tmLUgJ/s2rsN2ZN9gV5ONU26f6Pt4vA3DW5KT/rWI+nZMX3EkJbUIXTFfxHwaKNjt1qH98eOP0IT9vfbHBhy5EWchDBWL7lk8bcAnX4/8FLjPz45knxvAFLihswQ5CrgEKSbqyY0Z4PeQeyySzAdXgs+kF/N7fOARqIDBhIcMuoOLm9P+cQOeAu4FFmghEpCBSEIfAveRQcw8xh8NztyNFRoOQiADn0uFoIniInKQPwPF4pm0OCSG
*/