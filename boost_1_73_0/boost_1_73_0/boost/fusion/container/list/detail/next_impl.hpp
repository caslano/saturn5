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
eSAwAX8abRwvWq0DnlalQLnXfwSGqsMIGq7D09iTvHq4n3ao5mDSPnO9G+rfLm+/apBeVMITwo9qyxM9tgSQmmGsTYcflG3IsMQPE33wsXTXCcHX2XAicdlzvSXvMDYBa4uymE5ccCgaOaJZnYiN8aHDB2NE1cg1AymTQGFvMIoA9qEW31SWZ2+Oyn1aeV7nyoMAZAgYCRkqS6KPXM7BXOTJALsToMJZynrj/qQNjSm1sP6QYGdw9eVNW4ONW/asdJ4FC9y5gDKYwKUydVQaVAhXpXlPzwCZLqpIl1mzGy92UqT62K4FU2yGvNp3o0uTzs2kQAlEysLj/ziBhMLSwcdRmEbPsjnAl+0wVkkoC6xNNXNeZJLfW2229yd/r5271VZJ5W3x8PtiUNlmZtr93KHpLyqIJFCB+SD0qgBnDZfEzXg8HP3NfHqLrFNYYkdyagBOpqKUzclKZXuJ1Yyhd7Uja8MXRCAO8m6C36I8VFBt+UnX+1cm4lLkrcnEoEAzCqafRhELQGXbiKKw8xRcMIgu0KZXeCRINliYP+bQKeHlaP9R7NSRv98q8fy4Bj05YCbmAJNyEFMW6aOSLciBBYIicze50Uwy0lLyxidd1QILJ3exSCui7zb1N1oLn1sFL6/IyNa+jkBICZh0
*/