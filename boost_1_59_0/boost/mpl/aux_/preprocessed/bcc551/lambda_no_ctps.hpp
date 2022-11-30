
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/lambda_no_ctps.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      bool C1 = false, bool C2 = false, bool C3 = false, bool C4 = false
    , bool C5 = false
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< false,false,false,false,false >
    : false_
{
};

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

template<> struct lambda_impl< int_<1> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef typename l1::is_le is_le1;
        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value
            > is_le;

        typedef bind1<
              typename F::rebind
            , typename l1::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<2> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value
            > is_le;

        typedef bind2<
              typename F::rebind
            , typename l1::type, typename l2::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<3> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value
            > is_le;

        typedef bind3<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<4> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value
            > is_le;

        typedef bind4<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<5> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        typedef lambda< typename F::arg5, Tag, false_ > l5;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        typedef typename l5::is_le is_le5;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le5)::value
            > is_le;

        typedef bind5<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type, typename l5::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

BOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

}}


/* lambda_no_ctps.hpp
CVtm/UomhpWvhSeH1+e3ORxVqWjX0CsmYEaBC1xs8loYe82N6VdQnSZBhz3AmZ3Nn5RnEOd0SKDkWTzz6Zn1gEJPC5kacwY+v044WR6DvmxQZZ7k6Tw944aT2e7FpcaTPNFYPdT95SgzXDb2Dpf7ePZOmSF0zcwlZFmFNrC745Qwso7HiO18vzdAN9hG3KGbkSKNGAgE7iVIP4guh/lx7qAINY9zYNsXJYIu/6wNF1ATza093daWvl/pjiXesJcsGLsTnMbuT61sOnFJapYKHRYONKpa5o6cSqS5c5khUipoYaxyX5Ds95GPSVsVc70YnjWfHwh6xq6P37D+6b62E5CHP0+MeuHaW+HbbLQQNPvEfAxUl2NHHCW8CzvxFgmnNVO0qDhdKc6IwB7tB8x/k0Y7gcy/Ch52+rboEjnF6Tav4b55So9eUewgl93IPiI1DY5ErxDXvx+wjS88Np1OfCi/JDWr41z+ebb8bk6/nNmCGKcZn+YwtzYf8p7VEz0uuWPtdDUuI4+NghK63h0THAufKCAS3Xw5VoKBPp9LWcW2TK5Vdb4oGbZ+sU6eHq+ZHNlBVUAXfg1RvbdRluW2kUI7n5weggyB/kKvx9GdgakkjKUO2uRoSD+5+Zv0aKUMSoYeFdAfy8QPueGVtf2D9CcWIH2EkCIUzzKE5s8Odcs4czzVC0H8eKjgdZ3i6uXDXYQzK4LN9LxEm1iszWfhi+cmxQ48g9RP0H0jOj1an+guXMNt+XipepGVb60iir5gdI5FnVLg3eqABT1g5GWsmMHwdVgafncuC1yM2DkSurDs9Bc8WrApFRVO6m6s9rRQrAegQ+cYcrcUgh+90p75dW37N0VMNXM8oZniD30+rK0koNvjZzn01dNfgGfZKWjIBDMQhazHQEZy84VKMjrG0mqzPYMBzv3LPaJU9DUd+rh/2LqvAd4vuuzgX+/DJxk8MQ7XPR/vXScpoIWJ6lYOy5EzLtgHlqxeMR+aMtz/DtJ0Q0sgs0NDJyjNbPpetNXGO0zIxx+tIgRH95lv/JQF4XMv7ih96cCfqp7dLwqKIRdMwXmImGKEPQG/k+RFq9cTPZNtnevnIHOtrUWZ7hamKrwnAJhqagKLeqcriDk5dyX1XqoRjBYO9AKm2QqH8AinLf5ZZSJC4LnAe1PcLvy5J4rK0s88ESB42IKweqvdBLgW1mCzLMYzslCHQdoM/WDIUsJ7qrxNQ1DwYImM+PKuB6hJy2lFXZG6O196mO4j0iPEaZ2zzeOJVEy0dE1y6X/6UIVSsKEYvLFzrRqbcac7RHWCejNNDT6sYDnvKG6IR5KQ0IZwlQs1MAQhXMOL2g09+2r+8NUIarklQLTPaoRtHULmiHtBeBOHr395S5PmXVRSN5lUqRI3PJaLvTD9sor+oI8pUAY//6jvXZmuWZYWjuci1O2onKqGd4eIYyoNssy4gtjUCr8ge9EuXxmg8fiYRLxvw0mPBTd//orhZQzqvWDyeXYBDfjQEr4kfDSTR4eXe0hJtV9FGZdIGkqkYtgjGeiTbdSi2e2gtfI0uIz1tIO/x35iX27ssfqGqqMwbEYo/3Kthw/Adn0p5sb8d/qI8zHiYg3sM4YRNECXiaNy4r+P+eSwogoTwAhwsnlL/LxaGxTPCbAXGmaSZri91CF/NDaj9PFQ0qK60Sf/DbH7RugwJi0k/+kJzPnEumd1qRMPTEAVtJk4RU5gyiyD7mNoNl+d+BSsBjY3G/v9PeZ0flV982J0RW0681IydQP9V41T7qh1hC96r6AvGRyjmo98F/2CoLW9y5tBf/yE3iWpYgEBM+Agciswp+YJNdpxkQqtRrbaFqbfBH9fzrV99yb76vHi2Nfxzaf56ktv7Ib6YqBIvVjCoJkBZjTnhW53Ipnrgf72bXrG++LmSP/iZ+2rB9HV2nfX48uVyGbASvTaW40SJnMHocsvUPlgzRNxbdPMVnj2zWW/YXyN/AanHI6FV4oKqLXuEcw5FMu4zHuNyNXHbPKwSpiB0RV7LZNdGI99A2fNs3dVvpjHpRiSE9qauIv0qQCvPxZeIzn+7Dl0Vbn7WXnbJmYLLrDLDMf0Eg350Ebihv/o+YURxrBoF6l7zYvdSGw3auyr0WIEmzeSPW0tcWTksxCaieZoBqsxIYDELHR2K4h6e/H2vb2nuL2kSvkA3pBzIOdYdvvQg79MI8cL2cv3LtS/STb+BfVG7MXIVa6oPt+2YJf5snfwa3h7rXS7NLZuzGVXuOtfZ9hyHg24HCewY0Or7c/oASQHqidyu6dMgL6I2DpKA3iDJ5/pY7ro2sDlTu59bLBhOHcOpmdgHYb9ze5quZecAmkRUK4Nr08AdveZWZ1/WM62d+bqrREQPcxz/d56W9cLCIN1B3I7tT7KZVOb3J8gEifR7ds4PiMx9ji5s0ACWCB5dg8jHMzLmfqr4OnBfR9IN1IwO1U7is6F9Idzj/ozgzVDiDp5txEOpOwY1xJUMrQcp+zDNWz40z2rBhHu09Msj10T22v/HqFQBt99P3jdfszTKOfUwtefd4zhAGr4D2TRHsUQpOjBu00HkPdHjAj4m56GIf/Aya4jOAQbXSPZR7mv0Wq9aytnWKdd0VW8amD1tdg4/3mcmtJAzgT4kkVTkFC+rZ6ba/7k0bBJNyPcrmy7hpdrQzeFi70Y2XoPPSay5mjHHeBbikYUdrcuTAInMkU81qMgcnyccfidGPFExfcDpssysyP7uhs/w5PLA/rZdeZsNxCAHdnQeJFnT/vX8JTWHTZ9INEdt0P/RlyvQZuPnz6RH8D80uT7nZ+NxI+h075Yej/Dn6iNSYid6xwZDYbE26FnPEGve0Arrhjyg8939gcgeKie2tvh/J6H15AUoQUkwUx2RF7uZzejmYae2GLfefbIg6EvsaA945N/W97hQmSWakVIDlOwNV1FZj8A0+cTML2A/rc9ZonhfjLpv6UJQN4mCcFTTZOiHzeTGFRL911NRKXVKkLV8lDLh4hPx9LFq0XTKEYLVLhvFyD8HZLwFTA3jiAAcNAfyJ6B7NkM8Vkg9kUBAomwAXoXk+ATGACwDumzPB3Qa8CB8q87TZmgOCtWj78XJjaj8iIhcB4zduKPSfn0DUwGC7u7pwAwtqWda197QNN0GolGIWPsgLyfTIRxke5k5BFMwizZS7vALFzVFWAvAEDYgKEwMRALW76zck6egjvItyKDP5XZJjFVS4JccfLsYFexj2+XF8gDJ3AvhR7xkTNwubenQ9cmTOXdZvk4lXPD5soCDSGwoPu2p78doAlGp54n8fQbRFW2gHfzuehRE6GolBBb3eJPBIgMsieAx6plRPcpAUDkuxs8V41iCNCD0JotUx7ytofxOQEvXDbM87scGUow0aVUPgIq04uBduZ+bfcH2zV3QgEcD/eqL/m4abr4AnQZbvdFms3re3CNoElh8PixkoPM1uk5trLqNhQX/Qy5HITYfXYnUZlIsnRZ27ci7FPduNdJqMgId7YARQGdUZb4uBuqo1vIoSYWbvUNBgH89uHQHzeZT7XiGsXDllgtUh7jnaTBcoju4mOpXiRRH7hjp9W+cXq/cqg1h+Tc8/CCduxe1BerGjjodWW3rKA3WXENLdNjdnJv9E+CsCbbC/WvFCGpjopQQiVFl+fh4wz4ZqoqKPXKjCQR65Qq+SKHxhI7OP012MtY/E02Ec7o8vH8R8PPxPgsCFoTx7TUjuRs6Za00Ci2zqo0g78+Gq9QcB+M0v7ND1dT4zq6n53yZXrLL2VjtkPFn2bnH4hmnGqxnLLFXPIWhqzdbKsahYhI7SV/YauaMr7Y0TPy1ZGW9xuPiAqRM29yLBNH1KdmURBdiPHdhrRJSYR61CkzvsZoQPRmL+wSHdthLgFuViQ78pN/qH6aEpdKENs8pHRUor02MqNXGqBukL3QqsuRzVAG7G1fao24FyV8sNxKO/KHY/SF7kunTOcnSs6Gzs6LDguGrqqrTl8eS8AKwVVZxiQ8D6aDAzRdtodS1k7LffyoLqZ/jtyxGNXN3WkvglLFUWzloU1FAAAs/9PR1wkCPu7byg3/Ui7Wg03khebTmGiConvqpZesceWth9s7l+RkfWmQW33wjIfyZ5trvlwxnBrqkK8CDRHCNHSA+SoXBY+PiyeokDCFLDmDu6BnERIvR46z1uAkk5ynUw6bWQat2j1HLeWt2yG3QhGJ549HNGkhatJbfZgah6v++xw7ZnFl2ApMn/4r3PFcCOi6CwyNNtSAaRbwyEl9sItbV1BRwVf9zFbDbXMZrWnZnpWcx0Q672MyGd1KBQ/rkGWYSlvtBkTbGawQrYbHoYZTev+4EgVFLh/+qjig4LkZsNi8ma5s5mJHUaHW6OI8t+tjkEpZulcm+MCAU+jkebrnZbmfq/KxyVPzRbMxrLqBMK4dtmIaX/9EpdG7K2lSpEs4ValySf8yvuQNs/AJecWUhk603ZhAIzmtVtaCGWVoObXxJap4eDElP/Vwdawxa3rG3RzZKGEKI9B7VjcVJwXWZzR1uUzFacLvmpwgAyqzUl6AMpi9PH/hD8ggIdcxZdZlzeCOeGLX7rzx4RfKRf0wJo+hlr9EtmS3NK1q8or5VwkuW4g4X+utbX8UGyJx4E50w0YN8uO1y2inuYoMDm+WukJIIdb0yq9klCrybkpIRWBK+8UL6Qp1OXO8EY8yDV6+6g7R4lBSNrjFLXOp1v0Z5iijjgeRSuuPamnOIV0LMwZ46tQ5fInr6D1iyWUP9JvlqWhFO/MMiyvAgHVuDfJlILFC/P0+B7kr622FW6SM8fJmeZXdAdgIxlXNpEwspQCeYPFeC1dYU4Re7Ey8/xL14XRzKHVy8gqNHO4t/tHCUKr/JrWEihJvI3MhN5HRaAd2ZOUgUK0nemo1fbsY+qOdEDblc40Xd5cN4XX+GLX2iEAn0yfl80nTKWoxTiViORsohxstxt/JpuKQ5G3ffSpavthbK+vKBYhqd6XzCeR6BgbBCbz5fnHT3Ve+EI47Rpro8H5llLv31v3EffHqJCBDdYcbDPFiPgaEe7rWUZKHegphKMSN2ZXzjtSKb0cBM+bfEGCUZ0QOeYLtJBAcXxlFj+fEA7KWE69MxQk0wYL86znK2mzxtd0GbOT6gB3+7C9jnPVD1BoXYiaBUm6GY8YrzFulgGEQOARbh9lo+e094h5h9glfJqHsnMZIGMwzBQ0YONg4IvKveKWE+wCz36mfFhQLvTO9BW8dyg0gQ5u8cIYxNubcojKROQiCoLCzO84FOwxkUHcPsDllCWxHLAV9qIUWJ0pjiH8G7CP4fkVYjqWgEdIYwMFMVSyORMHPv9hYMq5vR8Gj19I5QJ4hnLrLuQZF39iTW35moSijMB/BxvnwERt9z8nPXPuHZzcRPHV3XOKDgtMob9ztiZbg+t6XpsH89frZVPrDoS0Oi8xod13lGHTx/r1nI/+Yz7+c2xIaRgNVGaZcCp+K0eh3U2cQNFB0qZIcr9Oc2xFxBPV3dMxvAOEW2+Cf1eEw7Ip5DSFdessfYXr+LX14So5gstNKkA4sFjymyJMftTgHkq4LJL5sa2e/WBAoUCiGJ+gKcsTdksRgfkDCJNxsnwTu88sICu5XKHqwAwPEtomigGScwqpNQHZkTIn73vwjnLpDDWHL+XrfbYKRnX+z2lnobMz7S8chiMRdSi8Yo231zGFEXbiNB6e3tTF8LMsKlFoDu6m80jb03UWJrEueyUEB/1gZZ91IkIReSUotlZNit060JZO2oZ/aVmHb6fE20pGJ5aERb4kbSsJc6VwxqkwjDemGSEVGFneBE++3TDxKiFSy4vY/IYrCWHNLoG28QAdfebOJHc1OFek3OSvm7nRwPNTsy3eMIMrNGENBCurM+qNQqCTFiA6wup1mlFnFEN8ZWna+hUPQMzeuD+a2OzOQQWWE6dB44HZgsMvyDMwQImUyucsAj0XgPUT0yHdgzDRnOG+GYfr7h3wrJZ4Vbp9oGQiT3AaHWuh0F8lvzUMXbJmV8g5UAkVj/fZR7A8wG+0qq4ypg86jK3O2uU8OJmRa4+CPc+IMijCoOYCH3bFSYtNmekrf6g+PFGnuwhUq4xF2/eCUo8/C9qbI4II6EA8lF5H6eruguwzd8ORDEAenUhsdsdAcaMQ8eGmxvNu5ZFJLM0kpZ2dp5XkP0bpQ6NSWR6fGsWigBn6oxtO4AseIrKPcEFiH6z8nTS5LVUK3PkwjDyAAxyAyeMAmtE6mIk1Ro/vY0IWl868mvxQzWYrswcqogUKZyQ8MsKMpuGaJIQLlduUGClLFJr11RXznRcYBeqQR3xSxqwC+p7On+Q7pvJVWZ5U3d1IoUSVKCNLHxChm4+GTeVhbY5LIKa6sUKhheUWLDETXT7AUTRnN95FP7bR1G0bTxvNeDpnucuUIfFia6aRXcxSMj1RZcpt81SLeTYUGlE19RjlElHBR83Z2wmJE0rARCR9vLzg0o9foJashITjB919IDgYZQ3iRAxuCtT0LjDjIBaxQ5PLWEwOtCz0ECjH3lUfdtFyi0nFTEgyS0Us+y3emueLCa65FGBD0gtFnDma6sbhRkG/TB6kQwzM4EsqlJHopL7JkTgnogjAEd3WsFnoJii2QaU6FVNG7ZWMI1iixt9upHnj5BsOiBywv7kFVbZKzSYdeQHtAck1tkTGfKXrrN9+IC9Uy5fs/IYku1YSLemAIP13hpcMk3y3lRbzCUYmFUj/EF+Umn6ZHWnAgThUNqEDD8RsINQhxy+QZaYopLvd1PBRp6DnAgriQk6Y9gGEbAdhm07W1Xo7UGofPZhKjjUGY5UzndlkG8mEDxfd/JFYTRKhjgV9I9Hzh4VqoK+fWDoN/yslzuRqqZJcBSQsOIt2imaIAlemPWHaItafX3zRWSzWeXMxqQiVkfYqQrgxkW4CBlX7QbHFDG6+a+HC1WAYguWzczh3UK+gSLW9vGT2MkWzs3rzpP5LlynfBeXfKjmHpovd9vWja37YwHRhLyi3YQ+0izeFa25olpGCYqmNsPNKp9rKxUU8lYDCtiCQcLNYCCyp3IBBqfDPtBs/Tdp/DVkpJIr8vkLFxVWVQLGMolwwIpSN6YqBnnQ50qqPhO2rDNYvWunrCXE2mYtWyx7qZlkuuLFXhzyQ2nI4JMu4vC6RWV7so/J8HXVZ5BYBXxl9ES5m5aUZXNmWke39arCeyqlSX5zGCHj4sPmLFGKtK5FE39OjQKoPzIgQHuctPcSByTFQK4irEOFv7JloqwN3EYQi54sFw28PXPUVShMsthJkc2BcnWEU5MiI0ujeH1ValBU5KNTS00ot8eGyjyvaZPd3KwkFkruew+KRmXkbLi9L7C5rizWRRgSl50xYMQHSTDQ7pvmFgkzIvMMZEU+A20MHfZC6FOjcuNnRuR7TmAGqGwlLBIfjpSkN/uhV+q7UYt/+WjeK2QM/jc7RXGlD3BvcuoMMIe5/1S21epj+sCnva8ENLMhCK5PyRxW1r6lWC1VmcHsQfaZb8B649N6BhfDr+h4FVy8B7X9jzZ7PQK6CjjqYpwGMU9blL7LZTQEWEQaK3G/8mwflkUIHyjUSDm8cHwD4pxo9wMFzonT/JNt6+btESOzJi
*/