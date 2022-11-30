
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
om0GfNnK8wNvuF+YLqD46X6hU9svKC4lZqBkp3guBid4SF81htUnWfLYBNI6B79hGb8Cxn4wHjamp3gcfzAm+I6lgsnwbvh/xwrrOUk5v0+Wb0ca3dELfJaAz1uxRj14O6X391QO49ATWNFAtjDWkq/H+92+nvL9gH4d6BXQP2yhZ+RyhYUx26eALiLkPXX9Hx0kfzvXvcHAdwH/Ux0/sZK0tuE7tZkcpdcK4qXXStJArzuIR7/WtgW+Y+vma7Pz2Chjdh4chRA7sJ4/mpkfie2kuE3zG1tCry1kEcOH1jsvN5msBJMOMBlktM9ORrcJZZHzgeXopWJdipHsR+xtmtI/hKWj8Y+giwddY4zpf+MjVanq/uM53x8OUP3aNwv2adBRQO0G1AHoLXAE5Ae0AVCm7w+NM7AJeXV6M60m+vz0Zn61ronGiwOp6THS9T2Kyrfr8p+mEu26/HwDovLvo/LtuvxQKt+uyf8PDneGdO4uAIBDS8xdf1xVVbZHBbvA5YeiiIqKP1BUUFT89YaUMTFz1MHyB71nZfOs1JpinlhalozGxEfA6GVJPWeGek0ybxR5poalCAqCRA2p1VVJyUjvNtRbggIp953v3mefu/c+52Lzee+Pxz9nc89a37XPOfvXWnvttUhPUS71/4ZcF+SenCSsT1zE+ZXyXuygjOyqUf51ksX7LFHp6yfANgT6dWb6epL1FfveGQafPu+/B7714PvlJMO/0EVSKX0TSRHlwJkmHfTFoO9h0GeyeLBgyUyn+YFokVoRQjjAxnQ626axNho3QXCdiAJmEzAPTVTO++v+d+tufMDMrdhZJE/y/+CtQ+LaquSX/Pl4rOW7aXBPTzT011Rx/X65h7wwT5XW76l8/X5UJeP6eypfv7/Tw2JUXgD5T0H+1QRDf/UT5a/qISumfpL+6sfl36OSMf2h/IIflz/YSv7n47AUoc/P5IvGnr242YibCxLM/gdWw/hGcET4ov8n6P2/nkz5grWn+C+U9rFwHB835oBvLvguTfA2fjo6O3fqb0C54+HLAajtE9rpqrt1N/QQHpVfa7A7TrEG++dTTPHZdqpSdoT9GBj1wEidoK5HQ0mJs1Sx/4Pc5qeRj5xg0f+miPB4r0tBnwD6tvHW+mnmzVL98Ah5nhdjyTM3S+WBNAxAaQAq1oHwWNUnK2kwTx/tuWn/PwlXW6dZC8KqqW4s1luA+O14ut5qMtNhzCgEXQPoksdb2kdzE24bSXn3RcHlKG3cAc9848Ps4I+O5UbBJQCM7K4BNo8T7RdOUX9u1Np/sFf92cn1Z43snmCT/uzUbnD9uUFr/8FW7X8MfLdRi6fHsf7nFO1nTVr/D7qz/UyTfzTIZD9zUfnMfqatyt4Jsur/kL8V8q/GQ/47eJcpq7qs8s1F1Kq/ai/pqHDGsd4ickAwIOoA8bf4zs6rOYl7BQIPOsgrM4ppAu1r9P8GcoleG8l5euUy5p0in60Qttsg6904aFJ3abKmx6v6rum8tQfJ4e0ECTDnA7MWmN+PtTif5jC3R3T4iDje4YPB3wr+v439GedZpBHoRCyWnTaN95mxnv2ipE/cljG40A8KwLEMHHeDQ0xXnZ2JLNJCrFL825FNM1Eb+dzrhSyQYvmUdQJq3n1q2ZbQkFj+1BGox17UY98Yq3gRWLk0j8Y6y1+jeW2MmO8mgkRfL2WPGEv68WISCbleKi8UPgDAbACkjBHib0eQ7340BqUzvJhE/v6jMjCuBv/L4A/V+XNzWxH4I7P5ptbSAsmAuz3bQpubWdCPaWAqAdPZOIt4wQ4aLYQGRM1tFmKL+NL49ftbPXh1DO/qKD7kNI6CXyKQfx8nnp987gA7P0+2kBo3/SXz+xolzlAheOMDMP7FKftpqeCiedO/UHaFVoNpOZhC44T4XyMousY50CvnVHAWgPPLWNk/dbuw35jvNe5020gj/vFIGO+AlBPb7jbnXyVTz/LDP9SdypTsvggAoYFY/8ZafA9WB5ZcfbtQzhPK73mmhtytwu8FRpkt+3Kox2wWe4RJI0X/f1RiOSpxbLSsHxa4o6ecsE4b1KRqihYpy+tNx3nVc+Tb4f8Qg0P0dk38vaNN/g/5O5Rusx7USaDuO7pTf3STPjgDnOngPD9Kzh+b3Ynjh0UiJqcpx7w2A766X/QmwvRzYgRmdch7hsnLXqPpF0Nr5PXKTlDZgzSq+0aZ/QW8hg8O7UxjTgXmbGC2jFT94UI0+eyceFxYjVsKGcz2dN+Pq2GHh+JTnP0S0JlAvpBcTamRj2mph+LWC+mFM3ykbMP0kNyh1Br3nY9srmkiFUNqZC0xazgsAHie6JFKPK/8YDwPPcf+UM8atzn0g9bHa9h2hPY8cybQ57HheQam6ORpAnm6hdel+LU6orGkCdZq8h8x3udDaR35CVgawbIiRl3v5ruji8/hK2ZZHEP592hBNcsESkSIhjIkxuO/MgXj8hdl5W69WGMUxWBSiVThm8IUvkQALQTQ6RGm/nOQOF8qossVnwxm9yzZwCcR3Snx1jCoAOB/a4RFvpBC8Gt6SV4gWyeDH7hpGxheoX4twDW5IsW5I+IY7zd6WPy3IaEJEiaPUOMRkdm0fk6SN3O/rO8sB1dUqMbVZYShTzUSZ1ClnL8jEXRzQXd6uJV+YCPRvzouNwxxwL49FOZXsL893ML/VTgvdcv6fO1BAOwFwIPDf8Z5mlPky8uwkNnJnx5ucVuFaLF7+0VaCCZDbFQPTeyFaE/7ibiG/cGjuh/CxshraCj4EfrPUKH5dQf7XLD/Z7SX8+g4OUr8m5s97t48jHGocL50Nj2a46pTfz/o+V18W1uGQIWG3NHRnfqHkw0PtVCFdAehr0t5BfjyM4DVBKzzw5T84cmF5PCV3TSNQ9X6ItpwD9NrNfmQXreTa/TqIFUvFNHELrufF5xu0F2/HQzzYU8NPmMYj29mI86l0ldT7ZQY3f4LjDlgvHeY3N5zo/B9Fh3ZpXXqjE+14hxaTDmnFacf8XiPbF7/Kf1kywbzhcliYFYD8/pQ8XuR6inlspobC8pmUB4fatKvtXlt8sUqaEm1ZOAv91OF5tmdu+QR4XIUVm9hGsIrQ5X696IjUbMD65EYN48FycsF+jHF5W9VuXMzY6jJv/W1I4iH5+rwLGRk4slv6VamjU0daK1OthB9LEpY0KSiRvmoUcsQSZ+23zFfgx6Jj1UzVZBcSw7lo5psZ2IBrSZfZqiUr+d7LGE8FXfFINgxeml1enSIMT4Z+r2rwyOVlSkW2/CbSQW7aO4MRx4VnMMFm4j7iLKb2MuZPYi3i2moRRpqcXawxXrT+8OXbfM8/MK8zh7+zW3mh68aCDUUYpcLYnkikhIh7yZDqSApVF4Kldf46hE9SBpLvmgIllkGiILnMsHzITi+N/TfKIvnbRZee7PwJuFlRT59E1Vopq/9UVaFLC7ZRFzwpiDcxV775wO4clQ1AF0c1VgeJT7/erfRzJmVdmU5DLbUjPswiskZZDG9lpD55ZYG3KcGCA3/EchxQM6tQfB/rPdEf8xt9JQznXLeD/zbwbU/vR84hR7oKav5QK5G8pbVGAmXmXDof4OM9m0dJk6Pqb4HHKng+PUgPh6TkiXMGbl4iXJu42VQ54B6sAffRrKW0HwRJINeXWTtEsnM0kCeoIB28ogIiI3rCQBsAGDdQK4/1grDQq02LFQb621zRpb/JwU1jBd8KFL7G/nv+kPV7YP2P6Dz+XP64hYaAOGJC6VyYrRAQNQDonCAl0B8Xv7o/LeITcsN9FpHHPTKK60tDKvEH+h7Zp3c/ItlLLP/A2Lp7MiAfvzVhfXDJBIB+28kn88dpHo1W38WpBfR2TA/XfHfqO8LkwDY1kWa5tNGUn2G5bkr068l+rVYvxbq14Izx2S/q5eBG9MX7T9SWN9GpAvLEPSqpaBbCLq2/j8/37B8/gcQeYDY31/1t82KLzf8bSeVM33OfkFZtTkiMNwDYE1/6byXK8X5xA7dHjQtXmRnkKMmlcva8RYghfbD+q+/hf0S8R853tWxZrwzE8tlTXIa8BYC72w/i/3GTvPOdAVvFnj/3M8Yr2wP0PUd8XmAjUOt90vjj4Ncup+NP+fp1WFatdcLv0itEX3v1T44Sd1fExmriaT7PR0Vsr/OUyCJBYl/Pwv/ZMcYJQFMIuhTQX+6r8m/iG4afvcqUkvSxcSZNMGEmMomnJ/C+az2QziGZEBt6cvPezqfqmT6uJ3kflwpiy4HfRnoH+7Lz0OVlCpE20HUBKKpfS3OK1naq1eAJypS4/Hrq5wvNOiFPRqPeUhMdCwQe9bpEkKTQNDICRoEgnovZbt1Grf/7o0tXFR7foQeP9RSmly23fl36fwXhPgO0ISQPqbx4BQzHEq16g+GeDCU9DHHu7Y9qX/fSLLrgLL19k0v2BHB+VIf5r8OhZK8sQ9KCy1upkVoK2QDLc6FKpO+T1BlljFV5o1evJVlA7UQqDEW9clqpKFurJ89Baz1YL0Srp9HTG1U9utjQWMbCP0n3OxPhRg7le0Vbp4aKuczZVC4EoY4amDfHG72V7WBP5Py28z8NP4L+NPAPyfcIl8IKfy20i3Zx5DB0U66BNKfSduocvc/lD0Zg+BUyHRA5pe9ZXuvg6w4U+ruJOM0lli957cIdjzp/GdPjEWDNOAXe9N4mdp4MA/E+YKtzxODhXwyD4Ple8odyTic25PPx5sAngHwqN58PraTLOAnVwvrtmrJTlprBBYnQfsr3UKw1EYyF+K1MbV5XyUdw+n/8/aSXpcv0rH84HBs5VV4TDH957HBPow+VB0JpP9XmFLSVygPAi25oge6VRT0v17G/khTinNJAYu3REq/sfzSffwr5SnsBQClAyiilxrfwgedLHqP0J1uXaXdaVYP/hoTwV4A9tNhVvlcYsrdehyqXfuOykNzF7CeAuufwnR/fASpqixS6E6HYtYarNE9Gya3r3pS/fo52W63E8SxIL4vzGs8pWSXH91OOdNnj9sIJmRhXHsEYCsAdqsny3dg26OcjUoEyVaQnO5pGg8bScyrpdTME0WvdST/wQuyP++tEOwIg/+tnub6Wqe5Yeem7j6px4dMION5cRkZcVL3ocmhj5R/QnjcF54+Io+wGyA8dogmPJI+3z8ST1G0jIsGoNHAXAvM6h6meF13HFg6GWpQ4c+CsRIE+JM9LPSP/xU+vubTwI8aquEH9rCKv5rirAqvYuebHz5HPcLIsWjFAjYKGEuBURVqiifo/HA737+MumY90+A5LwZBWQDGplDBnyyLZL1W7lbTkx8I4p1xN9gqwDY3FOfTncI45rSO597kLRa+tIRfDODQYbD/hQjx+ryub7GKGgKemeA5HKKvb+tJRE4pHfJCc0rlfttsR7MB9Wsh4v53JFlU9wEbQpJITY6uLSwkvx6lF5/ynKguW09mb7FSIjCzvg4BtRAQH8L1852a/pDvcU7emj0nD+c/QdkKyu4hcnyAn6HP11mEwY6wG/4PgE6Ihv9DsEX7dSiHQ/EazwbCiQEsa4O99icHT5zpIsdmtcgK99sA2A6AycHK/oeDRGzbRf2NnI9so+8BxYXbJH9taKGLgeEAxvUgj/1XbCEJoIgfrlF8HmTok7VkyixMaTwaxbwSj4Fg4CymwYfPYpaW4FnMYNB9FnNw6UhuYflUeSLQK8lstvyOXku8uYrAJ2xHADQDVGZmkOg/bR4fHGwTHdP0Q2uuWaxDoMSnAs4+AvZfu6x/ejnET9UwaXMeTbwHYJIAU2Rn851d4Ld3GP3pKL1jxLO33zYqzO74Gnd+8pIT4H1/eH9C1D32zvqryckHn3IlmEvA3N0ut38WT/JiGY8R+TyKzDUl5JJeTNKfnHZTiyE8EOi+MbD/BKrxybXxdUcNQqoiW0ECeaFbGVvpzrYYqo/a8DaBsyyQr9/q7xgP12rk6yQpslWc+jkQ7IDgSwFKf7KaD/uD3Hck9B+ZvHZFWnOOz6ouq2y56HWrtPdyVDJofnMXuhQ4Xwrg+pzzleMf6PHDE0jgp4fd2S+6fl9Fc7PO61rG/qOuzeeXlMmKyetASwdafIAQ3z2U9I41PuJl7eWj7/3bH0plK9BiMBeD+bq/0J5cxNm/WKaMBWU9KI/7KyOc6C9nW+BcZ2t3ywqsqzt0p1Eab64/Xe+7VIePFx3k8S5lbnNPlr5QIXAWAifZXwAGLPnTPf/uLV/ubHKl7jBrbcssDk4sAmQ+IH+0efY7E4TE54lCeYpQjvVSjvfy+0yhnOSWo9TZqaXexqb9I376hirMNvv88OpGa/W736hfdib83UwLjM0O5p+20Y/PSmvBnADm3jZxf0tyenNYOsB5HLgYaJwBOhSgaQAtu0vJz4oX6ovb1bj9zl2C/d2WJI36QlLyq9PZPHFxupTR2VCSCnlhJy8U88JeIx+6aXxwkDens/lmy3RhZ1U6MvGgL759rFbVG90V/eNnZcHo68vfSQiQTgFpZ/d2t2C1qyYh05myuC2imO4Hu6fh/wJyk14Pkmv0mscZcnjT3Wp6WuNF5JOPKFMF2UOvXHf1qMxZCko2jRBgHYT5gW78Ke7rBsNlnPYUF/3k98F7ZSYczUjT+5oerPuWsXaTI5S3CmV4kZE/CqGJNmcwv7JzXbnZ5lRXjCsQ+js/IR9bSUep2ekoyiIORWe5uGeTBft2y5rRYxA3ZYwmrqufGM/e9pESnyURhMtBeNrXu328yZtTLebbti4YXAHxpq/yPskUl+JGXgviehCvNMlbU0eyDpfKXsDbQW8bC/unrzm+k+J0Zw4ohEd8EBAzAXGjm2q/X7unlB8Hvl2ouNYNBt9a8JV2Y+e7Gkjhpd0WYWQwIFz3wbEuUOd1M+ZzspbSN1kM8kdB3wD6ZQZ9k8lBsJGpwOjof9xQagGFeWctoBLjMf51k/b3G0hEdBG13UT9c5Gsr8wETxp4vumq5m+j559wvxr3y437Rv6782UW+e/cbe6SmHF4/q7KeEnzP+J2Bm7/zlLeXtx34P4CjzynJq9xgfPkOV2ecDhQUPAbSdddH8o6w+NASxmvoXXrKuSz0PE2WeCR+R8qG31DgFEGjMNd9HgfOv89Zv4GsT7YakHqp+w1jeSry8flBv1JhwabNAH+b13U9aOO/+3Xd3jenjuV530WoCUADeti1m9gJlsIitAEjeIHH8EfmR4DXc3l0YTlrgXO33xdZg7f1hMIM4GwmyFI36/5tnZ3O+6+5mPMh1EmX9EGxV/fOmPaDoA5ATbTR9R/TOeBLB3tV4J72ESs/32k8Wgf3c/Zd5/nQ3OvgUlgSQHLSe2re/IBEduYUh6mYV6RXowiM3gxnkwuKpUH1O9vaVBbAZXlgVL1N7t5NU92Pd4ujz/vAMkBpGkUSdEV9QPnL4DKdxLsn4o85D+vTlQScs8FeTzISUebhX1/Zorz1HOHEBPHRbJFZtQoBMzLwbxTY5b3Z+xkKchhA9Uw8iiGKPjkTxpvAXjTdMHUzFdsfQ78L6CuBfUMo5o0ntT4Q9SO2TDukGzHTAeDz2Sc/+MM+H4x8Yfc6jnw98YxjPpx5ntZIi4eORK4C4F74LbF+5L1Z7uhPztJ6bUD8o71iXYNKQtIzzAkjV4K
*/