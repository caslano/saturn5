// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <memory>                                     // allocator.
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/iostream.hpp>        // standard streams.
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/streambuf.hpp>       // pubsync.
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//--------------Definition of filtered_istream--------------------------------//

namespace detail {

template<typename Mode, typename Ch, typename Tr>
struct filtering_stream_traits {
    typedef typename 
            iostreams::select<  // Disambiguation for Tru64  
                mpl::and_< 
                    is_convertible<Mode, input>, 
                    is_convertible<Mode, output> 
                >,          
                BOOST_IOSTREAMS_BASIC_IOSTREAM(Ch, Tr),
                is_convertible<Mode, input>, 
                BOOST_IOSTREAMS_BASIC_ISTREAM(Ch, Tr),
                else_,        
                BOOST_IOSTREAMS_BASIC_OSTREAM(Ch, Tr)
            >::type stream_type;
    typedef typename
            iostreams::select< // Dismbiguation required for Tru64.
                mpl::and_<
                    is_convertible<Mode, input>,
                    is_convertible<Mode, output>
                >,
                iostream_tag,
                is_convertible<Mode, input>,
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

template<typename Chain, typename Access>
class filtering_stream_base 
    : public access_control<
                 boost::iostreams::detail::chain_client<Chain>,
                 Access
             >,
      public filtering_stream_traits<
                 typename Chain::mode, 
                 typename Chain::char_type, 
                 typename Chain::traits_type
             >::stream_type
{
public:
    typedef Chain                                         chain_type;
    typedef access_control<
                 boost::iostreams::detail::chain_client<Chain>,
                 Access
             >                                            client_type;
protected:
    typedef typename 
            filtering_stream_traits<
                 typename Chain::mode, 
                 typename Chain::char_type, 
                 typename Chain::traits_type
            >::stream_type                                stream_type;
    filtering_stream_base() : stream_type(0) { this->set_chain(&chain_); }
private:
    void notify() { this->rdbuf(chain_.empty() ? 0 : &chain_.front()); }
    Chain chain_;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} // End namespace detail.

//
// Macro: BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(name_, chain_type_, default_char_)
// Description: Defines a template derived from std::basic_streambuf which uses
//      a chain to perform i/o. The template has the following parameters:
//      Mode - the i/o mode.
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Access - Indicates accessibility of the chain interface; must be either
//          public_ or protected_; defaults to public_.
// Macro parameters:
//      name_ - The name of the template to be defined.
//      chain_type_ - The name of the chain template.
//      default_char_ - The default value for the char template parameter.
//
#define BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(name_, chain_type_, default_char_) \
    template< typename Mode, \
              typename Ch = default_char_, \
              typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch), \
              typename Alloc = std::allocator<Ch>, \
              typename Access = public_ > \
    class name_ \
        : public boost::iostreams::detail::filtering_stream_base< \
                     chain_type_<Mode, Ch, Tr, Alloc>, Access \
                 > \
    { \
    public: \
        typedef Ch                                char_type; \
        struct category \
            : Mode, \
              closable_tag, \
              detail::filtering_stream_traits<Mode, Ch, Tr>::stream_tag \
            { }; \
        BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
        typedef Mode                              mode; \
        typedef chain_type_<Mode, Ch, Tr, Alloc>  chain_type; \
        name_() { } \
        BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name_, mode, Ch, push_impl) \
        ~name_() { \
            if (this->is_complete()) \
                 this->rdbuf()->BOOST_IOSTREAMS_PUBSYNC(); \
        } \
    private: \
        typedef access_control< \
                    boost::iostreams::detail::chain_client< \
                        chain_type_<Mode, Ch, Tr, Alloc> \
                    >, \
                    Access \
                > client_type; \
        template<typename T> \
        void push_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS()) \
        { client_type::push(t BOOST_IOSTREAMS_PUSH_ARGS()); } \
    }; \
    /**/    

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(filtering_stream, boost::iostreams::chain, char)
BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(wfiltering_stream, boost::iostreams::chain, wchar_t)

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

typedef filtering_stream<input>    filtering_istream;
typedef filtering_stream<output>   filtering_ostream;
typedef wfiltering_stream<input>   filtering_wistream;
typedef wfiltering_stream<output>  filtering_wostream;

//----------------------------------------------------------------------------//

} } // End namespace iostreams, boost

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED

/* filtering_stream.hpp
mNrERIrLQyihJcpq03jkL+Q+wFFWPKSsV16lepxjCj/XdkMmXkR+N1Ad3HsdhvwcspmfGW96ZnXyPw8y2VrlL8ph45lzyL0n+q4MZZbyCT1zt+mZiTaMzbn955BbB7s2P9W1GPNTAXnmpzKs1k6Y1koU/wyG271WorhrIpqv19wHVpo3JObBKx1VMbO7OOReWvhaCeu1IYWvoaC993VdAOsoLpj33me9u3SH9O51WZ+OZ5n05jwXz/P8Ofn05vVZX90ADOH1GBG8HqMcr79orMXfpDffyOGVgL1QDL35Xr7vc+2+/zO9eZLC86Q815vDZxu0ZB3HY7x3zTNgCXA+GA3uBivx3h5pvLcH/NCZF3t5jw83n23RANzHZ2F8Di4GD4D7wIPgVfAQWFH2nnnQDzwCDgG/BreDR0Gbgn4bjAG/BQeAx8FZ4Ant+eAp3tvlNFhP9e4J0ho8C2aD34Mvg+fBA+AFULWhLwJbgD+Bw8FL4AvgZXAv+HfwDKjVhzC7tz60Bq+BC8B/gAfB62CAw1tPmoASOBGUwS2gAv4AqmCY03smQzJoB+eCDvAA6AQll7deNQXd4HjQD9wE+oNXwQCwnNtbv/qAQeBCMBg8CYaAIR5vfboXDAOXgOHgPrAkWAmdbQTYCSyl1TMwEjwPlgbj/dEmwHFgGfAtsCz4G1gOjAtAvwxOAcuDO8EKYFAg9AZgElgJfBiMAfeDlcHwIG99bgdWASeD1cBPwOqgHOytx/XBGuBQsCa4HKwFfgrWBgNCMC4FW4Hx4CiwDvguWBf8EawH1kAFrg8OBBto4YANwcNgIzA81Nsv3As2AR8DE8B14N3gR+C9oDPM2x9GgO3ASLADWBHsCGJNYJ61EVtPqr97fcTN1kbsQbinYbG8VUTDJpz671oHcYf0/6mjRqbfEv2/NvisxjrSWNZRz4atCjuav9GNvqH/N3+fy3MeeBJd74Qxj+XZrbi/aN/osr9CvyltRNetz2U1P+MH0ze6y0x7eoeURO7Ahpp0/Gm3+Ztb7fk/mL65VcPRP0++8c3tJXrfFjbOK/5a0+UbaO++o18tGbg689CM3tv9D+/O/Kjw8aL1+K+w8Wjxx4XFHY/S+1svT66LbWAdsC31sTe/p8PBBDAKbM9n3vTkM2/S+cyb0Xx98B3qv/r+l/VXPuMzPuMzPuMzPuMzPuMzPvP7jQo78jbK/+npafRP6qiB/WkC4A/uAajNAZQsKYzz/lfyHEBlTk8MrA3/XMjwzgHcd19L7dFx8Q1T00dSpASvE+Z9P6z3kuP7zbL9qLFZ1nuEwG/R9zMz+1ViNL/DMvU4BJn8BlnGYci49AFev6Emv6H5/GapedfkRpj8RrBf8/r1iCKsXw8xzSeYv6916nMInD9Wa5rhRmlDeuGG9LJbqH4vpwtuFFfEv4DOKUcULrMv2qi5p3y5dv5d95wvMezFKXFfhL73we3XORX3+1zSkej5z3U2wqwj4bkCjcF8Pm6JfHMBWaeKNw8w95Ra5LmA1b65AJ/xGZ/xGZ/xGZ/xGZ/xmf9pc8fk//QBt0z+jywpjO/Ao2VD7idTCdaFHzkm+R+P1oX/Isn+OcWQ/XMs5Xlr2d/sF+HhL8TKSvY3++XvjksjzVG3QU7PJ5NTPHAdbohbEeXvPRvJ/ZsnHo5/trqjWs491T/94vM7sObz98jfSXrecp2JyKerD2D5OxC0sTxO8ydgaZbHo/h3Jf6d9gfk86LK5rt9srnP+IzP+IzP+IzP+IzP+IzP/EFzx+T/AbdO/1/WpP/PZfm/GqenKqy/tsGrSf4f8Dv0/9nFmAPILob+P7sY+v/sYuj/s4uh/8++yTxElMlvFPs1rxU=
*/