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
3dccgVFOvfnOeGxNehX+/UCFjFjMOGuUA5zXRvYaVv6Dwmyy+mcyCflvdBCiQ9xh0/QEPOodiz8Xj+WXZoGltkPDV7Ni9OhatRXH/ZEYb/rrFTpf6Eze/JxHpLBz/Z9J2LmGr52DYadr1a1LMDOHC/VilZcvkTWyKnxRuqpJPzmH5k+Dxa/+C4muTbrzuLIsVkZyPyW5XkLuV3a5ur0z75y0xcWwZR28AzIKcquyFcdBvKhbYfM9yL835Q6Zs1brx7MeB7kyueFBykzYDz5Is/TBUMPCg5T+xhY0N6YoL4eOsxHS/PyLjhSi4zCtE+q2rCCzXxW+Sl1lK3Ho+skY6hDQ4Lodf7m3CAm4GiaR38nRIpHrrfjjLAWaOo2vcKfvpynWY7/AhuVveC9TAMW0iyAgN7QF/sPw3rns44vCfKsbHsP/PBna8SC1GizD/PZFNMeTk8ka82qAQgDw/MW+4Mw0ncRbwsPf8QFcxRwqxzErWOMApqLgm4U357pC5BT5XUX8VnC0ArcKoZ4QDFUlsT22qUFytfksJAybFJRuqq1IIf4ABxz0kWHSJDbMsFzuYD72TI/NGiSXQUTOou2tzhJXan2x/HK5zPw3wDCkyYFdtSVky3I5juY+Nv9NSt1ifAJOMv2/1OIxBVUxhIQuGuOwWKMBgTmrtPyXUb2B2FzAsIQmm/3h7r9JofsKWAoG/NUBQQr93lj+3DpS
*/