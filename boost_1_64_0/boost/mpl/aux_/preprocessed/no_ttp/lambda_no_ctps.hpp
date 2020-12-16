
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
dO/UZMzDXyc/UHrHwrOP18q+8u1XTul9Xsq5S85pO/hHMYyUnbaxvI+gKVbEZtgIb8GmeCtGYnMchC1wKLZ0ve9Bzjl4t8zf830H5WT+FbEOVsKWeC22xcrYB6vgKKyKdgzDcVgNHeWQcwYO91OONrKc9lKODlKOjlKOTtgTO+NA7IKDsaurHHLc4zg/5QiX+deRclwv5bhBylFXylEPTXgTWrA+2rABdvmb9Ur/ZJ3SlapP+rt1Sf+GeqSrXYcUNaa4YRQxg1g+RtUlqaSSSiqp9O9MV+f+X3sr7+Xp/+/pUIP7fchy/99Q7gnrEU/w5TR7m35PaBljnmDUFh+XaI5JTrUE/B7fJcyD39Nd7+t9O4Lf27URBu/32e6V5Y+W5ccTj/PZKN/lp1gmFKQOguXz+75dHy4lwzZrnJ6fHMmPzZGffPOYI/f0PbC0uIH5Wd7xySMv6w8sj6X0+T73Lp/3GF4kw+V5z3iS4991Iu9o0swg4+Ld45o6x/V3j4twjluxwzWuscH/NpFnMogJFrPv+6AtTdzPOwQFM8ycZb3lWketZB05d4p9sh33Epu17fhe7nWkvQgisPXkP99kVPItz2rIuLExiamM5J4rqNz5wiw/yPF7uPU9Wa8e729Ojk2w26QMzumPBzmOg1c9ps+R6e9yT68/+zFWpnm3pkEf3uQa9t535sh6mSjrZSyxlPJkbfVeLwnJCfaCvJM90OMrXN7Jf78sfxaxnM+m7/JePo40J/+95WvbpA9L02bm+f5zecbGaz85Ivk5IPnZJ/mJ3umdH70mihw510nIZcjTST/1UGNrM01crKueyvO5oDMXWa+HizoyMFvKkUGsZPnh293lkMe2/lYZnOetcDYG83Dt56mOYZ6kkmNUnreyx9r0aa7TpiEYZprc9W/lZT1o09gS7UkWWfYZd9nz3ad2XZO7HvEZ8r3bu+zSaizw96z7lJ1y+ZTdUPCyn/HZ5jkBlPMMrr8K9ZF/sXcvcFFUewDH11eK4SNdERUVFd8vRFRUVHxjoqFivigesgLJY4VFMbV8Vb5SSzNTK3qZlRWWGZWVpZWZlZrerOxKZWWFN1MrK+ve3yz/3Z0dZoElrvd278zncz5fdpkz58yZObs755w5E1NPeb/uId9lM9p8NvD8S6HPNUofleK5nXKEr/J++M8d2sf8NP+27SOn+hfVXHkzhciO0962JGn11sbnnzvdKPGz/Utf7fTf1675uH2/lj66+diXbwUHL3prQm7q7VuLeAa1/X1b0+U/Lhq3aeotnSbdVz/U59Rfvx20fYby/rYj31310hWb44Y+2H9KzYiBPpenHTTMJL/hsKu0r1fHLgRlGSzte0PQD4diRxyG59BKiJb4N0j8KzFJ4veU+L2wOfbGVtgHO2EY9sS+OAD74SjsjxMxHBNwAM7AgZLuRZP8rpLfWRGEAP4uknRzJN3Zku85mIpzMQtvxPk4D5fifFyNN+PTuFCeA7wIX8fFeBBvxWokugyb4XJsjSuxM67CXrgeC3ADHsK78Sjeg5/iJjyF9+L3eB/+hA/h77gV/dmnbdgSH8cgfFJd7vJb4rhOue+Q/X8GW+NODMHncDw+j8lYgHPwBVyPL+Nj+Aq+j6/jUdyL8jx/+U1CGUq66uf5t5J028hxDsL22BY7YzsMxfY4EDtgJHaUfHXGadhF8tcVZ2F3nI3BznzIbxNcqZOPzyUfX6AZT2Fz/BJ74VfYF0/jYPwGR+K3OBq/w+vwDNrwH5iL3+NteFbyscckv0nwhOSjEe6UfLwp+XhL8rFf8vEOtsOD2A3flXJ5D/vj+5KPQzgGD2MMHsFY/AAT8Shm4DHMwg/xIfxIzuM=
*/