//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_GENERATOR_JANUARY_13_2009_1002AM)
#define BOOST_SPIRIT_GENERATOR_JANUARY_13_2009_1002AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/int.hpp>
#include <boost/spirit/home/karma/domain.hpp>

namespace boost { namespace spirit { namespace karma
{
    struct generator_properties
    {
        enum enum_type {
            no_properties = 0,
            buffering = 0x01,        // generator requires buffering
            counting = 0x02,         // generator requires counting
            tracking = 0x04,         // generator requires position tracking
            disabling = 0x08,        // generator requires disabling of output

            countingbuffer = 0x03,   // buffering | counting
            all_properties = 0x0f    // buffering | counting | tracking | disabling
        };
    };

    template <typename Derived>
    struct generator
    {
        struct generator_id;
        typedef mpl::int_<generator_properties::no_properties> properties;
        typedef Derived derived_type;
        typedef karma::domain domain;

        // Requirement: g.generate(o, context, delimiter, attr) -> bool
        //
        //  g:          a generator
        //  o:          output iterator
        //  context:    enclosing rule context (can be unused_type)
        //  delimit:    delimiter (can be unused_type)
        //  attr:       attribute (can be unused_type)

        // Requirement: g.what(context) -> info
        //
        //  g:          a generator
        //  context:    enclosing rule context (can be unused_type)

        // Requirement: G::template attribute<Ctx, Iter>::type
        //
        //  G:          a generator type
        //  Ctx:        A context type (can be unused_type)
        //  Iter:       An iterator type (always unused_type)

        Derived const& derived() const
        {
            return *static_cast<Derived const*>(this);
        }
    };

    template <typename Derived>
    struct primitive_generator : generator<Derived>
    {
        struct primitive_generator_id;
    };

    template <typename Derived>
    struct nary_generator : generator<Derived>
    {
        struct nary_generator_id;

        // Requirement: g.elements -> fusion sequence
        //
        // g:   a composite generator

        // Requirement: G::elements_type -> fusion sequence
        //
        // G:   a composite generator type
    };

    template <typename Derived>
    struct unary_generator : generator<Derived>
    {
        struct unary_generator_id;

        // Requirement: g.subject -> subject generator
        //
        // g:   a unary generator

        // Requirement: G::subject_type -> subject generator type
        //
        // G:   a unary generator type
    };

    template <typename Derived>
    struct binary_generator : generator<Derived>
    {
        struct binary_generator_id;

        // Requirement: g.left -> left generator
        //
        // g:   a binary generator

        // Requirement: G::left_type -> left generator type
        //
        // G:   a binary generator type

        // Requirement: g.right -> right generator
        //
        // g:   a binary generator

        // Requirement: G::right_type -> right generator type
        //
        // G:   a binary generator type
    };

}}}

namespace boost { namespace spirit { namespace traits // classification
{
    namespace detail
    {
        // generator tags
        BOOST_MPL_HAS_XXX_TRAIT_DEF(generator_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(primitive_generator_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(nary_generator_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(unary_generator_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(binary_generator_id)
    }

    // check for generator tags
    template <typename T>
    struct is_generator : detail::has_generator_id<T> {};

    template <typename T>
    struct is_primitive_generator : detail::has_primitive_generator_id<T> {};

    template <typename T>
    struct is_nary_generator : detail::has_nary_generator_id<T> {};

    template <typename T>
    struct is_unary_generator : detail::has_unary_generator_id<T> {};

    template <typename T>
    struct is_binary_generator : detail::has_binary_generator_id<T> {};

    // check for generator properties
    template <typename T>
    struct properties_of : T::properties {};

}}}

#endif

/* generator.hpp
QoR2jubL0ZahR2rxyIIG7x7X0w0s776lgJBscSE9gxbEFR2dfE2u5du9X4S/irG3njN+21HQ4Nmyir66llNF4U0YjAPd1rbNz9C2aucCKZsX9p/A+HenWuLwblWGe/pjJlw1f4VkJSUp7/iE3j2Trw/fqBVPK62yRhsyqqymfoA+ZOnLXB2uANRs/ZPojRa1xB62EzHiCom8PbSleIIt8VfZB3f1AM1HgFSdHau+U3XF+1E9eMqmutFJKqtkRnfhMuBFIFsiV7Q9RFuLsxez44g+0ROEOjFddDDF/O1iUyN81shMiP93uPa4HlSLh5uHweRCcR+dElS9Npl7HN2awc6O+XiJbWHPPtoecc6Obt17guZTp/lcYA/pcyeIZymtYCeRG09vVRdjShFp7yeQ1rEAr10sa5Ti1nOjbFBe5ayvAqRd8yjr8PkcTKsshfdl3PvE2KNRMU14NJFHdWrd0YQjfFE04Q6fHU3khl2UHM6M7rHHB0X35MX7R/fkxh3RPe64LbrHAb8CBe9n0vkUAtlHW0WO19qYaeGr1yCdVQbumw91+o1SiNgF5cUsbSyraYi8P3XjDDShpjyASDsPnoDJWFdAPPghuxJBU0XlJ41RCq1LPEuNaDtwVSp+8KgUe5lxWatHSKXSYIyFw0FxBVWiemPsDCcozjfe6vhtIL3FmG1UveKH75ygFzjrEPcNwSPM2UUBp0KJW3zy+4R+kJ2Z7Bdqdc7+BrXafvAfanWuWj1KrXaq1Y7bjXvBR4ZrxdMPvoisQMDFdxDyLWhQi6er1XfgaDJ91hiRwWhr4myjlVOLR2hTAurkgDZlmjp5mjblTnXyndqUu9TJd2lP8KbkralNyVEn52hT7OpkO67RShx8OQb0WwkUX/8mlv3GhbTs3cQWbGIEg0keFV3gyJ1/FOpaDUkVOjowW+NfUYIwE/ofbAUYfbpQHjYl01Rf+wFfu6k11kbnubj4Yfoyi9a87QDcJHVCiUq4kUhd9y2nVc30+DvDm7yfV7/lUdqr/+BRllf/1qN0Vq/WZtnVii7v5+HnDetpoto2SVAx0TqOYZ2FgeK9VxyWg+yass3vmEGYlpMPvsSzq9QR1lWV1aqyFibhNHf+pYixOoR64d1aPeC5Y92qslT118EVSqu+ifcwtyV+vg7S4FXeHa6ar1iGsFzzd0rBpUdZWt3P9UarWtEMv+H9NGJWt6u+FtW/1qO0hW3HKlrKWe/e9xurRV4RibOom8SrUtl2xFJfZRByj50EudRW4WjyOWGFJsmXbHqDKZrKIiTpHkAa+apvM4/9NotymJww7HuZV1PfLuS/oGnYT5SyKhbjKuB8HxJUsTGBDBAbq2/bObOD/zr5r5v/5vBfKQTL4789nB+CYllteyzGVcg6f5yAoO8FCLOaWC4ICkB9ewwXhTAOSqMlAZglLJcCswDbcxR9gQLzkgVY0gLZOeWehtyd0s85ctvEkC9gh1rluE3bnnajv/dCePvbV0VoStueftW/6UJ2Yu7vUn2tsp/e3a5lPwUR/zTLwLdvbbdBdFWLgRJfsdb1RsVqmDqwWFGtWKuWbSCgUZUugkrX4kFspLDB5q9X/Y2av1H1r9P8y6nOxe1QZmCho+rbq/priBDXKvaVB8Xh++CxoksrWxhzbos2OlVlpcpiR8/VrsX/pvWNTdhml5S+qqw3DIUsNt961JB7sNBuqxAHXwCVUO564wUpBmq1vYA1Fk9z3Xu51gbP6Ll3q8pmbaLd5t/s2vg0mx9ZD95kt/lo4E7XG9ts272fzr0S7rL9rTHnR66NbvVp0PWFus95gCn81p1t1oNnuzay6Z7H73zwY93XcLCV2tD8DVHfZqfX8eCLRt1U1zCOA9Ca33zQbm2LoY9tloO50QbHLco/dd9KQ/LvXxn1raeSrkfPw2vFPqP+aLdd8R0sym0bZhLytriN3g8OQ+Lthn5o5sEih0y+3cHp7mS620h30/C8u+feIvXC9n9DNOVB+3ZT/xPsQsMp7ILYGqaZ86/TffR/J9SdWArr8Tkf3HZw/8HWqG+vQ/fXuGrHMqfHd04Va7UYoET3dVmx+F1ef6fr0WMIaeZfavUf0vx1Vr+wVtRbfRt0f5urtgmRU5R94v48HFGt4q48AGNy2xc0lAdiU6aLJ6exYQA2h1oyHYi05A5CNGpJALR5yTTtMebgnmC0pLKPXs3XjuBkjwFHNZU48oCqGr9ign2PePcrDlbFCGwL9hRRZ3ILYb9JcZ6WEPV/hqzKFFyrb7Og/JU/Q0Oo4xI4G8Xhs6jzVrvFku4PsQIKSiFtl/rCoRO44PmI1nHNkRNwHpGoypuhvtdGz2pMnMCu7qK/ffIyLMeaYKgSztmacFwMSb5ai+/qe/iOb3ZL+ByzDOoCByJL9827xKLtEkOpGWqzthNtHtpLXX0b+bTdsNDW30ZJ/W18DAjLC0x09a3PLLQs7HgT5q5rEugfGrJajLjNu4QTVSbU91DPIh3+Ix86KyQ+3q/rM2oawv20JnHpWwQjPfEBIcJzaHfwSmlfquR73kNC+GytFv9qowOETJFjzc8Jv9ceVb6uH2DJXtiBEAFGR3eFxFbqtlZCRGY4ezw8zs3Nj3I1FnmSnVrXDLOuDniojK7B6MDClcdKHCrPkib/OjSelii/2bWPtv7DvWR57Ul8omeHzl8p5Tv8s7S2h/7ZUVOr85LxN2+J/cG3YvwhoD9kx6QKBZ3ltfTwKrlqvwHcFTuja1pQMrpmL/5Ra/ehnWK3WttKD7HaDagE5ti1LVzdHLtwnmcorhWxgQA9pga+7+TpA7/zZ+bAN+JrNWGu97DAWm0jhrkG3bFoMx3Rpuyt/7JFq90WOR3VV4fkZIeC4tbnE5R/M71Y+ZttZk600a0zSGn811vsnr9HextAbPQaxgz3nMt9vQ3GDGX6XEcshmHob6OEPjdHn+vW5zrFuXtQiAcYi7Wjz+5WeJmpIopSvl/VilL8+PrwvgQEmC2xlh6NoZ8OO/febwy7oCG2Zu0J1raSipbrS3vF/c2hDfjOkk+HusW/Hj6u1zQo2Qzq8QlSMwfmFkRIdMLUQtRQi1QJ89P+LvjpKBUXUlq8hV0a7hZn9QBHdRG93A9Z01QRS0th5qH6E1UZ+pDriadiX27gQH8HdASdRn3IuFdgzwFhQEAkZjosdBKhB/AhOyTnt3wNvTv4LvgyTyazrNlBya6+zKYbDcrFVWPEoGHd8E8Y7gNf67+UvtdfMb5niqMjgD176Bsf2MTwOwJ6qUMaf4gA5df8iYAY8E6Sa9O6uBnwgdqONFOpUvabpfp7aBwO8fUE4rBmO/WxE8A1Kg7qsYNVkGD+BLfrKBeiVDsUp3xO6FoHiXe0IFNr7QHFXXAUQx9SJ9uJf4jMPRDh+HsCQbEJve2Kt1XZ6/OyaCn+jBNHesefVj3YHZtZ2OTrAbVHVUnepsjORr7QLeWR91xEnAcze4bWr43QR1qW8EHEJFxlYbaZXndHq0dYlBGmeH16AzwpLuXnW/m5jp8L8cw8DAzdm6yOE9S7FxwmNwMyS2rmitvXnTBYH5wcTdbEccpZTIkyHktTNkenqXiWJpK5n2iHW9z8kjSaJQw78u1uXWwMy+h3t2MOPprjMFwxjmC/sRB6e2bmhI8QW7xBrKL8rJfb2eQTqDrmb+ZL1cv+gJA4rUwunvsHgEO91OxCXw3Nrus2cDq/tYpR9HaKQBf6OG2Q5nZBmtsFPf7+DLotSHQi0UnstlY+LanC0gKa3ueYWhrksoYSS1dYhnttk8YADrMSQ2zXVCwdOu3fki6327WFh6Cex4MYsAFvcnAZ/CyWVPQYoxbOZ0x1mw2ifYPk1n8xh9msShgN1y/FXH7zIF8MF+jafmJoeTrrbPAVyPoj2bS3nYcJe49vnAv5yNkQQLN09hRFEWLiXbVBPqjAZok5zzgshpsZVhWYIWWNKt+UiJfWdfe+lmWx9RZ41pNaI03hIQFTIirVS0DPxrOkoywP/3XV/JJmqCoQY7oqFJBOpETznYw/7om+dyW95j74SEpzopdiS/jHVX1nEJKMNH/7e9lHGDIzk0is1T0aS2/vISqcHq+Ujx8XNASoszhmSwPEKEihttQ3QV8NfROpU1Kgx3PN6/oJ/FcOh0X7TNF6m1w1ayyQhIO7EY//vtvI1Euiz99eeRPf+C5MMkHGrNzK1YRLTHU+2UZaq0iTBQB1phZKqgpJW0sZcdxpXrexyiC3zBokr3LraVJnLirlxbxytZQhPp1lMSFq0ZhnyGJkzdILNVbVzBMwP7Mz32jd931mB3FFAYg2iqapxdO0ojvV4ju1orvU4ru0ohy1OCcWBc4IGIKTW56hE7soVy3OJTwI1XhW15BhSuBorDhPi67jFPYkUzQSGsFFDjqoD0bB5UtJihbl8CFN4XvjWQb34dAKHZLhChhiHIZu8f7VVkuUr1h1GZYtIKc/prF4Z+lghHIOn20kSpnPfx43XQWoDg/7j1Ce036NPRl363Mc2jBDIPQTqtv7hdKJnbvzFyx8qppY34Ztu/vnYNngLk2xcQjQTs032njLLTgAV6DnwpBC8Wq+4WliLzZ0kOGfYO6Q1Mo0jl99yK2rWSpSC6Iz5t8sjqwFXmmBvK2DH9cxujm41pCXbWZMZHsDrw3aWACt/ikhz3XiX4Ri3wcmglZhpI0+M57Fxxbx8R+ApIUaOUQ9wAHCvWhIBsE7JGoAdFAC3Sv6AjGMZd1UOFxnJ3E3eX05bG7g8Y0Oj+k9yPd5N5wyztG6MgrYeK8+pAtafSPPXMbIjaIy96cIdm015kmKfOFg9m/r0b12XVkv7uOejsQs+XLFitWE22RRLoPH9VQLRj2fvmHZLXgZt4bmB+ZbIZklmZvaNDJtFrdQiSAe+q4xqjUymkvWQJnZVizVYtonmh+cWVDupo5uW88a6smUvWL9eizpZvHI6936FnlWHsIqqcoh0fIEvrUxt6e0ifeeSK3+068zUODm6PHXzVNms6imZ+EkunvbKACqK5sA9eL7HTJeCtN8F/Ft9zocHgA2AxP/PeZvFNqrp+jRNorX1zGQ6Uqzgaz8G+CD2Ld+C/xnwMm2XwC4lDZt/ET6XhoIBhl3fsZLdPMbgDE6okX1Q2qFw1PRWX0Xz5CsUepgOhWfWtGqKvs0X1dsorUURuSl1qmBUoybK9onuglYq+yI+M0a682i6rETiLbNHC9x5r9Z1p0MBdA5f6Wp2izmq56KQ3A7fyg5BPSrlemQNi1B84eZ/ckycwobhZeGTDxj031SHLoV0ZqbLHdVpwe3Ovyf1HVYyJ26Dqtsxqk+CbOeyxIdh1bmNBQzfW7TyWmOtl9lfzOImno8m9Bckd0VO5yNu60RlvBAU5sV2qQdbdlAknfatsmjTirLyWPHVnRX9JHhFvVpFiiylg5sHFi+CJ8cYQdMY6J351kKjhoKn8rIcKZHGR7O98wZGb4Euo2RPOOwMGwgeZW5dxK9FhzVJjm0ouEq38hGu/OUi7w7wucbwRXVOcMpKTzEMzYHqK6/RPZxh6qsjv892qzjtkFnbzdLoElE1bBmCdh6zdB2DNticwpVZSnuVxAlVS1bCd38lTCVdFFCP2PIvlVIXkV0IKJpxubM07JU30KtaH656qvhyAmZdEzFM7ViR34Wpa0z06bRCVLszC+2Qzl/Pcw7nB5WWHPVPCPPNm3SNDXSrvqADFV/p/wanqD5lngzcXUR9gSkz1LxCIhWPtY1ZSn79pprGG3IDE21+LsCxJ9rKZ3IZ+ljD0E98ZTMnsjwcJ5cZrcy1Ih+iY98Ue+rI3yoLFUja5HPTauUO7+vGhne5EPYRYsnMiLcB0uHGzzpWAMhweFJo7aIH0a4am+kB1o4LI7TMx6L46q5gw6Ux32j7lEjy5f4ntnhe9bqiawNO1YtvWiomxI8kZHh/p5HRlJKTKbEiu70RFYrthhNkRu+YljIKCWqVLOrZhskMP51hA9U32bXG1tNreCG20IhlV1yxnyrA6GYb0Mg1OTbANJM9ddThm1qpFGNtKSFJl0taTZQZF/bKRt7oWxiPVVgRVoAFo9HesQ/f4cgmgBysf9lQsm9aDVOPvYaVoklrNIB7yQi7Ex3ZAHiBHJsvoVGGNIa8zYSaH0diDUm0JhYi7JrV105m1UOqys0/+pFfZAS9a22T1S64pNcGzVkcW2Mgoxku1J6ftV8luUu1spWQ00tw7s13AdufnU1I56hXkfJ0W123b9CLVutfMmqa736wD6QpFskyBqVlQwiMIWk2jzvYTh8ePaRmqcyWCmP9/bkFDH1WPmaqVvANHJyUsV9KsHojdSyMS3UAZoZxEVNzot45lXYM0l/TLvTeyOu3YFtuQJBXmtXZfBO+m9zmzYG5r8ia10191KxcumaWDyhWi1apM6Ixh7VcXM4HttPKPcdp/22EpBWtip269UZKlPGmn997NaBGerTkHhqbpUVrrVmQ638KZCIgVCVqe6LRFb3RWNrxH9WWi1yTrjxy9C4srRA7/jUKrfYHUmaeGrSwlwq+NX93wYK7ZK08h0KNzBcGQA3iX2wW2v+RQ2FQOLkIKZ1A5wBjwg7JJ3M4etN79ZZTJbAmdYo4Ia7xG1V0AEIh297eTrNFHXWJbGM7OlaaNOuxS6/jvZo5S3Z9WBR+Lqczex96+Q/qwrpz8pCWVT2eW2ympfv+K81X/Nfaj5tJlK1wpduJs1A+N7KLmDI3SJjLe5+6qilcl0ZXtBAH7VdruXwsZgj9r1PS2tEC0+fhcri7K+SLX/f9FPla2gLEOoP52v+JRK/E3T1Z9VxgxNMEehz7tLn3FkazzPOgYLTclTpVVR+SQiu27lFqf7D/FlAHPgW/DHOzvAggxFMP1v5HFWLhnecl4B4Xzz4EyI0Rn6PPgydY4cIfY4MaPvNKNLh86J3N9Op3mKeXLil2hdTmmORkeyWi3KbeV21T7K75LyY4jS8dkUTNuknEpZQms+Z7xtp842GKew10UQGnba+nHzfaJtvZPyiaMKqVPK7U/OPzt9Kifn+kdJhrc9pa1b9R4gCjCmdxMGjXfg86lwTgE89KNJo/iOIsdNcu7P6Qq1sdH7ZSO8H4dx8X7PVR5T/aGrY2xzJ0FCt6hut+UZw1+qSXRuT7xtlQwyXRPxadI2SRuX7xth8CYh+RqB392j+MUjdmu/ryvdT7oThf7fL5u9S/Yn/0rcEEYhm38bkl42SfWux+kbJls2+jVJ9Y7SxTHJgYj/FpF7PNHSn8XYl1O1Op6EiI+HiD+VbUZIOPGSXREqWHL/qazcrpfQgCBXuS8FRPt79j/vGaZEj+ZHOJb5/SJwz3OZrvEdVhKYk8sG1xQlniKnMBbWaCPtvqxBQ+RD7ugUzIp4ghBL3mYfZDZovQdNFq5Pv72T8NVWDWKzd9UbZcNxIfjZVVkSb+FCpwc/ANBU8m9YFcVnaMGuPyviWV9KM5vu74B6JGOE510d/cr2lylJKs14f0HaBxv73X5juO0udcz0hNNPR1gvXQSQ+hvo1DqKdQCD2yLyYMnINdWj4Gmqcfp1wtnZojXjpCOSwsaJ5BN7wwyerFge2g6ZuU4uu13bEX6uaXq+B/N4zS1ocEue2Dpxz/5dB8Tcy
*/