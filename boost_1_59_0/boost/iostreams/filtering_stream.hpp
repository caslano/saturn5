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
+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
*/