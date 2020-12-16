#ifndef BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // size_t
#include <climits> // ULONG_MAX
#include <string>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>
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
    class basic_oarchive;
    class basic_oserializer;
}

class polymorphic_oarchive;

class BOOST_SYMBOL_VISIBLE polymorphic_oarchive_impl :
    public detail::interface_oarchive<polymorphic_oarchive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_oarchive<polymorphic_oarchive>;
    friend class save_access;
#endif
    // primitive types the only ones permitted by polymorphic archives
    virtual void save(const bool t) = 0;

    virtual void save(const char t) = 0;
    virtual void save(const signed char t) = 0;
    virtual void save(const unsigned char t) = 0;
    #ifndef BOOST_NO_CWCHAR
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    virtual void save(const wchar_t t) = 0;
    #endif
    #endif
    virtual void save(const short t) = 0;
    virtual void save(const unsigned short t) = 0;
    virtual void save(const int t) = 0;
    virtual void save(const unsigned int t) = 0;
    virtual void save(const long t) = 0;
    virtual void save(const unsigned long t) = 0;

    #if defined(BOOST_HAS_LONG_LONG)
    virtual void save(const boost::long_long_type t) = 0;
    virtual void save(const boost::ulong_long_type t) = 0;
    #elif defined(BOOST_HAS_MS_INT64)
    virtual void save(const __int64 t) = 0;
    virtual void save(const unsigned __int64 t) = 0;
    #endif

    virtual void save(const float t) = 0;
    virtual void save(const double t) = 0;

    // string types are treated as primitives
    virtual void save(const std::string & t) = 0;
    #ifndef BOOST_NO_STD_WSTRING
    virtual void save(const std::wstring & t) = 0;
    #endif

    virtual void save_null_pointer() = 0;
    // used for xml and other tagged formats
    virtual void save_start(const char * name) = 0;
    virtual void save_end(const char * name) = 0;
    virtual void register_basic_serializer(const detail::basic_oserializer & bos) = 0;
    virtual detail::helper_collection & get_helper_collection() = 0;

    virtual void end_preamble() = 0;

    // msvc and borland won't automatically pass these to the base class so
    // make it explicit here
    template<class T>
    void save_override(T & t)
    {
        archive::save(* this->This(), t);
    }
    // special treatment for name-value pairs.
    template<class T>
    void save_override(
            const ::boost::serialization::nvp< T > & t
        ){
        save_start(t.name());
        archive::save(* this->This(), t.const_value());
        save_end(t.name());
    }
protected:
    virtual ~polymorphic_oarchive_impl(){};
public:
    // utility functions implemented by all legal archives
    virtual unsigned int get_flags() const = 0;
    virtual library_version_type get_library_version() const = 0;
    virtual void save_binary(const void * t, std::size_t size) = 0;

    virtual void save_object(
        const void *x,
        const detail::basic_oserializer & bos
    ) = 0;
    virtual void save_pointer(
        const void * t,
        const detail::basic_pointer_oserializer * bpos_ptr
    ) = 0;
};

// note: preserve naming symmetry
class BOOST_SYMBOL_VISIBLE polymorphic_oarchive :
    public polymorphic_oarchive_impl
{
public:
    virtual ~polymorphic_oarchive(){};
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::polymorphic_oarchive)

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_POLYMORPHIC_OARCHIVE_HPP

/* polymorphic_oarchive.hpp
XEvI4jys7KUa+b8EyKKELPIRV9KdzQJnOfQ7wAwSh9g/DGMhxiqYZ9WJuMsmsubYMa8gHYk5d1lN8OVmwJdn9WHgGFaXGZNnKlcKBTSj0Ed6x6kmZri40MAMlxbWAUIXFtbDDJcBH/BfbDZ9vjT9iKXpNy4zm+5oNt25btNHzq3XdBc0nfZlWg2B6yfPFdvGh/AX1e+YI3ZfvquZuN77H+F8HR9W9R1Ttpf9f803WBN/3mKyJnZY/c2wF/ZmuXy4riADxW9YZZfmORt8DTFwLVUWnBTW2KYvwytMXtctvmhmzla+aMQyVZXX3yEFPD5Ez+TQIcJjpkkPpmeaHcoy9BM+ny92cdjZMnTvyXimqQX/55n2basM+D+gIfivygNfMsoPWd0Q/JfyAv+zQ8B/S373lSHsnyz5nxaEsH+y5M8J0f7n3mC+fWYI+ydL/psXhrB/suSvur5R8SIYobpK6kHKDmeOuWlf0kFC2fRc7Vt2VHlE33elqaGVNdm0+kjV37+Y3RPlaHv1rHkGE1U05paDQ+O0eeYt/9kGSOYppL9hNk9X+hsOjOdOBm/khFPbhnhcdOs8bHhQvaR2Dl3/AD5UYucELjFB/HR/tgh6Mxznvgv2l/LPLQRMGoRcBFXoz80I876laY+SihbB+dyMo+lviu+cBjOUUUkKgeyjBv4KDxwDzUbf6Gy+2dn9K6WzT89FZ3LxslOpl1QxxEdfQrzPRrUsVGOwI3U7q7qPoa5/FCpmUcGebOUvdUVVV9vBDeZoIyJQ0eXbF0G1DmahVjvUKqTc5lgfqOsaFTH2MAJq+azb81dgmvq6GaRgfJ3SK78eXQPkLSlhuMnr4kR/4kb0zv5oOgrfAqNas/NTDFc5S8fjEAzn9ZuGYT/pT2j/q8VzDH1SqHWl7XThTe96oakC3Q7KteRKVmI5Zaw0AlgeBhWrievsRjtQZckKB9YTR8QzxVrDDJxxdLaMBIhAKkJn5OIRZ55yLuw04sjH3KghzHvrixN0bL5x8Fo+J6jfjAJ5tFKkkJM8f85QVthiq0/wf4hIfojGWAMM4Qw09YLZ1JZnpan2aMrfojiwlBpJuVYSmyBRnouh1/Fl57Dx4sm8MEFfv4oc8ufD/xvMSrwxMLfUn1mlJHGZK4B+bM4/EECPTupnkTR54yrj1Vg4WGJxzGC2HuZPK5tu+EA+tWE4+BOa3w8QaAT/unpWMPjXPsjVEJCBYN6OQbSAyxIYeZZoTzj6FMkfUmHjaiD0VUcs7HjE02caNYdXt+AFmXUFLqHvjQja/0m4vwRUZ6UFOHyYPnuQ7M/fJWr/Lc5oZVWzrYi5f8U13LINLUujrZ+RRq8cIRXfFsfm+lHgciqE1s4F4grzxQIqAjx4vZeDR7vQOPILnLkb9B6q+i3MERwZARioOPznACYqXys3UD1ch9JhEaSX92dErPthuLT93lSzu025BF7sAl72LZDhZUwUzWex+dEGym53xG5zSUTREnRzEgfVYhG7ZXFB1H609bf/qPf/asv7nxni/bfkT74sxPtvyXcsC/H+W/LnhGj/86ss/t+WWvPloG6QfNfyffxCXeNafpjf1v74wo9rK/4SbvMOz9HyJURZdQecbv6Fd3RSAB9OLbkAJxPkPEsP59IRQy52saoo2uaNxped+KLbQASbxx97Q38adTMV/0/Gq11H0oLHIzwJNddtwrcwU48ImmkM7kRDoQUKhXma1FxHxoOrPB887qAfW4mH7tnGwzi+YmFt/G9myP6bhe7/UHMUMrvMQv9qMEg+uf4T6/TfRPXvGVCr42V1Oj7Dt9fSc1MUTZAfSebAT2w0Jv/zShnPDRV8Ed+sqTTHFOEpoDE=
*/