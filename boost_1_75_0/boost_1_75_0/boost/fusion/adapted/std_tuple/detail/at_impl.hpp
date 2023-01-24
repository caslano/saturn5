/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09242011_1744)
#define BOOST_FUSION_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                typedef typename std::tuple_element<N::value, seq_type>::type element;

                typedef typename
                    mpl::if_<
                        is_const<Sequence>
                      , typename fusion::detail::cref_result<element>::type
                      , typename fusion::detail::ref_result<element>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
xmAafyXBLM7AYO48BJHF5S/QXpffOsOb/qJbyI13q9tbBUtmuh/ld5zoD/uZ98/QGofTEpYBRrTbMVcGw1HUpIlfRSdt+S0QGwF4uRzkrKVoIFPIJZ6zBMqcYAJloriV9yfczTqPgVCUJatQZrMss5nLBOBK75RPd1oIkPvlvf3WvUPy3iGTigSrZtMGk2qwgsx5WzDThW3ITIMPr5hhHNbUw/S7IfRx0KOMG/1JFvjfgF47vRuNG+XtVwNuJz5KS90O+RQUGpdPv6P5GsbX/x6j6994XW/8zr8P8vXqMXT9jn9vGUvlqsYqGGCMHQkLT2VOvvFbdU5+xO/4MjNWaIIY493i6XIXOwlBuMtVGvhu2G814sQlPG4J2FvHJUuk31CPW2JwAuTyO3IzTVeF9CtjNDr58PGi883baKKUak2UUpOnAzt6SR5OfpfhvDClk17SwUbGIF7UW/tdK40cw43yVSfQAfJWM7C539cwXw2/bFsrDTevsvVY+7db8EdGQm4GhLEJOSH8HPZnaotSgwHSLWx0uuNyU6Yll/iwfds5vwCic2BjIYA+bIxYAIeYDIecnvDNLPFm+1EU6BErMVCtN7Os5OAEgWrOCaKZSiBAXRRyZS1FsQFv78cNWBu+HDdemnvH075L3Tg8nBiva03gDbR3IY/gx0FSIecwhjk98gCdK9Ll5wdIkPbSz/Fj6ecG+vnQ2IZz9U2o
*/