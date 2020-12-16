
#ifndef BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED

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

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; requires 'Seq' to provide corresponding overloads 
// of BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY

template< typename Seq, typename Key > struct x_order_impl
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
{
    BOOST_STATIC_CONSTANT(long, value = 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(
              Seq
            , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*, 0)
            ) )
        );

    typedef long_<value> type;

#else // ISO98 C++
    : long_< 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(
              Seq
            , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*, 0)
            ) )
        >
{
#endif
};

template< typename Tag >
struct order_impl
{
    template< typename Seq, typename Key > struct apply
        : if_<
              typename has_key_impl<Tag>::template apply<Seq,Key>
            , x_order_impl<Seq,Key>
            , void_
            >::type
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,order_impl)

}}

#endif // BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED

/* order_impl.hpp
Qlk10bFMOYLx4wTDlCppSZGhG5oUJ9P7e0li4mWcszPTSGjDIThMI1Sio7Ih8GhlccPg1bazUb+RJEzak2Gq2Hq6dpTpm9ZbqdAY1TteEadSamQRkHbE8Z5aX25fRYIsBseEUh+JRsIaPz7yKJlaY2ATnq7rOLo4ReS0oiReE63PADLka+AY0u4ITnHXRUi4aUUoY+NUMrXaqGcM8bx1clYktJ0UfgpULY9SGCQIy0xqBl2jWhE941qBJymphODrS8htF+PmJnUMDe3h79Uz1DeEKb/hXFUtDkFhS+L3wtiMxDzSlyMmJkjVSa5Sa0LJMCfrgSxCJo/TBMjVGsOYIRx1J5WStBdpCTIITNcHFUeXCYeSonPS6yEbGo/WMh6DKDpovEqmG/8m8fTzzNAexQXQJPXUh7E+xsVhpeG0V0i0RCWTMiNWrlbHo8iUGg0iiQmMjw1HSKfrT2QdFdIQrtCwrnrj50U6KVWxEg2Xx56rCKNZSA8zqqSPGYF2fCSiGaVoTw6fIrIEF/QdSUoXduWGSc7M+GVS8I5WyiNkan068h/VCLIf7yZIkwwkmcp0E5Dpup8sWKwway5L4tTxMZKSlwtKjZVUO1uYqciMLWY+q/WjgauGec/RZMrKWsOU2jUzoZij7QNTvtH6mqCMICu3URTSb6oY/TjkqJGmNoxTozqpdeumJM6oEVijgOggdULVhjow61kIs/Iwe2QJa3YEt0tImNkRjVc90/WcvQ7/aJ1Xod8w936eJsYTa+8NxS/bqH+w96ILMcAYfym+X1IXQyxRK1yaRZT2OyltHOmf+H0dfRzUqdS/lcPESeDEiYiWRQwRa3tEv05IpFJnMQYCJ2zYeMVDSAuWLIvTmRGQcnRcTBdXRsaKj1yNZNqBR3goP8PDg0Gh8ljOOqzfpXS6RvumOEIl065hP5DLFXINfnmJWQuggzTjkvTNw+HFIqIkSqa1F5gykF2Z5e+EyRDDCvsjE4NcRjqHMgqL1TKNC9PKpjJDK/9QjsisOvhw5744Uq6QiiM0idSPdQyNYaqjay2pEumgbuwyELk4gb2X68apUirjbJNEXzcn9Xom89uoEKa2mL7WP5TLFH8sZ1ra2C40HTKkjIzcdMgQucH6Ir1NFNgysjag7VXsdiPtqNOJkmkw95hFWBzB3jGJPtExHpOEJ9MxxRqy1LJlTMGM+CrDpmGcFaOj3dIMvFh1FJZ+7WggE5L6kQ2la0BnQ3o6OWeQmNr/hn79gdyoX5Gukbz4moOl9MN0iB6poiQmqlR6mB5RYrm0VLoq2RD1H+vpksNsjI2j4H5UH3LtpG+Vn+oZVxx5l6hHCimX/lRPV74/0oMhT0YtUfyD8mlY1fhDvVL2n4bVf+rS6Gm3E1LrP8g/bhj0Se4/ThNrhzNZO/5Azl6p/0iPrNic8qilnKWC8MhqJZfo9zfD6kUqw+L9wDgmeUOODtBIsO9LDTyoG+LDb7x46WWMHatfffRR4UxsXSIrgW+6P6iJTM7ItGbAj+OyFj92HTDhyOJi4Gmw+rDOOOIVbAuB8DiFwVJGa8tCy1QqpcrIHqYlMUhPmkQXJ6HP3VgnWqKmFUqa9EpJcm1+TPrM/U50cXPjIkiuJquxTsVIJ06ikuBurZ9pk3alizuR7C2MlPBj5Hg9JGOHyw3jhI6Vq3FpERFNseWoj4aOVMYrpBSXX7zLMFFMZSQic3RAykP9SE+3P+nVfqRHOqjktEpuW8wfFoeEyc9v4tKNgtMtRgYVQmksFRoYmLT2xJDWT06DvHgcFMt1RqDW8KElRvePMfpqXXpIqES+wQCWs69F5YoEdLCUNly7FMenY2SKKE20kQ6RyAwXP8w=
*/