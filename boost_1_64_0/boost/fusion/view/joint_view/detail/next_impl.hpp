/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
yduM41rSIMPDr5ZuTfvT4KvO3WE+fw5Uq4jXj57r0InRFh1UDjszWhkeh9d2MIGl4xnlXF6no0DJX1t4Ycrhj9ZF/3SKJdQMncvPTPqzfP2pO3sRLw8ow663mERR70GzMuL6T0ePXxchRCiFBydKCuVBlZfQZ142PsQi8KPoO81vlsT5O87yMIWbPWis3uw1SapB4J8bFBX6PhjhNqqkFgVMrEvDB7pem5Iboaigq4VD9W2D/Zf2wSzexMlb+cx6X+jDbt1pu216uAILS1hEuc9a56cFzvqYUKO926XzU/QxLCvIYf38EfIR+63QW7ETzrd55QjJ0WgYGjrl7SIG1lUqwc//LAuXyq5EmNKVvwg6YkC0xxKXqeKzY/RoKQX4HasToAU9Elw6UpMqZwTcvS8f2Ijo66UWMOrEpN2xEgQ5K97cY7GU/JVmlm0lZcvjkyu/y4jqjNOA5Z9BxAfgdp+LPycRq/TIANybOeoM9Jqpm0++CyZYOVEedfFrQjCLNkuDW5hKa1lv5qxGmggG39Im0FtG4WFI3QJv61ufU4F/A651Z+TTdpriqw==
*/