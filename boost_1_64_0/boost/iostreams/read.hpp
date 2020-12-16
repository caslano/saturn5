// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_READ_HPP_INCLUDED
#define BOOST_IOSTREAMS_READ_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>  // streamsize.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct read_device_impl;

template<typename T>
struct read_filter_impl;

} // End namespace detail.

template<typename T>
typename int_type_of<T>::type get(T& t)
{ return detail::read_device_impl<T>::get(detail::unwrap(t)); }

template<typename T>
inline std::streamsize
read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::read_device_impl<T>::read(detail::unwrap(t), s, n); }

template<typename T, typename Source>
std::streamsize
read(T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::read_filter_impl<T>::read(detail::unwrap(t), src, s, n); }

template<typename T>
bool putback(T& t, typename char_type_of<T>::type c)
{ return detail::read_device_impl<T>::putback(detail::unwrap(t), c); }

//----------------------------------------------------------------------------//

namespace detail {

// Helper function for adding -1 as EOF indicator.
inline std::streamsize check_eof(std::streamsize n) { return n != 0 ? n : -1; }

// Helper templates for reading from streambufs.
template<bool IsLinked>
struct true_eof_impl;

template<>
struct true_eof_impl<true> {
    template<typename T>
    static bool true_eof(T& t) { return t.true_eof(); }
};

template<>
struct true_eof_impl<false> {
    template<typename T>
    static bool true_eof(T&) { return true; }
};

template<typename T>
inline bool true_eof(T& t)
{
    const bool linked = is_linked<T>::value;
    return true_eof_impl<linked>::true_eof(t);
}

//------------------Definition of read_device_impl----------------------------//

template<typename T>
struct read_device_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_device_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, istream_tag, streambuf_tag, input
              >::type
          >
      >::type
    { };

template<>
struct read_device_impl<istream_tag> {
    template<typename T>
    static typename int_type_of<T>::type get(T& t)
    { return t.get(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return check_eof(t.rdbuf()->sgetn(s, n)); }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type( t.rdbuf()->sputbackc(c),
                                          traits_type::eof() );
    }
};

template<>
struct read_device_impl<streambuf_tag> {
    template<typename T>
    static typename int_type_of<T>::type
    get(T& t)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        typename int_type_of<T>::type c;
        return !traits_type::is_eof(c = t.sbumpc()) ||
                detail::true_eof(t)
                    ?
                c : traits_type::would_block();
    }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    {
        std::streamsize amt;
        return (amt = t.sgetn(s, n)) != 0 ?
            amt :
            detail::true_eof(t) ?
                -1 :
                0;
    }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        return !traits_type::is_eof(t.sputbackc(c));
    }
};

template<>
struct read_device_impl<input> {
    template<typename T>
    static typename int_type_of<T>::type
    get(T& t)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        char_type c;
        std::streamsize amt;
        return (amt = t.read(&c, 1)) == 1 ?
            traits_type::to_int_type(c) :
            amt == -1 ?
                traits_type::eof() :
                traits_type::would_block();
    }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return t.read(s, n); }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {   // T must be Peekable.
        return t.putback(c);
    }
};

//------------------Definition of read_filter_impl----------------------------//

template<typename T>
struct read_filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_filter_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct read_filter_impl<multichar_tag> {
    template<typename T, typename Source>
    static std::streamsize read
       (T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
    { return t.read(src, s, n); }
};

template<>
struct read_filter_impl<any_tag> {
    template<typename T, typename Source>
    static std::streamsize read
       (T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        for (std::streamsize off = 0; off < n; ++off) {
            typename traits_type::int_type c = t.get(src);
            if (traits_type::is_eof(c))
                return check_eof(off);
            if (traits_type::would_block(c))
                return off;
            s[off] = traits_type::to_char_type(c);
        }
        return n;
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_READ_HPP_INCLUDED

/* read.hpp
5kBy6d6dDnwYVoQ74XHw97ABfFbnuu6CXXWPzgHwd3CIynn+263PqWXx38vqvzdgKvT24tzkjaHCZWovEbVe7f1W/XcVrK5zUGVtEGzmysEWOleytc6V7AJvUn/eC0fqHqajdQ/TMTp3cjy8E07SOZRn65yyfLV3gdpbqvYOqP/S1b/N9D4W1V39Wy0c9W8CrAKrw2SYCNNgDdgUJsEDsLM31girqnsRVCt1ryJyLivBOFhZ3Y1X+zkhHVPTMcbBcBgqE30u2TO7KhwB0+ApsCk8FabDUbAP/BUcAc+AE+EkOAdOhgthJlwCp8Ht8Gz4IMyFT8IC+BycCz+AC+En8Dz4JbwA/gAXwxQ8uwQeByOEowmMgekwFraHF2PeDS6HveBKOBReDmfAX8Ns+BuYA38LC+BV8Fx4NVwFr4G/hdfDa+BN8Ea4Ed4Ob4H3wtvgy3AzfAPeBd+B2+BXcAcMEacPwJrwYZgOd8JO8HHYCz4Jh8Gn4Xj4DMyEz8MZ8FU4F74GL4V/gjfD1+FD8E34MnwLfg7/AokTsw/Whx/DlvAT2B1+CofAg3Ak/AqOht/AifBbOA9+BxfBH+By6Mb7VTAG3gBj4c1wAuab4Zlwu8o9qHJPw1jNd6khb9yC8qD5rjcqXvPdVD07ZDqsAc+CyXAWrAVzYT2YBxvAApgO58GOcD7sDhfAgfAcOAGeC+fDhXANvBBeDy/SPcyXw61wJXxGz354Ha6G++Bv4KfwSvglvArGEog1sBJcC1PgOlgHXgfbwethZ7gB9tEzHsbrWQ4XwzvhangXvAJuhevg3fA6eA/comc1bNOzGp6DO+Af9ayGP8OH4GH4CPwBPg6rhMiXsCV8CraDT8Oh8Dl4ip7dkKVnNuTCF2E+3A2X69kNl8A/wDXwVbgO/hFuhm/Cu/RMhufg6/A1+IaerXAePADfhd/pmQxOmPYgTIYfwDrwQ91zOi2kfazaLz0Y9kElaf7Yq3Pb34OJ8H2YAj+EteEnsD7cDxvCv8G28HPYWffQ7gkPwMG6l7acbQIX6lz3a3Qv7TthrO5lXwE+Bn9A/0VouN8NQvAdGIbvwu9NNH9UdMML42ESgakGm8HqsCOsAbvBFM0XNeFomArHwlowE9aGM+BxcDFMgxfBBvBy2AjeBnFb6qHWcA9sA9+E6XrGR1v4F9gOHoQdNL90hNVDvE9gbdgFHge7w06wJ+wO+2q+aQkz4QA4Cw6EF8Ah8CI4FF4Bh8Gb4K/gbfA0eDccC1+G4+D7cDz8EH5NvBm3/nDLP5wIk2AGbAknwXQ4WfPJBkf7g7SPbTBsi6IMyfUxcvHwC9gGHoCD4JfwJDg4RP6HX+sZQ9/Ac+EhuFjNL4Tfa33xd3gr/AfcAn+Ad8Ewck/AGLgLxsIXYQW4B8bp+6widPBbJdgE1oAnwCQ4ACbreyoVZsA6MA/W1fdRfX0fNYDrYEO4HTaFr8EW8EvYEsbp2RzJsC1sDLvre6c3RJn+cAgcAEfAgTADDoIz4WCYDTvChbATPB920fdPVz0rpB28AfaCN6v798HK3tkZjn7PSx+ItoOi9axcHbQ8d4NtYHfYX9f+DIWr4cmwN8yAfWAB7AvPVfML4EBdkzMI3gAHw5vgED0T6ST4ABwBH4Mj4dPwFPgSPBW+B0fBw3C0rr0ZB0+A42F3R/duh2fC0XAi/BWcBLPgZDgNZsIF8Cy4GM6Ga2AOvB3mwvtgPnwIzoOPw/nwTbgQ/gMug+QlcxFsAS+GfeEKOBhOg6fA6XAUHAOnw5XwbHgZnAdXweXwcvjbkK7lKuOah8HfREqse9ixuOTaB/aR/59e//BP9s4EzqopDOD3zZv27TXNTFOK0WY=
*/