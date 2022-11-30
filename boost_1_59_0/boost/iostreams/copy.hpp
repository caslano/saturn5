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
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
*/