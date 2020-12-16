
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
KYaUQ8onbSTtIh0jBUyl7zApmpRDWk0qJR0h1Z7Gv5EmknJIK0nFpAPTvH2HvS/vy/vyvrwv78v78r6q+vLz+VPm/4+fk7wg/mLN/1+LH+nFHc1z802aOHzs+BETp8SOGjJlRKRqLkAlVuCgKlYgymD+/1ylv2An89/2HVfk0Vw7o+vq5/7f6WTu/zLD/Dybc+dUR+dzFTUzmPt/HvUsN8zX/bl3rOvfbDDv/wLW79PZPva8Ng/X67e2440ejEFvLU8XX/244zfxn4jO1nHHq16e0cbjnrs1fujF6i/h6bii3vFD/5rjh3raj+IDcz+KJf1MQfMHL4h/ovHpxwO67n36z+lHEU7ivOh0/vX66r8TdHI+/3pd9bg4slxwpeuT8whc42K5CFmuoZPlNsu84Eun+7p8Dhp+q2fPQr3zglf9eeh/6llo8et//eehF2t8h6qM7VCV56PeZ6N/7NloEeem/aTTpEYzfH0GzPA+1/S+vC/v6897/Vnx//z+/8Pz/yu/6Q8F+tjihKbLb+wyiUnZS/qb8gOwnTUG0PG3n+s5Mp3HAMrvQSrCTBuafvrE/qalZudo5nYiZFET07S3mnFMXninSxOTF1XdOCZvQKc/JyZve3XjmLy4TpcmJi/c1zgmL6/TxYvJK/Q1jkvL73Rp49JscY4SAz+AzK/APngz+3tge4lP0T17cW8umis7Vj1GReaisc076niMnLeNe0DwkKz/iMSRp2YrEUsyl4wqjl7mkmGuTfJLZlYofdyKUUyMzB3Pe8nfGgfuGMd/QJbLTs4ilN8eY6SOs7og5basyr05Y7zPfLzPfP7IM5/L6ymfN+9bf0N8zd7NAhYv/3HY0vf9/5xnPnk+ct2U62mMw5wxraQPXxusi22xI7bDodgep2AEJmBHXIidpK9zZ3wMu8jYxF1xN3bHvdjD9mxHroly7YirrK+tLFfXxXJxspyMveu0j2qeLFfLxXL5tnydLxdQXc7Lcr5W2rOfpQ+m+TVU2nOYtOdIbISjsClGYWscLe08BnvgBIzFiZiFk3AZTsa78Xp8DmNwk/Qdf0f6ju/DaVK+6fiLQ1/yK2Ts5qYYJ33IE7ADJmE/TMYonImTcRbOwVTMwjS8CTMkhikTH0QTbpG+5TsxC9/HbDyGuXgSF2AN6TveGG/CbrgIB+Hf8Hq8BafjbTgbF2Mm3o65eCeuw2W4A5fjK3gX7sK7cR/eiwfxPvwc78djuBJ/wAfwDK7C8/gQ1mJ7rsF6WIBNfGWuCXwEe+Gj2AcLsdTPPmZtszMXr0+m9zlk1Z9D/if7ZXqfRV78Z5Hevpp//HlkOc8f/W5g/FjScFIaaSWp+Abvc0nvy/vyvrwv78v78r68L+/L+/K+vC/vy/v6b379WX//T0rK+sN//29C//c+9Xh23Ubp/z4ieiArTc7OHh+fMSvZ2vW/hSxTqF1mbJZlqcQUiQ+wruuIdrnBKZmpibKYbV0t22qWGRqfnpq2QDK0riuI5dJUyw2ie/6cbLrnJ6ezlCUe4XCgj22swXIn8QGBp0OVv+U6rMR1n3WJDWDAHOexAdHV9TEQefz9uOys5KltBI9iIA4H62MgdlU3rmPE90b5eRYDUbuSerb01cdA3BpG3ob19CQGwrLtjsn6F0u/kzzS9SFsu3Oyfu2Okphusqw/1I12nMR64mPlb+7yPiHW/jfqk0G8l+Ur5O/fZCB9T5R/t8csHJN/d4yZiPHT7wfbKUSpYfk92w+21tHvB2V+xvvBgO+N8vNsP4iuZD+I8NfvB39XYmEM6+n5fiBj+DPOmKUtp+Fi1u/zu6zf8eTDdlLW30O7XufjxEubPhasikOR9wmqeRgW1jM=
*/