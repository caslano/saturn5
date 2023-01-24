/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_KEY_OF_HPP
#define BOOST_FUSION_ITERATOR_KEY_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct key_of_impl;

        template <>
        struct key_of_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template key_of<It>
            {};
        };
    }

    namespace result_of
    {
        template <typename It>
        struct key_of
          : extension::key_of_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }
}}

#endif

/* key_of.hpp
kTvB5PDq/akxk0PZX9PRMOTaioYhV493jMC165LYUHNZ/MhR3Sqo2a4VD8c9dkHgh99QVnhlYIRMqRU6VXBE2Cqi0HNMmfmO1nJc9MEJ86sYLVCbSWj5GwkG7RzggSILiyskqaCkQe6wwIUxcICqzIIqscLxp6DC4HxM3WStJUU8yGLrWgkUqTguDecO3O6K/l/f8p8/p5uiz3bZt6OiiER9w7f2akV77T5heWuTpu1DMh3l86fpat6ShE/vjJ+mCo/jddlM/Qp6wdtYv5sBzhVy7yVz10t/JvJvw5p77DOGYK0wsZXrJ3Ou/If72DBYodl+zg/GPTPTQvA+JWHh2BYXTUMUYP9MVtgppPT7CdSBztd1PXaR5zWetTDzsAAz0xrxtLrOA1dAgiyRHqVIyzCFhF/ET7lTbI8+Gq+T9PBfgnqMFrz6QnoXAZePo7PJVmqDJVghyuN5ZhjpXz3WNpeyr/NLnW3GFJA9qHo9QM/8cRjzb/RiLiscErgWB1S9RDB/VxBTXZOD4pDH5HrDzAPX1g038IU4+69F5rTFKA31zehcupFK/wQLtpw2GQ696onTQpooVv9MRST+8Qz9SM4/jmtfBwOHM+ofhnJEWoX4vVH8Xix+V4rfpeL34qFxcHV8af5QTHm1K2rh4KaNwuw/8jTL5s0mwzVIZ39CCCkpQp1vh4x/2+Gv+g19PY1fVfr6KfzdjHC3apMc
*/