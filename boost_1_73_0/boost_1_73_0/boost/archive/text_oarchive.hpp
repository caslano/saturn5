#ifndef BOOST_ARCHIVE_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <cstddef> // std::size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
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
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_oarchive_impl :
     /* protected ? */ public basic_text_oprimitive<std::ostream>,
     public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_text_oarchive<Archive>;
    friend class save_access;
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_ARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_DECL
    text_oarchive_impl(std::ostream & os, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_oarchive_impl(){};
public:
    BOOST_ARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);
};

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_oarchive :
    public text_oarchive_impl<text_oarchive>
{
public:
    text_oarchive(std::ostream & os_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_oarchive_impl<text_oarchive>(os_, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

/* text_oarchive.hpp
NmHgSHFVjLpquGq9ntDhwwjRATYiN3biXy20FhzbTWkhgg4qRkMkWi913SEY2nUgoQZuGJmoMwflJqL8Uhq75374Bt5qYHZ/IhNE4tjEWQSN5+ZWstFgvlzmLdW56DIZcbQO9Y9RPlFvQUjwiOS+MY3G8KYl5/cgAYk0C04DBYawxD7PpuPtdNyRSvaiAD8DlSJDMkYM5QRYHCW1tzgkRfPqThIHvqQUfrm5W67k2VjJUNrnXCmCoiEdY6/UYFeG0rVQJK8II+iDiV3RUAUDg1RYXv8I8EYlOky8XMc8SWE5KGxDDNMNLExWaAFK0FoTZiNtFgOYmF6m8g4aqZ7BrUE+ad3wHEaxtiAMT8U/xofG7G6Iy+hoV4hg6TS0rnUgcvhmKp4ACuOxYL2LeyyhISS4I/E44gcMuiWYuKtlRL42NXFxzTTM+MAbFFZEYWbaPOu8r3ucURQmo5PTDBownqZapIkgxJ1lyaZaJA3DnyMR2zr/JNu6ctAYw552c4ezYuQjP2RFTJK1mkx4tF/RhaEiF1PdNn1H6JoFkZoVaA5D0ffsTHhCmFA/WJ1v9H9nt58VaJpzbdzfUD53oy7I19Csmqasi5TCPr7O1sC6R/NTmrIOx6b9XotZJ55I5wgz1vpxFLxx66jx0d2q
*/