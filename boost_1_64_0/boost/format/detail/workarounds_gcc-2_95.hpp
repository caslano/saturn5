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
UTHwZQ1Z+VNY4pKhTUH3rB/4NBe/mcndWADhTwnE2qqXg3zOhkTjqpi1hjd0ozubJ0o6m7EAdTf6VzbtWl5acXaDhRKzoK+AnyESEsgZVx8A34+C8rX6eGSAJ0e44LgQWnhAI27+/YB83QB7Q9bTSS6jRGwzqjCXr8Jpjtjo0bzJZErqzVUTEoEMyVfz1Lyd/ODlZ6WA/Ls5FUd6X8RDn3VrdEo5M0xN1Pt7VlDqCWMr5HIfV4W5WrcUS11MzcuwdMtuIjaLhk6i46184gJ1zJJ41XYMRoEy8OLne+1/F8nJaY6gO9pw6+Aiwn4HifBnyiz2+RwvkhRs9zw5Wh4anSJO5lpplwUhU4dyGbLHYSqAi0aBbVNaNHwhqntAYKINuXVy8U68bP3LYFyqY3E7dJdXV6yD/jSTPeVR/d8l1m+rhb5WaeRshotS9JbkSAPWjMPvxcJVtF4MXfVjQkjlb9y+OS9lwFk/pyMEwQtuP/qY7Jep+Qa/sXIKMYTR8PlkbWr1w43OJ6khXexR3FYDrPNeyQz4Ne7AyIriDhj5fh0JB6flDR4OeM4JgQ==
*/