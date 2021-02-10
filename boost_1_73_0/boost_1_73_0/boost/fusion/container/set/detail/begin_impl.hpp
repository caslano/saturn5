/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
B867iy4WygeO4CKV/AgWbEfroJ/fPYI4fB9BHL8PE8/vHkH824e3Px9B/Vd4vIN8cZtAn6Z07cpGVbKvSVvuX4NSKT8FK0g6y+ZTY0qq/yZxGHaHw1NrvLVhRiUJUbAIcKAVZBOmXjeknE0tx/iVVjxTj9aKZ/1j+bTo9RvTL0PamNmaOfTEfb2mWeNTPaVfDxt0tjeopKSfChERqDkDW9dpgXkOnPFsIynArubOnPaeFPcIE4pmwtpNF9VkfZUiFH69OlyBcvSxPnApDEuR/bFuDWVqgO7/TqZU9rI8Ju/m0M0jciJia0W8jljUw/sRARATHdx+2aUYAIkZjzU9ot6yB+0cWqE8SMbbb0KZ9PI+y1qD8TqJa9e9I2fJMrjnittOeRvXmtr+RxrB4D6IMrB5m6RnWQNgDdMFwzfrl3oJHfG6Ma9zamqkXDLH6p8NCvDQbAAQj2fxOvC9TOXG0V56jHkeQLViepprTYyBd0CDG7hhCkw+sxxFbWB+jEOeHVKBPQLerTXW3L1NY/seDujkVqEdJDcFR9UXOoYmLyhQhoYUn7XHZeR4DLJkUNP+8XeHoKNkSJV490OODVp6+xWiByx3+uukU7SuPdAcfQBjRcRcJ0HP3ATIyW5prA9wseljcDijMleESz14
*/