#ifndef BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive>

class BOOST_SYMBOL_VISIBLE common_oarchive :
    public basic_oarchive,
    public interface_oarchive<Archive>
{
    friend class interface_oarchive<Archive>;
    friend class basic_oarchive;
private:
    virtual void vsave(const version_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_optional_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_name_type & t){
        * this->This() << t;
    }
    virtual void vsave(const tracking_type t){
        * this->This() << t;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void save_override(T & t){
        archive::save(* this->This(), t);
    }
    void save_start(const char * /*name*/){}
    void save_end(const char * /*name*/){}
    common_oarchive(unsigned int flags = 0) :
        basic_oarchive(flags),
        interface_oarchive<Archive>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

/* common_oarchive.hpp
vhSDeD/2P2JD7+sy6nmjJKlT2seI/3gQ97rHBCEuZESfowntHkpQySWjzPoQH7UUZv0LGVKh903Ps8W3iznRmC5FxnWKL6NLAnGRl8WKX49P+zE9mPq0E3E5nOCZPxnQd1URjh4+7yT1y19SP2EW5WIK7ydc4UGeTau84F1e1lUFQJTb5Z1xkrdSBb6V85jKzz3Qu3+I39P+i2fP6PPwoCfGCXTAG/5cTyvbV0rh/pwK5f+8BMx/1vQXqWiRiZJhRZAmKsqx8cloOOUXUyiYRaxX5sfwiv88D3UglSpjOk5p4/6v+JInMLEg8rTOCNJ0nZhbAzwTphzmtyeuoXrpY/wO/5T1qxdg3VsaUYeW5h8TGHH6vBwRV3i04Gcm06cLjLv99jkvb7DMZzWneZ/j2IkHXVs0BHX9d01z2vC0J77M82/e1P69ij/6NPmPPiPyR//TBf87PWUJOTxkQR50BZlukxQrMOBgMqR/MGHwafL80HA8M9x4AE6qZMYMkb56fWP4I4egkNW8GI3pOGMwIhcnJqMpII2vPp9Oei71S5SfDv1PPaGfv8FRTt+DQNMxr/lpgCP79voV/+MT5b6Aa7T0/gtQSwMECgAAAAgALWdKUoMbDCi8PQAA4qoAAB0ACQBjdXJsLW1hc3Rl
*/