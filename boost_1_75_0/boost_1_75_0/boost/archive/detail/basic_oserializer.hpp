#ifndef BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP
#define BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oserializer.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

// forward declarations
namespace archive {
namespace detail {

class basic_oarchive;
class basic_pointer_oserializer;

class BOOST_SYMBOL_VISIBLE basic_oserializer :
    public basic_serializer
{
private:
    basic_pointer_oserializer *m_bpos;
protected:
    explicit BOOST_ARCHIVE_DECL basic_oserializer(
        const boost::serialization::extended_type_info & type_
    );
    virtual BOOST_ARCHIVE_DECL ~basic_oserializer();
public:
    bool serialized_as_pointer() const {
        return m_bpos != NULL;
    }
    void set_bpos(basic_pointer_oserializer *bpos){
        m_bpos = bpos;
    }
    const basic_pointer_oserializer * get_bpos() const {
        return m_bpos;
    }
    virtual void save_object_data(
        basic_oarchive & ar, const void * x
    ) const = 0;
    // returns true if class_info should be saved
    virtual bool class_info() const = 0;
    // returns true if objects should be tracked
    virtual bool tracking(const unsigned int flags) const = 0;
    // returns class version
    virtual version_type version() const = 0;
    // returns true if this class is polymorphic
    virtual bool is_polymorphic() const = 0;
};

} // namespace detail
} // namespace serialization
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP

/* basic_oserializer.hpp
uOAZZsKFHtpQeEgjVVwLGaw+oVXpov+aT/jPxXcvoM06gj2bGtjO/hKaTQ0m+3txUIb3lhVoC7HMYOXShqgzTfTi1hIKg+Nki20eCM8hHKeK/N6bnwfcDMZLEfHMdSSGSSV+q0ThXlydGDdkk7WRdOLXC3HJWnheB/d769WD1gejJUhucDjWnknamTeEtmpq+uffa6X983OBbrEYBQmRyLp7cIpIzF0k8rWOaH+92H/6eotEv3++EM9kiT674LtnD4o3GB/9cfrzkU3qFGQzsBdnk7UTqff2L5lHesdGMVYQeL4XNpvw8QSpO5fUNxhOHuhZgBcRbUqrkHqySij1OsH3forEV316EuLiPLs+U0jamyeuc6KuB+KsJatR2WSdZ7B8ob/nkn5wb14+ibtRwtmiHQ+GU0Rkp+pn7wPx0gkdweKl0RYtBlei1oo6H6wcrtfpiTWinO7lMYPEMUVE5hv+Dd46QkVYA0DcwWQhjK1CTJ8q2sxAnPVi9CiNO/fmC1F/4RA6k9pfSHq5flA+CsQeuH4IWRb0K18yBE4GiaYHz9OTXGEVRNBa/iB86AmFvloG5m8gtpcBdqonehDaspHMNxJOJtF5LimXLuZL/Uoan8TXU2vozPX56dImgcN46uh9jsrAsbTy3Bia3HeKd+m5ZYxwOYhphNnnC4RaGUNj03rv5MuM++zglXemmhmxBvWpqT6bS39wUAvw
*/