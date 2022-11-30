#ifndef BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_binary_oprimitive.hpp

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

#include <iosfwd>
#include <boost/assert.hpp>
#include <locale>
#include <streambuf> // basic_streambuf
#include <string>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/cstdint.hpp>
#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/serialization/throw_exception.hpp>

#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/archive/basic_streambuf_locale_saver.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_binary_oprimitive - binary output of prmitives

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE basic_binary_oprimitive {
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class save_access;
protected:
#else
public:
#endif
    std::basic_streambuf<Elem, Tr> & m_sb;
    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }
    #ifndef BOOST_NO_STD_LOCALE
    // note order! - if you change this, libstd++ will fail!
    // a) create new locale with new codecvt facet
    // b) save current locale
    // c) change locale to new one
    // d) use stream buffer
    // e) change locale back to original
    // f) destroy new codecvt facet
    boost::archive::codecvt_null<Elem> codecvt_null_facet;
    basic_streambuf_locale_saver<Elem, Tr> locale_saver;
    std::locale archive_locale;
    #endif
    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_binary(& t, sizeof(T));
    }

    /////////////////////////////////////////////////////////
    // fundamental types that need special treatment

    // trap usage of invalid uninitialized boolean which would
    // otherwise crash on load.
    void save(const bool t){
        BOOST_ASSERT(0 == static_cast<int>(t) || 1 == static_cast<int>(t));
        save_binary(& t, sizeof(t));
    }
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const char * t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    save(const wchar_t * t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_binary_oprimitive(
        std::basic_streambuf<Elem, Tr> & sb,
        bool no_codecvt
    );
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_binary_oprimitive();
public:

    // we provide an optimized save for all fundamental types
    // typedef serialization::is_bitwise_serializable<mpl::_1>
    // use_array_optimization;
    // workaround without using mpl lambdas
    struct use_array_optimization {
        template <class T>
        #if defined(BOOST_NO_DEPENDENT_NESTED_DERIVATIONS)
            struct apply {
                typedef typename boost::serialization::is_bitwise_serializable< T >::type type;
            };
        #else
            struct apply : public boost::serialization::is_bitwise_serializable< T > {};
        #endif
    };

    // the optimized save_array dispatches to save_binary
    template <class ValueType>
    void save_array(boost::serialization::array_wrapper<ValueType> const& a, unsigned int)
    {
      save_binary(a.address(),a.count()*sizeof(ValueType));
    }

    void save_binary(const void *address, std::size_t count);
};

template<class Archive, class Elem, class Tr>
inline void
basic_binary_oprimitive<Archive, Elem, Tr>::save_binary(
    const void *address,
    std::size_t count
){
    // BOOST_ASSERT(count <= std::size_t(boost::integer_traits<std::streamsize>::const_max));
    // note: if the following assertions fail
    // a likely cause is that the output stream is set to "text"
    // mode where by cr characters recieve special treatment.
    // be sure that the output stream is opened with ios::binary
    //if(os.fail())
    //    boost::serialization::throw_exception(
    //        archive_exception(archive_exception::output_stream_error)
    //    );
    // figure number of elements to output - round up
    count = ( count + sizeof(Elem) - 1) / sizeof(Elem);
    std::streamsize scount = m_sb.sputn(
        static_cast<const Elem *>(address),
        static_cast<std::streamsize>(count)
    );
    if(count != static_cast<std::size_t>(scount))
        boost::serialization::throw_exception(
            archive_exception(archive_exception::output_stream_error)
        );
    //os.write(
    //    static_cast<const typename OStream::char_type *>(address),
    //    count
    //);
    //BOOST_ASSERT(os.good());
}

} //namespace boost
} //namespace archive

#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BASIC_BINARY_OPRIMITIVE_HPP

/* basic_binary_oprimitive.hpp
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
*/