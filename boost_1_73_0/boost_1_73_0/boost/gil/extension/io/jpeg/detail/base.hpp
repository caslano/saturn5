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
KNpqLuN349RDor7YSBuvaibrHMccX1ESS5rNq2dYoCEyahONN+tsG/hYjgTBEJx13adb4hajC2uDNdQcWZhrJckC9nAQstLTp0mzljV+ikPpjvmWdenj7XfZxPwTQBx2NhVbbuMuGQ+iJx91NcYQHkwu89u0ftXdOL7u8jy9o+I0OdtWHGZls+isr2AxmqyW5jAzx2XCB9hnVUquZKqj0XWF+6xJOsyHDxF9VxPeWCsjb+3wqYyJgMEn6osR2trEwpVgwR2OVvma2R6fQz8YTFNnqDj8adPkHfl/eprx2fmg86+YKPDVV8/0/85UOQlA1O8M3p4PzjBZGQ7cBcxDXoiishIPLcJe1MvhkFCWlntjrpGpByvBTbyMSUKj6YWtSZ3u415wNWjs+XL29Wv5tYv5L6Ukl/ceXbZRS1vbDXTDvWb2x5B05dkEXGbL2ph0vpUwH2v9AHuXEfOLDJfIPi/98avHQpmwCCU1ksqxEh+gfrJwNS5ooTiIVomROW6Wk2N7YCMht3NrpuVNW/WQm37ObFcwF58VAg+vYovdGpwjs3gych313vh7TJE1bLEy5GWu6hTNQOVxe5ImOf1M3ZmNL/ZFN1ebswW6nhR9eWZ4o5famUtNASFmRpxYc4YRoafXKbpNlrAum5RX
*/