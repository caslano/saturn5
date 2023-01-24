
#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/begin_end_fwd.hpp>
#   include <boost/mpl/vector/aux_/iterator.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
RR4LqSSFT52h6Oyj7U4qoLtWCqDtbZR+i31iszoeckoFkjX5V/hjbQkGJO7wgOApjRmii6X2T6m/98MuZeJW5X/FnVOq95uCI3YBfFjJPJhBSSepaOigOI5FN9jbQiaoRM4cGfIORHTSJk4sG9EUxEJYL4Ao4pyDxNpEXrOwI6Dsl4cEmkL3c2rWZWxY0iV/eIx6k38gi52z4QzrFA+h3WUIqWgo9FfBqfkMeR7/PAib87KY/27Llybv3wpZ09fKayNz9Ly8m4GOWQJVsSZe2XKQHcMgMytoeBLaTC7VhEc8XfUjbKmaIuzv2BtBG7zDg3ACdZ6VEh3630nj/iOCQkLnVvzKiXtJBiC72Ok3CJXdBMEH6eHCa/+xXttgV4ySXbKsfVqs/bu9/bBi4uBiiZjijS4YNQW4xRDP3T/ZaTDvfyiVyGK+5ZKfpjwlyqz7zPkWfkJ0WG4GTWBr1WjMCE0KDImFV9pSTJISV6FL4wwDhkPk5W4y83gi0pVhs2k90CnZBkueISBa8+8kuhuwOQIatkOfYIVTlBooHDgbqAjX3jaVmJtmLH7z5DTVe2UsTU3ZEDfMS1w2KPEJKJFx7VBCUVZXi1uKfUKZTEG1NvJP02xeoEiNI/sPV805dyF8oUB3CU1ATjvrn3DnHCZZnli941CNr9z6CguIsq0AQxCzJKGJhFY89DGAIq3IMDazlmfdjuNdxynQcjnT
*/