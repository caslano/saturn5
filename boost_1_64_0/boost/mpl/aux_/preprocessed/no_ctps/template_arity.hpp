
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
cy+9ffexJnsYpB0j+kt/43LoS2Iy9Ssrje+hE2ZhEzyHzfECdsEP8AZmGKTtIZ6Q9T2Ic2V9STIm4XisgMnohKn4EKahB07AdjgRe+BkDMQpOAanYjJOw9k4HTNwBr6EM/E4zrKMlfiAtD+UdolKXMRvHdv5spTvQ6yBV7AOfox9MBuH4qe4Eq/hevwcd+AXuBuv4378Ct/Cr/E0foPn8Vv8BL/D7/B7/A1z0ZFYfsCH8QY2xZvog7ewM/4Te+OPOAx/whD8HV9AQyn6m2IpvIGl8Wcsh80ptwO2xorYCStjX3TCYHwQx2EVnIJVcR5Ww+VYHdejMz6PNfE01sJzWBs/xofxa6yL32I9vGGuZ2l/yN+Nsh28+e8zqExzVO9GccEn0IjzZH9YgF1xIY7ERRiO6TgWl2AqZuAsfBKX4Qp8BlfiWtyKu3AHHsQX8TjuxHfxJbyIL+PfcRf+hLvxd3wVDdK//EHchw/hAWyIB7EZvo4d8RAG4GHsi0cwGt/ABDyKSXgcZ+KbuBBP4io8ha9gJr6Gb2MWvoOX8F38DM/i9/ge/orvYxnpp14Xz6MvXsBu+AH2xIs4Fi9hAl7GKfghTsOPcBVewefwKr6An+ARzEY5/qU9J8eqzvH/mWzfa+iMn+PD+CU2wOv4KH6NvvgN+mEOBuK3OBS/x1F4A8fgTUzEW5iCP+IE/AmtY+pKXM/qjJUaIuelUKyAYeiEY/AhjMCmGIVtMRq7YYzEFStxjMVkHIcLMA7XYrx1fAdp14mVdMZ3GC7n2xFYAUeiZbmsuyzXQpbzlOWMquWy77JcF1muqyznr1ou9y7LLZPlMmS5J1GWIwj7y8XLcgmyXKIsN4BURZYLkeXKo78s10/eQTUAa+JArI2DsCUOxjY4BEfiULT8vmXIegfo/L69LvEcQic8jE3wCDbHo9gPj6Gsj0LaX99mWd8WWd9WWd82Wd8Lsr4dqvpKMtqvrzGyvgipr0hVHLNkOT+dON6S5U5KHKckjkyJ4x3shKfV+9dd4mgl62stcbRRbbdsWS5YZ7t5y3bzke3WXrZbB9luvrLdOmEQdlbFE9rSfjyTJZ4pEs9UdX3eZbmVstwqWe4pVTlmyXIBOuXYVZrlcDc64R6sg/uwKb6GXfAA+uPraD3+ZL0VdeL5Rc47v6ID3sEbyALS5ko5ps3L1VXOb6qxnStjXayO9dAd66MnNkBvbIh98REMRDeMwcaYgO44B5vgIvTA5dgc12MLfAE98VU04l5siW+gF2ZiK3wH2+AFbIsfYzv8Ab3xJvrgbfSVd+l1xJrYCZtgZ2yGfnjDtJy078JAqb8ySJymqbvsXz2wM/bEAdhLvX/K8gN1tutm2a5bZLtuQ1d8AVvgDuyFO7E/vmTdrtK2Cp10tmuM7Gex6IhjVcdtUmv7549XZLld6IS7sQnuwea4D/vha6r1Zcv6+uqsb42sb62sbx264bPYFJ/D3rgBpVy0C7JfrtGyvhApVyha3q0bKsvVlf1V/W7dsrJcOayA5bEBOqA7VsKW6IhdsTL2QSccjFVwLFbF8VgdJ6IzLsUauApr4tNYC7fjQ/gy1sa38GF8G+vgaayLV7ERfo+P4m/oLn+PN8Ga2BQfxmbq82Vb+/WUIuVNlXpKk+UmkXJluQ2ynCPGyXIzZH+eKdtpFhpxNrbHORiAc7EvzsM0nI+TcQFm4EJ8BhfjOky3xi3tcNBFJ+7P5Hi4hjXxc/V5TJaro7Pcx7LcJ1gbs1XLVfG2fz7+Q85/BtN+AWh5h6KrLLdEllO/Q7Gi5FcJndAR3bAyNsUq2A+rYhRWw7HojIuxBlrf1Sj5hOjk06sU+WBvrIB9sBL2w5rYH5s=
*/