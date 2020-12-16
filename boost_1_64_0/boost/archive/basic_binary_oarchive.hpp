#ifndef BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as native binary - this should be the fastest way
// to archive the state of a group of obects.  It makes no attempt to
// convert to any canonical form.

// IN GENERAL, ARCHIVES CREATED WITH THIS CLASS WILL NOT BE READABLE
// ON PLATFORM APART FROM THE ONE THEY ARE CREATE ON

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>

#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
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

//////////////////////////////////////////////////////////////////////
// class basic_binary_oarchive - write serialized objects to a binary output stream
// note: this archive has no pretensions to portability.  Archive format
// may vary across machine architectures and compilers.  About the only
// guarentee is that an archive created with this code will be readable
// by a program built with the same tools for the same machne.  This class
// does have the virtue of buiding the smalles archive in the minimum amount
// of time.  So under some circumstances it may be he right choice.
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_binary_oarchive :
    public detail::common_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
    #else
        friend class detail::interface_oarchive<Archive>;
    #endif
#endif
    // any datatype not specifed below will be handled by base class
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(const T & t){
      this->detail_common_oarchive::save_override(t);
    }

    // include these to trap a change in binary format which
    // isn't specifically handled
    BOOST_STATIC_ASSERT(sizeof(tracking_type) == sizeof(bool));
    // upto 32K classes
    BOOST_STATIC_ASSERT(sizeof(class_id_type) == sizeof(int_least16_t));
    BOOST_STATIC_ASSERT(sizeof(class_id_reference_type) == sizeof(int_least16_t));
    // upto 2G objects
    BOOST_STATIC_ASSERT(sizeof(object_id_type) == sizeof(uint_least32_t));
    BOOST_STATIC_ASSERT(sizeof(object_reference_type) == sizeof(uint_least32_t));

    // binary files don't include the optional information
    void save_override(const class_id_optional_type & /* t */){}

    // enable this if we decide to support generation of previous versions
    #if 0
    void save_override(const boost::archive::version_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
            const boost::uint_least16_t x = t;
            * this->This() << x;
        }
        else{
            const unsigned int x = t;
            * this->This() << x;
        }
    }
    void save_override(const boost::serialization::item_version_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
            const boost::uint_least16_t x = t;
            * this->This() << x;
        }
        else{
            const unsigned int x = t;
            * this->This() << x;
        }
    }

    void save_override(class_id_type & t){
        library_version_type lvt = this->get_library_version();
        if(boost::archive::library_version_type(7) < lvt){
            this->detail_common_oarchive::save_override(t);
        }
        else
        if(boost::archive::library_version_type(6) < lvt){
            const boost::int_least16_t x = t;
            * this->This() << x;
        }
        else{
            const int x = t;
            * this->This() << x;
        }
    }
    void save_override(class_id_reference_type & t){
        save_override(static_cast<class_id_type &>(t));
    }

    #endif

    // explicitly convert to char * to avoid compile ambiguities
    void save_override(const class_name_type & t){
        const std::string s(t);
        * this->This() << s;
    }

    #if 0
    void save_override(const serialization::collection_size_type & t){
        if (get_library_version() < boost::archive::library_version_type(6)){
            unsigned int x=0;
            * this->This() >> x;
            t = serialization::collection_size_type(x);
        }
        else{
            * this->This() >> t;
        }
    }
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_binary_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_BINARY_OARCHIVE_HPP

/* basic_binary_oarchive.hpp
zolH7f4LJDF4DlI8hR1CHsxphnZIW+aBvScmP6FtcYY761D+Ab8LkHGAbJJ/tDATU79E0xkqyVgi3RPY73QX3EXvkNgqyeT2TAK2tlTezMqSQv8mL6y/36dCfNtbZE/LjfPaF3hPE3tE7yk+uNXenYkT/uV+ciL8wsQlW8cG1B0QhPyYeYwmGQjlzheHYm2OJjhzcr3ao0lEofqiXFrHRPfI6XLaQDpys6rqJRYKO4SSffQuO+cWVUXyL3zwSUG8cyj4K3qLkBdL6T4JRGp6VJw50K1LHCU4+rEI5aNgViAXQrsO0FsiXo7jAvB5dEPfsNhwBG/sOi2yqaFSOpZQacAVp44m/dYcZbrP48Tx+Np95BbimPvpWMaUzEPgHMk+ulELvPFSh1qoEhcx7a0Y4beN7BC6r9I22v83ZhO/WPkv+USud1iS33WSQb9TjtJSa9shddU/6sv8Q3fmH3iqOuvaehZ30HkNJ0k7mTbo+uNTRFpOL93aEp8I9pMGyFzc9KlTFcb69Oor64Od3Cxb68gT2BDFVJm9j0gZq+2PKVA3ZOl8fu1ZedqfSvE/mfF/ojEnzF/f4ILfa/3VewVjXwPEWLCZLlA0PQayGRoekJUcp+h5DDS0i5qvPVMj5uuQftMblvlaqsauPyxj/+snlvlqc6+arwO28/WRKnMV9yW0WHfcSxi60/10T4MlqhhoPdlAQp7IHSt/q4+t/PmWMEUJPqfEpUwoskmUdQxEBb49/I/6hFo8aFCL1D5MLXL6CKW4ED8xpbcKiXjmLYNE4C2I8G9lQEhEUyYRaJaxcANy9R8Ph2iq/ybkYVdvns4iYQPv8BCRyKkhv7J8kbTinHvMs/ASoRNrFJ1AzRY6cWl/af5j2tNJf6E9HTnrYEn7mfu/x+9zuYgq/58gc9+ORdV87R3sAm3PyaKzfQUGqm0Gn5J7rRgttuYHLddRZ2wOznsvya3evJeEUGMxVSFfIkd5AaEW6K+glYLCg0rg3adv377heEFDdW/gu2QC6We2kGHmS+HFoB0Zaf0T/UZD13JDL4UbmvmO0dAA1RBe2fCgQo8RZkl+u4nlEp0SyZ6gD9XyBr3wPIzyWQWPJnrb+mGt0Bcbg4oLY/zj5jBvfNZCvjkEFsb8ho8y5sdef70v9Neru3/eHadO5BWZ2mHsHXlrrXe3kKSZ7O3l/Cc7BEPu5sN5fjcSiejzhmnLAp1RnqYzQeP5Sz337Cbu2T5n8R5X7S/JTkArgZ7kI5NiHJnaUpLx6s6cZFwrchqQXlk/l4Me1vU1uHUFGyMlBSnBGvjSFF/0IiRDQhJIjXGPltA66a4M9+z0GE9hOq72w9xPvk6pEz1wGhv3wLxGcEr09Egv/vpiV4Z2kX/OfiLO7Ij1KntCeFeXSktBWtCPhBoq4TxK6IOEM1RCfUq4GQmNVYKDEtoRn6wSDr6NhMtIbqoStlNCMslkVcIqSnAjoYlK2IsDmp/F6kOiclngJ6e/LXL/oHJfBngWKLun8NaYDO0zJGVjzPreVqzCVT94Adkr3yewjwAWy4FL61095dJ610lFoaugFWMvmYu5wr+b8K83/uXgXz7+PYd/b+FfEf45nDGxrl//iYtPcJ3Op8bK/8IP9t+cu8v7Q25yT/nfgyJ+fym/TflNEcv7G4xVGzPeubeuw5uy2KvudniE7FgT25J8guF5UH+jh9zo0pXuwh+x27aD3LFRcyzsrCfzpfg8trP+7DE6SMpmJ6AeOD0mS0p2XzG/xWYSaYGkvdFCp0sKMmfw34/EVzMgXsFflvsd6iHUYWAc9eaS46A3fcvLgzJeQTMh8nmDPLAwXpL7wPEbK2Q4nuDX7fjCgc4gObA=
*/