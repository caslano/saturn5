// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED       
 
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { 

// We avoid dependence on Boost.Range by using a forward declaration.
template<typename Iterator>
class iterator_range;
    
namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iterator_range, boost::iterator_range, 1)

} // End namespace iostreams.

} // End namespace boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED

/* is_iterator_range.hpp
nxtr0do8oseOzQDzA0BNd5uHcEhNPP7tXo+YGgPhuvk1zENQZ37W43C+ilmxYAKuqXDurFD8MzzBTsogXb3OsvibwFRalT/GpxrQkzGGX4dkXvnrO2HWAp+idIcECHOpBkVOnMEI2m1Ep0t+OVZOPL4j3aE0DO6YosEq+Bd9BkKK5uEWZB/xLwrGdAQx6JOG7D9sVKgyomkblekxi4dv5YI8GqX0oCuCmVhaxR+fAlz2r9E6tP7wRhaUh+qR8UvDOJTbg+zaC75/382FKEhWJu0lki2OFHjVh0/0vvVG/oK4NYP/QNWIEf6ZJJNYh1sbcSioAjk/vPTI7l8J87Ucasn/6grfSjZuKnk2ReQ3EtoP9aEAz8/1jTYcIftwhzp7BHaBzCPq5+HFCGMjoeYOFPQlhv04l5xuchj26bdygXYbLC1InRGdRm07zPokBPDZYKD3bRXcnz/kjn7RaBbPVS+cSKKi8O7JemGd8PqZQtsT9X7/4sgqHb/JLJ1cmFzg5L+Z6IlgNX+2DAnaXxiwguLJVExg/OavUaZyLMdmn2UFyxIpTlqAmV8fv2adVem7wNuooEeqGc0xzhUNux85XE16IknTCHuGP3KkZnTOO2qrWbrOcJpfabu27F73MalJqvUh5sIg9FPLrlURrAwy79Rw8gs/+ng6WP5TKrpS78ncsaHPU0QwaC5XVzhn1f8a3+9muuRp9gU5qUur
*/