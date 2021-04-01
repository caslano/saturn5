/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07172005_0836)
#define FUSION_NEXT_IMPL_07172005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::cdr_type cdr_type;

                typedef cons_iterator<
                    typename mpl::eval_if<
                        is_const<cons_type>
                      , add_const<cdr_type>
                      , mpl::identity<cdr_type>
                    >::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.cons.cdr);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
7ZA2EM2bT0bTG8bZvtBH9JC6QwNicvcZOPzOi+SuQ3jLU0fbCUyHaJmvcY7Vp9eT8FrUk9JhYjKNDx8DormAqOSdEewiYOvY8Ce5oi4eCtyM23LeuLvDcs4AWzXFzeM8VRfBSPaPtxx6hzCTV5WKeRMLaZUjx2YA9l/lZZeenJl5bmz42GwHJ528UWaG2ArIuA/us14/eZ0Ws369whqfSfNszpKJYwjzae+dTb9zkWeqDjJw+ESCsoD10UXzeYQ52+ZjSDX9/vJUYYmfoOghk7prWZKQmMVu6kPeftrsC8Iz86cezx91thp+kxKmB6CxB6IctnoxAPBrzPIjeoSiT1STMFgZxyw4NhHPjahVMYZ9EM4BRxKb9M7FM8O344Buftc46/ARQgl8GqFtNs1ytERouO+KxkwI5Q/6cnH6k2AV+p9UrtE7NK/ik6haO5z0s9wL/PLTr4f/uBdSB2yfmf5a5z1b8C5RQUWZspbsS/WWC2lPxl8T2w1ga7YgYjLxSz3N1iUFsKPEiew6YUTT5AzPtOgLMcQGV4cAhTm8L+H469PddYYHZC6opQ==
*/