#ifndef BOOST_GIL_IMAGE_PROCESSING_HESSIAN_HPP
#define BOOST_GIL_IMAGE_PROCESSING_HESSIAN_HPP

#include <boost/gil/image_view.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <stdexcept>

namespace boost { namespace gil {

/// \brief Computes Hessian response
///
/// Computes Hessian response based on computed entries of Hessian matrix, e.g. second order
/// derivates in x and y, and derivatives in both x, y.
/// d stands for derivative, and x or y stand for derivative direction. For example,
/// ddxx means taking two derivatives (gradients) in horizontal direction.
/// Weights change perception of surroinding pixels.
/// Additional filtering is strongly advised.
template <typename GradientView, typename T, typename Allocator, typename OutputView>
inline void compute_hessian_responses(
    GradientView ddxx,
    GradientView dxdy,
    GradientView ddyy,
    const detail::kernel_2d<T, Allocator>& weights,
    OutputView dst)
{
    if (ddxx.dimensions() != ddyy.dimensions()
        || ddyy.dimensions() != dxdy.dimensions()
        || dxdy.dimensions() != dst.dimensions()
        || weights.center_x() != weights.center_y())
    {
        throw std::invalid_argument("dimensions of views are not the same"
            " or weights don't have equal width and height"
            " or weights' dimensions are not odd");
    }
    // Use pixel type of output, as values will be written to output
    using pixel_t = typename std::remove_reference<decltype(std::declval<OutputView>()(0, 0))>::type;

    using channel_t = typename std::remove_reference
        <
            decltype(std::declval<pixel_t>().at(std::integral_constant<int, 0>{}))
        >::type;


    auto center = weights.center_y();
    for (auto y = center; y < dst.height() - center; ++y)
    {
        for (auto x = center; x < dst.width() - center; ++x)
        {
            auto ddxx_i = channel_t();
            auto ddyy_i = channel_t();
            auto dxdy_i = channel_t();
            for (typename OutputView::coord_t w_y = 0; w_y < weights.size(); ++w_y)
            {
                for (typename OutputView::coord_t w_x = 0; w_x < weights.size(); ++w_x)
                {
                    ddxx_i += ddxx(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                    ddyy_i += ddyy(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                    dxdy_i += dxdy(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                }
            }
            auto determinant = ddxx_i * ddyy_i - dxdy_i * dxdy_i;
            dst(x, y).at(std::integral_constant<int, 0>{}) = determinant;
        }
    }
}

}} // namespace boost::gil

#endif

/* hessian.hpp
5TTDh7MeCucjqQd55XvCv8CbmkLNx6gilqTVm6iayovx95yhGULY4thKzCWK6mCryeDg+53AQBMQhzSzKsPvHoNm5F9ckt6x6IypZFeBoMWuTpKpunSXCikUQLUhcenQIam5dcpV/AlQVE8abUvYaSPx/AHyta0E4ABrZAdzTkgGP/YlTXb9II6GEatAIFcZq0Kuxb2cSUfGpliQbrhL2uzAfVpcliUC2FCjykETEAUA3S+ikHCOqu69DboUt0Atnb83Ac44H34kFE7oSH9WbiRkOJHamA4aW2V6j2Rh2X+pR7KUnpdRw+egT5BvV93Dz5Pi3GuGhL8MpVrxvtNXl9xV+ZSWkCRQe+yN2t9oYuZvsbRiILvA09k+SIi28aD0x0BtmvG4OhpQCAz7T4i7bqpx+R67cjrOirzJNE7wsm1OQ6G2jHa7QCZWBjUsj0H5otKlYDebmiBgIcJYn//VAXx8ND1JiOEJR8dOJsYUb2IfioCwmKQ0gaMA6FatCFKMqWcja/zOUl+agaNLEPznp3Y9NyjuJl5v/4gaAh6JNjpluYIcIXjxOKMmmdiqJX4EO2spdMRaDbZQnrEWIak1I7O885T3C2SOEf7Z6jKvWVsSbiN6SQUIhpc5cFml1e0neunw0uAQC1R85uhFEXX+7ZP/JCAaG7Bz1QMmSYSPyEJgqAyEmgG2R5EfrqxK28vLAPuETkBZT1xAf8yhSWI/DwuA5S3cGJQjUbYOA2uiIJ33j/yofL047qihhSG2hyOUiG1NCWmSJPGsenvw1pWG5Svc2+yY5HUfG/B4SwYByRLbGQIaeoBCpXBDQBZxBV/1nw+jB6rLkoi0xwo48lGUozy/jLIsoPM1z4Wsa3X2Nfal9X2sU7L8q96L6z1ffoPZm1uQWnordKbAC/GU4NBbrBsODnzRg0+0bImAMseCziWOuMGPchCiQnPs6DnlfEpCuWEKgUfuysTTPeX8cqq9sP80D4KIarBqvX6xSIvUVaWIN4S7LOy1OKNFOQaeAcUtSHoGcn59c2F+PY0rL8P6ZB9iWReU6hRAqkvaMKePucT+WjpIziK+HRUNSBudBi0F+T9JJIikYxgWtu/YxbbLu/22AUtgZBYGXC6wmX6PYTOXa3nyhsiov+e6xrJvOfqCHtoAD8A5rpVFPE1sA315J/1yXXZcBtHCsJ9Z4rv93+/vb+AWAEDQn+A/IX9C/4T9Cf8T8SfyT9Sf6D8xf2L/xP2J/5PwJ/FP0p/kPyl/Uv+k/Un/k/En80/Wn+w/OX9y/+T9yf9T8KfwT9Gf4j8lf0r/lP0p/1Pxp/JP1Z/qPzV/av/U/an/0/Cn8U/Tn+Y/LX9a/7T9af/T8afzT9ef7j89f3r/9P3p/zPwZ/DP0J/hPyN/Rv+M/Rn/M/Fn8s/Un+k/M39m/8z9mf+z8Gfxz9Kf5T8rf1b/rP1Z/7PxZ/PP1p/tPzt/dv/s/dn/c/Dn8M/Rn+M/J39O/5z9Of9z8efyz9Wf6z83f27/3P25//Pw5/HP05/nPy9/Xv+8/Xn/8/Hn88/Xn+8///78/AHY/lv/1V5j8L+NfHtiVn9eQeC91VQtZKx+lTHb7CEN4ObGvt6Yt/cXfPHgMQVTa3C4ewo4y4paPtBvnIQ4rJXG6FlUMaCexxSQeR/2iOYMc9Sn1CDEgE/dCBraRRhkhg8GkjDbyJi5pO4h4/mCdcR31lbDedKqPmK+zCyjoo5CDlN4lDeSqmDtOML5eGWmfPieOCcNxo39Icw5/i/50NWPUEOG7yPnd30WmMC96qFfO8DHlrGyJ37M2rqdJBgPAklJ+Szb2DOaueAQPh117fgtMq1RJXaOZjCXoHehzMT6eKS0BTwEHXNmw6Peh1gARJHKoH6QSZho8slvIMoikURI4mjTPNOeWendrFoSV7NlM6dr8k4QtTTo1jjOL5b0gznDxKf4GiSHsD2R/pEk66x+uaxjd1vExrAuM2nVsJM5k6ZtzY+lJlNU91piWQpFyUSrGP0X+KCAZNL0oSPd8n+BeGhLRySM8Ob/tfpAfTtpXm3eDF1tMzwyCSfGsmVaskAa8ExsRmbH0y4cColDcXqWj+BuEN2uxCs3aNMdD+W7/0fAJIBb//hFD3UA82UNK0Vci98x2022sgcxkggsXj0f1if9EqbqB1+vfVnkIl6NfBmkQ3vpa+njJ+h9ifsjZofphGsaYuqax7tvidLvMRY0ARRKwMxhqtm9iinQ+Auh+R5NTgzkCdMOB41GIKwSLKY0AcfAGUW7S9hI4u+iwcMIWPoQIQPSp/gOFxVjVzDkGHBr/vCBHDFhx+6+1HEjrMPGYGIht1AI+EjBaxK3sD0scopLzNX8ZKSD6FCCFPHQoEioUsjnb+cJSVvKXOxJbdbfaGCAly+4TciYxxVgmjwU7Tof3QjOvJ3bO9h43BJe3mIATi+yJ4+OCcCbTzO6oQUnGQbCGIA5/m0n6iFwSydRQrK3LviTVxUwewp7gUboBeOqI1D3g0953HxqWiMnoIwo4aPyOy46nQmMHra+etc/klPR4120o4fQycvOwniPNVEyT7vYhoNFnrNYwFgN9puJpeqoGxbKNEKlu7SYpuvifML/9J+yWiA99vUBN4+Yo8xT7ZrkzObmh51L50f5sm73gO1dkJ+rPzvuj+z8L6REU/9egEPiphKQ5xSVrp0m2QuamqVDrP6Zbr8lgyo1yqzwj6JmzBv6aWcLFrPcty3zftwlR5XVgmHWASPQUlIGvUKpSgRVKEr5sxbJq5Jxo4SLGIoPc7n0Eye1UaWbg2SrAeLYcqn44s2uiYrgKSdcIv474FZXZMv4zN5v1gBDHGvY7WLlQtOVKbkUntN7DWppokLi2Dhu/qH75BlX1hpJw2djC2MTZZXm4dhHRZ0hn8Hj15eCYcQSD1cA0L/BNG+EEsg7rhjpYvd6FcKkKeMa2Us8m7OK3xg8vhV0OJoLpuu7SiDjuuQiL3gafhTOzKgn/J9u7GUedgDMzliWbiMF5REl5q4u6xufY843lwAKIfkR0D1yDWPIVQF6MSynkA/pfJW0AuhdXZpFNEHGC8fjds4HYBqPYHpAhssP1amj1KjiHSQ9/Z8QA3DEqw1a1cJDPU5MzRfQEzmfwqYTkahsl07Pz4rIywo3nIvFVIH569Mb6j4Ej1l59bURMsu0O2remaLc+gmanr6w/KEvk7DNZ2dihDX+mydx/Zsnh565oAY+8i8wHDe1epX+2eYbK5rao1ekQ3jeRext5CWXIoo1T7DkdgropTaoqJ8wf6V9S/87IQNkOgMYzh2hdlax+WabedRnfk/DDtT8Dw9qZss53NAUvi6J9hot/yJflBQ+MANH22cmPG0YJ8DXGV8a8NGdu7k8dIawo/5w+sCUy1aukl52a1zgQ6Z0WEywU2CM7gtIUglfeMhxpH5g9ONEh5uG5VBL/93WX7jM3vHck+PZFlXL9ZXo6IqqgHhv4pYX3fubU8V5RWHj0k/GBSxp54FICBrIsfJmK4QU14dPLH9ffYyMDY5CJXK5UWHMa1s3wkRzDrlCv1D4iwEe2/CPvq58wR9GlgH+H9xEIu3QpBIpBp/SawOfswU+Ay2DzZ+Dd/vzI7DLI7AGFOucRj7odJy2apEmtHIDiPVmNUCtb9C9MehLDzo21VC9mE3I9uNQQqj/T5Gix3PgpglF/yv32p/VImW5dmcYUuuA0sfgwrVO4ceNzbwmaXa5tJ7zhncCSmIsM529Tx+LKDHIFfLgTD7r73brBgCdqN/JmmeFjzbk4IcHY/Rygr4Yy2JkjaywSe90xS5+9VXa3rperayvvV2kXWymvB/Z04/Okg9zcACoUcTCsPxewneGbrEk8raQKtG+zoCzI7K5eDmPtBSfi1PSNDSSIiW2K7yJEWP1/2FXU4U7abxcriw5/yIra+/Ex3WcDV1p45jQvu3LbQB8UlZqK/8UMsF3YVvPrXPKBSGy8yMK5JKgR+hUYVaxYWJZx8QB8mERlMP+ygjBXKZiH+w6M3TnMs2wUd0K3b9dMtz0STzqggIrVNVYjxfwgDfAa7lrjO127srd+cKIfUJ0p12o1PoShQH3LiMmGsabDieEkmrsn+VwXdsOWPdJWsWBto4q+/VfdCvsq6qESYinuB0DFWncO5bUw1jvi8HorwejYsHKWtgs8FuSLAultApl/MSWmuSbzNWHtdsYVHwIZw/CnSz0mK50Oua/bmv47pgV6yOtmpWgCBPyjbLDKiK6xhWJ1loJKGX9r0oVR11HOPbTG90VDBk1tG8Tj0ZIRbR9Gk0shkyhTsS8XIgFQPkgzwdoffeOTP7GqjxCTaZRtTeaeLyNY9Lrr65jw/+Kfco4JT9eY+zjtVuIMHVD9dzXK2MLKNLsLasqsJ26p4BaJoUkXaUKDc3bf5ofLzbxnKwhaVrCegOsVtU8YGj3daTzvQsDdm6w0SC0Xmr0NOptcqAX2iFOLTdJLJ8dPCcnKIc3LEQXdW3dXjephCmQlNdzO4LBZD4o2XIGU7WXKztEbKISNqnINit9s4KD5hpU+ULo7wya8tnAdyOXBr+3EtDgALiiPwPXUee60h53ibg0RTzsRp9si7s3OWA5qZh86hFSMyFa+4+ac61T1jARgzQ0t4Lcl79vDL4wPbPc2pHdkP5bq875PsItFUPrf8hMdl1Z+a/w1QKZSaJVSN7bplwqnt0PPzwXDEYk184QlPe/9pzqGchZOmfmQghNjfYpqWfLYL1eVEswqtL91/v6Djgp7SSiJ2c4Jg7ZobKJFcR7bYZvgOQDt/otgSDVW79bieGqi1YMPVkV7nrgPK5EYG57idDZMwMlpNChGo7U8lQ7QLF0SjC1z4EuIqGwnCfxgmg2QrhiKQNObGODnyREwvnWyjsl1kFal36WbJQIw1ceuaQLhNp2Pq1Yll3jytUg/eZNhjmB5970c95I6qbtypuLCFo5LXKatUyXaU1wLhPcpfLj5uVZ+XyImkrxcDIIlwfWec4hjLI5bn+DHmTcL/SjSxl8gUuMn89hDKWA0UrH/PrhMg2+BPrfu3DrHxqTsfAaSSaYyyqisX1Z0w/M5hvpogUlWqXhk0onLdUTGAFrJV2zfJlVQuR1fa6FonXgfzvFVDWAQJH5m6hhVD5G1hkEKu2+Cf07jujZ417+ciQCEd+v2kg8jm7nXqfpd7gBphMiDYhnHCxK14IaQn7yGNJc/RVOywa2RGPjcFzndW94Ed5jLCJm+1XnOukvL+ciWg81UAheLO5+ZBlZSa9u3lEZ2/UePwkc5MuOYpxxKjwQYBhQQFjU2gm2XGCmcVLurq51ckY71jE7G/qGpvgh1p+eurm316/kDfAn5OHHh87ENjGgu4JsYM9cr41wsrsGDglSOfxCdxfPdBtP7xwKAaEXlqpgDznLGPRw1hH0cyNth/Nt8PW8SEvRIhz3y2DaK8flcrVp8TrA0gkXpQUGbapYBNAhXrWYJJ1u5U0Db345dYnJGQZV2zL0F62TZpLD+Q//VUHFn0uGgGE1BLg5LD36Whr8F0sPig3hk0dp1fS4k3ieDYsqWj2I91m6feDRqo6OexyFTxsBiBYH/gZsWhim/f5DotzynY3Ehrq0fUjcs59wYRATEdfPYhKX9LSp5oEMVwmnemC9weaFFzYbWolFNHgAJgAALP/Te0LUWS3HnUuM/qoR5pXoxqJtaUHQnORV1j6WVohEeB5bbeVMhLkj4BgOxRt2DKRz/tExjHGdKLZA+opEFNJrz330hk7QtT2ItREdYW3+CpriDH2GeFdk+zO1JxYsEh30jFs3Irg4d2VfPf5wak5dPfLgnpS1QWO1SsO8/lERYp1KWtWgUF3PDEvdxQum5w5orcy83gmWMar/S0QEdJcs6fnFiAhoBKCgvAKEI32dgZFG8P2gpFLvTPWYqcnCkq3PDEhR4cpN2Zp1+Pzf6HJL8e0k7BE7BRRUy0+1nvJ6s9mFQNVSb9QoRSPpbJsSAYzNf6Bwp4XwK9w6VRmBUOe3ZZ0LEQ+uGCeBMpNhJDWhh8OzuWUh8qbE3IZepOev0SexpelJgEf8lS/vcULyXM1OtMe05XU7mkmmaV0G6IlO6sVbMe05fg/7KO4vPsQMgYnvyvKHvluQP5uwhoqvl+mMrrV0ouxCFS2VoCoH/AdkB58TiXkeQCeYYHdG7swN2zBhE+xxJxnAik13qW4Lm1QHmtQLWde8WoG0mX2Yo3HAdUZhlrmoumhtYIUTvYR3hZhollAiyvu4sD/zhs/8OTSFNhOzFKKHNMlwWUw6zi1V89MfX2gXmuf9tMwhUV1kgkO2P5viaSL79axdpPttUC3Nc+wwXH3/eOJTjE76wMLH07kdfTDWY3RxFD/t67bcUDm73DfezZbyYzrchG4Nvcxp+gvMnpcNRnuSE7RCGf0zrbiX5Q7RsegjCpmCdgwoFpNvCMYTbAnHhuveBnlKx4OFXIEWpwdtEva+n+UNxMAnb/XA8mpvvqcXpN/RTZK5yjLMBtCjuOi9dC0tqrQ29VSKO7QKvJl+r4Okhd47NTCaBZmir3oALjEZkqc2AVVkshQG8d1hyOMq07PvAg7MnzFCtnCAe856pIXi0oSiu7ic0/aO9wqn6qgV0E0Nf76uBu8HDoLshtaIeXAZ4uQE1JH57/9JVIds7m3btK2lHUiV80Yjszypt8/syi0tIWblEuJPXiCy8P7w7dmfWp7NiR1/p0++fHRwHl2dlgnn5W1Kqk/Lh/Hx1ymIVV6eVfZpvrR5RrcvyRn/G7IQ+I+SMFoHclzQ1izZwjkXR2AmyPDntYXjEA7n4eoequrlVH8Cscy8ljkkMwp9NIEHN3Pi05J5A72+oAQYlnZgjbiAl5RBMtMKOx5F9os/VgeJVIQHw6kBttysthiC+XcKWYC31tV0ObxgdtSC/DEiTeMJZHGazfI81ZglBWMEDSuK2WmoKEFDqIYL0xSshvEWF4r3aauJ2Ahvxr2L72h2bz+aveke9Qgg2mU3onrRJZvd5y4SzRhPkPoeUcOkxo8PfnBdB6iOvx12IbWrnpD/HxkLziMz1uMYdnTE1w4j/9jM8Vm76CfnosOXr1bG7RlGbLEyQ4I+bE3AxTMhJ5rHQZEDPsWTZr5VJWhOaH9nqBY7jgie0vTvlvS2GYmTZtRO9yWYCX8v9rt5uZ7Oaixcyin+OW5MIFPAvgi735E2iJu5d4Nzx/WK9Duf4NjPhNHP4ezTMVxLflDTI4+Cx6vpzsDEk8GKe+h/UR+wlEsBMis15zc1J9ij6wGzK0HloJUr53AK8GwLXw6edqVvzM+7UvJKr/Cu80lLTVG5hp6LbAsDFLxf5xHbErzmpWUhuWqemxcZUnPOnrFlZmC8zBecAbnIF5wRuZzPIqrtBVj/wXsMSQihSpqRLOROvIX43zF95EzPefUJFMocdOjpDLKmULSgxcAHLW8STMEcLOgDACYwe56uMrrWlMqbarxvSZ4RAvfsIJ+VCpmdJwD2X1iUlT2HFX1vKWyO+W0IUBu4u9aL8GKQfMMa2MY/ff8UCKytFe4gmqNsiK9cyqp4MvO2zTth87YtOZHzui08yXoWwvHKxo0rTNhV4RXTVgWBItWB4HXSrmCxn9SWkIMu4hdTeELt
*/