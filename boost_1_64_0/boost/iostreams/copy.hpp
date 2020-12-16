// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains: The function template copy, which reads data from a Source 
// and writes it to a Sink until the end of the sequence is reached, returning 
// the number of characters transfered.

// The implementation is complicated by the need to handle smart adapters
// and direct devices.

#ifndef BOOST_IOSTREAMS_COPY_HPP_INCLUDED
#define BOOST_IOSTREAMS_COPY_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                 // Make sure ptrdiff_t is in std.
#include <algorithm>                        // copy, min.
#include <cstddef>                          // ptrdiff_t.
#include <utility>                          // pair.
#include <boost/bind.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/adapter/non_blocking_adapter.hpp>        
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>  
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>
#include <boost/iostreams/detail/ios.hpp>   // failure, streamsize.                   
#include <boost/iostreams/detail/resolve.hpp>                   
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations.hpp>  // read, write, close.
#include <boost/iostreams/pipeline.hpp>
#include <boost/static_assert.hpp>  
#include <boost/type_traits/is_same.hpp> 

namespace boost { namespace iostreams {

namespace detail {

    // The following four overloads of copy_impl() optimize 
    // copying in the case that one or both of the two devices
    // models Direct (see 
    // http://www.boost.org/libs/iostreams/doc/index.html?path=4.1.1.4)

// Copy from a direct source to a direct sink
template<typename Source, typename Sink>
std::streamsize copy_impl( Source& src, Sink& snk, 
                           std::streamsize /* buffer_size */,
                           mpl::true_, mpl::true_ )
{   
    using namespace std;
    typedef typename char_type_of<Source>::type  char_type;
    typedef std::pair<char_type*, char_type*>    pair_type;
    pair_type p1 = iostreams::input_sequence(src);
    pair_type p2 = iostreams::output_sequence(snk);
    std::streamsize total = 
        static_cast<std::streamsize>(
            (std::min)(p1.second - p1.first, p2.second - p2.first)
        );
    std::copy(p1.first, p1.first + total, p2.first);
    return total;
}

// Copy from a direct source to an indirect sink
template<typename Source, typename Sink>
std::streamsize copy_impl( Source& src, Sink& snk, 
                           std::streamsize /* buffer_size */,
                           mpl::true_, mpl::false_ )
{
    using namespace std;
    typedef typename char_type_of<Source>::type  char_type;
    typedef std::pair<char_type*, char_type*>    pair_type;
    pair_type p = iostreams::input_sequence(src);
    std::streamsize size, total;
    for ( total = 0, size = static_cast<std::streamsize>(p.second - p.first);
          total < size; )
    {
        std::streamsize amt = 
            iostreams::write(snk, p.first + total, size - total); 
        total += amt;
    }
    return total;
}

// Copy from an indirect source to a direct sink
template<typename Source, typename Sink>
std::streamsize copy_impl( Source& src, Sink& snk, 
                           std::streamsize buffer_size,
                           mpl::false_, mpl::true_ )
{
    typedef typename char_type_of<Source>::type  char_type;
    typedef std::pair<char_type*, char_type*>    pair_type;
    detail::basic_buffer<char_type>  buf(buffer_size);
    pair_type                        p = snk.output_sequence();
    std::streamsize                  total = 0;
    std::ptrdiff_t                   capacity = p.second - p.first;
    while (true) {
        std::streamsize amt = 
            iostreams::read(
                src, 
                buf.data(),
                buffer_size < capacity - total ?
                    buffer_size :
                    static_cast<std::streamsize>(capacity - total)
            );
        if (amt == -1)
            break;
        std::copy(buf.data(), buf.data() + amt, p.first + total);
        total += amt;
    }
    return total;
}

// Copy from an indirect source to an indirect sink
template<typename Source, typename Sink>
std::streamsize copy_impl( Source& src, Sink& snk, 
                           std::streamsize buffer_size,
                           mpl::false_, mpl::false_ )
{ 
    typedef typename char_type_of<Source>::type char_type;
    detail::basic_buffer<char_type>  buf(buffer_size);
    non_blocking_adapter<Sink>       nb(snk);
    std::streamsize                  total = 0;
    bool                             done = false;
    while (!done) {
        std::streamsize amt;
        done = (amt = iostreams::read(src, buf.data(), buffer_size)) == -1;
        if (amt != -1) {
            iostreams::write(nb, buf.data(), amt);
            total += amt;
        }
    }
    return total;
}

    // The following function object is used with 
    // boost::iostreams::detail::execute() in the primary 
    // overload of copy_impl(), below

// Function object that delegates to one of the above four 
// overloads of compl_impl()
template<typename Source, typename Sink>
class copy_operation {
public:
    typedef std::streamsize result_type;
    copy_operation(Source& src, Sink& snk, std::streamsize buffer_size)
        : src_(src), snk_(snk), buffer_size_(buffer_size)
        { }
    std::streamsize operator()() 
    {
        return copy_impl( src_, snk_, buffer_size_, 
                          is_direct<Source>(), is_direct<Sink>() );
    }
private:
    copy_operation& operator=(const copy_operation&);
    Source&          src_;
    Sink&            snk_;
    std::streamsize  buffer_size_;
};

// Primary overload of copy_impl. Delegates to one of the above four 
// overloads of compl_impl(), depending on which of the two given 
// devices, if any, models Direct (see 
// http://www.boost.org/libs/iostreams/doc/index.html?path=4.1.1.4)
template<typename Source, typename Sink>
std::streamsize copy_impl(Source src, Sink snk, std::streamsize buffer_size)
{
    using namespace std;
    typedef typename char_type_of<Source>::type  src_char;
    typedef typename char_type_of<Sink>::type    snk_char;
    BOOST_STATIC_ASSERT((is_same<src_char, snk_char>::value));
    return detail::execute_all(
               copy_operation<Source, Sink>(src, snk, buffer_size),
               detail::call_close_all(src),
               detail::call_close_all(snk)
           );
}

} // End namespace detail.
                    
//------------------Definition of copy----------------------------------------//

// Overload of copy() for the case where neither the source nor the sink is
// a standard stream or stream buffer
template<typename Source, typename Sink>
std::streamsize
copy( const Source& src, const Sink& snk,
      std::streamsize buffer_size = default_device_buffer_size
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Source)
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Sink) )
{ 
    typedef typename char_type_of<Source>::type char_type;
    return detail::copy_impl( detail::resolve<input, char_type>(src), 
                              detail::resolve<output, char_type>(snk), 
                              buffer_size ); 
}

// Overload of copy() for the case where the source, but not the sink, is
// a standard stream or stream buffer
template<typename Source, typename Sink>
std::streamsize
copy( Source& src, const Sink& snk,
      std::streamsize buffer_size = default_device_buffer_size
      BOOST_IOSTREAMS_ENABLE_IF_STREAM(Source)
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Sink) ) 
{ 
    typedef typename char_type_of<Source>::type char_type;
    return detail::copy_impl( detail::wrap(src), 
                              detail::resolve<output, char_type>(snk), 
                              buffer_size );
}

// Overload of copy() for the case where the sink, but not the source, is
// a standard stream or stream buffer
template<typename Source, typename Sink>
std::streamsize
copy( const Source& src, Sink& snk,
      std::streamsize buffer_size = default_device_buffer_size
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Source)
      BOOST_IOSTREAMS_ENABLE_IF_STREAM(Sink) ) 
{ 
    typedef typename char_type_of<Source>::type char_type;
    return detail::copy_impl( detail::resolve<input, char_type>(src), 
                              detail::wrap(snk), buffer_size );
}

// Overload of copy() for the case where neither the source nor the sink is
// a standard stream or stream buffer
template<typename Source, typename Sink>
std::streamsize
copy( Source& src, Sink& snk,
      std::streamsize buffer_size = default_device_buffer_size
      BOOST_IOSTREAMS_ENABLE_IF_STREAM(Source)
      BOOST_IOSTREAMS_ENABLE_IF_STREAM(Sink) ) 
{ 
    return detail::copy_impl(detail::wrap(src), detail::wrap(snk), buffer_size);
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_COPY_HPP_INCLUDED

/* copy.hpp
h/wk1Zfj1On+GSHY853zPYvq2irXaWGTP1J2iF62/UJ1LJP0scrLlDfvBKhStL+e9xspLy8FYqcJe1vHNams+xjpr9YhbzLH03tYDuF8f0ErV+TBfrGNyuecqSwmiNQS+tk542dqbpNFCOd5GsVrrzQYM656m4+gd0KS3TRGMtrjKUrjs5ITJyfpOoPK5DZcvRszYosxC1JdXiwCFOxvoNQUy5R6wqnWMPa/iaA4vYsRkgtjpEjjLIwy5O6SXNCB1BWPGuP/XlQnGhiyzV/od508/VF90/unHNXlmWh9a5QNyn7j/dOT3Ffi9xxlrXJRCeB8O0txf9Km5ccWU571tR/N84yGJvlpGYWlGuO77fR7p8OOt4Ie7+BZN/qfg6Zwn5Cjbfq79wSlZZgz/3hzNj+nNMVtCMoceQVbFzOMGeAU2AXYKfND7Nx5BPYyrL9URtyL3OsKO0SqKJaDG2BzJMxKyshV2MpyddFH9oixsLNgV2CXh8/gfgz2ivw59OYucQHWptYW96oIC1aXbzdT/JsZ/esT1FcmGGN3la5PU9eJSYo53xqY3hV9KJ/WK26xUonkcOeSW1eU10vKLuUrZa1jrVE2E+lafzWA8/AJyi/KP9rTuyLV00wnv9eMPH5Fbh+U530SdyMO7Yz3Sa5DT9t4crMbaXuX3yV6WU7OvlGWuabnPCDhvcXvkjKUHxPUPM+tc+O5b9EzfsNzLxl18jtyW4L3WCklRhlN7W+rKfw8YdW+EVYQ3XcBYZ000tBUTwO3s6n53od3cRr0NL2Rzdf5/ZhN/UmaS6+b++i6jfL2milOu22/+XO/QF+Bt+I4vUTXS4QGow4sUe+WfrI1kZo6Sol+6IOfRSjvoA/+FX1wafej0k7PMIy/NsvlgmpK6cEjpR9CfhGtOB2PUzjfB5QVHeWJcry8SX1NHovx1mr0vx+jpfzmrCJVxxu7r7ui9IwnRrzr6SVVxfuwg3+qtC2gijEGt1F6fg7aiVnQCkoJuYx9v3QZ4+MZ7gMiym+b9GPAAUnXIf+Vyi4dI7bF7s4etzzF/7AxHhswlupsiFMMUHYoM+UsxzYpwn3Qodf7t+j6+yGXpJVBukzkT88uQ33zHlPeNRF+ISFcd3W39kr7IH2sO5T68J7yHrHFOOss8lFan2OcX3aE3pl7bPo7cje9N4LVM5j1PSCfzNNn1TO1vYv0Ln0ebW+e0fbiqH018YSKCcozygllsuNNGqvtN8UvR3SwB/BY8m3qj6rlHauZ+t6rFJeFaMsvKq8qR4x6nkTP7uooLfor05SPqH3vKKye17sRXvxkOjcDssRxxznHGEXvb/uS+1toNxspvutMYWUqpWRzeI1M/fa+fP22Sm1mC/rt9Q79/dKO242e5hN0z+cevc9pT2V70JEnznVvxPkKhTkBcT7juOiYZsS5MsV5I+L8gqLXk2qUXx8G3mhPLYzxZgalZ3aIP7QRgyCBfKbMlcbY7pWO2BOkKmhPLZ01pCmuUmK1q7/kRo7XQ5v6yK+vVAujl94BdaU3ML65GNRSahNSSugyzW7vuy5EFv6YG6gnj5W/kpLVmtJc2/3St3jb+ztipBYYZY12Npe2uJKlSpB126B9vQVZ9yu/qVJGQCvpWOATsj7e+ZX6iKZObSw5UM4RlxV/VZd3Rnnl2hJO8aL6m3pW2BzXEaZdXHR9oa4JHG6sZ3qa+nR/JUHqIV6SHMba99OUN/39neJn+Sre48/5ree+TBLesg4Tej5+Q8+KlfR1nn2pvh01zvO4SGOeaEnv2ybQ/cPlcG53qygd79h2IR3t5QNCf5+co35hjn+CY4ZaltufXs/aytPsiRjNHXH/1a6GtMpT5+o=
*/