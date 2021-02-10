
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
1go/d3y1VLoyObksipF/wfnw5no0vC1IqWQtJlCLhpOMbqAZDdk7cMv1guvYiAoRmrfNCk8rZlmoR5O9BPZ7PRhegVmaslGGkzNmeQrFnH+EXh9+qAUikh4kB+lBP0XsxXVBQt0UnODY+IDW7I6TUyUtlzb+zuXETlNIEkLGDQuLoLJAntEHMajxtBEuI2gsfYCAUDQnU2tbhK9DyCSb8aAemKwgPod52yhWgZCw3RDIaIBmxlZC5gSRbmNQMSl440KrVDMo59oHLmnwpVET6i51lOzZe0vmyBuzCUqCAUSRExKKQVaq2QwFBIUppbuXOJJvo3TXSRsNbwq65HTJpKVHCcRXEGPyY84O/OJQao6tBjsVxrPDmNdKuw08C0jAIyEX6o5X70jmQf4O0b86o5zUSsWkcKVwMZi5cMw0kros1/F1a5H8J9eiXoGbBbDacu05XT2YMoM6uITITJXFGy881rdRizYnv9+vZ1ysWjTKbN5Y0TJtKYqfxa7myZ946/mw1/V989lZq5VVpWpy4iwM201aO7JDLpWxKTzraId8LUve4lGXdjvPvHbQO95sviwOxmouK6ZXg/iVp8/r4+pwv/f56PBTh3TIa9in6LWGM2FaZYQVSqawJSCM0L0jVzoY8i0onME9hTP5
*/