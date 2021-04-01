
#ifndef BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : Set::size
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
nWwSc9eCw18Jyn79Xa2A7ojup92rQuWLxYddNJjBdOXf5AN75lCTzsWaMmDMlHYefiAzxWKf01HZqGKcsksd+sUwzOxqjNmS5OQYIqW4QSXnETvaf8sigkv/KTTjUgpxP72rnGW1oA69l/lpMiKq6gqIFQmO0kNWqZjsJ107ji/7PTBHxR7AbmGSlUVoy8PARneWHhlESFkakOMLXhCD5KPbgCKdFICBVc2OHNIWZgO4ENmdAApDqgKFyFO2x2ldvDohzrdo+F/JgTYvbNHI9ffHkiWHUBbL0WnviZSTiCsMTtn9F7SV/9oEvGAkhd8YKQ97emt4yIJvRh7XNMxapqJZ/yYf05o22zLoLeYxjSO4506WbgIzyDyTZXDsGWXhE+2fuFdwv7y5FOIMLpnWbVS5jsGd2V2XLGq6KMc3v1Phzfkqgn1pbA3UzZNXXVmWLbot9ZAbWALIxNTa3kYkQT7qqcQ+UI/YGjEQRVETPn3IU50ioIsf6DTULQGao1ecbyEd0+VzxSBdkZiMihiaD8RsDdO+C06B0tHbHsvtyYw8LxMHeHphbI/A+w==
*/