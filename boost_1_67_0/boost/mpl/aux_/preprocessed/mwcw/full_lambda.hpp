
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
lThBjVBX2F6/4GYe2/9W1g1e2BDMiHqHxuwWzXUmD49xnPrI1Brvsf5f60g0fnipVdUmB6SwGYXetE8+V3qjHbZk0svIqXVIGp+/jqqmlKWio5BfaA8zoHNVj9vMIwO+6UDpn9jIrTLkoUrzMhbOCYNsGvM18YFy+Jf4JeP5YIdVB1fqW51hpN8XqTFS3IYa6ZX9+WFXtEUM1bv7KXyQylPshURTE6TZlYJ/Vk6K67XfPMI6Yee60wTG3ZKs0beuSiS1i/VVktEIjUyZtRklm3fqR09i1nheiTF11d0IGsbItCvK1fnC8SKAGvraWHZOgJ7mSL6iibOSftFE69TiT3F2VAw9AQu93XJq8pOAvmH/qhhnba/Qe+RtI3eNclmD7VM+s/g/xEmpKzynd2PL+cQ4T7vXwv6lc7eWjF6pdaTMJosKjtIuaakVKjko8h1H+/jCOrwji9tlDtflcFyX42d45mYJsyLuWsSYDnfkQ4TcsnUkjmuhu9znKjm3HoRubvv1SBVfwBKeUiwhd/bUbzkudbr7dumJooTMPnv9V3KkzlbOxlhe7mPtZz1chsyy3HO79d1Dmg4JlmsS8QJ3cSjcKWwOBVcZFhtWum/pFstyIW/s5oVRuKxnB4WYuLsO3oxPaR0CAO/lLfrLOs99ATaLlKTyP/lIrJZjLIKd3oPF/BqHJdy4ah2hojNXYet6uFjoF60PKiOmAdvkoukjKXrjEHJivXFv11dReG/SI+XTm8W200eecV8/kfxwBhUrIg1wApA4vXQlTOPEGu4MHpx7noMvu+/jkM7bkvPgg4tYHCZFBs+k1hmuKp8n21/oYaC5Juyy+ZJj1jZRXX6Fty+kjuKtQGazGzdmhRVZEuXW4k//MX9DubwPUM+Vlrx7dzrlRE0flDX6ztFuKvnM5295u2B/5g4e0XW/i3frCTL5Np5n18XanIWMu3LfW2f9EnuII6gZYfxO/9xMy6cl1G2E8ru47/IJr9PgnMOUZ8Y7xHdzwSmuxbr7zKTHmWOPOp7JaWDSb0pZL8CrfjRYBpOrEmDu7NnfI3e9ZrLh7MNA9PlsQc3FDzi7tz3hAV2vAAIs/dPgz0xolxyKT3z/bnLgrXPpwozEdi3HG7NsQnT0srRJq700EWDy9CV1Ed3FEY2A2eS8teLrhOc4j4W3BzvubpQzzSKXKdxzKg3Lv9mx8ooHYg5fBI7zmZH3eFXbf3KadlKxVFqnnjdb2GiXWTiRPGMyLbyNZLZdqqyVDEhjisOV2Z5+vH/oqT+c4uLLVBfabk3vhjEXvace2xDUWx3nodHSR/eUGevanqQBNIj5PoxcuGxz3lV7Lhjiu6444mLnJq3S77qNny7uEZkpcR8c8HveJmYPT/4tTsO97x8dCcS/H34RTqHze4WlOoYbQPuiSSDrBC25y7Hvm0v38sORObkvK13weuelm9puxwI2C6QyD3A9aqCvEIR0D6wsr91XpJtjkVBLR10OykiooquvTtzT3Em4P30QK9KLpBlA3SYutwFPJjILinrHVOW1mXIZgTKp5aRK4qdVPB1tdFR7es31hUM0dYlwMZi0FduGpOsq3/x+3771SFmk643BC0qzzjK6emqa1HBLZP7Lv+51iLEtldbB6e6fb21YCgRd78wJYJgSC+WwtmWY00pSxoP3Rjcykn1DVsZeEvt2NDD6gY6LXZGbiHF1DagEpQEVLjcQtAhKyWkK/Uc1bmU+mTqPqM/9EiOB55upUtsXLvlUNnevQVQ79lhycs8+Zq4VFhaxObeSjkgo35vcR5y0y/Xc/SrPFYhlGyuvn9VVCVjLzvKPg7xLKzgjjevEB6umTWrFficyHWdlApVhiq14D53GtdLVEnC/BSYcwE1eCViW3b45FVqyHqn8m3s7NecamFgMbUzYsZv59Zhd3iAHSvNONIERSyFjtgkncAt7qmLbIQTHPruZraNNWV1idXkkzvs32RcbxPcD2E2JvdpPr1E+ttvTue6arG+a0uPPWor8717HZDPFFTSm2RmvOXzeFy+1LEvOynb1SduAYT6oGO+LDFGz+6laNmDPV8RrwuuyBNuV1XrJ1XDu1M+tJ6+8dHN8SU2G6d2rxr7ajO3gHd0rSvBL6cWSdjDMshytvlqa35t4mp/AhpBjb9mUzUR+a8/4H+SeIY5ffGRYih6pzEwd5AIgScLWsi5fLWUnVYYnK1ieHvnLB72TirtNMVbHmjyDS0s6PBPHWK7ppM9PikL/DPGDXL3YNBn7eVHrwdjzK/doS5LKrtMnfS73V3d9U92rfl8fA8W/NgnO6pan5V/lqd76ylHXePgBzdc8GzOZdW7pAGXNT7GudT6guK6fcuPbwzl30Zae+4fz0Zbm/dLMsPdAPbez0mEb/UbibX6bxLOkZgIRq0ev17hPHLvtKSmb4R7QNWNrbFyb6M8fVIdTpJ3okzsn1DwWl943yq3TwVJdRqo7/tqzbfScHsBK0GriGj2A7JDGkUc357GkRI8PCYWCkVoiFyFS9u49L5nXeDgyGhGwcJZ5vhWp2ioyWexBjvcKTX/UPZyPekWbKKlTTPb9KfV7oDlpR1/Uzxjl/UG4ljjv67z5stv3g9zIRdHSMGnj4PIGmlRKh1ixQMKPNpPQgYu4gU3+uycpS9D/78yKTwKNAR9t1ARH6sibgEDWgV/K7//91dSti+SgM+Spj4qsUwne1i52xrl7ZqGFdMDMjGyAAnVBO3Y6nEobH3IUu/GTMyQ93JxtP16TyuQHEQ0HMC2CK1zIZjfQbWEbe2ulpUOWIDINkSVzK5c5RsLEd4JAQcAfgCjDp8/ufHkCt/O2epJqFifj3L3er56frjYEdvzefXeYF1ArorfnB+5cakaToET5ctK9wykID11t5Tj8mh95rI0D9wQBrUIChXMQA16iur2NHqfnHWyWxTdnlu0JkA0Os3MWl4z/5hcljyxY5G7TKUD2+p/jzoWcdranhs3XPqPo47+UIHq8/Ye/WfhSbKt47pC75L0A0o7+HiUfflpOealFABG/75uJg/l3KPTnd7KPs/fotxcWbZTZqy9mhaz3Ofzt7lb7jZABjLjYuOl6Hv6q+ZQ7unmc8BR2nzU2zQ5b9eK49iPoDNLKXKrUzWKaHPdn3rG/qu5eB4O3QNnREbVWzbOKg+bPSmxjB0D6s1XY3aEHRJq/goBrGYd77kuszbVJ1COZkmZgzJTOYrKAwNKI1PnoaY5nzWdDl8QlQH2vi/Bwan+iHp1Ju//+b6mHcledEjODe4/qbV9liNQIdY9bPVbxew+mvqzAE5SMu5+t90iMgL6f5aNzHVee9etUo3838MI6nOCrTZNlsTW1dimsXs4qxnVePyeT74yc5MLvoNyuq/woeXVQKzVemJrVLarEZuij2TYjv7gyocRHKSYzb/5aqbhu189IGDc/3jEVkTwpPp+O5ogOx+QdfNGkb2ll0odcgd3XOTr7C8REb5fyhrUeYRREV5CnHrockjqgCer+EO2G2gF6FGwjgK6PchZiEURVEILxdcbT6dcqiA1oWKCbAfIfhOxPfg+Q8MBPQYJVeHiwqkDyyOcRyZWTYSl8P3Uw1b4MmGRsTlA88FYQrj5wnADp3ckFSSi3/7jyCU9/TnHyUTgf+aIx+wx3/6sHw4KYD/jJ6pjk1x11I04YBlougpmY474+occDaUDIv2FcofD+awUtEsSs/1UOCs34iraNmn6/h8UVcmFnwBIPdh5g9dOc+28FebCkPsddiN3//ix1ptkMuaKdgmYGeApCOJx35YO5gWUFaNJ5S53k9vz7+OKUOgDSG3D9WWAX336p6inGAJyAaKdek6m253ozK8SCKCQ5OkGv+Ar26Q9s5SFoSo0fnspn6pA+HFpgAwqbQrIbWJE49NWTRb/wvsmLqIsWn+rxcDQ1g7vWK6/MqPS/PWrr3O0p1U8w+0deMIonYpC0iaUG32hKPBaOhP8mnh0B5e0J9WfE+dVdt1GszZvwPolOdntCa+E3t+uyORTv0weenxpo+2fUB48caMYYNDZM61XWorIVXk0+E9sm7t570x0mLt7fWtELl1pAIPQ7h+mj2vKfq48n6PzXXGkn1I/bUuPSNtvtKndCbZuS2Xoh7xtq0u5HV1hBhcgty0qfZFsLKU944LxWzJyoPS14R+7H1IdHq6v8Oz09CB5XE5hzKqbKeAk58HPf3i25EalSFFjOLO4jY6IrRrEn4//W/J2gqeq1ENI6CkEvdP60HU9x572oujv1NQ7uRqwQ0lkj+Utqr1mk7tnqaZVjm5waJmswd5ewt3ofbxrY0bd88ZzAFXdFFvL1dUvA/FoX3xAI1sduwMcI3wwKByK8gGSM8B88GFwg7O6Lc3xKoJwgSjkItMOL/m9lsMG+hKoRKYpaOUG2PzDdt7SHD+b3556ZNGjChSU+/IhvPnMHS//g0jTz9mQz3YTiMOqTv7hAYIWPBdjFY3dCO1+Qz6FXoWysN2XYD7SEpN+TFX0RU87LZfy4+C2St9nuVc7UZK6HIK+GwcICM5mhmiWOkpPmY3qDHrHqH9E7piWvBZQav71mCt7Yv6hxdIXq+TRMH2gm2ISAC1fOb88iPr3IF9vihO91W8VWGwR3wzNP8XhfpZ0FfjrqYDWC+A4fUxSSR8Cr2we4lnYOpHSROvPh0YyfmCHzy/OkUZD/j+G/kXjzY9I7kJFh96Tg9jbCVUgbUPFA0llEWtBjsP8LQesHZQPCeoRV+GhQ8no8DXAVEHBO/gyK8ADeeoJyb+Po9GdHXzFE/6z/lhSbDzp/wtkM5GT7cIYn8AJ593c90ipsNViiIM/sf4v/pfRV6Adi/PQGiDgIqgVoZaD07oPU7H/vgXR9jPU45XwZaWfu7wPeL4Z5yXsKd4en6B/PX6jPHm5T920K8VXQMVXiq4/js6puDJWAIth1tS7zmJSEs85/64VkGNYJr7pdlhOpFW8eyrSldyul2CkXGgmU95/1SqWbJ31yqJ9+15Oga8fX3p8zfLl6XZCPan9ZDYHS8t+N6a3/WZ7QU8XXABgevtW3L5aeWzYG3XByCSN1djRk7eubzoqtAaUPwe90r6ghPmasft05uchOonEKbQsdbKXZ/smptIBuQW4x/CTv60eborc2hVFblgPHV5+RIElM77+AuHieWHAjW5VkVJ5+XK7gVEhpXIo9ghKs8Ip4vXHzsPnyz0LhJ3El/C6sbTmvXM4Y1fsyiEbJVZQcvxO9mdTTTbdQhv8uCqi/gwz4Rq9M0r+0TpDSi6c2W+p5n80hlMiekmP13hBm4mqdRsC7ptGYQE5794GRWL/10d5zT71MWiPKlCA+ErAOKi13IDIt/CG/14IEXo0SvjHdym0bu1vyhocj5mdjMMjwySzqG/n2mk2XJWmzWt6VMrlWEeKnD85orop5uBWnhuSIO53qvTd59ZCSfYv+KzHaiZVRiFwlsfJnUlesanxefFW6cWr4B5dbp4OrLcXl4zZjqxaWN0BVncTnrMrQjyuv1QOretnFhpvBlkrFFJO6PihO+LsJZKwW5p32xRM6UMXI/9zTSvxZRJtonSkL5fXZmJXXLWXWqHwENy7V3vpsZLZws+JcWTPFtu0Ct0gaM8v6GhX0jFYtadg+BUO/7fm0ZIEPeejz+/sbtBDkP7Af4D8gfkD+gPoB/QPmB+wPuB/wPxB+IP5A+vHrB/IPlB+oP9B+oP/A+IH5A+sH9g+cH7g/8H7g/yD4Qfjj9w+iH8Q/SH6Q/iD7Qf6D4gflD6of1D9oftD+oPtB/4PhB+MPph/MP1h+sP5g+8H+g+MH5w+uH9w/eH7w/uD7wf9D4IfgD6Efwj9Efoj+EPsh/kPih+QPqR/SP2R+yP6Q+yH/Q+HHnx+KP5R+KP9Q+aH6Q+2H+g+NH5o/tH5o/9D5oftD74f+D4Mfhj+Mfhj/MPlh+sPsh/kPix+WP6x+WP+w+WH7w+6H/Q+HH44/nH44/3D54frD7Yf7D48fnj+8fnj/8Pnh+8PvR8CP/429R/xSN25WkvTopi1CzeJ2JFt+9D/zjDaIzHaT3zWSSOsUSlpDnLGmYsOSjXbl0QyLu2V37Sn5xjMbGgqj5Lsgu0K7RLuDZCE+4D7/fTA4YHigvrA5oLygM8Jkg25DbINuQ26DEIASQBKAs4Nmpd5wZ3Np3VxedPp15tp8zTxW2+jyNLs56gkircgbicPkMaVIJUrXIvdo8vG/Yc3HC9jagNTtUpXY4qnFCakYGzcMmoXBFzTf3lsUKfvo0pYmfhY2k1nghHOhL+NmwZqUxrMs9/jlUQzmrDMVHO1phZ9aSJcs1K6F3Y5fmZRYZGyezeQ/gcB+06+xD2CYa/lv3V1t8QpMxR9eHfzyqUJ5dz+5l1/3omv7GnQVeLUIHPOgPR4gtLtZn+LS7DJsdVXZRYYnNXb6Bxif2v8mj0OXTHufrIqc+VB5n9x/8XWR6X88+n1hxeFhPcDFQzEKUjyFcnd8fMHhcfeUltCKbmku2tsBF2WpTmyLP38MkxcrIulsO1YrrIVjeei03XbM39nfFJ7Z5SxsDKXGqq240Iwl4kbIZyvf03prkWWDs2Arils0UELXoFfoklvWHBsnb5bPmsmJyrrVQkGDNophiNQLqO9vgqpTXCL0Ds2X8nDokW8bixQWUTHDeqJk9erYP06j38Z1Hd4VWtykEitDetCUlnosYo2oNg8unsdU3lGhivEI0y9UShlkQOe7GQQd6/q8OjDyP9usqMdFu/udg/tRIO/ici1TdXxUr/9nwRmCwQ+u49KvjgFxYj2kigGWCy/ElTO69HS8enarHprVyHEghWm8J9CLJkNnzrdroC78TY7FN/tuiwuhd6Alk41PTv+3ApJN0PgK9kM6h6X2r53SoZXd5MYWkxjUvxdq42qqPideXoLwfNiy/6a4X7QCofUjXGtwgc/Db66NQJ+qpcFpwIUhy0RNcCJnA4g3kPkjWMSHSmEv1KL82cuHuzEltUV8pRY7JklTOZL+8kBF2M+1jVvyyCTwTNHi88rjy2/+bfBds9f7j3/ZDm28W4LaszDTlV4xvnfSxYNGL2aU5Y7g+sJX8zdlac2KP6qWO0JYDh5VUaylK+lRgxioi2xVDp4ikOLVQl1TXHxaeRF/49gRIYPNdfJU+haZUEVmgdGCVGbewfbu2h22lt5Fd4oEyeNzl3/xlbxYtYOJNJ5dpthWUAvFsjbvslMiyvKZxLaDwXY5lXgGyk0+Obl/q6Im2aaucGFsXugrk5Mk8eTF+DpFBBjrOwgU9nO+MPJuoCfY5CpIBJCxgKhPGP8+g2cHGN38/dN1yHRvtdSAlow094zg6asY6+SL45uX0rLsRLLEIWn++dTq9Q2Mxburri4p9VlodFf01m3/eCDKKPaJa0kfPukvVYAzIaq/1gnsvoEZJja4Mx59EER3eCoCXYOdBEPMoYv3NX91xa2H0UC6tN+UmW+vhcQJeO2z8frmCJ3lHd3u7R9rmV3oc1ZTqJ0qpaB3JjISL8+W6wgkZQOWShW8zXBaNz3Uv5TIzyf/C7echpc+MdRbyQWlTR+RUuQjlHEBKLFut7AzVDmKbcvfXotP/7pdfUWYI0UY8llEfj7ahVudOT0VOfXPC53oLz49UomEvC+MxqtU1zvRiXDAFJf2yqvL04ad2YqLFBVTANRPBrcE/1L5mEzpJWD2CrW19N5wZYOTuTFj/RJU5R/441vdDGRkPo7hAPeY+j7QLcZJB5sETc92CXR8D76AqlKwAgt57xaMfMxN205lYe5Qq8jtL9Jk5iReQH1fUH94mkddKnnb/093XKE0/0Ly2RR+IZF3oY3DgcZazOUw5QzJsq4syKV98spNi5rnoPc3RZPejqRZzqokxhGF5BuAwwt6vitcckT5rF+niu5+pbgMgYQMl59FyC9vgUO71HY2/i1hdZRXnzLnxQYdcaebZl5tvOfkeawK7V0U3cj/hnhvkGNQoqjLb60tnNUd9nVA3bar7ALZKgVtjmS2d519lW6Dw21BVLBrN31zTKnpzjcq9u3NRLxS3ZYA5qp33MgRXdm013aIPUZfA7f1mNkV31GhADORMeij48uL0ThDDCI/m4PHxMdya6o0Rx7R7BP+8+G2RDw1T3imSNZphZ29eI7FB8o5pqfn1H2uiQlcX56QJYZVN1KqCSKvbfP6YsaQnCq4NTdnnKlwCnl3q9XJktf8VpXIr23+/mJwJwcfb4pCjlDKgtbwdoiWRX5GS5c5MelxykDpt4AAQBsPxJbHdSsW1TJrKyzjl4smue4LjMiHU2zSacsyeTQ8j67seNz8rIgmiehcR9PQ+YFcMV8ClobDlTBuzEASv0ozHT+ImNhCcb6Qer33B4WRzOPZmkth+PBpw2QIX7w8+XzpN6c0ScbBYzEXMsK/j03Lt0/cU8PSIa/2miGpaspcynOPjwdzDjFNJQWchXFDBLpPxIVHrG/Mh/sZB1epfPbPs1IWg9UKA1OoC0+vc5aPz2wiGpGZBwT/493Vv8vkmXqK6whPVUNLH+WcXl+4X+48bfrLbmncQOh+0dNB0Y2MSP/mdVadid2y08a3wtR+dbWphduvyj2RCZ7VWq9E+XEj3TY7LUBhJ7Sy3xdab+P1UNnHZkVrGIq+y/hMnlIVVVtvmXNIUg8mHynLXJYjJArYsiCH2oVL7H/Gk0gPDueWuGOb1q5y1degF57jPeXRnXZEJhfjuodYvxfwQ0aKOFsCgBMGxGwXOQ/QKWmdjhKN0yVgN4ke3rj+G2HTuqKdDMNI+wcUPtBZ3KrZ22pRdGn2dhFVj6CPKnZWBJOajVh4t2o49MvX+LdV7ovW3+0y9s+M+ojU49qTh/ythxgFDZNlbgmYSl0P1nBfsbbVjkPzlqbRhr25N/CXwjvGo5EIa5OOwrSc4RITHrU51m6dCTAztk1OKtNT0h5wsGJ4rAy6GeRBZ4xNGBT4f4sHv3UL6UnUzieqkRuqNXW6PBoYG+2K4c++VGhNlUC728vlFBTmkK0vH4T5lz47RNX/HEabBQOK2N0riEgsu5BmX5ncWemsdYZArfIhXE6NuuYJHLJSDMO3OucjjKbQ/Ypu7g+u8BEcx95Y5vbTMQQuV3jK2LM5HKsODlGofllZYBHSmJK/rer15DFKh5MlpYy9/i1k5dOoNUQ4I0lMwR0=
*/