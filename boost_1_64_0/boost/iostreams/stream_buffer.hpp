// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <memory>            // allocator.
#include <boost/config.hpp>  // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/detail/streambuf/direct_streambuf.hpp>
#include <boost/iostreams/detail/streambuf/indirect_streambuf.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams { namespace detail {

template<typename T, typename Tr, typename Alloc, typename Mode>
struct stream_buffer_traits {
    typedef typename
            mpl::if_<
                is_convertible<
                    BOOST_DEDUCED_TYPENAME category_of<T>::type,
                    direct_tag
                >,
                direct_streambuf<T, Tr>,
                indirect_streambuf<T, Tr, Alloc, Mode>
            >::type type;
};

} } } // End namespaces detail, iostreams, boost

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream_buffer.hpp>
#else

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
public:
    stream_buffer() { }
    ~stream_buffer()
    { 
        try { 
            if (this->is_open() && this->auto_close()) 
                this->close(); 
        } catch (...) { } 
    }
    BOOST_IOSTREAMS_FORWARD( stream_buffer, open_impl, T,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    T& operator*() { return *this->component(); }
    T* operator->() { return this->component(); }
private:
    void open_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS())
        {   // Used for forwarding.
            if (this->is_open())
                boost::throw_exception(
                    BOOST_IOSTREAMS_FAILURE("already open")
                );
            base_type::open(t BOOST_IOSTREAMS_PUSH_ARGS());
        }
};

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

/* stream_buffer.hpp
Nhjx49Gnztr1gJwlzc48Lrb984FiB75J66GLKvOe+vnrUS9V9Pr6oq2TX3/Sbu8dy347eXv1DMnXSTde/ubiZwoKjn9mePX4s29Ykvw69rHs2HeV+Ks6n/7D8XtfdsDJ+ftdGerXYlFs+3b7up3Jr58Za/3Sjm1d/2vuvOyx156fsuKojLmZGzX/ac/k7ed/bOiHy+/OebAbzrcP1u/XJMe1cPvZnmrX2Au2gRtAb1/rApV7Q+XMfa2PUftThEXuRNgdngw3gafD/vAMuB08C+4Cz4XD1P7wAHgBHA0vhIfCi2AlvBgeCS+BJ8AZ8Ax4KTwfXgZxzuXwGjgT3gKvgI/CK+Hr8Cr4HRzpfZeGvTU/zXGDNT/raDl0ga1hV9gergs7wfXgujAX9oLrw41gN+jb32v8zS3l3E/j3xw2g1uo3CD/WyppqFxT3ACVa69yGapXB9UrU/XKUr2yoZfPeXHy2Uzja67xtdD4Wmp8rTS+1prPNprPtr6dq34HBJkav9pZ+vMVgD9foRfsADfSesjzv6GRpsqn4bqo/N0qP8e0N5fw9nLdRMNvCptJeMPeXOVaWeSyVC4btoSdPLmA9+1H6kzkurtyOta3q7b7QTAT7g5z4B5wYzgYFsAjYR84RO+DobAQ7g0HwmE6T2Q4PASOgONV7lC4H5wO94cnwQPghfBAeDUcBe+F1drej4BPqPyTsAg+A4vhc7AEvgpHwwVwDFwES+HnsAx+CQ+BS+AE+AucCGkDTgVcH06BBXAa7AuP9Mtbv9vAdSzlPVfL+37YGT6gcjX+9wbyonLtcCep3BLCpcHv4Bbwe7iV7pe/NfxBny8/wl3hT3B3+DPcC/4C94e/wlHwN1gMf4cT4B+wXO2AD9d4vfkDs1WvfVQvc/7A29oOFsJe8H24IfwC5sMP9TlYB7eEH8Gt4Seq7yK4G1wMB8PP4QiV13LR36TUhaVcHtb0n9D0n9T039D0n9b0n9H0n9X0n9f0X9D0X9T0X9b0X4FFcL4+l1/X9viGOX9H9WppqecuWs9d9f5f17jv+T1mv+9N+3hz3o6Gb21JZ1N9jhXAVrAP9OZN1Kncjipnzpvoq+W2FWwOt4bt4DYwC24Lu8JCLb8d4OZwR7gN3AnuAAeaz5m62Hrmq54bqZ69vee+36fFz/Lcv8bYf3xdeAPMhbfC9eEtcCM9nxF04q75vDCAPTXsgV9/bNtH4qpwkfbuy6Br8x7aK7bd+8hVrA29ArYeQnz833tIYutEz+X/Olz6UHTEDcSdhv84OANWw8j1o2frGtLz4QC4DHprSefsHXs96eqINaVnwSdxtrWlmw8jn/yfBwtx9nWmiRO/mbiB23MNFsNFMNYeJRVqxz8Ht8BYh3oF/z+r61Avh5FrUeeMID7XDw7FeetSjxvhzwPgJsYP561RPWdE+DrVufvEX6u6zlivOnPfhjWrR8HpuFqcuX71gtXY62QkftW4mbi5uFjrWi/Bz1vbugdusM5HOCtiTkIt595a18/y/yJc5JrXzv7oC/PgIFwxbr4bBs7E1fH/Su6TLmlNnH64kbhq3AzcHNxC3EpclyDXcSNwVbgZuLm4N4Jcx3VJb+L0x43EVaen5iqkjtSROlJH6kgdqSN1pI7/17GW7P9ZnW3N7f9d+/6rjf3/BqktfFengeu568W+YdjhlZdVsie5ayfBgHf0uGeG2qKOEJlMrlvtzYgzchxPLKas43gaFj/fPqLosJKJ08ps4+ARcXcV29Mxox373smEDR8zvyYJuyvbOKmMp2lesk07CENnz/YH3fBHN7U7Gy26UJe91I5L96/OU7vgSen1+RsP3XqZXl8vbntwG1XV+HJveUE=
*/