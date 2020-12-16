
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
5rbc81pJtDUHsg6pQI4h55C4MualkOyyxvmkxk/jp/HT+LH//HDv/5+Sn9Pg9/+7nv1rOxrez//TsaMSh8uTv8Tou1zbq8ZCsVBt16VmOS03i3cFOfVT2rAOzfm/zKypGUU57v/PykRdf7/giDjdxrBxSXWvt+cNg8489pF/uvX/uhPtJY8mnUxpUCd/KUOc6X+iKmMS4YYxiRDFs/p+7Ccvl2dYgwOBxkx7O8b6fsJCm2f1BIW9QOKT1cTZP6cfOc/6nP6OdgwVNgOJUXaVx7v/+0r+lyIHyb/UI//RiSkjxg5PCyhG4bvkk+thL1KeeyfLntNbkUOkq1Lbo0S+9/VGib1e5EOLJdQQtSi/hxt+dzovv0fAvvJ7zqxZM4scdb8714TL73Oy8qdPvd29R1XKY3pH3XZxbKGUZz5SRbrkFebyZGRmxqflZ82ZNTMr05+9yq46vA8r+KI/S0fwT7LRfdLaKa91N8XQizjfel4cJl3ISrNPjJb5fSzvU8QrnKews06Lb2m2E3AMI81Whkc9x0mcvkSxNQx5nzIlmG3VhSuczFuRsvL9Giuzq+feMbJ/WtrKzVJ+La7aXKdNzs0Ys4/7xcf+4mM/5APSlNn4WED7yshpuI/O/coSj07ydPr5ttpPeec/acTPcOQ3pKm2+uns/dMyMwoz6lGXxja580J13xlyt9nm9ELfdlz95qROpn7TZC+sibXfPEYZIzzs0cH4tOeMNSP5ljSxjiN+RL7xHvkWUHdyFZUrqO9yueITaNfhuquy+biFXWSNrXMc2+metht43KR9Od/3RRamc75UfLhUfOiF9MOHErMP0nfW37bzPblyvpU582Zte4w5fkF4U2uMm6vJtFJ8Md4ETcn1v68b1Mo0fsl3a5zL4qbWvu8T7Ryy2g6on41oZZ2TOKmw1UtTWmWxFXBfiz3Lfc6ki9Xnavxyi72Aztc+cfZxWCsutp6vv9PG561l9PucvUzaSY0Erfha4rp8BbX36JUsceZNs+MlelJn0X7cZwTrHXqueD2Ml/NbYUGIIaYPY/j85n53opwf5lgsmcXO9+ppcRv3h9fFa4xcSpk8YrTkTc/U6qMuRqj8v5q61b6HL9O/m949uK2Z7E+V+5px8u7BCHedcdtBvfkRwzXY9Wa898nwiL1VKLH4fi1+H0I+I13CKt1vuQtLm15QUJSVn5abUTgl22cZ7PopiXUsflvvzyRmjvM4bcchB/4N0e6xNX8MsWEPU95pMkdk7OPKJI7e3yUe0xnYU7u/vEcvD929lKXAn3hVlnIY4yqZ/J5hiKu0TPPPEIvzhPyGz1h1x/NJoC1LBTvLXEx5t1AGbU/hA5rPkrZa0e6PG9u91IvUp36ucI/D94yCWRLn13jN7xlhvTaf0J4t1pjn+Lg++ew/XPXUtF3gc3sVCj/+iB8hpR5+yHNbIP31HwKY+3T1rcNbWv35gnziPfyR/tVvX3oH5Etde46V2HjdpD13gn3Ip2yR0xdumdLcj2RSL3388CWQe2NnnyLnbt2J4z4PledvZrFT5wjfZ2ntW84DY7k2Srl6SR33kPuidFO55LYogONtc19kft5rbZ3L/VKzXeqayw283d/nxxxyqcLun/lSqtutfzunb1fZN7Xr8Eir/b/wpVK3X792HdHK97t5t4jtZGnHSfAUtmvrbNMnFznSpmc6GvKsP5a2pmURZWqLjrRZeTk0IXMMzLA21nu2r7Xz6j5XbMUbEsckjhua5AyvOF6P7ulPbFOjnXVtrDEcT2OnXG3HzxjG5jiON7Uxx9qcFGkfazM6yurPN1qfb+cPkTbr44vrmCyT+LLGOGXLo6zPZX9Dr1bpQ2Axf68=
*/