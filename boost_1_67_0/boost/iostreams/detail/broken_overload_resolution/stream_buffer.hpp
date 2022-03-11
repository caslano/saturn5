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