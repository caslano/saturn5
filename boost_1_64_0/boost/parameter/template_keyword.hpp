// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_HPP

#include <boost/parameter/aux_/template_keyword.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_array.hpp>
#endif

namespace boost { namespace parameter { 

    template <typename Tag, typename T>
    struct template_keyword : ::boost::parameter::aux::template_keyword_base
    {
        typedef Tag key_type;
        typedef T value_type;

        // reference is needed for two reasons:
        //
        // 1. It is used in the body of arg_list<...>
        //
        // 2. It is the result of binding<...>, which we mistakenly told
        //    people to use instead of value_type<...> to access named
        //    template parameters
        //
        // It used to be that reference == value_type, but that broke when
        // the argument was a function or array type, because various
        // arg_list functions return reference.
        //
        // Simply making reference == value_type& would break all the
        // legacy code that uses binding<...> to access named template
        // parameters. -- David Abrahams
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using reference = typename ::boost::mp11::mp_eval_if<
            ::boost::mp11::mp_if<
                ::std::is_function<value_type>
              , ::boost::mp11::mp_true
              , ::std::is_array<value_type>
            >
          , ::std::add_lvalue_reference<value_type>
          , ::boost::mp11::mp_identity
          , value_type
        >::type;
#else
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::is_function<value_type>
              , ::boost::mpl::true_
              , ::boost::is_array<value_type>
            >::type
          , ::boost::add_lvalue_reference<value_type>
          , ::boost::mpl::identity<value_type>
        >::type reference;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#define BOOST_PARAMETER_TEMPLATE_KEYWORD(name)                               \
    namespace tag                                                            \
    {                                                                        \
        struct name;                                                         \
    }                                                                        \
    template <typename T>                                                    \
    struct name : ::boost::parameter::template_keyword<tag::name,T>          \
    {                                                                        \
    };
/**/

#endif  // include guard


/* template_keyword.hpp
EriT+y172a6/yeOYPcAmwLeB7YHvAFOY7iTvvapY7N1fDYXrxPGsCDXSvRIYCfwXMA74MrAZ8BWgKD/P+C53Dbn8xAMbAhsBxfcB5munyMePwrjdAYYAv+R57iNAPewKYFvg10Bh557xPf7dynJsA7qB21kO/WUZ881kvnpwxcx3O39XuAMYDrwTeD6wFNgKOBt4AfAuYCfg3cBh/H448F7gSOB9wGn8/nbgLOB9/HwSeAwu9VlDjjye10uEO8JyYO6V8mMLMBK4FdgWuA14EfA0sD3wdeDlwDeAfYE7gUOA7wCLgHuBDzH9w8By4ALgfuATwEPANcDDwB3AT4HHgV8CwyHAcWA74HfAFOAJYBfg98B+QD3c/sBK4D+BJ4E5wFPA8ewvys1S3/W/K9v7bsB44OVA0X4u9T0PkML1owPPq3QU5R1uqe/yvpbL+zou7+u5vG/i8r4ZaJYXD4ezVFFe/gG6KOAwYFvgcOBFwHHAi4E3AbsARwK7A28G9gDeAhwMHAXMB2YBJwOzgTOAOcBnORzR31vmu7/XhvvVbfk7UzvgSV7cmcF8aLOID+0K8of3H3K9mwVsBpwNbAM8xPVtDrA9cC7wSn5/FfARYD/gPOAgfj8YOB+Yxc/ZwIXA2/h5KvAJ4D38fC9wEXAW8Cng4/z+CeAzwJXAJcB1wKXArcBlwJ3A54BvMf3bwGeBe/n5XeBy4OfAF4HfAFcAT7D/98BVwF+BLwGD9bkfYDjwZWAs8BVgI6BOnwBcAzwfuBbYlt+3A24AXsXPVwM3AYfz8z+BW4G3ALcBi4A7gCXA14F3MN2dwJ3AGS7WC3A3cBXwLeBWfr8NuAf4Bj/vBL4H/JqfjwLfB54EHgCGB+G9PF+x3Hf7ncf2Mh+ovy/g7zMTgaa9qmT+Jgp71Q10LuDlwFBgd2Ac8EpgR+BVwM7ATGAXYCrwauA1wAx+nwnsDxwHvA54F3AAcDFwIHAp0y0DDgFuBA4FbgMOA+4AXg98BzgCeBB4A/Ao8EbgT8CRwNPAm4FxLiO8hsAMYBI/m/rKeNH396Js1lcOz/eP4f7SWOn7VOmLvsdZT/+HvXOBq6LK4/hFEFFQARERSPH9Nnw/chPfqKikmPgE5CEowg2uis8wLa2oqNS0tCjJpbSipLTUojJTsxXNijbbKK2srFxDs7La75z7v+OIc+m6W/vZz364fH5875w5rznnzJwzZ/5nroQvgI5xSb7432YyLnnT236dOghD4FuwHzwEr4cfwcHwMBwNj8BkeBQugu/De+EHcK343yDbhfA4LFLukn8ya90qxy/zoYO1/Mvz6VY+9vx0hN1gdxgJH4ajYC8YA/vDGXAAjIdDoA0Oh0vhCLgaRsKNcCTU8jMGvgZvgMfgBFgOY+BJOBGqZ+bwIpwEtfM3FjaAk2EAnALbwqmwF5wGB8EZcAxMgGkwGVphCrwVpsE8OBveC+fALXAjfAZugiVu9uN9AWbAl2EmfBNmw7ehDb4D58H34Xz4CcyBX8JF8Du4GJ6DS6EbZbwM1oe5MAiugG3gSjgAroLD4e1wOrwLzoJ3w0UwH+bCe2EBvA8+Ae+Hr4r7+3AD/BBqx/ERXAM/hxu1fMFNsFL2n4edoL875wFsDHHXx7HRFIwbnGQyji2Q/ulReT66WZ6PFsrz0Sfl+WgRHCzbQ+AWeKNsO/r1UkmnnUm//qPcx/8EA+DPsIlFZUZdz36R+/lUN8JKPO2lX+yo1l/Jc0W5nu2D9eEB2AG+BbW0DsMBsAxGwiNwCnwHLoXvQtXPwbtgOVwLP5Tr2XH4NPwY7oAVcA/8RK5fJ+ER+Dk8Dr+U69dX8CI8Df20cRhsC7+DveE/4Ug=
*/