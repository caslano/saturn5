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