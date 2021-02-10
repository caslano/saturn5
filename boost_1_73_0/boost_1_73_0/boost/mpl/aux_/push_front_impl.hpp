
#ifndef BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

struct has_push_front_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_front' implementation below

template< typename Tag >
struct push_front_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_front_impl';
        // if you've got an assert here, you are requesting a 'push_front' 
        // specialization that doesn't exist.
        BOOST_MPL_ASSERT_MSG(
              ( boost::is_same< T, has_push_front_arg >::value )
            , REQUESTED_PUSH_FRONT_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_front_impl
{
    template< typename Seq > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_front< Seq, has_push_front_arg > >
    {
#else
    {
        typedef aux::has_type< push_front< Seq, has_push_front_arg > > type;
        BOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_front< Seq, has_push_front_arg > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_front_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_front_impl)

}}

#endif // BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

/* push_front_impl.hpp
8OrxyDH01UmoVIon+6WjhIjrJI7miYrXu2Tw3GwTcBK65sbz01TXNE2xQnhuGQPAAMjkvZbJByyayBgHsclAPCQQCqlA233UhUThwDoqgU5WPKdWPy1csdCUOuApxyFRpDkZdb+jaHcGY7/v9m6u2SaLtTcTRWVb7WcjjZtu6/twdNMduC0IKVthsEXegBQCPt8sYb6J4oAcra7PhrOWhdB1fOscJ1KvtH+d7LkUGt8eFzhMrNfYfYbDmmWd6bS8Ye1Mt+5wMPItu1TR9TsYOmnGd4Vk4WrvGA4oHOtogNd2FUVwU55Fiy3oRgC6UJqvPU8hlTDnPIFTGQp1Spz73DYPJpRgum5IGeTJlFCVYf+yCqSDQWvwIu8C0cIgsuiR6uruhS9oTx+DzvTx2x/eZzNvhKzSw2fuMsZT9PTB+qDfy/8Wzv5X4Z7rXkPrWEN4LwRu9719Brnetl33DgVXf3duY+nODgk0Hg7K3Mk3MNOly5+lGQpE4v1q3aZX3s3I/Xp5MZBBfzhvpMtLUW1OH7rjwUVL3W499q0z6f0+XamZt7mypV29sgfTNLC/PP5IRjGrjMrMnm7vKtPtvB3es8rXlwzozt13m2MdWtA6/h/2F1BLAwQKAAAACAAtZ0pSv598OC4CAAC8AwAA
*/