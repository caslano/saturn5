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
#include <boost/integer_traits.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/library_version_type.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

BOOST_ARCHIVE_DECL boost::serialization::library_version_type
BOOST_ARCHIVE_VERSION();

// create alias in boost::archive for older user code.
typedef boost::serialization::library_version_type library_version_type;

class version_type {
private:
    typedef uint_least32_t base_type;
    base_type t;
public:
    // should be private - but MPI fails if it's not!!!
    version_type(): t(0) {}
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
    class_id_type() : t(0) {}
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
    object_id_type(): t(0) {}
    // note: presumes that size_t >= unsigned int.
    // use explicit cast to silence useless warning
    explicit object_id_type(const std::size_t & t_) : t(static_cast<base_type>(t_)){
        // make quadruple sure that we haven't lost any real integer
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
    {}
    tracking_type(const tracking_type & t_)
        : t(t_.t)
    {}
    operator bool () const {
        return t;
    }
    operator bool & () {
        return t;
    }
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

BOOST_CLASS_IMPLEMENTATION(boost::serialization::library_version_type, primitive_type)
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

BOOST_IS_BITWISE_SERIALIZABLE(boost::serialization::library_version_type)
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