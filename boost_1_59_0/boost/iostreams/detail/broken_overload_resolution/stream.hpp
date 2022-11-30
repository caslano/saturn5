// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_HPP_INCLUDED

#include <boost/iostreams/detail/broken_overload_resolution/forward.hpp>

namespace boost { namespace iostreams {

template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              > >
struct stream : detail::stream_base<Device, Tr, Alloc> {
public:
    typedef typename char_type_of<Device>::type  char_type;
    struct category 
        : mode_of<Device>::type,
          closable_tag,
          detail::stream_traits<Device, Tr>::stream_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename
            detail::stream_traits<
                Device, Tr
            >::stream_type                       stream_type;
public:
    stream() { }
    template<typename U0>
    stream(const U0& u0)
    {
        open_impl(detail::forward<Device, U0>(), u0);
    }
    template<typename U0, typename U1>
    stream(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1, u2);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    stream(U0& u0)
    {
        open_impl(detail::forward<Device, U0>(), u0);
    }
    template<typename U0, typename U1>
    stream(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1, u2);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0>
    void open(const U0& u0)
    {
        open_impl(detail::forward<Device, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1, u2);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open(U0& u0)
    {
        open_impl(detail::forward<Device, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<Device, U0>(), u0, u1, u2);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    bool auto_close() const { return this->member.auto_close(); }
    void set_auto_close(bool close) { this->member.set_auto_close(close); }
    bool strict_sync() { return this->member.strict_sync(); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
private:
    template<typename U0>
    void open_impl(mpl::false_, const U0& u0)
    {
        this->clear(); 
        this->member.open(u0);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open_impl(mpl::false_, U0& u0)
    {
        this->clear(); 
        this->member.open(detail::wrap(u0));
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0>
    void open_impl(mpl::true_, const U0& u0)
    {
        this->clear(); 
        this->member.open(Device(const_cast<U0&>(u0)));
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open_impl(mpl::true_, U0& u0)
    {
        this->clear(); 
        this->member.open(Device(u0));
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0, typename U1>
    void open_impl(mpl::false_, const U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(u0, u1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::true_, const U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(Device(const_cast<U0&>(u0), u1));
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0, typename U1>
    void open_impl(mpl::true_, U0& u0, const U1& u1)
    {
        this->clear(); 
        this->member.open(Device(u0, u1));
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, const U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(u0, u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, const U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(Device(const_cast<U0&>(u0), u1, u2));
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, U0& u0, const U1& u1, const U2& u2)
    {
        this->clear(); 
        this->member.open(Device(u0, u1, u2));
    }
#endif
};

} } // End namespaces iostreams, boost.

#endif BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_HPP_INCLUDED

/* stream.hpp
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
*/