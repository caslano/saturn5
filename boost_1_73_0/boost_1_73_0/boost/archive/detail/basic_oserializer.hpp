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
Xgus41v+/Uh8GROgOnMRPXgjI23H/lFJaoop6GW5SPJsiX11/HiRGMwBOdIr6H6DvEyWeQn5STmijKgXolrlWrVar4ltiIHAkUZ3u3YHKg+yU4Y5QskyibGsm0tep8OfQJhCnQhXOY122ojIYVP4tttLu+w9N7AMCuo2iK+mjHAqw6spaWKR5pCLzL4mhS654cOUTBGqPloL4Rm7dDjn/evzqRdTNMtyZRJdU5Mev3Zp717XUXGYkSHvZgx4jtfMYUayC/QaN32798Slxe9n2gOxN6q82CnVjqfiYG1CsIn1WbBvWuOsE84NUHFJpVxQ7SUUAalZMmsc0YKmX8TBs+Cl2Ns5V3mBKGhnvxkSWHHdpofNetVU761c/5cLNIBPKENYV+uO0E9KK8w8Wz+OWz1PuN3KBJTHcTn+ipcZjA/VpBVXQu8vTxrCRDNkxBekPagSXdE056B8UGsIUcxVUYU1amoPu1sp5jhs0HR5INaE9vBM/o4kyDQW9rifEYqDdtixjTYs3ViWdZZexUWTHvCuppyX4713CaGyJWIWV62zVbUnKCJLDoxN0oKiasenZpttHm+bQji4d9gjiwpRq9RvBVxnd9qvcdoX8MMqos85UNmBijJixI1gEh+/Yz4lh1ayTjwb1987iMF4
*/