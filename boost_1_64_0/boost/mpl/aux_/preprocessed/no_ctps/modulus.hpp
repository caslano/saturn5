
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
MRiF8ahXnUfQL233+7in5NdLyh8k+fWW8gfLcmir0sfMb245DijnyZ7y+/ZXOb++4iLnkXJ+fQN98Cb2wN+xD/6JA/EvlIv96aPBBROxME5AN5yFRTATi+IadMet+BAazx9xH5bCL7E03kIP/AvLoJtynohFsRx6YAWsg17ohxWxJVbCMKyMUVgVR2E1nIPVcT564wKsKdc3a+EmrI1bsS7uxofxKNbD49hArns+iqy7riFWwcbojU2wMTaV65z+cp2zGQ7C5nJ9swWOx9Y4BdvjOgzADdgJd2AgHsRueAW74zXsgb/h46hc/+iJVTEEu2I/ud4ZisE4BIfiUByJT+BoHIZy3kE/tv3zjrbS3h7DUtgOK2F7rIMB2Bg7YnfshKEYiCOwM47BLvg0dsOJ2N0ydo70Z2Nfjf01W/I/iaXxDDbAc5LvTxiMFy37j/QnQ12N/SdGljdK2v9orI6xWBvjZDk3Ckn/r/QLsxz2efKR/eddOW5ukOPmJjlubsZa+D7Wx63oh9vleLoDu+BO7Im7MAQ/wDD8EONxL47HfTgd9+NsPICr8WNcj5/I8fQgHsZD+D1+iufxM7yMhzEXv8ZSrMtRbIPHMAC/wY74LQbjdzgWj2M6fo+T8QdciidwBf6IH+Bp/A7PIPuiLger43n0xp+wA17ALngJH8er+CRew5l4HefgDSUf/BM/xL/wALIx0y+iC/6ChbE0G/QhbIilcAh64HD0xDlYHuejF27AirgFK+MOrIrfYXX8A2sg3926OuiNdbEh1sNO2ABH4aOYgA1xCTbCV9EHP0Vf/AKboNIQ/bAQ+qMHNsOm2BybYQsk6VpiT2yFQdgGQ/ExfALbYxR2RAN2wnEYiJOxM2ZiF3wTu+Jq7IbbsTvuxB54BHviUexlvq7jQpL96IKcN7B/WO4nTZH9Z4x8fzwl3x9p8n30tHyPjMVmOA7b4kTsiOkYhZPke3AyPoVTcDlOlesP03AtTpfrDTPwS3xers/MxOKUaRZ64BysjPOwLb6EHXC+XG95GcNxAabgQlyAi5CkW4yZSErfj6/gAVyOn+MKPIZvyHWHN/EcrsLthRx7FhBjnGiPbTJZ4xk/dx/LhDFMHB+/xFPGLFlPsh2jxB/7kVRjkmiPR2LzXB712CNVZbyRu40zMpSkMbaI5Xk7e0nmZ+xkk6oGsK4a44fMJMl4ITJWiHmMEPVzc+4+JoiMByJjgajH/mB5Doz5wXg1Mu6H3XE+5Bk4vG4zpoeM52E1jscx0jgZt+MGKeAdtgVpKmkFaS/pIsnzXcblIE0jbSFlk0ps4FndpJGkDNJ2UjapxEbG8SANJc0kbSRlk6puctcFktJJG0mnNznH9bA3FSZFP+D7/xkj+r48+68cB2OJW+RcWmIfJPa0LJZS7nddpxHLRAH8jMFFjt3zeu6de49ZUsZJjkiJtsQspZAYuFUzzjTbJkbposwbR+6VZeaqYqTNsUksU+LbZfxliW+aR3miExK5fClxqTbx1Dka92Qcl+UxRLKyNHVsKP078jta6vg5LE4dZ71rL3bQLyHSwTpu8Z5jdayK5bXEDdqupyd6F5Z6l3qWeteMDTst66y631jqOG9MYQWpR9s6l20j9asd11tWtb2SRsewWixPtd1TkvRRxjcyqe99TJd7+Tlvpd4pO7pT7wGb7cTpRbKXJOqTWJw6TM+h7XBrm2PbwW58Xpj18wuk7WqPP2Ebz6lx3/9t9X3/tvuAnXZ9USO2byZt9bbSJnjPoq0SzynbnrcaV5g6l/cq57i8xus1jfXBclXbaXRiQrw6BvCxLdYxf6NkvpfMj3zf+u8fMK/+u/dWZ0ygMybwTkxgU71x+U8=
*/