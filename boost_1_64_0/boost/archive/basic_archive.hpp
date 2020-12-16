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
v1R58GvPqvEsUGai9uNfWqF/302Jtv+XGvv5RaP+w5uivs9YmeiBSw0mOuUAv8B42F5OvU3Ge9Mu9MdDpiryE9TPGiz6WNo/EtTA69ESWJDSqjj2GEJmeLyFowlr8fArsG2ISQDe/gHuoM8i/y7PyBWiVYHw2jWUwg9uErWVCgeEukuNd53T4JrV+b/EnJ+xan4+j/Z+c+8SU3/2GQU/ygpvH5+6tZQSe1lgonvkTF69qx3u/LckkuEvaJ710PBOfyVq1A5BDtuELk2NYHpIc4aMc1g8mxsTKxppgHhYROk/Pksih2Jqy/WUiHZTRYDvr2dwGyJX4IsesVNfOURpZlgzeT/+iKtYRlUM3WIqWmmllrI6KTP9VkGaFf4vNuaz2Rg1n6kbouF/iXnejHY5lHc28zWoanukKSVhpq2MaMK5OCjornoWGKccTMN7WFbsxu34oztBU2HVshWt/Rm9U8GIJq5Xq9OCfJjjHluI1aFMfdgUdjBdSxC3oHkQC/UrrZcqHf8iy/vXHJv3r0Umv2Pg5878Su2Jn6lAj/IXmfbERvnWENBWZf8upZS/jCWzzWt1X5qK22EfSVOEQOCotw/N7FaIbdUBRmBXebUX+DugW3lJYdNfTy9hAWJ7l5iG4fWpvHX5/lfFhrv2pOCphjqo6P+hOCj+kmV75iTSME7OMqUBj9A+vNcbWBAexkvYr3ojHsaTxjDaezWGIOirONZTXf2XiQRSg7JbiNqZhv/W65eg+0hLjJT7EfedOvHXDSnSHor7Isbx6SzDbUKDi9McBTEqlzJYeAhBYlX6Un9ZKLbU2qFwnP3rJRi6VCYtaN5ESkzUn2FbEMWk5CbaWv3QjNztDcwJz2smNpo+f2M59Ljegh4pQI9EQo/33w0ryJ5DTxzihzwylELaG8HQb2rnYzO/8TyFJfb5Ev3Ageyo65Nkvz7IqO76rPi0muuTJOvT7jPr+iRVc32mFGJ9mm2Iuj5JtD5fTeb1STLWJ8l+fSa99jutj3Ef+PCTMG0q4F5i9BxmC0RyNUR6+pwPwxNRmu5yVONyaan/Zrv6z5ag6A9R9XdYq3dUs3by/+5N42WDCleJpb098832rGKgcovkeNoF5m1duUXaxH2oZuNh/n++wR9N09R5MHNlNP5/vqnfb8D3iwbfeL7F/mWcjf3HPIv9ywc29h+W/C3lHhrTu90mIB8oEG0O3dyIkQUDg0MdRmldMrWdpFjRnTzQio/f40T6j42Sl2vSsSCnNvGo5oJRNJ14xqEMTfnH9UI/Ec/myxh+6APaJvzW22DAmdpiUnxYpic9aZ4it9AzoN4Wo7j22xgH9og3rbU7X+4nzYPn8usRToZakHPRc+xgIyHmBTH8R914Q+8xit/Qx5u6DOgFHRrbR7OwejZEe9SJvTPISpeHxOPDYJlzyz8wLEm9U01DCX0+MeClHRnrWc2hZc+7SqAi4BkxZiGlISP4wsrf4QN8Tuf337kmPuMJvyVtTPGtETNG5kFQPB0oDh4AygafQ4QgCVHrp23YXu2Z6XPMNiBk+4jv7jfSFLxdSPt/OimFvi9Kp90K5GVxMETI5lax77/Cr5uk8pQQVZ/GSJZTq7Cjk+fyzhJP0S1S84lRYLALvSv1vkPlzsNWwUpp0ku2lukqnki/REZKtgPtn1Sa3kiiC6fOfUZoNcWLLM1koYGnNIH+CPIW5jbChqcOiDaLvOPUpQdvGGvqSA/C9oU8NiDqcVquyz1yA9JInfMgKg4r+N/qIgzaqtKUnw3uoPjGuF2/42UZQqKqm5xQlNEjQIbGUGt5CqFKU4CfpK30lKWSuUFgPwE0UrXU5Fr8NwQbqpKPPR5UJYdeYZY=
*/