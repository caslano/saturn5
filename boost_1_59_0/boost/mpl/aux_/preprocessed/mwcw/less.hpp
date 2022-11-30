
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
eSo6nIrzVFjPTRzD/MeGeIVxmEYWzGdyHroJ+wJkGkuNfOYX2uhVJ7q1FLUMm68AnUKGHAwGP6IDfh5Ur/kgubsEHZ+e3N3PPuLdzfjAlZzPQNj/zfv95vPCt+ZOkkPgo2sFZq23jh2MBOsjcoN6/1tfaCLJ2eopwg2xUd7K9broBLeVap9gBrcNOZOThCv0uyPxm2oTaMJQ2zbJqG0bJZ/c1v8FgWuv+Qs3zOSio/fy24EKUb7FjWQGX4OgI2wmaoFRFCTUm0iQBEhvs2LR5CadLb6xBCWRGzJMXOc2qUwZy0F7AlG51hcfw6UC2Pe1ASx9fHaSGHMZPNxZbuWPKldw8ZxMWjF9ThFYtxbNSVf81SV1XmMVbincoBXTiQk1pc6a4NCh6cE9Q7LeNNEabKZgkO24/p61JrXnEfhpvPB52ESdMQufBjUxDdML5W2hgsI1Oyiq5Qks8MImykpZqn7ru72aT/0WDDD790cxSyhmhgKy2PmAJRl1HKNylMxC71ZlVKF3m6N6Ed7nYM8cShxBxwktM3gY1pFwyAu2FS64XXFyulBrIK+gtwIpHdA1yduSwHKYRdO7kaZ3DU3vug1pPFvwRppYgiMGbk2ZKOC6D18pt14pt6XJ7QTd3YWKOBO4N55fMjT3Le49xlH4+eq7nVxqh1+t9nDVVmGJVwyJrj2VRJf6YKlKKs0rOMcztCq2pJtixdpZsGPIqlBpVXQlVsXj6Umr4kH4OQiYu+Qc6OspO9ti7uRhanArNbitcz4vMHz/koon9W9nGjXWImLhgoeH9K+V+teW6N/LaUn92ww/O9+VzgdSfqsUGsO7FZF3xEdF13OQxh1oQZDrmLc+EoyhtkTeg9kNmiLB5iSg/blUQxHtdlM9/4QRkOvRqhWAuozV62JyOwEnAN8SY6iv2xMJNqF+U94BG9w8mntoeJpoeJr1UdSHCTiNVNzC692uYfOtAaNg8AQX8MPfOGWIj9RZgqSrzanj6aOrlnAwXFvqY0vnr7MjXCdJOFbhWLqIlZb7uIDEM0KTBHNhG7LtIIAtVq3dQ3gefn5NtpvxPYaN1yULN+GSIO9xBL3HKX2B3AayGyY08Oaip2V7ANlHb5f2LoEOjwhXTZGU67DZhr6Na+ASc5JDc+KmOcnVTW0ghpBOC4WGtvAhbUajMo14xfJDSdzuXOQV23XyHqkyGMUqYhT3rwP+oyqvRlPc4ap8SbmwYu/evRL9iXpdeNifAu6580OojS7qfso3vGtwpMJPeeQ7OJQu6m+OSA9wUH33PRePqHCRsWL3e4JzcAeKeZKAg2odXcvl1+D3FvgN7bmMS0IYL9SEl6Pv6ZIgRQUtew9deqDFubz6YuOVd+ivdBfTOxdQ/ZiaVv3xX1wp/aJfix7QaDoyaTquZI9Tpods+mUTv0YYWkLZhQ364EhqJeHLcb6QpnD8+DxJJM9RJpDDlo6vnS3wte2kI/N9Y4DthdAcE8A2ZwHIxz7bcD7ZMQR/+3z2l928v3TVBDB/iMsTO4MqCkqkhGYB3HABkXgdx/6lVpfhoI+b7IljrmR72v8t/O8ndyfwv/MkZRTMcgIOnM3E9ys/RnV/6liIwdXyWk2w7xeKwIcsEfgwukBjjfwNr5Kvf6MZSXzVPiR5HGV83rMHjaKp8sshM15lZ2vbRCB4pp7oa/J+lxT/VglZ6o7GLWyxtdKljXfPJ68Cp7+Ez8ktiScvqfT51KZPSDVrKBOnv+sS4aZmhHiQY4zrg+Xzu+znxDMCkVwm+cqNGaV7It6WGb3KxMLFbiULqn7/DaQNhwUPbomUH4a7l7DF7pqjynht/B1AIme0hsY0yggdI0HfMjBTuwqFLsUqLizcgsK8klW4hUT5RDC2LVLeQT+gqBOLjgGBvHALuumiC0e76XIXfxgvd8HlcXjZXrgFpQHFynowrx0L9gSQBO7r79Ui5QNPIjPOLt5A0lqTksOdjafiVXTfDVcdBk695qQyScAjlnD9fKv6f6bBqY9uv8LNu2ewVu5Rs1ZuO5Cgzu8SMEKHxDO6h6va4VsDfeuSQjeFq1QpNBde5eJBACVcM9uqDlwLbzpJE9DDw6t4nR3PHNSS4wVm41uaJV3XX94zHDs01EXwkKFKhRZM0FXzreoKjO9+gqIe7vWJGLqjh2E782s/Gvqm2r/nTc7Em8bDm+J2/R330TtQmbPyq5X3jmOv7VJt162817Yr7oQL940CXq0xDbcgBlKCTKJP3nicOVOuNu1Ur1bPRZpUsdymfHj2FPp10+JvLFYuCas3KFlXx0ZiZG8ELtavW78eSHn9dSueleIZ9fk/YpRNzkea9mCWSdOOGbCKDX/V+rfxrMrGBH1ILn+DP0WaNvj56NsukSRtPp151VRa1AC/lbddkklTH81C64NtVsRrW6URdPpyIK8Vhw4dkira2tqkimPHjkkVJ06ckEyTwjE2i20EsDmjF02sNiTKe3Irent7pYqTJ09KFV9++aVUMTAwMOyDP3JiWEKuaWjRdT2sFWETnBW/O9InVbzyyddSxbufD0A7Tn6dqMku1gWHi1HrT0ATgngdm6B+AcW7+89IFV98BX++/PqMZMIHTXrwQ0fqJqQ5ag5xQJWKwPJNUsXta34lVfw0+oRUUbH2P4bt0MNoyaGhZqVWbMkPl/1C8uFBWotaaBqjigf+1CJVPLzzHanid41H4Nuffi/xcOjZERtUB/OA9QbtpnoLyUKkj/CGN+JSxe+PnJAqdnec5H/OVcGm470pujlYP1datny2rp0r1LVzkzkYFKvCdLcm7hI77uYpFNV+WE3hPU7OJMDxK/RP54nn/8B/8lPYxF8Y7Vmot2eu3p6Z0BKxUDNeLZI49wPtG7Zxt36jxm1Jbtx5jRdFI1a5zU1KSjmp7v/KaJKbuM6g25dI1Hy2PAU/E81xD5Y3Phlr0B9/yTDpBhAiUP1D0ecaYt0MRDdiXAtPQRAJ2hrTKVRmtvVFglz1DjSmd+ih8RsJZN9UBmNa+P2XrRygNbpxydAyGUYdI6Iblw29P9K4b4tyLUvy/VHG/dFR0o8Nuj/GuG+Pbtw09P5Y435mdOO2ofcdxn1ndGPt0PvjjPtZ0Y0NQ+9fYNzPjm5sGXp/fGO6gBeYEN3YMfT+ROO+K7qxa+j9SUb9F0bWIdhnhOfh4rnF1iHkcGTBssi6w/TzNBVooe+ohiMgl8gWDPKJEA8T2bKNMJu301/yOFyDTFPjGmQj7PQNnbMyqOweut9Ef0mBuvhBtX3x55g44cgWzUijYFZD84PRKqXIh6z+bbOmnZRtacqoUnXmTheFIu9bPKS0vp6v6nnEWM9DVnMFgi2o02JUC7CS4pwEvnFMJdpMOqFpGJuhtzEV2TP+hV+0U+y5I/wiQWeFRtCB/1pBjJfsvOhBTTOVr3f9/jFzPlZoL8/6fjIcu81He+z+o8RO81fx+MqZyGyERnFIc2gEKsWjBDzT4/ep2//aq70vq0diQBUovQElL3g/owhe9b58mrIYtI2dDr/i6a37j7z2fhzuv4eXM9q8PfGM91vfl3swIcHrRkKCnFz1rQ+wGa6h8WBq66cI7wAt7YeZwNYXDcr3aQ/XcyzHUXq0yUU6QNDQxOGZQLoCvOef/0HTBiXoFP5VG9adI97RyPxjQyJ93LHuFXPmn1pz5p/f6P4x5TkofLtBPq456qh+xTDa6DnMyQ9vKmK/Y1749jTDyUGZTbGPUnevzmSVJvxJXvck+Wd89VlvynhFEKJ5ctrRr7tSAmWSRZ8DniDgR+CseWunrtZSR0Web353PXHIAfOwxczD9hwNW7bEns1GXeqLLkxZfxmBVmayZ2+la4vgb9zNnl1Ev/BaPItK2NmzN9M1X7oONtulxrp6E1nK7GwcT4dcVnoWQNku9emvejXSOWD/000D/UhX71BzVLaIOKVEPojfwg/CK57tTlU2OR/RZH2p/i/9dL6ErboL2z/2dno/Bnx5bQG1uMklle92SuWd65Z2a0PlbUreC0Sstu0rzafGGvRwoKvD9Zx45Ir9EjrLNsknABbnMLmi6ZS3lSEHf9VzGh3yOdI/sn/QELZ8hf72e/We3wljZ5ERm9kTcnIX/33Cxb9S8zRRPLfleCACrHUom++eEpyU948lpngt5Wddv5Ln7jV8zX5xcdJ+eeMYenrncBnEN7wdOXxvt3auZH8GPeKzvhIeCcesSVpjEf/EwoiJjVl72E48Kn2q5ShO1gUv65M1unEN3kik1Bt2FkpwFup+rWkRqkpHGjHrp2veUrLYrAo8chgFarVQeCfFxNfO2yEl5SNFEIZEvmUenZfNc0CKLOt2n7pnL67BbJ4vGrhUN/TKyZ2OcDT7mTfXgBjGgMdACXnCRkPdWjLKjaPmCTM9eIRA3rgHxBpJ94AILS8kjWLo3sK1GMin/JRdz9YWiUrYYzYKpThIGEeh0dxnCsYpjWcUQawNJw+aj4xJxtQhxUUog3BWcNKNJ3LwCXKHAy57NI1pbsI/7Vz+duy4vrGW60s7pC/tJTo5ukZNrNV1G9LJqpouSZwqnYUEY/pWWJBZp3rN69ii9g7xyztL/nG+dHDl/OJP3SkeHIT/fb79dayrNxP0p80EfYuUIMVTP+1NWIJzRJ+B5qzbSuOwmeCphh0BaHz8KrZmGwEhbk+XdNo4DJARvrDji6TR+ssnQ0eLq+3P9lIxYupyLcXDg/0PVu1CSz95eB16RcTx8gBqOftK2SVCeimJ/S/x3QRkTDqPldQUOkbwdUt3u3jwsJ00JD/SC4v4390i/vcV3TMhRxpCj4DZCi/7PqqHfXklbJGbq2SX5bKi/FW7UBRAZXAQg+jVb1Nb+yKyLWp1IOU9/aZWViIa2rUL391DdP89/E6pztXPG1wJVD5oOe76QILN2n4Axutvhn8Lk/OBWEzGY2oKEkBvHkKtIblww+YMuEwzmSKxIddY+PzC7jiTHNtQTC7DWtwCGD3loYUgsySd0sD9+mkR3Dh5KP/3d6z3mHm9P2de778zrXe5w7TenWK9h2C9u2m95/D1joPmSq0YwPVOvMw64msQuB26Zqx33X5mrPc+1DERUJNp1X/4ce8gEUhg/qJXYZ5RWT5VNpnk+WwCAkv1IoGKTNMRoBF1Pz90X+RLqeSlv2N83zaP7z7z+L5oGt+/fWRi7XLYrDw46m4I119H7M61ONzqR/n9mhi9jTiSvnMQmCn01A56yiVoDFuTLZ48C6m5/3gSqan86BuQmgP/2T0sqTGPZ6ZpPLOHy8+gGoM6YB7Uz82D+pEpOcOGv5oOKIUGbtn5HVDteEAt7UHOitg4ikFBYtLqORXutkStL1hiFEny5leeVrYv3JgOvyJVPUhsGuWu0ZTOi5heRCm1BcrKinzROWk+9T6iTip7mPhi/aavRF0MNywfaN6u0D5T+ofu9lTC0Hkdi5a93Skfbf6G6zlqHvqViaEP3aev5Unt/+iwE1/wJUiJ3IcfuRibaSW2f/gNVmLBnSlX4j8iL+ewchKZ70wzDcXtaaZVWEK8pnu+oxpdSuADPdVIBh74IEFIRXKtf9OTay19kpYMJXGD3coH7BybtRnEZcrMJqxXh9RjL7nMNPPpD4a1qYDMvIbo97ocTh/O640//CyJPNwI9ce/J2zj8ZE+bjI3oV2cC8ruBXx5aamAssuH1g/fXC8qb0v0NeQbXr6//NAw8j2bZa3M8Km/7dW01xLrf5mZ/jhTkh8d+Ffz2jn0bwdC//5qCiKd25nT0o/gZ3yRRG+emB4JZqcWC/ke+aLNtEdo9CkHH02AdO498k48aQ4a21KK8kkDz3O0JfbDt/9LS/XMeed7r8KszzAsc12ci3ELCbRk+Elpb+hODeVcegcq5iqOZNIIZPh4mnaNGKTfFspu5SeUpT12NDFoAjIaVUiqunZSn5YMkpYMoqOq/zIpKVv7xqO9w4FKG/vo1392DdJv8UopCAfur/6z6yx2yhT5ovP05XCpvhwmoInea2+UOjo6pMa0559/XuJyrY1HMnntkXQu0EXGCRFXN4aw48un6fV9R6/vckJE094qVrKLldHFofH1a1b/Xvrv2q43pqkrihcQLMkzPieLbw4nH1jEwRKdOHHRDdQS5oC01LYzofhnZjrUhWXUSdA5rKLdWxGcw+2DcTMmaAQkbHO6bAQDEWcUwRktKg4zjJfBHAvGoFt8u+fcd19fSwFx2xfofa8978+999zfOfec88trOtmwdyP8W1j8J/0nt+b1RL6jOl7cp8AeNRSKdGJQzBGdP81MdtO334R30MTwbqx7s2Cwu6Lcm0UDhSX0r7fkB1YwEDMRIDJ4UlBITHCguKcAR55yiefrSAadvU7lq+KHWOpTT6gaAVxG/6X9+l6Hbg4iQqqMGcM6lUMC5uDijie0X5e2KSPbr7oXAmORRH/LXBe69TtDr7+k0PhJW8EH9St4rx483dQhUqvvX63iyXfQLeU+yUqd5iLORiAFNQhvIOUikJ+d9Y6brrIvtj/IN3i2dnk3/+1uDPdaqB0qepxEfg4KA+JSZHSfhgggXD8IYPfFa3LQfzL380A74burAyHruKrRacIoBZlbyabzyjDOMnU+MLcS/YHrKZ2v6UvIHC6czDpMDfQ4R5Z/LRmC4u1HXW843IDswDiWJVF2U99v7fp+a2ZsAztgYwnTIyuvaJ0XmFchZyUxWlh5V5vamyNZnGpnrr09oJS0+FjRaHK6RkKX3qAaRNgNb2xvPVjWsTyIcGs9s+o/qwlKr4C7k64MDJtQQe8EMypGYJLn+RQVF5THyqcAJVsOr0jevoE+wkIoUeKKkkuIQWOZD6WvQcXauPbI5NpjsXsrcGpBuKCjkMrdF4Vhh+XlyGvKZE8ArPBJlMq5BZllxHRbYaRDSMnF6qDajGZ0iHzxNmbPCH59aCRzb8POzjjUd3IYBFt8BAJzlDbyyqFflKD9IyM6Yl+V98NdmOGSu3YzuvK2FUGbfo+Ldx48roPAZcQRF39ZG3Fs120Pukhtoh9ThqIfUjFl1K/6AbbyWIj8ndl1AQktsXVsgCUfC0C7P/4cAglJw3ug9S6Vi2TbeSXUr0PtT9D3XQq2OCPppL99/7gKF7JEXqL6xDKGbBmpRM7xodF8vD+OjK6//R0SEa7rkPt6s6OHEQQlmoTnIRarKDLDffZRKrK6FkaEOWPokydmiSW32MnX3T89SoPjEM4R5hTCnCLtym6y/JJf8+9HbJol5L8IE3IdbKuG1PndMCHraC/OdAoznaJ3VyPzaJN9R9W3L1gWeUxxjPCxlbxVK+n5A7JruU8wVYu7Sq0NqBOYSJslLWfVIbLwqMQZBlJ5IOvE2gC348Mafok0C79sX42kp2G4ik2gDoYqOAJ6C+WmRJPYrvhL3lINLGLVW8hrFXjVF4+pz/1HRPtf1sQWM9TFpNL2oLQ+77L5YVaQXlTDKhq6ZgBYzuqjklvg6TDMebX65SXTw/DxMqENLFutZNUR3ZDuJr+1DYdVVYKB0fkF5q0JDbz1/l7BwYvc3KrS9HuM5uKtr1b1u4i3e6BajYKTMEgcU872VGszFIPEi6rZ2wWqRGBKoYc28EOSZSlItVezWfxulZbIHQSiQb9RaHkjAoOeRQ1b
*/