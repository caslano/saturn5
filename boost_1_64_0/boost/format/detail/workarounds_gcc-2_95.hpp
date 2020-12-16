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
1/bujeveqZP8drdu0/8RGDg7PypqU7dz58Yk5OXtavP69ZFHa9aE1Pv27eURH5+xV4KC5ka2by+cPmZMzXMczl9mX748rWRoaDRi+PCfBaGhWb6dO6fsXLTI8sGqVd3f9eix5OfSpf33e3qm/zVlSsX1f//dZfeCBc39XVxkRh8+vLmzezfvwLZtyarr1zfymjf3tjczYzcsLHxU4927H4kXLuwLPHNmRJ1q1cyda9duZffixaF70dF7l8ya5Xza13d8p/r1bXsdPjzt7cqVkSOHDfvu5+4+eB2ff/xJ//472zZo4DhDoXicFROzf/aIEQ3Oh4QsHH7z5lJhixa+w9q0iVibmek2avz4qie7dp1o/erVsYu5uQmd69SxSr19e+X9AQN2N6latV7SjRvr3e7evdHT0ZEf7OqqbGpiUudGQMDfJpUqVRNbWPg/7Ncvt//Bg4skFy/ueb1unc+K2NjDq6ZO7bRsxgyHjg8fXsxITX3r+OTJJZ/jxzN6d+wo2Z6YeH3ipEkG/EuXNl8IDp5/d/XqgK1i8dWvPXuuq/z+/TvLZ8/ObRQITk4ePPj90w0b/MyNjc0u7dwpHZ+SUiC1tOwmt7XtZ9G4scubFSt6Hdu6VdHj6NFZLfPzTw25dWvxfKUyv3mzZh63unefeXPPHu7YjIzqY/76yzRTJrvr7eEx5HBOzqA1QuHpq/7+mRUrVKhk8PHjp1o1ajReyuUejHZ2HvilV68NeTt2iKaOHVs/6sCBOa2bNHHdsXBha5d7967V/vz5efbs2W3b16zZYpdIdEF27drqCZMnV145fXr7bfPm2bRo2rTz3+PG1WU/fXoi4OzZcYWRkWtSrKxCB9+5s3zKxIkVPi9e3Dt9woQq9atXb3h93z6Bw+PHV456e4/OjY/PO+TlNXLTnDnWyTY2fWqamjY9tWlT2veIiFWXd+1KdK1Xrx34Lwf/0eA/B/wngX918N8D/pvBPwL8Q8G/AvivBv+h4N8A/GPB/zH4zwV/DvgvAH9P8B8H/nXB/zn4nwD/quD/AvzjwP8H+D8D/33g/wn8Z4J/X/A/CP6NwX8D+A8E/z7g7wX+huAfAv79wP89+DuBvzH4TwN/BfiHg38X8K8G/mHgLwD/AeBvBf6Lwd8U/HPAvwr4dwD/eeDvDv6twF8E/mfAfxH4NwL/heCvBH9b8LcB/y3g/wr8v4H/R/APAn8u+J8F/zTw9wD/QeA/C/w/gH884R/824F/DPg3A//j4P8S/PeCf1fwvwb+3cH/Nvj/A/zzwb8b+CeAfxvwfwT+9cD/CPhfAf9I8J8O/ufA3wz8K4H/CPAvAH9f8N8J/g/A/x34/wT//eD/F/ivB//d4O8P/kbgfwf8D4C/Cvx54G8P/g3Bvwb4J4J/IPjXAX9n8LcD/3vgvwT8T4N/J/DvBf5vwX8k+PuB/zrwfwL+bcF/Bvhngf9s8D8P/sPBXwj+w8B/LfiPAv+T4G8N/hfBvzP4p4L/ffBvAv5J4O8G/j3BPxj8m4L/DfA3AX8x+D8E//7gLwH/1+C/AvxXgf8y8O8I/hng7wj+PuDfG/y3g/9E8OeD/wXwvwv+W8H/K/hXBn9L8N8I/pPB/yn4m4P/JfAfD/5S8JeDvwX4vwH/Y+DfA/xbgv8Q8J8P/s3B/xb43wT/seA/Bvwzwd8b/A+D/xrwvwr+FcHfAPxrgf9S8I8G/y/gnwf+U8E/Cvxbg/8O8HcB/9rgnw3+7cF/F/jLwH8C+K8E/23g3wL8/wZ/NvgHgH8h+KeA/2DwnwL+n8E/Hfzrg/918HcA/6Pgnwv+h8B/E/gng39N8D8F/t/B/zL4u4I/D/yHgH8y+KeB/1vwTwA=
*/