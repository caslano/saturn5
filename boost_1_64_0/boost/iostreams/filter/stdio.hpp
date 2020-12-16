// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Based on the work of Christopher Diggins.

#ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <iostream>
#include <memory>    // allocator.
#include <vector>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/aggregate.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/stream_buffer.hpp>

namespace boost { namespace iostreams {

namespace detail {

} // End namespace detail.

template<typename Ch, typename Alloc = std::allocator<Ch> >
class basic_stdio_filter : public aggregate_filter<Ch, Alloc> {
private:
    typedef aggregate_filter<Ch, Alloc>       base_type;
public:
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::category     category;
    typedef typename base_type::vector_type  vector_type;
private:
    static std::istream& standard_input(char*) { return std::cin; }
    static std::ostream& standard_output(char*) { return std::cout; }
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    static std::wistream& standard_input(wchar_t*) { return std::wcin; }
    static std::wostream& standard_output(wchar_t*) { return std::wcout; }
#endif // BOOST_IOSTREAMS_NO_WIDE_STREAMS

    struct scoped_redirector { // Thanks to Maxim Egorushkin.
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(Ch)                  traits_type;
        typedef BOOST_IOSTREAMS_BASIC_IOS(Ch, traits_type)       ios_type;
        typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, traits_type) streambuf_type;
        scoped_redirector( ios_type& ios,
                           streambuf_type* newbuf )
            : ios_(ios), old_(ios.rdbuf(newbuf))
            { }
        ~scoped_redirector() { ios_.rdbuf(old_); }
        scoped_redirector& operator=(const scoped_redirector&);
        ios_type&        ios_;
        streambuf_type*  old_;
    };

    virtual void do_filter() = 0;
    virtual void do_filter(const vector_type& src, vector_type& dest)
    {
        stream_buffer< basic_array_source<Ch> >
                          srcbuf(&src[0], &src[0] + src.size());
        stream_buffer< back_insert_device<vector_type> >
                          destbuf(iostreams::back_inserter(dest));
        scoped_redirector redirect_input(standard_input((Ch*)0), &srcbuf);
        scoped_redirector redirect_output(standard_output((Ch*)0), &destbuf);
        do_filter();
    }
};
BOOST_IOSTREAMS_PIPABLE(basic_stdio_filter, 2)

typedef basic_stdio_filter<char>     stdio_filter;
typedef basic_stdio_filter<wchar_t>  wstdio_wfilter;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED

/* stdio.hpp
8+WdkfPknZGLZX9YHy2Sr/kWfZwk+ZoAla2J6GUSLIST4fHwVDgKToNj4Gmih9NFD8XwLMPfYot+homOpT0qf1WG38oEuApOgZ+GZ8IrpTyb4CJ4FVwscqvhJbABVsGNsBpeA2vgDvhReCOsgw/Bj8FfwfVwP/w4fAteDv8KN8BgILR/ELwCHguvknLMDj/3gnmEJs87Oz9EzuWPRH/NUr+3ix5vg7myTXpKuEXSK5f0ehPqJb19Uh/7YSp8CfaGr8NM+AdYAP8Ix8ED0i7+BGfL/iXwILxQ4l0EX4XLZVvahazV0+cs7WJgIJSPwTALHgPVM0g4AI6AA+GxsAgOhWfAYXABHA4XwuPg+SJ/CBYTmuW8/eW8iYTxct47RZ+7RJ93ix7ugnmyrf1ISjoplnHyfklnN0yGDxj9dL/Em2X2U4sfwwT4uNTnr2AW/LXk40mph2fgsfBZOBS2Sn95Ao4TuSkiN03kpsM9cKbHf2RxfPTy/Fzyda+Up8WIV+KJZ/UjLPG+a/hXXCbxVkk807/ilyXedVIP26Q9Xy/l3C7j0o1wBLxB2uHX4AL4dbhIji+G34QrZVv7w5Xz97Xk+xo5/xbYB35O4jXrNRzGAoln+kF8T/rP36TdfCD9Jz0QSufv0o8+lPokIe1HbiiMhyNgAhwLEw0/crNgCpwH0+AiGJT23RuWwT5wBewL18h5tf82yXeiux3o6JeNNLVccydypKnlWnzKtRpyu+I6ypUZcvt9yv2DvWuBj+Io43t5kccRLk9CGiBNeb88KG8DhJAAxRSukNJQaJOQBEgbkpMcNa20TStWrGk9KyoqalSqVVu9tlTRtoqKiP5QzxYrrdSmWhUr1mtNMRYq/nfuu7nJ7uzebg7r65bfx5ed/Wbme83szOzcNyGLdEpqbLpJkTkK9asNADE+YmFS2A9GAntQkEm8Ooppd/Hi1iVi1v1nx6xLP/S/EbfuvylmXfozqRc9bl3pM4nYdbLYdW1vwO6AQ4BTgJRziDUHqAG0AXoAAUAQ0A/IPw+dAbYB/ICDgFMA5U34IcAD8AJ6AA8AjryZ+G1q4kpciStxJa7ElbgSV+JKXIkrcSUua9dbFv+vsbP9YsT/K0N8v4lF6uJ0CtYZaS/UitVLa69eW13fieP3fT5G80t85DgZpVlWvbb2iioiAAuMZsxIyHw10fD9bpyGl7MnSgOCK1YvX0NEQjn9g2iurl5Xq6eZv16gWeep3FBbvY6oOM2uwTRrVq/jYiljiObwYBrI1bRNJZhAz1OuEZ6vX/OO6ioNz6TDlaAT9LOuFlpcJ5T1Fcjey2mEPWeijoiutG4QT1VLa5cSVVSPvVGayqXrrlgmFjWGeHJuiPK0toZMJsjWHH2+rnrt+iuWVdesWcZrCsd3XFCsRH8HS3EXcsNIURPfqf7W6HX6nbDIDJ2/m8l/W9Eo33uOvOIeoi05sfcTZ4u/gUC54r7nEPGYJuyJGsjDWrqUx1YmZ6zfXBRCX28WomymcxzZ3tiGnJpz7lNonzVlHA4Yhv3WXmm97Jh7LvNWCzKLv285n6K3wxfxodxPdQmNlBkhk/9WS24Dfxw2QLnMBiJ/3lS5DQ73a/mDGm3of9LVGv0LdZ5M1ev/XereVL1OoHz7uo/YeVeaXvcZsHOQ1yN2AFz/2F9trP9gHPpHubo20J8m179LyqM9G+y+xrgNNAzT2yATuglJ6x2aHSL2VtL1dnhmCmQ8S3VFOj2hH3rauB9CvqHbAOXq2oAvXW4Dt5Y/m33Qyg3GbeBUul7/J9T+WVtnnP3Prgy97r85GvaneoQBAPf/W036n4Y4dH+rpP8JZch1H+jX8mfP99tM+p+6TL0=
*/