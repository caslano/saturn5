//
// Copyright 2010 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <csetjmp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4324) //structure was padded due to __declspec(align())
#endif

class jpeg_io_base
{

protected:

    jpeg_error_mgr _jerr;
    jmp_buf        _mark;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* base.hpp
PLdVDgmf2WEc+aXVv/dhBVyP38nfZK30ZmuVb1OcYr5LceR5u+LU8h2KhxOoV4yNtdvBXmgcsxclVnrG5gm2WrCbBLtVsM2C/VGwQ4JZx/+lumRXipuhrrdKyLFPquKnZmvibPjV2kSpqVrHH7w9Tnj7W5XJ2ymWwnN4uGfeVuXkbViYFzb1ibm9fea1S58gyPyyvK7Iyuv5nv1xff5swiOW1z+yvH1UsSF/wvbEP1Y8fLDD8vifFDv2pHbGw3o=
*/