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
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
*/