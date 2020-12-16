
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list/list10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct list1
    : l_item<
          long_<1>
        , T0
        , l_end
        >
{
    typedef list1 type;
};

template<
      typename T0, typename T1
    >
struct list2
    : l_item<
          long_<2>
        , T0
        , list1<T1>
        >
{
    typedef list2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct list3
    : l_item<
          long_<3>
        , T0
        , list2< T1,T2 >
        >
{
    typedef list3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct list4
    : l_item<
          long_<4>
        , T0
        , list3< T1,T2,T3 >
        >
{
    typedef list4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct list5
    : l_item<
          long_<5>
        , T0
        , list4< T1,T2,T3,T4 >
        >
{
    typedef list5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct list6
    : l_item<
          long_<6>
        , T0
        , list5< T1,T2,T3,T4,T5 >
        >
{
    typedef list6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct list7
    : l_item<
          long_<7>
        , T0
        , list6< T1,T2,T3,T4,T5,T6 >
        >
{
    typedef list7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct list8
    : l_item<
          long_<8>
        , T0
        , list7< T1,T2,T3,T4,T5,T6,T7 >
        >
{
    typedef list8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct list9
    : l_item<
          long_<9>
        , T0
        , list8< T1,T2,T3,T4,T5,T6,T7,T8 >
        >
{
    typedef list9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct list10
    : l_item<
          long_<10>
        , T0
        , list9< T1,T2,T3,T4,T5,T6,T7,T8,T9 >
        >
{
    typedef list10 type;
};

}}

/* list10.hpp
x2V4BJfjSVyNV3ANVijN+RVr4Dqsg+uxIW7AXvgAxuImTMcHMRcfwrm4BRfhVlyCD2MBbsNn8FE8gI/hq7gd38An8D18En/Cp/Eq7kQvtsldWAmfw2r4ArbFFzEa92B/fAkH4z4chfsxAQ/gJDyEB/BNPIhv4XE8jB/j23gG38HzeAS/xqN4Cd/Fq/geKt8qOIbV8DjWwg8wHE9gVzyJvfBDHIj/xKF4CrPxNE7Dj3EOfoLz8FNciJ/ho/gv3IFn8QX8HPfgOfwUz+MF/AK/wS8xgAPiV9gAL2Ij/B7b4g8Yh5dwBP6EY/HfuAh/xhV4Be/Dq7gef8UX8Dfcj7/jG2gozfaLpfA4lsHTWBb/hbfgeSyPyjuKFbAKVsQa6I1tsRJGYmXshLfiKKyCY7EqJmM1XI6+uApr4BqshfdjbdyL/rgf6+AbGIBvYV08ioHI8ZD9XOrMpC5NOR5yHOP4wf/k2wu18CGsh1uwMT6CLXAbhuGj2BEfw9txO/bCJ3AgPomj8SlMwh04CZ/GPHwGF+NOvA934f34LD6Mz+ETuBufxRdwD76Ir+AePIR78QjuwxP4Mn6MB+Q9qVexG76GcfgPHI6vYwIexOn4Bs7FN/FNPIxH8W08ge/gaTyCZ/EoXsR3sTxl9x5WwWNYE49jPTyJjfBD7IYfYR/8Jw7GUzgUP8HReAan46d4F57FRfg5PoXn8Dk8jy/jBTyAX+FBvIhv49f4FX6D3+K3eBkL8Qr+gIbS7BfYEn/ENvgThuHPGIlXcAT+gmPwKhrxVxyPv2E6/i7XK1zXcULU9xNVn38HoDJkyvsck9AXs9EfczAYJ2NvzMNBOBXH4jQ04nSciPmYh3fiHJyD9+I8XI534zqcj0/iAjyM9+L7uBBP4SL8HBfjeVyCv+BSbEOaC7A9LsOuuBx74QrsgytxLN6HM3AV5uNqXIBrcDmuxZW4DtfievV9Jqnvwxgn7zNVlOs7b/THShiElbEN3oodsQp2Rh+MwqpoqwcolOX3dFIP4CvL98MaWBObYi3sgLVlef7YDesg275b78RcItjeewkdVOGGvPvyV733ciPeeSn6vsuN61NJ3m9R320Z09TbkEdYSdhBOEw4Q7hM8L2Nbw8QoggjCObbPO+2eAbP4Bk8g2fwDJ7BM7gz/An9/yXnZpivu/8/pe3/QD/qLG19pZVy0g9PC6bzEU9pf63E60bfO5q26WaHb1qj9rvLNIbQtZc/JGmoJ2moS8hS2vfr0xCfNK74fs/U9t/Mz+8lHdY+lXLVdOjT5esiXbFeRcsmh+UWOKQrxex+urYSWYqb5WNrI1/oVfTb45NJx36HdKTRM1umG98cKOm60vajLnGofTlpv3U/EGtiNOaRvkKn6VNWozWNF0u517bweteptPPRpV/5Tchv+r6qohhvF2nvq7Ar45Q1bYKtvw/9Tf+N+nAZn0DwYzxMxi2ZnZKWnMN8ljaJtnhMU7LVNl8yLScryTL+GuNTI+WdBU07RNrLWdrM7mpGWUoZKOO1m6vjunURVLbotjJd2ZdCnK4LNkX3txd3t11X24v6zoek8QdCZcK3hJnKfmVPY6oxL57VwKHLUHybJ832rH6zvpIufv33G2TVSDqt/VEmJ+Yk8k/dtqJMIz8O/bDp23FNcGhDPF/6Lawt5V+TYFL21RaWvFk+bB/P8bwkfTjW9FHTp3ufhbRp+4xjX9a36wqSPvgaS1oaSlrOaNOSUvyxvaTpYJGWbfT3FtI3j5t9sZW0zy/nbcRK3keb87ZgJW/zVdK2XSXto815G66St8ly1aasr6XNV+3vrvz48r+Cp6165svPL/7605SStzW7kW2+Qg1yLYKBTvo=
*/