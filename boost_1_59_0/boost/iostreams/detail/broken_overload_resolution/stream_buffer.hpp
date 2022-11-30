// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_BUFFER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_BUFFER_HPP_INCLUDED

#include <boost/iostreams/detail/broken_overload_resolution/forward.hpp>
#include <boost/throw_exception.hpp>

namespace boost { namespace iostreams {

template< typename T, 
          typename Tr = 
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type 
              ),
          typename Alloc = 
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type 
              >,
          typename Mode = BOOST_DEDUCED_TYPENAME mode_of<T>::type >
class stream_buffer
    : public detail::stream_buffer_traits<T, Tr, Alloc, Mode>::type
{
private:
    BOOST_STATIC_ASSERT((
        is_convertible<
            BOOST_DEDUCED_TYPENAME iostreams::category_of<T>::type, Mode
        >::value
    ));
    typedef typename 
            detail::stream_buffer_traits<
                T, Tr, Alloc, Mode
            >::type                           base_type;
public:
    typedef typename char_type_of<T>::type    char_type;
    struct category 
        : Mode,
          closable_tag,
          streambuf_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
    stream_buffer() { }
    ~stream_buffer()
    { 
        try { 
            if (this->is_open() && this->auto_close()) 
                this->close(); 
        } catch (...) { } 
    }
    template<typename U0>
    stream_buffer(const U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    stream_buffer(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream_buffer(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    stream_buffer(U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    stream_buffer(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    stream_buffer(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0>
    void open(const U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(const U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(const U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open(U0& u0)
    {
        open_impl(detail::forward<T, U0>(), u0);
    }
    template<typename U0, typename U1>
    void open(U0& u0, const U1& u1)
    {
        open_impl(detail::forward<T, U0>(), u0, u1);
    }
    template<typename U0, typename U1, typename U2>
    void open(U0& u0, const U1& u1, const U2& u2)
    {
        open_impl(detail::forward<T, U0>(), u0, u1, u2);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    T& operator*() { return *this->component(); }
    T* operator->() { return this->component(); }
private:
    template<typename U0>
    void open_impl(mpl::false_, const U0& u0)
    {
        base_type::open(const_cast<U0&>(u0), -1, -1);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open_impl(mpl::false_, U0& u0)
    {
        base_type::open(detail::wrap(u0), -1, -1);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0>
    void open_impl(mpl::true_, const U0& u0)
    {
        base_type::open(T(const_cast<U0&>(u0)), -1, -1);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0>
    void open_impl(mpl::true_, U0& u0)
    {
        base_type::open(T(u0), -1, -1);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0, typename U1>
    void open_impl(mpl::false_, const U0& u0, const U1& u1)
    {
        base_type::open(u0, u1, -1);
    }
    template<typename U0, typename U1>
    void open_impl(mpl::true_, const U0& u0, const U1& u1)
    {
        base_type::open(T(const_cast<U0&>(u0), u1), -1, -1);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0, typename U1>
    void open_impl(mpl::true_, U0& u0, const U1& u1)
    {
        base_type::open(T(u0, u1), -1, -1);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::false_, const U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(u0, u1, u2);
    }
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, const U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(T(const_cast<U0&>(u0), u1, u2), -1, -1);
    }
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------------//
    template<typename U0, typename U1, typename U2>
    void open_impl(mpl::true_, U0& u0, const U1& u1, const U2& u2)
    {
        base_type::open(T(u0, u1, u2), -1, -1);
    }
#endif // !BOOST_WORKAROUND(BOOST_MSVC, <= 1300) //---------------------------//
    void check_open()
    {
        if (this->is_open()) 
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("already open"));
    }
};

} } // End namespaces iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_STREAM_BUFFER_HPP_INCLUDED

/* stream_buffer.hpp
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
*/