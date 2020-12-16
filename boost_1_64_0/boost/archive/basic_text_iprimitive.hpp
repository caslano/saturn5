#ifndef BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iprimitive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these are templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// Note the fact that on libraries without wide characters, ostream is
// not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<IStream::char_type> but rather
// use two template parameters

#include <locale>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
    #if ! defined(BOOST_DINKUMWARE_STDLIB) && ! defined(__SGI_STL_PORT)
        using ::locale;
    #endif
} // namespace std
#endif

#include <boost/io/ios_state.hpp>
#include <boost/static_assert.hpp>

#include <boost/detail/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
#include <boost/archive/dinkumware.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_text_iarchive - load serialized objects from a input text stream
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

template<class IStream>
class BOOST_SYMBOL_VISIBLE basic_text_iprimitive {
protected:
    IStream &is;
    io::ios_flags_saver flags_saver;
    io::ios_precision_saver precision_saver;

    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<typename IStream::char_type> codecvt_null_facet;
    std::locale archive_locale;
    basic_istream_locale_saver<
        typename IStream::char_type,
        typename IStream::traits_type
    > locale_saver;
    #endif

    template<class T>
    void load(T & t)
    {
        if(is >> t)
            return;
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    }

    void load(char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(signed char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(unsigned char & t)
    {
        unsigned short int i;
        load(i);
        t = i;
    }

    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void load(wchar_t & t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        int i;
        load(i);
        t = i;
    }
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_text_iprimitive(IStream  &is, bool no_codecvt);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_text_iprimitive();
public:
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_binary(void *address, std::size_t count);
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP

/* basic_text_iprimitive.hpp
nDSX/kpK16WkvzwlxqGicd2Lm512Jla7Fwu5xjIR7Iw1XOhhLcFs+AJNwEJJ5FI5t5/l0noMjjmC9cwIKVgicl86mEMeTHrTDwngl6DdwbRy1eofCNjNdPSQnjc2BozdYRoBzs9TvDM2o1UxgS1NZ00tkLyCy0X2cSGYgn+F6U5l96+ifjT9j/cxbl8PF4X1KDxk2X8Yty9cBuiq9ZRTOUZhPVM2nYYo0j2yAdJJHHknudMZmpahfQ991K/+RrPVwQW0uBlCwPytmBbGV3BA7s6lme7ZdRL02bidhUqyCx91tj0n7/MMvO0D6jtgnQcv/LTWEwBQRmIIwC/j28mCRJ6sTRCn6T1+EGu2aRK1ANnXD89zHnL4Gw3Pi7sUdvOBg7BM0PHvmHPYPvj/7f0jetYOPdO+h+310HRo22f8qQ2Qacb9MQ76Tsruf0b7gRP1uKNZa7B6rozaC/Xa6EmgBFUtjfG1PZq3JHAiES7p5OpWCnk54gncrn4W4Wcwy+yxcWxu0qd9T/3lGHmX/5O96wCPqsrCM6mTUBJKkKZ0pBOISAjFDCQ6gcnSFFlFAVHEsopuRkCRYkCJzwgqKCprXcW6iiKEABpq6FUEFEUQ9CVDVyCAMPufc+5785I8Rqxb5/sCM/ee2+8995xzT0FrjZMojjTODN5tG7dPo3/bpVF6IqnE5YBzpNqe7GY+VmDWWfWRrbRN5YapI/kVc8SNN/wq5PIbfIhuqEx0AznVY6JhGY99mTU+hsQrlmMfexPvO23plKsbd1qik33NFLgDIkwdB+bK8XE4oJCS4o9k5WdsPH6B6NWWXyCuk3DUH96rHOK55B0RJNr3Eoznw45Mog3CiuqX3k5QcZ3a+RIMh8PJxAM3L3DS0R2DmiAaOtqGXy5eR6lLLkOpJqNMi6ZBbMHsS0DWU0nIih0VDFaQqvw0fN7d9NPQGo8IZiP5UOhiV+zS40Zu/hkLHUF/DXL5VQWd/UeSPMI1aiyviRiqBSkAH/z+9jUh7KEGD5GrNTc1GqpVz7phm7QXR/RobquwJWfDJ34D2fiEB6MDa7PXIhw/+SNvT0rvPlPA3JVnT95y4augd3/TtXZWNfLLlcZmkHos0nFEqmE+Pm4nugXVGrHN55UqfGqJET518hfjWkB2rq2FdhClecNTXXnEuWwtObHJXd/B/DZV3XJZjBsj6san6Pd0KZc6QCwi5V5sPZhnDP4pMoYdxZzB3yO2grKy24ydDWK/VppWwJaJ6+neFCPDG4uyQAFjChcnikr/EP3FLJlHCdGJFAv0MjWxNLgsbP33ZevnXcZbv3kHLEMrkEW0tn2QUNKWKiX3HbS6enqWxcX5nVQ0Oxl7XH+vL3towm5wclZfxVfJGaihTzXz3VI2EQDaIY+Gx7KVQK01SN7rnjA2KuDwxQbWewKrADX+UHClySv3xUpl/weHVO7+RJbMlT1Ulpm+ZmClD467DCtNymG51566ElYA7dwnCsZnxQeW8oJra7bqbszNEVXGrRW2XIo1Rz+qog91AwH0YYMnsBasivRBFoJFwzP78Fn8q5T1SNvqe1rMGKrES8byvHvQBTRfsYFbW5L99fgu47Ma0jhN+4RAAct33NqqrcVw6tBodec1vmJqL70l6uyL+u6Pz8h5UOQ5fOh3tpFN3qa+1QhSOVcps9S/wQ79fT9WUrztIEHtp/UoDrV+hHfJEw7LqyRNmubEuinlkFGkKBLDqplIvEjizr6fZDoujS9LXWcfpvsmgGcwzGRclENs6z6LFKfhKcCjRIHI0cA3FY55WdlqfjP63F5e2OR6ed0fRkJ49kdSpM9dQJfOOBzXa+W4xrTj45qC//QHh7FrDmw=
*/