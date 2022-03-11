
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
wl/TMlogVcUP584er931YJJOT1kFy8WYskPySCQo1k85BlPoGPXn2vNThdBRqUj6V5lHZYAWUzYk3wY39HlcI0A4O+eJ6kAO5dCyWbKgrng0a4/t1oWh6LRcoZ9HYr3toiduDaIzxI9038z3wxixq5+MbJR4NuCJcOZlqvlDUz7qTac8R5za2+fncsrZW4fDqPbuXvRFyrildI2eeCwqbK0VkEXzR7CSIhKbmSxG3/fUnlBLI4kMo5NY96WN6Iscmn9qw6CDaK92/uebd0eJ+LIthN3IQCN79H8AJYDafxMeK6rqvvrj8E8Xf3yA+CUgGaYEjs/je11uC+16yGCpi3xhCFbZ467IKLQR2nnZKmSWf2gsBlq1//cMB0ufJAYmZrLaUb74EMwQr1gKaO0o4R585DJwa91wfaWfcaS8C6yW1KVCQckemrUmlu8ID8Q+TftwJmFeJ/LdwQmcE0rS2oceC2J7SJs/w0KbsXhHGy8cePahCohqIINbK1MLymZ78p3Nn0vTpEC8KQ9DFrrFjvJNfIzR31eyXfvW692cTYA6+6dz3ZxU+UNUIUUf3cozQSSIuBD+4ujX2WF39Gt72Bn9OivcP/p1TjhL+B2k2f0u5VkLiDbPLoJ9f7fARd8tcMBQUN5C+m/xd4TGqPYUB/0BYgxENP3F19RJ4gLqSWF5S32e+Gpsl4D1lEfr8ioE7LpuvWVm5Is7Qcpy9K6JTw4jdmN45ipPjOi8iUakOPTJ5UaEOHmcAJ/29TI9v5CDDKIUx6bkBCHjVQU1tP9NEmzI+WR19WXjBfASo7lVOqper6uH5uXyPubNCbHHpLb0posHDNDvf665THvZ2LkxJqTmfJk4OhmoQN9AS8PH+v+HT/RkQdI5tYqzVQfFmZapDikX0CCcR52FN/q4wyLTE6uz2lu87YwgNAit5NcFWYWQhM6P1rdjopkYnh7dhu0nS7ggtD/BAzKuGvupXru9VI8FFzrQ1/vz2xLvkwrG9P6zxHsxVDzFGC50WSKeNP1iqvFaogZuCJzQnp5IM7pJoVgXt2A5VEMcPu5mmWtRC06hbyrP0YJqZ8nv79dCCRAcn0c8YOd0n8EqcSY+5IVRcMpy08MBxetomYp0lTDVR/GCeFBcvjIKIn+bK2a6DdznTp+rVCCi60PKTPeD9/d2J9b3gzem7QfPMd+3qEseRgaTXFU7W/WuJGNRnNK+u4PQb9zIR6kOxbuS0Kp0vvvsO9ADzZvo99ONm6G0Kl94uvld+mPprA30egtev4uZprZgqfeVoOrd5Fta+cbSWa+R8UnzZcmeuUrlFx1vgnaqupD3utqvWZ+M/brcdOnwORipKMEKRnv5bWSEeLL2vsBS72u7vW9YpUqvrfDV9icgnIDhNTHrja/aCFvhXY7cYgHV2+TT1v55DM6DZTqK2gIYQn6JjjwCbNL3CCCsaM7srKHjeIJwFMsSImaolJTwJU3vZ/LB0Tki1YgWy/j7CcpEXKeRO8GWHzWutyytPJcSI1utXOmXu66kKqkLfD23+5b10odmib7xmykm2kRNQa3VV1sckInWaelMvPcC8tebhZZPvL74MG0DUj8P8pqct8+Zl+9mvfJv0XqH3EII3wnPIXn7tCqoqjCttN9UFScGS5bcM8u0v2FQjd/Eqvva3dCPuvZqwSfJYGwz7WXEjoYHxE4TeXGgp5mspMqrtPd/+3n8PXlG1vtS8Xu+iX2cvyxYc9l4P16HL7TzEQtHcMlLHs2pzZCzluw6Aqs9tPPLOF8sutaOixZb+Z7IAaXeET/EZ0o545r1q5Vb61Je2RKvstRmW4YRTIhvZzbbzc85JdsVzrGuNObzb0tG34d+iR73lS8qqHmuaD6rrr5sPEkQgPDI4qTyHsmMOcR3+cSBHB1I74cuPplGP/XnDDGhJ59o1gzCxI/I2cdu/K2TOT5kRn7KTLSuqPet5l7zOzI8UDWOdCpOqY2A5Au10ljWxA+pjWjEF9qDR8VrpxJGwR/aKz+Ifs8Svjq6lTMJ41TBvni3TTpANBSt5ywTvYNwXeI/Sc8jVc9dOn4TvKVl/MouxdueCHrLRsMSZQzf4u+SCVbZLQvvPwCKfNe+KxofFLkeV9Vqb5IZgDN3Yt6RCaA26fd7OwtwKdH8hQySkfjCJq/5YzOBwZ4wuRcfHMP30Qv5+4McCECGWpSJgqVHhxYfcmy4DHrEIbFeZPmhWd6aSA/L/qL3Eu/gIxcMi1laIPSwqYCb1hKMYk14N0sl3HWx0MLmfEV/WX25+7niFOFKiONoYL+y1cG8udFDcrEVsYNtEbf0JKqpzaP/raHD1JXOwallH6N7E5FcsgnK9loo3xqfFFfR+BzisvAGYvwQrYoM2UgMn1J/TjRjhBfvwAD7+QWTaCtKcflS23o+LhUMcewuXRl5QGFaVrjGppOkEZhHe2zOGK4IIkDxNswx2kIJhWY40fyOhU9NQlgywGW7JwVELL5wkHgW39TaakK/smLRdogBDeL8HBJQ5hUBGpQAFN0K5WWPTGeImBG1z84xRNsVQcxMRY1X0ysloKwrAmRNBQQ/ZO1uCSj7igANTAUEJygtQwLKuSJAziQgI5Y5fHhCbzyiRzcfZwR+9XaJCWABmAVHUsCZa14V2pRWE0mXxbVgIn/od5KlDhE7XRzEwNCbaSCcgngztPubVB4UeiutMu4J+0ItF6vcMjV8ePWzlo5cG1jZ6owtl3Hd/erCwdobXzNJ3UTSZ80kDfRN0kYmaa4kqY9J6t+G3X1trgQ05IoAuVIBDQagayWgoVcEaHAqIBatw2cY0LArAjQoAUhqrQxc5o4dsZrsh7zQK2kDcHVfDMCs1GswRLObzdqIWzSeY92SG34g2uMK30um7rToVrkyKzReusIT8UV5tGdw+DbSQ+Fboj2Z4XHRnozwaJytI4WdXinSL8pazhUeIP/IdcZeMkfwJzyGhzamoZ4Pxrskv48IvZpWZyTz2zdi1utCr6VVvh4ZylOYtWMO1Pq/yu+0Ed9lL0OP6EMMQy/rH52ZwB+NghK/KB6hDfrXe+XXhfg6peG/WEzDepOBQgLVsUQbOYyXptC3Qi+l1SyCLmGG8H0zjVBsdC0B4ham0zciconR00TlUlYnF9UIslOkF9aQXjAMM6dohFXmM2xGc3whVOp7PZDwv/14rtk+6G0dGM38IDFbG3spjfB1kpErd8wdY9EnZ3UrsKnRXh+Ei6auVPy/V6NjyVN2OqYXzUwg/6uSZkUQKy1xSsp9aKku9D0AAiz903Fnw3pG1wV0udM1YgKGUmlELAalEYZNZFRtVuj/SPoegekA7xkq2pNeZOUsU/xcgVXthIX5HFNfH9gjZPO0GHV4TgNWjA0mNTmDERP9UuothWmlPU3rPaSH1f3N++gIr1qpM+EB2MeA85TY/2C8nV3Ig7JxstY818pTgaeSneyFcKOOVDzUmIQsrSylmbE5RyaMTq4WJg5oFhlVZabQtexd1Bo/lEqjQ/e3MFHx30OGfzsS6yZxOZWOixy9BJnkoEWuNlGvUafefg03P8wjmTKEnm+CYJLMvc/r21aZjrx+lGk+r384M80baGFm8nq2LgrO2NcYFyl12p//Y5RxX/vfudguhVEu8YxrV60ykIruioJrt5mSeobwTvEUhH40hwfq8M1YkjoM930Xu7vMLKj1+AL++JA1OODtyXHG5kiQroRXCkBaUzxgUJIhXU1MJZlScrNCY+Qhcp5uazNXGBY44zrOiHggoebjMlSd/LtUBqVw+/p+Zf6bD/irPW4cjwb9oYGWJ2mwcZA6wzOFOnlLAjHdW2UOkuvC3tmKWVD3sikkWIWJL7MSBMYKzVQ96drCPZUAtVvSqVHdi2KmEkvybFUfKP3ANT8ZyDb/Jj5sZe5IrsCbmH9K9mm/eFXuLdXCtWrIvuH/wxh1PEqPuj5faL5fktfHcg9esu3j+fDvhOKlNfZJxathvb3QqkbatWDFl3FR6cHJQOSEmFXgF5V5ATHLrWQLb75PeF1+ekLkyHZ/QPs3cHyPrseDOtz4kBM395Frpq983wTczgIeLJtkX5St8FaeWMHRjyKOoLoMwqSshotmyxJD4eixPJbpexF84H9nnTioLIFyE+JJPq3OV1b38LU7t7IMay1R6VKWwDIU3jxlNYw5MUxZBhWjLIEdJp5ayPtS7EMpE/pFt3GTpIu98PeN5JfNs/98AOOLLIh5FrFDLEMjyt11uIyDve7yeXan+jJnMLYJ21vS0S+2Z+Et5Uv5aGqMr2S7OKUtX8F3dPJEq+b9E/85QEy0O7dUuBWJfyRfXQF7P6BGm9jZQyzlm5srGmQhPvKJJTwFa4F6bN3mRbcltmoc6hLWKzp5Ku1TCf3yR+3OJlxcM3VBuvqUbJdPfezXTFlgcm6aknGR/dCICwlVTij1mn6ltPwrZ0MQvjuVbm3+o3zW6NGeuJ33xoYjEyXyUMa2R5x6gqKyrXCECWcq9V1iap2Y5VC8bexzXHJUqTxGKrTZnglCOpeusSK5j1OFg6sISI9gqFgEvhKbjItROM2Rp4FOFcd+OBEc/ovuOC5yOBswQLF45PaSPdFFrrhz5Q6xg/AaSTPPlnYejSwaDelV3PjMGKnfI/30M5rOHH0bJ1qvWSKDxQXt71904zKg7paeo98LjNafwOvj2g1/w+sTydcn2CQjI9VbICrbSZ5OkGBpJAxtAZ92K5ixvl20RXe5b3jAIyqP4br2ZHgzH6N+N2HTGDcOMfSnd2Y4G1TkXOcY3JECdO5rzhvlFge0rx8by6TZzWxPQqtuojnfr2X8lQPiWXnhT99Nnj9WopNPwl4lHnARSo4gDgY+QgUtAB90w+1WtPi0z//a55brTslNSIHVnzNkdfwDVTi900ZrnLM2Z+x+Prq3+9VVABvQnuhgPKR7SZeoLBCz8ql1zr6XR+RwBHx+HYUDZ80oHAloD14EBVA9/ITwtmH9lUUrsciPwYN/mydJ8QEbw0kUvtIYhQwDBVpXMQUIA0etxR/w6e3fk9L+Ab92vONi7WuW8ENosu6nzPYzcAFUjQGKT1sqm8tkLLrQXS83h87SpJjobjstpk0R8qi/P6H2wHknZZrvPkLmcf6DMq89fFeZ1x0eV+bNC4+OnnHRIvRMLi1CzwymRegZGy1Cz2TiRUb4elqFjoieGdQ5mH6F3fjWiW/749us9yQPO0j/4dmObzKjrRnRepclfB0g5aNoGMARACs+G4jPnPjMZuQ3W/i6SX+sybiEf5EbN7brXUrMDjcX0tJqAV8ALlBWedhT3aPEHPyqUFlrg6eN6sbvVXnsddN9PsHUYpjIgCYXKgqFnmMzeoH0+lDE6jtdtmU5x0foDxtKLTT762Soar75OVNVi83PNpKXx75fRBpZHSe9UvTonCHXW69ajMqc58DDBcXJgolcUJgoEPy334BkZJ0TqwAkkFY8TMQAypdaHMlWuC98zqC/qU7DvDqtZ4ntZB2Vapk+4HRLDDGRbJkvWZTNiIOkbD7JvzX+fULueGarqoV9mQ5oe+cWyVROq1CCJPT3cVBpbsavbczhvJRUsArthO7451csAe3dV9vj8pixn0+C0o04+tKMEN9YNCGsbEZnyo+Hr9F9xlyqYB+RT0WrEkO9zqve57UCAxFLKojXxu52NpzH9pmWEb5KQuh43YExnwMp++sf/pO3rNQlM9gIl6Xdw4oseidV9eHzBoLqKsSNClC/Mx/hfg+jCqHzJvyHqmrb+URQr83gVRYiCdfvU2flB8R+JbYS9Iyt4fhTU4tIBauwrPZrwyvhFBapooLKfNJQ57i9/drzM7m9PMnOPnN75xLttTB36OeoOXpX9hz9z3jHWzm4VAmiEP83WdlPkf9Hs6raBdyolWvvKpJ7YpshVXzEmmynK9mvobhWHqkUMRZKllEj+i4iAFXpl4ZfdIGHE3cvr+GtwVUs2ioEVvvsMRyaF3bAdS92NHxbbVydVqcfpPoNAMEEgOGMyDKEKxKHtOJ/7I53cNrJbcvlspUD2u5ZXKyHAtPbChBDBn3a95ezO0XnDw3NgIy20wRrGnlyXODro818oy+2lL5cC1S0AVNuY5hOkV2rh48YEkK8Gh4II35XUFU50NhPm9rjpoEp/iMNzNXZ4I1xZu0yQlVd5ueRmOlz2CiWjlGS6VuY4S36VR1n838QDZaLzSisIkPn2woZOq1a55Fu4rN8HZsV5pEn/hIqGFRd1cPz4MgKHv2ChHrRx36kqvYkxz6Gd3CYjcwWKo//KtbRMbeJC2jSJC4A2dB0asiB63gb0swGf5hnYd/HQl08/8AC8wK3uWEBH6BeL5+hcgp/UGQRS9i/ZBnMY7G6ie/DL9X3EGhVuRbfVomH6sg8hrFM65VVQDtIz9JqZpIEcBP+zIavaHqQLcdOh6dFP0J3LJHvCtY82tX3kvF3R8w+6SWLNTxGdllz+8bCiydXUkME7D6+eMAvq7TgmrE63WQfXqA+CJ6uqIGJKtfx6Uxx39OkCz9iuQ3fKIcvdZynKlwYP1je5WwCRmYW0bXk0DS1b7DY748Qi71LlgbNzc7YF3yjRntvFs9cheaZq78EAPKOmcNccJXKFAto0//GmxsyN7Xsri4kybAZDg4T/8bg0TSdMXvscgDU69SSkBN3jHlks84j7BAb8F1UUwzgyD9mFnn7JxYQnHmeGMUnDihrQTTtLmoDl6cNIeuvsJD173geV/iPOxs+zuZef1zdu9cDk70ueYh77TR6XfXF5XvNYXK09wel9fo9akkfws3cA30ggzBGmAxMEjKta1S1FH14t4o9dAcRd2SKBQVB7XczOQCgfE38U6TvhjxjTdyEcIlIuzH7EWfEFpheyXJarm4G7bDGcjYHOZ8qNENejDXDJ4egGdy6ZnBae4ncYDWGZ9zb2vxgEa+oriJWKo+0O9UMXtYdE7Y3xTKWxNUsib9uSsrgZlQO+sUyyCXJH1qCSFIJi6RYBkn0k7YPaJEXSQY3SxtOas7wP3I7v4La8x5TbZsMeblpCeRFiug0wdaftqDaJKLf1kX00RkQUYZSnZHANtdHyyj2f9Vl9dWVLKuDesuqIZUje8ljXkIeNzKHFupMtDXATOTmSElziphJclV1H9B5LO8vcWYwfUzXFZlZ0Cy5SftHx0CshZam1V4mxshjnhtuAL/VMGfnmznbozKnJb67UVWfA/VOHmHpGEVInTe9Hi2DBOmFnJKLmIfjZW4+LG2+QtWwSJ9L2Dshx+SNKbXUGF769MllrxmEtmNCkUWqsjK2I53NGzAsq9jKZO5Qp1tCboZoM/dlDDjvGazlZT01xj79bqlE8ak/dNu9mNjYuNqrrZ7Gw1BowAEpdQNrr/bbO2FtkYlVIQ0sVjxUPtnLlW5KN7AKzao2aWB1fCIjV9y83mI2pHrOSxf/wxMZ2lifMQ5JaKap9IA2TupiT2I5oLK6SwzMOALMa5sAaSGProXazpu10LfwmXbowijdWTRXgvAbUDlA7mzjqQ2bsW3Rs/HIDca8jRfQcwFf6Nx1ryBS+BALHDi6Ou+q0k1Do7bu21IkLLJyrdUn6/eqC6TMJmP0QoFz2WIYa9y0SQ+yig2ESmngE9Xb0HQMhq0vrembqemUyr5edWXTSas4erbg5/1TTONCg8rSSOc5l2Usylxl06dcnd+a/reUgGKD03VRLVXVDebnEkOF6M/fVtV15ucbDdGpTpNR/fmGtLVZjtH1asMXTl8qGWs3wSu05IqNpo/RYi1wjh1dlCsuIJ/nAZ0GLba7I38PGtuyNnkkZ08Lt2VsbjOt+rpfsXVFn/6SU79RfAvp8v0Cy42uHOl5DY77Z+X+JX5xv7YH0+ONWpPt/ab1vwFLaBdDbjoAgENLvX0NfFTVlfibZEgGGJhBJhAhaNQIKB+iiS1xcA0fCVEMvpnAhK6AFNGdZt2urTMVbZJiJ095vTyWrmSLCpRW2j92012qYKOQNhTWhD9UEKnSgpW1WfvSRI1KIUpk/ufjvpk3kwlq2/3z+zF57777ce65555777nnI721cle70ggEUXzwRTrGqvl6ZYFeOVmvLNIrC/Wqfl2dqlfO0Ctn6ZUz9UqK7ayrZXrlPL1S1Stv1ysr8aCM1nmVbr3Sq1f69MpFeuUSvXKpXrlCr1w10MOEXd8qJN43r/6M6oWyP/vmbbmo/1DGYA72ypJTVVQWwyrZMFlMwEAKWtyzNgtlog2VHuMj+j7PcLZgoIVX50Ni3e/FQl9x3H8k4kaNXBdq5OoNPrHQayU5OclLge0Jb8vLShvmRaYVx0sbKhsuNbYXsR/9eYb7BSYTqvhdaElNIatYwwwoPDUyEUuWNFwiQjMM94uJIiVYZEayiERmrKEASuVze4XJ9ioKDHdLonAhFF5YEEgUHkz6mIZf10efgt+oS9yM2sm14facOsBy/PV0PyMu1VwDEwvlwbFDcX1ZP1nE6xVOW1YHZ0Vz+FVfm07eEtCN10InirJn+0SFU1T6gqZr43S8iUB3DCdhCENwvFuLhoz+Ex7DR9cVXnT1NscpGgoN9ya9yo3DixJdOB7XOILGwnyzZBP6v3QDMlQaD5LwQznY20Rdc/0n6n6CsrQyWwsvKtzCsyR29GELAWihxHA+qZd7sYVN3MIdjoCxcKp57HvoF9MLYxWkEeA7BB9GkbVaWJyP0nls4Tbt5Oql/hP1S0R5PtZcCTVXGr4n9MVQ8+o5eKx3qMbCMrMOa4W+h+YFiCg4Rmw+QCprfT6TFq9PsYZVxotf6ORxoji/MpxxewVpkF982sl4P30X4R8V6KcDB63cpT/kFiGnPmcRvgZ84tt4VUTOoaIjySLi+RrYCeDWWbwSe7hQkXL3X4nKQn9liUfD8CXiNl/shXl0Z9z4n3jJvynV34vL5ue4BihnnFKc4sYG24dRcKIdRuRrotILs/XbGLKhJjzsS3z2j85A+G71pijcI45me/mybwCnQo+1t3lrV9Uq5pNXFytEmV54+TW+UF21Q6RXkZDTOtMHw70ffxlAn5VBoURagCBO/s1um5Seg/G/vc9mX7FqcI/JevQ0enrr1Jf10GJFeqLL+tEL25dzFF4DK3ylm9AhfGSWWIOapqVLzkSuT/GPg1F+svz7I3PQMuS7mKe6OlibXeuguKkHJv5Q6b5mQIE=
*/