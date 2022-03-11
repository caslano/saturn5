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
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
*/