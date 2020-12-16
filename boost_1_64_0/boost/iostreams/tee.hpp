// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/config.hpp>  // BOOST_DEDUCE_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/device_adapter.hpp>
#include <boost/iostreams/detail/adapter/filter_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>  // call_close_all 
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams {

//
// Template name: tee_filter.
// Template parameters:
//      Device - A blocking Sink.
//
template<typename Device>
class tee_filter : public detail::filter_adapter<Device> {
public:
    typedef typename detail::param_type<Device>::type  param_type;
    typedef typename char_type_of<Device>::type        char_type;
    struct category
        : dual_use_filter_tag,
          multichar_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };

    BOOST_STATIC_ASSERT(is_device<Device>::value);
    BOOST_STATIC_ASSERT((
        is_convertible< // Using mode_of causes failures on VC6-7.0.
            BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, output
        >::value
    ));

    explicit tee_filter(param_type dev) 
        : detail::filter_adapter<Device>(dev) 
        { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::read(src, s, n);
        if (result != -1) {
            std::streamsize result2 = iostreams::write(this->component(), s, result);
            (void) result2; // Suppress 'unused variable' warning.
            BOOST_ASSERT(result == result2);
        }
        return result;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        std::streamsize result2 = iostreams::write(this->component(), s, result);
        (void) result2; // Suppress 'unused variable' warning.
        BOOST_ASSERT(result == result2);
        return result;
    }

    template<typename Next>
    void close(Next&, BOOST_IOS::openmode)
    { 
        detail::close_all(this->component());
    }

    template<typename Sink>
    bool flush(Sink& snk)
    {
        bool r1 = iostreams::flush(snk);
        bool r2 = iostreams::flush(this->component());
        return r1 && r2;
    }
};
BOOST_IOSTREAMS_PIPABLE(tee_filter, 1)

//
// Template name: tee_device.
// Template parameters:
//      Device - A blocking Device.
//      Sink - A blocking Sink.
//
template<typename Device, typename Sink>
class tee_device {
public:
    typedef typename detail::param_type<Device>::type  device_param;
    typedef typename detail::param_type<Sink>::type    sink_param;
    typedef typename detail::value_type<Device>::type  device_value;
    typedef typename detail::value_type<Sink>::type    sink_value;
    typedef typename char_type_of<Device>::type        char_type;
    typedef typename
            mpl::if_<
                 is_convertible<
                     BOOST_DEDUCED_TYPENAME 
                         iostreams::category_of<Device>::type, 
                     output
                 >,
                 output,
                 input
            >::type                                    mode;
    BOOST_STATIC_ASSERT(is_device<Device>::value);
    BOOST_STATIC_ASSERT(is_device<Sink>::value);
    BOOST_STATIC_ASSERT((
        is_same<
            char_type, 
            BOOST_DEDUCED_TYPENAME char_type_of<Sink>::type
        >::value
    ));
    BOOST_STATIC_ASSERT((
        is_convertible<
            BOOST_DEDUCED_TYPENAME iostreams::category_of<Sink>::type, 
            output
        >::value
    ));
    struct category
        : mode,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    tee_device(device_param device, sink_param sink) 
        : dev_(device), sink_(sink)
        { }
    std::streamsize read(char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((
            is_convertible<
                BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, input
            >::value
        ));
        std::streamsize result1 = iostreams::read(dev_, s, n);
        if (result1 != -1) {
            std::streamsize result2 = iostreams::write(sink_, s, result1);
            (void) result1; // Suppress 'unused variable' warning.
            (void) result2;
            BOOST_ASSERT(result1 == result2);
        }
        return result1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((
            is_convertible<
                BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, output
            >::value
        ));
        std::streamsize result1 = iostreams::write(dev_, s, n);
        std::streamsize result2 = iostreams::write(sink_, s, n);
        (void) result1; // Suppress 'unused variable' warning.
        (void) result2;
        BOOST_ASSERT(result1 == n && result2 == n);
        return n;
    }
    void close()
    {
        detail::execute_all( detail::call_close_all(dev_),
                             detail::call_close_all(sink_) );
    }
    bool flush()
    {
        bool r1 = iostreams::flush(dev_);
        bool r2 = iostreams::flush(sink_);
        return r1 && r2;
    }
    template<typename Locale>
    void imbue(const Locale& loc)
    {
        iostreams::imbue(dev_, loc);
        iostreams::imbue(sink_, loc);
    }
    std::streamsize optimal_buffer_size() const 
    {
        return (std::max) ( iostreams::optimal_buffer_size(dev_), 
                            iostreams::optimal_buffer_size(sink_) );
    }
private:
    device_value  dev_;
    sink_value    sink_;
};

template<typename Sink>
tee_filter<Sink> tee(Sink& snk) 
{ return tee_filter<Sink>(snk); }

template<typename Sink>
tee_filter<Sink> tee(const Sink& snk) 
{ return tee_filter<Sink>(snk); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(Device& dev, Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(const Device& dev, Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(Device& dev, const Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(const Device& dev, const Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED

/* tee.hpp
e73IOjpvujJnBY8P2utlehL1Mj3JeplurxffXuUb0e3ZgK2eTNmj8eSLblW15isTni/X90vvRy7UDoyjks9fhu2txN9WzwPO7AXueY4xxortitqs3fyWe22Znnth15Mx2BV//PHHZZLe8HQjrT788eUvfVvGdAM2+eXI/yjyPwW1nDkmT5Dv81pPd8r1LdMznbrgj8FeZp42M8vsPkmnr5576awr6SwjHUfyvLQhHanPKX57qJF0LmQcoxMy+PlxdDXTLOCPxLmSOJfU14WRdzE98O3QJ4lOOU54mhV+2eSITudZysaLr4IEG/L4pcQ3wM/jTRK+l9PSD1/q20v1kmsnOHtpmdjDV/hxV7nXLGG/5Hmwle4P+QlK1+HyKbCNItxtXL/WZ7S7Dnc9bmPcJrhNcfvhblB/jz9n28Lg9NoPxnWP+Em6R/F/H9zsUMN5gTr8osLgJF+bcU7e5HlnPvBCa+F517Df5V9vV7BM7AF+TSua126Xivuv23vEvb8Unnh74+2H/lfv8263c0h+XD5Zu4Jk7QTsdiPJj+/b7Qdi213IOK33Ltd+S3Gccdq2sDvMhD3gd7AiTd8x+p4thnvgShv2C5Lx483gerAf3ErHo3aET8FddBxqMOwPh8Ot4IFwG1gCB8CxcFs4BW4Hj4Lbw9NgIayBO+l4/0BYC3eFD8Dd4Hy4B/wU7glXwiEwA+X3hnlwONwO7gNHwJFwAjwI1sAieBssgc/BMfAdWAaXa7hW5P1gGILjYAGcCPeC5bAYTobHwCnwUjgV3gynwUfg4fAJWA0XwCPhl/AouBQeDb+Hx8AfoayzFFS7CngqHAxPh2PgWfBQeA6shDXwWHgePAeeDy+BF8Or4GXwBjgT3g6vhPfDa+EieBNcCmfB5fB2uALOhsH0+vH5DnAOzIFzYS58EG4Ar4MF8BG4B3wU7gkfg8Ph43AUfAKWwafgeCjtJM2Jt2+p7m2a3DpN/9V9TFN73sfez3QR4y7Nm6TGXv4Jx1r6/c8cpjX//e/O/2/bi2coL6OgIybNVZVFlSQ7uZznuFxv517f3rx+yLTyMTK3Sb4f3GR8PyhVm6HN6uH00bXUQ/W/U3ceNqxo4uSS0iKNCV2m+vMPWhDD8SFcgnPklsPcQKy+V+w+Vrd5rv/ld44+ccvKVy7NPu1957NT966J3Vez98li9Y0abw/vZPtM8fpGgxytA62bgnDbC3nXebZoGXAO7Arvgb3hXNgH3q99i+r1GQfG2ffVlvfR37Jm4D9pvcC566eex6kjdaSO1JE6UkfqSB2pI3X814+19Pu/tKyislH2/7/FWN9vpX7rvkLzMRPXwZ2r+7p1/N8yRmyZr4usN0bczTHHiO1jymb49r1kjLhk4sTRJWMm2MeUzfDBdAk/uogp6tbxfglvmVerY6Fj5dp+/jjoY3LeyR+vdojbMcac95Dr5znTzHVzjPH2bDhMwpzuTHLSGsYfjfUd9q8vW6eU0vLWySlBmWIdU7wVzsKN0bG7UuXL8n8i65M0aU8+dN0bHcuzjNs11zmUxridP55HPeDv14P4h7z1ALS81/aY3gj5jjM5/dYrbpnx/Lmvfv7cZYsu3e/K1Jjef2lMb653v+ozqVjnYM7CeXOu0uF6sBXMhRlwfdgJdoc9YT7cAG4Et4C94UD13x0WwJE6tjcB9tWxuX7wSLg5nA4HwONhf3gq3AqeDbeGF8Nt4EwN1381x3YixnX+02M6/4bxnLU9lrMw9d0wdaSO1JE6/mTvPACrKNIAvK+kkZAESEIExFCkC6GDIEVAQEBAECKiBEjoKUCAeKJySImAGhUUFRWVO/XkNFJOVFSsgAViL8cpCnp4onI=
*/