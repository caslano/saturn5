
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/full_lambda.hpp" header
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

} // namespace aux

template<
      typename T
    , typename Tag
   
    >
struct lambda
{
    typedef false_ is_le;
    typedef T result_;
    typedef T type;
};

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

template< int N, typename Tag >
struct lambda< arg<N>, Tag >
{
    typedef true_ is_le;
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type;
};

template<
      typename F
    , typename Tag
    >
struct lambda<
          bind0<F>
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind0<
          F
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1 > class F
    , typename L1
    >
struct le_result1
{
    typedef F<
          typename L1::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1 > class F
    , typename L1
    >
struct le_result1< true_,Tag,F,L1 >
{
    typedef bind1<
          quote1< F,Tag >
        , typename L1::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1 > class F
    , typename T1
    , typename Tag
    >
struct lambda<
          F<T1>
        , Tag
       
        >
{
    typedef lambda< T1,Tag > l1;
    typedef typename l1::is_le is_le1;
    typedef typename aux::lambda_or<
          is_le1::value
        >::type is_le;

    typedef aux::le_result1<
          is_le, Tag, F, l1
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1
    , typename Tag
    >
struct lambda<
          bind1< F,T1 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind1<
          F
        , T1
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2 > class F
    , typename L1, typename L2
    >
struct le_result2
{
    typedef F<
          typename L1::type, typename L2::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2 > class F
    , typename L1, typename L2
    >
struct le_result2< true_,Tag,F,L1,L2 >
{
    typedef bind2<
          quote2< F,Tag >
        , typename L1::result_, typename L2::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2 > class F
    , typename T1, typename T2
    , typename Tag
    >
struct lambda<
          F< T1,T2 >
        , Tag
       
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value
        >::type is_le;

    typedef aux::le_result2<
          is_le, Tag, F, l1, l2
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2
    , typename Tag
    >
struct lambda<
          bind2< F,T1,T2 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind2<
          F
        , T1, T2
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3 > class F
    , typename L1, typename L2, typename L3
    >
struct le_result3
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3 > class F
    , typename L1, typename L2, typename L3
    >
struct le_result3< true_,Tag,F,L1,L2,L3 >
{
    typedef bind3<
          quote3< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename T1, typename T2, typename T3
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3 >
        , Tag
       
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value
        >::type is_le;

    typedef aux::le_result3<
          is_le, Tag, F, l1, l2, l3
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3
    , typename Tag
    >
struct lambda<
          bind3< F,T1,T2,T3 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind3<
          F
        , T1, T2, T3
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename L1, typename L2, typename L3, typename L4
    >
struct le_result4
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        , typename L4::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename L1, typename L2, typename L3, typename L4
    >
struct le_result4< true_,Tag,F,L1,L2,L3,L4 >
{
    typedef bind4<
          quote4< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        , typename L4::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename T1, typename T2, typename T3, typename T4
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3,T4 >
        , Tag
       
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    typedef lambda< T4,Tag > l4;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    typedef typename l4::is_le is_le4;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value, is_le4::value
        >::type is_le;

    typedef aux::le_result4<
          is_le, Tag, F, l1, l2, l3, l4
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename Tag
    >
struct lambda<
          bind4< F,T1,T2,T3,T4 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind4<
          F
        , T1, T2, T3, T4
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3, typename P4, typename P5 > class F
    , typename L1, typename L2, typename L3, typename L4, typename L5
    >
struct le_result5
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        , typename L4::type, typename L5::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3, typename P4, typename P5 > class F
    , typename L1, typename L2, typename L3, typename L4, typename L5
    >
struct le_result5< true_,Tag,F,L1,L2,L3,L4,L5 >
{
    typedef bind5<
          quote5< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        , typename L4::result_, typename L5::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3,T4,T5 >
        , Tag
       
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    typedef lambda< T4,Tag > l4;
    typedef lambda< T5,Tag > l5;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    typedef typename l4::is_le is_le4;
    typedef typename l5::is_le is_le5;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value, is_le4::value
        , is_le5::value
        >::type is_le;

    typedef aux::le_result5<
          is_le, Tag, F, l1, l2, l3, l4, l5
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    , typename Tag
    >
struct lambda<
          bind5< F,T1,T2,T3,T4,T5 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind5<
          F
        , T1, T2, T3, T4, T5
        > result_;

    typedef result_ type;
};

/// special case for 'protect'
template< typename T, typename Tag >
struct lambda< mpl::protect<T>, Tag >
{
    typedef false_ is_le;
    typedef mpl::protect<T> result_;
    typedef result_ type;
};

/// specializations for the main 'bind' form

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    , typename Tag
    >
struct lambda<
          bind< F,T1,T2,T3,T4,T5 >
        , Tag
       
        >
{
    typedef false_ is_le;
    typedef bind< F,T1,T2,T3,T4,T5 > result_;
    typedef result_ type;
};

/// workaround for MWCW 8.3+/EDG < 303, leads to ambiguity on Digital Mars

template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

BOOST_MPL_AUX_NA_SPEC(2, lambda)

}}


/* full_lambda.hpp
PWpVb1yQoQILpvcTLSYPqjQEaDNj18TFkhMqo0oV2UUomoSjJx2lFDEJWGqFRudu9+7f3uVn1U66aiPn1vD3OIDHBzAtzrWqfgLBFhGLjZLesyfAUfCgoIWaFvlKc2JEag18lRiqxX+4pWWNEalXJzGTmuQP/LQjqnwshTBFxvYRdQ1LHT/ollIe9dRntU/YlDh8qcny4AVA8aOxc4WPVVYzs6NEYAaoLKaYi8es+ufb3r/I0hQM/ZNHuLnz061EGCRbqQFn5E8Q4e/BLMabAUiepGVsxQ1Udb1+HDc7VC9jOwFAvqwMHQH6MjPngbEcxBoxGqm9Lhp/nPg1ppCmGo34l6cAm5SS0wxZrqVayWgz2dN5GJwqIWGaiv+z+k+X2c9DYB7zha6QIvsHjd3vJFNxnbwICZTq0a92fjI7yOSELi8IpLYQ8PfBjHo+u7AfDYzmTuse8FSBaG2OCbjbWhjmTvcrBRv4SOvFbXh1E7ovgw8MIcVfnlpdWVmWe5bMx/1oz5eV6IboKzuriLs3gjWoJJxmoqJ65riHXpRCk8VxXpXFhwk2KVB1vYPD2gJA+vm7/3KHwPzw9F8iayZCTD5pPIyLR4/uUyXPA1oMMaWTTcIUS2a4mpEGkp8f93MJtuywaPtY0+X9XrPFI+9aafWE5MIeCkcQCztXw8D8MlhBRZOIUpq5TEpr1/CJ5tNMCxnzmuxMD21Bh6uvHw7rGq5dLU4ml7tlspDUrVxA34NaT48D/CNl3vsFWQO3BcH2Ymqsv9xlPj0vpCmsTMnkpQ963IMn3zdLvuu7y2Cx57Z0n8zogHQBJ4zV0OEbZqyUbsww2JskN8pRyVtH9bI75aER2ojS/qEBLyRw+R23Ay/Zhx0BOkXhhNfvF8kD3yExMab0WUnl7HkcW0UrNashZTiC788y+xYVVq4ocgvK4UE/J5LCOXOwx1X4/hLhQFtYODQkDeU0S0oHqy7pe+RxS9kD6qMi7gfqz1oZRANo+u5XnstAPBiNqFsawhE720cDu3YPbLO05xQTD6GVG4IgZ95/tFLSxHqsufU5DNLZb31YLIfajDvMIoi2wxMzVq9AaIyKhTi0Q/H+efs+rQ1EOQeqpPK+Aaqr4H19E6uKkVZCP4lVQEg5LgN95x+YvQpQMI7RM6xHS5yQppR8Q35RJki/8TLow03D8i2TvqiNNOhs/tj9uc6BR7Ymcwc59KFaI2FRM5M0ihigz1AwjyH0eCDz7cYBIKr/3WbVysFUTKFF8wC30oWxiwnLY0RhZOlDyY4Z46QvlGjVe33dMETEqz0Y+elC92bi36s1Hq9xXJEyXpTOhCDyFuf78NpKO/IalMo/jxUo5mWsGFJTUdH/6jn+OyaC5/j/jYJpHT9n5ZWcPOIkY0NS4zcEcfpkZCO0EBXm5kFQalBS+YvmpABpa5L8MqoYDluQ7ApJiPwk4bGpZewoVSrKitYo1tNkHXXgKQegYmJwwWFypAyNMRtVOmP/AX503/HN21evW69HU0YIyufsH4AMt12f1+3Pnt3Pb4fdV18+aqtOn0aqIoM8LupG1Lu4R+avni9fHd+MkKCj36uT8FYkVhCoqHto8PqeudaE3+M5BBAmTM022TpbhzKGS1Jkh1WxT+TWGNLOuRblo7FHTHKOOLMZcqDP3Klx3pseWI8uefpOq+ayWhC+KEUs6+icFJlkjEdNCoIJcVVV8vhgbY831jZ3LCwJltfLh0nbIzzb2CjjeUaqWdoF9vMkBWG2QaYISE8ZQUy0CPleQi8vI+YVfINnQWNx1P1Xe/ut70cG/fXNcEMrh8CheGMe5yYa5hL6hBSZQORfFLFIRR4MW0Cv2BmWRkqm0N5AxwYRe6muB2hpUlxBl3CnJywQ8Dyo8aXBH0Gk2vYbYN+BKw4+gyl6RuyzZ5+M5ztSThvTYiFrA2dlKiLoVx0BYnxhp2VaQheTKhKYSK8sW4BMO5U1Lj+jI/UEQcWt9y9UGeiByf+QMEaE7lLX2z4B3s/85JUXI331E7WlCBeRRhCquJkghC5oPaZidhas7Sa6ot6R2oilKOTeGXeSL6+1HHu0xd7MHQKU+ctwd5fIKVKpeVOBcmHhYvhB54dRGlNkVVuUCoSbPdrCHflSIfCz2OVVEPROKphK+KU6YNz3jARS5jBBPKhhJaGsaU+oBbHVw/jhCoH+kiE5u79ecx5RB3gtmgcNg4KG5wKLzcdUOZ2OUvdT2kzO9AmKijl+9KHCxj1RX08+dQeW5ueIOIy+6nLZYpdhicSsU0L0Ban0p70EX+FGmEDWIWucliXCrc1OWExgREA7G3xEWv1uPiGpIBd9aAJfL6xz9EQWFPCrKkbAjlj/EEBENqmhhRVMCwYKbEarYx/4Ihiv5Ss6SU6Ck26PhtB8p9GbOs1v5AjFApQ+PZ1uYX6AgfWqccTawzy45CiNPR62coWDVF5jurrIeJuH5zurSf3XqC2SqUP1N1M6gxgDYpfECZbNoSs8Kn3a1Tl4SaVdk9o9DZxPAb0bWHgbYiuaVV2MQX3rLwDTCQ+D9sjxFEKeVRuUddwi72tX+qpqlA+gCHFcEh9OnSd9s0qSpU23k7Fj8IFfl0SS5b/UYOjIXJxyMASyU4ZsPnlgYAYOqwdchEmSs6X1X5KDifn0JNaKVuNGFynQd7gPyQETQbI4PI5VeKm5xsuW3oB3ZpAfh5RgFBMwjeS8uEh2ORWEzWv9FHzNVqRDqFd8VgOhy4sFhpkd0TGjSksl4ZCAe8F3We1E12CWWEj0RSnBWrgOZruOfHLcRhkDm067AU9VWMsBYph5V6q2+Tx6RXRiy65n6GOwracfExBpmenYH0iDzz1J5iNWbiP0dv8yKMVWNkMcixuzoao7IxbEFo9lnrqkiwEniDt1KEgwT2ElLY6SMP75AKWQyqqmZGtL9RKjen5j8h8FhRD6lhJSp0RSJ3AZ0v+8nd/I23/v/Tq9013+CV35Wdt9ixT25R9Q0aAR8Jw3wy/Ut9CL8ZI4gR5g0lFFYtZXpZ2N/STH+9nARvv58z0MpLy3rPZf11lhmC+Q/JPlMGfjBqed0Iyyl/Dug9VP1ENp5G7paZCSErpU84PJ5VbEsUOoGib/EuQUCn5rg7I0U3B0mwyDUFIL+XraQSdJneqZn+8bO6Mclg5LN8idh4SIwElb4PvuljvHUSOBT99x3weE4A6wOAUOMOt8dQpRKD3A7uIEFB6NLWmmZCYe4nP6nn5kjZn7VpK+dRXlyWKBZlNa2uBTK5bhvJ+lHr7buzU+lOB9Bf559EzgMAojR59N00Vdx81qHNHg07lqwYzFwdulWTClzzlzICt9qmKpQrfUoUAUmkGS0dAJF6cmnqJiNug9NAEJ4Rh9pMOFR/g0+eqDf/dbI379/XkaSXmwEPz0OK29+oVcDTRVtJhpU+jdvgTevCcaAjOtQ1TZEuAh+gAhwjwy+k0qQssX+a0lD3ofcXgfMxYnlvZCydUXusN4w9vnUmR+i71UAW7JUhFG5qwSDJ+xJOWrvwi2Fu0DzzB+Dm8IfUs2CeTFk1nZfz+Cq9HLgwxwjqasZaneGvTlqDwyn2m8TydJTC7AekS9xzOd6IAMr7myTi/792pk6pde4SsRv/HZbVeZT+02uEsZwPFvZ52iKHvCJzU8oOTTpTX/FYX6wZm8J+ktGs84gLtEOjTDUEKcyxv9uH2l8QfO3wl/ZvM1RxiM/v4rKTQNHFfnnOCVXBt30Nn3kauyBmlqNAovbY4UZH+yBg5TWBoy99rQ6lbQn2Ie/KD/0PwlGgfvzgj+sv/tpz19fcia1GdNlO0AXDSaIYtkBLWEyflgw7JjAPNBW7pn89lfHG/atNBIfn8+V4N8kkqYF5SaIonCv4Y0GA3kPbdkfKuWIdfJzCN5eevjER0FsjQPf+jkkoXRHwygloXx2PBn8HkCoBi4r+dDyIaHF3WnIq5VSr9jSTbPDvTiiEk0onFrJgRK6/iJZTofLrSVdKdPQfgxiQa+0v5sqQni5tSnDJZi6ZK1vRHBeI0Nxi2m8a7opmlJ3DJYnbe6DRcC60DHwvjuThLJd0DHQnVA2JonnNjwcOedlNzkiTxXKg9mo1fpP0fW+4a+OJDjqN5dW2nb144opEA4o49NT4W0XzYb8u/tR/nE796SU+cnm0I5N6CS3Nde8DcY1SicgnaIRwe+13d/dC1XyPXULBePe4QZnD5h433amJzY4wYhQKbE7CZa4MuAQZy5tVb0I9LKuVGqt2Kr3v+MJqtLgZSR2zB2krJC2FdMUUFM15bdIAU+KG7sVBokb8orHL5V7T12VuPyRMS3dxy60cQtwmYfIjMt3LGKqo6vFcz/W0YHRywMQYvBhyKACQimAfzqHrkpojvxzq3HjZ5eEv03InJeYxQIacRFYY6KIxh0qRCt+8iQeKTk5kppDUkdLbmkfo1g4gwP7dXE6u+svgUGctQKvvMacGQK5uXkHV7pEf/7lgdHhQ/5m86L6mnrOq6q694OlbEmTlMAeO4DnV37XTmK0iK+WcMyIH/VU9ECWTemFnWK5Tgif3zcuNUgHPC1L2z4lcGB7caCFduJa90WGiwTTED/pgwaYPtP0PsF4i6M8Mo1Ez5CZuIEFeJI0pXrIJB2vYGAtcO+zTLV0R0g/heHuA+h679LcffrFvIqlOFX2RHY/B5SHbgG6UHD4kyn4bBgRMF/B6ddi82irXPtfiEGcreoplB3bM4jZVaq6AcsFw1FaYl7PX11eng0QjVwdi5gNAht/yIu0uk+egqVR5g82gPTzBCTkvwftEevtD/fj6ClPavN4FL6oLLBYcneN6sPb727kBaIia2yjKplEqHl6PAFBlQEryLMPA0GC69YPYPSE4Wqu9OBn7U9s2qSSI3YpUUzFFDkT4Anw8DCuAAbd0kRX+3FtpaHvFQRjLjnRAGLEH3BSj8hCOCSn4bwYZX3EF/eTwjEfmzT1e1kG5CVvGEexe2V3IH9pqTdlnpu/sslTS2BEgNFqesqi1B5SVYFdfThGW4BJtlv0mBONN0zQHsfbxM7sGwup0muOVO0ZI0Jaulawp9JyLkTJs1wwPkyixNFMYjTZwr2Uz2tq2SQyQ6hwFs/hEOH4DHm0/v3iEEgUsYa9MnVWRkpvCvwMi2I6CNLgUdbrECPPwU2J12Ai1iRXa7h25QCPFic0dSPtvE5jJxvDBmbXklwj2IFV3XDbiogk4xUaSFQZ4+qx3sIZVJKwjRUb1lJfixVP6w/ztxOKj6viHdXin0bjIDfJx8R1i1XkI2fQGirYlaFGHhy6PSovjJrki6h2BbYh7kE3aCt9Q4e9JJ63QO35+gT+m/jTaSEn0r3kf/AEeVljcdcjzeyIZpWXaYWTKHsk5IL5+x08x1ml7cKX2pxeZMQRcUbOhm4JqHfRx/EJvDheuBC1Wt+0qc1tt+nANKs3tNo/gJuaw2jemc6Ds3guLzMRnJ+A4F9tafuM6m/XeaKAyi0taRdRoCvPTI/BWh11fbG7/ZQ/nXip/VJD+Z25/p2lPKciikQz+X2oqfVK++3npzeCID5Sfa1V5foB0azDaw6a+SaS7vj53UF7Hu7y8vJuGMTPK0rcFVG4FL0l9YvTfMdqMbxzvx2XL/eq689rXcRHXrvPlTfE2n0TEVsebGoh/QMoAdv2s39u9AQ6kuIKeLXcksDXua9MofgaLdksKzOP21Ps2afxN0VY8SZbEga/hOkXaYeZ25oo4KRs6nhSwnFvX/bqiuYAppkmuoEqJKJjfzGKtWcZLYShBGEu4/AhVr5PyX5Ca/rurnCwxSrsN2sPTZzZneNl4N1p/4+sBfuqNYmnhAKuQzTlVunvLzmzTbqEmO8zU9Uxo2O3xmbDZdarq6iwLpOef/qG+MFEJWvL3qIH9su49O2QXkKGybQu4zx08nL4NCB29nKg8cRJ/1gmg4tv1qZ+Sb2ys08amlMwUDhyZq6fvg0kwqpjJGlzM7m/frPq+KeWxGGPhP8ttwDPV9D48+U7hl+gT2b1P8owQvBJK1Wh46UyycHrizkRFBgewXFh2CVH6DFEtR93c+TwIZfG5vLZZEKTIxg1rghaCRAhqsB5Kw2isGbwxUe9qZA9HnHEZDOclilJ4ZmU3L1mrCDPxXnolGYvEdRbkRKyi5tgRfM1uqhGM6j59qxN2bIBgxRIyiEIlGcCDW8rjJjEqpLNRoytE3wX31qF/DnAY9LytT4crYsw6FLuuQdnZN1dZdCDdJc5TPM9yg9UuOGVRGun7AVHyIFAwkxAclRUT9Gdr2/rJ7lIos7vNZ9yZ6cYONT+lMv4RYaZBlU2p8ZylS1BUNKcs+AX5WvSeVGson5HagTbuWkfh4yW0/1GJepsV+wW1oowUlGftBgWNwupHApPP7JM4npMULRWpaeS1258XMpPZFE8fonRnwk1ibChGYS6kzEK+Mqr5Pd396s1oUdvfWvoAoDA353TvsnNJHaM0AQNPWu6NwUp6GGGd5duBRB1yIoRyoJ8T2s4B1QqN2n6UNJrwYHpdB5qklnNB8SGi74uyAhII0V9gvt3Q4+yia0YNpOv4vnMGpYKX4W9xxdyE8QiYF4RUw2vKeA0sIcaRY2oIurs8HXCMeSDyml2dmfnkVudVi3RjxU/rc/q0vbDxOiOeSPIDwP2qMhh11TIe6tlM/bUMGWX9E+MRbAZlzIw7ipHLiJVndlmkeGyD4R8Mpj+HP7W25x9s1qXiSMcAAubTo8KgqvPNOy5wdvljTWlE1bnwFsoUNeTDnjjP4v62OXoqFnWz1uA0ysde3xVOWVTic3BzeYpALT2QIvkp1pI5dCbWXXZYHqJu3T19h6jr+Gh99IvzXKnNrWWfyNxeV3P8ip4TsswwdELTKPu0DvVimp1q1hkKTI9d6QJJQWbPQgXQrEseBp2PWRRVqnUccBYgKqyHcNP+e4GSAuP2zXqK6/1apQ/ADXxdBzeJjZLVwzBQHsOZ+akozQ9kN9B0ABBrUZqEoHK+WnonzUpCVb9n223p0s1w/XWGPq2ZWOh5oO9QLtWdv0On7b8viQbrCy9ir+1u64w93mMp7O8hgSnZCZ9P2O0rN9zOC2poahzhPCx4OEDr+H6OvgPzgVfUx3sj4wvvCWmMHpf17BvwiI1up+y886eTN1aUSXvBFIkpQu9UQICwl6gmJ72+jYvChKQCJLjlgvCFMt7ycZ/RhPPIbJmj9d7fBXk2Edm1/j4mGu3zPFtQlwAwKT26gzveBsrj6oVLPbqBa9YOLZPrEzX2pvUG0e5XDrbYtXMivq/XVmsH25Nkch+uQ2aridPcfeAtYYrvd3GO84VvnkAAIs/dOPwjEdMHiVRIwHDvUe6QazbdIjTHhko8+80P+Nuciz+b9aaCdcObHXyj2PAGDfHL/tC0KlP1N+gkdCTq1A11FhsnVnF4SmHejC4GooWriw6JSH3w4q+QS57lvuLHrR3tCM+KRvGdP7MJ92y/LKyFLmKcd7DpfuxaA5L1YE8XnKpsjuCxQjTVksTgX9d3suRQqXuXZpIu/ft50mDXpuEqQb1UVWPykrCRCac3ErNjBPsWYE9otc62VVDH22YOyfoNrRiVeFUpZkXn6Vvw63UU5zGZcEK/qtXWxxVMeXuTkv
*/