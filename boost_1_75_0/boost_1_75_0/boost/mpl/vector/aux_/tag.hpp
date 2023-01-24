
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

/* tag.hpp
w2AlQDH+bxnzh5cvU/15upymcJlToBLcBXvkcazkL3eQeC7HmoYD7BVqkUooEqci97IiFQIt5RA+oX6Bt3P8BtUf68+3TmNWDLa1iLo2rVIJuuC7C5AcyeboJsbALKFmXgvxWH0MZxCKdoC++yFqYbpMVMpFfg3ya5mhv0Bw8h/yiC5cRsq7MqIqHkbbp1z9a2i7A/kWnZsq32hvpqxy64ka9PSUorvUb/M2+VlA8WQrirgevZljtHKcJuj21XTor9SXuIl3v/+ivaDD9eylHe11YHuIPp2j7yHygmGpRgL4pfUUdeeXnqc4ZObuLUfHWDkCVFzDE7no7t5yhB/TzGCYHwbZYt8xQUChHjRdoAcDOr20bocdfjPH2GGq/9OI2uGgFuSV1GHaEpL+RWa7LSHQYdcSgx/bkAMF+vvtVfqas6G/H2J/N/L+4hpf6jYqX6T9NiogKupvAWVB0LtjsnK/2ThtW03viCp7C9vtcGnSFtnO/1xfZDN0Z/H1hrxoxvWOfL0zLq/UZgjh0P3y9be298vjQHml7QDqKRkc8x6N1K65tTukFv1H6koC7me7jgHaAT+snN01P7RWd84PM4R2/LCtujtAfv5Zh/wwgIOZBKdhD9AhthyxfZYW1qdGzZZhXjZFOkYb4GKTNiqOKdVk1x+xrWHhtnznA1yImmJnW1/G9AbPs2AfvgkFgyn6ApPXlwLVraXQgmOl
*/