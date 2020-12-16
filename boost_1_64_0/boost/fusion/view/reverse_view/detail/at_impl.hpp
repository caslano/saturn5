/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
ZeZjm2v0cxpbNCuznFuLrqH6bhlhErM0xuhmVCbaE2a7B4/7SmXeNsJMZscbvbHRGN0xwhWtNM/bZBpb630jzABpBz9/DgoLoP0YJi3SVAeEwR94P62RVtcxbxyN31Mj1AVpEztFxNJcQjvBbNjeu/3JnhlhH7PPQ/ItFZb43Ai9mGVLjqd1G0QrobQlHG3V/TyzqMwXyrVDsVlvzdloD0HLx8w6qfJmKhNtHbMeHQ+/pb7+KzTuvq/+SGHw0giJzNzHNQto70Gryqx2ywEa6mu0ZGZtGiW0prhXuI6Y0d9TonnQujDTD8tCe6stGBrnbPlPWZq7aFWYNd+200NlohVmdj185BJqJ1okMzq/oAVT2LOkk98Jg9e4hzCjz/TRrGh5tdKWby2zn/r6LT5L4P3iynaP5tk7PCsy+2qrk+ubrQ/zof2sWIRmfVirWZeqC3P8jc8cmU2eN3yQMNd7I2wOkzax/IjVwqz/4n0Os6qrTgSFub8qz0MU29isXlthdjDBbmadFvQrLMymMYGeGe3zaI4URt8TQHOmMPk9AWxLCqPvM6B50aKYrSy0eZIwP1o/Zns2RE6m+rQmGMusQPy2I9QvYaH2ocKK2lQmGq9v6cs7r4QF0dowqzW4zCKqL9wEJmZHL5+JpvzQejNbMunsT9SWiND61nYML0jjgMb7hb4fgpaIlsgsa+T4B8ICoWXKuYsGaUwwRSOtzeWZZSm/tCZoB9IKT3nenfKLNEEfZqs+XHhEZaYzQWZmgVNFZF+j8b6O2L+wNPV1CvvzTM5pNK/Th5b5SB/nEeZBa8VyKF2r8d/ULxlD416MmfszlYl2jtnUQg9+pzHSmcDGzLdtdF1qJ1p5ZivuXi1J+UWF9nW4vhSNux3tL2a9x3qTqD/1JhjG7GP9mYeEGQwmuMzs5//sZag+owm28/nSe6aJ4kyh+fk/LB1EcWYTOJkNLB5XmdYYWlNmGWaP/0JxFhP4mQ3QTO8pzJbJBMeYBV4srEOWOdQWzjg4gyyLCbYwm3GxzVbKIasJVjNb8EbzleYnGo/7eqLdrzRG2UJtYb0J6Si/7KmvBz/abmZDqoetoT05hwksGmmfLvZeTP2SywSn+JxYVKMXWTTOQRaX8KbDaZqDuUMtX/lnEbRurSZYCtLuvF/roxzymOAlr+/tuSEU950JdjKbvrlyO8ovrwkcfNzHdrfQ/MxnglJ8jXW4RO10o11kdilN78u0/vKb6L2aadA+zBr+URgUMEF6jTRLy+wHhTkK4h7JLO7n1yMpvxgT1AJpNeBykOZErAlWmqVd3pHxX2pLnAmqRkorXiuB9heoa6LfOEqLFuM73JPi6pngDUhbtuB0W+qz+ibowuK2aYo2oThHaJmZt2RoTP3ZMNQyjHtipTFKMNHfckeidfww6RTtWY1M0E0jLeuAEkZaK01MMBikZS9/sCy1Ey0/i6ub3Jz62t7MBMtAWo0t73ZTfzY3wRgWl8E1KaMwaIn7RIS082kCU6m+diaoq5X2W8tZ92n8OprgKEg7OzlLDbIk3AeZxS4qGUX90skE/VlbGmfcTWPr+9kEyYqlQ1vkezObxqGrCYaCtFcHOh2g3LuZYA6z+b/X1FF+3U0wgZWZ68qHBbS/9DDBSCW/9Gg5b5ceSmu6twmah3+zDGjBYflp3N39TTARpOV9eG0ctWUAtiXNN8uItmbztjDaC0aYYCFIO/X3X9/TWnHhumVG38tD86GNiZB2vF05uZePM4FGI+18gY6dKPcJJujK2uJt/f0OmhPTTfT9CR3aiGV16tP8RPuFWeF6niEUN8MEHZhtODRiJ/UL2kZmZTT/vhLm/BXHj9m93XknUZkz5Zw=
*/