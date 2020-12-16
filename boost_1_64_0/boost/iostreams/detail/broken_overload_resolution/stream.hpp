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
11jd+HcKobNeV1Vq6livfo6S3VWtjtmb9mpnN4j4tZvCy8ULJPhQRvD38Ex7X3Rr1l++JHL9RnRLm6FbR9uiQ/bZOjSsrbe9ax1v0YmzrZ+yE3Z8Q9WDcCo6aQhra9XMxVWVR+u1xJN0/yrnrrmtJQ2fe51vY1uLrP4+Nj/T1l30dq/6WaUsohvnmtxh/XRPySPGGWLfNYSTkc1eGlHnip1KiiuLo1yzTMWPXGde21VOMH1lVzMJIXspT2u0lzzi7S51Z59x/feAwV4WLNX2YlzbzNnmn4rB+cUHvo9/ZiO70lT/0vLxogLn9WtcafATa71ecPr9dtztTHoh3eivlSuXxnatRN71vb/yU2k4701pa/+YJt+iyBvXqTb5DdWy2k5kPVKT31CR1T5QLaVP28dk43qcPZQ+t2AcyK/SHBCSsxplBimZDnbb6uvRCLWvxprL3qbscLXK/2dlh98TdsEOOzrscDKsxRbHkOAzhOcJP1P4YWKbKzNCthndteyh+7VtUgZsU1+PxI5ivFfJNU38J6j2Fn+dSlb2NcpmhK8zq/11OteNdZ4fi2Q8fbRcH0YRTkA2+wHn+VFV7roqKn3PaP6aKGn4KO+h6hhPOugyeL17IqPlcz10bs9wXO+c17YK8QeQL2UfTjgR2WpT2eXqptecEzvpLHYyV8UZgs9Fn3n8pYm67B5jXWT9uZ3c16nHEuS7ZYJP6jSLutQb66KvVE3W5yMVbzdrE3N9SDf661T9A7Fdp0Re+7wYJOfSK+upp1jOl/+z/4OH1bhOys9bzLjjwUG37LDdiuWjH/Tt0nrjOp7/g9Yfp8kNvQPBDMN3/ufKd/G1MN2xdk+dfrZnn8RLIcx3+AfwwXSYCDPgFjAT9oRbwd5wU7g97Ab3hJvBvWEWHA2z4cFwCzgJ9oHTYF94gqRzIuwF58HesFb2S/3keZc6Geo3X+p3IewBL5F4C+QZ07mGXDJhnqPf3Qf7Sf12kPr1l/rtDnvBAbAf3AkOhQPhXnBnOAoOguPhYDgDDoezYT6cI+nMhXmwRn6vgatDzzbybNkg7feclO8gKd/hUr4jpHxHSvmqRf9FcEdYDIfA8XA4nAAPhGWwHB4Lj4eT4CxYDk+Dk6Vcx8GL4BR4JZwKF8NK+AacDr+BJ8G18GS4TsrxOzwR+nz8o/1AyP0bjjb4gVgo9bscZsAr4A6wDg6Ai+BO8Go4Sn5LunIvJS1DuntKunvBVLi3+JEYDXNhgdjrvqKnAkl3pL7v0EaSbhvCIEl3jqQ7V9I9Tcp9FsyEp8N8+V20nv4mGFfxfE6sx3jKxjCWEus4iud7ovlxk3WMbWRfHm+NJEwk1BLuJrxFsK7wxj28zdu8zdu8zdu8zdu87Z/fAoRj/sLx/9JJh1dMO3bCpMpWGvvfI9PS34ssknHsQh99OnAP6KezJvdC1X88zv6m5sC9C8eVTQ72GU9Klm9kZKwkDe6rZPv7dqPH9QEr2dhvTHq637g+W61pNy7k87ae9b7GquO76LX99lS/k81j3pJWBz2WXqXSeYt0jlDH+ul0DlG/2xn7m51lOiRF1qaTenWB+6njO/jyWBvwfkIH8dHOCIJKb2XY2m/jqiY4xrw/UHGvsHrJWnNVhrXm0uFzSi6g0ltNerZsnHKYTpMXHl0yRfrKP+RYYzpMwbCTkWOvyLFKS8rBMWef/kqVx530XaVYfelbb8++D2UcYiS2cCnkb71vT/a9K+NWuVGuL2ePYU24KHJ8FXsJ+3apHaT92Sftz75EPW5fZf9Weg36mq+w++uVXqpcY1bsVzpBV+wXXcn+V7S86Mn1HdH8P9k7E/gqijOA73s5CCSEBMN9yg1yRAQ=
*/