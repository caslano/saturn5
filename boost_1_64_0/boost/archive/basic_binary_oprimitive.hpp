#ifndef BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_oprimitive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATE ON

#include <iosfwd>
#include <boost/assert.hpp>
#include <locale>
#include <streambuf> // basic_streambuf
#include <string>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/serialization/throw_exception.hpp>

//#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_binary_oprimitive - binary output of prmitives

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE basic_binary_oprimitive {
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif
    std::basic_streambuf<Elem, Tr> & m_sb;
    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }
    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<Elem> codecvt_null_facet;
    basic_streambuf_locale_saver<Elem, Tr> locale_saver;
    std::locale archive_locale;
    #endif
    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_binary(& t, sizeof(T));
    }

    /////////////////////////////////////////////////////////
    // fundamental types that need special treatment

    // trap usage of invalid uninitialized boolean which would
    // otherwise crash on load.
    void save(const bool t){
        BOOST_ASSERT(0 == static_cast<int>(t) || 1 == static_cast<int>(t));
        save_binary(& t, sizeof(t));
    }
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const char * t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const wchar_t * t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_binary_oprimitive(
        std::basic_streambuf<Elem, Tr> & sb,
        bool no_codecvt
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_binary_oprimitive();
public:

    // we provide an optimized save for all fundamental types
    // typedef serialization::is_bitwise_serializable<mpl::_1>
    // use_array_optimization;
    // workaround without using mpl lambdas
    struct use_array_optimization {
        template <class T>
        #if defined(BOOST_NO_DEPENDENT_NESTED_DERIVATIONS)
            struct apply {
                typedef typename boost::serialization::is_bitwise_serializable< T >::type type;
            };
        #else
            struct apply : public boost::serialization::is_bitwise_serializable< T > {};
        #endif
    };

    // the optimized save_array dispatches to save_binary
    template <class ValueType>
    void save_array(boost::serialization::array_wrapper<ValueType> const& a, unsigned int)
    {
      save_binary(a.address(),a.count()*sizeof(ValueType));
    }

    void save_binary(const void *address, std::size_t count);
};

template<class Archive, class Elem, class Tr>
inline void
basic_binary_oprimitive<Archive, Elem, Tr>::save_binary(
    const void *address,
    std::size_t count
){
    // BOOST_ASSERT(count <= std::size_t(boost::integer_traits<std::streamsize>::const_max));
    // note: if the following assertions fail
    // a likely cause is that the output stream is set to "text"
    // mode where by cr characters recieve special treatment.
    // be sure that the output stream is opened with ios::binary
    //if(os.fail())
    //    boost::serialization::throw_exception(
    //        archive_exception(archive_exception::output_stream_error)
    //    );
    // figure number of elements to output - round up
    count = ( count + sizeof(Elem) - 1) / sizeof(Elem);
    std::streamsize scount = m_sb.sputn(
        static_cast<const Elem *>(address),
        static_cast<std::streamsize>(count)
    );
    if(count != static_cast<std::size_t>(scount))
        boost::serialization::throw_exception(
            archive_exception(archive_exception::output_stream_error)
        );
    //os.write(
    //    static_cast<const typename OStream::char_type *>(address),
    //    count
    //);
    //BOOST_ASSERT(os.good());
}

} //namespace boost
} //namespace archive

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP

/* basic_binary_oprimitive.hpp
Ivp8N+D0b/KZg2mr0m6ntPWc5q9V2N+ZVfhAi1uC56ncGyl3Fue681/ByxBnfxpDfVhKNKYeiS5AUa6teY9QlGsPYWG4JwLQgIhQPDiwYD3P/EQ6rRM88+Pwl5xqZecfcI/Mlwhn7BgDfi+/cLNvLy9an/P3GvAY4MG1ONR40lYjPRZCNPwdcSJEl48nn48lf5xwplnMyddc7c5/EkkoPhjFQ417GQWRcjGOFpT3FH0ECAbXn79dKYAEEW5qthSMB5g+Ahm40sp1Ax1OWR4+H0EI49xo8eqMC0P+K7yB4y7//mxtibaJ2IhaXUWFpg8qg1GbVPlBbxdLIiZD+FuWH8M2W0RUGhdvQfd6HwPIZ8/VAEFl93mUMRUZsTqF6+u9KrSknfvTZmnsX25pDfAE8H7jabvYnb8RtedvdY8kgVTgxCU8mfgC1e5bqd3e23hWfbE7PEW1JIBcqPGTm4wJafuZe+Q5gBuehtO1caxi27OoFUCS/IIHpU+6WRBADqq6X98jeL87Eu/X59JcBsu+Ahx6TWf5BBoTRrPlS2oU74uFzVp6e5/gcSK5BMmxJW03u0d+FUMnTLvh16SiL2tkgryFT4uL8GHPqfG+jozyeLUQeFWk8KoojnfueC4kzvg2fOukt9Qxt6mAdOkYEa57GNTm1nzlDXxHdZ3kupajrjmqrjlxSqevXVbhSKkQU5lLtfbSX7yYRXh/VNfENaR4svmvMkkFcvxBQiMaw52C7DDuZ5ksnsApd5NDqQA8fr2mTx4IhHjXEdm7q9E70zMiprNDYdw+h7UT/fQvLlJ608jmkwfNkaC1s3Rk5Eucvs1TVDeOe9T6bkHBZpBYg6BMxSrKCzEuuKFSEBQmO4O6B0N0T54Ep4mokOQG7YfLyD50ql56ippIlV/1kiqXgxLh5zWszrBK3zuc6d8TgKehT+eNQPYMc86TCXgD5Qq7DtFfexRHKzg6JP2C3mVrCaglxAQEHkfmJPCA4zephJYAdbFYTXdgG6FrZX8LhXh2F3MTeAU359jTi+dYvz7cxPNmEy9GNjGgYhMvvYaFqavq38b15xBqvEy/XXHm79H0+0czv+wxVeQwJ71JSf1UUjAM1Q1J6EjvO4XHKMoSLImJQ97GXwR8fbiGCwDOI6P0ObE8wp49w1h0ux+d7XVSyv2dyw2gchqSvGANNXXAaOrA0fgAQtM4kvgvTilOxwHEv5+WUzBlpT6H7n4jFtNx+ed/xdvK/z//+o/S/33SjO9yu1IWSL4hGCX+0xNmfBcDftiLVdrrTlalNCfrhsVoTVhbbJF2ddsdrDHm7lRMt5ys3g79jH1Evf1xrXacmmaUev+WlohOdVf96+KLMp54czzTDPjplfmP7GYGWuvC9o/5Bh8550vmI5lXTDnq670Z8jjtO62+Z0GIPeT0deE+kov7iDtfgqB5MAkIAHMdXhZGfQ6K2faEe8xy/MXLxOVkDsMOliC80H/EOQCeKbCrRk4Tj7YY0ttWxfAcjpeL9T/hRfHouuRb6rTRShgesTFi12T1Jsf7S1Gs8E/b2PsotH8edqm27lVt3WXXlvbr2roDxUBrtSsDO2sUfx3b6pBHq5e/HMM9juESoSHymqW18UkXdjukC1sc0gWf6kIydcGFujyoDFXlJGW02om2wXat9KwPoQOeo19kJOfVSZYuJFu68MVuDPdiGe792dqjLm4rd3DbE8MerdDGG7t/VRsDVDHtII1zX2wrHfHHWXVMvGH1RD5ZCLU6oi0NxgaWiT9PIqYPPMPKN12MKHl3/WdSVKX/8rjpL+gWtR8SO0TZP0sM+LpPG/APTbTfP91upt3j1fYX5VJJ7XFj+wzepLZP5iE=
*/