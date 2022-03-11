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