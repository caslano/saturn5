// ----------------------------------------------------------------------------
//  workarounds for gcc < 3.0. 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

// There's a lot to do, the stdlib shipped with gcc prior to 3.x 
// was terribly non-conforming. 
// . defines macros switches
// . supplies template classes basic_foo<char,Tr> where gcc only supplies foo.
//  i.e :
//     -  basic_ios<char, Tr>        from ios
//     -  basic_ostream<char, Tr>    from ostream
//     -  basic_srteambuf<char, Tr>  from streambuf
// these can be used transparently. (it obviously does not work for wchar_t)
// . specialise CompatAlloc and CompatTraits to wrap gcc-2.95's 
//    string_char_traits and std::alloc 

#if  BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
   // only for gcc-2.95's native stdlib

#ifndef BOOST_FORMAT_WORKAROUNDS_GCC295_H
#define BOOST_FORMAT_WORKAROUNDS_GCC295_H

// SGI STL doesnt have <ostream> and others, so we need iostream.
#include <iostream> 
#define BOOST_FORMAT_OSTREAM_DEFINED

#include <streambuf.h>
#define BOOST_FORMAT_STREAMBUF_DEFINED

#define BOOST_NO_TEMPLATE_STD_STREAM

#ifndef BOOST_IO_STD
#  define BOOST_IO_STD std::
#endif



// *** 
// gcc's simple classes turned into standard-like template classes :

namespace std {


    // gcc has string_char_traits, it's incomplete.
    // we declare a std::char_traits, and specialize CompatTraits<..> on it
    // to do what is required
    template<class Ch>
    class char_traits; // no definition here, we will just use it as a tag.

    template <class Ch, class Tr>
    class basic_streambuf;

    template <class Tr> 
    class basic_streambuf<char, Tr> : public streambuf {
    };

    template <class Ch, class Tr=::std::char_traits<Ch> >
    class basic_ios;

    template <class Tr>
    class basic_ios<char, Tr> : public ostream {
    public:
        basic_ios(streambuf * p) : ostream(p) {};
         char fill()  const { return ios::fill(); } // gcc returns wchar..
         char fill(char c)  { return ios::fill(c); } // gcc takes wchar..
         char widen(char c) { return c; }
         char narrow(char c, char def) { return c; }
        basic_ios& copyfmt(const ios& right) {
            fill(right.fill());
            flags(right.flags() );
            exceptions(right.exceptions());
            width(right.width());
            precision(right.precision());
            return *this;
        }
     };


    typedef ios ios_base;

    template <class Ch, class Tr>
    class basic_ostream;

     template <class Tr> 
     class basic_ostream<char, Tr> : public basic_ios<char, Tr>
     {
     public:
         basic_ostream(streambuf * p) : basic_ios<char,Tr> (p) {}
     };

} // namespace std


namespace boost {
    namespace io {


        // ** CompatTraits gcc2.95 specialisations ----------------------------
        template<class Ch>
        class CompatTraits< ::std::string_char_traits<Ch> >
            : public ::std::string_char_traits<Ch> 
        {
        public:
            typedef CompatTraits                compatible_type;

            typedef Ch char_type;
            typedef int int_type;
            typedef ::std::streampos pos_type;
            typedef ::std::streamoff off_type;
        
            static char_type 
            to_char_type(const int_type& meta) {
                return static_cast<char_type>(meta); }
            static int_type 
            to_int_type(const char_type& ch) {
                return static_cast<int_type>(static_cast<unsigned char>(ch) );}
            static bool 
            eq_int_type(const int_type& left, const int_type& right) {
                return left == right; }
            static int_type 
            eof() {
                return static_cast<int_type>(EOF);
            }
            static int_type 
            not_eof(const int_type& meta) {
                return (meta == eof()) ? 0 : meta;
            }
        };

        template<class Ch>
        class CompatTraits< ::std::char_traits<Ch> > {
        public:
            typedef CompatTraits< ::std::string_char_traits<Ch> >  compatible_type;
        };

        // ** CompatAlloc gcc-2.95  specialisations ---------------------------
        template<>
        class CompatAlloc< ::std::alloc>
        {
        public:
            typedef ::std::allocator<char> compatible_type;
        };

    } // N.S. io
} // N.S. boost





#endif // include guard

#endif // if workaround

/* workarounds_gcc-2_95.hpp
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
*/