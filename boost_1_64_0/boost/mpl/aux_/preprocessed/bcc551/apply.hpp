
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
hNw5VfsLZYRGtyozFLIcEvcTiKLMksVJscOJEaedzKWvBbr/jUKs0Ibg0pTwTFBCF3kSxFwBRJsybxOPGE0+hiGVK37IWIm6QRIlmIixCAlUxNJDhgDNGwW8RKegwkEYGENpBwXTMEpo16U3Z4uaUQTsjBYwbXEAKBsDcmnuQX7szDec21YCKLUJJKt6ZFbKQoPsLTSPQyTOQgOjhUbkE7uqWmhOYcOAhUZk82tVWGiQTO6tvIVGSgvNI7r1FlpJZwTKQiPSSYSFRsnZY1BoewzA2WNgyh6zGMWePg2UGIu4bqNB42w0sIpBBlo1yMCdQQZWMcg6jFjyXMXY2WhgtNFEeKPkbDQwZaNBZnBWlPYGTNtenuQIexsNUNtoAIUFZkSGQ8RAYtuTz5nEwkaDZGy0hBzQiXE2GqFOCm0wLRV+dLS1jQagbDTIFRsN1NtogDUbDViZZBZI9XM2Gpiz0cCcjaYhUcVGA+6z0aAyNppD45bQRoNkbTQgZaNBdjYaWGmjQVQ2GmRtowFoGw3A2mhA2kbTRC5jbDQQb6MBOhsNzNpoQM5GAytsNEi00bLUCcpGg5xtNJwqGw2ys9HArI1GlCs5bbRO+iaf0UYDMDYaiLfRSGkzEXkbjbqbK6kn3mQDVCabBZOas8rlVYIhsSEmlEyw9lps4+nb63q89Xnpc44X9vTidfTmLMA+zuC8TgWnHVJlrUbQ0mqEaK1GoH6rkdrkTQCbYN3+msbXtPKVjPZ5rJ5UyhokceE4qzFDF5rrgBLSp7MawWg1GsS8oFgGrvOEViMEsRV5Jm2ZshohW6vRo3w5bzVmmltfWo2lSHe5tVNWYyHTqbIagWgRepmhkKWQSqsRoliNOCnMRCNK1hurEYhWIwRajYbg0pTwlFICI6+sRgUk2tZq9IjRZMfAWI1krESdFagEEzEQHTEWorIaCVLvjFZjFlQ4OYzDmunFBDjFcCnLkrxD76u43yCjrssv63zwlpdn82z4BG9jBWtjhaoVdTS21qszDMFUT82B6We7s0alCXKbJvwyTQGCiSWQjiVAJZavoDZWYCoSDkwdiRMzhmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4hmM4/mPnXuDiOOoAjm/CsffiYFS02NB0eQYVD0pIi5ZWakglSis2mEblI9Dc8UiOu8txkEtCUpJixUpbbGmLLSoqKlqqqKhpjYqKihorVdTYomJFRY2Kiop+8PH7z5GSNmpbHx/70Ww/0+/N7O7s7Mzs7OzehbPL2eXscnY5u5xdzi5nl7PL2eW0peOd61QnoYvQTegh9BL6CP2EAcIgYYgwTHjUzpZhxDyWmico4zy14DxP1bnOU1OEMvd5apQwfjfxg+uVMZSuOtlm8nl8Pn0pMz2Td5NvnemZEcOmZ0E03B7biMTdnlRRuT2FYqfpKRUHTU+VOG566sQp09MhjpqeHr2d2zMkzpqeMbE32TMhLpieab1fkmdWr3d7FvT2Ho9xD1pujyUayZ5iHbd7KkSV7KkRy+yesFhl93SKs0meXnGB44mdds+Y2Gv3HNf5JHnm9P5JnmWxLsmj3o+FSZ5scdzjKRHDSZ4qsSrJ4xMH7Z6YOGr39Ip1Hs+QOJXkOar1eCZFw+E5ofNze+a0yZ5FvX2yR31A8nF78kXl8JSJZZyHaDk8UR13eHrFKodnRCx0eCbEXo9nVqxzeBbEsMOTOir5eTzFo7Le4ak=
*/