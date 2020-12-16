
#ifndef BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/config/operators.hpp>

#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING)

#   define BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
    friend R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_MAP_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
/**/

#else

#   define BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
    static R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_MAP_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T); \
    using Base::BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f) \
/**/

#endif


template< typename Dummy = na > struct map0
{
    typedef map0            type;
    typedef aux::map_tag    tag;
    typedef void_           key_;
    typedef long_<1>        order;
    typedef long_<0>        size;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, VALUE_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, ITEM_BY_ORDER, map0<>, long_<1>* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
#else
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, IS_MASKED, map0<>, void const volatile* );
#endif
};

}}

#endif // BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED

/* map0.hpp
GLwFs/FW/A7T9pLrq1x3le1l8jpJrsVHyvaOwjAcgf1xJA7FY3A8jsJ8HI2TcAyegpk4HbNwDmbjPByL8zEHr8BxuArH4114LN6HubgN86S8+Zgtc0Hn4qmYh0bMx2I8CcvRiBVYjlNxOk5DE1bhGTgdr8cZuAqr8R6sxRY04eN4Gr6GdfgV1qNBYiX74iw8BM/A3jgbR+GZOBbPwsl4NtbiHJyF5+IcPA8X4Fy8G+fh03g+tmIjfoIXYDeJleyDF2EfvBhH4kIcjU04FhdhPl6CJ+ClWIuX4Wm4BGfhUjwXl+F8vBwvwSvxNlyOj+FV+DhebZvTXP5fgD3k+6ie0/xamdP8OgzF6+Xv2khr5O9KJCYTyevtfsRkkrEXjsVIzMUoLMBo+f7FYD32wdkYi3OxL16IcXgL9sOHMR5fwQT53iXiBzgA95dYzCBMwiwciGNxEOZjMk7CwXgyDsVTMRUz9ZiNHrPpQMym8NIgw2zSctL6S/XYjb7oy55aur79v2KWyai82P32/1gZ06/oVKUOpWxTCS0Ya8vMjnMAPsA62VK/2iJxgo8kTvA+aXY6/08PttSvLHWrwpMYTGtqhdm6tQpze48Fg8G3dujRIa71rdFOzxAcEmipJ9vaoWN4X15iLnGe625myWwjVVvnZwqc2qrt466flU4+5pkmg9O4byvk/nax7HcTaQ7rrglx2e8O7LN6H2VMeTf7FOxmn3Y57dPP6hiC7KMyT55J9sd6Hk1STz9Z9ucE0rnpfH6I0/7Ua5/HCB/2KcP5vJG0zttBqvPG/tliID3ZBtnb5vObpXGOoqTuXyr7NIXUwLqtrvvksD/+jGWR4eEcHaQ6R+rzk6yUv95xbMTFge7HRiyW2JXqx+jXHJcNpzqNjSjxhKJOfC6mq+MJ/j7n4m/8wf3YeP7HGfyNJ/gbN/A3ThJxrWV/N2d/8EbDkOdG1d0SVVu17k7/x+ToSJxhg0H+HyD/b2jlRQ9cK1/SSVI/OwHD8ESMxJMwCU/GwXgqZqMRc7EY87AUC7EMp2AFmrASZ+NUbMAqvBBnYBNW42qcifdiLT6Lp+E7WIfvYz1+h2xLrunsj+xHd6yW/YiW/eiLh2EcDsN+OAIT8DhMRCP2x6k4AGsxCU/HgXgRDpJyJkv+7JNcgzkmkn8Qlkv+x0j+YzAUM/FQzMJozMZ4HCvHNQeH4ngp17FyHHPxBJQ58TjOcp3EUsl3fyyUfINVzx1FYpjk1wOPxJ44BsNxLB6KJ2EvOV+RtjHw5Bon175W9XwVEjcq5/u3ZnGQT3Xf1ibX+u/yjf+dOnDLxq6tB2/bqFUXdh5b7t9dJ36V75PhsiBDIqmQNOcyvV6sL/qiL527dH39n6G8O3H8vxZV/3+z1O0fwAPxXpyXzv+vD7KOIW4f/8+3eu3eITsPdp7v3bXPeHe8OMxeTwzG7TJGgNTlrWOMTzVPs7eZTpB56+11HK1nw7u+7vNPq+P82+syuZa6TF1a0IkjHz3gx96zDpw/+JOXevlfl+nM8QUjuslvQX4jm0kxvO6OyhIh98iRGIlR2B974yg8DHMwBsdjH5yIfbES4/Bc7IfnYyKuwcPxVUzCHTgQv8Vk/BFTMaSb9F/HYXg4puFATMccHInFeDSWYgaW4xg8DzNxLlraWjEHL8VxuAyPxZWYi2vwOLwX87DoH9pWxbP/nXavrvFMf4fbrazP7W8iybP6Pt+3a92zy3P4nd6GtXpdx+7ZeaZ+t+7bd+j36X+xdydwUVV7AMdHgVzQAkXcSHFNXBFxSVFRcUdFRENDWUdBWQYYlEpfWGZaZm6ZqaWlvdTKKJdHuWRq6TMrX9nLzIoKX/o0JbMyxXw=
*/