/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_0115)
#define FUSION_BEGIN_IMPL_07162005_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::concat_type concat_type;
                typedef typename Sequence::category category;
                typedef result_of::equal_to<first_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, first_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::false_)
                {
                    return type(s.first(), s.concat());
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, equal_to());
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
dzHthxhEYzB18i1/VxbX0s460Aw6WSgeI5+DKRvVK0YzbOXpMZ3cW5v7VmdqwDxMK4CtAXA2GpgnGuJ0EDBnWshF/TN6Dr+Tg+7T3Ka+sxAdz9L0zueCrar7l+flzZkV9K3U2IDPOtqfKqcX5DOLyS0kzsKg4qVYPizcSs6CJeY+omcjn82LSSB8bzosdqCbuWxAc5LA3hmFKev9fVXEF7Msaab1mEfKRePA8RVlvBFlnVYIEnlEypH7t38WVEV4+z+rqWrPsiyHLD+5LA0GGnwrS55Q3eT7lpPG3ENZZQxzT3aljXRFy5Foxm5AM7vlEC6K8mTDyUrwp7weq+RM963RaLBdCi6h2FVWO63Awkd/apJUdMAOZiWhr+ciKlrqwZwg4CBQbOXRSUDYjObO0hGoz+r9rpJwzHZqvq2KuYey7ndzT3b3u1nHhPe7C9Asfbp9zPgrzIvpTwjr/CCyloplizC/sZvdQG1DaL+9OqdIG6ONOlMNzsARgXAnFtzjmSHDclUkbbujEX2n7bcz82Ria3NODNWuUGcOsZovL2PC9iy/Bn7PNG+q2Yh1mN5G1ZOoX1fVYHpdNeSs8n2Y8a+lF/rnCzZbYaqMhVZ4pMIR/fpbr7V5ffSroV4BFdT9mUOM/+nw9I0fb3bf3uzG7dpt83o8K1tqa/18qgGLQqOPvkZ7CqsLQx+lPidpXHtqzclbmNITLxVhEIZZ
*/