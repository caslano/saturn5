/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_06052005_0900)
#define FUSION_NEXT_IMPL_06052005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<filter_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::pred_type pred_type;
                typedef typename Iterator::category category;

                typedef typename
                    mpl::eval_if<
                        result_of::equal_to<first_type, last_type>
                      , mpl::identity<last_type>
                      , result_of::next<first_type>
                    >::type
                next_type;

                typedef filter_iterator<category, next_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
jLUwcDZfe8gBhLP52nmE83nZbeYQzuZlX0Q4n5e94XoIH45wrlXPB24ADHM2PYe/bOrQopcUUeRkjrAj6RW4t45FNOzRiM/W0PLt+fSqn5DXao897fkPmnvaniiixLG96H/f7+E6AlWBnqpt3s3y2J7IbMtO5av/EPx7XqByflCfjvdmX6zHQzN+xxJJHEd2YZVG/A+DoQNqBr92/vkcdB7yHL0nycpYCD8Lo8C1fbFXgt1/sfA0DXmjXnN+yCx/JDzby3IrKK8mbVQMgnZV6/8LGbMep/X4Q9y2JSri0spKXyAjfSjliNujTLRD0eUNG+X10yQM8+wq4m0cIFxr/fBzCZRXn92cNfPlFcK2aYaY++41t8O2agL8GkKKlcZJx/9agRXMLrL3jH++6ALnUZfNMrmFKB0rz8si/g+V6dqy2U5liGHoORDAPGhH6+WHTb3MqL+kvu/lobi6mmzbNLWVDske13MZlqYlysRJM8uzrsLOq2Xf9QK9n8biLETuhrHjxqH4j3bvjvtaPa6b6TueKJLMCf3YEVfZffZo82tu2s/p+aeZH9eRdWwXqeteY350v/pnRpNryrf+3s99pGETUYaRF4VVOz5bZQNxjBBH9+p7FUrEde3fWhjpKkTfn/oI14sktaMgjFKBHI/QyViXZtOIf15Fdf84+5HGvCAJCse3rzof/1zqnbu/Rd9DZeknoggdz/Kiq07+ajqvm19T3ha29Lhu5s1OhG9FbuomjpjQCof/+cq4u06v81GeXlk6SVkE0aT0jvwL6ek5wqGP8jlCESdh4vnZNX+3mtx/VPm8LJgj6D3bsx8w14s09R+oPR3soffU+oyWSer8Ua1n6Jd61h524ulUk6fWMLS7vUvH9XQqY7x9cZFzaUuiEauxfnSniYv1o9y5kqudjvFeDXAZw/gN3lkWPt8xfXiNMZVHExP7OEaCSOsHwFQtybUe3rnpTdhX/qgKJ6Yqp/EW+PV1+GqfhLavQ5nqvacbaJyf+d3/hjpcbm1WQtjbBsbP5AY3Qjhbh67dGOGoH+x93URjqB9grzvIsXkjrXM31Rg//7vDzXQ4P//74s11uIoKeywHP8DOnFMrKILUj7GX1FtZ6Q9G9fvhem/c2EdSC/6KjPXwoQ8094EKz4qD5FoXxHp/Zqq5P7PkHX8c9mcUjv0ZhXnHlexTbqf3bpYKJ+nK7ZZuvXeL/Zvz7zf7Y1XaQb33+vvbVdKW43jl8linfiDrwEBq1QEupjjevLN1HjgBdZodtk+j8aFG0Y6vURj0H2necEaG91YGo8l7MOeB8z2Y2f0IZ3swZxHO92D+gnC+B3PuAMKZ7p+YQzjfg1HvfQAb675h+zqj9HV03aBfXW7BG2Xv5/olvY0FRXLN+4zy7dGZ/a208K7zzeQ5PsfU4fx9CRvJ/CuMHoBjcHebkpUb7F3mX5x+urJNabhWVVq/zwQ7/imNS12s2uK+WpZjFEFzL46/j8u59cUnIy+/a3NUNHgjb6aJ68HT2Ktsc+hnCDycbeJKX4B/keH41iEP8/taeOv78V7OoUrFd4/sLxg2/Ht1dqnFbdfZkw9wTrPOftXC23U2mOOcZp39uYE36+zs9TjerLO567dw1BnePFacps6Ozy+uAG/rtMTxdsxv6GwO3026xVadb8Fv4JderXE5EFUPVu8OlC80fEcu/kH3rY3t7WcQWl0WW9f9fJH180Tkru25buxcaz+/k+rne6VHuHH/8Kmy/riqGP4HgctTqvr2m+GvcRq4dLK61T8z0gdtmNe8ARwVNeJ+zYwZ3qVCSS8ZxvjB8WdrAmwJZzW+SgVbWeuZ/sb3aewUDTqqVZGfK8D4m+sv3W8=
*/