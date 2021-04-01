
#ifndef BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

/* size.hpp
gDW+iF4LY6jwX3Plb7WAQiswRP4yV0F4yVBN5XbZqbxHbTKPfL1WdfHXF1hkOSXzdJ2Q5RW3UOUYDwrNave6/vQmWyGXwYa2qOZO7nDme+G6Xgq6c/BDBqerJu8GPEVZqmzLa3xjwglvQuYjWWPnLKlaN1hcRrJVT0vxcNN2msisOURtqdT8hHMU6kRiY8bwuQQ2OO2pxFwbKDvHgNzxjlmIStf5lQiW4RSNBrzgW+ryz+87kNESYMq3TBP0A2lfR83wvi1NXHoBgFzGqgMkmqIqqKBFrAUd6NF3e1u8r96r6I5fjvzwc+QvZqUwlKL7eAlHMBhdC0OIDq09OcrEFqpYQCyK+w98dfFRbld1hKI5luqqEze57bcMGro2T2hkEOnXo8m4IKpimASymM2e0gMu6WiL5n8/FBJGOX3AUTKHoL7ybaxRNmCl1F/2AgX5oN95QnL/WeRUuxqOMoPK4dXoZqdyKOQ69eZEKmk4xDLyW0UATSfGfSpxmUNXo8bdnvOSMk7AiYXTuT6k/eEKjSkEoyLxeVSthprUL2SEHHkQuUHa9SNUapiFLw==
*/