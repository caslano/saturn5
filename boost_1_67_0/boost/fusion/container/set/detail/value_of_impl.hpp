/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename It::seq_type::storage_type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
nNlfyxBBFTkJhQNyE/2L8mCAKKSJCRlVmn75AcFoW35CrnqQx98wZSHtwDJMLW1D+hN7GVVJxdntgzz+HlO9UiJKLGw1vr/iCyOaYnHWR3ufDvL4CzWrLksszm40vDcQGNGWiLMUH+2ePcjjzUAgWV6iWFKpfl8gDI+EzI93lx/k8VdSXVmcLEopUsDvJxLs42OQx98p1VUV6fGJeU3690qpwMiPxEEef6dUR3W12YkJkmo1/B6TFowA/WpQnv/NQqRFmpqQLJUZ3p2YB0baChJyBvXdvxUIgmiqJAliYBu+c4QgaGuOeGDa5xhZMecfwYPpZX1znliUWiSH3kEEQZrSk8oHpE/1P4iHEcZgRVm6SJxd3Q6/NZc8AlUlpdYaB+j67j+Gh12s1+cmxScXNnW8Jdg2jGqlogF6aO0fIz9emSIlkkRxWpnC8Jcn/hFElhlfoB7cP/8sYh3uaMpPFidnV7RCb84lBqO6kqSkys8dafJ/Jw9mzjKqanMTE5JzKhVvJIIhTRJRdr8TUA/y+OA5C4NaKzLF8cl51S1a+LWMezCKthUkJlUOwNg+/1Ae9vCfHU3FGUmixKxymcZgTwmD9CQhMSqLEsUFAzVmxj+Mx/8HY3FqE+AsAIBDS+w9B1xUx9MPEAULJXZEKWdBuqKiRt6eNEXBYEPUJEqXSPMAEYPBPxhjRbqoqAhShIhiAwRvT1RUUEC6LaKoUf+xoUax5L597/aeB8fL5fP3xRg/5n57+7bNzs7szs7MHZzEnV1akJWcGJ+YnHGIf+ac6B/6UDZXaUFaQtzuovLP9A9ssTzMenI2fzrng77XKy6cKfx5T1J8wrZdGblHjvNLTp0qERQfzkqOT9jz0f9t9MeTR/U+U8I6xvoLzciaT0ketNIqPwuPZCYnxMYmbEvenZqWlpqyc2tc7NbM4vLP9c85yy5dStEn7GO+VNVeV/tpyYNSWpUV5wWFR/JyERygIDd3f+7BowJKHJ/n30eVXarOMCLsYgyUR8Q2fnLyoE5JBz8kJvpBv8/4Pp8cM6YnZ9MndX9ISqQ9fKZXh+T9YdN7UMQndn/8v4Syaur+cIh0HazCq6zp5Mc/Lo/aSzG6hGtGpJ7C12Wf3397/vfJo77y+769IsuzxhCWJ+o+6Q8UPv+7g5JH46m53fQzXgunESN21tR8shcIFSuh/y3vZy6QyvpMPcKu/J0wtIfKknONnzStn/3hoH7UpmylCuEvFP4hHEsYZNR/3N+i7AQpuJpjLsdJEyLwI7q6nb7ayZF/8nSU15cFKRNuQhoMCa3NtXUf8i/0OuH/SBw1jfEmxBeZ72h5rO1KkCkN1Z/hbwb8a8RxOdeW6OYhxDBTvsuUrPrP7ydO/i1Q05A/ryvBPSc6HsLXcBKhbLO3rvFi5wn5B07HhYbGnFkqhMmBN+Lz8SZnLCFPRpVebawsLysr65TKR5IExerKhivlCTZdCYOkl0IGXqdPUiBGLM08X9fYUFtd1QkfBy7V1jc2XPg5yJggjJOEbSDfvgchNzooTVBRfammpqa6E/5uoLh8qbJk36qJXQkli8y24hC+FvK0CKLnUMcV0bv27d//cyf83bB//749cWFz9VXliX5epa+EUpDrq0cQ8n10RhqP6oSPASb6uv26EISuR7qwY8gO+WqUOtEJHw9UDKf7pl0WskLl/vWeX9ladsLHABsH1zVZZcI/gz+E+9fHdMJHA2HrH+0kgO4MwhGlFSiloHQOpScoDZAjCC5KS1CKRqkfqjNEyRIlZ5T8UFqD0naUDqJUitI1lORRQkqR6IqSEkrdUepJnUyU1FD6AqU+/4t+5U8Hqr0/30+AODfrInoS5+1B2K3D6tVti7LwPYGi3NSq3fjVHeEPc+ao7RIOVJs5VkPN1cVd28XHx9/NJcjbHzFrBeSoVaFk5c+zWeEd5Mjzd/MIDCQIXyKQcCP8CR7hgV7GhDvhg14EKgcjHgcR3qiHB6GNEg+9qH7a9Fy9aI4RxBzCnviKmI1ekn1ErbMJO2IGMaWDFoKwRqMciMl0j47aZxHjCFPCDL2oGiPUZzKiJgj19CUCUK6Nkj96D0b0U/Q50LPZoydqNe50nSeN05fuuwStJBA9uaD3QBqLK1pnKKpxRzh4qNWP8EIlP9SDWvVyGsN7XFS7N93igsZ5EytxP39U3x1xQYyf6ueO3t3odg88pzaaLZjGT7Vro3n96VmptgD08mFGiDAaoxY7epUirL6oNpAuUz2XIrwi2ql1UdTx6JmCUS3Vxx+tXJvG50P3F63MhZ5ZzCcjem0UL71RHw9EszahR5igWh+EbSTNPWoHuDE0SfLTpUNO+dE0UjvHjZYOj6aF12akNU2TAxrrTa+zvbxHM/L2QyOC6L3hR3PLC61VG80QgMa6YfmKsPugXLRasaRELb4SHG0/zygZ+0pa3h4S/LZCeOZgufCYFhGH/WmuUWfp79gX7ddhyqxDTJOYbx2twL3d+NHEeGZ8MC1RV8zFP+MCxQOKPjEuSXzmHyi/EHqFf37OOppv3AfMR+1S9w+cbywzXwAtKQrvctSfh0YF0zg6Ojnis/geoxjfmA+gfxGN1QPdmRTlJnhHiUqU5MRSlKZ/FDHhT+Xtj2bzwBSLzrM/bqe04HJ6N3aMt+0+oqihMLnRlLlL7JmOdL0kHnMZeHyxlvOmTxyPxurO6IClMvF/yH5pO5M7zW8XjF2M9/05pHjqT+8HPVqPLqHvHOqkezC8Fe0G6fNoKiGfv04f1UO0BymZ+dLloDb0mUrI56/jdUHvXqiHGGOg1P41ldDXnrQMRKdHdOMEoLI3PVKbvp0C6BoeXRZTIRrj3oYXBLbPuKocNco2u6fCUVNGeTTKqR5TUU4ZZU96cdQo/zYa5ZS9NhXlvan6nhy1AZSRhPKBlPWEcg2UC3pw1AZR9ibKNalJUD6Equ/OUdNC+Stljhpl3USjXIeyR7tx1Ci7dDXKQ1HujvKV1Dwof0vRh3IhyrVR7kCfDR59T1P3L7U2J1r3i7WCFWGAXtqIc20tK3v05IpGUtwOpdfeHfPBmH4RxCTENwqzF93LF9+9otEUrqU0N0PQO4ll03YGG+ZE6NC4Hdtgm0hbdB4Gpqam0ialQCgcW7JEJ/WK6nkhY6sqdVFSohLRpacoSdiz4fLi/iRXZOE/Dhe1ic3oJAHOuXhMOLs/LW57Eo7dBSYfYGQ9541OK8A5nDWXgjogHrk82zZ2qF0J+Dl2G4LzcMMvZvMv2eQDzvzIQWeXFcMyv/xHL9TywLakL7tPyDsMiYxmE7vb2WDJ9D5d+mvmQr7Gevc9Wulg/Ki6uYP7Z8HUVM2pOlO2gvKWdZyKoXtgekGTaZiaJzgxPW+Wk99a+N85bef/wa5PNDX/AK+t9PyqUy3TvkTzq+TBR6fR/EqbVb+/vyMXlK54FVm//TCUk+/IkRDb/2I/QZvbNm/E9Sk455JHL44KS5R3sGrLc/o4SfJTKMqbcFm7Az9ldTjlZqAtEE5tA3F9WYvdMpSeLrZM7YXS5vnPXpVo+aXL4fw/QS7o5vNHNrY30kT+7p7UIE8ff38eyt08vCnXgnChOlF7bkXAKGrPuVADqJwahMDH34tKdBvqQwT4h0hx5rWa4brn7omAbedYlNyd2zw8Asxtty/E0LSqr4qFry9Qp+GkVHtzsIHNuCvzgObxPYOO78lhmecJ6/w7FlnNiAQJTLttlN+kB0E7mLJ68MIrbvt/BDt6cK45BxeCdeblw5V6rwM/2r1dfl6/HhxXKgr5MSwY6AQPPTZkfB7o2V93fsKMYGA01fanyPASYLpQUT2m2R1ou3mSynfTQPOV+71uyLmBrmWDtXKzDoBUo4WbisYVgvSX62YornKeJKb38jdxWbeuR0rRnbZrxIJuY7KZ+tceRlaz5TKZsrytxvrHCjvBq3TD+sshZUDPdtFhj9St4LXzaKuZlY1A+fKWo83rtoAHmiFyc/JKQJSJ07N5W9YBTqaeQNX8LHjSmq9t/3w1uL/ESif7xjHgNmC93rEjoeBJkVH/qPJjwHnU3KYXwedBn3tgfs0LY4ZexzO/KChY7pWil5zdJ+5MVBFTXzUuW/l5zTGm/G7EkWuOE/JA0cGVjd+a1YH0e90rIg7ngOGj+oROPn4d1OoZLHo6Kx34arTMz+lbBRJWleiuuZ8Cskt33/SZVwUcRxpuSZq6HRi2HBa4xp8BBXsjB2geiwfctZGgQOUUuOb29Vil72qAxbaKwQ4BvsViet1yIgxio/Kl6LUMeObk9PYCUz9zglP2MLnzTPmbMBULM8UzwHjHwx2XVW6AsNO/LnJsOQnuDDuZePnhLdBYJL9g2dd8oG04bm2+0hXwcKz1dMuaQhDDtZt+Qv0y4Dt7Hj17+yhY/i41LlZQA+L7j7iitu0QMLihYMZffwmMfvx2W2jEFeDVZ9Mxk40BDH/NrXomDfz9jBS9cncULqg+vcHU29zba/3lsetMeff+JeZ7eVdBmWaVReG7O0Bdb3DGId5l0GO/jVNryH2Qc7h3VdqmBtCntQeMfXobmP4622FxFTqH0RuB2bbbQMmk4Jb+6FowNmvc/Jsrb4EdmqV5bw5XA8W1Ux7v8rgJfhujNDBf4yZ4MOzYxelOUQx/m/vzDj6dWi1Fb5WdoUHyLy1MfVLx3OHO5DOmnKrlLTTe+gyccBtz/6eHj0CKmkq3Qy+egb3RDc/VeraAtKgZKRpznoOaC9+N3zXuKbjuqa+rc/Q5+CFkn25/pRbgNy1l1pb+L8AoIvu6uU4LCKudYi0X9gIMDk8eoh7XAqJb8/ULXO6Ap6uStc9k/cTwt7Q4YHJj7DUpehc45Jwd+q0Sl5F/JnnfIrEHU17Qkhl/y1yVW+7iOn1N6wvwRePOBQez1bkDiFNB6S9eg+Z7huEb/+jNfT0n6o8xge/AZpdeXj339OM6BxQ6fNFEcK9b3xi6KHkgt8JvFVKqCtyIjSMjHd5qcuujawcO3KTIddS7rU9YPQB3taPUC3xXYv4S3AIbs+bhd2phe3o95yd6zE/U4bbVv8OZMsf8YqRlpKG4zBXp39Fckf5V5E4YaDMmUdOcm5NNQXeuSP9acEX6V52rpT0+s6LIktt14UHFhQf7ckX6dwpXpH8HcVn0LZdN/9YUTP2q9YEZsw5/55c9HxRov9e/64dVPTveHd7ffZuzaUEONNadbdS31+/kzPh+Ood4e0Cxw7CiozU3+VFftl69enYN7OF2RNHd7CKZuX/7o6ETgsDWiGmhhfn5/K0v+za9mPwNdJqmcfvNN2nkzNSS2zmpdoBoal1QYVcBB5oHbVpcMMRCPG+l29RB8RENQHI91Idp0Y0LZmvHGTD0at3YIje4vh9DL//pfIXbE+Sgb9iovf1/yICqRl4Rikf+Sw5xHWSy0GY3GN9yYWb/2XX8nwvNnz+avhoeTY05G3dfQB4avD2mZHUAUFn4nVnq1Gy+c+Tw7lZ758LbKy7f0DoWTzqvXN7QdYAVmueB/r2i89DlASfEmzPxBBPHTAy5YXm3Xoreim7CwhWaHIbeiGUz05ueqDL0Ftv3CI1x+Z1farthjUAjFb4e6573W81NcnSWhv6DZcng8bbqdxrXz/MPHN8M3MxC4YPS3ab1fY+Qy7rc5R+PXAq2ZqTEq+fu5B/2+pr8vuorSJJbtgefWEvuzefvzRtiAQhB5cgKuzPQOa4vNPt+AkOvzyOtn554StPrlJ60ynmCBkOv3LV1O0u6dGPoNdAPCpym+JD/k80a5976yTB0w5K5w9MayPqnZo+eo3tgXdK1rAnrIb/gaG227Use3PNYPiZiSxZZObL4il6EFyg4sD7W6Xk0/+ERraC0Z7bQzTN8HzwSSgLh+rKAq+MAkZKa1fuRAN6cnmqxe6MZQ6+3z0X1d3LS9G6d3ldDbqk6Q6/pcksjOEWOofec9vjCWvdb/AFFPkWbcuJhrMPmdRudqsgw1cDFO/KSgPqbvNuOrYf4QbsrdS/qLIUZT8C0XXa7yYpIg3cN2e7gQOD3bmFTI/ka83XvxAoALL7nvCd3oh/52uTeHZOdoxG94+rDpxTC4uqSktZvezP0cvLetXgerZOi171c4/Rma8X3583i4NXqlW9Icdko0XJXem4d//Gr0GFJnI3w8pANepP7nCPPbB54cOL2rWD2rRsmNWHpfH8zz3nZYS7wlLXy4voZCeSr7Ka9tqWuIPnQlqVpzUF85S7212a1mkGPZuGO3+TcSOtdaws8z5gAgtt00/XCQRgevVSuOFmdofd1Y+Hdw+HS9GboHvimYeRzPnO/pRd3XZX6kqF3+0l1Hql5mk/W+SU8b14JeSrBjwZFnyJfWNXG9H6ZCHyGeI5T9ovj/yfO3/Ge7kwIan3LCydHk8JDSZ5nD7oAg6dL521Y4Mq/dj/lzk47Dry+RkHdUHMhecyidsm2AkO0f8v8+pxOgZvqVl1UdezN6Ic351J/bFokTW97/cZXeWmw5bvfSTb9Fz7cul5Rr4Ts73Oyn89JaTvZNabp9CHfzaRXX7ni75xcpNq/TgjVmnFlHtnj8Zi4kBMGrHZuW/tair+kDP6SmL+Ahb8k5i9g4S+J+QtY+Aswf0/I4i/ev0DG/iXx/gUs+5fE+xew7F8S71/Asn8B3r8WsvYv1g9Ahn4gsX4ALPqBxPoBsOgHEusHwKIfANYPFrL0A9a/QIb+JbH+BSz6l8T6F7DoXxLrX8CifwHWvxay9C++34CM+43E9xtgud9IfL8BlvuNxPcbYLnfAL7fLGTdb9h+ADLsB4DtB8BiP5DYfgAs9gOJ7QfAYj8AbD9YyLIfsH0GZNhnANtngMU+I7F9BljsMxLbZ4DFPgPYPjshyz7D9q9Ahv0rbhew2L8CbP8KWOxfAbZ/BSz2L/yr9i/2LwQy/AsB9i8gi38hwP4FZPEvBNi/ELD4FxD7F5Nk+RfYf4My/DeI/TfI4r9B7L9BFv8NYv8NsvhvEPtvxbL8N+wfQxn+McT+MWTxjyH2jyGLfwyxfwxZ/GOI/eNJsvxjHH+AMuIPEMcfIEv8AeL4A2SJP0Acf4As8QeI4w/FsuIPOL4DZcR3II7vQJb4DsTxHcgS34E4vgNZ4jsQx3cmyYrv4PgZlBE/gzh+BlniZxDHzyBL/Azi+BlkiZ9BHD8rlhU/w/FJKCM+CXF8ErLEJyGOT0KW+CTE8UnIEp+EOD5ZLCs+GXnuvK/poqFccS6qXYHj3OOtCC71OUAhGodzrpdX4a+jkV63t+dssrWYNqabeVNq1kSbwAAF4w33Jx4wo9st3uv5t/QHCx1/X2cxnmc13gcpk9p/djGdsCFmETPQuz39LQZjwho92Yt46xNoy/PwoPLZHkFOLj7B9PMUiefJ1Fd1qL6K1MdUGOdg9Cz+VCBR4nkzehZ/6BIl8bxF4jla4jlG4jlW4jlO4vmI/PvnoxLPCigpi/DR349668xReztWg/6O0Vy//2nvbOBiyv4/fpGV50GoRMMkLVFoCXEmQlGUQlZqppmphpoZM1Nqhdg85znkYWn9skIe1rbrcRnrKc8hpG0JRQg9zNzJU/7nfOdcDYv1+v9f/6fX/z/39XHvfd9zvvd7z/mec8+deyZTFMppCr4sXiJTmaYZMbwJAl5wH1ueRBNTVMesIIkdfv1VNtw+vng6B2m8XCFVTgvUmiYqYT5WI1OPDp8sk2h9FBFKdQwcGG/K4yvWaD0lWnmczF+pilUBM+2bzDB+2KI4UjZYGT+eGcsEQq18WB/eeOnPxMC7LzIbiHykdHGGOTKmhf+OJNCFAe4C3IUSMn/ND9aedO0Fb6xNc4zI22jyGcUoYaaMORtN58lwJBCvVXQuCsc84Q1tLMxZIJ8R8P474d02eUduOrcKZjFFg4/kXaKEiSKxh4+Hw5yc2veLI2CmSi0x+cv5yPnF+cP5wJ2bO6/pPAnvzs2dlzsndx5iRwyzI9Tw7tzkwzDwtnafzJQhKTRmbDy8FVbAbBmOBuFU5vt+8M67Nk8g+Ga+L4ZrMZ2POw9nm7PH2eHy4xjx7h8T018DwSHFH2e+H/7wyUYC/jB+fi5SqUsCnMQfV7snlpdMIosJl0HljlLGvdseLdEqyWYgbiUc9IyNjNVgx0bERoONEbEKqEhPlRpekvmJ1RKoP1m4OlasNqURK2ATn4fYJ3aJTWKL2CE2cL4EYoPkJ3lJHiZQrI1VS8VgY5haDltBUbFqDWXjZVKFjO4ExZq2/JQKAIGxdC3WkrwkH0lP0pE05DjXpA+MfbMZ/TBtcOefRz4daPZeMnuiYQ9yOt9n1PPIF5TvJdzB+tl+NG6VSLugLX1xzRwgPO3Q9WMoLaeXYrq4PuU6wkuf3TiB5rVvutjvQjW1c5Jw7+kHz6DG091a5Ks70PQ5hPvfXH4edWI78eqvsqIc3r9Ux068jJb92fVG05y6lOcSnm5YfAUNP+d6fHGYE+UwjnKbFn4NZZ2Sh4YijueBn7tcryNV719/yLNrTTk85wht2BtoWOuHls/9OH/gPa2737589Gjwn+P2/cj5U0C47pm0AM0Y/FuJvbgH5TDezMluWoikKZerN5Vx6W8TbhGZ9Rc6e2cRm92uDeVFhFv+JbyDrkaEHE1P70r5XcJTZ8qKUGb37dU2Ee0ovwf+T+p8F3k1/HX46tuI8vuEZzYuuou+D9mw2WAcRHkx4cFLV99Di3qWNb1vKaC8hHC78qH30UbL2VHG0zaUP0BQmRX30dV7v8y/fbUV5Q+hnJetLUaZNg4NjW79KC8lPN7gXoKmrMgxuHp7UP6I8OSF10uQ2ipJl5/tTvljKM+ImAeo3r5OMZaDOlH+hPCT2/B5Jq556CFJ7kJ5GeFHpix7iDpl1ilpfa0z5U8hPnNtStFfC4URY7I4+88If23YXIqyU4J+X3asP+XPCcfji0eot+NPLYY1rjPI7Dkxk0l/hDzm7LuXP5GWTxLw8s62j1HJhP4uTp59aPoKiMNFyx8j2+Qtox7n96LpgbuPrvcErVW3Le7YpSFND++1sleonyA25an79JF2ND3wMtXtJ6jf6kPRNf0caHp4bjrSaHgZKhRPblgqp+WcBDwoMasMdQlpV5ko4MpZD+3xXrOn6NKMfdLJCzj/gV8Yr3iKbi5o5TcunisHA+HO1eeeop5LbNyVts40PXA=
*/