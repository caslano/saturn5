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