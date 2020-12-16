
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
PIDvFxyGZ2AONsfH8Uzcjy2wUx9yGIzCVrgCz8Jt2Abfxbb4FbbDavTEpnx/tUdv9EIf9MbueDbmnKZxWCP3yaeUUMooh9W4rAoVKlSoUKFChQoVKlSo+B/HqT3+PyFEKzFZTH6sDf7Xw9j/D3bH/zdrcOI49kGtH6qDeQx5REhMOptJT8uqefyaMTXrdvfaXVewFR7B1Xq2bdtulsEYw4syb9fTvj3djNuu4vE8wOHaDoxByzzVduPk9uODjVinc5xjmUshOYxjptjGYeX2IIexXy5pYh0v9POov3E+1/MX130+Ytfjl/U3jljX+YLrOj9yXccpXc9r7H4e4fZB2vovlq1a1+mXG3odevuuKeN7XRSvq/O82K7nQXY/X7bMF8Pfkm08sLiB43wxZ8m4Y2tsim2wNbbD9uhpnd9E/nbkb4rtOMxv4sP9WmEP9MGe2Av9sB/2wggMxkuwH6ZgCC7H/vglDsAhbHsg3oWhWI1heAQH4RpkfpMa5zaposg8Jda5SUooOynllLxQzvdH5/lEUp36M3dRLHN+hFCiKJa5PPKkr3Or9Hdq83W0pljm44ii5FAKKKUUmUuDOTQc+0XzKGsoJZTtlHKKq3ktcil5lELKBsoW6U89SGkxjPtTLHNNRFOWUGTuCIc5I/QU57kgcinO8z1UOfXJzqRkUOznY9hMKaNUUA5TCmnXzaGqr1aFChUqVKhQoeJUxWnJ/7kmVH0d+3+QmvpLnl4keXoIuWhLDMQH9NrBFJY83Zyfe+tqPq7aOT/PdpGfp6RpGbpcZ03OEUjPNmorJQe3y9ntc/ArHY89zpHbK5xy+CpZvtLpGGEO91Y5/L84h7/NlMNf53P7LR1n3L499K11Dy4tWpN2enL45Q3k70H+ToobOM7B6203d2p77IydsQv2xF4YiP44CAPwKeyDwdq2cAOeh9p7MxDXYBD60B7BWIj90LsRdcCu2B/9cQD2x4E4EEMxHAfhKDwfx+NgfA2H4Hs4FD/CCJzGPhyGs3E4JuAI/BRHYgWOwu9xNKaw/8agEcfilXgBVuM41PbLeGyME3ARTsQ8nIQrMRJb0p6T0Run4Dk4FbtgFPbE6RiIM3C16nv4R/c97FL9DipUqFChQoWK/0Gc4vw/WCvpSfEDQupp/P9namo5jz1QzmO/nBfRAWfhOm2cvqnk/8Expqem/0GrkPUayqG6us8DmJImcwHY8n5L3wCa+gouNSZzzoP0DTxMPbK40HlidqrBcj6ytzw2Za4hwTLO3xGNjeScbekDeERv60MolzkDjLK8R8b502S5Qm6fG2Q7P9lUH3nOHdZru8812B9bkNGI58iwnfe9Xs9zpNj6Lcz1lHO4Lc8RaOuH8KYcNuW1y4b/Oum6ob/s6bvn7soHJ9220Jx3+jSQ/SD7R4uuFE9thczl1wE7YBf0xu7YCQOwCwajD+ZhV9yPvliN3eQas3psjt0xHXvgLuyJ36MfHsJeqF1j0R9bYm/siAF4FfbBPOyLP+F5eASDsKvksX2wHwZjCIZjfxyPA/BiHIixGIovYRj6Sh47HcNxFg5G7b1UQc5xmNIsTOUeKlSoUKFChQoVKlSoOLVxOvL/hHrM/6vt8n+95P8NGzP+j8d5MY9q89g1sOb/Ca7y/4BaHA9wunJ+7T4+kt9LNaUfwDHvr3DK+w865f17LXm/3H6c0LbLk7rM8X+33J4gxyY45fwH3OT8vYO1nD/gjc9WJsxbk7Pqs7fadZ3+7HeWsWZpe9knhMNYs5eMNXtjezwbz8VO2BU7Y2/sgiPRBydhVyxCX3wau2Ebyf19sDsGYg8cgD1xFPrhI9gLn0F/7Cy5vx774DDsi1PxPJw=
*/