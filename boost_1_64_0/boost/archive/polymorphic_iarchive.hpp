#ifndef BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // std::size_t
#include <climits> // ULONG_MAX
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>

#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/interface_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/detail/register_archive.hpp>

#include <boost/archive/detail/decl.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization
namespace archive {
namespace detail {
    class basic_iarchive;
    class basic_iserializer;
}

class polymorphic_iarchive;

class BOOST_SYMBOL_VISIBLE polymorphic_iarchive_impl :
    public detail::interface_iarchive<polymorphic_iarchive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_iarchive<polymorphic_iarchive>;
    friend class load_access;
#endif
    // primitive types the only ones permitted by polymorphic archives
    virtual void load(bool & t) = 0;

    virtual void load(char & t) = 0;
    virtual void load(signed char & t) = 0;
    virtual void load(unsigned char & t) = 0;
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void load(wchar_t & t) = 0;
    #endif
    #endif
    virtual void load(short & t) = 0;
    virtual void load(unsigned short & t) = 0;
    virtual void load(int & t) = 0;
    virtual void load(unsigned int & t) = 0;
    virtual void load(long & t) = 0;
    virtual void load(unsigned long & t) = 0;

    #if defined(BOOST_HAS_LONG_LONG)
    virtual void load(boost::long_long_type & t) = 0;
    virtual void load(boost::ulong_long_type & t) = 0;
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void load(__int64 & t) = 0;
    virtual void load(unsigned __int64 & t) = 0;
    #endif

    virtual void load(float & t) = 0;
    virtual void load(double & t) = 0;

    // string types are treated as primitives
    virtual void load(std::string & t) = 0;
    #ifndef BOOST_NO_STD_WSTRING
    virtual void load(std::wstring & t) = 0;
    #endif

    // used for xml and other tagged formats
    virtual void load_start(const char * name) = 0;
    virtual void load_end(const char * name) = 0;
    virtual void register_basic_serializer(const detail::basic_iserializer & bis) = 0;
    virtual detail::helper_collection & get_helper_collection() = 0;

    // msvc and borland won't automatically pass these to the base class so
    // make it explicit here
    template<class T>
    void load_override(T & t)
    {
        archive::load(* this->This(), t);
    }
    // special treatment for name-value pairs.
    template<class T>
    void load_override(
        const boost::serialization::nvp< T > & t
    ){
        load_start(t.name());
        archive::load(* this->This(), t.value());
        load_end(t.name());
    }
protected:
    virtual ~polymorphic_iarchive_impl(){};
public:
    // utility function implemented by all legal archives
    virtual void set_library_version(library_version_type archive_library_version) = 0;
    virtual library_version_type get_library_version() const = 0;
    virtual unsigned int get_flags() const = 0;
    virtual void delete_created_pointers() = 0;
    virtual void reset_object_address(
        const void * new_address,
        const void * old_address
    ) = 0;

    virtual void load_binary(void * t, std::size_t size) = 0;

    // these are used by the serialization library implementation.
    virtual void load_object(
        void *t,
        const detail::basic_iserializer & bis
    ) = 0;
    virtual const detail::basic_pointer_iserializer * load_pointer(
        void * & t,
        const detail::basic_pointer_iserializer * bpis_ptr,
        const detail::basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ) = 0;
};

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_iarchive :
    public polymorphic_iarchive_impl
{
public:
    virtual ~polymorphic_iarchive(){};
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_iarchive)

#endif // BOOST_ARCHIVE_POLYMORPHIC_IARCHIVE_HPP

/* polymorphic_iarchive.hpp
7MCttGWrdZvHPA8TJhrn4eKJdc5D34n1zsMlrGFc/QEYn8qzc8wtpgF08WsRchAn2fgoX+1fCRd0aPn7mewfCuh/PJYlIycm4M1l7yVf5g+YCmNGjjrEg72PzvNIvme7CMidMUP8+E1VLV/Fpe6lUt1RSpp330rNZ1nbdxanoQa7iIKLuC/yB3TzdtHvJRhsCRMw36Zu3EfHxNpXJkUw9hZigUWwnCP+3XhOpmF8zlhmZYRAisfuD3r3mxtOlZ3Qqroedenmul5aSfUrtGaEDYbvcE/ZqXceTzV05U/cKRe6Vf4UuuhTYtzhwx0USfuzz6itVrJ1dLHsMRhTCtp1w/pwCr8SOau6cLTOMwHRqleGGZqGKBeFcpQTixz0QXZ1N2M2orFIZkHf3UMZ0UGH5HcyGJ/kQGJOSVL1bdyaCpz3E+oGEmPeCa7BHDuvQSQyo8PgH+L5Qo6rwAgqtfagrGpSdX6YiJ2C/mvKbA6BsoV068+nN3AKwPOy/t5m5Q4UoNSXAROI+qXvt93P4LrkjypGQgU3kkS7/7XdWO+WNLuXKBSZrHRgffh7tNZ/HWuudX/MjLvNp8Db0x1qGcPdDn3Bfmon2p5ae2mrCwMBtXpr19Dq/dlYvRd/z6tH8A8ZuFgytOeDa4gLBhnSU1hK/a5Z5j37foJxz36cUOeebZ1Q757V3CuQ8ZY/YHsL7ZYNmbuGNmTh2yJ8+xsSqQMXvK1BzTs9AfriR4LRENdnpXf3fiXr9NVNpBP+XQfXSxtRgFBgzc7rVSFnc+UYc73OwyzUOpGPBjmfvvWRxqJlf8qLT6fcbq9zJou/dBb/VS3KPj4KuS5/jizllTfRUr5jLOWMu+scxPdqHUTRmv2Q9/wuCxA78yYBYpnXmIt7x3hjce8aX2dxrxlfb3HvxgXIJYehfY7yJus33MTyvJJu/kiFTK0G2BVF8zVrWDOG4LPxHv1net/93/8o/H+5xf5/ZAj835Lfe34I+X+Rxf8BeBu1/WeW1pM/bpDyZPeATK62NxvVQsdHr1+/uMj0V2fU73VHQ/q/Zn8frjbsH7Mbsv8y23/aKL/99ob0f5cZ+shfGOV7r2lI/mGWzzfK2xsqf7tRPnK1Ub7spobsv8zyX2iG/RfKh17fzdb1JTv31qMU/3uZYeOVX8oWB83Jj+6NFOZmNvtndUg6PIdS4m2cmCM+iX7pOosChnJw8OpSY5lzMQYoYOgzbjMtxVKwOl1vFIVUKl1+i8V+49YrCLqwr2/2AKlcHbDtxkxydcBe3vX3RjCbcLwE1ByMJSDZR6mKQDSdI3J3+UhYkCBn/K2QnYFsSo+T9GmG98zPmOXoyZYYmItHsID3MQS6dsDBMsFSqK/h243GUDkYiUDXiaUEXdfgBYvU98zgQVywWvgU1VlsinOJWSVfqvQwq+zWH5theq60X2h4rgy/sA5Q/tsF9TxXRuBO+G8BR7xOUGtz3U6Vl9zGf9T5X2zcx3zNuP9DGjr/qjwkbEb5Ibc0dP6lPBfcmRdC/92S370U+aHlP1LKpVUyK+MI1j/zOjAhOG74qJeFzfAYnnjaec9AV1mcoBM7Vitff1eaAQH2QemJj4pnkKssTIqVFEsLO1FM8jpCRCx596km1nITOID4fh/aKLOfnJlxLft9rR487Xet6V/AWN/CwQ35f7jW9C9glH+mIfi1a5EB7wYa5ZtpDfl/MMpHxhnlN93wS/BrwOra+i4Lrb+ZEHRTm+dJmwRlnOeLlZhSe29dKlBmOF3dmy1Qpuc0pc7tdk1UIGaSgBgVDZjNXaE4cPU5DGcWTVsjDrHfxWDNeK0rbHZhPjCL43s2wtK7QZlVqD1Sujx9haJ6vvQ=
*/