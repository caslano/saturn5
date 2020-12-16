
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
5B33/LtKDiSAPdO2Qr7HmbmXvoJFXmQ/5ISFS5/Khtuqj0rFpKbS7n3aua8oR13VOQN0xgC5Z+fjptP+EPpkk10uO4qP3LIdtljiKPr5w/bBjv/pBnteUO33tUt+UPYT1X4GYrcM7S1JZ+XJLskLlnpOzRHrldaGS7LsHDOjWI6Tk0cH5tIZDCyLimdaNC4/0+okOT6xHMiNeEqhxMkxkc5IHqQH6I1d1hn2QHpDv7PMFrYen+2HZVrHIstxUDjTEWCeRdSXqpXlJru96jNa8oeXaM2ncgcm8eiJncfF1oCZLQbNJlONTHs0NpaPmo20AdIhSKUHthMZ13pWTug2wDL5VlFKN+2wpb2zJpt8/hTJSaZMn+xEu/fYpnJmzbdZUaSyfvB1jmT7mhW1ZPtqLvFYfmwmLN7KMxk5X8ycIH7sWyArq75v2MhWvyk2DyvcOBCCHf8dAjMezRo6sitFYpTfvVIeJkYXUzmkPR/BZZoES56JSoTLpcROt7Pz8MmnjA8sf6rN6MRX8KBvAvRNXTzEz8+Tv6zF8+M0jXb1pun8PKChyeoQdyyTAVVbb2esfu7YVINNYHpMq59JV2mzNFABa3jhJIcFy70wOyVAS8/KpGdWJuyJ4xZbX0/6JgMA2RfhH32mPEcpU+Gd1kFOHsMiEXv5Om9SFnbR+QFgpWvBX6dqQ6TD+6htcS4DltQgo3aK6oCW1JMRgKvmiwqvcUt1o+SpCsquCUPbCJHMkmvNd5h4zJzPDm4Znk52TOmXeAx8qCKc8+3V+QypKVziWSZjUT+zLpVbVi4cuzmCkb9JEFEOqOWt1o9g3qnHUdUfEHnKroVGJpWshid3Peiidpof8shNntKmksHUqIgV/qLSxol6rOkrOHWTa3TKp0RVl0G1q/FYJhR9GqdyqiqtjNcBxedcrmmPnbrRqpuyrFCZTsOHP8jy0hgEsK2ucnOr08ajjUMrkytCEzdLO7lV2r9d84lXZb9PW55aeTUlq8kNKZtWplE6p3LCSecyatGdy+wG4stnIjnslG2qQpWca1Wt+3zqGY6udk+d/Kks+uZXFpqKnCwx+QOZA+Yu1F5tjzSJdKP4ARmKr6DJnyUzipxkqS1Oio/GnmnVt/AkeSIra4jYpfwYHf/InhhbrfMIXzjGNsdsrzZfYkyUxmzFoGxsVw7ahAmSBH1TkEBQca4EtBloCShbeOidLOjpfMpqV6zNkId2trfit7T1G4t/pXywsoWYrhQTvu1PHu435LCTYkSh4pNp0wy2PIlN/MkUfn4e2zEwKY+diKPZ4KLYD5BjNOWxIqS+C10OpM1uyEIE1Fsx2XJzHA4poKpgFO6zpTqFLJMcYngjMLa0HB+7M9CPUblPS43obqduHdsgULXtyTAVaErdCYV7+twigoZP6sBwL3LOMqcLFDi81eC/aoRZW++if7ZMW/pqNOtysfywJ0Wwcmc804TSNkKvsbWFFVmNOashjQL6WBQO9noZzQjcmG9ifVj7dESVqz7yhi7ps3ti2kTT8gRayE/Mbhx4zDLnG6EgYMl+JGOy5DvY9pxMC5JuV8kFo8kOQ7ey/MItXQ1xD5fSIUVDEvpuY57yu41pVZ13iRFBmMv9JNHYnNsuyl8UCdSZCiB3gtTxwiP7zTpof/zNPrJzu1W58puuGNZhRtnSycCKhCuOFyZzpHxUV1OSjyH7UmkYySINRl63ZArQCqpMqddODrVp4j0STXK0YQL0eWwqnNWeJVxN4RV5S2XfCp1ozrfk2zUHGck7cMg5j1/jjjCIG0RNNtq7hvKHvsZDjzRZ1bhTbu3RuqR2KjDU2DUwuNrN5b27BvYzG2urM9XbhkkSbit/348=
*/