// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains category and mode tags for classifying filters, devices and 
// standard stream and stream buffers types.

#ifndef BOOST_IOSTREAMS_CATEGORIES_HPP_INCLUDED
#define BOOST_IOSTREAMS_CATEGORIES_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif

namespace boost { namespace iostreams {

//------------------Tags for dispatch according to i/o mode-------------------//

struct any_tag { };
namespace detail { struct two_sequence : virtual any_tag { }; }
namespace detail { struct random_access : virtual any_tag { }; }
namespace detail { struct one_head : virtual any_tag { }; }
namespace detail { struct two_head : virtual any_tag { }; }
struct input : virtual any_tag { };
struct output : virtual any_tag { };
struct bidirectional : virtual input, virtual output, detail::two_sequence { };
struct dual_use : virtual input, virtual output { }; // Pseudo-mode.
struct input_seekable : virtual input, virtual detail::random_access { };
struct output_seekable : virtual output, virtual detail::random_access { };
struct seekable
    : virtual input_seekable, 
      virtual output_seekable,
      detail::one_head
    { };
struct dual_seekable
    : virtual input_seekable,
      virtual output_seekable,
      detail::two_head
    { };  
struct bidirectional_seekable
    : input_seekable, output_seekable,
      bidirectional, detail::two_head
    { };

//------------------Tags for use as i/o categories----------------------------//

struct device_tag : virtual any_tag { };
struct filter_tag : virtual any_tag { };

    // 
    // Tags for optional behavior.
    //

struct peekable_tag : virtual any_tag { };        // Devices.
struct closable_tag : virtual any_tag { };
struct flushable_tag : virtual any_tag { };
struct localizable_tag : virtual any_tag { };
struct optimally_buffered_tag : virtual any_tag { };
struct direct_tag : virtual any_tag { };          // Devices.
struct multichar_tag : virtual any_tag { };       // Filters.

struct source_tag : device_tag, input { };
struct sink_tag : device_tag, output { };
struct bidirectional_device_tag : device_tag, bidirectional { };
struct seekable_device_tag : virtual device_tag, seekable { };

struct input_filter_tag : filter_tag, input { };
struct output_filter_tag : filter_tag, output { };
struct bidirectional_filter_tag : filter_tag, bidirectional { };
struct seekable_filter_tag : filter_tag, seekable { };
struct dual_use_filter_tag : filter_tag, dual_use { };

struct multichar_input_filter_tag
    : multichar_tag,
      input_filter_tag
    { };
struct multichar_output_filter_tag
    : multichar_tag,
      output_filter_tag
    { };
struct multichar_bidirectional_filter_tag
    : multichar_tag,
      bidirectional_filter_tag
    { };
struct multichar_seekable_filter_tag
    : multichar_tag,
      seekable_filter_tag
    { };
struct multichar_dual_use_filter_tag 
    : multichar_tag, 
      dual_use_filter_tag
    { };

    //
    // Tags for standard streams and streambufs.
    //

struct std_io_tag : virtual localizable_tag { };
struct istream_tag
    : virtual device_tag,
      virtual peekable_tag,
      virtual std_io_tag
    { };
struct ostream_tag
    : virtual device_tag,
      virtual std_io_tag
    { };
struct iostream_tag
    : istream_tag,
      ostream_tag
    { };
struct streambuf_tag
    : device_tag,
      peekable_tag,
      std_io_tag
    { };
struct ifstream_tag
    : input_seekable,
      closable_tag,
      istream_tag
    { };
struct ofstream_tag
    : output_seekable,
      closable_tag,
      ostream_tag
    { };
struct fstream_tag
    : seekable,
      closable_tag,
      iostream_tag
    { };
struct filebuf_tag
    : seekable,
      closable_tag,
      streambuf_tag
    { };
struct istringstream_tag
    : input_seekable,
      istream_tag
    { };
struct ostringstream_tag
    : output_seekable,
      ostream_tag
    { };
struct stringstream_tag
    : dual_seekable,
      iostream_tag
    { };
struct stringbuf_tag
    : dual_seekable,
      streambuf_tag
    { };
struct generic_istream_tag 
    : input_seekable,
      istream_tag
    { };
struct generic_ostream_tag 
    : output_seekable,
      ostream_tag
    { };
struct generic_iostream_tag 
    : seekable,
      iostream_tag
    { };
struct generic_streambuf_tag 
    : seekable,
      streambuf_tag
    { };

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CATEGORIES_HPP_INCLUDED

/* categories.hpp
Pbn0sC7TQvR6Y+nZ35H/SrlxT50r5RhV92afQj/CqsAIw9g0KaATNPkrH/2zKR4EzvnZU2o0Ji4pafeVCUS7PB+uGdYjw0PL/SEUpa+/aO3A/ZTzIm2E5bSwL5N1XQTZ8BNjuFYOePKFUA9xbzE+TO9Iz8WUgDbNh1MsDky/DIfWH4HTB5tbsmXWwzs61RXykXNGbMLccAGUTpaEKtcJl4LViUEb3AL7TlV9XnWXMcke6A3dLKiw1fga0G+cL+veSgP37eCAI2orj6z1i1AjI7LQ4pDcDB9t0viiaYFFCrh5a9U81982cFeNka/86ZE+OKh6m9tbUVw4cXvF1Hx5Txgh5kWrWyEY7mZLQvRUuEKLP8K+cbz1F7LczT2OLP4qBbDVwfBdzR//ih+ixjTM0GQHLKyuDYhy5EDYCKKiQTseq9PM/PZZ43pmvqKBz0ZFH/4Hdhuxs1ntWsh5el9DOu9nXvcOBhk4Au+H8viw0Apm4X8JHLlvT28h7l+jA4Q4Rf9UwAzTqDQav+OZR6ie1r4K3X7cIeWLOp/oBATz9QOvtz3GTnwX0k5pFg==
*/