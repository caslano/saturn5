#ifndef BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<OStream::char_type> but rather
// use two template parameters

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_text_oarchive
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_text_oarchive :
    public detail::common_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
    #else
        friend class detail::interface_oarchive<Archive>;
    #endif
#endif

    enum {
        none,
        eol,
        space
    } delimiter;

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    newtoken();

    void newline(){
        delimiter = eol;
    }

    // default processing - kick back to base class.  Note the
    // extra stuff to get it passed borland compilers
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(T & t){
        this->detail_common_oarchive::save_override(t);
    }

    // start new objects on a new line
    void save_override(const object_id_type & t){
        this->This()->newline();
        this->detail_common_oarchive::save_override(t);
    }

    // text file don't include the optional information
    void save_override(const class_id_optional_type & /* t */){}

    void save_override(const class_name_type & t){
        const std::string s(t);
        * this->This() << s;
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_text_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags),
        delimiter(none)
    {}
    ~basic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

/* basic_text_oarchive.hpp
PDwJb/NCqN1yO/ZIxsmdUCVIjoj1kQ0M9lpGbkSMp/PKsUW5A3A2lkILrIVXWw+hYbK35UYvHrdPfg7DjhhIbSZ0CiD0QGB1YE3P3IgqHtBz36Z1Xhr32OPo37hK3XMjVtD2LXqIRAnDCtKww5PxT/VmuIM3u9tviZu3NLAqu2TcqKHe3IuvreQPiE1ieJfv2SYxuy7+zwhfG9iTF037ulleFP3XIC+S/qvNJIC/Wl44/VdR3A6Jn6c0PHJWTmu4Ji1ljS8KvShgrU1bGee0JceqO1bhbyP+PsPfl/jbhz8//sLRviPaGR0dHRYtn/Do0p+I6NCfyOhf94la9+/wUf7PBlr8vzW18X9myR99W/l8nyV/aGMb/2eW/L6tbfyfWfIvt8lPsOQvt6n/+LUW/3dNbPy/WfKPZtr4f7Pk53e0Gb8lv6lN+z5L/ol6NuO35F9jU38HS37NETbjt+Rv7WUz/gEW/3dtbMZvye/e2Gb8lvz8y23Gb8lv2shm/Jb8E5fYjN+Sf41N/R0s+TVvtRm/Jf8hm/aPXxPM3zHcZvwqX6sK2fwu0BES8mxjIHAe+YcVXjfg37eBJ7PTmv2V/b9RKpaZDqBukiR10aow0VChGckgJO4F0PbJxsDeFGT5CnI22UYEC93aKHr+DsBqDHstv2XHwWvQ1IHikUFsW3vHC7mPFrqrFt68tFQL9zwQzS3cwS10kBZ2tZYWljBrA1jR88rQLlTha90F3Wd4NGK7C6sDqz5Xq5cjCGvStENp2jntECjd9PYnUtsH9LcbiNTmW4CK+nDcLXKNa595SeqcG7m8Ebh8XDTxnsDSFG98AHbi2aejfAcgXIt3z3Pyg+8MUTmACKEFRkr6MRGxdPWlpLkCvgdg/xntO+CeF0b2FSvp7WhKOFfp8AQKUrxheIjazjqjJdE+3YsoyqnzncRZducqW29v5WKlhOGl7Euru9BA97h5sDBtuckXxW3ok7fgQS7AN5dXOxSXVoIRQcF5RX2xS6/NDhKUtWJQ93ugC+SmaAulTzoh5I4b9xsHVOnTX3//Spb31xbvtp2vEC2wCuTAoWI/fpdyTzgX5uvjwXt8L3qWymJLlisfKKKH3/xRyiztRjG829SSzNLehlmaU1/KIvMeJIn6EkavC6jjehq2YRE9BqdOCmRFcjyF1AmBMN+D1PpzQ8XH3WoAKVHawY6SVIkpfbyucKkCX3+z5XHS8gCz5XDd003cXHW7VPy8X1tbHtpGXiQmik81kgAPC25EZ97ilwvAHdbHDTLZ7AJq6TI9r7nxqJPVUV+M4l7hI1vgPFALX7cTjzDuwmg2a84Z7/Lm3MHkXc4doL+S/H3Mjj4qHX23hdHRNUX9sGak8hSth6Npf2MCG8FOxcY4aHKlxANSQr+nK1PneNRWIV9TTY8w/3qpy2/3Ufi/j8X/88U2+N+SnzzUBv9b8i9vYoP/LflbLrXB/70t/u/b2uD/3mZ84uZK3nyk6vniXf4ZIMvK3H+qPOLXGuWvuCVU/FeBx3aoaMC/PDgEfAcDPnJXMwU/0B4+9RoRgSdTsXN/4mLsbR46f6f0eU1Npr81Gj/cUh6na9Lhf87yOP0p3pFZKSiZNiVCebGMlhz9kFNS0kK9GaYQ4EoS9Wp1BS+f5O3dGjiDPKBsxn/8/iyxzG5GZ0ku3oLvNPZq0CKdpTLNCDnTDVYvaTWhToWPu7M9fgXgykjfAXoxvEJ5bo5AFfqhNC6baZRNSyow8C1wdRhwtTvFGxHwtQKiRnkM6UclR11ckWQk7EAkrobgEScqQwNd4RST5oIqYc9F23GlrvmzYNBNyv/ex6A9JX5a3ToibK/LiLqQnhFxZWBylDQ=
*/