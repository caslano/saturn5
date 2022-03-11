
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
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
kKmZLip/j8kycGgZ62EN5qzTAzZo8++I73CFBfH6pOAzGnRQvT+2nCPosIcF+YXaqUOHap7UNOpSy1Q+wg7lW09jmLqJ9i6D7ItaBrNaMQB12aVymlQ0tVZaP72hshoJDiRIbsdg5RFJeeBuLlyHk1DhLcu0bxLoZyD4C8gI2HiefN4oBTNoj6cEur1PAUEYuOR+DDJYvJKvl9WYyAuZMPPLwTXH4GhyBmnVEZnfXxklisU+ybZJ1ZbpplcwgIJ7LdqnOADgUN95J3BZDEI3lBdmcomSbzvKzX9QAoKeQ9kWE45SVvsR7lajrQItoWJZoScRMW2RYJC4JoI1fnzBsjyW/W8ReBcq3XEHPgUqwvsNrglZyHOILqzi+yoY51jNV85A75zVlpgvPXwQq21IpBoZzShQjc96v45Cg+7thKlWCsrvsCAqFwu/LNZz1y9e09bzAsFT90j1yiRgNjZ5+/raqSp/BU4+oitnPSpnK5ev6fRpg+6VvuxC+TFcEdas3/TY+HpRLBM3EoLGAah5+66qLsp9E21GJwbKg3tTwNQU8cP+cCsuHwtN5S4sH8OPt97OJYUZpRBakSTQI30mqbwFu+HOkek/22KGYV7uMig3ZpJVqjtzBlPwO/8WXoI+2HvFYa4P5gi1oyO+/ownoCzl7R1R0ryQzx0oQl0vL/11Fy1N44vXPxVegj4h1qYzgLEByoueaII6YMujYTWVfsd96f/mIqT/v8xNSf9fnV2KvPPJBH2Ys7dyF/cXXCk1IKfg+SlF9cdUz/IVXK5WD1uGOM6idw/9KorbZbMD7cA7zdzfKWvH8bWeQSN0dsdRx47jSNvqnPnDp7RhGXkhqspBnI29yOPdBXCKKtjVv5kEzEKOl9AeIGFRJ86X7ajHlj1iD6u8LKBIH/cfNBvgmFvFDu8j54auHEc9t8gHsEruGp0t6Zw/KtQPiHbkqm2dRcNz1ls4os6hz8KjD8yh4DpPDadYnxs/W8L66BtOWB+nSM8r4R6FBWIy5RlS29O89NmJRdf/tGY5yP08IZn49zm4EIhBSCPXt07YrQsr6HL9QzTaYZ4cco8IR24Mlc+OpiGPMbsBXUMG01AfCLNlG1KtH1RQbUEfO/Ir6A0oQR+Rp8stJ+i1SbutYY0mmubxK1opzc0zlAffgk9flLhz7x+eZ8E++h8v739vI9BzAkEAgENLrX0NfJPltXhC0jZAIEVDKVC1Ck60OHX1gyxzKx+BqgSSljZMTfHuMtdF/7tsS7QoLcW0pa8PKWwCokNEx93wjk3uFWdRrK1ltnwIFXEUWhAdugcTtUiFMDrf/znned43SWnR3f9/+1nyPt+f5/s5B893KOk93dFTWV+nz1c+SaL/kTYaXIWrOpr2IiUxjKuA6E4+a0IAHZmMdpwfQgKAm8MclutozkRfaaQW02HBqvmmaVFh7+Vf7ahcETIxfz0gH4xCXoS6vcoTSiUH3C8NaubkRlwdHl/5eDPcFaWyQ6k8CEw+xQ7hxAKfMLkOMjfPc3cy4HkrY0ptLjnnIv/ma3Lgt6mkQ4lMJJ+jW8kLuufsYZHDSoBlrcVfyuuT4O+1a/CvR7DKrK6XtMyzoRu87ObAGPWQUptNreNh0hNRI0eP+2qtiGqoCBCa+AF8+3FdAnGCrJg4WTHFlEKrYPtEcdRXRCI96KH1GoBCQpyMn+iR4EpIgYawn2rqJw4ZsuLFWw83bSZfVEPDTVvodXZVuKmDfoSYWBOaPluDi6ZEzPg7Mol+W2jFsLqpncWFWNxEiwtdKrWUvVOZglKVNfgBHSseK/Cz1TVSrtUhFtxEjQA5BoXIN9LvzmXh20ZaLVY0RbxupGycYT2RUNq0IjQwmBmNFicnhgfzi9Rm4gIIRadZAA6l1q4m+FFbbQtxfgdJuFKDR0L2QzFctFn3faXPutacNHcsHzHfoaxBu3ogfln8HdX0OtYxvY7dhJvitJTXADFMjRCBzA7ldTBqp8iDUr5VSESKrRY9wRxXpM6ROq2giCIRywCzo/1GLxXZX9DRMLbV4tHw3KOxa3Ruzm9ulrFkq/lSuGQ6G0JXsiSeNaAoIN0mNboCH/qQFKeVJO9hStNqAscYLQgfNZB7sOHtAAiVpvWUvxH/NiAsU6YsKEuFZ2gfpK77On98rlwUJvhzABm4eljdCXm1CvmwO1rgivYUIY7DtTqojGP+TOVuM/PbWTszsGoU+Sp3Q+XsUp9yt7Wf8pQouBzYf7QdxreMobs8vKsnS9f/uXvYLDO9voc7b8d7Lt9txObVPS/fbfBNv29WB2rWxx9/mBaZnknUxeSw0xrvJi0/yZHXckJM6PseEMQAokgMYeix8o76xHZBl15oeKAuL7RnzWQt4Ubi70qDE1g9/mJo6Jy2kdy4PYY+tkthWd7SNM2rcFdrD0hbhHrcXWRLMAR5ePEUuCTIq4QfMRuCaayoMGpiRTNqD1RY0JP/HZaomR4IuOIM7UOBQkFb47naA/KZkqPknYfF6/D8Lle8UxODthzexRfDWety9bKeY7uPtfAH8OS1I867ES64HCCKRVMS4LNNGAUUoGTfUJakD4MTFd7eLbB4yBIaw1w5HrLjBpJhFlCFZULGxdwoGvWG3xxSFHHFMfMIQiBMtUPqP5Gf2ocprkzYm3DzkDsoRuFrmFSSzVx2LFOI9TZTvWyod4dWcQ1VzIYtLgy3DKGKj2kVrVgG6y3S+rNCGS9WK9P6s2q1Zp/TB5zY31wkOdGCDnfWB/cDFnwC+/NG2udIpdUH9Ohj6Bhd7ZCWWdiCHc7jOvEmbxjafsm0htXEh/axggc9/KiCvkJLPs2Siu0xLJP9OoaWwu4+oFXXkQ1YO8YJ7DMEXy3mlS64jKilf8yK/ss68nd5vYorlt+MsbzghPfxe/LRjlEY22WzCiubb3+ufCkw8q7e/Obf4i/RrDLVDtjO6EEL4LWY0DYtm3hryvUoU62spA/uZsBIPjfkYPiDH51VRXnlEavspySuzLeLfObqVbzZcizUGx/26WfqPSnLciG9szgj+T178cAxEvAR4WERT6JtFp1C1AQtIetA8VBDQpTyzvf+y1B+Av4Qo515HUDN1wj7BMdEmKBsETVJaUIN8HrSV0v4teNUbDiKFRpRogyQ5AQKlrPIWxNgU/mkQXGdEK8aapsrpoUrcw2NBgtUTGs0WGFcl8N2ZHr1lw0e/QUIK14kncZm57kzlVlmxXaymozTgEe4QQQAvbASxmNXR6NQHp20uGLKGKgZvYsGiRIPGCSZtb5GMCiYNgLH8vWDgEaE9kPJAHToOsGKbvSkWE5qUoq2wcGg9Hehufxm5xA2OZbjaocyFyimMuUuM2uVVUjMXn5CCOoPsP0Aw/hvelUhq1qJ9En4XO7SqwBImzqUkuzaXVVXhd8QhNJYtpyomJZrXdlRK1uJDi9MsILubFr8TJp3YyZqLLPg1GR6IisJf5b0abNfKTaeFqCkD7ZzkYzmUHQjEFYEkVD8T+vxqBmHro+7P7zPTrxfyG8m81EyD+xBg3oAy6eIXo7hnhH1LAlTkrMDB+qODWpR75MOhRfkvy0uDP80PdUAXay3IBGSiQMHEQK22hfp9yqitH5LHjHiHqUyTn7IZ5PtJpnAT8tFrgnw7SQi3/tYwyqBtH6N/KgHlwMfGWKih2f/6e9Ac5AX9ragV6Q6ts8fDks+ij+w4rS6QKFYPMQQOirMwVHPVcDNT05to58Vj203OG7fCn+XDhMp86u3G1JEGmhXdcZWQ1Ew5uQiUlxPxGM7nYIryvEtJfD5JnNCJljXLiWryHzZheWt3fZKsye1HOZayDj4dmE8Fhxpe6WjKDBEFjrE6qyi8ijomeqbElmZMguqsJm5RQEjZXnUQwtSBUoCnsWS+Tekygbj31zW/C6guLKVWpiZ6tiA8Cs4ka/9AYH5X6P+PACk4F4ND7TV9UkXpI4Ne2nD282o4pmHVKryDP6jPDOfiG/a7X18zz+RGXqQWserFLTheQwapffqqFV55kGqtQipbYtCbALzmJW1yGpoNbspZnkbfaGz17ZaLI5AOGoXqWY9dYhogAFLbKDXmkTBl2wtUogRMdZtlVZfDcjZGonALybW0qP4tyr+bYq/UfHvkKwlMKUUqgL40mcqaKAoT1f81Yq/RtwvYHenIG39S+Cr0YRTRLbQeBijTt8vkTyMu5ruWw3ct0jtFMElziYukah8/Mle9xAfEqQOE+vj2ICALVihyUfkQ7/yRJ8rvnmf9+p9WlA+Tcuk0ApGzB5TXInQ0kdwDEvTFfpX8H/O+NIhyAtupucwVVlyY0dKRq/dKMrS6NlaTIsAMSbap6wI+mBRau/DVRv/uapCI5c7aJohi4MmGhzpqJUdi2ZQNtABe+DvUPwHFX+n4u+Wbzvw6c/B8G5VDJ2dc6xF7gQaWosHP3g5o2/WRMzJGiqzBg87BqnGc1EPV9DrSX450uaqn4S0Rs9fhwL0+a9DQ/HmZUZc64nIUUcvgm6jI4tRH14cuFEdvQQt0EdyLxRnETz8EbuR0exMHZEZGUOcHVWjIf8mPd/UYqJspytW9aO8CP6MLFYFeefcE5wODIijTs6C3EUHb+TFpz+GdQIusyAX/oHVaMZBNyv+nYq/XfHvlatRuTPv9fv6zZGJlRFLP88yhLm4s0MUqLKHv2sMTWJ0gfNaCsUiYtptYgYBO5BeEUz0eaM3QYmAXS40ZeuZoidvdCRbQ9WyirwBNaCiOu7Uh1kGeYODbbULIXcKsKzKM+UigKrxjXL8fH2hDEwsGhajDZgD5gLPVG9xMcCTS0hxh8V4+ftAN9MEUMOBfNtC2IN6f59ohqz0qOCnTwHbNiJ4w/OGwKU4Hvw/ktn+D7MSCjq6va99OjBnHFOzDEkOqqS8+Iq/ZRmSZb8o0yu0evmnH2TBkVlOYRjUD4iqVupWCWn0FfzFB8+rGlJ7D3IhEfDQKok+SOdiMFQj1HzmY6hLgjVDcARkFJD+YDmkwj/zz6HnGCG9I3zsKUbuoA6L+wSwRke5fY4mxEahKxxNiHdCYxxNiGBCNkcTYpNQRn5XxGeMZrxKZ+QITMHZFipxvh9MV9YiSkM2uGSbUtKolOwk8Fm5tc21o508NjQrrnbFtVdxdUgD/sruZLGdUtmjVPZiHK3Z6Z+o0Zs9fAb8C01fJ8d0lRzTODmmS+SYhglsKhyl40Qcrr7gWEdVbtAOIAPQf1qgwBc1+QIF/JGPaDHuiqfEBfpG/jwknc5vOAvbjxbgEpyi5juJeJepSL9fRIFUNsD7vNuiX2NvRQqZb8OREyHPqSchARdiad0gniR3ContlKat9JfgaBNJjwmohfcAddRB9m4HxZMFESZBofPTVoekKu1aE95BZcMJ+svpb4z+9tDfXioTp7999JfQZ5OZ/lror5X+ZtJfu8DhCtFG/JfkzggdB9CIG2jEhGoVwrCsle1RiDAUBKMkHgnMSclRsiypqZn+7pRvvN8aTCnXOP+9AfQNF9cXkXlaRteF+qLhcMvauePiGqPU/518tJ8+5PxjPSn+BKx/TRkfW9YMbbVVr7BIZ9znr+Fqf/renvQ+mfh+rINkPg8fy8JXatNzfR5J3K/FPHIWmsIDTMtF6vpGMvZC7wD8L0ezZGH22CTo3IQeafuABRMPTdPOZxkG80eDPS9basbxslOh77BZlnB8fGg8qYHRBl4ql5MehZGRL/rJJoPPj1F5PP33PeqCsoH8Q3nRmcNy80ikv5BNkC90MxYI/Un49txV2wE0FJbeDxye7Y23nmLt+bvzdjcq9fX1Z0+a3mn5R7o0+AI+7sri/K5lbSdgmvcDHb+uleEsfQFDMZ/2fI86J3TqHuH2UDYuz8tD0W/ij9LD57zQo2mhgQtvaLThrZ0MO8wP3skJmaEPEtqub+ae8pv3L/rR9WPYNZ/7HE/Sn56q7RlMf3rHI0ny1+zB3wvTyPnl3XjI8lXhzTAZrnM/3HJfILPcsBQjNo2uxmcT5cjt888R85H5GRrVoJYZsD/SS6QTJU/0CeM3PBDf7YReEh6Sugfxe0BI+CfxLPngSOLfvyTHfzx0cX2Wt5gdZoyuEJ8Ot54hN4pvTi/Bx+WVFkOpreYVXFRGi/qPcLqBzcoNpMGxnrcYH15NPJJFziNsNa8JttCrHdLgQhamK1WFGnsT0mbxoBtu29U1zSr8nOaTjb5c/6Vayl/0fgp0wd8PZ+nm4sPaludcKSABYfgbIC+RLANusYdyA0NKtdGsPSxHU/sLfKGdx17aYaPonFmRhRPRoJHdGsAIawdxhGdCn8kRTMBpZQh5Fb2wPsALbj5FQZLuPEykyGRUi76FHmQntHqkEe/b8y2G/F3Q2eoWb2TlFHzMHHjnUzX6M54fjVLlEaLy3Vj5r2ePjD8w4d2iyMoTk6HkKqzcjJWbIyvN9ITmeqgcWb5OMLPfouepuezS55BAY7+W6mmdUCOVUNSELdP2oWn1NtQvqgdqz5SFxsm1rxYhNmHRqvdKUkqSfPkJkm8/D+B5o3b4rLqYyp6gytNyy41pKW8iF9zTT96h6fun/qonRd9PblnXw4UQev902sAT3USVfAqdJavpE/YgUOoUv/+feGPLTh6rTEEWiC/aj1xU3w7jwXMPd6AtfV3XJgNeAOvBwS/AyXvm9ab6E+rqjy9J3zzFLPTN2nz58L+JYxa8hOZl/VDasET+mpX8JCzxfjlSh84FPOXzpuNFOwLVl71lwd0qL6GUdki5EAEQvvteMr4DbMBLS3tVthzHxF5ZRH4lwh8Y3+Hh40Z0YrySOgIKlB/71lcYsc/PbTXXQ1rjd5BccJ3YvlB42BZ6CnRhEXGdAODU6w2YimmAMJEf/cakVegF/FnSWwQ1sZysHQ8Y83cVQyvlXlHhJqjA3O1wD3Ba/EfQN9UX5RHt7qSeej1obFwcMJZ7qCLwZ/zLp2Vnoh8sG3Ht9ASMVDkA04qXF+ml26C0NgocdaRkZ1HARPWhqOjJ307rCuN6Sms7dSCKu10bS2AIDKZYlH4ASp/8NvmvmoRy/pK9RcBH7tUZa8lHPhknuXY3stwJJxcayy107ccDWV5YszxXt9wS4vi48b0sg1iz/fwvx7NgRO3AsX5fMK634St66DCm+HsUf6/ijye1Gc9z90CbsMgwizxXTDa4Fc5348LkxYvjFF3ttISJHV31lMmgL5eRahTLzUuuxcuhnNib/dyKJsVF4rcBf5eI372AlsSS7eccn5QJjxzCZTI/dCoJHwF+/e9okv6gYlD8Whpxr+B7AZtQOLGAET+fhc/yboZ02gp+HUAPpRaFNvzSyZqmZS+++ujwYP5XiL4a8F7AfWCttjXA/9cUKK5qZ6ut4UVhI+mvYftsa96MvDqXrt10YJUht2aZgfwSJMs5+DXIRnuE1YUkFoUD43XvZsF46hMPGOHDS34DkP5s5zNgR1jlivLcZQb5LKBeF/LXJ54FwJDVDnJxVC+xuwtHW+N0VdtWeInLx7l6cWo3dCU4cvjccnhgdtzfk5Xig0Osvzn29fZv+NS3fA6sCV83rzfxErmTXiJ3A1TkN7aqWmhrst8Sn0ModDvC+lVFvWpAy53eiUa1O2RUurY63BQUDg9qNCcAnxjvoliK/99BPbiShEr0l79XlZ70yIfLxL1k1WimAuQc5cPMXnWrCXjGSMNGYWnaZkQFNqTwj+ubkwjFnx3IMgz2plrSVyVJ9nB/fPsi9FXjkqP/Mv/1PYz1tPztwfiva/+f+K+uDdEUfBcbaHy/j30TevuY/hqKNdT/sJ+7Q9aw4sKkVf2TxI6t++GFxmy/3RUdyA1vo+VY//EC/fpUxe2ASPPP+JzHQpezZdXw5XwrNIwtq6dfwelsHWrsnceCjsj2KdeSPZsS6uM/83yJyq2JGGT9ksfPqOEKD8oU5+cEx6uuPljt/TP5nVDG2bOke0FZuF2lV1nM1ac/xCyN/De2R6jfs+IMmqJwPjlDNzDT6WsaoQ8m//18Nf8MN9f9BXu+RmZw+8++QGPIjHDFIkPIOEskz+RHa/+CnR+OzJJCnFYWxtlhbO7m0BWOME4weC9j+C/Sf+iSCZ/MQHbQlX+mNMJweLx2Lk00f5WWMFERsw2ODFfcbAhaAH47CnOCOQGDKDCTF82lee9LzNsbYZu+B3XjOadhNAWUVgo3/xSfR3D34GjIzNsNtCP9DBj5yGcw3iN+oAwJ627JOE2UnRUgudQnydIGfnx9jPLsMi9xHrtiSfqa2enJ+pqkY9niYdWir8jmc4Aiqg+f1uGYSPnTu6cTBj+UkvPX0yk3iIBodjQryX8D3vePkvzHvr7r4vyUTu9xoveChGY+AXgdabgXw2eVV1BKJ6as7UBfmOXGqZjyFqbUzUAFX/lDVGYb1aKI4eUhSnmeak02Y62HKWUV1dqI6pnyV6ZhShXVsqdhrZco5UGqVZ+GtdKpr7upFj4J9ZQfLsCUQqq1KB1rLaNat1KtzJFY6zFKmUi1to5O1Fp/GOnYbaORjhXzevxwMh0r7G9QSuOLNNDJuw5OHusE/I7vSTF03HZyXtOwEY4Hm05R7uvw8MMBvkypn4EuNhrw2ytP0OO3nFZPrhAuVkSx68MV5YbgGKVwEVuLSUWyZAeUjP44oJ+9rTfDdwmrq6dqgiTW8uaNh3PQgDnh7TfTy5jJieskMlgn2jO0i9iX6gERCnFFeo/K/H1segVrmH8t+oQpLg4M9yIx5e8Tch9EiTRzw2UZKLgZ5xHfEnbykzkZ0PbZrvFd02XBjPozKr3Yok845PyWx4DgL4mjsYcoMm/+WbhZ+JOtwhBfIlkYorTV4VqSbNxa2wV329ULg42mk7WIVzbwt2XQ4tr5BLsAgw+XjhpYHSb194MjYU+iYR3+4f5WWgzIlpwKjZZtz1p+BoFZOivIwXCBDbIXAyyM6CXctB4bIheVoXS2Ac9PpGHF7XrIv2LZUuWkDOnEeg5MQSZ23vklveoIfhejqQRt4UdvFlFA9vDLsr6EldNqq9U4R1qkx3YQXy9z0OgyMXU5KLEa+tSLkmy9LcnwaFksnqwx7kPdhh4P/lzEHcvvAq6ATD9T6XiURzrPy2ers3KFQWhgCAogPcBoo5amQpgjoCfegOpDIwVgnZeRJpgiDiCN+QLsXDHKlVejX61o9IxaTJ9LyBU=
*/