#ifndef BOOST_ARCHIVE_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>

#include <boost/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_xml_iarchive.hpp>
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

template<class CharType>
class basic_xml_grammar;
typedef basic_xml_grammar<char> xml_grammar;

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_iarchive_impl :
    public basic_text_iprimitive<std::istream>,
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
    // use boost:scoped_ptr to implement automatic deletion;
    boost::scoped_ptr<xml_grammar> gimpl;

    std::istream & get_is(){
        return is;
    }
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
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
    BOOST_ARCHIVE_DECL void
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    load(wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t){
        basic_xml_iarchive<Archive>::load_override(t);
    }
    BOOST_ARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_ARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_DECL
    xml_iarchive_impl(std::istream & is, unsigned int flags);
    BOOST_ARCHIVE_DECL
    ~xml_iarchive_impl();
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

class BOOST_SYMBOL_VISIBLE xml_iarchive :
    public xml_iarchive_impl<xml_iarchive>{
public:
    xml_iarchive(std::istream & is, unsigned int flags = 0) :
        xml_iarchive_impl<xml_iarchive>(is, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~xml_iarchive(){};
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_XML_IARCHIVE_HPP

/* xml_iarchive.hpp
k7qCrsH00jFEUdAsDHyPFV+xJCnJcltBHz8JQS9hcLMTZl8F+cS0Ql3Qu5CNJGp88YliazBoATR1tF7IfQrVB9q2HoNUsJc3pqKcxVuH0hAYzZOi4UU8cjYZJH8Kk3nmqIjRluD80MeLYIPJLrIS6kB5/tpR3DNoznMPXplyD8j0N6bnqw0mh8iKlrROv7LKIr8luJulUBlO/pdoZEM8mrHUGv8jzBB96Juul4ppbzuhpuWImav4MqljG9tl8PytJ/N5yj/PgzKl5X7KP+JdGR+9NJne4pWzQz7Uf3iMhgFf8B0ifR6nya3boo9Q5I1l/6wP28NCcjBRlaI+/tqNYfOHALMHv/mrvjJYOgl7iVGP++jCg6Oy+g2LGCRlhPhfinqqi6Qh40y3dF3U40HD+oW6GXVRWcMi+g3FtGsd7hwGpqIym/YbFqlZGeJ2MsaxTIhbKvJ1xAjawVoQax5LOSSGQRxzj2yjN3g0QZa0/61j2cyGJk0w9OY4KzDByQ7m2QN7YrO2iJKBw+lPYfWm569Q/3zHFNFDWYV/vK/wqsRRbrjcDlcOxJWYBlco6p5Kk6mJMqk0PVUjKdIRkc0RGefM+5JlTizvf0izEmULli5R2cwFwn6teTg1e1xQGBdo4u96jxqWov7xFT8jNE0r8AvzgiimyKh28IuOaoHE7FL1iTd99W6p+hgSV0k+LuNU3ymyhqQeiSsMB11S1L3ww4GWPqh74Bc2gfWNyG846Jui1uNQzRFN8IteZIB/gnn4zOsfUXN/vzPvWOqfUEe9/6WbCt1lLoShrLqmO2Ks+myx68sEobLqo+4nqKnTJqTrc2rRKZeOHKtgKJvq784W9bBwAmY4HNksvQgwaYvdJ6ntW5k7b1+fRyTYYenRjWKQSH2z1BZ7nWP5pFzJLQkRMkJYdqM08UMsKTmVQUnPOEiRvHQ3Zgay4ZVVHKiLoxmDQrafEc3T0lEs8xVoSnpC/G6lxZcIf9sJdewvSBOtILQClB7bEw3JhI0onrBFmX6OE3gWhUnbGT9puDD7UpGEkuqjNdx5PjKbIYnaT0/rnzIBGW9CzOJke/oYmxkoDxBPgGTa7HQPVXZwma52ca4qsskC4RsKX5SHrnmvOJAOhUyAG+uKu+EhANHB/9QiG2a9LRvessiGkecNcaTb8xx9whBHYjnVo7+ovEFHwG2Y0QRtXTmUM7fPhL2rogL6jPr8emRRw1gfx8gCkt43Nur6i6F3YRBqtAbWK4KW2EXgQyU6Sv7qD3R/kOghTNQXugsha6ABN/TzUel31Vh5rfKSSjxw8m0OIMSuVV+gKvmYtMnpdNchPrTWyaT1M3qosG6vOv3enU6/cZavOF5NxyG+CPDSJ1731fuH0H+s/UjU7zSxQ/qlceAvMqNcaGN0aJIqIE9hN+9ZKg7z4ZCa8d9XPfDsxlVzV+E2C6OUlrB+CDOSVQZL/7P8QpLuXBxlfTT/sLe8EuUa9Qj0XhHw3vcHI2TDnjuhKtX6AhN/MgropXq0fs6VJFinr4wmSK6GJBd9vasj77zzQXrnTj6cdo2XnLb/q3fTXiv9zrRp7A960gtaTxVt8TGEZwPUOyyaMTgxdlFKJj19GfbLse/HfkX2P2G/CvvV2K/Bfk32a7MfwH5d9uuz34D9IPYbsR/MfhP29ew3Yz+M/Rbst2K/Dfvt2O/Afif2R97j8YR7HM6+nv1pd8mfzv6X7EezP4v9r9ifzf5c9uezv5D9RewvZj/rz4QvZX8Z+8vZX8H+SvZXs/8j+z+xX8pIvjf7TuzncPnT2b/M/nH2E9jfInM6MufLftxD8uMf8H2lk9+dQ8ay7/qI74t/T2Z/OPu92W/HsaM=
*/