
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* plus.hpp
JUzA3+F8/BwT8Qs04t8xWSd9GqE3psj6XWwkv8fl93k4Qdnu5+X6baGsX5qUWzrGYSYmoQkzcREuwSxchzm4BRfjblwi67EUH8MVWIwr8XlchedwNb6FG/FD3IRXMQ8rMB+/wQK8jTxuk/XZjm1wB3bGXdgHH8Z78Id4L+7D8fgITsUDOAcPohEPYTr+GJfgUVyPj2EBHsed+ATuxxN4BJ/En2AxPo8/xfN4En+Nz+Dv8VmswOfwWzyNjSjz57EZvoCt8UXsgC9jX3wFg/EcDsdf4Fh8DaPwDZyKb8l2vaCT3+q4QvZbZfudkf32Hdmu72JXvISD8H2chh/gAryMJvwI1+LHWIBX8GH8NR7E3+DjWIov4u/wbbyKf8ZPsTH5+AO2xnIMws9wLFbgDPwTZuEXUv6Vsj4pjay/U/n9KuvTVzk+ZD9dIee11eiLa7E3rsNwXI/jMRen40acj5swAzejGfNwI+bjDtyKR7EAT+A2PInb8QzuwF9gIb6JO/Fj3I2/w4fwj/gw/h1/iMp+uweb4Y+wNe7Fjrgf++IjOBAPYCgexPFYhPH4KCbjIUzBw7gWj+B6PIpn8Bi+iI/j63gcL+IJ/AyfxC+wGL/En8r5dC0hIM1evx0u1/Bm2X+CZP8Jxi4Ygr1wMPbDIRiCQ3EkhmIkDsMpeC/GYhgacQRm4H2YjWwzyYf89sUfaOQjVbb7g6jHhdgR03AwpuMwzMRRaMLxuAgnYhYmohmXYw6uxsW4DZdIeRBPfvNSRrL/KetplP2vj+Sjr+Sjn+RjAPbEe3AMDpR0B+EkHIwzcAjOwmFowOGYgCNwId6HazEct+AY3IURuA/H4qM4Do/heDyFkfg8TsCXcSK+gZPw1zhZ9s8p+AVG4zc4VfrymoYtcTq2xRjshDMwGGficJyNo3EORuJcjME4jMUHcCnGYy4m4BacjwfQiMcxCZ/EZCxs7F77h+uHm+r8jjR16mtE3c+IvX+RPedcPj/g1KeIy/5EpA8R99pMSH8htn5Bipi2H537AnFuT1EmbSqsfX50R6d+PjTbV5xwamNh7dPDu0r69HBqcyF9eEj/Hda+O1y/YzGU4NQ/h0abDHU/HNp9cJzHwBhXbTXc62tDnmuQPjbs7TjKY3CGvT8N3s9Ypz41XPen4dyPRt2fg6CvDLf7yahCa98YsQRrXxhnCVp9YJgI1/nsN7tmG5EQpl3GOFT3baHu16J3Af1TEFIIuYQiwllCKeE6wX+bp12JZ/AMnsEzeAbP8O8eGqD9v7X6/6br/s8p7/6T9v/d5Zpou07e3UMI50KxdJ60/7ckazDWpU68cIBy7z/dVhcwMri6boD79rZ0CyTdYEJjwkDCaEaKHlCn6957Gazpko6SriWdkZIOI5bhTknHizBGWT/HdOgIIMiQYDIZjAlmyvHG7x9wXlfStD1TYZI0m0uaynwRpFmpkWYGr7Wrb3rWdSzTWMexSsEanNMzzM8wpGcaDUlLTTeZZmzjmmmOI02fmmkmsu/lmJOUerD6pWkt1wsaaY4nzYCaaSZT4ZedUs91tKYX2qRmepGkF6SRXlrCArfe81Lbvnqiifb6hddMTxrjWArV7TTV6zjaevzfXjPNCaQZXUua1Y8Eub+ukq5D3xyFt2uva3zNdJW623qlNUjSCpD2ERvkHLeGcD9pmRzTykhacuNznLRtsrR7kGPXoU2H7Ai2c5/mdpb8tJZ1VyZGKftxvEN+sut7TrKm6Sv5UtqRqJej3scjpP48RcrGSJhM/PAaeRko56obl5FTPqR8nMpMysfEgszpJmWyQxldbFqzjKKDme6Ur/qe05zLaCDj6gWp8xLXrGZepjF/pVNe6ns=
*/