
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_returns.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/local_function/aux_/preprocessor/traits/param.hpp>
#include <boost/local_function/detail/preprocessor/keyword/return.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/first_n.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT_( \
        params, default_value) \
    /* `DEC` ok because precondition that unbinds are not nil-list */ \
    BOOST_PP_LIST_APPEND( \
        BOOST_PP_LIST_FIRST_N(BOOST_PP_DEC(BOOST_PP_LIST_SIZE(params)), \
                params) \
    , \
        ( /* list 2-tuple */ \
            ( /* (param_decl, default) 2-tuple */ \
                BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL( \
                        BOOST_PP_LIST_AT(params, BOOST_PP_DEC( \
                                BOOST_PP_LIST_SIZE(params)))) \
            , \
                default_value BOOST_PP_EMPTY \
            ) \
        , \
            BOOST_PP_NIL \
        ) \
    )

// PUBLIC //

// return_type: `return result_type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_RETURN( \
        decl_traits, return_type) \
    ( /* returns */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits), \
                ( BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_RETURN_REMOVE_FRONT( \
                  return_type), BOOST_PP_NIL ) ) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )


// param_decl: `[auto | register] type_ name_`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM( \
        decl_traits, param_decl) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits), \
                /* append param (with no default -- EMPTY) */ \
                ( (param_decl, BOOST_PP_EMPTY), BOOST_PP_NIL ) ) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// default_value: a valid parameter default value (`-1`, etc).
// Precondition: already added unbinds are not nil-list.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT( \
        decl_traits, default_value) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* unbind params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT_( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits), \
                default_value) /* append default to last added param */ \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// var_without_type: `[&] var_` (var_ != this).
// var_with_type: `PP_EMPTY | type [&] var_` (var_ != this).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND( \
        decl_traits, var_without_type, var_with_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits), \
                ( (var_without_type, var_with_type), BOOST_PP_NIL ) ) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

// this_type: `PP_EMPTY | type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_BIND_THIS_TYPE( \
        decl_traits, this_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                        decl_traits), \
                ( (this_type), BOOST_PP_NIL ) ) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    ) 

// var_without_type: `[&] var_` (var_ != this).
// var_with_type: `BOOST_PP_EMPTY | type_ [&] name_` (var_ != this).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND( \
        decl_traits, var_without_type, var_with_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS( \
                        decl_traits), \
                ( (var_without_type, var_with_type), BOOST_PP_NIL ) ) \
    , /* const-bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                decl_traits) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    ) 

// this_type: `PP_EMPTY | type`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND_THIS_TYPE( \
        decl_traits, this_type) \
    ( /* returns */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    , /* params and defaults */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_PP_LIST_APPEND( \
                BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                        decl_traits), \
                ( (this_type), BOOST_PP_NIL ) ) \
    , /* bind vars */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    )

#endif // #include guard


/* append.hpp
bPSE933h/DGOt7jf5yH5hwWTdmjJurGPw8HSLDz9dD/+zZQ6OBaLcU3+LWghQeizG6HIejbhGhInyUuMFmy/T8wphr8eYh2EIm832dEC5FHEAw4ueXPZbxrHYkTREyMPa+OxM/OU8ySxbW7HSJeHOX7inKRx+GiX4grv4Q0SGXrI5Xy2IOiFeniaw5vJ4/muKZ/lVa929gP7tfixkdyTe0UWuamzd5uNVM5Sg0JUDr90sDY8dtgh6/TAAlwTku2HNs9ovtf+St+/rHnt+gBWpaKpajq1SV86Lhm782kAkVQUOZjnGtbU+YaMAhd0okDqf63WViUGSU2gYzc3EMfHG43WbymiBHRf4D37h221dVvAQOjHSWxsN7Qa6z/xZ45ZgqytujlRcH/6CoqFuESZZuheXmJZoBZhw3S4dumAgC/89pFc5G++k5t7Ub+yAwcRSnpkIwGnT4FyxbX3uH8Co/bQdg0212Go+uaKZmk6JjE8gW8kvyiVAObb5610x3QqPOnR9Z4zPW7+vNKlrZFPjSqtDdZnJ4AtxxHe1jcBMyRuB13GmqOeu9WkWaZmMXF0ktiibdR2cb9Pvg4+Oq7sVFktacVmb2d2biMjp9THT/otJr0vzhr8HJj5ZnAfDjSjXLyc26hYvpjhsD8VjscUzNjP1+C4v9rDPkj2KNki3+I3SG+3ms1r1WbSQT+TGwIh/ZXXdETv6ENaX+NxZe+aEooh/iL4dPJtpUmp1hr9vgDRyZfHK1VuTzIDADjYigobnXpBOn3sZu2FanT3bh75L5KgmEV3F5bdBZm3JHZDxfEy3sIAmIIKuTkYaUQpYsD2afBmx7F/AdZVoUiXSDTCY0KWhcGYX1fcyT4xrWeTZlfRbp+1LyYzrzQsXqBZ/pzTBjXRg56dqUAS5isrKkNhh+bnloQLEqVq50PlFAOHZF3vA3eyIqWKzuxG9MUMO6YJoR1UAb/g9yEy7+kHk+VGw+wKyKRpVRfZvp2keY+SKKXtdt8fMCRgX/h/fCzIZVjRW4PXDKESr89bCqTDZsJQrdgk3xzjFXhyrAjd3gesdYakaKEBhR2FsPN+iFXCJZrgnEeSjU71Q1dpNNqof9QzyHbNuO2unb8SqT+rDn73hzSgu0V7PgUHj0RPixldZM41+c1/KIa2fNpakrx9hkMb+MNTgNnQ0xTIr5+SOZFMTAu5vg+wyCYBGp5B/h5My9arX+GdYhMu619ax2jPgWxO3Id10GQAp9EyIkJcANpHkuR1DL+sxdgHi33OZ+qRqLNnWGRtNr4lkrlJPf+Q0sHtnBy/A0TNYsIxEwMuvbXt+4AJA3y8RVOjKP6dho5BVzSo6k6qnJkUBuOM/SElOAr/hrycjB8keWjeK1Qok7hWPU0M9UJAAiifBG34O/t8u6uh3nss3ap89LYJQxpWR3I+SP6hDNaMM3qD55btnDQoCiD+5o+/JLILDsgtvpnGGPkZmNqKf909AMna1DCyP+U6tvQCeW4mUEouiTqVRdzPEWUygrNfPFXaiTVweFzoI1Ni/bOGAeI4Anq6Xg43idyuVp5dvJPgWJCiq+M7CIwmipVupdMrsRR8AIEurCPY6THqWVFsQl7rVffximIsHvj88kBEp9cHMY2QZ8/Z96qRONuMqw4EP5YSJuyfHEbFNEFIAKghhL12+ZOrBE4QWbuHvhA4Ya7xr6kdY6UQqRn/zs+b9/ca5J8tJEo4YTW1n09467pLRjmLQ5N8QIepYlg4fk4fzdrvrBaPScPMZPMVx6ooPkXSK3kHt1FgzDUhBuOxp6uBohYGB9jRyfri3/T9km/ilP8lX2NNYRed5G6AMNv91C7cEcxuBdLajvojXB5GhGR/m3tVg2+W3BgUNoaePdMMC15eC2JKS81+aYtTuij43W3DLdORVaYXUDAW/JCFeDdsgFDn0y/6p/edrSS6cbWzIi9/FFcoTZJZRjN1mN1j64lHrv2c1b97kP9LotHIFa8ZrSO7wScb637zBpXLK/feDhjBsfGp156E69wXnIxO3IgEcHRpIk45gRPYuwCwmiCulG0Tlnd5ZcbooPKlpTBP5FUC8Pdf1dhN4zhZu3iOgggMtzCIBFq/W9mnsm4ejlab1Ho6cQeiUVzvYxI5TmG4dsdeNuKJWXl6PmVo6DxywzbjI48ZLl/1AFsea1IdvHYA4YOBLjVUk3/HmxkcwP6q6dWOp94+RE/VR1khyzBRxqPvjhn5Fa65OpJ/Mmsan6TM/xutBDVrDNR/o1UykLbAIkwHF3Jiu4SEtAxrH4oMLMh9kpUT5SZlyCpA39ZaavTvqtdHiBzZWr06dqjYzLvlljcXhR7uefCnN+4g4nJnS1wDIcgr5RrnOh/Jceckuy+rNDqGF0Y/IXAZx9+fFsvvCoa6e451lLDUOVXHK7Tlb+wRsjBQ8LN7/MxuYEXY+o+6kLkA5iMIQoFNDz5xttgAlrhk9QVwXcsQ3EUcZEqkKw9uUocmPCZa3iqAyhNekpOTzGIT0yix1lJ4kabQ5l2ixS0MeAAXKkqkIeAcuoODIH4gYb6TFJm+J74K8rQRO9jeUBDN0RxgyMpSCDq9DN67x+z0ozu5Gkr+KaO9PRsF4yfgU7pkdcEghU3O+Q3ts3wYWXz4m5F1sD3QYyWYtoaWV2D5Gv/7oVwip5FvoduaVVxhijNzFObDrpbZ/eDYZ7bzx7uyImwQFA2dzo+nimm2wefK6r6/B3g2Hg6n0BMui3muvF97Q6ek+/icC3Z9sd4mgQJTrEp8E6iC74+t9i1nGv0fFTki5rgx0jIaVplBJz3/4B9wUNueTTd2LHgrU5/brqyu0vOlYFcITM+PhqK/IOCcdYty993hkNw0BVLdsEkNIH8fttOwNK2U7tUGo0F/m90rvqttF5Kwh4fka5bFytGwIUlfQ1eXGyuINNoDzY6jFPVMYe2qHICy1ny9QI8sdqwUMaHf2BdNQRNKoq8RS3ZnTahNFEDCfEQyzBivp5yZkcH8Uj7p1QoUMxna0NS3pGgRPxQo7ZZRvYM74bNxTJ0Vpvscrjy/ecKCuqfXT9mVNtrZEdwVOG3nDmgv0F8H/vLJIbLIJtdcra5F/Nim2ZRYr5X0UHtlxyXFMiKjSsNCwS88EcthilNuPD22zVXWLdS1S/oNStqu+BsraF9KOXriuUJysd6/qUHAO0IslJJBmAnE/GB/OFrIGJkp8choZg5zjw/kkTxhO7E0gn2C720M3C9NoEaSd368DA3GR9scORWvorHGv+Pyd6pQZVwSevxpeITo1bzomFEif9OLASH13bxpi8Wrz1w2B5OLIT4ykIO01iIE8lyzSm8JyjSFSz1cDCMHcEM1W9fMVVVaZdKoi8xs17ymqVCypo8ZSH8DANlN5nnTxWbRUIJDN38griVEgnRj7SaL2qGypSlLuQNB9asCrzYdV8c6j5tKVSUtax98279TVsRPUE/wK6pvvSSzzFVxt8PGpOCR0h0ty3VtSqL5K2kO5BRA4eVCeXMIB6QY1MKQktSJbhLMGvLVrFGFVBc2N3o7dyyRUDjSZVxy9446XH1fYOWqNHFkZrq4Xv1Ea4duOPbxEloACOASQkzlmcb0caQM67Um1hKHOUjoDCvKethYQkFwqUcXxvgQh17+689rG532K4c/4orpOjHTc2zjq1ZYwYzSru+1Q62TCda02cmmPyWYDIe+yqP4+33UfxeoRYdZ5vxkOs9NuccfXUEm6uNoKjLeEYDH6D0LEigmHkQcFNqYKaRZAhMr/Ap15zzlR6abNpXz1gIQks36gD4762ohndElbKUKgVSKAKQtpvEbFVmd1c0zZH1BRrwModVOciQS2iHMDdCqIKfB/qVllIJBVM7MCqeBHAk1TYraj2IJ0CU0//U/CJOEGChCwNDmLbINmMP189pIY8sPQLN/69mREA9Ax8+zQ4yn9GdU+r4YDUZhjR/0iT07wdP0G48jJIevTXoGTmOvZmNLsP8ci9yOKyvEgJga38z8mRAqy6UDpgAAgFYBc2FES+XsAAB0V/4ZQxte92Fa1OYHW5QGObxD2MvyN29d7vZIpR1vSNgjmTez6MYJGpyVIS69OFFIeilFxTbpkDCIhrek5h7fVLDoKXAxUMaYviNaTCbHdayK7MagTGNEVqX/ESVc5OezwaNy9ZSBHhxmKw7YqYaQ5qUR/Dy8UnfTYNrYlVOKxT+fFcRRjHoYooUCmdKlMFWhxSrfGl+coEUSOvrd24Hkd5ZCZ0BlhPPLDvpsZGJ7Hx8yZj6pWNxWVaz62D1mM4y/4wTW3+7u1dy34HeC9LiicRtg+UvevzjAQK+cFOEwsltgo49tp6pruhKnpUs1bCdACJBn3TVln9VqQ2hZ1nEREd8LIzWgjRSopC5zFRLrGls+wkO9XQW4aS06IqUhTLZ8u03FWw74KrS3v8xt5eXGFVYpHrWUHowq12CLqAEvxJ7KVetbhh31bWz7gcqjro3KFdn2fHB6miRL9eK9q14HVWbmxJZP8fHY/kuWjnaSHSWMg4URELa4sB3RBfSCR3FfwyyTK1wk78Dd59/SMumtwpF+EWbmHflIefwVy0PF65IZu70xlpFR/WD1x+RUBoJY4vaVVmFcOxwufe01JJ8V7x6nnWBErKspGEUaydm8ZXAmoJIZWcySLMxIN1MoonxwG+OB6RRLhi6LvcS5+UXOvT5m815x5n986qcrrqADZ5Wvsh1RomU4+/g35yWvIGPY+ej6roC2uhXpiwZrh7SZ7Djcf5WI0g4l5/9lcplC/WfGd6X67lZhS05GYfRCQs1BX9JXcWGO5TVVcTFSR4aWvsZY5otkJ+LhyF9xqRYnBK83i4DOAAues01vhc0XmUKxQs8pE/VrBfEpvFZ7t29ozPo4HLz8+5fhHXx75KI+smHr9BPK5n1X+KY3VBQWb8wUFAYRmvoqkYRsOhBcmqRy9QrwdYM24LqrjTsR0hadrkHBtzS4OUl10eTwAqhCiLGc0xs7LBQBQNeTvJAfDGhwlmQ8ycc4EW8bPrxCntB4nL2e/G2b35LCH4i3mJJqepldBrfw1kf4GmlJ6iOYxeWbGV3ZPmk+9mhaEDj0g7xCMm2Ng/Y3CXOxK+cx/GLhcoau3DOX0iRZJp8ma3CzhCiCHrbVNnDv/RqI/2YgBm2WUQNl9JZPz/u7WanM2LEJ2VinY/s9+E+JsjY5tIjEmSbGLAud9p+iGuoZy53lb2NccWfK8Q4Mi+bWl+RMcncNpD8K2RCIQYGoAclji5R6qnpINUMH/aBLUVV+QCygNiSZPKbexXgY0yCkpLLTKLXbm7wjaozIPd5dViTGI5Lbw8YNmVV+JUtpfOLbTYqojqEc3oifP5Rquxgq106cnJfcZOZ1veHd6H7wbpdlSXyXye7idvKIzc5/so3URkEYEIqEJskm05rJ1D7SA0B0xqXcEHzoCDSC0TalFh+9m0UgitceflvXqo/Btv74eb/SWf41SHPDlOVGP4JZ7dR9+I5T8ipJltnyP4zz423nW2pGcZdfdUgjT3SkuHz4NfSH+tzYJJOqYUHut8aQPIMHuaCs0xwjKNGdrgDOhIKDO+EDCIqXL9PIutzAxon4YIv7e+Iar88dIsSngpAIAF7eBo1t0i7t5SqMhStW1DUVl/mec11XGVSnMCpaM5hgISiDtldgerMMt8aDBXVXz+gnRXKS9jUKULBAwIvoCSFZpWVLEyLHx6tq5cHRmSu7QuXDgKDsYM7PPOWsnx1AXUwAJkV9QE7THtkkzzGNfcF0XtrfkPJ33egBed7F9PYDcFBDdV3mBCL091SohK9gkFIo8J/pAQAADv+HUon/Q6nel5zHxsqfJwgpTozJdtNigzEYS6TY9xZiBGKVRSaEfuLocCmLNv4UifI7t2cLvPhedEYJhBRsjbM5rg5saKTedd9nQQSis/T5xb5gAAks9tMWXZvQ/FfRHjJkT9QtkXjGHLVQqoeUMEu8P5gaRF+/IlRmv6698srP73JiFu0jrebqqfGMBERbJcmY3LvxeA9aYqYv18/v18wn1U6Nby0HP2JGQM2gxyUvoAuKh0DlZhM4zAm54jENNrz+VjCnY3xHYK2Hvmjp3rMNExyxMv/ztyCbb7BV2JUtaYywarGBgV78G6/mWbBd2bdtb1EcdaoNWNvGPePjSqRfCdrWuKmbTpw1aIN1a9xw1ksUbGf1h0ggrKFjJ/vkRu1jc1xNkN9K9uo9lD6c2Ka651v9ZxaCt4hA/Y27AgorucMenftVcmpDU4JZeu0JW17YNC5i9s6PaTTb0ub8GLqKGhs0F+qIT73pJ4yRRRB4WJ0FSp8p+i3gOzk8+NFJhFkZyiOFPi3bsjjJR0C2nvlYZz9LW7q348Qp4jegfDncjBtf7gwK3gn8ZWg3edhWivLtlbR4HK2XR3W5NVr/Lo17yb8wBCSE/xyQUps6gcSUQesU+kJHR1QVmAyscQFXkDfngqQITm5u+vbkaIf/03aJE6FWQ4DtOPz1J2L+K8Hetyg6qRUHXhImGBhMTG0Vq2g3GxybF8jiARflgztiuRReI8CODZcmGSKACfBxUnk0G87N4ioTF5KNlUO3Cy7FolvlDrqceaAx4d2YD7igpLNodv6E7hCm4thFsAy3zCpCAAcGVrnc3x5QjyMiddymtKZO3VUJsAzj9v7wp6yDJeU91UdWfDNY0aPct6sMaiI4iGLOqDlgFX6OhoYDOL7Xs14IGamlf7yjWbq7G8qNvWc9W2wUPWXuNLJagx3XPBAr3dAR/vAJh7z/PKx3cFFURSjF+84r3Oq8/8wAPGuj5pYZRTHrX7elyDSZu81ghB5cDgBQ64FQtVE3YoRyMxbmrPefcj29cEPCkIh26KcnzUt0KyRU8kBOI9h9t2wWrBGYAA/TTYxeU6DkVI+r6x98yk/N60+xDpm581WWSvmHS+qyKKFSWbTNv0px7Skrt3oZhZsPyk1L30pQ3J8+HW4SgRIuiHgBhKjgiu1uQS250Q2SECV36fo+ix5IxsXKTH6T+CY6bFzhMemedFFfWyUjgAi55k1nnRiQJDSTVfIHcxVkbVxFDEPvo/ai6J4NbIBXBzzt6VpXgQKgskYE44b2OOAwuuFCMRTMPHHTRzbzCaJ3eCDOgjhTYDj3rgGJn/riQMT1s7AP3PN7nFOKADoNPqXBbupQHnvRSc1XfV33g5Ps3MF0uLpHVWfddeBjR6OMtOiVsNrpcReJghMl5Z7GDRQnLXCA2CCbS0Wk9aqKYbhbPpwH193Y8q8UaPwAAMBM/9FD5v/RQ/rwTRTc/7mjq/tbvXDit2stI4fftABEglJz5/ojCV2QRnJkUramcvJ+RoXsz2lfmYeLVlGbT7pHjtKBxxIbbVpP3vNGfzcKaJtFqDBskU70d5faopbepRSQ7OHddtw0XZZijIgmh2wBxpYEhiBjnV8Ui9FgLDC7b4yey3ds4Rr3ippdUfaFarXxQMefnizKVpdEEhabR2EXivtgIACQ8K4tDpdgeYaeIyiNNI8erI0JgidznznsFU0Qx6XDSSd265oe6tN+3mSu2gt0/X47dPZyXxB8Q+0bxw4KaT/LfJBTo4IqTAjmnRzLrondA/gP+b4bmOjfXf6f6YjedKgu
*/