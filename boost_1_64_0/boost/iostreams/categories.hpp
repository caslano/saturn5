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
DcvvbeL2PNZ85EleUhS/KVq/0+y1auXitsN4Dq6m3zTFb5oqB7ZT6JeyJxcZtv8B78MdXxmbG635bof1Yx9IG6/4yRQ/Vl82Qfy0sPutyXJ/uqlj0s9nQT6x8myn6zSjnYTz2y4c2/Q1JJ0Dv/3xRx+ex9jh23upRMaTEMZDkvaz3c1tvhLxOxJuCaz/KMmp6nhrznuB8QXDZn6Dw86B/0eE7wwl7Nl233yDuDVz9zIypCzHgD8oDxw/l+J5sp2OvPyp0zIL1LXTl4oMYnlvyckjMpoIv2fL/UMYaXTkea+B/JQUXJVvKOG0MMuDY7k8+Hta0tfHzbhlvXJJWWGp6meh+PHacS+S+2YSxnSEsVzCGOZOsOMtzC/Cfx/9HxT3LSjR9vh2W+oIxzHOob9zJU+tHPyBtFJ+2ayL1MFs4WkXqn/S9h5EhaxEwFul77zOxfYQfVqgPbwI92a57/LJe5yNW4DW793APaCP2A+auJe/TawCmvQxfteQzPZ0XavI3wGRT0c/iLrK9xmue7SesW2z9g8cScEztk+oQ2DhM7XdwfMU23+m3KfZ99PMsKROmTqaynoGHqkr0G8zfLkfY9/PFj+lhxQ/IfMkkJlcU5GxC4HnAO8Ab8XWcP1B9tBMQ98ndEfanhF/w1yWrjwl93H6d9Gt4fuDLgjrFXEfYIf1gtwnaPsCNaxPfUpfwPp+UNz/6Vx3q/hNpt/QviAdaXlbeHq4rPZ8s9x/Cv/v2m3m9dtk74bdZj5v3kub63Gev6zEe3R8mSnx9UZ8O8WtnZ33rXIf7+w7tOFMk3AyEM4hcWtuh1Mr98dp+xGGE7YtP9qOzrHb4vXipxvkQjeRO/wp7UXuNraJbAt+ED9fYt1RM7sNyROeGLYP9r2UyTwJFy08pqjU9/x/SjhfsF0NaSOR/35I82HhcbtOQhvS3My/OV/ENuMT4BNAs8xrFNrHtqG2WeRtw/PbfnrbgPgdbQOeadsGlK/SNvBe3zZIPe/LdfOVXOM/gGPv/qBc8GZ9aNfzaZmcEDblOUzmVfBoSu6U6flH2/EJwn+yrj4zLO6T5VxuVcNj11Hq2NWMN1WJV137H8u1/99xHdQu0HLwVwblAS8PMkGktlFTpqv2INYL/+vG8XhyDTRfO0/EvDjGBKwLIX2qPQfbZHuCvFUMRB1LoBwNA2lCF+qjDLdK2GuNZsjpTFB7yCvGHO+zb3uY85XquH+zoovxDeji5dvD6CLl4NCVkD0WeccHAn+PulIDugG8tdtVOfsLc6fkB8aZyOcZwfpizyMfED9vyt6tCtAS7R4uhk15+71KmVGuR8R9NcLti9anubYPYBhaez9/E7ebMfruoJSLJNa2WxS/w+SZhe8l3SRen9lqybM/GM3w1G/EOcrUCv9i4RsPnYqXfWjx0NWFUNL9PoTrSoxv4on3NIt3DYlv4saPMHMe9FcFfwfk3bCzyeuY82hDvv3g+0zm0pdzCqFVrLPu8b2TfmJRtp/LN5j5jjkS6/6gr2GbRlZ9PSOkviarcwEsQ1W3BnGj9QLq8Q2gGxFG3Q5Lt2RWGwFiYrsgT6nDMuy2y+ofwj/HuEJrW4fhsU+fS93k3KBdV78RnvnGlfiv0SeGodcnz07TrQhr1RPsPitbnsU5xs3WO8dx4n6xcQ44rLm7RHl2idEMT81ynY7yWdcWayypN7GeeFdmfKxbqy/krwX/F6Iv6Vp9scfT4cuV7XBIewGZq3P3c1nWlGPQvEIiN81dyDYjCzQY/JU77XK1JjStz46c6zT5Laej/czvxd9oXdkyTJdzriyyuZKg/saMP9WOP2SvGfM0zFJ8UDH4E3c584TWgN/qgveWJgE7Cn8=
*/