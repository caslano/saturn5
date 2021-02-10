/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09262006_1920)
#define BOOST_FUSION_AT_IMPL_09262006_1920

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename
                    tuples::element<N::value, Sequence>::type 
                element;
    
                typedef typename 
                    mpl::if_<
                        is_const<Sequence>
                      , typename tuples::access_traits<element>::const_type
                      , typename tuples::access_traits<element>::non_const_type
                    >::type 
                type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return tuples::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
VEhfVFlQRS4zVVQFAAG2SCRgrVVrb6NGFP3Or7iiH5pEBCebrNK06aqs42zYeA0CvKklS2gMQ5gGzyBmyENN/3vvDNDUSVbJSotlDx7ua8495+Iubdj5YZfl6nDw6pWab4oXroNT2Ii/aKZedkjTB+g+6LjE9Q2pRvDo9ZBuw5u8HmDLeKV9rhN9n6ZvSLfUReqfkXZepvoWdzrP3n8s6vuGXZUKtsbbsH98/Avswru9/WMHTglntIJYUb6izZUDJ7nZ+aMkd3eupB8coApI5W4ETEomQYpC3ZKGAt5XLKNc0hyIhJzKrGEr/MM4qJJCwSoK4yBc+LNPDtyWLCv7OPeiBVmKtsqhJDcUGppRdtOFqUmjQBQYAePnTCqM2SomuIvpKSjarGUfRhdBKimA3BBWkRWmIwpKpWr562iUtU2FJxnlIpOjbIDCLdX6yakWWM2a3IOoFSgBraQOaHsH1iJnhV4RItys21XFZOk8loUJeT4SDUhaVX04dGVUdkegEPdoOdoSaqyeKb1IwaXOdluK9YYhwtoHKtqGYzqEBe1ygcA70PKcNsbeADFk6VE2kL/SssfacxAcqwLbi8GPbVgRyaQDl35yHswTuPSiyJslCwjOwJst+ngX/uwUucEwawP0rm6oxCoaYOu6
*/