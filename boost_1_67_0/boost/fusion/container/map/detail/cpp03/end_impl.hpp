/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
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

/* end_impl.hpp
btLkl9ZfS9gHOpO9rixMg3YpXs/PSnDGul7Zkcx2HCsXnC2J1OsoF+fZ4ORFwD6C7CSZKZI6mWFzmubaTC6SnN/qEyD0KDG/w8tO29D81uEXYsDKOyQJOkp+Duwt2lfqCblDP887X3/wpP0d+tKZU2J8g4YtUTwzkXi5RD7ZIPmWk5ygpzWSZwnyVs89bLWMXnW//LF+tvcB/cHT9i+nfYliQ8Y3vK8WXg/j3iPgrZ0w4DP+f7fEEZAa7z/FPWnKlqhlS8EbS4Id9BUKBXVfgs5d073mq5corjmgFT3a/fgD050F9ipz7eWyny4rSbu1AQRfQ0vUiTC0zIlNqr4+gaRqy/BJ1VAw42E6JrdJcFpKf5jT+vtCoXMBRduZOY1YpSTCbdnGPYSs99X5EFLe9WC4V8BwzG1vSY2mPq6ARdw2exkdb5kGYjeccDb6gdxjkDwmbD9UqSI+6s7hei/dKUKeLUG/9yXKb8Em9m+XKNfIAUNZ7RGaJtuAkkFJMHRZHMtyfip5dH08TZ78UIm+Nn0WxKscouk39/LJGNZH8wbro5bKKjlgqkYVPI0HzTVqmVihCpiwpG33RbIdSI+uSEpdzitUZlYrLPI+WoF94SNm4XVRkdzimFxs0S83qystNCUdkxXDGIQqtH1+iwVTrowcL1DM5wkLsaVc2vXBTJpIWWnhhuk/75H7UiTfY4SSC9HcXKpbT+pCn1FyP4NzIEEMNA8cdqB37g80vecQ8dA+YFARxuAKdfmgfAyRi7E8ggHbcaOw2Me5GOUaFkXzaCbptfeAxYJ+uc/g/CEB7EyX+5IAeorWkGOyg36Bu835Y8gwYkCLuZBt3yeLJc+bpwbxmSWS/m/ZHX3/4fa9Tc8G03WklqkvPE0PNd7N8B57dzzdZdAlo+pPJR/tTm6zip4zOV2/vr8vpHbBbHkqRfI8ZeBaWHl0632SHpeiiybKCeTeyuUEcllK4a7z9b+rlejBljvtD8qGbJzqCzKUDawZz85WmhAoqs6JlB4oFqVVlnNplffEbbQ4KbWSaT7HrBZrh18l/e5aHH4dRUplUuoKPvyK6fszByTBQvoPFj39cIWF3kobolIs8j28yFp2Q2VS2mm87yELXrkCXX8it9X3hAmyo4AmKVdWWJSagrW96E0rNXq06FyXnlGKD58zw3tdDLxXjAIvtxJjmEeGt0TuTZV8H2kBuof5ep1UnyK39NF3ccM9vnWYCLzKaB1QMItjeX95MaegMfdn7Lb75QaTtXXWXC0SXa6/C8pspvOGGHwHlfSJxneOJWLtlYvNBmUOp0A/gshscK8/Se4JO2mYJIxJh7AYMCYgjZiqUnPS7FG/Cn5OdPiEMFAqLd1zuCdiscX+rfFbmmhEkrSCGPDPFDNJwv6Zr0LoD82f1e5CrUPlgQr5ZYSyoKBGFJp5jGZHxJpRHAXbHEuoOGJhAo4LOUMw7tHh+DjCCKNvkRssutZZnJBTex6tQbIk7OQTymU5E8lli7Db4QB88pSIQPzVKS6SaZVfzuViym4kGakP551Fzrgpwhlq6CzwBmktygOL5ZVzSXb/Dtu/YSGB/ZtE1uW7oTtTXYsG7whHg2MR7sJVRN4BgutFQIG8Y7qg/nOJCN/JwV5hNIkh2PhpB5J0hmYQtjVL5Xqs0+HIOv3+3Ns/I67jMmAp7zomrOe/nXwcGL3zl8u9dJP6j5Ni2z+FBrGAvi5nOq3K5T9idShT5zxffu0lxseN7slyA10FZiR2ykQJUKf6K3g4lZo69RH4OJVGrnw1q4TEciqCK9wHhvL7GaaPke4r4bS5bdzqygSSHfQj7CX3U5OSOcohoYk5NollqUvj9UF0X2P9CcEgokQylGx1HSdyBZJYQQ+2q/MXqsFge0VN1z91RsqVzEJF410HuOhsCmGvc0ryLpyZ+tp/Zmb6hcxt6nS15fGSQ1t24WmbY9HGK40ISqhFxfcMnF8316jBrnmfRQDZhWbIDUnwakG+0kFeuxQnuPPvE3xvhN0at2ohMCji7PXtQOje7q6+Y7Sh/JL7YW7jq/kMxoaZ0vhsAlwSu9kat+i0PSy5/lv0ZaRDfY2Z93JiEwMqlFQLeK2pNArQ0bf1Nia38zYmZhVneg+vUqV9halWWIaloggkcv7I6/swlSm48wumoMv8DWsiGfKqMkLhDSEoYN/ghgxyT5LkemHcu2giVfhNLp2WPlh4XEjZfPSAnlzwRh1mZcGOyGFGpFY2NTGdYVAgYrs/F3/V3jBmjvRMvuUa6SzftEFrZWr/Nv/FLj7P3zEw9I536iYlsz2qE1GLvne/FMz2Niqp9+ol17LJd4EfkeybJyeLBDvK1X1sqy3SH+yxB6YFAC03fZN7iOaLSerLPb2Sp+aYEFrENk66kJvzt7/EAhchHPn3VUjrvwaCRQsRUerp5OHJku9PwtFvVddy0pOCBKiCQun5gLoOp1rhv5446XjPqS+o6Np6YV+I7Ut8D6tiZhzrPewfle1gGmX74/wvSM/dFDjbqtjC9WrGfD/LDd/PlO1Phw+i1sYMqAqoXdGI6vPcbsP1zHmo4POCUDKN/IemcV4yZaLvBhO6I/dETt0KPnVdSYZJfVy9zRKEBMYt55DAOHAOnSnvagyRoPmKFSUoXY3cweXhxWaouwgbVNfdhWdfO3++lD/noKF1y/hzjqV7eDl/zqFx65z0vMvAZa1wTc1/caEZO207/OmrFuucqwVsWUMuX8Y3Y852/QrzQMQoTvcPdYlc3SJjaR4e3j7hhoDvbqE//R7h0vU9wuXo9wiXY2MVJuHL5XGNGH5xuTrHTtmIqaJHo8ORNfooJBLxCjT267TE+TE6BriBjfyajosQ1o/VOdGYpB8nGKaYczuht5vH+3YLiPByHVQdZ/GYZ0EkcXfSIGPFwwkd8eE2HS9zv4VKM/RQX0YClCm20KjwLIU8HMpqZdfyW6B7m0j3nrZH8eXoo6pCRoIE5aPZ3B80twINrTJv7nqshga5YS+zt6Hf6G7JNTWFDt7NyIGWXJfSc3UN+sTlb+6iT5xTko/Sf90X5G9uOg8/KKL5kz3nifoqGH0NUNnBZfmRnuXkzmO5s+SQpaHIsbsuk8My53Hw0x9pu7FXnn6UFpS7tHvAfvWDYLe6n870Vs6Lo+HdRVr/KmOb278ym/3689ivf4Tm+N/wHAjknk7zqPsCR7KMhwrS/jgfozFL7Rtw6ytPvPRhuk7dibr/DFIhTTcGkJ7YQdMwYAvsbeOASUzUbQaJIuTyYjXknblCKf83FGFjIG/k+UkOnaT5O8PzH9bmzlS8rwI3s9f/w0ssgU+SZH9S+EWIsr4Z0WHNfsAtoggzkP866swI09EgD8+mSIi1/toYD1zGQ4EjlxoPgYfDo71vEwyj4zPojd4DcY25OPBJsuxPHhj27ujDegNfDHpV8/vamJF5Yih4H45hTHtcYzJIkMh+k71tYOCnNNDR53xI7KYzU+SiwCcpsj9lYPDRuAg5ZNhxGiY1zaZtcwTB9vG8ejC2XQD6LcmVFefoMQI++KXHtJeii+SYXnp8DC/t4Zc68+N5YZhhvf3Yl5qwg6AC1CrOlZ3oMeLok9avxu2XJNYNYxeiN6ihcckq3f+ki3h15KZKbn8f4p9EVWH3C4QAvAnZu2PqD2dXVtfwYZN9c9dVC/oQ2J6Hfu8k8qYjDKkN9E1hcNpNaQGk0QpwMtMOyN0WtSW2gLA1uoBwLuxFxvfpgMohSG0xa/VWmOKZRPHuIUUvvCVG/Xw4+zEULZQapxrZ0JWn7Nz6Qbru7hCqRFR5c6XWtVvoby5n2tz/jYHLKFslz+eIymqeftoAQf0x/9Ek/liK86/ZQ3/MCiehuEPS+gUoRhzIa0vnWr3Iv2/O0BnFUeQY21GEhS2xt8V9PlrPcD5mKD9fc3YgKrK3CfvcOOCpY2+eRcmSW5OQ+iDoWTiLK6Ltlzz+0xxnOl1uthHERPQ7mei5AD+a6GWC6B8KoqvNO/STA78wvScLPEPpDVIO0LvlNPdaDWuU2bu15LDsQfknGdXql9VoF2pZ0HXjTchVNMunr5Q8D6ewRpjBdmRnjrmyhquL2kPwzF0kbfsradu9EXMMw5uR1iIfIWX6eZ31EguMt1wqO2DiHYvCQJ85Dfa2UUfrxzXaMK7RxjONRp5gyCJ5+omu7jbJVZnMF0QxYz3PeHjwjEgewnRov/T/3V1vbFvVFW98Hc8Ek/coXvEyL/PAQoFnINQWDTRFTlWCFbLw0mVJKEkaMWQFVHURakaCAlrlRMrb69sXguBDNXVf9mGaln7YgkorHBPypykBXKtldAqtqqkKBEGaQps/jb3fue8920makJQhpH04Pu+9e/7dc+8797zrd++LxERTnPKGG5HZYGzijIlljMbUd4bDs2EO74Y5ijbM4VsvxxvFE3zA5HzHC3hHonyW77ewRptk9ld40uRuO0VrrZTjAUj8Fveb2l8rmeDpf7oFjnu4BRhfb0o/3YNvl0LmcReX8x2kBDNSbt4fXNKu72oP92poXV5d3qFfq8x0hPUzyetn4t8VznDWgFPoGqWVVsefpnrTwzl/PvrWei+7tXvqUhvluHPDKnLWydFTZ0GQSbeJ0H1/ii+Z8B0ced6s5f9jDdHzRiKuCT1ja9z7TGYHt+y93PTxyhlJMeGPNMVGqyZp4HJWT3aXL6T4tve05ld/V55Pysh8UmaGPnmtT8wgzbj1LEziU0JudSb2JX9gQ1VwSunGwSS93NIm6W5e/n1Bk50+cBUT36FvwE6VHEzSi9UHfsSXGE499G2cpE3/y4QSCqjVGZavbCSGRJqh3LRv+7XOD5sadQ8tW7tt+IfPF3mMJN61e/L5x3kSX4R+5NET+Pv4MqM6nsDTBrYeJN4XaaFRp9eJBpsS+frrBq+bfxXcE1mY7dws9N+pPWlPXHzCJLKro3x5U5yScX2NBw6yV3j41LHEBXaOBJFASpUEof8l/i2uy1B5yVQ5nM71x9RpfVHHBa3yjpwqY3GFR/mnPR2WtnHLL+mzdWmblwxOHs73usMIL+vnEIlDXMpx67t7Y5OFTUq3E4Uj3Vazl95w+fz78Jeje6Dtp8BWdEi7TK/iTv5lht4b019sG4zM5qC80ku+Fatx4Jjc8sWScmvbj1Fmpw9ROifzaNWKWZILzhoumRaB2XdPll5dwmnjnFmav1jMKuf9o/7Pct/dov891LoGJA20yOWAt5WUtR7L5fkq3ysvcfGYjZ91X227xX/6HX1dcyRl67xFe2o+ccl/0n9a/Vnvn+4Whei++qAQPVHPv7sePVwfBGbn2YR6v17sazGP6blPiDa0gPxvLUQmZRFJ57PIAhDEKSC9JSidzyakh7mMdEPQonlO5IuM5sw6UcMdb+pM7fwJMLqvPUgL0sDVrlt7oj2ob7jmZsQkGox0t4gSrqZFlaj8TMrQhNRFTpG5Uq/uOHxT6nwr1JWuUFe5Ql2DuuPITakrXqEuuEKdrKujueesq83qDt5A9A34Tq+XLdIGlHQE/+/DczhxwHvSIn8gwRGncDKi0tunL8nmE6mwUtpCDzBMV5G53Nmim0JL581rJ1r4bh2QgcvOrMtUOb2FIaPUMCqQNirAjQoaRpWkjSrJNurN78eow7pRlWSUVipJtHBYplCIUBySJmi7MTqibnxY7/FOdl7o+5SdSywYAsOKm1b/uliDaQ4v1fXgHqJ9TaUGMolfDyuHdZMavDUZO47odjSk7VB0ac0gq0/bUU92HPnf2IHg85xpi2kHvbnqf3/y53ffgUGrfnBJvLTrUWcUKZ5jU1veCCIoH0gdCHeINaGFxHNeh/+k8WVe9PK9HiG6TYjWNQvR3wbVYWlQepcNqWelMzhv5r9B6Yr0DZ0x/D7IplgCXEE2hd9mNkX2Cn376OeK0Dco9CUSi4lkYjYxH1YeDCsvNYeVJzxhpS5IVq/4PlcgEz+LYX2JHj9Dx6x8VSgtTz3G+KERReto8T9938d/+pEar8wrKBsVTFo7Ba3qOiooEwU9oWj0JvaAZ4TW4dL/CVEZ1Wy/IERdQvQovT2t+R6V5jVnofSp8vx15RGl2qo8bY8MBJGPpDCItY3zt6rR2fynI1/+Xt3VW6w29Baplb0IYL0eNspOsQ+FvnGGvGmn+hmNJInFyLAnMmSJLVrCyt+bKSGbkvb1BqRJ9hX5SWYILiAyKPYfUXmhtAu/U1kk0mBikY2kyS6QEULfEMM4lJhFShObxeVyD73Beui5FJ8LChodw/YL6hiBQfhXzvi3Ev6tCUc2ob1lBDX7r4Rovf3XtVrgdmmsTp0ToiGXmojPS/H4HLzCTmnuh6TLuGqR5sGxGaHQJ0Rb8pCHVnIeHlaJrUA9o7Oxcc2n81hB7eG+BasTJ8VgdYBVNlmDnNW9ktUGaq/JugUsNUK0NR8XA5pPZ93FWQvVswbrB3Q38qnRwL1sXoLvqB2Q/cTVcXjNy6YkmiCl67Aqvih9yb90hvN4kh1AtoImZt+AzxVL2sIKzc+K7Ap4xNgizluo/QOxBRsv5UtnfWGl1a4F9DhUDIlfxVMIc8UkV/Nt09ksdHdz3aJ0DfdaKYlYNKRs5hsRKC15FFIhrUALbJcW1In4gnQuPs/OaL6tuhSr5qOCBq8szcRSOne7E+IQlVrdMLUSdJpzm3QNxA51IZ6S5uATtN7t0AdNNs2NQvDt5eetW5qkOPxT04iy/Ni8DR0mrMiFk/FC6jTy0vwLeZUQzcEdFJsFb05YKUOnK7MCcFpmB+QBHIB8gAjYDHACtgBcgAKAG1A4qH8PnJxbVzv5rL4nA0VAD70uOWDRqmz8icyfEqLV80J/a5LNbL/2itV/ekpQz+pPBZ25b/PNmftbUz1yEnTX16Ap7pFJ1JpicnpwJ9zOzm7/mFPcpq/qNMp75BylI6l0zLMhPDM8KXT/JqVvOpP1fXPY7xCiv9xEm0Y8TjN8Yi00R2Ke2JyNXfb/e/uVVVWzyz3i6sUWFMs5q5czKresUk6h3d0jMzaiNFqVRnIGu7wKbY+oG7NasZyjW7NquUW3ZtVyboVDabT/8FY4lUaRW7H3ezQDqsa2n3pF8J/sCbEmpdGtNLrQZ/TPzXfm8t1JlpRk7reDX9C7DGbI7vLSixF0z/zDS9vLhSM2ilVu/0BdZLiZ5meEaC3GsqojQnT/gFaK6Kh+IkTzs2PqI9KcHpQKpHOgFvkmStFXp9UxCrPxOQmhtOooZTFCtOkjBJopRLNxyDsqncKVaWmejSEmTeDKNKPfo+wcyWdIDPZ/xH+n2Rn1cwxS7CsKsbGURfqYEmJ1iq59FpuzSAhGCOd41PIqJ7roNRiylYKQW+ntojfYNOe90rhyqGtUf9MaA3xXC19V3NkV0krzEPUbuorAS0seQEZrZ4KRYUtk1i4cmk3ypU8ejf7FGhbprw8732CI/l+qEFWL+oJdK82RYuq/1J0udRx1Ho3PsiHNVyLN6sPUT6RP1Aq3GoNzvOrLzvisNKvutFLypu6h7d1dhl+GpEF1j1OaYzG4ZI+V7XEyMFrh6QoHq3CyCqv6mekINzmC9rvy6I6YxHgtDWpuNAjVEKE8rLzarJXapVF6tES4CCtVsuYokoZwjHDLKapE8hLG+SDtJxNWHkMMR2V4WdM0JHikGA/N5cWRdz1wCZIWUei2Uj5wyFuUyRWvuO7YdPA96l2D31N8ByDNK7sLAEPL7gEUAe4DYLgsewBQDNgKCAAeBpQAHgWUAh4DYCAs2wnAwFhWDggBKgCVgCqADNgNwNBXVguoB+wBNACaAEg1y54FIGEuCwNaAC8A9gH2A1oBLwIOAH4HaAe8DOgEvLp0fHrx+o3GJ/sPND6tQWGhmBSttqxFwyguRauta9FYESJBY1uLJrdHRneptq86XuYqHTalw5IZNUWMmuPJ9KhJsylCVKQ9EUX/SfTYsGKnOZ7aOiQi5OMOu+7YDqv/JCz4wLTACJpJoT+UYmO89LZlATUl9NtvXASZoZxVuBDPQ5ZVyhDLQ2yVMoYy6yplVpTlrlKWywafErrv5InEM4PcH2/Zwzkhe1gNERaFt2QLjkUcu8I5ch6O83C8GXgzcIHwVsgK7MC5A9gJehuOnTh2gz4fx/k43gK8Bbhw+XyaoY90WIBxKpNukmnL0mfKz4c+MUs/6XMZ+iBfLsBxAdetkv4b6ENwedti/J8AYRdANA3i6XAO9PIqG9X1AHuAi4GLgYPAQWAZXBeBZ3A+k2W6adJdwHcBbwXeCrwTeCfwbvD9B/hrnH9NVTWq6TTM9wJ7gQPAAeBdwLuAa8B3Cfgqzq9yt6jkmrRL7wG+B/hh4IeBy4HLgWsjA/YKoduFth1cUn9rdv2vgzIJjmS6/ummSDeDrs/sEnng4k1hNK3pr3STpJtDt4+ax2V0Fd4kOC/M8q/pL7P+Zn2KgIuA7wOfD/gBnD+Q1R6mf01/mfUvAS4BfhSPzcvqT9HUXhcVzfG4ls+/Ujwd9jzVdnlv07L5gJX0Feuht2bo/3p9Y/Sfr4fenmXPBun/sCY9zdfQGFxbR1t3xCzcMqG/GkNHK4aOjv8C/DjnqggdAIBDS+xdD2wc1Zn3/PVkvfGOnSVsnI3xodXJxRFdSFQcLgeGulYoJlkHZ21E/iBdm4tpGoWrXaXXkCbamrO7mRzXQ1edhHqtrqrUa4+ig3OB9LAdk7iIFkhSTGiOAHdSb90QGlII/rc7933fe292dr3eGUN1OlAQeTveeb/f982bN2++73vfe1vSxoSzQx3w5uDjZKkaMBbWhIbjC52vAQJ4aYAhuxCBtOYUOIVgC8BM3AVQHE3XAGqChODBHYK7uwcPusDiBHd3t+DuTgKLLxLc3d2Cu7u72933+2/dulU8yfRMz9BnTtuGIgwiCUH+ziVTOIcbrG62+dXWNtnvorMbQycf2eD3NKHbDYH67yH//sFg/OxzMDLbQoLCd8pQh0U0hbKmxLGTxNsRmGUf/0ITxl9Xc1Y8bi39yAPzUbS5Yfr4QFJfhnDmJZhmvyD2geGt5jGuxfqsM21MA1axlz3CldqYBdrLjBSnEFXfk1YurqZ4EmVjlZ2NB9fLnA29crxfEUfjU/OYvwdMcFKixhijemvskz2+1JYcEKhcEMmPl774/3G3vOq3qerazBy1EAEZbOu59IUAdX8=
*/