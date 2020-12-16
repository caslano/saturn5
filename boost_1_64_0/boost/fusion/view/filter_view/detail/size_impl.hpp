/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_09232005_1058)
#define FUSION_SIZE_IMPL_09232005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
hksPrsY7GwdqjA1F43o4OxHnvtqvMI7SHcR/Ys7EoFqQ/RnD+Rsg7vVMTNV+l/41fq+8jdfuGAx/79c3ODgpM+amJj40fCjeQIfLsX2LfdPDG46xUaPt/wKsmod05UlVx8jPjRhet6CRH+BqCET46MYIJ1U03rxHOPkvONnf0YeYeDvnJhxXo8iov9Uxbe/AoSvY5tzlIMJHO3U5kU9g6mo2wp9203G46ev8/jfT4SqDyP8Nb67DhxP17zUMn6x/B28BDtM/Jc+wtv7d/ZYmzv1+v5dhSjeBHbqViak2QZ7fxrDJennvW4PD9BJ+j4GTv4Q6Y8wf+200visNQk6Z7XkO2LPY+wBzt9Xh1acE9usqnMZSPbSb68jbaYx/G+Cb8J3MF02Y5kmU2rYYzxIbvglNfi6yPHHDMvSENAbRblIqiXEaX+JpxGkaWqlnCSpJPafmaVwy+YUos7KMw7Aw+G1ffJd5vvwwT93c8kmmWmcYfgM78G9jytiOcPzQsQPPI6HGZ4f7c5w7x3zx5KFtUx0oKRz3m/zbmPxF13NiywtqPiI36uvejF9YeVpYoS30INfyr7do8qWDTC8K48D2tUSXTtxJ/wfN8pdMzhFFHKd+WSaQw9SYt8+aKZcLrwilI9wCYoNtOEm7uy7TmXNcz+KwCP28ktlYH9KIxuvslZyfJQ4pmhNIfj1j4Hl6k8kvRJxHluN6sWC7BvW+lLbv+uA5Zh9qO5bvZqrW2j45L/Ay+1kc22GaCdPKUpcZfg8b7ZIkdukVWgZW1K32v3yO+2RL0yD2Q4FNHW0vqvlXeF05SZB7cZaPBeZ53Xbexfhp4BapHTgCuz+NPn/Q5Mtrgl5mRW5g8Oex76x9QB0yZWxXeKnlB2WshORNlmFfaaW0HmmVf9GUXQwcyymzMBP6o6T5Q80PGd8PU9/Oo0Loj1WLf4KXvwiswLfCqtsbhoToJ2uaDz+PgZUkrinQ3SJFqxMSut7OmnKFkMcIVunGEKO+daoWgr3w67hMkVBR3LgwZdZHtQzGcFPmYV7sObkfBAIfiqZN8nnenlEQWFkRu6K6lsDGJAtjOEujcNK8pLFCwJCk6SP3UkPHqOBB4BdKwPyuwNdnq44jK3PyUNSmcmTIYzamgG87JmcLP40CKy5iQ86sBOTv4LuZPVOYZHZiB8oS2CzPSPMPMb7vuZbllqWAAbLmw9b43bw8RZmmZUZaSQbb/XZFI18hS8eJIieOk1DgsoC2sdJj2AmT/9DAs9LcpWom4/D2GLZmcnOR2550WxiJ6pvKvABavh63WTlyERQeVXFeffCV/i7Ivxke4XqnpBc73YdsraMsnkTQB9CzYy8XvU3y3bW7vUviNCCQPGUBRmXcd+mXzDhKEVJ1lnFqVX4eyaq/9puo66ivy/1jUy4TSRkWvmt74uTO9jOkzGB90OojvzFlCpH5ieOEtiOqDzyvLF/roinjOKIM7Jy+EYWgj6Is28nr5GJirwoTHYyd7+HfZZouFalTFqI2LFaxcJ+N274eO5lsITzPzuw0KLnsaIc84lEfXK0y0x9iUIXNNYvHFkGc0lQvsmU8I+UzUsZGi59GP36dKVeSuuR5bjshfCgyS23jDsh7Tbmjce4XoZ1nYp2aZ3fYSOM8TyOOsjhPU1fU84iFZx2Vrik3rmv5X2dlikTpOE5O/4l6QrFAU/3dna3+qmqYNSol1+HfMPlEuFmRhL7snb2NU/RkKQnupcMWfCO+l38XyyJz0tJ1hfqALExSrxX4RjRlHU+EiVfaUUQ+IHE2oJqTpU9/GZAL1FOiAz0tWTy28IssdMLUUxHBOnNSJOv9VYoHvoRZWSyRxklR0FdHxaMmgXQ=
*/