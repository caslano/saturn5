// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                   // BOOST_DEDUCED_TYPENAME. 
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/traits.hpp>         // category_of. 
#include <boost/mpl/void.hpp>          
#include <boost/type_traits/is_convertible.hpp>         

namespace boost { namespace iostreams {namespace detail {
    
template< typename T, typename Tag1, typename Tag2,
          typename Tag3 = mpl::void_, typename Tag4 = mpl::void_,
          typename Tag5 = mpl::void_, typename Tag6 = mpl::void_,
          typename Category = 
              BOOST_DEDUCED_TYPENAME category_of<T>::type >
struct dispatch 
    : iostreams::select<  // Disambiguation for Tru64.
          is_convertible<Category, Tag1>, Tag1,
          is_convertible<Category, Tag2>, Tag2,
          is_convertible<Category, Tag3>, Tag3,
          is_convertible<Category, Tag4>, Tag4,
          is_convertible<Category, Tag5>, Tag5,
          is_convertible<Category, Tag6>, Tag6
      >
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

/* dispatch.hpp
87d1CKcObsNUARcmMyBa3/CEJS62ajpfYjEQNuaLKFT+dRXBz/1GFdK7EWKzalZmU5xnGISlSf7ih2UVqinp6WIUD3R5vVfmmT4UpD8i66GN2zk3G9Zo3R2RHgcUQ1XY1LN14KYvcNqeaFhJebM/FZZJORTEu8KgmThVdufLJIZCdrlJ7iTgGFY2vTJKbQX549EBN7two++WB2MG6hrB4uuPRsdOVx+61xYobFlqFSMI9Eepms6guDkatvGPTxWXwn2YB0Nz2AAlFC/dRf8rDfFE0vXHkLBSolc2sqTvNQ+BZKm2rRbvwtLy2Qwu0iJ1/mK2+AI8bgQfiq8t5D3Vx5lwu/igsRQYQ7LWk7QqWvxiWBznBOi92YDiyilKwRQ3jIV3SaoTPA3QrHPvdHII1uhgihOBrXZ+6ScPsBBcBt0hSve8cs8EV5z31poYG2gWBI1JtaQqzueTbXUuWt1IZdzhY+cnFR/NfAb3lHyvNWuIdBbOmqEMcFv7DEhx46T+NOVPd9xUsdUHlkSRVahA+fm6FnNBCnFUyf9uoPt/pwOb+rXVba5W7jALBQ==
*/