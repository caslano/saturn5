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
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
*/