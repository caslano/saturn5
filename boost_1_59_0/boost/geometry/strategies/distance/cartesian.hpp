// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_CARTESIAN_HPP


//#include <boost/geometry/strategies/cartesian/azimuth.hpp>

#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_box_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_segment_box.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/distance/services.hpp>

//#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/relate/cartesian.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace distance
{

template <typename CalculationType = void>
struct cartesian
    : public strategies::relate::cartesian<CalculationType>
{
    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::pythagoras<CalculationType>();
    }

    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::projected_point
            <
                CalculationType,
                strategy::distance::pythagoras<CalculationType>
            >();
    }

    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         detail::enable_if_pb_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::pythagoras_point_box<CalculationType>();
    }

    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         detail::enable_if_sb_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::cartesian_segment_box
            <
                CalculationType,
                strategy::distance::pythagoras<CalculationType>
            >();
    }

    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         detail::enable_if_bb_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::pythagoras_box_box<CalculationType>();
    }
};


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, cartesian_tag, cartesian_tag>
{
    using type = strategies::distance::cartesian<>;
};


template <typename CT>
struct strategy_converter<strategy::distance::pythagoras<CT> >
{
    template <typename S>
    static auto get(S const&)
    {
        return strategies::distance::cartesian<CT>();
    }
};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::projected_point<CT, PPS> >
    : strategy_converter<PPS>
{};

template <typename CT>
struct strategy_converter<strategy::distance::pythagoras_point_box<CT> >
{
    static auto get(strategy::distance::pythagoras_point_box<CT> const&)
    {
        return strategies::distance::cartesian<CT>();
    }
};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::cartesian_segment_box<CT, PPS> >
    : strategy_converter<PPS>
{};

template <typename CT>
struct strategy_converter<strategy::distance::pythagoras_box_box<CT> >
{
    static auto get(strategy::distance::pythagoras_box_box<CT> const&)
    {
        return strategies::distance::cartesian<CT>();
    }
};


template <typename CT>
struct strategy_converter<strategy::distance::comparable::pythagoras<CT> >
{
    template <typename S>
    static auto get(S const&)
    {
        return strategies::distance::detail::make_comparable(
                    strategies::distance::cartesian<CT>());
    }
};

template <typename CT>
struct strategy_converter<strategy::distance::comparable::pythagoras_point_box<CT> >
{
    static auto get(strategy::distance::comparable::pythagoras_point_box<CT> const&)
    {
        return strategies::distance::detail::make_comparable(
                    strategies::distance::cartesian<CT>());
    }
};

template <typename CT>
struct strategy_converter<strategy::distance::comparable::pythagoras_box_box<CT> >
{
    static auto get(strategy::distance::comparable::pythagoras_box_box<CT> const&)
    {
        return strategies::distance::detail::make_comparable(
                    strategies::distance::cartesian<CT>());
    }
};


} // namespace services

}} // namespace strategies::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_CARTESIAN_HPP

/* cartesian.hpp
Kjj8djdz6v89TzTILLKKnAFhvkEN16FN6UB6EAR3m+Zhk6Gsm9leePlF9i+8/CP7zeLyFDwz/Kscarc/0vQSfpR/hfrUM1uZrcJVJr+suHYTKG86kS9U3nFigdgi9ov3InjWUlpukrtlO2Th285PJ4V70aVeGa8ernuyt8bbjDxcDPraEklwlWqu++vK4TnlF8JnoKnDZykJkP8KgTMv0zRGF6Mem8YWsfJ8Ej/Gg53sWpvd4KJXzYdmrnCf1wfWGzhBDbup/QmpLKkw4ASdxQkRR6ZDRl0hH8iJoMEkLgWvb3EPuGfcJ+HbsrResG+56xXxmnjj4QKJ4XDVVUPVGll9CLRuhtqOxH5bPVLfVBvQ6Ti9BD1T02/nTwgZPvX/9lovQpqRZEYuo4BhG5OMR+CB+Cw5FG48n8EX8j/BesEZAhnBRwEDTA5PzIoN/x9kHcS1x7G1/dYOTi77C/xzWaSXHcF0M5CwNssKYJ6eqETplnMbu+2QsL65Pb3RyDkrvF1Q5eAryuBL0uVqjyqsq+qhehqIJZWf0+f+UP/+/84ejrxOn5Qif4RnM00jf5OXJBrNQ8vQavQl/UWTGYHnHgx34vyIq1/BXrAv8KG6vCXSxyZ+nrcC1Y1BN+8zJ1iroVZfrP3Io19tLf4Ug+XMcPVPArjtRucEKjaxmwWsod0OyEhzQBkPMN7RvYxgDNvb5PUOx/Q/1R469F7/0hkiv91rHNnHmQiF1i4lR8lFch90EOwMewUk+hQsWgjJdbnxE/4hkAL6sE3sADvLfHjk2nBHomCfloH2KHsustxNpOU+qMyJSGznkINKYgzb4HrmunW8hl40MF5TzPNPtU4f1f/qLzqxnwe8H7B+6vAZwXKyltwmMWhcmgtUvJ3uoflBJCswOoPRNevZDjYZOf0O/8ATmxmtV3K2s8e5AK9J6xZArqntNkLXBifIBCfQRfWy4c7Le9W8ul5j1Nr0kK3+9LYGH5sOiqz5whj1nUh9n1hsnpObvATvgER+kT/jjVA1l0xm1bUWQztvW/Hh6OXDeu+MpDDG3m8fsU9hNoL0mhssZIjComPI1JORFs6KW+DFNOjKmtC5OzKj0xU89MURbmekwr+QC7+4XUG9I71Z3nzvlpcX/NMd5HNaZdNc99A79Xft+QOQXYPnh6nDNRdRSXE4wzTymnh0Jd0JNXlDSxmXjOpsJkZmP7sdvkWpAHrZwx8gt5Y0e5mrzYPmN1NZR6y8oLZvINsswgexfRed5Hn0aGKnvlPYPeYmCqukhjcO/TgCbPlN5dRddLXINcqLUofPL7MSEe7HuZBko7PpZ2RRyxhiUFaMfWOxeAMkrYO8NDT/DmamAZJHfmj90XDVeU9xBgmDItlPl0vlNxkLPtPWOYgKyeEydzSy4is3v9cWLvPJK6kWQmFPwTur6OM6ri/8pcFucRtTh2vjJZkOfs1AG9KZqM8URjajtzESjvjCKAKSW450+oHl5914ZjM/9GqD+dWU1hxkoPh2ObuOvRNz9tyOgNZPhdL/htM3Q5b7W16W5Z0uzijnX+elU9St7K5AvsnutUDHv/KSQ/HnqFyYlQq6EdLqMTi39kf4k0GfL8CfqcPnKybocwm5h3zalq6h++lzSpF+Nhh7jYLgy3XsEcsOrlzCb/L04brdbdZrK5pdEFfVBHw41F6EzD5WnIR61pbEqYlqyRQ+zbzl5oPrdUdi/gxeyqJb6x36J7JyxPnIvq2DethMztGERgVjk5GODWe5eGW43h2exWxmLjefmHmstuEzi2zIXL3s1ajb3Mi07cVhERWMMxoq8lb+krWcFs5157mTwS2N390KatNgtoHeZaR2R/VG6niDrq2mm2BOPoDZGvntkWv/AaulDp8r5yImHHg2vO4nqYZMsYMeRaLIYww0xhsPjHdGWVaPHWSpeA7el4/jj9C/Vc3GyOBHzLRWbmuANc66b321StrV7bX2QVBJsNPmaDFTvBapZUk5SV6QyTEqs5C00+P6Nrl33JyYn2XwtZRwtWnqokqqq8CPz+mU4IKhkXtrvo2smSSkGjlBstIKdDq9QPMY1UFRGRlhZVlzNoDNghO/wqg158t4Q3D9S9NA9Xa1TsBzS9pd7L/sKOjseWKNyCVNZJxg9813spRTw1nr/OVkdku69d3N8LccXkWvuXcGmS0JvKyHOqNuKkOX1qP0An1GP9DSL+XPj9S6iDThGogoJBGqeTdoPRc16Vz081VawJiOq3tgvDJSMY3ZPMKigWMvI4U1NAebM81XZn7M5x442Ddrlr3Pjip+CiW7ycXyAGq4umOAmKbpFaiSi7qgXw0ePypISeCkNOF38s3JNNrR4GxbuA9Fbrj7Er4R85E3PPvsrjnWWmZttgrYuUHz+52q8L/R6M3PXjlQ11Tkz93qIeowq/Z0Y6TNmn4LJM1wXVbmNOH6wggSLzjpEsQ+ka6ih+hXGhezPxYdsI9F5YX5FF4Lv9TNPGBeMNNYlax+1m6k8Ch2KyjTZChEO/kfHK2ic9EZ4NZCZnBUbbVRxdGuP9aPIJH3EI9kIi3IYDjVfyQ+zW04Rl8jLcvOeJjnauJ37vL3fJS1xnph/7Qri1HIXfeR34vLPzBS0ZwOXmcVXafT2cK3NX/qKH4zf3HwhLBw5D0cgsIUpRWRjUfQFfQh/Qf1UZs35PP4W14I+jbdXGjeAP18A0UktFPblcJ3YL+DlZphCp4v1zsHwrPb26ODKqmT4XO+f3SzkAvShN/KzyG7CKcX2EPWm4+AlwWnmfY155pVrSbWbGhDXfuB/R5KVUd8lXGdYM1lbC+x10ENUvH0V93P3/F/55g0ThPuKVebHKfxkdmzoWbmsXz8DC9r/WmbQstT8iBGc5RbTf0b+myaiNzhO8sNxksjOyuNHLGXnWKXODU3mU/coro0CH+MHzEoTbgnQBzw/T0Sy2hpPDT+YP3YW5aVpzP7m5XtVuKlEEh4NaCUeb2a6MYcaqs6pihG1PIjJqUJ3y3UIU1IPyhCNCMzvOKJ8c0w2Xt4eLDzYC2zhZnd+s/KjkRSBelrtx0L6fi5WCqvyodIBTGdoc5Rp5rbyu2JKtzo3vEeIYMcUQ/UQW2DBlcFT0kXpQmf6dYjXUh/MoqsIxfAD8+QnX6QWDQpTUOzhyuQS9BytCZtQtvRnuFOlXPpeuoYS41txjHDQs2cYjdZSl6et8BsrOeZzERWHWuT9dNqa2+zD4RfK1QVtiwMRlwNyn4Eja7jLHO2OvHcVO5asFYlr4M3FXT4AJRdF4QzT/0N3oqnK+kGepg+rF8iI0wKn8WkCf0iE5JeM1ztCVztaxLsnrmb3qPFoZbTjfnhiv096P3L7CtbieroCvI2kcibWnllBVkdVVYO+rPUSeVyzEAtdOkwpKXVUO0b7kP3vZvSq66y6Es6lh/fp36xcF1SmpB38pPaZChILwbNRw3akQ6ji+k/9Ae6dLixyriCNJ2JGeiiXmwD0skzlig8MakvzxquaR5txrMm20vtf2xblBGtwx1AJou5Yr04JRKCdmI6r51YuKZK7jhk42C3n7ge9bRXDNpYAxXyByjsmMdUEVVS5dOzoFNrdQl4SRck/9n+an+jfyzw1POR11qcbAGPviPNjdEgwDSsaXi6zGWm+GJo1i5Q2lMezUyMbJffDHb4qWedhpY8s97aX+z4IqUgwgHr7BPXRVXZBHw/BOyxFrqW2ykFwj/qpHMrgO77uyvdK+4n97ubzuvk9UfSXOZd977A9zOpWyo9PNfWvfRsKOpbMFnwXmUJrvSsf9l/FZypdDdNmD/jgp13kBvkKYlNE2NsJS1CK9Fa9CNNhOz+wtjKWoLn7/BXPIf5l0kt2xoCrtwMXk4Cbzkjrog7IpmsJ0/KW/IVNDCvYyENj3bmgqMvOcH56MGpmy/cZF4mL5P6F26XTmfXReAtsUGJW8GJR5E83vgRb9OEnhewWlFSg8whK8lxcgvJ4xfYpA7tRc8i392lH2hU4164x3QS3pVP47P5ctT9Cf6DJzSzIO31NgfAbe6Zr80P5n9mQsuyxoSe0yH8Wv8n5r+YqCuaiw7iH9FLDpUNnI6g/fTuaD1Xb9YP9Sed3E8PJ/7LPxWpUxFpw+cc8UhWMozMJCvpX7SC0YYNYXdYfJ6L+7wk78xX8M2g+zM8VagOXcEvO8yTSG7vw12cCllFrBpghbVIn++slHYL8Pcd20EWHibmg2aSy3yyImY4jZPP0U4T56MTgVwgkD6fuxFeOaSA1iDu6d5xEFVilVZlVkrtBXHfUK9UXN1Qt9Nj9D59Qd/S9/VvXc7fh2qMSJz2f3u+pSY14TpdyTbUpGN0NQYY8aC3HdlJdp09Yd+R28ryhzwWEqcOT3GQ1ghrmrUQfnrEOms9tWLYSZEgXtrxRAZk956gmzliozgq6sk3sraz0tnlfHDaIB0EfbwTRH7b/enm9YRX25uA3Bl8lXvOS6faqW5gwbMqs66pB0BZYvjBirQyfsXwa797kWvBMqcN80IMkorkQRVUJc1JD2jjHLIfrHGf5KblUQmjQdBb4dDxkaCrQwVPs/ugoBa8Nw92M73Kc5qfzaQWAznnFlI0Fs1lfzkV3lzDGeucRa5L7z33UqFHgideZ/R1/Vh/1DH9BOHzhLThe6t4NCfNZxCjstHO2G0cNz4bJVhPJAWCX/jCI8yUZnozhznNnG9uQU8cwjyXsIra0+zzUFtbrENdjZFr5EF5123j9fJGeC3VcXTkA2TYuDqlLqA1iC+icOS9BieH9yN/0gP0Ed1o3DUiv8koBg5YaMa1TKsmmPuX1cd+an+38wtLFBeVRHXRSwwV48VVUOZgkPA+cF1wPkR2hzvSaeWsctY7neA8S9zd7iVQ0DywXRRVR61TB9R5XMdXNUNHVE4b8u8hcgUdlgh3XIY2ovPpXnok/FrsN5Q1r1EYWSBY2TvGmGScMZqwzhiBWTypyC5MUQ5pZCAUNAKcW1/ukvfgLcORFd86ydzqbtOwFtLDYQehDh56771mqIBBYLEFajXc9h+MyFeVTgvdTK/Rj8KnOuOgT5eC1W2NI6+tMulFJpBXoKU/6HJ6hj6g9ZCZ5hsfjCisFpvBvrBsXPKJSA0feBT0XWtQ+WVolG/NggdGtZPZwcmLt+xXdhkkh/VQ1LTotJHIci+Q5Sohy21Blgt2xOmL0boDLS3mVUHS3ubFU2nUZPRYdF1MD9EHdYTvQ632hhwSOW8JCEemDJ5Xu8h03ehJeo0qo7HRw7hp/DKSsz7I53vQW5n5DL6dn+bV4ULDzB9mK6s9dCAHZrOaaCo6idNikJwgF0DhbecUclzBcNfKgbgGV9VXa9Q5dV9l0rV0X30P+aUD+CZt+C3bblraaGC0AHOvMU4Y143BbBmY7DMLzlpvxaNaM6xeuPcd4oRw5US5XP5EYq7htUIyzAAXWxCuVT+uc0SeNTApbUTx4Hxw3p7nshZYjez+oqvTD7PZzz0BgjuF8SiqOqrIXVePoIpb6z7IB/v0UzBobr9cmLXThmsX1pA8cJDedB2S1C2odQwjtZHL+M+Iy4JTsq6DSH+yAZizVfwsxqSFOcbMYhNb24PtY3ZJ1HZ3MU18FbPkJnlIHpf/wFNiOPHhKY2hieWRK9e4E72dXle48CldzK8ErQvYJPK3ExGPVCEdyXgyIzyRZ6Xx1UjM8rAOSEvLQCX/sAS8INSuMu/J/+FVzElmeuuklQbp+rjIiiqeKmNDf0shUb9wsrsd0DvxvAJQ32bh2++4qopqqw4rV2/Q2fwz/pNIfziQNnw3Gg86K4iGWsWhuaiNzNYAibov1Go2XRmmyss0eCoenGJe0mhtdDcWhdryCVeYgZUCIwRrSrcia75gMXkyXol34kvhKUfgvrf5M/6ZRzUTmenM3CYzC8PlxpubUe2vkJI7WcOsucg+l6wb1kNrhr3MZnCWOmIQ+Ga3sGQj1Fcpp7Xzj/MA5FDTneWuCPe75N5N76X320uqbLUpPG85Ibw5WAuW1icY2ZH+wuCJ4Pm04fOt+ODh7mQ0OUgeEAEdbgz+OkJf0DiY3RKg7GHGbMOBmxzlg00J/jxix5K5gzU/ziBnivMUDpvHLeZ2AnMedh+779xvbhSvO7RxPcgzFtzhhCqm/9IJwSVpw7WVecgxOtCYbCwxdhouun08ywD9rci78Tn8T1BdbbMJ+r2jOchchUyWwSpttQGZrLG2WGesK9Zj64eVMXxjUM7uCT6/h35LIdKLSWKh2CKOiJMimnTkHKj0GbjYF5nZcZzSTlOnD8jddvu5Q1Bpe3GF5TH3vcDHp7x/oGGplaWqqz+gY2vVc/UGLJNKK10VnfAvOqGIPzDM7mlDro9JUpJ0hJFypDHGbQxZSLaCmf8ln8D39Wg/OgepOSYL2LAr683GsB3w4+8sM28MJ+vEh/MxfDo/BoJOgcz5xExrNbPWYVTj26XtOnZDeyVI9l+wYkcQxHJxW6SSGWRByaQL5wlWda1G/0QFL06Eonx1DrkX3Ufh7tnpQbTVQLPXvdKqoA7PaohIF2ptVczvQ1IMdZsAav+WRcdIr+b7kBx7mn+a2+Byn8xo4VnnY61FyPGPoWH57Ln2mTBBUpBBTVD1UNDBefkRXjTPuQMuCJ7nT3avuabne4u8M6i2ZCqnaqoGq8XqDGjwmUqlj+j/+x66EfJsK7+t3xFaGz6LTpwuZMKEpAMZi8zxN4mH66tH9yFxNIEPrDXOGV+MjKwMq8+asZq8JZ+JBP2Uv+NfeUH4wQRc9XHTspQ1EY6wFb1+1ypmd7Cv2tlEYXjoEZFSXsS1JnVyOoWcItC7ZXCE4+iUl47huuCvT24ScGtLb6y3GQ5aSa3XK4Iry5wu/O50CNh5N64qAc1Ac9OR6OVYLFijlZ0JVok1AvXvYy7ocCgfBiKt7HSAhsV0C0DHssFdzqvpwXpQki58pjKXUKjvAp7RzGXOw3xntkpaHTHjyTHj9e0u9hh7Mjr7Nqq4EPLLEHFZ/CeyS1+WkH2h7qdkcaeCk9k97dZT3dUotQo6dULF8bP5Vrg2pac/1J/q/wneDteOF04Xck4K4uPqz5Nc9CUdCPVZhip8xNrz0XwR38B3YxR/hqcZZzLzmvWQ8QdbLUUfZxqY72/nPnr6oxPdzQT3rIcUt96lnuOlVFfVOH8F6Pl65MnxMPF04X4rnEhSHCRaj7QERa8gm8gucpicDt/pPyQv4PGxkD/SIvXmpYT6oJFKtD5NwwqwymwRkncabvOGvC0/HJ72k8YsaL41Y4GP2iGHx4V/tLf3ow5ziP4iDTphHfr6kyzkKIxKfael0wNXPdfZDre/6eR0q7nNkZ4WIZn/Ax2M7h0ED+ZUXHVWE8Em8XRwWvsyfUdHNI4cp6FkLflCBiDdPjWysopgwQS4Dm2Wx6i0MTea280UuI7h1grrkngoPolYcp48Ii/JaE4xp7bz3tmMKirsVfDae12RtL968VV6NUSdUnfVSH1ev9Oz/It+RKd0oc72B/EsIaXpZOT88siPhVgRVoP9zQbyY+i/5tZsa6m12toE0owjCgiFrmspdiGDtQTXLJVb5Ql5WWZw2jsHMEMvnbhuVXeAK7yO0LAn0K8xarsuGrmP8aDI39sBVfpG0lIn
*/