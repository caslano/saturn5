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
nuFF2Ix1oQfTpgW/pRhG1KM580/KWM3mZptvfLcnLIVyJgpjkwez9xbXkollgszUTzXMzNQDAlqast9aXBZONQqGvn11Ud6RkJ4MEEvXp8kWISvej57BLvYq4rUHJL7WVmqV8sqery0osQfpKXZzdU0kG1fedE0QMZVERY2IUVFRYWNj7yh5WBcsxLIqfo9299b/Wz+ldzFKnRGZi6l2yibm9k+0MsqV9Sy0ELO8w+l83WIrOdmPUqPUpXzdGqQERTHRPJJX1Gk6WsaL89PzdlUfIyMjq38YLPI6WWtqdv9SVZ2ZGT158zdBZwWLj/MJWgfBX6RL8lnNjGJpfulXdmnUKhq0sRSwq8wmvOP4+a7o/bf9yWvCJJQi8rxcoj4L+MQ5mpN/SY+WtqZpZlZSVs7YeMn0wmvZMGMbrZL84PB0sRd/U7EnZ4CIs9DmaDCw6JcMl5TUGTqVq7moqldMfWazty9QspZyr6ZlV6OgKsfCVBcHfnTfi/U+BRdeXKTm5k5upqD2vV8QeuC+EChIrR9gDddmJsi/77YqF56z+s3KODxBgU8w7W7tLSWF8fVQLo/LpIiHUbeAuUC2pJKZiE1IaJ1i9sbLUzCA9G8SyUydDY77ZeATJ0dKO0dKR2dqR2eyz/Zk9k5hnqlqw+JWnS3IIyOJzLKfjIfNjYxADg4+llOKyqpOfkF+BbXzlFoaHv0aoLKc+ubfxZw8
*/