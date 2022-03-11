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

# if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && \
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
JVtKHcp/iGVJWF/upvdOaMkSUpzLZ+dl/9lsnjFt+UsDcKq6OheJWjmSJipT8AsSX/lfritfVMtGJuooSNABzNUohC0vPKNUb7jR/tmRPqi741hE4hLv7oas6tZ9iBZR5XANPUaoQeEX4DiarOnYKUblyNdXyknhNny1q6h9bD8Z/sqNseF+wcSdptrDV5+0DF7Tjn4g1De5fRcZ+XJoeHWeF1U+uLUE0LR57+3AXyoGhgZaXhWWVrEH0TK8PEBllLT5pk6lLcYNQGpKBedc7fPFD4NCZvJlUXEm1hkL4BL9vj6uyw2QcYshHNLsyi+ei75Grx0e1ljaaNIlMcz0Ewblwd+cSJ900N3CKLcR8QINwEflbVHhPMA8ftootI6P1ONpL/zkrsNgYGE6p0GSTNMoqEKPZlTadVNOeEfRr6mEkLg7Sli+UPiq7oa9ES6LjA9Wams40xWdeblHGJGLWNyic7NBHFyDl7kn46Btr7VyR7Gb5ZJWPVWNtPrXVgayrg1qPWRHHL/McquM8nUR5EWSdNOzRRVhouJV0FR4eKUCjCDn51B9OGTd2tfor3KO1H60HGVOXlBpAwOrc/LU4H23Cs6L1mBJie2zf9to0l3EUDCTpxni2lHcth4uj3fokpAuH5obPfOt0Pb0SeqW9MP86OZ6PImUj+yaUW4PiY5yV4+ropbEv/1cUT4aMIthkbGmx3FpwMe35Oz1ZG7VxvfJyXjpD/QqkMkLLL/2Nx3BeatVcwS4dDS2EUDtwG0+8mOUCSyZE72E6JpILbQxkJbmeIWOiXC9LnMLMy+7+YgzPr2M+kmWZBb6NPH507d7Dx74b07hbf92ayky0l/fl4D5fF39v1d28NOWs+YwbKJPQ3WA/dnQja1QL30wDR0ziiBNXHMsWy+ppPd5U0pmyhea36Hl7RRK4/0wEMLNn2x+kQOHBeS2/1lxBP2XIRYke9a7222Kx2MIhqEiXE8vqlEXmyDxH/4chxAOJb7mT/RPP4KoYlDv6RNFNivkruvIjsFTzIlBahiy2VK59Gkfq/C2CFRTynzDv9PxjPQFCqJQ13zCm6F3jWr8fcYjS1U1361ZwtY+MIK9izYAt2xX5cqvMrPxziEkfnXWlK0fpncR3mooinlkWI3XC3v5RWuWUnxGOjj4VaW4Ddmm/MSWNEAFsIoht9vpjzDgzKVq8YoQkOfqT/n6jA/ucLFGULixGrnl8g9TPIfca4qlIYguoCOOP32Aa59Ad8FKxfXdykjMCHBqXQ5obaB6+6iP0195rF8EVy+fx36Xk3WEX1RYIG+on8PUay1oEgpZdM2TBuMmxO8lHg3yY0I5F+hcSm+c5aKWoxcIUtozutbbj8XnU5vkO3xakyW9ks/1RV0MRBlP27WmFbIrTifbBon1q/kycaXZ1EFTiSFOu7U2jlpfLdcdTXYtQVwZ0IidXsE/o3CAFm4SJi2hZ4/bTQuwOQolNcdb6P+KJLM9j6bQkSFOBprp+yHZ719HCKLsiw+yCzrptSHUvlw7klFu4Hd8Rp9yjnLNVhrifq1owl4Sj9M7Ul1/GOXYG5xlcT1iVCx0Iw+a4u/yjWHcQ36nJ/jZQidSj0pRP2uKEOCHhi1tEVKmvZwYe80kFgzkI4UyuBQ7TPiA3k0Pulfh9Tbl0e+MLdlxT0JgNIPBZyEmG3eO7DKRuFIZqmc4uTjldJpbvrzuI50H1KmMC52XFyJH2h3+RRBmUNflg1FgzcaXp2i2rT7dsfmLmFuOHRV3UeGe+2a2Nnu3ne7lG13Im5IuDSdpckQ9HK5lfKBYlEdQLXvRAGqxbZVzuzHaKip4GgrDzahDWu5Pf740Bl6XEU5Y7U47UtCp0MYvb64rffhH0e0GABWW/Ci6Tid+MFz6f08oPG8SQ0LcGKPOBQMi7M4GpAgcKJsnfFI0Y0Ygu4JWTQCnauxjhpymmMzFVUQ5EoxSYQ39vVbfw/wSM08mUkWkuDezKD7xr89b7pVJ7C+xdQFtgtL2JVO0pUHjWsU6E/Ql2zWtVRCinCGWlBVb1WjdQtuDpiQM/7aYyeWO2SPZCnhqgTE5njlCZ8W2lsInAnXSbF52zEas9ECX1vmaoRJwVcsVRCHNX2Utmt0clATKArieq65H811ypFdmLovr3uSAvX1SrbK8T40m9vLODYf3r9yO2nBTbnDNbo+BP1XntgmeQXPANmahfFRQ1IAEVfNocPWU2IIvUCdPk+VZfjJ9qCZ0UihrVaG7AUWrxfFSoQmhTy6D06pABZRLxJQeST+dLL2vo0qlVK0Kp5gCyHkNq1UNCJkD2roW4PMM2st0c4qbroqx6OBmVsZgYTbeWiKaAZGl+NOVtFMhoMASDVS2cu0aGGE8nkJK9NP97bmrQbgSaexG38RXEWvu0PlHdjEUfPPlhtnEA2uGsxtTqlBoqdLZuiHRhxKB4JnFPQY0tothmDONP8Opf0hqTeQ/i4UWBAXxbDd2QHFPBVIoLAe90JkpdUPQBrC5Rl2LjKzvbColVNWuFy9/w4MKTWB0tyxGrWpLaHxJ5nfXbLVOjphKy54/k4o2LmK1U5zhzY+8zUcWqa6suKbF8U7PQldP66ipG7DScTRLQRFMmJNdq1nGglUi54ObZZqTpQNJHma7flu+zOvoJGwl3XaD5fQy+olzAHgSwCm982ZGKE8ZKqH1ZgwnKJPIFH2A6+aQGv+1aQJH67XGGk6fdCXQllSTLkKpza2v0dalhQWL855bjarpe1fQnD7COj9i+YJHg86ez2ULajQgP+2SVUduYCbFlWMibLkU0208iPi7z1SEOohg9LlzmvQf9P2I2wAlL1rIifnM4laY4gvypm3MqcQsajA8Giirth94HIKjN8dH7rVlNiwNaMqEX+B5Z1RatxdsjFySOw2V12PryI29X5Svd2jAvIbw3AUOTIe1FiljkoNzVzdJJ64IulKZ5fVp+HI+LbDjHMUNZhY6cWQolRShQu/MNcxVVEKeryeouZ7LSCgaKGuRfW30495VAaVSvqqGClIHLlgHakiWO16GRJG17Q050VOIvLwGW2LUuY6Fo6REvfzk7pW28PNKKwWK5Dfx83TXvbiEBRH7ObcQskfSE5g06E/GTXKiM7Yx5cRshzFbj6XevXakw+JkN1k+a45jwRm4lUEiSYzparz/coQLa6hlYbAbk0gJBBqfuNcR6qeO/wkWoVM1ITAYhQ4Vt63t25LKxWVn6vgSkfXpXi0XC/ewE45YnpixisSIqumwWVRyij73pBt6vqfIqFCqzmypmkJD0UB4zgS+tfa2P9g7fsvtzpx6ozlab8NTH4wMp26Wj/ZY8TyexhPPRRkmjKLW0VtpcAwv6T6f7qyF12Yig+P5tv2xcXTxD2hakXIUy4rz+DOW4AViYs7EC8TFNp4sMvu52+W5o475m+L4YMVomKPe2f9xGKt4ltPK4iimiTaXBuGhHlywn2Fc27s2tpsKJqC1lAR7rVtalYCvjV24kc6bEMOgxtXKnbXB6WF4A5uAlkY4B1BtMp1cMtrM4qqUUfZLNFBJTxnVGzRM4+coS23Fj9LiCiGU5X6mZ+rwRMO53hIXoxepUrd6vcEp2pkl6kub6T6m5uHS7RfjxmFgdBW+PHfz7HHXT9g5Ijhb2TuuV5Jw2vmG5T7h1W2JxV4mZybUXodU8HveO/NZM2SYlPcp2p+NYTzaoyv26THNLhpEy/S8znrK5+5krtn2x0E3gSCznLIJq2CYyTAjAQkKsLGVCM0EpS2R9H4WhYhW3DEL/aNVymqr3S52EVJo6l7llFV9V/Iko5z1UjaVXHUqqNSFE5mKLPLEvVTbwfMEAVVPVG39gTrX35oGFRMgC+duTQtm2k8zMXb6GRYe9TAhvZ1FhS7TqXNtynTTsF7Zj8BZfbgvP4UTISJmoTuFXt5VejYYg9YnArG2F7LirRx1aaKnCC7u04btX0WEO2GZg3An0MaEU1m+BQJwBUDNRN0RqxF7RXEbkMm7tvcJkSNxbdwNXuCz4297xu+vxEwtGfYws0+8yR5MOUQzvQdDdG2UqfskhwTgRvfTtzhe1VxJ9tu4YcXGrrSLu2aTD2sWO7oW0yndpegNMfV3ImcDtO5cWBLj9rYYNOsar7mxJmrsltHZj3yuXttv74C00KXpWGD+QwYuI9pSoVLAjsncxxOvLGBVKDEEx5bSMLjBLz+BXcwk7rim9M4cTCfWupgNp6s25d5IzDTc/JVcO8IgW0+bXn7mukfBFGOsRdpZNizOMytmG917NmExABOXPvlMv4/zyDpdzkJjnklXNcJER91mS9A/NLMYF7m2gZirPC/CGJ7ujn9jZzKiODWZFuASqbYwOq9xWx/Pv8EFDZt8WSJJTZxWF+sq0ZfS4+5QGZom+6lggZ27CXI2hOyq4fcXbJkULSPppSbmKOZvMUDYJdM6KiZwdejkUuNSi0WD5dRCg/lrc3DTF4Zt6MtnqqVwc2yBM02k25dZfUS2B1EcFPbl6ERgCxr+dpWjWk+KzutCjjrgz1+uOwo86AqBoQQm+bkXYMEjRg86sxf5jCd1aCJevgYZ5LXpMa4lIyBx9AybCiwXLbQNnHPLCGsbaxURUxAuEZJ5ylORpECjka9lL9qb9JgNte+iOjgQzw5GOfymJ1uySCjs4iXA1RREFdZZIoHLDRGhVhUgaOtWolBUeUWl3q0H8yDjkWHGSmyDrIVq6OjYdIx6iLkNqQyhU5rtd46Leyg+CKMEd20KC0MQ1Gqg8nSaJugpauV/XQ3CmKvcqPlGCnW6oBnprLGjRJT6Ibuycq/9veQesxzZEI9cT+QCvn/TIYGbE0eZWwaCOBnC61VaFFEfydxz5re9VglIs429U7m5b8noTw0tIbgu4d6QNz/6R/mQ69zgdkjW2xnsMFU7ch5keC05L7xjJTqt5TofzhOvW8UrLYvs6ywrzI0ZQwnAcyXxQmlaNDhFyMRszFXLA+zmW8YqQeSdS9tH1aGWsIkXOlEchEEoUmOnOW0VXd6mH2iD9rCGQpfIe/Wlm3nONMLPLtF4zlBd7+qmwlj7OZVHhV01lui8tJVpSAAQz3ygmguCc6ZYpioW+arphSpd5XwhV+WimBua57ieaIJkpg0Ny2tW7heOJC/2WLZ5j48FRggK46t8K7d+t5Fc2Xg1SgdChf/BpH3gUjNextuzxb7Wri2p6/Wt2h+wp3XGdaGIaSoOqbZuNtrV1tVh2jnz0CQDBm639G0pyMX2JL8PfQ/7pEsMfJMLJQKDREosojbovw2sint6Sfa553X76y2XHU+83x9Z+nHEDUrkdfLRn9g+VKjo0SZlkpjPIhT8TvE1LpEo68IUTQuEwoARbAZLv14mWl5A+RLT0LuLGyh1JhBixr1lsC0wq0+bbQjySbybdal/Nid5D4jI0TNviWGzIUra97PRLLrcuT2cjllUuomzX+DLkQpEvizHOYXGHaBSosCIJLn8TkN1sSo4fHTWjGO9E6nsPvnZ4o1Wo2bRT7BzvDNOK7Ugl6nVaNl4PvaqmjYB3ah3FXMqouPoAb7CJXjjlp+N4/wp633AbmqaI2ALkb3pTCR3j4kem6/pV+YgOdnNLDZROlyoQwvMtOq63US+olHSRGHbytzexF8g3SfyPA02FH9Ww4ZWsYWRZBBeGiK+m5pPgIJRJokauLTF4DRAOU/xlNH2sBLTIni9dGoUhDOk7Rd3mYe+aXUTmuBV3cKuFwA+yc8SbTVPJQH/ZGqTN+hIQkWwluufPuCkU/ZHsezs6VlUUrUWkfoumpO9fOIIDhTaSYzo6SpOtcyHewKqm96mF1j5/e7T6gjCzgdZrtunOMJM5Q7CvMei44ANO9HiEiZadpufMy8YjZ83IyKJyY7bjH8L0gQAXLU9rFNEMf1AUFRxp4S94J5wXnDi5P6jgoOid3iTVzY6P/XvPTcnZmQkkzWDGTfDBvfwee/dvtoCfxeOAxQwDjQBEhYNSIYG8Ln3kZg0llOqq/8LQbZr0E8Z9DKTZcf3WXiE/m19KZjbaFLF1Hp47zekQm4Op9sB5hMZSSC+uHp+b37ea87zPm5YXNQLT4qXl0rfapC9MI5TQdynQ9xRCwL/gkwonn2VtNoUUusE48hktnxr/OSuTXYt+AIrBMh/rSRO+IMxD7+t1WxTjU/dpBWOXMnxsK75lgvHtCGbWmP+6GswU1KAm6/zFBUqzBtE3pVQqsAwqRXcS7hi8VVwBWrOvCCqzVWuAwXCvRFwr1kb17Do+fbEzjguBsUC/PKfxqdO7x3Q1gPA+k+QDZa02fq+hnwcps8ycUtv6D5klgK/NoAyQQy0pGEhUWvjy7DHrcpaA6pON7MOmWE2lk8Vet6Ge8+Dzd76a6DyKppYV1ybmY0BataQdeL78OdZnuZ3JLjdvI/czvbp4L4mLDc7JlOuMudDaAmqFipK1g4nCO7TPVRZG2p173U8bc2zX47c6/Slcm1bZtl9Mrk6sjRvB/8MmRQXjNUzyTqE3R3Tdouum5WzZJf4ZJCHdYI4pWen11SWNYwcGLXsuztYEjzGeDaRbPDuIc8u9WxD4MGtLTP9bwnMJxdtvlmo5wkZrjL65JrdO8dQwRPm4FuJq4OkE3OGgIvDIyMVFAjA4LRkP3kK3BiHEd/nz3tCeWws86USMf4TIhA4ydyyyH2oMMjo7G5tfb4AhDIGwj2eFnJ92ToDvV/czdKv4UES/5qtyqeOGjqqW60Wi/ZwyXsENuw8MhsUbJtU0p0ZCFl8e2IPS18MZhFB7e+JZ0cJgqV2a9heML6JYmIwplApriX7SpcQ1K+qSUKAQEtHKcTKZGDngidfutaGXUVO7sXH5O3eT4JiAxWwoWbzPGHWWNXVnG+CDcLzcMg3pbKbJrhgVL6oW/mj3c3YBZ1DLUd90+s+Kz3Zz2HJ5V2N5HTIQo0LUm99dl/JJUCP3J37qLFgTlG1B61iM1ciTT/UzSBOL51mo4zUKnxnqbIE5yV5WPFWV857Oe1g6YfacUK3BFKHcKAgrZVbVPqWQbo+DQ9GCsQSjdlZL8pgIEV3PR2VBuz8KrChJWCEPUvSUn+xITJEBXqAgtkZcd3BG91z1afgQuQlDoFiY9K5Ms8D8NK1iRemH42SQlX0BDZu+3ljQx/v2WaB2W5ow5kNXx1IQ0lzucA2dJrTuwbkG9/PbrWY0qI5pfFtp7ujzHrnpMBmdpHNvGMO8gxBC7YIdW/ywVvaa4lh2hk/MVRA2Fy+uKyDQrrHz3RXuP8KHNkjB6fAlbhk58TB1YeSkcMV8JZnySsoXJp2UHCiWW86OVXJFP+GPG4SdgY/V8C1ylsPhDm9trdF+xQBTyOgdHc4hUdjes04QR4bQp0PlFSLvd5sWDyr97hr2ziRxiY2BmuqYifIJJrxu7E2kMAp0OoIhmzDkvHiNzpAaWwk/kxYpi705sv1TDx964ONT1McZsjhXKpU0EbIvEWGZKwecO1drRGBTjFHTRFVdsvbqeWG3GO5U+W5j6FKyqPqW7MSLqZFG/GrZz30uiM+wGP2PpT/h/337+EDzIag5e/KZcrNsUai8nmdY1C8NfVc5cTDpmx/nTc7EVy1nKFYkC/vTur0fnWbnv3Mct/cmilW+2/7Z6+tPaKSGQcjPW2kmVxfZpgJBLEhDWp9iqLtxi27DeoBWgIDTWfNiFHUndCXNwehKLPI7OIXmXeEQ2ihXnmapG12FtPwiB9/aknnR8O44pBMi+BlsY/eP+BabM7h0nz5JjQBzrEtA5uEWF9sJuPX2E/Hq9vTqs2765kBtKu7cvtm4omzMZOwn2u7J7hfaIMSga1aXwtT42jJTfh8cAxsw/W0Gh9RehK1Ux1HbyaBHnqD028JHu53f/d5Ibo85oGWGkDo5bxYdm0zo957jjWAR+ewKGaGLzNW6hAvOzmbjgh6CHERWKvrFIaKyoJH9XVnX1PwqZd7+F8vefhFHBrYJCXIRiH3S+eqvSDiTz0i1WEgyJKmnz1dDyVVuWrCw0/NQKN8zlP/1Bp76Qpv5kglBqC+cRz8sqKxYucKBINsKDHyibellwoHA6WUpTrqSKg41JYtqnic4AapXRxmgEmpxaXuIN8yWyrxcUn0tloUJx0+Eq1lE7srPSqsFC3cW+GkHpfLgeL1W1dkpbAxvvn7GKQ+mfTdbH3aEq9dIdsdSxbFTjdTMHLd8SSzY0ZkbKt7JVQmwPuZVh2RwFfYAlw052oePasrlSa0TQUIHDHMXLJVFR+58pKwYNJtzQwfiQ/7MkdP21KH+tolPR1XY10BG4dRbSMHqmF7rOTF0ZTOYksiIU8mKh60//tFRWaxWl329bBdFZwlm8ICcV9mg9Ze72fBcVnjkAbElYFYFBVZodWokyFCOA1ee2aZBi48XWXLQchHKF/kF1Tz3lSS5aCFhFB+dVMLzRRRRKuTlrOrkjc5MYhVDs+hyGEgTk+yvZKBTgshJZ8wCuHwLsybWmY1d3fxco0Wq1jjWzZv0JQ9cgUxenDxhTbgylR3q/ZI2M0a/JxkRgf1IUHQ1GZvbjmYX5HM1ch82s1eqKhQdxz4VzPRZDbt4T55etQQ4bajtlRhMaM+59XvAnlvcNQ286oR7Va/6fNtndXf3s3TfXvjuOP/5G15DI2PX19Td/4d5eyu8VbaU708i87C0GpxJkbJjt/JxtAIXRIuTaxLIk6rlxLNO4wz61vp5FxvIct7QST0UWx09g2XoYYePFRo6EJfcOcH1EWZHq+m1AtfBv1Owsdp1NozgXoXuQbAPOp8bI0gyEdYBC7P7nXOnh/NNO2bHfhoNS8cRvh1sHuizL6f5kufmNUeHqlNGvd7y2OK3q7sgkxo8HZlrJFdViVkE65sQqd9zz2PLQqDLP/L0IpvTNrZbVdxtSwln0i43VLkc9DUeWDvIAY4A+ErHrM1soft0UcGjb/uKFLUQHEsb6X7Lq6ND8at+G18HRKQ4efqjKL+oOoNRRL/Y351pHbMftviZ5cZmRmOmhhJ2JHTUZEREVTMQZKEl82ZFGu+f1vagobmfU7nMuF54cMmNLDZNR2oYywjTk+YQEGx0+Ujncc7grCUamACHWUMLsWrAnALPa1r0Rt5gelomqZESlETksSt65/OQJFGJ76vwWQq/WZnLHjb76RSZwovsRrFeQq1motadL2vdOy5L+4=
*/