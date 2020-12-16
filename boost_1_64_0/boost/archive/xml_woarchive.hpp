#ifndef BOOST_ARCHIVE_XML_WOARCHIVE_HPP
#define BOOST_ARCHIVE_XML_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else
#include <cstddef> // size_t
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <ostream>

//#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_xml_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
//#include <boost/archive/detail/utf8_codecvt_facet.hpp>

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

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_woarchive_impl :
    public basic_text_oprimitive<std::wostream>,
    public basic_xml_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_xml_oarchive<Archive>;
    friend class save_access;
#endif
    //void end_preamble(){
    //    basic_xml_oarchive<Archive>::end_preamble();
    //}
    template<class T>
    void
    save(const T & t){
        basic_text_oprimitive<std::wostream>::save(t);
    }
    void
    save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void
    save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_WARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_WARCHIVE_DECL
    xml_woarchive_impl(std::wostream & os, unsigned int flags);
    BOOST_WARCHIVE_DECL
    ~xml_woarchive_impl();
public:
    BOOST_WARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);

};

// we use the following because we can't use
// typedef xml_woarchive_impl<xml_woarchive_impl<...> > xml_woarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from xml_woarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE xml_woarchive :
    public xml_woarchive_impl<xml_woarchive>
{
public:
    xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        xml_woarchive_impl<xml_woarchive>(os, flags)
    {
    if(0 == (flags & no_header))
        init();
    }
    ~xml_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_woarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_XML_OARCHIVE_HPP

/* xml_woarchive.hpp
7wL844H/WOBfFvhXAf5Fgf+PwH8r8E8G/jLwvwL8I4B/CeDfHPj/Cvwl4D8L+A8H/g2A/zbg3x/464G/A/DPBv6ewL8X8K8F/DsC/53A/0vgnwj8iwH/5cD/BvDPAf6LgX9e4D8I+F8A/rOB/0Lg/wfgXxz4zwT+RuB/HPi3B/5+wP8a8P8K+H8P/GOAvwfw3wv87wL/RsB/IPDXAf8lwL8y8NcA/03Avx3w3wX8CwD/PsB/IvAfkw0BwAQBAPgPAf5fAP8DwL8a8Lc7DgEA+FcC/m+A/7lwCADAfzTwP1wCAkAMBADgPwn4vwD+nwH/pi8hAOggAAD/0z0gAIRAACgNAaAtBADgPxL4J0RCALgBASAQAkAYBADgXxv4NwT+zwwQAIB/TeD/A/C/8xwCAPAfAfzPA//qwF/rAgEA+KcA/9LAP6kaBADgvwj4q6tCAAD+zsA/H/CfCvxvAv8M4F9+CgQA4B8J/PMAfwPw/wT4F64NAQD4DwP+nbtAAAD+bYB/PeB/dhIEAOBfAfjfAv5Vgf904N8W+DP/iRAAgL/vLQgA4yAAAP8uwH9wLAQA4L8H+NcB/s2Afxjw7zQDAgDwTz0AAQD4rwX+L4F/Y+AfDvz9gf8M4B9ihAAA/O2B/xTg3wr41wf+3zWHAAD8WwP/VcA/SA0BoCEEgJIQAIB/APB/Cvx3A//tGyEAAP+SwN8L+JuA/2/A/1QUBADg7w788ydBAAD+PWpBAAD+wVUgAAD//e0hAAD/ycA/8CAEgHgIADUgAAD/UQkQAIB/FPBvCfwvB0MAAP4V60EAcIMAAPybpEAAAP5xfhAAgP/V3RAAgL8b8L8E/K8D/xoREACAvyvwDwX+TnoIAHEQAID/PuCf1hgCAPDvXQcCQHUIAMD/NvAfdwYCgAQBYBgEAOD/uR0EAOB/Bvi3CIUAAPyHAv8OwP8J8E8H/v2A//imEACAvwvwjwf+Y5tBAAD+VQIgAHSEADAKAgDwTwb+MvC/IkMAAP4lgH/zXhAAgL+kgQAA/IcD/wYjIAAA//7AXw/8HYB/NvD3BP69gH8t4N9xEASAghAAgH9iXQgA5SEAAP8bGRAAKkEAAP55gf8g4H/BGQKAPwSAyhAAgH9xLQQA4G8E/seBf/tWEACA/zUHCACfQQAA/jHA36MfBIBzEACAfyPgPxD464D/EuBfGfhrgP8m4N8O+O8C/gVarXnSum0/3eSk1QULL+pevu6RIevqPQ75tsS6Ti/WL3C41bz9i2q+2Z+P3jBv9NHosmH2T1+du9Py3JGKB6YG1yo3Z1XvbaGdN18dUCS+7GLP9JAbCW+62UdWTcqXGRa16psmscnP04bc6zHH4etl87UZ4z/fe/GzNl9XNuw5nVYyolOFQddDgw8emj04Zl/k2HGznwxp0GnJlRE7y29veWNPwQ3Rmf3X+x7aWvf4JJ9m1/pMq174Tk//1t+ETGnb+/qYvpun/zJkV9EVUW8WVnJ53mmgfnih1yFzZg69unBHzoQ2pdNGrbtp33xkxzklblVc176/s1/GFod926ounXDgyx9cPk3LmulXbcsPe0vHD3aw7zqtwINKRU/Mmr913JrMLOffvr85qMWxJxf7ndmjdirRu+bJWW9+3P9t2yo1V7T/bWWNG7PUkRnZq+vcN7itfdQzyOm7Ed1bew379fmskg0Cna4s+uVP7J13XBNNGscDYsMCFuxlLSioICAq0qQFRBGQYlcISYBISGIKxYoFxLP3jmDvvfdeUbG+drGcvWDver+d3YQliYLv3R/3uc/N+66T55lnZmdn5js7OzO7lPa85b/3YdetEyKmlO53ZKD8Uhmzn1ah0U2/zq4968k=
*/