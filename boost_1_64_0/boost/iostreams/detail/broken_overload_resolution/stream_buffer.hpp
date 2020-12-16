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
xJtb5IwKFkUNgQSIQgghCBaPgAiIFFDwrGJQ6n3Qeh+tsVptPanFllataLGlLWqqtMWqtf/93vcm+/bNCxsNtvaX92P4Z3a+mZ2d+ebc2ZlkM9dpvo9tTDjV19bofFnxBQXlRePdpS7+b8Os+o1f867DfBs2p3yufd2GkTfrV8a1Ofh3rpKmvu/BeF4Nm2vmnrHvu4bpsLlZBDwP+s/zZl1neV4p6r6ybn9m/Mc+w/g67FOtehGXN7mp9rzJ9cR18cx5xbPcrAmYN7nX1S1vcq+rU96M+Dp581aqPW/y4p5XsyZg3uTVY9701z0F5qXr/unhyJx1O5hOXEtr4lrIOzZ/npg97S8RuePE7qZJyg2u/TBb/DXMkKk7WStQXG7qNfZJj8oQm0W0WlG/et2/JmFR6eKZtjYAWWsbYOrO/de77teQdgXIjJD67jnx81LI9XORG5DnnNoDuF8t7l/gHq2vS2ZeWF7kdNR25SFx/27oWna7f4eZ5Xkh5hUxma47Lv3ddNG1CakS/sKZJRr+PsK/Wfx/HKpxn2Pc9+L+A3H/S8jTXpl1DavF7Y7QFucL55ZQsrZDnG56Q007tF/bNUfCLlxUoOnREj4p/l8LTQulcC16/1KqD3f3fHRM7zNG0q1fqCkz9Pez8Ogtwt6j4e/R8NWvG3eTNuPE3/BQY96cvEgO7cLHbowvbYwO/EHic2/o5FCyJz7kdiQ68tyt4VqRuyzU01nv/MLpiizXzXOXUk4yJG7VxK2jMzGbd8CyZ8CENuhJqOKa9OT0/qnJGanc05SpibiFnUnZUfm+TaLyy9KTUsMZac3wkdQ4Tr6tyk9T+aTCqHC4sV/2LOzuI03C/vMskRdzH3/vJkPew/wB8zz2FzAXk9+vaXvucrvFLETmD9q+t7e371ofpGTnSvo484vm06wfpJ6TNlfLadxaOy2DmVzbH9u+iz6Qb9iNHsn1anNd89NXH03QCC8Mcy84X+ujzjea+qgM5fXXR2ZtUH+R+z3l5JWQpQ4iHHsd5K3ThorMVD27IeqnyIQTuRa8PkK29vro+677dXyjVGrqo+vFz6c8R1T/CyXsA7jVXCuJxBnJdyWMZqbvPVb8nxLOrPE/v1TXkLr1ja8eM/X3ueJvgOnLfhKJeyhap+Tc5NrPM2X1cnHPCF/l/NtTtxUvnF/qaL3j7ePOjdxMnz0HrhH/KeE1lPWa51oofvfGPGtpTD0zVa6VxdRjG26M1NEVoRRPWEVmHDFM3E8lTUwdivLU1CeDxP2+0DZOTX3PeQ5/XDfPfIHRh5aS1stC3rRdSNp665rSdJ42U+uCitdSw0k5bl2QlpHcKL7uUPk9yE8W+RvSe1J9ZGCXfLKcsV0lcT3K8eeLp30waxR3iexg//PIvUuIS1tkZrSK1EX3YV7WOslm8jCnYl5CZgX3eVXrpe0HMchRR0Xqp24HqZ9ybqr/+umAqXcKRWafsUu5kGv7zTXRX/G311xbiD2mXos9Q0t1qbm3jhO90L0ctH57OVsfVh96OOYwty98c6R+m7dgZr72Kq11VFutowaJ/JFOK2q1Lm6rbF/bRbjx9VThIutaZGSD12keWWs9cqy4D3UsZV/rLK6ITNJBx0i6dtKa1+YsHH0uW/57983rm1OzBjgd/tuVI/03RtJ/1twi1tRFbpHv9pK0z4QbtkRnltnTzZbGRlbSJVnWz80vmFM8CydrOht5Mxdgnt/MaXwqMtc4k4nNIkwTZJdF+pCmDtZrpm6tjrlWatqF5uaaabfF7fMYN9N2mzYpuqb7NOqG0zFvt4w3FXq+PXE2v2RL+S/dwvPwoAWF3MO71l3KFPlgyXtiZNYBkq5cM+lq+ic=
*/