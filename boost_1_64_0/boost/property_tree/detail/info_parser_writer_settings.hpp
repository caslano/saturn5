// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITER_SETTINGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITER_SETTINGS_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template <class Ch>
    class info_writer_settings
    {
    public:
        info_writer_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4):
            indent_char(indent_char),
            indent_count(indent_count)
        {
        }
        Ch indent_char;
        int indent_count;
    };

    template <class Ch>
    info_writer_settings<Ch> info_writer_make_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4)
    {
        return info_writer_settings<Ch>(indent_char, indent_count);
    }

} } }

#endif

/* info_parser_writer_settings.hpp
WXGSFXK+Z1w+5TH5n1b+U10HihNskeNaKfoZ5TLKGtnz1/Dzsvokxj+nbeZn60d8T9vjNaIfNRc/bwxYIHfB/GeSLaJfMF6sUvhFazMTbJH/JePJONvUL0oj8mWPGWX+E9rwSX064/uR2vtoCsyr414r7nQ9c9b3C+n7lO9lftaa4/tCWU/zfUQGmSEy4JxDzlfMjTnl91sn+6RP2w+ezxI5b16UWWc+qC2eT33IOFPguA7G9F1sFZdntFv/p9hmSP9nyfqYec5Jhlinetb8ZJv4x+UjW3+mxozPg33vUcwZsGa8yZx4n/3PPNnvt/+4wOAbncfIIcpxbV4g0M4o82xWJH5GSltdm0+IW0Rfb3tmiLzBPmKABYrVW/hW+4IJtsh9gGPubdrBOMvkv92cY5bIhH3CAONcovgd8jPFCpF3qodHM8Qc+e8yn1ikcNKcZJHCd3udZYrfo62sUPJeeZjj6I2M6Qv17yXOQ6LfORyMi0tMPdm5QDzyImNO4D3OhLjMiT+aK0Pyc5H8F6vLsdkqjrFA/kvsHwYYZ5ngpeYjHUywRNawNnGSZS7eWLterr3Mk/sK/WWSbUpGPGeYOTY58kr1M0PwKnVwnjmyX21cucACORftOzoYZYnc1+gTk/hZ7GBVLHit8X6auphgi/wBc5QhVohYv84yxzolz1AOYyyQ80x94QJrz7LOPNu+ebexFqfZpOg55hznmWSV3AvqZZhFsp+rT4ywTtHzzBsusk7h8+WJOwbp8HiEObY5MqiN5/STE0+V9yn2CfMdnp/VVjYY7DL+RLq1mQ7GXuB70uI2RU+ybjPJNis9yuo17hTMWxvEI32eM0/hW6wZZPfrHxe5RPcTPWaVSIc0Btg5Y7506jNH2/WPjic4NvClLeNxNe+d7cv7q4PTP3WNKm4POm+LRx7gNabYpvCobV2TnRanWafkgfYfk6xS+CDzjglWKTpmTBhjmYKo9jHKEnml2sgwKxSWSWeURXLLzS0GmWaHWEyfmWaN4gp10nof7RcvUVSpXiZvaykU18mtko8hVohU6zuDLJBVY66SdTvnXfESRbXKYZwl8urUzxAzBPXqp49R1shp0Aemj6vjofrHDFkPUxZjXKLo4frBFNvETiiXBSKP0DZGWKXkkfIyTfAoY8IF5sh6tLWaC66NRsU1Sh5j3zHGKvmPlc4i2c3a+nnXVInIInknjR+TrFDYYq4wyw7Rx0lji0OnpDHNDkef5OdwrXvDzLDOqnPEkN//EbuxvMyxQd5N9JNuJud9xiAusEX135wnc/Wbs4yzTHBTY8xIgfO4Mk94fIEpLpF9M+Nv2yNiK0O0Pufq7m9Ye5nxPH/G9Za49efA34UzXtvem0kLfu+87PkFln5qv4uRxO+7Eo+I+XnyMsQCkVsYCwZYv45rY3GNYb/vaoNi5eXc0rYe9627lueo5x2MKb+bUY+XiNzKWHKaURYJ8s1R2x4SWxlh1vN5cYvCW9vfnh8XLzDNGnm3QV314lnGWSK4rbnASUalD4tzRArsNwaZJ/t29guDzBG5vecMMcuhIu1khoK7mN8MM8MGh+4qnRHWyL+bPIywSFax54yzTHB3+5QTnGeCHUruYW4wxiI59zQvGGCWHUpKrOUMMs0l8uz/MRbZoXDHtRFnvUfPzjFv/D6DYWbJC8wXJlhim4KrqYduLjJP9tW1mTGWKLqGtrJAbsSYMsUqJde0P1ii8Fr2AUsUX1s7WSWS5TknuMAUK0SuY3s6GGWBLQqu61hgjDXm/uC6cMs12Envr8TzTLJB3h89Z5bgTz5DpY9R1sjx80rbnPd5/zSRv8jDCYZYJu+bflaGQabZpvBbjm0mWaE=
*/