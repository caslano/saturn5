/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
vWX89I7brqP1K96ZYKpDjCCOESuTkTn93EHOM0QyAGzRb1wKdWfMYLCk2VZN5Ta/ZeLM8aFBz/HzhEJxecJzKi3lDEzHxxyqR1bfuoXfkbD8JkxNQPh5ogR39rv0Kl6WYVRxZJi4SjCnaLjKSDEojPfeDMTtMN/OS2Wg5g+GUVmsiVF4fA3Co0F822rU8JMp5hqCCbJoWf0ognOUR3AckuIboWnlfk7sDA4SAmg6Kc4XtJuVH8LRAUOvoR9dFmbQZSEMI9MA7HKXGIB/zxG/fp9DQ/Egf/44B4fkUi64583F12089lOK/YS/zqDYd+f4r6usbN+QqMuyf9cbsgxtVWEE+6//Jne0NnEsuj/P4h4P1+DXwGorF5KPm9yZNcr2vqY1Si6dYKM84o1xrFA0wWH918+FZv1Yfj6hX38+W2dcf9IMpdkWTjKdUjyYbTqlWEfyp8tBlD83HET501IlTilOjddPKVIm6acU1svolMIQO/nXmsUOnukVpD5PZ3rRwtYXbMcka9T1001wejOm63B6PtuKu3ryct+9P153VJrhbwfWYrSmZvvhmgTL4lMHLdGLiq5jWWvTTFmHm7N+Yo7I+pqOs24zZ+25BiFj8prDlRP6YLjnGrEBTA5g8Rr9erIt0WpGlOF7wP1ioh18p+jJfneidVavO407SzG38N7cvl3vzWLazmq293L4hAK9+fE46s086M166s1U
*/