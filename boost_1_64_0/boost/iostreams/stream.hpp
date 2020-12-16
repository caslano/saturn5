// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/iostream.hpp>  // standard streams.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/base_from_member.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename Tr>
struct stream_traits {
    typedef typename char_type_of<Device>::type                char_type;
    typedef Tr                                                 traits_type;
    typedef typename category_of<Device>::type                 mode;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                BOOST_IOSTREAMS_BASIC_IOSTREAM(char_type, traits_type),
                is_convertible<mode, input>,
                BOOST_IOSTREAMS_BASIC_ISTREAM(char_type, traits_type),
                else_,
                BOOST_IOSTREAMS_BASIC_OSTREAM(char_type, traits_type)
            >::type stream_type;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                iostream_tag,
                is_convertible<mode, input>,
                istream_tag,
                else_,
                ostream_tag
            >::type stream_tag;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

// By encapsulating initialization in a base, we can define the macro
// BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS to generate constructors
// without base member initializer lists.
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              >,
          typename Base = // VC6 Workaround.
              BOOST_DEDUCED_TYPENAME
              detail::stream_traits<Device, Tr>::stream_type >
class stream_base
    : protected base_from_member< stream_buffer<Device, Tr, Alloc> >,
      public Base
{
private:
    typedef base_from_member< stream_buffer<Device, Tr, Alloc> >  pbase_type;
    typedef typename stream_traits<Device, Tr>::stream_type       stream_type;
protected:
    using pbase_type::member; // Avoid warning about 'this' in initializer list.
public:
    stream_base() : pbase_type(), stream_type(&member) { }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } } // End namespaces detail, iostreams, boost.

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream.hpp>
#else

namespace boost { namespace iostreams {

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

//
// Template name: stream.
// Description: A iostream which reads from and writes to an instance of a
//      designated device type.
// Template parameters:
//      Device - A device type.
//      Alloc - The allocator type.
//
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
    BOOST_IOSTREAMS_FORWARD( stream, open_impl, Device,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    bool auto_close() const { return this->member.auto_close(); }
    void set_auto_close(bool close) { this->member.set_auto_close(close); }
    bool strict_sync() { return this->member.strict_sync(); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
    Device* component() { return this->member.component(); }
private:
    void open_impl(const Device& dev BOOST_IOSTREAMS_PUSH_PARAMS()) // For forwarding.
    { 
        this->clear(); 
        this->member.open(dev BOOST_IOSTREAMS_PUSH_ARGS()); 
    }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#endif // #ifndef BOOST_IOSTREAMS_stream_HPP_INCLUDED

/* stream.hpp
yFZSh5RMm1hV5A0rODI/YIasAajjojo/oK33jQD3o2uv864/HjEGpSs9I4WWDWsX2cYhkEvcPiH0bmJjEG3D1+OLaZuwiTd2rzb1b+ACuNdxhyBb4OdJpgKYefFtjjaXMC/Lvm+kqTJvUB13mflU/0DYHoFtVWaoXJvj7OIcUD+vnfq4lMiLOlC+WeiXHd9d1tF1ic8xiCgfPdfyEb22aj9edOLbYs/w8ahxGpn3jWEj3K+EKXzPLysx6x9TWVUkO4NpGzjXKLcMZAZJ+B7WNkFcfpv4WcamSidV9GnYH3CgXG9vaSN22SmG7D5yvY1lDQKb7PgpkyoaZEfL9Za29QeQTa5tnhvRNkmPc8mn+LU2/KaoX8jzU73MOS0rLfMF3nE/6EbUS1n52PHlZWF1Yh/PXs38mDoVNI1ec+039K+J0OmQkjFVkyunmjr5ZT5Dwna06ajxUCN+fVX47evCWG3EKjfFl7te69jWPmpWs0zamnUsOpr1OyXMHvamZvb7a15EmWGdY72vno1zX82Lyne5X85Pxiovq1yZL/dmrPvJKlfqy30c516a1yjlXB5Rzugcdg+VhtnADGoevV9epavQQrPci/QF6S/V6q8h8qo8d4fLu/TsR/FoGvUu9feXbCJxtoiXv90JF3Yv5bUw9sJTvo1+ueH6lVWLje2q72/kIt6740uroa3+Nayf15EdVr0Gjl831ncwaUXk70mLnf/v1FOBmT+j3NtK/uKu34tsYu0ow9RV4zP7B4Va6K2Msr+vJ/6+bmKe7vcPaDl+Xe8qYdL9sns+gfWDzHKZr4n2QzgA+/LnYNIYGpa2Xy5iz5Eva+3ok96wWV4gMjfxLk+zlhdxmutN+nMzO2tfp0Sudwusx9+RuLt0D8yBFEgIPS8nUPDQps1bt2xh3heyb95mnBPEuUFtpEkUap9F90h9GXcF/1+JK+2Q+P30aP39tEqb67bsmdr0fenXuFulOtla7255ZTWUl/R/xr1v7/9M1/kK62jEnXHvk5c6wmt9TC0bM61yfNURRaPHV011EmyryBvzRYkzm/GvJPbGN9uuqe8A7ahX6zP5cFwxYUMfGPpa+mvaz/XnQqwj4cucfOs+oBqftp2mWX6fzd+TO1uuT3AKCG15xljl6ff4a01tKtdHUt4By7vGJi99JL/tbyvXd3SaWdf6UnnDln92SJ3lfg0l+HsDPSL7dPhF9enws/fpzlJ7/3302TMCl9YLnSLqTvtP1np7QMIOZMw+3T4fVPPd0i+3Cr/M75FrQ5wetvW9rLJT/PJ+Wa5tSnk3sdaXymp717JOYB0u228XLWuzb8V5dN+qhxrRTdDyPFTvhdwPzfKUvpW1LPMl3AGxypJ4Isuj3C/LnnKtzF6WVtkyvyy3k2ub2cvSKks/S2Ur5FoHW5tHLvE2n1w9lJv1YPa9OI/uez3bPnqf36Dbzo16iep7JTiPbvaHyfUBYq0Z8HlGdP+rlETmmTr6/a9Vf/eY92Hi/S8zrM7ZqhxrXzOasOF9tf2T6KvtE7uvps8vncul6Zvl81CH8HbSSr8LzQ8vH/0qtOrymf9h4t+F5idYx4l+F/LylJ6lwji1O3Ka0C7rzDx57dGyp4T3jWixhB9gf++r7mZbNvs2AbHTDFnyHSXLMYmJag2yn8v1oNcW+Ka06m9Dtr0stJzMe0P6SMs+9PtIcp5d55+HleOCrOi20ZRyLGxYU6SqbKrXOFb926WwLvG2UViXXNs4N37b8N8lc7Ojf6efgezQhjxNqyiqLDskvK37dTNCwrXUb4CeXEczn+pn/2Y4Vq5l+XWbkZn8fR7x3c+3x65Ni2WPnfz6k8naM8dav5Gmhv+An/I=
*/