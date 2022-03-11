
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
mTOeH7CsvuLrr/bt28JapHvCWYWYL+9uDeb/jTZyx87zxZA26ebIKpUR0kqFePetVjxK4S3v2cxAqOgqcMUsV7fRtjA46l/blQHuGKH29hECbIdxcYoR518XmXYmtgE+mYVZIkR0iM9DdPQLUhVio1PkU7iD3Omcq/YqjBjAHYoQxATaj60d2pZkPPtUClb8E9aS/iEEUlF1fTcq2S9IzWyMGEChgqrkZVCynf8hEeOlNlZFp7GnNVlSwWqh1ZOhr69BuueYcnsqMXBgA2iWUnJninwR7AAfzZHicGt6bK0J5UvtxJ8jfs/MeM4C8wPuWPEfd+zrQEO7yhDAQVRy7rlCwNR5RGnUE2jYI/61fcWDEAtZ5tnrBujbbxrw/RYISQxgAx2zA5blHz3RNwmdoxHXbUxDUf0pRAzBl1NFUhemHGZQ1/CNblY721EhTmW3eps2JfVp0Weaa23GaacAuks8tjDoDl0pV02YnVi/Cn8g5ONRJXhDqNsLTa22iKeqpOoQ6xHmgyjWFZmRPAsUfHsxBlGyrezQapkK2fWWfAthPvZ7uuGUH7SdIBz19/xSv1Vmn+GJQzG9LRWuF53EVCVfqHgqBBt8gQY2XDWwZTgD56Apg+fAuB4Lw5oX7CDtKj1A5QF1naMZezTYME1Ug0nMbwOpF0DT7aJAaxV7JbcN3+9V3mEF5co285ghN9zRuVEUheN4rEJzWGUk9RWdH7WXx/cFM33orouW2MIOt2TaSJysUz6bWvar7Av0DArfZic2Jmb5OqI8op4qA+aqBctki2GNX345LnW3lpXwvMWOrvFrl+KqLtV11Lv3ajqsiGJFk7x821a4YKXiQMn1BlFYsze/cFgn4BlwfURwIZrjN7EHiZzMouBeWaPiySKds4IztQ+jPIWjpOYw5kYpmTzCUu56Y/pJyZw5cOCJ5L6gesG9CRS/bB+/YHYfCQVEwntFFgycJ5zl5PN9jiGNEcK7LvjE/8pInT2QT3b/0aC/d9x4rq3XW1qdR2CRGxhsLapd3IhHuytTB9YZCttlfkT4JFFrDAVKcKOdzutmyn5dWHWjJcaKsylrp6DMfjhF5LgNCE759yAOWOAS73eV9LTYy/eiSHFW1DelXqnaVqaGB9bNn8dahAVS9WN6TcwYgxoKL//2tf0v9yz6FN8UVilfPVh+QZZodnaEug6GgNPgrXPgbS5gGYy9hUdtu+gK3xQ/0OI/gSe1/WUJW779con9YSxeFJbsEwC9GBcV0NsqpebGPAjDsUeSsa+ALlKH0AXnUpVkvbAQpcuY/Vy43FooMXlEal9yWt/4ki8hMl7/1Ny+3fzsVn4eWyRlKyyvlJGOwafWLsAi6VKCzZj/YLW4HeEhYgAAvo+7SMzTdN8c1hF1kkGoeFFlf9KKSHyHVHOLJ+UxREzBNlni+WJvLPHVJZzIL8GI9MPAHnb4XQIssnyiJsoZkx/P1NYFW3Y/I8SYyxaH1CK/kC251KGse2l/LTu0+pKLnPh+Gr9GXemwx1hDb6merCTMqMZSdzzAWNBuyYRFOaQ/Q2IDZ4rZcZPfiJQBMqWhvllom8BDkpMz586o4lK6PZVVIK+UqAHNn8KdSs4+FcZkVJ5fqyhX3USB+MmURbIWHklnJiPo87qDyukWFikLVpEEGJqfxYuLefsvH8k0yanuZQGy9yFuxR+ZnTmqV8x1bLGybBmyK6oMyrtky2HHSyjqVsgVlcvXyXGoiL/b+xAHLENLTrFyEJxQc5EXl97V8ap9WZs0naoPKoYjQeK/COl+JHI9F5dVZuQvPqV3llAqZjTx3OFCMtaKWeiDx55+lHZ4oBj776ClJKEjAqKuOSqf3urKPoJqezfNDq267M8n3PULTkHsTL3eWWTInfu/w2nZCh3k5kB7c3DxfYcWRk3kva1ExHAxoz/SBroLxglp2x+p53++WueSluXVnNsHACGOOCdMNmbebEiSpRi3RNCiWHd0W3IqZiOtTCd+E3D2AvUnYut/hY44HRqpxOcsp7SEk08ZR2ccleW1aYuVdkUdB8cgTI2d4amduCLe3tqZDlkfr9UOUyMOXTFxe9O9vhIwxg0UeeZMk7CgqNMZs9TUNBJMwzlmk8bFJzu1WDJjdRzOsDJfKVtQyA5dYD2KhDsOohZuQ1RyOF3cee1HFtAe7QLmYWWKvjdI2h/9vkWndLAD1EpyT13kamTQAjm+y0Wyf8AUrhpbe49SeD63ldONI4xR4UhR2kGLWl+049EfwN9J5loAytdSHR5DCjR//0NezA7T63uC3VIJU0FAcOSf+/YDkBGHKXCv3KctB5Oi5XfDXQeGK3EFd7ab7oD6YWBMdB9F6O/W2SpmvDOimDpSKsnIoggkGbIliEjCgYcWk4ipABvOOEa4JK31KxQe+Iii0iU9qiEMvjy/FHNJj1MWSalFcFiNG2gO8KQefwFXx4FWrV/Rw12JHQwjBNU34GDXGHQtkNEJZLEP+a4SLSIJeFHjBBlSitO2rWDT8OcXd+k33ZDYUX9eU3deU++S7MujvBqKqQSAoJGtGpUMc0l46abHi+TsB82iXSkkVytSTdsIbNnV3XJTQbXcK0zUfScxO55qGwWD44lkvkN7BDbwtcWs6uV086Xs7o6GDM/jEnS2qiocqs4fZylO2BKDTiMrk/ZgRpNx9ZfB8ehjpfsktIrelPcfxq+xCplNps6W77WR9w2+fAqrgZXe9Sp9yuV2utkAY+AvNlhe+6AeE376z6zxPYbunfiiK0eQNX70reQxbkROgoX0crCqyHQ5GwwnffQ1e3NwJvpozJGwaOsBpsw4nRiLlrAHRBBoUEQ5kXYkK5n9ctufhgkVw1n+69dKtK8ZUsO9V46pL6Wn/eaT6/F5M+P493AuzKhLCOs7Qt94g+Upp0Y/PBpEKSGdX2gq0Vq0y+QXxTt45IkPLsdAs/GWv9o86B/lMHTp0odH0AglydAiAIDIEkDmdpM9wy73lKak0R7IYT6ar6kprl/W2sX3PdC+Zh7nt4NH3wcqp8b5uw2nhg9nq9GOQIthYgKLKaStYHFw66pgB+NX81fUHarZhJMqtVsfYr9oFipqr4HAFBvNIYdWH3gzDTJ7yCdTAR4HiGqq3m1Kh88/GyPBuIAdH4+YbsnDIjaQyXeQqAX3vCxyJ61xYjZrZgShr3hqPZqQLa10j5zMShg969EpzS+9AQ7YnI4Cl/yy0Gl1x20Oj/bVtmi8l+qXsJGtX5uxLVurOmZBxCwX3zwq5DqGgosvRtAHtP7VQqkrEQPb19fJE+rDfWPdObhC+m+Z2F/I7yqwSbXIW4RoklrTqVloJ1GvBF61kcP5pdYogphFlUZ1q33kh31Zj9kksq5pXN4KD5CXXVsARj1t7zdGyOevxiIxxFxqKE/RVJTFVOUkod1ad9HmD1gGALEZXhY5Yn2i+lwZc5eUC89RxjXM+tf3TJiWk4h68heasOoDYQaQJFPbRu4K4XM6T5sN92hu1+O9F63+HtLvLt479HchMou7V1lPj573benmFBiOdQVlmV8E7FpxQtFc47yI1b7LzSXSyZWC753aypTl1aL3k0YHq4dp79iyaS5y7nf0tC4Q3cRrqFtQg10483KcoSYlJxTXBeUrj2wqN3Tg1vX8rRVd0vXjvVcD8Sxs7qBjexfxohDioMuZxY5+kUUHtE2OSV+XfYqSG4u2O1y2tI5Gf2sYbQvO+WKVUBpmz8o9SLl+IBksTz4yDrESAXaZ/nmSNpn/ALTGmISePdXp4bJBkRFZ4ZpPTQPvV+eFbV2Z/VHwFJ2wpgz1REz1eYAYK5IuzSjBJp5Z2avm60X/k2lYzXJPoPlxVK9TtD7J63VmKXKCd4T+oRwpvU2iPvDhwGiC80brN1uf48z2+SH85cKJoqOjZmtqT8pU9JbOoN/gF41HZl77MdhhSCgG3HTgJRHdS1PXY91leXTkiGnxmZVi4C/zR5Iv6w+jaXDHlu2BKcuyIWZcib76sH1O+3hqu7sEHRGt2bd/2m0EU4ec+ApVj3pEkksXJJxlGODPUojVr8n9TstwxM8GtvOhBbEoN2lsC/uxzG5YN4yA2siY/N3xZHR3ZY2UiyKUJTblkATbsgydL59fu9MqlKlA+zSWztSVzLOG1XF7o+B2/Dzram5Oa63y81pv08VY7w/D/A3+PDu2dma1nUNZ8LHJ+72ABg3cgX/G1QkIkUqv50/l/9Wd+M3mDtQ3GoB9SC+DQ34o9Gr3SJJcxnjen8V/jj2PbHxj56G+wvLFHpY8/ncLfO9VxM2Rm/h0xRcKjU5MMgdQfQvgMZPrhfnDYyTq0JryxBf1xQnypEZ4aiXafT/ACY9s6g12eUsTBDyUh3O6eRdhSy75KYa4I3C2Ig2fXSgAJPFsg8DKa65TLJO6ybmBrtUGC6N008qfOEIw4ZtPxgNHVX8m8PIFCXcaiYQFlHOOt2BKgpfiO4pQKhe973rzvIBbMk+ssB3LLtJ+7quMb4M3dXILu/7FWrMsX2xPqIxxjtOAMWWaoBXZIYSoBcLb54d05aqi0b4jX+yxB9D1oaruw1f/1ovQ8HKlaTU/ookagTL+NK5bIrgXRF5KFYwZaHq3ikmprtn3E1K+rHSJk0wzgHcGncslH2kqe4DwhD6Uk6bIEiqJxurIay5ArF2dKPG80K10j3YAEBELQnJeNIum7hRRkY2s4gNei3orv8soD5IL4/mB37Ffmzvdb0rJBtQH00+F5PEANEzRYPXjedV6D1xJbJT+VhslbKxQ8sD5HbzcRcCnSzNEiaJ4k5VR2BW8o46y9ubgAeYtofVG3FmacOltHZbBKWDhGVUnq1y0k0u6ciPyU3xLUHINAxvSCdBv5/hAncER3gzezHmyPuVv+wSj4LVG7ZvZzL869hs6i3n+WzsFOdjp7xX5sjf09NhyuDNPDH024z4ld9bc7BairkoyaFuBlf4fkzBMVbTHPqZTKas8QKS5lU38xFgNQELq1VTq6DSNpRLTsTEehWp5QcNsKUf2eYor1FuF1rf7e9yubP2DJyI9OCV1bCK8OymZx33/wd0G3ey1Gwvh8JUR6Sx2qthyqsHVcIIocOIek/05q/8Eb3r9VWdEWAQGsQd6Oqo6eB+q8W1n9riuEy/lyWeu5vYvnkgh38IvRcq5/Uweah2ANjTUP+1M+w0Jg2F4DY0WGdOdB8CDAXqvxjnHRC6b8SLcO63tIt5ihNpYyTecIYrU1IfL6H9myoOA1TYQs1QH/VMEYCi4fNiHe2fMc90vnWhGeVOXY1FM6KED95LOXEelRW+U9+PWgFHKLwH8b0cz0MG958OO+DwBvGs106J8l4oYCbiGg6HY4U7QjUVgt0AvczPJfTgVnbLG/i87/4I9JRf0R7jsMvB+YR6Gl3wzb7pamvPyxWM33D4RBa8xRbHEnRDwT+Ju8hS+Qyr1rbuFtJAe/ftpKylJ1mjES4dWtVu5xddyTm+CX9LquM1fdWq5w6u49z4phsHvdmsgmk1Xt7u4xfWvxZdaTnUDm0/LH1fNYlHzWfIS4um1MuSWsBc+jO6884xHGLG+anEnGLLso7f5PMyHm9ROqG8HpduPc9whnUCyv460RYD1dx5yMo5AwVPEUhjSobLRdAKgONFLYajQ/MrYi77t4T3w89/hCB+8WPs00XzB2QP2OndJz7lQtPCePJYDuXC/cTcas67RoFyACnwAA/H9IK4IjsaaAkXRIGjmeiSbQ4iq0LwUYe9aAaBLIH57/xNxOpd1Kvk/ABOA7H9hmhor/uQdS+ogrt+GyrZ5S7JBibciy01kGnueZBuFnXAXKUzADJ19EHNVsiMiGMPXR076W4zSmX9RCTR7IKVFsEssknqjE/IkM1X5DT1DeGyAzBLsmvgIjD/3y1SS7WD/WJoZrFTBIdtbMSM3NqvlwreROjstHgPG6joYEPSYudaBtEg9mA/BhP4HYof0FpLrn0iSWpWKGYjgQdvnLMAMtPULIG1/bhY/RI0gFZppbKwKlG3gYk0p2cvEGv9S2+fE1eNLq+ow174DT2FZZvEN+tlf3miUveNILVT+/uzgJqXyi3rHkt17kAACWvGA7bhv+EIBP2cvElw9tsNYSJ2TecVf+ifwKGC19/4v+k6fAXvDMfFZA5u0FY9BWzPg9WwSi7MxtxuzvjxHNsO7UjZD+Tm2YLmRnCP9C9mt5b+jE+xWNj3M4iegDLBJ5pCIcbe8qZVht6SZ+GJPDQB4usnzF5XwV9659I4bAxBW3aNj8XohpuXn8OyB9bIpJo4zHKDA0JxagILn9lhIzkvAPMKRnJD1B6Yfwhlu4oJmnsr5woJL80Px8WglGFcYHcujyjdLIvJhUWlHsDdJiZBuoj5kKyaH0Ci1D23LjnaqB0tF27UrwH/UKHjbwDbR7n/8tEmcsjg94L9gFIpOwO1FrVRRZtbrjTeplpByt1IxPl876dOwOmR9yIT7KUzbXUwS2tw7SqH/BbyWipc6pcFLteA0x4HZ285scmLSg+RcSlGb7U8VY8lOuC1zKYNc2Y6UN3I0lhUvQArvVu5B51mwgvYA8Gp4UkKZsDjrxrPju0YHRv9cx5NhbV0JclgAU2GNJ0VNZLOyp7bH2QPE0UpcbXHNALmlPWKXwIqHyD6OsepiGCtStzqOUSewrGoOOvhr4hi1QDUQ6AG7QB3wrqLpLmS3886jh0YKvR2fy6G3pTTDhlnNyrskVEMx9B4BefioNCnsXIcZzy8itiOBPShUJw9TjHb+gEmwt0rfrY8MPDshJi20ugA3Zj/tD/Rb7YAbA86GCNyY0iaO9WJf7J2Q20uxjcdj5kk+VUtXqPa32fNi8Z27uL2Znr41zHuz2gAgE7Feh0oydynvQtfB8/CbM0+sh2/0xeyJbWC55/cD5OAOUsMcDew6u5den6QAORDK8UQXZL05JQW7wGSs8NGE56t79je4Zc1VctbRS/O7cDOZCqc/VQgDDLKIYoACzEhgSlYCLw+kinxJx56bCA2lz7G9iT+DpKttcix8LYgEtHusJevMW15BZxBKtJuYRDtCKFlXgoKzv2E90mSOlXaJfGwX5aCdcgRVKU5J3/9Alt3pl+n93H2YyvBlC7j/MOOa+IniqvOeCUzgFmpA0GYvlVwZFkzno7kWxo82uyqMH61hSVUkXxpqx7THvXMYmed0qosrMcwQcZap4ZbjqnFIK2bx2+CAmwIyQw+jFjgleAfQ3DhG4Q41VR4tg0wOs+CuTp1qj6Q3vGbgN6zFbHmVR1ciuHs+PcFaeNijL7GALj1xpR7JM4J22ANicWj8YgPn0PjRBg2HRg9MmrjvDciDUW88rTz2nQ1hRBuoolBZdYDnY/YOD6VGciWH0XAw+o38wgJ416GHgH6jB6bvifQBmYP/pij4lsZtemYu3jgmIlGzUUe2Q7JRIkAuQs5KZ4zACxaKucnSlul98trVdCxDAX5KslYxawlYRrcoltFabhlFp05JMCstCV6ZlaFj8d/FVFJPwGQB8U5p+1xu8gjDz0fG80ME3eDx/FQ/0HVdny/wyD19alxpHcRdB+PLaXukj/9zhkejwDyQiHeAhyjB9JDK2dc4sQ6mk/Q4+2oM4hmv012XcTAaz8C0TpR6hUPbeE74HIOS/ZVu4fTWZcxe20EwepDVt9ApfbD/fETAuYIPgNsqbkN8gNWG33x3MG5LknAgLAAoi/1c/j+lsli/BGUO6QztA7BIlqVZYsY3XTC+el38fXjk96PQl3It3ZduIBOVwJpcDKzJxcCaXAguhrCaF1LBweeGTZGqHQja7Zc9CEddNJ8lDpEA23/Rug/qba77nHskJ4LAwK6JCejvxuZmvCQaXxLd5fmhyvwKxrx4Hcu8rGEz1+ZxhZxytOObDMpW4TVRWQeIgqcyLhBYmjxEHeDTAQX/R8tIRlOBQiXinw+GyzKjjvFiYP5oFlmwQ4FKY8pBTr4BVA11AS2TuhKcX3RxMW02b+LWETDLvEBNDv0zMtQ/MUMFfnG7Gg9De78AzSpvonsXZiPdLsHLO00oMVr34tQpU/HX5lrg2LPtZR37QxSCeceC8WSKXs1OMh62yud361VqGQSMQq/kIbsIi3DQm6nyhYw7G4FxxzWwWKDf/217GWdhvd/Xr/PE+YcboIOa1GXgnW6193unWlnWo3HSwWpFfDmI4ktcQD8ck3vzJNiHb1PbG7YkNPhIXBSp6qLgoLP1hjB8JFZKxUeuvW0I/EVMmKlHCXsC+Lo2N2G8l8TSE58SitpwY5/IIBf+hq14Qo3yN9TiB0P6eXDLNCkumkuffTD5sv8jQ9V5UiR5RgTtnXBg9QLzzXnzi1T27NTeDhO16rzXmH6sd1gjvhBlshTG84hBFynNKVQqX16OMR5buDxaX8tpECeALMqr3M9LTKElzrLuw76fJs2vCu/7AgihR34lpKukms3wuDNUElZWD1/GuJstJDXLUF2uuItKs5K59jeI7GCTC/MMsFVLlWbac3Q8YPo4IcIfhMz2OfY+WPut4Kjmy/9V5nIsY+vCt15d9uzACVZf5CuT7nrj4GSFjbsQmxUv4I9itkKgCB43T3p6QMgqB/AQE51RKLJ3syTIIAZnqOEfQLwvFaRQ+RZbAD/Cpp5j62QB+eYdzU6qreJi6NYshna2GIBbQCKuE7Zmr36prRnkeddpT1wcHR3XaeLoinO0x7VDfAa4Nalm4S5n+gOxB3hiZtTnPRNgIVr0qlVTIybgbTZH30bgRUklLsnq6vFY0gPpx2gbWQtpS6u1WZ5b8eF42tt6exdXmNUm+31tOs+Iz85PPu9vMfQOZx+MQvFqUtTDCTroJtWjbFIPaxWBh3Ji8k+Erc/bOX4zla9PS2h90qGbrwqluC7PKiDO9jlavGxYgRxfj4XdzQvT4uvLw/H1WG4sfP3jcyzh+QI0xyx9xXz+irSw+jaw+tKyxyhl/wnSgz5l7ZMVc3fSnAg8WXj901h/zOXl3xpWfpNa/ii1fID6sZLfmx3tT/xq5QeuWf6D/+/yW69Z/uez/r/lt12z/JdjlB8+GVF+uo0XPTOsaImTXYVKPs1AlktmxcJ/Xre8i4OV13fLf1XepcHKe/2/K69vsPJW3BJj/mIMFZZpq5LLnrLhZ993iJ/tzQ2Ml86atcZjgU2zzKCkAKcvWJDNbi//nbo=
*/