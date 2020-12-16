
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
hWOxN96KY3AcTsPxmIa34YM4Af+BsbgM41CeK1BX4/55xFDldxuHYQAOR/tyWWUsFynLjZTlRqF8Y0TqRshzWU79jZFO8p5MZwzGUGyBXbANdsXueA1eh93wJ4wlFMt658l6a2KUrLex/D41wQAMwdbYFPtgM7wFm2MKtsBZ2BLnYCvH+19Sj4HUb7Ad7ftf3eX6qwc2w54YitdhBF6P4zEMZ+EN+AD2xjXYB7dhOG7HvngQ++PnOBBP4yCsxrYj0PaNFaljwDaSfvU3Vh6W50OP4FX4D2yFS9F2PyJ1A7jAxf3IQjk/LsIAvA874P04CB/AWFyMc3AJ3o0PorwnKM/7yWvJN/V7gldLvjXHYGyBXbAlDsZWOA5bYwq2wQxsi3OwHT6I7fEp7ICvYUc8hJ3wOHbGXzFUng92wSbYFVdU8P0reffqL/Pe1YV45+p/4vsyxjtW5b5jFTu8Bu9ZsW7epTpGOEsIeZx37AjjCemExYRNhFxCIeGKJ3j/ihBOiCakE5YSthByCQWEs4SQJ5mHEE1IJywmbCLse/Liv7dlDMZgDMZgDMZgDMZgDMZQkeHC9v/H+/+EmMy4jExrDwCV//b/MFX/f5Hy7Lk1wYfQklCTkawj1nZ7kQOHx1jblEZ3D+3F5+mivWnjusGfZ/uW0vf972M8E6VNo6bNMn+SNsvaPr9Ou4jflYxs1cWPZr8VimMSc8VXMI72PEyX57xtCT4S1/d5wFFQGkdr+0dHBL2Inz4Px7FF4qftF83F9t9j+yEf6rZPJlUkDpJHLuIg7RcvYf9nRn9ml7Y/sxrXK9O3rTzR5ol6tUoOflVyImD3G7+4a8964ds1yvcg5PzFsSDPOdXfg6iv/v6Fh/MVyHxty56PY67s+cKN548Vfv5orunzl34GmVnTx3gOWYHnkEHr+c41YTwha73xnNAYjMEYjMEY/hzDxbn/576tiu7/b6pvcvT3NszN/X9OvvP9vzf31ZW597ffVxe5uffPy3e69/c6fpW577fn3RQ39/0mV/f9XsTN9T2/Nm8K3dzzh+u3TeZ4u33jft+433d3v9/Der//7InBUXsz/Wcnr5q6Li318+RLf7+fk+/ZfXyeh/OZPLzfDz9i3O8b9/vG/X5V3u8f4x7/DCFoA/f9G4z7fWMwBmMwBmP4cw4X5f4/LXFychXd/0eq7v/tfQxsI9QmPKuo1P9/4LiPHM2WByUmx0339DtrgfnOfUuGB0rf5XJPGUKmkSS6mdL2o8g0R59k/ibpj4sOmPR9ayfFMBtq+rWVPquKZTzRpO2zKMmk7b+tjYu+/euS9th8TdoHJyeme3zvrE+nmf1k7R1R9+xgl2z7Ktl2IKGeku/abY+xmOlWzYt7d1f5zCri9H0KT0zJSE437umNe3ru6ada7+knD0qaOs6y/bmNY0yHf9m569ZLe0+/yCTnINwm99Z18Hbdu15Xoz82w2uxOYZhCxyJLXE0tsEUbIszsD0uwg6YjR1xOYbiZuyCz2JXdLxDl+/+Xbj68k7b3zEA/VXLZclyV7lYLlCWC8JAvApDjWcGFX5m8Fd+XmA8K/D8WcGZ/sSJZwO5hBPGMwJjMAZjMAZjuATDRbn/V26Cq+j+f5Sq/b9F7v/vlfv/uwj+3IfuydXWsQ+IsMSlxiXR3YTn37fR12PXb+1ZHbv9nv6Thtp+qK310rp68NDqsmGJ/zxCA7Zj+Zcm/qoOyise//s9bCNgj//Ieu7j39v+DEK+d3dG4n+aEET8Q/Y7tXFw2gf+HqTBus0K7oOz6n0gz14s/D05qfT7DKrnCy6/MVfEuHzrT5Pubixnf/+kNg7D5Uqf8u86pztSSXUCH9BP86Q=
*/