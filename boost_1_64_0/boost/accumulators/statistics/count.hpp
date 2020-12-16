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
HRvI0AM1YaScmlY0Ih35z/iZ+N/R/sGXsMHggTxXj7dH7i8C1rk8PnKVDZO/a9E/9Rdb577hLLuLvhSWgOzB3Wmh2OILRHRR3HAGYBCS+cvLoK45bz7PgOF0unk7UhtVu5LJ+muoiRMhdC6H7uba+tP849urGSdg1keGZIMSspoRCipCIip6D5I1w59udrnPfqvLNfPTAuOT6QK7mrXqcEZ4gewA0Bw/LrSiWosdPBTpTIXmwYPqpiL8On3asf7yuOhqHEMeng5jEKmIcz3dufyDvWoYFsYAQTC3INDm3oLjU4OgW6otC9/CJ9m91tlp9drCX1q9dkkepl+SgKfbNernw2yqJhYJnS35pQvtzMdS5to9YvgqeLmMOslRyZ9VLP7btN9zEdlrDTqAZSfbVcpwMsjYL+Jz/UpV5wfYSXu4Tpk0S/sRBboWsxJ0XV4OkCart3tLGRcgsQ3zNGlmwwjgON1VeSpoU9fVFN8b8Q29EUmenty86wlNeiZqdKZIxS5LqNh4dZrfGuoNuxPSbpeJfG5C2jEN9yIF8+yMh5dTAX/aJUFXxFFzsw66NB70wq6DeSb7/38/kj+5v/qni2z5ARk4cC0TYjLECWKSysRkK4iJV73s0xLvnFrTwYo0dDbBTMLKfJaudT2/uQhuOEAg67WNk2xZWz5TJJF4MCji0c9lIHvcnLv5BmuMIEwjTCBQ9iNaZ08O9aKEP3XKLI3TgsG3u6QBqjPX3M50cMzdQfxp/cdCS/7w8K1anlDdo7U8QcuvkKS2xf0nK3/HSVZ+FyTI+7f/YZc3aaFOn9/jAOnb2PAHWOkfm3yA9G+MsdsT1el3dD9A+vus9B1nWumHHwh+WNJjhFbN1+l/d/kB0vvs9Hcu1unn7jt9a9M+7XXdzGRkH4vs2C6xtQew4Kwbg3OYvvZiFjZo/i+V+T+F5v9i+1ZAWL2ci3TRrkcDCnL9sRvNqVbmeMCH8uGpunKYPZvdgPrsEoEaag71BjVdoNYsEgWrnzNYCAywi8FW1qUW9kF85Dgk+ZVOMh5J/HRKmxdpa203D6lZIPuvlWmUlQUiaDWVLVTCDRAWtZwL9oBOnLj1tF8DH9eNrnx6VX2R3RXnoCsevVW6wiAx7KKEaxdXGdT2fZouwTvD6V5eWlX6qSKEOcumEf4Ui3cYCdAMUh0HWLyV9fc7LvQgMWsFQIPGFRTmpP7EofZSJBUI/QEB2bsge/SCOWD2nlTvQYuDa+GuPpQmVJrLF0fHd4vjRiXM1PELaabuZiMl+uiyEHPu5gn2TD3Vbv1ym3MquAWtv4WA/cTDPal3PpiV9MYSHyQSdpTQrh+82nl0f/pY1fsS60xEWO57hGobDecw4zcbxp6OYttFKSxewF3sBUNZVSUd3GJ6UoLw7THN3ZDMxGwbIc5ySipsgrnmvacZrWMGiG1YKOJO4cViI6sevqpu7St7kLdEywU2UZCSSx03lgvLaC7nW62LEgsXw9gyVY7qDpjsww24J/qDtRpfDYZdG09IdzPPeaYN4xWBgQMiZlQxYecWU5PlsaBXYxvhCJQPz05mKUle5Dwg4YtRQcL3ugoSFuZFcExR1ziEAD7Ha9CshDVo9SJrSBac1xQjOG3y+p0n17zXFDDmX6shzu8qsx+DpFWNMVLWEB4ihD7Ef5r+j7Do88MWPd9+6b7l6WxGtUAu/U2RbO4YiQAj1psln3sqV/H1NPMzr/kZCzu+Av/JhIb3cP3OxUMl7LgeEo+tyWIHqDJJGxxng+cquUiU/KxHC9Tnl8TPy49HAHX4m0eJOGlbPl0142UjwLf5EclbUuDGNefKjS57zpRrCfYOfNVAkKJms9LUsZu1sVU=
*/