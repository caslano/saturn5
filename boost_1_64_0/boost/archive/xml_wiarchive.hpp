#ifndef BOOST_ARCHIVE_XML_WIARCHIVE_HPP
#define BOOST_ARCHIVE_XML_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <istream>

#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_xml_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
// #include <boost/archive/detail/utf8_codecvt_facet.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class CharType>
class basic_xml_grammar;
typedef basic_xml_grammar<wchar_t> xml_wgrammar;

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_wiarchive_impl :
    public basic_text_iprimitive<std::wistream>,
    public basic_xml_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
    friend class basic_xml_iarchive<Archive>;
    friend class load_access;
#endif
    std::locale archive_locale;
    boost::scoped_ptr<xml_wgrammar> gimpl;
    std::wistream & get_is(){
        return is;
    }
    template<class T>
    void
    load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
    }
    void
    load(version_type & t){
        unsigned int v;
        load(v);
        t = version_type(v);
    }
    void
    load(boost::serialization::item_version_type & t){
        unsigned int v;
        load(v);
        t = boost::serialization::item_version_type(v);
    }
    BOOST_WARCHIVE_DECL void
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    load(wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t){
        basic_xml_iarchive<Archive>::load_override(t);
    }
    BOOST_WARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_WARCHIVE_DECL void
    init();
    BOOST_WARCHIVE_DECL
    xml_wiarchive_impl(std::wistream & is, unsigned int flags) ;
    BOOST_WARCHIVE_DECL
    ~xml_wiarchive_impl();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE xml_wiarchive :
    public xml_wiarchive_impl<xml_wiarchive>{
public:
    xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        xml_wiarchive_impl<xml_wiarchive>(is, flags)
    {
    if(0 == (flags & no_header))
        init();
    }
    ~xml_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_wiarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_XML_WIARCHIVE_HPP

/* xml_wiarchive.hpp
atUa/Lxjx19Sd+4cNO/LLwt2SkxcUr5Ysbo7ly8vH3DjxoX8OTkZf1y8uJJ/3ryldg0adGr4hQs/x8ye7bxm4UL/7X/4Q+VSxYvXnz9zptbXaDwUevz4TFP79mvH+vm1Gn/t2g9zvvrKIef77z+bGhOTp6CHR+GLe/f2q3737rnkRo2mxw0cmJqk003btGRJhTGVK3fOq9EUP7Jp04RX7dr9dHbXrs/rFijwCfD/AfhPB/5LgH8s8PcA/r8C/83Avx3wbwX8HYD/z8B/EvAvBPx7A/+7wH8p8A8B/t8C/yDgPxP4a4F/BvA/BPzdgP994D8A+L8G/unAfy/wfwb8FwH/LsB/H/AvCvx/Af6DgX9n4K8D/vbAvyXw7wr8nwD/msDfBfgvAP6jgH9b4N8Q+LsD/zbAvx/w7w78/YD/98BfA/y3Af88wL828P8D8A8E/uWA/yDgfwz4fwf8iwD/5cA/AvhXAf6Vgf8W4P8Q+L8E/tnAPxz49wL+x4H/BODfAPiPAP7fAP+nwH8g8Q/8PwH+PYF/CeB/EPg/AP57gH8T4H8B+DcH/leB/2ngLwP/ZsB/CPCvCPzvAP8CwP8A8D8H/NsD/4XA/wTw9wL+TsA/CvhnAv9g4B8P/G8B/9+A/xvgnwD8ZwH/DcB/N/DXA39H4H8N+CcC/0jg3wf4VwP+hYG/J/D/HPiHAX9v4F8L+FcF/jeA/0rgfxT41wH+HYF/FvCfBvybAv/1wP8e8K8E/L8G/iuA/2LgfxL4TwH+/YH/ZOC/DvgbgP9h4F8B+KcB//rAfxzwvwn8iwH/0cC/HvDvAPxbAP/iwP8S8HcF/kOB/23g3w34DwP+j4D/j8D/J+C/Gvh/Cvwl4F8D+DcG/p8B/x3A/yvg3xf4nwL+14H/VuD/Avg7A/+ywH8j8J8N/I3A3wf4nwH+0cD/C+A/EviXAf6PgX8K8G8N/EsD/4nAfxnwLwn8rwD/y8D/S+A/A/jPBf6NgP9+4L8W+J8H/mrgbwf88wH/VcC/B/B/DvxTgf884N8J+JcH/juBfwDwzw/8/wj8/YH/LuA/HPjHAP81wH878C8F/OcDf1/gHwr8TcB/LPAfD/znAP8c4D8V+BcE/heBf3Xgnwz844B/EvDfBPzHAP+8wP8I8H8F/M8C/7rAvw/wnwj8xwD/CcA/C/gPAf5fAP8DwL8a8LcD/gOAfyXg/wb4nwP+64D/aOB/GPhPA/6HgP8k4P8C+H8G/JsC/0zgvwH4nwb+K4H/RuC/DPivBv4jgX8C8N8B/F8D/wXAvxzwrw38GwL/Z8D/KPCvCfx/AP53gP9j4D8C+J8H/tWBvxb4OwL/FOBfGvgnAX8f4L8I+KuB/1Lg7wz88wH/qcD/JvDPAP7lgf8W4B8J/PMAfwPw/wT4Fwb+RYD/MODfGfivAP5tgH894H8W+P8R+FcA/reAf1XgPx34twX+J4l/4P8A+PsC/1fAfzPw7wL8BwP/I8B/D/CvA/ybAf8w4N8J+J8A/qnA/xHwXwv8XwL/xsA/HPj7A/8ZwD8E+D8H/vbAfwrwbwX86wP/74D/T8C/NfBfBfyDgP8c4D8f+H8L/AOA/1Pgvxv4bwf+F4F/SeDvBfxNwP834H8K+B8D/u7APz/wvw/8ewD/b4B/MPAvCPz3A/81wH8y8A8E/n2BfzfgXwj4jwL+PYF/FPBvCfwvA/9SwL8i8J8L/KOBfxPg/xD4xwF/b+B/Ffh3B/5uwP8S8L8O/GsA/7rA3xX4hwJ/J+BfBvh3Bf77gH8a8F8P/HsD/3nA/2vgfxv4jwP+94D/QeD/KfD/HPjHAv8zwL8F8P8Z+A8F/h2A/xPgnw78+wH/8cD/F+A=
*/