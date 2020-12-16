/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef std_array_iterator<Sequence, 0> type;
           
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
2v8LKunvXq909/p0xnZ4qH/BH5i1y3L2a/p3IC9/RFYuyclvyUipgB2inBPj6q/6gSfU7rL1ynz8zPXq8mxdWmPHi6rsZd8kIkOan1zPMF+sFzLzy1VyYUZerJHf69/u5evZ2TLOx2bxKF+X5+T5GfkjFe6P0LfzN03IUEF+Kr9LvZ6XLVtdl2fLfW5tPUcLA2olpFra9vxtJ7pGpciOjGPPS9rkKiJbMflKyFg2On1P5sF3in6T9j0nY/f079m19ksZTchVRrZy8nX3HedHObsgX1pb3sfmxyfyxSmrdlpyxvro2/Uv9FzsUmvf5ZOzgJy15Tsqz6i53+M1LqnDX8trT7/jcrB70a7scjw6uwrJT1vv/+jJ+vmmGTnS0/XO+WRdz65O9zTOJ6D+OX/V850MPe083/bRk3S9Xfbi99U5RX/4nXX1IwfJqv+xKZ7eB9Fv3nUe7YdItj27lxyWudYs787fIHE1u+3zvZ+M/3OB9ydn92mdvTy7z6/ay9bISxX197gVE3xsHB6cA5BH/sF8Yl6XB9k113Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13Ed13EdjJ8BUEsDBBQAAAAIAEKxvErIDHOFVFsYAADQcAAWAAAAYmluNjQvbGliY3J5cHRvTURkLnBkYuxddZzzRBAN7u7uDh93hzul7UHhrne0xQ9Cr80dgRpNi7u7u7u7u7u7u7u7z87MSqT4H0j2R/ku772VmZVskt2k3y016159pDVncvHkIovM2Z/vnXOZMV1dk008cypvQZjSssaGfyabwLIK81sYJpnAikMc4hCHOMQhDnGIQxziEIc4xCEO/6Jwyw8/xyEOcYhDHOIQhzjEIQ5xiEMc4hCH/3hYdhzrvx0++TkOcYhDHOIQhzjEIQ5xiEMc4hCH/32Y5L7usZbFdf74wyDwcfHfcdRx8N/JrXGma8Pf88DvE8v6dGFrnKknm24cTqNZtrdwtrU+/+xTgbVQ06y3a2VPYD3WeNONDdsKxgKtDF9YRccTkWyvZY1ZJbGOPlx1VeuzTye2xppyTtCNhX+PPeU4EHdSOBL4OAY+HuNTW2NNLfBx4XjO8S1rfPh3cmvCKcmicawJ4FjoJ2S9KJNl7TK2ZYbfUaaJp9R5T2KUqcVlmh3KMb4qB/lrUv57Ml+Zxrcmh+O5QT9BB30rFGcCa0o4Fvm1OT9RL1NPKeKJRCw8HgePUeDjF4R6g7hTjwV/N8aX6ZJwevbPDGyT1I0T0M3EuplZdxW3gxbyrartOSWzHYwrsKpbM7EJBbZZvd20NDYp6srFbQ1sSsTqvrjTCmxbp2jGnVFgW/vjzoo6PzanwFyvDLX76dxQ/xNBm5zVaJPzAo/13qqq+m4YbW12YfO4Y6H9c7D9k4OfxhZpizrjuiJfjG3Nxb6am7WYRsC/83IcqA/MaT6OM78RZzwj3wUD+S40JfwC+S7MaSzCWtlXp6E62sqso6lFfQisBiDYOYb76mLSL1QPbtXxGiAQ3pEH6KMxkf3IaxVLW8heJA9Qz3br/sl2d3GZu037WDd+wL4lWLska3sjy2DbpWbLrtRLxYpjN+pureU0PSxQJLPqqpjm0pzmzOwzKp89WCmWnM3qlbLThLEP8hsLCrKs9BH60Hbrw+0RzID+RHt7Iv1pSx8uvSRF0McQa+XftqdcbBUxZghlO1b4Hb6ptistd3jbli+5MIF2iDRXCrSnFdEmyNutjdS5n608pfBFdVhivWz/Kqb9f6JuguP7pIHxPcFtYmpjTN7S6LupwHkiPSX92pY/nV5OZ3Wj/00cOsfQuJyR7ZLjrgk=
*/