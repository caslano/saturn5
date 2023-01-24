
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
kRlBrR+5yUBrjdx0LQj9k58XVaO7fM1Wzvf46Y8uiCxHyrVKAfdVptQYAZ6mocst0Li3IPA4l+dCN9nWUfefCzmba2IbO90sCwbb0mIbqP4MCznbKGoeQf5qD0GUag+BXBWdIpv+r2FPxBU+fWfF+73yp0LXfmoekRTxHVrVkPLOtrAHLU5fyHzvJ49nUcHU+YYBFWcBu+Nx5Cjwz5+xYOQXk5NoIu5Cd4vPqRxiS9oCvL+0pMOeKfp+YMZqF5XuHr1IGUykfUC0WGXbb5FNkL++zjlIWDZmyFAyrI8xZuNM1UjD78gdFuazx9SpderCtcWqozpYI59pTn+DhSW/yZ71RjovOBrU9Pt4XwrPnF2BvMn8K0DfmpaO4Gum35l40TWGgyXur3JGyHtwVvZ6cLx0Tp731LdiwM9lvVSXDjIPZ+svaDmHMDZyXPYtT6dMMF8e57ApYIxjKNFpvr7maN7deX3VTsABJj3GJpUUkPE1poAGbX70OsLpFjj0k9VykF1qtVVt1In9I3tMur6ky9Vu3oXbSVMwmKI5p94AKrK2SLdaa2/T+ayxtsjSAvUVte5qY93UOsbzDlkYHWfdwx7bTC5xmLscXVtxy9ed4VOkeiHPV9NM0tx+pFmLeI5rCojOPGuERJ0f2AqcTaOIHP05rYip8PzntBVxHrrZsJvcnXae35eX+mgi/1fAuAZnbl2oREwsY0h4XnuU
*/