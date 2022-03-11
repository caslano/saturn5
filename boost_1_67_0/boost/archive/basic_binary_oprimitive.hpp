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

//#include <boost/mpl/placeholders.hpp>
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