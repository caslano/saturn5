// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Thanks to Gareth Sylvester-Bradley for the Dinkumware versions of the
// positioning functions.

#ifndef BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED
#define BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <boost/iostreams/detail/config/codecvt.hpp> // mbstate_t.
#include <boost/iostreams/detail/config/fpos.hpp>
#include <boost/iostreams/detail/ios.hpp> // streamoff, streampos.

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> 

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::fpos_t; }
#endif

namespace boost { namespace iostreams {
                    
//------------------Definition of stream_offset-------------------------------//

typedef boost::intmax_t stream_offset;

//------------------Definition of stream_offset_to_streamoff------------------//

inline std::streamoff stream_offset_to_streamoff(stream_offset off)
{ return static_cast<stream_offset>(off); }

//------------------Definition of offset_to_position--------------------------//

# ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline std::streampos offset_to_position(stream_offset off) { return off; }

# else // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline std::streampos offset_to_position(stream_offset off)
{ return std::streampos(std::mbstate_t(), off); }

# endif // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

//------------------Definition of position_to_offset--------------------------//

// Hande custom pos_type's
template<typename PosType> 
inline stream_offset position_to_offset(PosType pos)
{ return std::streamoff(pos); }

# ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

inline stream_offset position_to_offset(std::streampos pos) { return pos; }

# else // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS

// In the Dinkumware standard library, a std::streampos consists of two stream
// offsets -- _Fpos, of type std::fpos_t, and _Myoff, of type std::streamoff --
// together with a conversion state. A std::streampos is converted to a 
// boost::iostreams::stream_offset by extracting the two stream offsets and
// summing them. The value of _Fpos can be extracted using the implementation-
// defined member functions seekpos() or get_fpos_t(), depending on the 
// Dinkumware version. The value of _Myoff cannot be extracted directly, but can
// be calculated as the difference between the result of converting the 
// std::fpos to a std::streamoff and the result of converting the member _Fpos
// to a long. The latter operation is accomplished with the macro BOOST_IOSTREAMS_FPOSOFF,
// which works correctly on platforms where std::fpos_t is an integral type and 
// platforms where it is a struct

// Converts a std::fpos_t to a stream_offset
inline stream_offset fpos_t_to_offset(std::fpos_t pos)
{
#  if defined(_POSIX_) || (_INTEGRAL_MAX_BITS >= 64) || defined(__IBMCPP__)
    return pos;
#  else
    return BOOST_IOSTREAMS_FPOSOFF(pos);
#  endif
}

// Extracts the member _Fpos from a std::fpos
inline std::fpos_t streampos_to_fpos_t(std::streampos pos)
{
#  if defined (_CPPLIB_VER) || defined(__IBMCPP__)
    return pos.seekpos();
#  else
    return pos.get_fpos_t();
#  endif
}

inline stream_offset position_to_offset(std::streampos pos)
{
    return fpos_t_to_offset(streampos_to_fpos_t(pos)) +
        static_cast<stream_offset>(
            static_cast<std::streamoff>(pos) -
            BOOST_IOSTREAMS_FPOSOFF(streampos_to_fpos_t(pos))
        );
}

# endif // # ifndef BOOST_IOSTREAMS_HAS_DINKUMWARE_FPOS 

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> 

#endif // #ifndef BOOST_IOSTREAMS_POSITIONING_HPP_INCLUDED

/* positioning.hpp
x8+VP4ucNafxHsyzcVWMXJe74zjwUs2zOZWPnmdPLGOexS1bnvXPMMuPl7Pe7HOXK5e9PkPWllf9tP+NmLf21619JvfV7POaK1vzrP8OvF7MT3IGmAr2ec6VS+RXv66vIOHNDaxxn503jVV2mVnzfb/OE5lKgXXfWe7j/ffoBeL+PGcqT5/jxAXmLk/Lzs40fhivFnfq+HHdUd311gvskPsE/3y63nLf3lTk7VxVzzTtKnoPBfcH0veErqcXv+Q5k6mXlxKuWU4MZp5/pmYXzMmc6J6OPHHygvwsjcNE2Dpe4tCkmjR51iGe1V70Hg+coeba1Mgxhe+mxfLMcwh/hLIXYrwxQtlinTB18JZKtMHwWHxk0ar4cHx8TGx8qLIbd5h3x2wTapZrHrNog2tSyZ+7PsmP/yrijziTiJ0zkN+Imu3aCS3a7M7p9lSKPvP7QjfviA9VKeam1h3iZqq4uRX5Q4VuPui554XhDDw8R8KwGPOK8aFIfLhGvBPrmhvMxqKyi5sbI26nYTa6srodXpwW9G9tdX+ruo95TTeOnEg0fjLQ36Juq5m4uRC9TYVuNrLFQVw8+d41j1301/hIBT9POnIOXmGePE3iISLP246bEeydHbBX3N2x8X7c/rG09OovblYQv8YjPxqlcfuu757uv3SL1sXrA3Vy3FHOdKWc6Dlyv1wd7a3VYghZrtQoZM7oo24dXSW6p1j2nLz8SWx1zRdK1sSss4PxY6uP1Z4TkJtsrXtVTtIpnpfD3ipeOsRJgbLl8XyxU1HS4Qrk36zipUMNP11LX9+bNlTiO7juQNyWuNX7yUXiZnA1bXOhYlB1NW5W2+JmWlbQz359vE5ka1jjarUlrry69IoqpZ536ttzy1vzqrhVzSuvJj4uJj6cqGV1N2ammleuapYaR5EfEUfe+qV4dSlJXXD9/hhxtNMWRzPypK42xp6+T4mdGFtcqXuOhGs4YdrjhStUzfyYdA+ks7ZWKKuazvU0nffawjAr35rOH4lskv0c4yOk8wdiVtt+pnEgzAm6PtpLy58rHb09hjZpHFRSFypqOiZUtcTB7LzJGB+1LhC7/P2YtPH8tSvRz1dyubdPNsGmzV959MtMyS/13dBY7Fj3PFT3nGCYLGlik5tsX3tdxrAXXQel/tV0CqZbfCnlL5JUMn4eJ356lx4/NHhKj6P+pceRuqntztLiyCJnjyOV0/z9Ag/fUkPf1YmmTGX6SHGXH4w7/36yv/ZqbKj0tUL2NTL/+nM2337A1f/1hF0vz3pm3sNXfjH6uK4z5z9e+pov+5qd0taClb6WJ+FBV/+RufM/um3V2AGNPi0Y9s3KU5OPfW3asa7VOtY1Yv/qNVw/17kEX8v8u+g1W9cxTeV3tv6e5fY36e/5hnv9vdTt39XfqwxlQX/f7LaX9Pc2XQ+V4/eFYkf3/a+MytTnJun8v1RYHdaCTWEd2AKiZD1AGmwDG8POsAkcBpvDyfB4eJbKH4A7vT45eK0+Nxm1XZ87T597rj53oT73fH3uWthK5+um67zcDnCFPvcSOFLlTtX5uWPhSpih83Oz4WqYr+YF8NfwHHgVXAnXwCvVnXU6n3e93h+AvR3t99E+tdWwCaq99q+10Xng3WE12AMmwjwoa/VhXdgHNoZ9NTxDYXc4HPZW+T5wIOwLh2h4RsJx8BQN16kwC56h81Enajgz4HJ1ZwUcpeurRus5C2Pgr+Fp8HaV2wyz4FY4FT6n+s/DmfBlOEvnPc+Gn6v5FzBH563mwpAT1Q/DoTAVDod1XX2Nx12O1x9BHGs8dkQ97Pj92DIfeYPG440afxs1P2zRefR3aXxtg2PgPRo/2+HZOo93ns4=
*/