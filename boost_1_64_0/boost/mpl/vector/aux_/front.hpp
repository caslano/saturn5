
#ifndef BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<Vector,0>
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct front_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

/* front.hpp
cnB+PhvJnTCYcboV9A2UClddl/o/DzIhmN/ONTWiLQadQK3Cf8yqMhUcuUJ6tTXcH+OLqk7TnYPIxLZ0GBtK2XdwlaEHYTiUmQkmJVZpm2dqYidr63/C17IAxcSvNyqMpDpOz7WxrbPSPl0uR7OKXu/736BDL0IkIQd6x9/JWhKwfpQzwojGiCS4Pd090ld8taOibxI4VOZ87/2ts71e7nD7c42szOqe2HOJpWi5LUc1ir8Bq+L4qe9aC2i4hIvaJmKJ+DxwOPk698YCNgYqvCdn2aO/dYirVz4gsA5tE72mP1v4/z5n8SyedLukBHQr/Ckn06FCUAkKJ5JAod8k6hv3xjzJvPIG5hoJpAPW69o8KEOTfbtjz5JC7ZVUzHOmbjEyL8iV+1rUdAQpzeTNuE1lzlhXiX8wCSHFPcowGwsN9x6wBJv/q7OMCfJ9S7fjPkvGdZCrN0kVbjyI+C6c1DageheXW8pmIWvHxKB3QjP63J7thXJ9AmPztj8pbrDk+k3NTMj8Evf/z+qEL19ZcvDyGqbm4r57zwVnZ8iNIU6tYFkFLkRHHZ2XRA==
*/