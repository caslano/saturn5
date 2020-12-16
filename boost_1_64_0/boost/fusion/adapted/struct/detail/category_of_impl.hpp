/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<>
        struct category_of_impl<assoc_struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef assoc_struct_category type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
8L1Y640tT1uZp27sgzp7dJ6MD8w81XU+qtOX4bC/nKFSxPE7/Uzh+wzJBeXnBNv4vaSgpDg7K00lHXHYx/F2u9ocILViXo5jXubvsuSloFDe0H/1+5F6W4X3sgP5eRTP35X0s3wlX3G67Th0YueF6cTecjz1FbG+7md93f2hpTxmY6cjM6MoK4q1Lc5zXcsk5xBlEohQJqWHKJP54fM3vg+uxRTZ++hy2urbx2b6GVyGrNd+pPKKKYqqxVGt4fGdWOUR66lT5rnPp+Kt8sltPsM+65Wmpqyxr6+ppNrm1ZNP1AlczvwtE/bDXOxjlb/cnsVpgyeM7ZGWOHbiuYnjB6ckDqu9vdbU109UH0EDQExvqjkWYJ5MHe8147oEx7qzcz7bqI17muM+sad55NiUxBGJ4/+D6dV1aDfTe5Dp/YHjzmqmNzCrt9pUk3WLuti3itNrkDIkcawfKdX4jvFORjyfWccwPazjcj4LjdX7mc961eSpG/M0n3YMh3v0fstgMID+MP7TmjydmZY5pfb+yr42DaMM+U5bFmy7NptKJcVFlvqfqce8tjLvRFuDaz1aD/v9Hl3mVX810+cs85xa5kCplrlbwCz/M82xhq38Q3WjV3/tT1Z6neW4j+l8p0bHPlx2f1kkNdOZk10adTkiTTbbbUkudYLjL/WsZj7ZPiQXlSr8MLsInJPxd6U6D2yPFW11Qq5k/Z4H1w3/afKFyoMIujSM9KPOg8s+Fp9JKO62GplersGbc+mgw47nCJ0m46TmdplyZxz3srw6D/HgNNln0P6Le+baZEqtsp59mkOmuO7jOtppbnFB9jR3u3ssi7Nt+yfudjISLOGh/tjszrU+xWETgXYnln51Ku0EDB46VNYGhiVOGDp+ZHLKyHFjxUJCXWwGPNvNnIda4y4/JdxGwXPwW3mouFUxHV7ckewVDGB6GrULtz2RJHXhbzXpGTpu7PC0SYPHTEwMWaCIohysNj3mtwsv72tawqdLHHUt56taMq+OfDU5NdwWRTz+k+wWZ6AwIEvNdbElUtCC8VrkXJZ6JgHJJRJ7GSxzSc/IONQ5l/QoCxmHmRa+b+7P0kaGJR1x7cPr37X4T5VLOupa765qWXu9q0nHLe1d7Mr0wXv7uiYdIxLHYsA1Rp25qZt9kuMj1In2HcLfQeO+OLfiGqeqFXWy73K+S534yFYn7Omp6OBi6wZlMN81PXW3W3J8FO+jJi39Tgsvm54dIZdCaRmXnDh2woQxaRNSxo8cOyJtam5BVh3SYu7NWPd0WUcdaVl3WnjdyFWKSt3TInIpmnJpWTPH1X0pjoLhtJlDPo/p6CI38Cw+QtyHIztYFrZ60rpJ5Hqyo6P7uwlESFNd5Uc076amfPI6haclrTfqMtNCGzuJqSlIEfquwymfT1uFl8/lxznLx5yj7mGgPZimLnDtUJ7VTJNarcXQKZp17ZAdPK610I4fv0+xxbu5s2nv6xTa+5qBehr/d8abG5DVvam5pbZ9Jvd4OX6bpm0bmTad1XtQ2x60TR55bp/gso7Z4BDrB0b4moNtXFtKm32pzN8EuHyZ+3+j8qd3sf5Ne1idwveqHHseaeOzi0vygo75xG6muZuUCWVrK4S/lGnGDc46nXMy7SzZ69wS2gL8gPHskLhQ+apC8eDlFwdgz7A46nF/wLTD79gDmsn6EWqXaizv/VaP5Zs0M9T3yeZ3W1orqehqK/VVvgQWyvxb+0e/kpuVJks/Uazh2NcZA451RrMuBqJYZ7LPY7IKg1yHTDDXIblf4zwr5Gu6FOW/Gvl6Hs9z99v2qOkXPguyVJ3pYnkmMbPO6DL83jEfYpml0w5dP6+u+2eBM2Vv6gc=
*/