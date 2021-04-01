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
RQ8QUz2Hpx2VQA15QEg09m+/wtr8P8imQ2ldMPfkF7NcYeFUTcUi4YSwrLiYyk69ZLSDLAuYY/GJ58SunN4iA7uY0GeUr+P41Fd/Vu1lgh+lnK+2FHQ2Yyn4rlExE0tT2FURiQLbrasq78YiTRehTe78f348VTjxWCNludnNofq7yStIQ/1ZmNN332Sy0aASU57quMK8VrVBLSwudwwTt1kEBU15Fn2jBGSQ0hwUwLfSPEcHETjqLLg35dkQsCsxMWfAZBZCzi4Lg4anCEsrobG3m+9SOqbK1q6zn12zY3tUtoXOrRhM3rEeIqpaaF5eviFIrLWGHkLLeZ3D/nxJ0M8X2YhS2yIiNOBQ8vnTYpoBFKCoLQdYMz0Hy/FfQvbH+qNAkFIq22PPuRYKV4bFzeYnKnVD0AjJmmZc+y9exv3tci4dvZD3dMoVzmCxsQfrL8YCbgkTGIHvrs+iZspfDfqJK8C3MCEsOS1En+qrLwjvymoqQAPJBsZ+1Yca/BUSe9Ie/GUBdsPU4jhe8FmdmR8Kw5l0lHQ3L1HYT9HVykrgOt62Eb80NPHtaA==
*/