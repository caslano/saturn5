/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_09172005_1115)
#define FUSION_POP_FRONT_09172005_1115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct pop_front
        {
            typedef
                iterator_range<
                    typename next<
                        typename begin<Sequence>::type
                    >::type
                  , typename end<Sequence>::type
                >
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename result_of::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }
}}

#endif


/* pop_front.hpp
01zM/pM0mdxUSqdTUwKNw1MwPnlO6ZDYYfPCfIMr/Ms+D9zalENsNExR5K8pb1ui2MlEusWWGNuqxP7EMu/NBo+EI6S1hLzbsZlX48IDq+ANVIb0rYcLfFUX0z/+ZYAz1MdRFn+yv6eP3UjJOsH3cqU84DkoSDXZC6JOHKKZ/2dvMJ7c/F1ENjJnlBe4SxK6tLvNQwghTKclsehOZsiOcRV9pTk6gNw6HQYifMVZkIzssvdlk5CBQT6FvY3cr0SgJcKrpOeRT9nfJB+fgfKh6nVFrLbndvfSGm6zSsZzOiTC3wkWs+EH1pAyENd62k3T69iRfvg9f2v7/hMLUMVaFbo4mjQu2Zu2UiNgVwrVqq0/y0QvlPeROVfu3mjojaZbhXeZ0iWrEB+EhvVMKGOuT5xGqyIbC0+MhZwWl4Q/BdHY7W5clUF9QobbW1SYP0ecE9XO8E9+AWpqwz7hQ48fZxgJlWbhVxVnGBVwW1KsB+ATDOY9j9THLZZGbhp+v+lFGE1K7bmzkQBl3UwOR8r1uEaclwFlGbyl5ilkTRrm3ZGJx/8PT7joZtQnWA==
*/