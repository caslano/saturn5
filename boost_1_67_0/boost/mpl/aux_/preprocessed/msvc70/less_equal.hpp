
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
luLAzwg/ToCZ4676pj/qSP+IWi/EO6+Qdit/RgsqhOd6h3e4EBwqiWu+hoSlpe6KRyaw6vzN4taSUYtOI9HgEzC1588M11ryn3ynyAV2hVm/cTVJz5WIgAbd3chArpAX6Qag8LV3Mg3ubhbRh/BUYEAf6aFM6ikh2RmGqLeAX901uhjtrcTzZ/ljEvnjxCb39U/2mMw09AQZrt+ey/sNunRP/+q+mwuUZiTXk0nGGMdVib7dR6QMSwI0ExYfMnrwagUaBupDFLfZg+iNf9B+k4yhpnlvyk3c22+VtFvE1VHYk/Zp4l2RSFHJleJHueRbsnD6WDkUtYMoK+Or1MN8uJSE1MqMMZufyB1sGiCG1tMWQm/MbTqm1ECtj6g6LHY0cwcZTUqMt0Loz+W5c+uC4+chyyjxaj6ZQYY5NEG/CFy/dv8m0Fd7sU/FTsmWZ5tAlBXrYwQv/X0MnahdDEIaD24uIZon4g65/qhaVBVen5e/XudacDsryOaU2HmJZfGD5APPhXAssYz3pdifiaaQicAFvY+avhuPo7TH5bfL3+OHQM3yThsUVhMKhw6zOExdBc+akDnF7SjaBPHWi8t3ta+BCcl3CT9d8261G8YnznPkFVjlfZ6/ozkgK4fKCywymWl9ZHZPtIV3QJU31KSWt9vpVMOyFm+lc2W2+OgKaEotTgyQCTuXCMgPG+fC34BncILHVjHM5fUXvD0tKQXloozTHKzNhoV8JbzS1/CXp0iiPyBJ/AAUFJhwhYSR/Tz3U//svvvhGeGKq1fwFhdiRAv4UPwtiDZCjvqtJsGC5UrylssA+UDf1TB5muwWTjQiuOkgQJvNaTfwo0/KplXNgnOA9K3uRcgBhRwNn9Q7Qzr23TV11yiRDgW2vhQZT/Qa30ShSSjcc+LmMC4iR6a/ZM1vf/0/+hc+TLpfhaWIgfSSoyRHr+gCcr56PL6Uzxmh1BBPE07d2B6PMaVbXPkoV2/EK/KDT9EgnFs6A8YDhH0w6mYLFcWTfkRWy21AXCdaLq75p+i6tPtgO4Jng8ayffMPm7l/zN+2JL+Otdzi272+RSlSTe1Cacun5gHhr33mfApW1MQq8tVN4HfpKu2JZheRQgJRzlxjTHZO89nJfVaf16J6qD8Hh61LoXC2h3VKvI2+uy/1SnenRWuAE2ljIUTMHJsoqNL+4/KZSDQzmPgAuV/ydeCBU64fgN/7/VZw340iv50nw/4bA0kLwVrvrSvN+c2ByLzW6HakPxLo7sDwzUFa9PNIL3JtdcYBIoGk5Mcx174+9/mwzgF/oT8/f9+QNKZFOMoffQmqGCEnQtV4t2Kpr5/D2FousW0JqflMCFEzJ2GWchz7JCdsgyCIbDad9A9fPtp6pjtjgKebsor8WCy7McSP6IXn7AzjVdkPfhtRcbgLY6yu7tL2JPC5jCacIYCy6YPmq0/GIoLqpZO4txgZGriH7ky6LuhQhKrLDixEkxNlxl5belSqkCvqv46c0RP5gCBPyZB0HmoL0f3qYZiaKw54Tho58GutlbgrX564JTyo8L4l15UpayasN6gRPy+X+m7pcHfo61R5B4xeFUuUcwbQ59aVluZf1mcNs/yiT9KaA9NPChoMJ6WNquc/1PZ7RB5EZojBgUvv8dKVfOs6hGBXcrCG6OrWCYj9Sb3ukCp7BJjkl4lO3H6sN3b+dinepq1hRzUhMiZWddsp99hHH1P079hYElBuscpm2mLCu4caE2DDmj3ShSoQ0cP+B/eAOUYr5U+O7GN/C2q6VNn2xO3xbACkyABavhxk01Q6FSnkbpxKn+DAcmk2iaAK3lay1HuN0yoS8h8flSUIt33+WtJH/e99J9Jwkgra0o+KJcdQ2x4W1F6EixE0pUQXjItglh4JAg5iBRMV+wcxopeeSJF0Fcv3Fc9RWKuj9uKsb1twVRE8O6dqIqWeP1iiHwTz12ucDWru8JsCBO5hN/gb5bSno+a+Ebp4Om/kskY0qH1N6iVKQ0SWbJBupTLP4yi8Mss00CX5b1PcpwU6c/TNpTHz3el+TOlUNxPmskr/xUJnRRn/zuPj/V61mPntnmzZH3+JwHymKuGm5nffjvQABA43JAv+ouh57TN+QcXHpclxr7++6VnOgVA/1jx0E2FttsT5p3QbzwVVvI6fTHreWwlB8sFBOwu/SjEOnfJf5bON6VU+kICFMfyQunpYCBNlqibbwpnBT4hfZK5534nwLK34EdEyXN7TuhK+yDQBeW0jQIkorn2ChPnNIfF4ZVL5heG5c/Fufm6xBj988PqjVH1RtM2qrfUjVq13uO+C8PWCetfden51d8AFvMj8Ckn9R+7x4YVOoJ87bjiQ8srfdXY4jmWo7KdCHS6BZGoPdXnoegTtNxsVu1HsJwM8gmDQtb/i+2Ff3wpwtNxzlaWQO7RTK1fMgpbv52z3C0MVkkrDJolmI4L+qrfmmE/iEooq4eXxlpT/eppG9tV0jr3UDKUpeSWmKZgPWE0oLpOiJkteefkiH0Mdx7ltTanM09osm6mHpctm8UgdrBvOal80kJvKITQfa28p0KOo3Y9y7W9MRYm7/uoUenQ3X7Ku4uf9wh3ZiaqjU/81tIQmJB4NeJdLPzX6ZTJ7Zn0SCxC27UbKkR1Dffetiu1vWmxwrPegPVILTic0SOb7rygw1Pr7bxIW7iakts9Rz8ohyDsvQUMZAOevD7nbHnS6J+e5/ygyQcv3LRPruDXV6fYH7xkt/cf94+PgKnRHQtwVxavFD3mD7YSbEISlLByCz8VyEecBKoLMaWm+FmZwG5CeTXQGO0R/yF0VROz+lOX+JQ2SfAQdH36cQFvxkxo5TnCd0nHPie9oiebGsj9QklnnTsm03/QPMfh1mGShwpm2QxPF/u28kOCnrWgLXMQYMS/609q65ynar3iyp9Zdrv4RDJwhop/T5GzRdX2M56vidFoHakSH/hY07OSM18R9NJXK7WY1vYbu2v9yZ116sdVUCN81IdfuAOViEJM54YpF5DBWEWi38CbxzZ8R7H+ZYj3JBouJQIXMoHfa3eMj0MXiGLiM6CdjPT8ofRWI8i0zJ4h6d9/vrIDGXz7+q53kN/TifwTugaqiZ8ciYKNJcE2kpnXujJ+/EYl7zPvJ/lp6EvWkpSPL/ofcl7gB+5D5w9C4/DZsx19KPp/uXPqkE1u+MMmaFkLwi/yPtlJUo3ut4PBHEIWPUP+hbhI4C4lb4WmeKxzc/il8mXkNqnl1e0e5IVYJcjJlFRDsP153EtI7ZqboHKmgswSlf0uHN/9ulz2NOy4D718dMv36rCG4f1wYyMZKiXgdCOV4MW739AG0f/z2kAuC4OuEJqdQGs99YtYHqx4FGUCf13WkLnWWe9hWq3znnMJnfQoiiAZm2T+5iZL/TVn62P2Lqo7McHCdNf587Kjl6hMmuOZdtlwb2thpC20ZS1w/U3mVXfO9XsJoj1PDt1lhiXj0CuEeGmvVj6VmyB4+uqG4jWOyEknISh+4m0x9lb48eYVnxBwBCAsWJVRlvkIoRev0JcI5//dPL7P9DDSX1kdyJZClNLm57gRp/2acJkdlfV7ZIY9fLbO2JUDERCxEo4krSP9S4gO/UIfH2BmzrsaCz82s5KZkUnJaVy5sIUXPzfVlKLHKzGgV6FTdJbFz4qcMPL7LmXkewDJe1ptpYJvR89vixbRTWDHG4FvcFJ9yUOfadjt7Fu9/WNmEm3Ioa4vlbqk74p0zsBkRXlJKdQzwyXHhuHKymySkJsrv4qzFHHmSK5YiehdRlnXf7tKuJFhoHND+cFibrUn+Pbud/CqA7z6S4+L98gRgoEU6EOU+N5LIyu6UwxIEad8keX6yO80smGn8errbUidzQPSTx104Bz5r9JDKciK1fVfw2OHiprZZ5oD+4vSTCg12Uq5bl4UK5rAqtrnoWY1fTaoIJEOk4I33tkcb2hbQT0WppD15Z1eO5uM+V3wi3D4d2GKX20tiIzSQ6hzTRVTkoFEacJT43anf49zj8s22RSXBMtpa/8EdzWXPWUlfkWgF+wLnru5LsoZQtlyL4vES8ifKoPaHpX/SU4Nd8wp+voUOqLvpDFXrORyNTcSPB2axF3FZCJWX5eNSm6wu8l58zzqNGxtJcT7euHqlMXqn0if1JiodQusLX3Meq9Zxw7v5kMD0ReEiNHVMbf8+vcyKtvGsl1oCP5TaekFxmlSU/IxqlkR5Lj+Uere02s30NJba4pWZCSOfF5PSNMToDWCn1XwjPCK8ArUahxoHHWjcxdTpe7pLnDlXydJwxL1V9AwC7IZs5hmJiks5QgTci9vd2jHa0WO8HkLB+j6h1jbrZTNlgtnTMzO1Rl2+D+fRICn0RaceXwjWYJ8P/AOJmSk2Wq/gPtC49odklcEt+q3TTyZk5L5u6di3TGSeT0GyYGonFAGkA8rFUUDPEKUQ7WF8Tvwt1Cfb8e2hs+RA6GnEYM/LlfDbYwxU6l2ZJ7nkimNnCXelp5eT7gmNre5l91xTbqVo01Fmi/HVWsK6VoftW5wwi0smRQcOayAaUI3g/KZw+i0nZqeQL6XGf2g7161O6CBiPV6vkgYx18M6yLvYdEeHpKpvfi16I6Ikd16NsrvueFvi224nuFFH72VuX9i3X0dZuMs5/nUOJUU+yGh+84ZYgKbJHdFntikAnDIp4S/Xs6TkMU2dVWbCLhBxEyMpszcmYKBAOSWUAm3MyVK5bUt0y6UlGZqoN86SH57LynrOxBcNPxZpBv/qH74VFcO7p57hvzK8Wxb+EndcXeuvFwdmFFu4X7A58Mkwvuuo1/oxc83Mnqo/SjQhpKjvbjTGfYecgtWeJBB3N08g+GXkLmExDTWB82fllNkuxtHl27fTv6MTJCBrZfNDiXgxF83n6fHSAHeqBGG5t7yOIBVXujszB0VK5smSFLv9OVD8q9IaRzr7CfRBKUxplxRj0gI9t38iTsmkSGXXOEvYTy5SafdQYRop8S5Vnxa0zXcqUYDXfe/7xmkxgCfqBWFATFGume4peo4A4a49hfo9SVlIfqSfGRCRdTokflh5oGsIc7oMBOqGDRWKnFFqe1ct1+D6fHvbaMCjKEzhK3gRtQFHl4Op/1xeJi9FW3MvrMcjd7UwJd+/s3+oHYlKxhqzP3/EoxHQSF93PGV5ATEqlTmjkPpSvfoVr9nzXo6w9jAgzzS8A4ygaLQm0W5vXmpQ+P6U4hOsLmTDWGtkpxw68v+w8bfcTnE/jQPa5lfDnK7LQnO0yXO4ZVElDGIkNzSc7v9KiJKwMfRr3m9TM0qnPl7ssVbFgr0hFnT5YmjTGTW0nvaRWLuhk0DqYTR5oFMSxCw/T9K84zxROZ5lsPxyUWQ3vqejO/ts/GY9Zsey/5T5bea4bpSn4zzJglXh7VEWLqzWzK1wki/5/Hz1r1SlE5P+ChfU2Orcehal2R16C8Dv/jlmaXNlGU7qwpci6vgY5uZe/PHQEvdF+8S6KLMctDZVQ668rIY6yGVppCEKyBvjs37Qn+FF+cadp3X+XXdjCst6WU+7HlhKOj7gw3Kzh8uX/EuHR2j5n6Pr6pE1VKYzKvudfpCWjxut30SQVtjtgWszN/DB5JbthxV2ToVqoP/P2LF3VaqC05YfMvvPE0UjtWKZm3oU91n/3DKnBD93CkOfauXX1btVMM+bmdv0rmwDLa2+Fv95JAFw+tVTxgJ6Z9yv9HJ9nfbq/Jo3NSEvgj2uTrNKtGbMwH++xsW3o6Sd+uJrHoe3nhQujixzfQiO1g9xcQWeN/VTgL18Vz4x3Hs+qTng7geFaW2mie2jOaeSD+B9ciNXwELKeFGXMPBMU0rgX3ztk/dHirZHt4HBGWb8c/icueouykvv3FrZ5+eS2wGJwKN0T3lLSZyZjfX0rEoR4YPM4+TJV7EdiCmJzyFi4GEfB62GzmBEs+KnerybUdwgtS8gAhfJQgv5EvWi1I2WvzMOHKpqOYxH1V6ryZOnQxXChX8XyvLlLdU5cSrt89ywWY6Iy+P31dBrTuhRo7xDrYddpGzbjAN60x6j1JJ/Ul4znhvTjN+UXf4dedbv8SjT7PY3Zj3eANsKXa6OTFCKRYxMe7VdgJ79WrOGRbeGliD/Qo5jX+PK/DFWXjB0XluiVYju0HW+yNxgTiykJecwr2JvGTsy1LauRbHR/46zN1PQCZS9f2R7XHbMjtv2iwj7vatXlzv25um7utzzQHucZUpXOrM6oJiNHV+/5BL5VzSuIW/yRv5IIfdfs3fB42DA+KeXGo0vpP7TgUZ3Bf2e2eZpfiw6fw8xeA/nbWgbwIzNmoqEtMZ1B+dBnwpfSR2yAiaWj7NVn8wAdR8CAcwAi9QvusbnNkcZkKR5lwPi5cufaAWigAZ2iFEVg8N0vQEnOaOVruZC4IHoHWLSgvyNwOPS2/vb1iBzXdpi+REBCxYTi8j6H4sqFx3L8QmlCz68nT+4vhiJzqxH2XgCZi7C/xIcG5i4klz5JV42Nn8GD0Xbdt2Nr9lwsmK1FpUIBUTq5jiIF4P97c+tcBJAyJTntKmxOAFVfud247Q9ExmQ+gzjdYtHzVpx1+qeSVOcbA1firZJ9MHrVud0Ts4sUp1/oa3NB+jlJoSxrKNkRn0Hl2Tq+ctB5sgN7HZSxYVMq0HWmS6gdr+trisjr9qOla3znp2K1zXnS4N26nbBXaFiseudDZnAdPeC5zjKEyyS5JvBPsHdc5xFbI2AnvVnTz/rizp4+owZICI4FxTH5N30lJRe2jm1gpJ0PFZol+YnWAd6zX0rep4PnO0JKlBS3cguqk1TQGT8U2CDSav6hfZPmKVqlL/XodbJFI7+6LuLvPsVFleesZKGBD86uoRTSgJXCUdvjkzFn2vmF0i/6sfedV6Tvl+BJIZNOsfGuo1pcaZu9q0teWeYKwyQj8bXmCeKwt0EtxHvibaFT/7eR9peuBuLvFdOBkoLU3KgHKpT9+eU/Db+Qe3UYI8uvfk1NLYf/zQYx96pJamz4eMomh9Wb3RjDR3Vex9Nc7XrrlHEg+ZKQ2OdSntdQNglBPySwW4x9qKep2echvNsPF2gbvJEqyAi9OG5LdNKZ2XlWT+1qhaoS4PfrH5u982Xa14w0Zj6OsrZDMNnvME5d54hhSwZmy/MtzftE2BX8BPr9EeujRz+fgJ2cCFuUsUvzfAvSiCqeIAawXXjVHFSQoqRlF+vMdok6+xw3vtkBI1zg1sEQrRuyh87CEa7TojEDEiiVK/Ut27DdH9Iva1k/lTS7v3a8ftA6S3hzHwA3/KP3MDko/gRiqhJDw4bA5LRib8O69K+maKtwZ8pTg6Hs8XGxTJNGVPfjK4IWtqwX9XIRbn3LKcbx+O8nSbl5KKObFSvXDN/FHCEViwTtp3Q0j9cbVE8en59/n2MgvHhkfriEm5DsCDgPRvmzynZYyRq8jyZVkdRz9GH/IpNCNy6GlwbqmsDHZ+YtwLF5gcQwjN/X/4gwpc+7VfJMi60qxx9Q8ABnv4Znq5kwfzUsyaC8s+kHf5VxM1e5Kj4nFzwqx99BrufRAzYITb6LBRn6V3Qd3r/VuWnQsFdM4/+PWorpLVZ4Dwj9m/QSXecb5sekc3ufBY05eb3sYTwvoj0Fx+u31H25vY2ySD5xkpG63/3KnQdwuxPH4rTCuhD6keua/JXVani5BLpd1bePq5MDiLJ6Pl+UwzqomFVyv2TmlHUXOjttPP5y9jNn8+X2fK+imm8AjNKaU7mjT8033V5J2Xi08ir7FNlxrVxYNfd/yUnv9anUpCU9Y+rRP0b+h3xhks5rq9cNj04AUubnoplj16+OsVSLTxZLMq9XynRSmfqa+e3xXnqOyWpaezJvv44TOL6sVwCm2IiINd7ALxDe5UOQ5Hv89HIadkPhj2PYnHi9i5lg1raw9lE7Y0isb2f2Y3IPwLK1Jrb8jfkTx0j7PlWMbB/Se6Y7SArD4IRHN/xI46LC7Qi1MDLT1MHvUfSC17OQ0SD3wqGD/2JxgGHiUgjgfkXbbIXXV1c8C/y0c8wKoxWcezvGLw//f/hXsAD4XH4MeNCZnoZr72cCbJQRa9JW+Hf7AUW33MjF2wXZ8ceILN+cES8z+M6waZA3M0TI0IKj+Y2IfuLtCfxRRYZ+5rM+ZeUCTHDt272gSnk877zPDyH5/DZn1698KpIcXCU7vQ7OUjG0a07ZK1wTL1aqu8OANvl7C9hUt203NgQmZ0GVf6wvhXSq9y8ACRHytaunYY9K2HTeymnGNTI262SLnOj5sV0F0be6EDbrK7j+28RRIq8k40uRN81JbVFesPDTOJIo+ow7gdizIPe2a060xDv9MzZ0BPv+sJLlQse52oZUrv3JbT91FmYQ9Oy+lmD94X+1gVnZd6mnem1RGjeoVzO12/dPXMgNVVer3W95uOqhf+4bHEvR5+s5Q78cCSaWCwEG72HTJwtFDUqjHac09LWQH7cWt/fX+8smBhbRq/izaA/3N/2hH5bTOJAiuT1s9nD2yYt3jlq/1GpXXwuW5Jb2cjBRnzudsIKmVj3zfJGHCWoUns+V4H6FYk5fb7qANFTyGAnw5KW74B7Tj7cnRlZRfOmFxgwLiFaxOMk3S48qF81jsQ9w3S80m+o/WX6F0QymZP01LGGakX54Pwb5BerNlOsTFdglnTfVCJBIA4DkvJOdAilt8L7FUzC51m1A59JpmMHgXhJxxipXG9pLNTa/qwHPW4BgHgbsvaacsmxiZg9ExjzcaTiRv7nKcmtftmRxcoy0i6f5BGBS5xkRCeazxoU/RXeZxdhQGj0VWbx2Y9ZQIpkccI/sE6R/Sr+3wCE8SyqXsT5gWGDcTw3pPFODTWZepz7Kjzowx5rw7g7yolSL/JF7/nX9pR/YKp7qWsn9Y3lJ4FbQ1ShXZTcxbN3kwVvjch4b1F67FbY8+/Sy/b5ZJnX5RvJ1xV6ENqrGRBbb6u/GGqJFrcaH9XDu8aXsbel9ICk7DyEfJrzL3i0dXV+gkgvu/PYPOeko5226NnHmZEcTdZLSji7kV9BZYFcZ8cI03w/ZjZk2fd+ElU9eU6SnVGIdx4bGfJxHThSqW3VziFRQSo59TBwhm0FUqU18IpwuXWLFqPwvStSHf9ODqgz1zK07St9W0W3+ZWsXb2j1Vxm1+WNW2lYUxL5JZainj+dV64=
*/