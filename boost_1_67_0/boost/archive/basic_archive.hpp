#ifndef BOOST_ARCHIVE_BASIC_ARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_ARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_archive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstring> // count
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp> // size_t
#include <boost/noncopyable.hpp>
#include <boost/integer_traits.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

/* NOTE : Warning  : Warning : Warning : Warning : Warning
 * Don't ever changes this.  If you do, they previously created
 * binary archives won't be readable !!!
 */
class library_version_type {
private:
    typedef uint_least16_t base_type;
    base_type t;
public:
    library_version_type(): t(0) {};
    explicit library_version_type(const unsigned int & t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }
    library_version_type(const library_version_type & t_) :
        t(t_.t)
    {}
    library_version_type & operator=(const library_version_type & rhs){
        t = rhs.t;
        return *this;
    }
    // used for text output
    operator base_type () const {
        return t;
    }
    // used for text input
    operator base_type & (){
        return t;
    }
    bool operator==(const library_version_type & rhs) const {
        return t == rhs.t;
    }
    bool operator<(const library_version_type & rhs) const {
        return t < rhs.t;
    }
};

BOOST_ARCHIVE_DECL library_version_type
BOOST_ARCHIVE_VERSION();

class version_type {
private:
    typedef uint_least32_t base_type;
    base_type t;
public:
    // should be private - but MPI fails if it's not!!!
    version_type(): t(0) {};
    explicit version_type(const unsigned int & t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }
    version_type(const version_type & t_) :
        t(t_.t)
    {}
    version_type & operator=(const version_type & rhs){
        t = rhs.t;
        return *this;
    }
    // used for text output
    operator base_type () const {
        return t;
    }
    // used for text intput
    operator base_type  & (){
        return t;
    }
    bool operator==(const version_type & rhs) const {
        return t == rhs.t;
    }
    bool operator<(const version_type & rhs) const {
        return t < rhs.t;
    }
};

class class_id_type {
private:
    typedef int_least16_t base_type;
    base_type t;
public:
    // should be private - but then can't use BOOST_STRONG_TYPE below
    class_id_type() : t(0) {};
    explicit class_id_type(const int t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }
    explicit class_id_type(const std::size_t t_) : t(t_){
 //       BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }
    class_id_type(const class_id_type & t_) :
        t(t_.t)
    {}
    class_id_type & operator=(const class_id_type & rhs){
        t = rhs.t;
        return *this;
    }

    // used for text output
    operator base_type () const {
        return t;
    }
    // used for text input
    operator base_type &() {
        return t;
    }
    bool operator==(const class_id_type & rhs) const {
        return t == rhs.t;
    }
    bool operator<(const class_id_type & rhs) const {
        return t < rhs.t;
    }
};

#define BOOST_SERIALIZATION_NULL_POINTER_TAG boost::archive::class_id_type(-1)

class object_id_type {
private:
    typedef uint_least32_t base_type;
    base_type t;
public:
    object_id_type(): t(0) {};
    // note: presumes that size_t >= unsigned int.
    // use explicit cast to silence useless warning
    explicit object_id_type(const std::size_t & t_) : t(static_cast<base_type>(t_)){
        // make quadriple sure that we haven't lost any real integer
        // precision
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }
    object_id_type(const object_id_type & t_) :
        t(t_.t)
    {}
    object_id_type & operator=(const object_id_type & rhs){
        t = rhs.t;
        return *this;
    }
    // used for text output
    operator base_type () const {
        return t;
    }
    // used for text input
    operator base_type & () {
        return t;
    }
    bool operator==(const object_id_type & rhs) const {
        return t == rhs.t;
    }
    bool operator<(const object_id_type & rhs) const {
        return t < rhs.t;
    }
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

struct tracking_type {
    bool t;
    explicit tracking_type(const bool t_ = false)
        : t(t_)
    {};
    tracking_type(const tracking_type & t_)
        : t(t_.t)
    {}
    operator bool () const {
        return t;
    };
    operator bool & () {
        return t;
    };
    tracking_type & operator=(const bool t_){
        t = t_;
        return *this;
    }
    bool operator==(const tracking_type & rhs) const {
        return t == rhs.t;
    }
    bool operator==(const bool & rhs) const {
        return t == rhs;
    }
    tracking_type & operator=(const tracking_type & rhs){
        t = rhs.t;
        return *this;
    }
};

struct class_name_type :
    private boost::noncopyable
{
    char *t;
    operator const char * & () const {
        return const_cast<const char * &>(t);
    }
    operator char * () {
        return t;
    }
    std::size_t size() const {
        return std::strlen(t);
    }
    explicit class_name_type(const char *key_)
    : t(const_cast<char *>(key_)){}
    explicit class_name_type(char *key_)
    : t(key_){}
    class_name_type & operator=(const class_name_type & rhs){
        t = rhs.t;
        return *this;
    }
};

enum archive_flags {
    no_header = 1,  // suppress archive header info
    no_codecvt = 2,  // suppress alteration of codecvt facet
    no_xml_tag_checking = 4,   // suppress checking of xml tags
    no_tracking = 8,           // suppress ALL tracking
    flags_last = 8
};

BOOST_ARCHIVE_DECL const char *
BOOST_ARCHIVE_SIGNATURE();

/* NOTE : Warning  : Warning : Warning : Warning : Warning
 * If any of these are changed to different sized types,
 * binary_iarchive won't be able to read older archives
 * unless you rev the library version and include conditional
 * code based on the library version.  There is nothing
 * inherently wrong in doing this - but you have to be super
 * careful because it's easy to get wrong and start breaking
 * old archives !!!
 */

#define BOOST_ARCHIVE_STRONG_TYPEDEF(T, D)         \
    class D : public T {                           \
    public:                                        \
        explicit D(const T tt) : T(tt){}           \
    };                                             \
/**/

BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_reference_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_optional_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(object_id_type, object_reference_type)

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#include <boost/serialization/level.hpp>

// set implementation level to primitive for all types
// used internally by the serialization library

BOOST_CLASS_IMPLEMENTATION(boost::archive::library_version_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::version_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_reference_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_id_optional_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::class_name_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::object_id_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::object_reference_type, primitive_type)
BOOST_CLASS_IMPLEMENTATION(boost::archive::tracking_type, primitive_type)

#include <boost/serialization/is_bitwise_serializable.hpp>

// set types used internally by the serialization library
// to be bitwise serializable

BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::library_version_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::version_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::class_id_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::class_id_reference_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::class_id_optional_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::class_name_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::object_id_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::object_reference_type)
BOOST_IS_BITWISE_SERIALIZABLE(boost::archive::tracking_type)

#endif //BOOST_ARCHIVE_BASIC_ARCHIVE_HPP

/* basic_archive.hpp
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
*/