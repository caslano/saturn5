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
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
*/