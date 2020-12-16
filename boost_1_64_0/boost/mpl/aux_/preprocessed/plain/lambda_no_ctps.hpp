
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
AuUraTnFvKOV9GWmJsk1zDL/Zh9Tm8/Vidbj/pi5//KcLHW8jHFlO3Ifpy6rvZ6n8X9liJbrQBQhmO0YvkC3n5jPBC7cczTW7A9ZFIzlvCjTMmWa0/Oibj9x/rwr21rXJ/d5ydMEydMYQg/iLTHlKTElOXGReuAnZ7j13C77t8StPzdIf8yN5dv00rdfNIawnE+KGjeLE7NxqTl6NW4nN+yrWBW/3wxS42pKLMpxNyLV/riTY8Xm2Tc1w/m9XeXXtufHqq9tj4eLX2v3cylrpv09kHzlzrfJb1oTU2ITpazjCL3Ib3mqJb9q0/DkvJw4DhCXy1ryZP9srLuvy1JWquuv1ygdkr0qaTpC6EOaohZa0rQoISvV+nBxFc9N5rKW+3jGtdcx2Y91zxrOnpmOKutIXmQ5d/y9rzqebZDzgpEyTmNlRsa3KXnQP29K37DaPqnX+pkS31eu772wr1IGiyxlYDq1Keco8yFuSmi131dQ9sOsNKfXetlm+mPY+bFuPvdqy+iyv/SvoLun1383QHu9X6i7LzZlUK6LUi6hTe3Pd/2V62KaWi5JmaaOfXONOe7tq/N19/PqCmT7bWRbhBBvT8a/VeLR7cM51n1YDaMkrSVN7fudHqxsw3RLP8ycnqcod/+pnEssv0uOT16qdEPtcp/MA1ln9iLbfvbDm9n3AX0j8xldiFvpINmdfr2J32mf0EMkPQea2ZfFMJYrcpyesezVbpXBUEmD9hgK87cvgwjlOuI8TrfzPtSFvJf42+d9NMuV26Rjqrq3K4lwtw/ykZIGbZyhze3zPpb5Kp3E6W4/4COd5Ft7Hj/sIA3vt+JammFOQ0zfkIFxEVMmxBkzjcqB6/r3LjjnEL/1ueQexpUVKA0eGbU5Z7RvYV/+vZRj2jYdlLrr+e8p/aBrr6W7Wtjn9xPyG2UTj/t5LdHlNbuxLq+aNLRvaZ+GvowYbdOgbm139jHy63h7S/1Lfy9n9QXdr08Z3VCZ3qC83tr57c4O+fZQ6FN+6WNTnNezHFVPmR72Q+dO0d/nr9k7epZ/xfUb6Kz4rDr9yMmYL3antTz/66biEe+1e/KC877OH2ik1rOM2j7y/J600KLg8te/unx7p2vXR7nj+p3u1+N0XH/UeT3RPWq5FT76wFufvhoSsuLVqXmptz9S4X69zI/U9eS0WPfdislbZ63uOuNBn9A65wyG19R6mQsHNDv6dcBn594c8GjLyLlB+c7rv4YFK9PHjnhmZFz/X9b6PRS87NOcwbnO6uk6q1fqrB6q8/qjv6rp/PnZ184GPfpF/8A/xKw9cjCm+bWrP+qs/vEFta9defeKfyEUs+6GWChH25NSr/Rp7ITP4HB8FkfhYYzF5zAeX8BlWIrL8UW8C1/C+/AIPoBHcT++jC/hK/gyvooXcItB3o3ifkmXD26UdJVJul7HJngCu2E59sST2B/fxBvxFA7Dt3AOvo0JeBpT8V1cgu9L+j7AYvwI9+IZ3IdnLX0Ry3tODJL0aevjjvaiPi2OwdY4FgNxHF5AI6FAll8ry9+ASbL8AsnfQin3RTgU0zACMzAaM3EWGnEu3oS5mIUrMBsLMcfSX5C8X8RZEq+2v6AlEu9S9MNl2BJvxjZ4i8S/HMdggaRjJU7HVZo+1YslHt4nEo9tn+of1iQePIud8GMcjp/gWPwU4/DvOB//gTfheVyFn+Pd+AU+hhW4H7/EcvwKT+HX+A+sxC/xG/wGL2Bt0vUt+mMVtsTv0JR+eR+I/g7Sv1PSvwsDcDdG4B6cjo/hAtyLqbgf1+CT+AAewH34FD6PT+NRfAaP40F8A5/Fz/DPkv7Dkr7n8Qcsxcak70X0xSMox7W81+M=
*/