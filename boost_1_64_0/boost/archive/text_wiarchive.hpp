#ifndef BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_wiarchive.hpp

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

#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_text_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

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

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_wiarchive_impl :
    public basic_text_iprimitive<std::wistream>,
    public basic_text_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
        friend load_access;
    #else
        friend class detail::interface_iarchive<Archive>;
        friend class load_access;
    #endif
#endif
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
    }
    void load(version_type & t){
        unsigned int v;
        load(v);
        t = version_type(v);
    }
    void load(boost::serialization::item_version_type & t){
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
        basic_text_iarchive<Archive>::load_override(t);
    }
    BOOST_WARCHIVE_DECL
    text_wiarchive_impl(std::wistream & is, unsigned int flags);
    ~text_wiarchive_impl(){};
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE text_wiarchive :
    public text_wiarchive_impl<text_wiarchive>{
public:
    text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        text_wiarchive_impl<text_wiarchive>(is, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_wiarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_TEXT_WIARCHIVE_HPP

/* text_wiarchive.hpp
wmH8KOWhT7Lnh96piPLQ7eV1p/HQA27xJ3eCI3dRqlH/HWdgdrRYPxg3zV7swjWQe0byhg25nZbTELapPFxQlI0LqugHsX0OSraqkllojxyqlGzYeSpZ/6FWJYsWJdtT2KKjy0slW34TQvtq5DG1nlNERUldw5xEJU6itHUSc+y5jhoH4HS0Ko662CjVZZPpZ9MUEwR8T8Tqop6rSgHRGcvs+BQXBAS3bVs9ogE4bllEGaMV82Uzkb2k3jdEyW/XOcrvjzikrA7z2NZ4GsZ5RR/eIRCQRnkB4MQHDvLTFHz3lP7iNpwo+6GbLqSk4lkUdV0uwH9l2RN/xSpDRAfwKuSbvETxtph6FI75YdPF3tiKwpbXfB1DExEu7ZcXJdPlvINKAoLkg7uU5LAqitYzTi0j5pJVRSmkA4rOwCET5aTY3kpsXnq7hmRvcVEoeu16JeaZnTKshCiIQA5n5SpKzBXukmAeM7KVtNVqQ0n3K4Yj5QcHc8eNd9pxRzQ+QixdlW/iBFRa4xmEy89ROanBe4y/lKURfzkrI33B8TpSC731Onql0evwH2we/zvL43+DrV7/c1GDJvpYBltPnGQBcRZS4lF2KEaRUqs3aEJa51aANm111SMGIMcWb+f46BTlmDhIyTH+DOW4ZZCoAMu4Akyw2krGkfOVu4g8nd7O8/Jr5EmrruiW2+IthSnfla/Z4iFrFWRZhb+KJDacvpBDwBOLXKkkXeyk8rT1IqnqAE9fiegCARwVr623LlGmjpc8F5Ub4Y0l7dKaNEx9gK7b8wveS/sU83uJKIuOX7yT8k5aoAKiWckIpmT7nRemqbqdpztPGajcecJpuvO4gVbP2tWBLQ0fx327F+T77sO6A5MYVs4pID5IgdAKK5IENR6SaE9oFwsvKlkJ6GCp2s74lU5LEUbFoHY6BbENrffwf/FMwv9PF6T0iBbcVL5DL8zya2yrU2hXTNpZ5aynjPQwTxnJr6X+UrajmCAZJH+zxqID12H8u795/PsUj3/j0GJFNseRiTnlrZB6Xi57XJkpZ85DkYOT4u3NcrCjKEUXSV3FnHR5TrqEddJvRNJjzEk7yoehlpA7Xqbukkr0JDp7i9r53bN3Mv1btzT4q/qaP7e+tcQNfuZiYWsIj8TG0lOVjLR1Ro1zJpP4/iuWX/A2/E9ZJoGT3FyiDD+UzibtpHJk4jzQAe0arHjRUzMO4IkIqn7K03qeSk/rcV88rYHK0xroaO7VNcnPFH8LLR6ezE8XuT9Qzs7SHyiHeFgJdCQh4gfrsY7v+yrJL+Xk51snP0y8jPR8ysu4IAcifSRMht/fuzPRZ8BdQR/BdzXApF1TlnqAoxz5va3Mx+8NXeM70MtGmeheNdO9IO1i/pu5GPm5GG7WxRhtucueXBJ5B+bzodnZd4HH/xpTXdhenNrziVyZnaj/I/KSJzylttqJTYylQzERzJZLvLjLj/b2DNuT/scvGv4HOq5/1lNZ1141iqmdI6qwiZnnmlg71BdMedfzoiY/YYSCRSZI3vE8TasJzqWlyDdwt3xSbAsHnMcn8cuT5+M8EcKvE1ziEkXQj22RRx7J6dgjUL66kSVbkmPmbeOBwqa9SeZNlXekiimV45WNIR1FtJ8SfVWJ7sLRHnkRjLdBQzRyh9MiKkhEZffiqCl5ETX/oIgqqyQ6RiSa1kskGpUmop2U6OoZHL1ViT69XkTfU3HC34qER3vRhus3RNRRETVNRElUnANnRNRmleV5Ob/9vHrz7K3sT/A8Zq7lHJuJ65ujM84i3nH+yI+kMhW4JJ6DUqYCv3JURwRpxUVNoHqUr/3AwbwbXuFzfEV2T3FF2y0cVZZ329zDUZc=
*/