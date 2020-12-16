
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
KwH/aeTThbh/FvfrcL8W95eeJu5/Y9SBq5E+E5CPx5KsI86A07X0EXVgG/rliFusw7XDr/phw27CgTW8rlvsd/WSl0dUP+Sa0tw5aVX77C4/aBNQN5l9FFle6htrGjJKPXsi+ZLXgWNtt5e/0iIN+TxKb6/h4+n+7tNb7K8E/PW7iX71O/P09dzryb/pRLI+Bb7ad1uBEvgu0ukPJK949c0ZehxxZRMVjmCdtTue0N7PPNMvP62PN9Wf6jrroD2Bfhv0dalkFnq9/aW/3u93CNNvvbxAbm86U4apnj8GZLrn/Qvp7nk6EZNtEq/jz2RTzXEZ95779NFYN13pr9r5Q01TUa76nyXS8A2Us+G4fysoZ5jnsLvw6Hlol3N0fdvrezNfhpXLB8La/19sj41w8/1HKIPkPMJshA95W8aNyN/LyPer6IXPe99J8+VeiO+jvTXTfBP0Ms3Rj3O0xQvh3juIuyW4/xPu75ivt83vGvfbjfvBC3Bv9P0X7W7UcWjrNjE/iPtEZnrr6ze0dVZfTE3zA1BJVaKNnUTyvtfGnh28l+tVL83b0r9EOnKYK85GvY44qMH9A7jP4f4d41twHfx2OuJkNskHpFut+K0hnuWiJ/zXmvrkh78FkRe0vLjdqvtk2pXsKV7wINqG++j6Z+KWn6P6k73YivqhS49PFobWd2KvUOwjIfMv9gqFHvld9mfRx01zJ0voerOOw5dJx+uQR8zyh2/f2WO81obLmhcH3Si8DV7dzuHT69GgIwn9Vl8vPRuUreV4/hPkg9hCvV97He4/xf2LC2W+0fpve4sIHNxF1FsH0vUz4sw/V4//tJJH0m3ov1X9XOm/0f1F4t5ty0k2BHWbGperyb1+Xl2Uq/VUpBN9ri3EaWaN7FdN6oE+Hvp8nxOndjo9g34W91uUZ5bJeovTqJzSpzslcB158rrzZJ9tDfpoSb4XfcOt3vvTIq2Wwh02zqa4Jyr6mXjOT9MlCAt4ucacyBsxivxuvUXd9QTeq9qXmigTZeW+s4FfN9IzXxN5j0XIT7KPylbmtNInXg6/NMDtDfBLLX2Y+ZxbwJmJ+xW4T+N+Fd1/6cVhWrhxLeOcNl4ZZX95H5obEJZDFsmwvP8DYelGebHAa9d+Lp/ZiGdqGvEM8v9z5wrOP5C/DzsP90Y9uBX5+yHUg/eTfO0V6sVa/pbdqv9QPWjVe3Y7yf7ee7Fu35op77Vw5P1IeOBG1JPX0fVbr39hhgNVyL/yHfpP9s4Fzsoxj+PvuY2W0F2oNRKS6EqpZKZ76X4zkqZpZmqm5lYzUyPRdNGFbgjJLQkhaQnlGkJWbGhpiR2EkDUI7Qr7+z//38z7vue8Z+Yca+3uZ+d8PL6dd97zPP/n9n8u7/P+/xX5+KGBxzo/SB1ofke9yPWqnS97X/SQ13o9LO/Nl5i8ovFq3s/k91tZFs+F/f0V+++uMaQWDwfe4teyudGv47+1zC4b82gohjmm6KgZV1e538y82HOC45h/P+TMx+O2yicwuPc4lkWw4m9T+Te7f7v2Osx+1tVuXZ7L7w+HzTk7NFXBj2ebOAZMQDpDrrHznZNdqIN8YSzrqlDdlGtjXy/gO59x2PPQ/fZ+nmtsM1NONgav+fdRLAvnHsgB93zVlMU/rnHPKZtcy/k4v4/l9w/C+k+tEzSj+7lP8Y4f11BWW691l5UZa9PwcGZqoSmvVjHP0UN1p11v0s7Iz8s03/Ovj68sd9tlZ/Jf5lyvhq1h0x17EvvY17i5ZuLaE9Yf94a3M9ZVM2d58zv2P0zszv3XdMea6OQV7nn5mLDvq1e42+/b/H4E+3HoOvcc9snr3H9/8Tq3Hrjmet4fVqe7WKc=
*/