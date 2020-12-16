
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
pCFybWkvfsYyPyk5dgLdHgyyjCu+a/k3dra42DG2Y92Vyb893uf7u+yVn+3A+A33X35ZjzoWv7LSRkViaUu6qOyP9mJJiY1OuM9tcU6JRdZj6T913jIvhEqjki3jUVywzuf/+KyO/ZrE3lhif5T0kbIfudqJnS6PsVEF78uhF/slJR5ZjyX2y3nzlChtj3cZc28k6UHSENJVvj9AL0Y6Z+n153CwEx/n3XxjCBGztIXPO/7vlMs/bsfHyjbWiyGleI5/S32d4Nwqp1bbc0B56TMhMfmQslk+Vzem4jkHvEIsshrrOWA38+QUYD0HvMY8OQVYzwEHmWc9Bcj8OnhY5sspwHr8H5P5cvjbHv8O+bfHp8Tr10Cv7MVz/Ctll9XYHv8yfp+rxFKPdI3lQ3VjKZ7j/xSxyGqsx9A7Mk8Of+vx/57Ml8Pf9viX2GtJ7DVIX5Bfhm7sxXP8nyMeWY019ksyTw5/m75BfhXz94H9kvXusomxP39bDR7cpwD1qu4HtN3Ouo+ybtsxZuTvMvmjrSDHtPoc5lIpfz7XlfOHJp/CrF87lo06v8OS33Zpn7wZvyK/bJv8OFma8yvQeD5K/6IJj+TvX9SwOjMSoulJl3cO/XvtvD6u/UzL8KzFaFv33tJxuL7USV3SN3zH0EgdY0qR6l7v/K6un1zJO07+fla+8C15G7V5F6p+bMf2kf1dHYP1b1/1OVOpo0HSd4b55j6BjWzr7JbpmZ/9vkX6fbUK3ydIv2+U/T5cvLOJ+b4/uTcO/HHa/J3dR7jklF88k+eGpvmbdq85du6d8benVjvg3Mzhp772+nwVvg+Ufl8k+32j9PteFb4vm35fsML3TfvEtJ7U2gv/OXvgmhFPNB22vkrrCtfs9ynbYfr+3G1rP/j8lNE4+9TgSbFLtubY6ytnv++bfp8v+33ffEx9wc6u7/rL2UuxVUN8P35zf6ozDbPM78aU6025Dk0qpXo3proPjupdkfVxPnbEBeiPi7AvLsZxmI7JuBRX4DJ8GjPwWXwS9+By3Icr8G+4Et/EVXgJn8YfcDXewmesbYHlWhHdJG51W+Dt0pbwBXTCHdgIX7QuL9d9UFNneWdps1kDK2BNdMZaaGmr4CrLj5Pl1W0Vfpb8f8EK+Cs64x2sjb/ho/g7NsM/sK20ffRVwO5YCvtiaQzCMjgay2IslkNLeXbdpTwVpTyVpDyOUp7Ksjzrlmsd1iXLO2AfWd5Nlm8sy7vL8k2wNjbFR7EZNkMPbIvNrW2T5XoEG8v61W0EvGX9PrL+9rL+DrJ+X1l/R7S2oZT1jZT1WdtmyDtGH8Rn0Q2fQw/cgEbcKPW9Cbvi8zgIN+MQ3ILWtr2Sj5Pko26z9I5s59PoiGdQ6lP+hqcMOvX5miy3X5Y7gDXwINbD17ExHpJ4D6MP/k0Vl18D+3Edk/Ufl/W/qWpbESrLucpy6rYVV2S5q7Lc3yWujyWuT1THT4asp5bO/va1rOcbWU+OrOdbVfy7ZPmKOvE3kOUbogM+ou4zdZfl3GS5xrKcu3o73mW5VrJca1mujWW5B+TvLfk7jOWIheXk3l0vOT/2xgbYFxtjP+yM/TEAB+EAHIwjMRAjcAhOw6G4DIfhUzgCN2AwbsVR+BqOxrMYgucxDK9iOH6MY/ArjJD4I7EcsUahE0ajG8agO8ajFyagLybhEByPwzAVJ2IaLsMJ+CROwqdwKm7CabgZp1v3M/kbEOrr7GfNpL49sAI2xxroiXXRiJa2UUZZT5ysR902ylvq3wddsIPsp77ojp2xHfrhY9gVe6I/DsJuOAYDMAa74wYCu1sbHNf95vfuRVx2MCwgBfHfcX1pT0LaTtJtl9PP3DY=
*/