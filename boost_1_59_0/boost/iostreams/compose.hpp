// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Note: bidirectional streams are not supported.

#ifndef BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <algorithm>          // min.
#include <utility>            // pair.
#include <boost/config.hpp>   // DEDUCED_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/direct_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>      // mode_of, is_direct.
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

namespace detail {

template< typename First, 
          typename Second,
          typename FirstMode = 
              BOOST_DEDUCED_TYPENAME mode_of<First>::type,
          typename SecondMode = 
              BOOST_DEDUCED_TYPENAME mode_of<Second>::type >
struct composite_mode
    : select<
          is_convertible<SecondMode, FirstMode>, FirstMode,
          is_convertible<FirstMode, SecondMode>, SecondMode,
          is_convertible<SecondMode, input>,     input,
          else_,                                 output
      >
    { };

//
// Template name: composite_device.
// Description: Provides a Device view of a Filter, Device pair.
// Template parameters:
//      Filter - A model of Filter.
//      Device - An indirect model of Device.
//
template< typename Filter,
          typename Device,
          typename Mode =
              BOOST_DEDUCED_TYPENAME composite_mode<Filter, Device>::type >
class composite_device {
private:
    typedef typename detail::param_type<Device>::type       param_type;
    typedef typename mode_of<Filter>::type                  filter_mode;
    typedef typename mode_of<Device>::type                  device_mode;
    typedef typename
            iostreams::select<  // Disambiguation for Tru64.
                is_direct<Device>,  direct_adapter<Device>,
                is_std_io<Device>,  Device&,
                else_,              Device
            >::type                                         value_type;
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    BOOST_STATIC_ASSERT(is_device<Device>::value);
public:
    typedef typename char_type_of<Filter>::type             char_type;
    struct category
        : Mode,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    composite_device(const Filter& flt, param_type dev);
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which =
                             BOOST_IOS::in | BOOST_IOS::out );

    void close();
    void close(BOOST_IOS::openmode which);
    bool flush();
    std::streamsize optimal_buffer_size() const;

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc)
    {
        iostreams::imbue(filter_, loc);
        iostreams::imbue(device_, loc);
    }

    Filter& first() { return filter_; }
    Device& second() { return device_; }
private:
    Filter      filter_;
    value_type  device_;
};

//
// Template name: composite_device.
// Description: Provides a Device view of a Filter, Device pair.
// Template parameters:
//      Filter - A model of Filter.
//      Device - An indirect model of Device.
//
template< typename Filter1, 
          typename Filter2,
          typename Mode =
              BOOST_DEDUCED_TYPENAME composite_mode<Filter1, Filter2>::type >
class composite_filter {
private:
    typedef reference_wrapper<Filter2>           filter_ref;
    typedef typename mode_of<Filter1>::type      first_mode;
    typedef typename mode_of<Filter2>::type      second_mode;

    // A dual-use filter cannot be composed with a read-write filter
    BOOST_STATIC_ASSERT(
        !(is_convertible<first_mode, dual_use>::value) ||
        !(is_convertible<second_mode, input>::value) ||
        !(is_convertible<second_mode, output>::value) ||
         (is_convertible<second_mode, dual_use>::value)
    );
    BOOST_STATIC_ASSERT(
        !(is_convertible<second_mode, dual_use>::value) ||
        !(is_convertible<first_mode, input>::value) ||
        !(is_convertible<first_mode, output>::value) ||
         (is_convertible<first_mode, dual_use>::value)
    );
    BOOST_STATIC_ASSERT(is_filter<Filter1>::value);
    BOOST_STATIC_ASSERT(is_filter<Filter2>::value);
public:
    typedef typename char_type_of<Filter1>::type  char_type;
    struct category
        : Mode,
          filter_tag,
          multichar_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    composite_filter(const Filter1& filter1, const Filter2& filter2)
        : filter1_(filter1), filter2_(filter2)
        { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        composite_device<filter_ref, Source> cmp(boost::ref(filter2_), src);
        return iostreams::read(filter1_, cmp, s, n);
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        composite_device<filter_ref, Sink> cmp(boost::ref(filter2_), snk);
        return iostreams::write(filter1_, cmp, s, n);
    }

    template<typename Device>
    std::streampos seek( Device& dev, stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which =
                             BOOST_IOS::in | BOOST_IOS::out )
    {
        composite_device<filter_ref, Device> cmp(boost::ref(filter2_), dev);
        return iostreams::seek(filter1_, cmp, off, way, which);
    }

    template<typename Device>
    void close(Device& dev)
    {
        BOOST_STATIC_ASSERT((!is_convertible<category, two_sequence>::value));
        BOOST_STATIC_ASSERT((!is_convertible<category, dual_use>::value));

        // Create a new device by composing the second filter2_ with dev.
        composite_device<filter_ref, Device> cmp(boost::ref(filter2_), dev);

        // Close input sequences in reverse order and output sequences in 
        // forward order
        if (!is_convertible<first_mode, dual_use>::value) {
            detail::execute_all(
                detail::call_close(filter2_, dev, BOOST_IOS::in),
                detail::call_close(filter1_, cmp, BOOST_IOS::in),
                detail::call_close(filter1_, cmp, BOOST_IOS::out),
                detail::call_close(filter2_, dev, BOOST_IOS::out)
            );
        } else if (is_convertible<second_mode, input>::value) {
            detail::execute_all(
                detail::call_close(filter2_, dev, BOOST_IOS::in),
                detail::call_close(filter1_, cmp, BOOST_IOS::in)
            );
        } else {
            detail::execute_all(
                detail::call_close(filter1_, cmp, BOOST_IOS::out),
                detail::call_close(filter2_, dev, BOOST_IOS::out)
            );
        }
    }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which)
    {
        BOOST_STATIC_ASSERT(
            (is_convertible<category, two_sequence>::value) ||
            (is_convertible<category, dual_use>::value)
        );

        // Create a new device by composing the second filter2_ with dev.
        composite_device<filter_ref, Device> cmp(boost::ref(filter2_), dev);

        // Close input sequences in reverse order
        if ( which == BOOST_IOS::in &&
             ( !is_convertible<first_mode, dual_use>::value ||
                is_convertible<second_mode, input>::value ) )
        {
            detail::execute_all(
                detail::call_close(filter2_, dev, BOOST_IOS::in),
                detail::call_close(filter1_, cmp, BOOST_IOS::in)
            );
        }

        // Close output sequences in forward order
        if ( which == BOOST_IOS::out &&
             ( !is_convertible<first_mode, dual_use>::value ||
                is_convertible<second_mode, output>::value ) )
        {
            detail::execute_all(
                detail::call_close(filter1_, cmp, BOOST_IOS::out),
                detail::call_close(filter2_, dev, BOOST_IOS::out)
            );
        }
    }

    template<typename Device>
    bool flush(Device& dev)
    {
        composite_device<Filter2, Device> cmp(filter2_, dev);
        return iostreams::flush(filter1_, cmp);
    }

    std::streamsize optimal_buffer_size() const
    {
        std::streamsize first = iostreams::optimal_buffer_size(filter1_);
        std::streamsize second = iostreams::optimal_buffer_size(filter2_);
        return first < second ? second : first;
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc)
    {   // To do: consider using RAII.
        iostreams::imbue(filter1_, loc);
        iostreams::imbue(filter2_, loc);
    }

    Filter1& first() { return filter1_; }
    Filter2& second() { return filter2_; }
private:
    Filter1  filter1_;
    Filter2  filter2_;
};

template<typename Filter, typename FilterOrDevice>
struct composite_traits
    : mpl::if_<
          is_device<FilterOrDevice>,
          composite_device<Filter, FilterOrDevice>,
          composite_filter<Filter, FilterOrDevice>
      >
    { };

} // End namespace detail.

template<typename Filter, typename FilterOrDevice>
struct composite : detail::composite_traits<Filter, FilterOrDevice>::type {
    typedef typename detail::param_type<FilterOrDevice>::type param_type;
    typedef typename detail::composite_traits<Filter, FilterOrDevice>::type base;
    composite(const Filter& flt, param_type dev)
        : base(flt, dev)
        { }
};

//--------------Implementation of compose-------------------------------------//

// Note: The following workarounds are patterned after resolve.hpp. It has not
// yet been confirmed that they are necessary.

#ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //-------------------------//
# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------------------//

template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(FilterOrDevice) )
{ return composite<Filter, FilterOrDevice>(filter, fod); }

template<typename Filter, typename Ch, typename Tr>
composite< Filter, std::basic_streambuf<Ch, Tr> >
compose(const Filter& filter, std::basic_streambuf<Ch, Tr>& sb)
{ return composite< Filter, std::basic_streambuf<Ch, Tr> >(filter, sb); }

template<typename Filter, typename Ch, typename Tr>
composite< Filter, std::basic_istream<Ch, Tr> >
compose(const Filter& filter, std::basic_istream<Ch, Tr>& is)
{ return composite< Filter, std::basic_istream<Ch, Tr> >(filter, is); }

template<typename Filter, typename Ch, typename Tr>
composite< Filter, std::basic_ostream<Ch, Tr> >
compose(const Filter& filter, std::basic_ostream<Ch, Tr>& os)
{ return composite< Filter, std::basic_ostream<Ch, Tr> >(filter, os); }

template<typename Filter, typename Ch, typename Tr>
composite< Filter, std::basic_iostream<Ch, Tr> >
compose(const Filter& filter, std::basic_iostream<Ch, Tr>& io)
{ return composite< Filter, std::basic_iostream<Ch, Tr> >(filter, io); }

# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //---------------------//

template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(FilterOrDevice) )
{ return composite<Filter, FilterOrDevice>(filter, fod); }

template<typename Filter>
composite<Filter, std::streambuf>
compose(const Filter& filter, std::streambuf& sb)
{ return composite<Filter, std::streambuf>(filter, sb); }

template<typename Filter>
composite<Filter, std::istream>
compose(const Filter& filter, std::istream& is)
{ return composite<Filter, std::istream>(filter, is); }

template<typename Filter>
composite<Filter, std::ostream>
compose(const Filter& filter, std::ostream& os)
{ return composite<Filter, std::ostream>(filter, os); }

template<typename Filter>
composite<Filter, std::iostream>
compose(const Filter& filter, std::iostream& io)
{ return composite<Filter, std::iostream>(filter, io); }

# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//
#else // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //----------------//

template<typename Filter, typename Stream>
composite<Filter, Stream>
compose(const Filter& flt, const Stream& strm, mpl::true_)
{   // Bad overload resolution.
    return composite<Filter, Stream>(flt, const_cast<Stream&>(strm));
}

template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose(const Filter& flt, const FilterOrDevice& fod, mpl::false_)
{ return composite<Filter, FilterOrDevice>(flt, fod); }

template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose( const Filter& flt, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return compose(flt, fod, is_std_io<FilterOrDevice>()); }

# if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600) && \
     !defined(__GNUC__) // ---------------------------------------------------//

template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose (const Filter& filter, FilterOrDevice& fod)
{ return composite<Filter, FilterOrDevice>(filter, fod); }

# endif // Borland 5.x or GCC //--------------------------------//
#endif // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //---------------//

//----------------------------------------------------------------------------//

namespace detail {

//--------------Implementation of composite_device---------------------------//

template<typename Filter, typename Device, typename Mode>
composite_device<Filter, Device, Mode>::composite_device
    (const Filter& flt, param_type dev)
    : filter_(flt), device_(dev)
    { }

template<typename Filter, typename Device, typename Mode>
inline std::streamsize composite_device<Filter, Device, Mode>::read
    (char_type* s, std::streamsize n)
{ return iostreams::read(filter_, device_, s, n); }

template<typename Filter, typename Device, typename Mode>
inline std::streamsize composite_device<Filter, Device, Mode>::write
    (const char_type* s, std::streamsize n)
{ return iostreams::write(filter_, device_, s, n); }

template<typename Filter, typename Device, typename Mode>
std::streampos composite_device<Filter, Device, Mode>::seek
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return iostreams::seek(filter_, device_, off, way, which); }

template<typename Filter, typename Device, typename Mode>
void composite_device<Filter, Device, Mode>::close()
{
    BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    BOOST_STATIC_ASSERT(
        !(is_convertible<filter_mode, dual_use>::value) ||
        !(is_convertible<device_mode, input>::value) ||
        !(is_convertible<device_mode, output>::value)
    );

    // Close input sequences in reverse order and output sequences 
    // in forward order
    if (!is_convertible<filter_mode, dual_use>::value) {
        detail::execute_all(
            detail::call_close(device_, BOOST_IOS::in),
            detail::call_close(filter_, device_, BOOST_IOS::in),
            detail::call_close(filter_, device_, BOOST_IOS::out),
            detail::call_close(device_, BOOST_IOS::out)
        );
    } else if (is_convertible<device_mode, input>::value) {
        detail::execute_all(
            detail::call_close(device_, BOOST_IOS::in),
            detail::call_close(filter_, device_, BOOST_IOS::in)
        );
    } else {
        detail::execute_all(
            detail::call_close(filter_, device_, BOOST_IOS::out),
            detail::call_close(device_, BOOST_IOS::out)
        );
    }
}

template<typename Filter, typename Device, typename Mode>
void composite_device<Filter, Device, Mode>::close(BOOST_IOS::openmode which)
{
    BOOST_STATIC_ASSERT((is_convertible<Mode, two_sequence>::value));
    BOOST_STATIC_ASSERT(!(is_convertible<filter_mode, dual_use>::value));

    // Close input sequences in reverse order
    if (which == BOOST_IOS::in) {
        detail::execute_all(
            detail::call_close(device_, BOOST_IOS::in),
            detail::call_close(filter_, device_, BOOST_IOS::in) 
        );
    }

    // Close output sequences in forward order
    if (which == BOOST_IOS::out) {
        detail::execute_all(
            detail::call_close(filter_, device_, BOOST_IOS::out),
            detail::call_close(device_, BOOST_IOS::out)
        );
    }
}

template<typename Filter, typename Device, typename Mode>
bool composite_device<Filter, Device, Mode>::flush()
{
    bool r1 = iostreams::flush(filter_, device_);
    bool r2 = iostreams::flush(device_);
    return r1 && r2;
}

template<typename Filter, typename Device, typename Mode>
std::streamsize
composite_device<Filter, Device, Mode>::optimal_buffer_size() const
{ return iostreams::optimal_buffer_size(device_); }

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_COMPOSE_HPP_INCLUDED

/* compose.hpp
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
*/