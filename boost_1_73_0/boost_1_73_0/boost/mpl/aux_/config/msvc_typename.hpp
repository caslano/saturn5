
#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

/* msvc_typename.hpp
6cHlI8sz2B3RxGdbOg4gbuvCOvsyv40Wy08Gm8UxVmR+Z70z2EprzylSibHu1AA+IlZ8VuSP+EYP/CvYdX9T4/4p+qTHBtfi9iJ0OpuDH7X89509gLbOJ2avWleYlSwb8hnG6KDrpanwHWeTbPDSRldshv54c+nbbipcd5hsLlM/wbEvYt8fp3biO94YXWd8IfxvBsyrcv4Z3NM8mD9V5Bnogc7jl4FusK5IT8UVWi8VZ53+kvwFUEsDBAoAAAAIAC1nSlJHVVemxQIAABcHAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA2MVVUBQABtkgkYOVV227aQBB9t8Q/TKgitVGNvb5BXIOEkrSgVgUBTZ6X9YKtGK+7uw6lX9+xzSWofWjap6oSgl175syZMxcizZVmVPGBEaX5SuDPI99thYzVwBgtFtP6Cz7cLZrDbbpGB6ClTozIOplGVuP9CuZcPnFpqjTmRiR5ke3wbUw1bfAs0iHg2QSGCCFk+p3qVOQw41/LVPIY1FaxTCjeMhqgEIYFZQlHP7fjdOH1LZXbNH8D09HU8jqk47SMh4cHs4LjuU4Z1Tw80JScZpt+u8qxPrbfQi5yxvttYvtuYHvE8/EZzdbIRCdoOh8NTccP2i3j
*/