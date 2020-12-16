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
t2ofOyj9YXuVHc2D+ylPRLlHBInVkWjXgrKTsdUVjQsfQcsFaVJZf1AOUgzJ/0Berp9qRActSMjZNcuLVSzjXJX9yhvTKYVwCq8GFyvsGnuJliZIrn7UIqNqcHLtSkKeMZ4wmpC1XUQ/BIYqgacRSEl343tP1e0s4TDN/DxaXeFmtopy6s/KqZ4O759aVpy64LVY4DdZZOUY4Y0WRBeHE80C6W1cjBjfiOqKtUEXbNuL+yZbTmLGxxq2DNxJ3HndcuJdTcnDl7lEuCnphDqJfb1XAgur2Z54Z//CNcysn1Dq57Usfs/iJdMU80K0wNiPH51l9VwPY9/jmNaMWd5swYxN98vJ1emh4cZkeRd+cpvxICKIbYQijTl+iuiNK4OF2Y5lCIK9Rgr1FqF+pH/m0GQKfXOMak8h8Qyzy4jaU8+F+vyFReANDsQDj1BsnFmVMZ/LR1mf/OsuSIzmCfuHj5U+UWj9UB7K42kuRkxdX0kiKKaRRigDQyRWdktic7nUueUB2GOskjFpB9fyVJl1YX1wHc1yNtsj4/sylheagah71gq3E0LhFoar6cq8uFJRtl0obVa2yb23iwaF13y9r2fDSJC7cr1BUV27V7PStc0pLaQoSPoneZ5GthhAxDgWHnRYpeT+c7EFAU3otauUSvtjJqKSPMCkn7hf1DS8iJOIS6SiWQgjdEgCnfnBerqaHwEehxC/LY9IUm+MUD69P12nT++KiPcVeDmlLAq85ugJyufTrRR4l0oJvHyRm1gxbtI617Q84hnreFUJrMDyw7Ss6dXtdFahrok1lcfwbO1M2vP+uEwp2n/KR0nUPyHTNXz0lkyH/5EBkOmC0Oss1tgsz6kkXX1/UxjPbKYVQ+1RUWij7Nlq/uEgbLpD0MOt+4npmr4kkpEwt7emWZijlRmQBfdYBDgHNOt6DcahxzjQWzbcwKqIRHnDQyrRDbo+3CzShcVOJJGOH61JO7SmqG/HebS7sQ+dKnJGUy9OCbXk+rOKc/1wXjrkRSko+ZnlxwghP0ZQSia8QJqUhA8JWhG0Kb6hbGyUbY004h5tTkZTqEBr+1qMatTDmaFibrcXVq2EidCCyuTkSXgOoYoG9VB1T4idbAHwOH5ytQ5XkRw3/CVhhxcikXCNFwIZ7t9UiczyW/4HSl/jUn131sUUv2TkGd7NH5KkcQChYmmQ3Aq16uPndFJvpKWSx8b7nAcvHQhF5+Vg1dzOy/qq1p2X2dWsOi8VSghih9l/hJrmPfuudc2ZPsb2ULOxCl/pQBWTgvzwbujzEkY9Cik/v/UwFb91XdwT0VysLy4yf2ynmGzFa/w9Nltzl4bo2uV+GX7I4EKFk821m1jZS/0bZATzWcg1Vg/tymM5eVPu9Pcf8Lx5/F9neGMX2cAQuPoLGlurhbGdet7U+qeEV0oR4/E7sB/xDt6P2EVvSLCH9bz7mMfhFhYb+H1+Z8yeG+nDEwroezvAMEllP7GX3jDJRRXRmSwuVqnI8+l5UxP8hMk8sXyEbdEvKWWxRV/gBrWoJ8QjiikmHtFxFX1sU0VgRDHxCd+JQCkEWooWLomyO/Q0huu++DyESqeFTLW+MstUdSX12WFKw37iIjXsKTiMH6A07GfVbFuG7M8iXdTKURCOZdUdrK3oxqYtY5t40QICKc2kjRcpdof+15ziJE4x0jrFS+JTcayoRZD1pSQ33DaZkBBXyUKVqRLeEfezuqhQFxlNrPLxiOnuQ5JKCqqoZdHGRCt7fpZvlq7rX68k/0IXZJlxJBQRRYxmRYRroGXkEOb30/UxpJ+hMQBMQFIk42x/sj8TKoV7+Z8K8RcWBkJimwDYwE/MAr7mc+Whu1ygh64=
*/