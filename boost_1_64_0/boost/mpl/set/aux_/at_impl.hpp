
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace mpl {

template<>
struct at_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef typename if_< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , T
            , void_
            >::type type;            
    };
};

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
i6T4/6tYw8T/MaluoHpyQEjQ5BL8feOZmTf2o1BARo0K1fDL8NVb/dsUeOufev9NeM9QvxHkJ4h2JLEFwH7GbhKrvG8X1/ZXoFe6d2ZHCiXjyFVVUkjf490nLhb5datI+oaPgIpInQ2Cj/4KB//IAjH/QsiQHIX0zuXcg5JfY3wYpTFHL2zuAjH14/E0rlaGSWPDNsoZPzSV5l/BpylpZgBdOYsLu4lzpsDGfwTA1IQfTDHyj19dPVX0lv7xVfM+/b2r/viJlkP7IuN8SWoCP//OgooErbg7ZruWA4EUz1IWITeAAg76YkGcPtHAyFbnix2MK0mDpqSqujbev5j9XySBBcYejjY6lELUulkSGp352ZIb8pSagXRYLdzsZQD22Hrbtaj1KCXaIH2ZCSuQzn6ftdqPqnG0qdFXkqZWWK+3dBsYn+RmAZZcDY0x8GZMXgtJbMkdJRQC4/Uv1Q6FNtI3I1XdefGwBCLjLrEbDPs722aynIm0iCq4qGD9jDIS2A3wX0fa6ChKz0woIcMp5JbKxuBgSNMV3ncXE8lbfXP+yafQ23wkXEDp4g==
*/