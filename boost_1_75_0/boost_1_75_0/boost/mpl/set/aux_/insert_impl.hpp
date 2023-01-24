
#ifndef BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {
template<  typename Set, typename T > struct set_insert_impl
    : eval_if< 
          has_key_impl<aux::set_tag>::apply<Set,T>
        , identity<Set>
        , eval_if< 
              is_same< T,typename Set::last_masked_ > 
            , base<Set>
            , identity< s_item<T,typename Set::item_> >
            >
        >
{
};
}

template<>
struct insert_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename PosOrKey
        , typename KeyOrNA
        > 
    struct apply
        : aux::set_insert_impl<
              Set
            , typename if_na<KeyOrNA,PosOrKey>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
xsAGkqKZvUaWRpikaF3yoLsCT6Ulfxh1m7Dhl/gJcRyIeWkiD6eu4hL3bLgwLOH6MzVfEWNLjKK8x6+e7UvHPBDvIknd8j6VGOSXOVOO33GxW3zOqVu8ThglQKNn9m4I8EShgP1EfS7MFlAmO+mOLfL5M+e47nJ0pqtHBR/lI7cq2H6jwLCR/8qcwUdLcwY0X1cKAJMUfS8pVpG+P3mq0j/sKbz6oD7cbGQoOe7A9TTbFeXDP5UHims2vwE6dtNHhbLfSvSsdzWtL+ft1ppzZhxt764vT/7xyjbkuDp/Wg9xDLVnForVsd2ghSz/ShrpoNqoPDyXSOF4CccGeyWQdSQFR/YolRo4E7C3Y+qlhwNChZxxHhm7sIW4PZX/QthZBMXhpFE8eIAFgv/xBHcS3AYI7u4aXAd3mQkE1+AOwd3dCe7u7i6D+8xmd6t2L7u1hz70obsvXdX16/e+7+08C46ZXsjoV2x2v3fGoHKwIKpdXYTwHI6cgkvuO1zXAt6uemDVC022DvMbuaHFEACSR+jTWntoLNoAOWPNboFfw8M/QqvzYjfFL4PAM6skJ6FuQY2BATXD0lJWfEwJcT2CU/RvwIJNigzTnbEs1VRo553fau56ThsC0xumyShjJ5i3SwQsd8ajAt7TQzAw5qhlz7wQ38xWli+XhP1lOrGqAfZVeDR8LGKqvp1BBR/CHVcYMzXB6HGvZI+SN7P7
*/