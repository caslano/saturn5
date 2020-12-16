// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#include <boost/config.hpp>                     // BOOST_STATIC_CONSANT.
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename U>
struct forward_impl {
    BOOST_STATIC_CONSTANT(bool, value =
        ( !is_same< U, Device >::value &&
          !is_same< U, reference_wrapper<Device> >::value ));
};

template<typename Device, typename U>
struct forward
    : mpl::bool_<forward_impl<Device, U>::value>
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* forward.hpp
WokpW2bQn1Vl+wCUbv2ppccVVlZaveXY0c5jo4cOL8wfesDQkBBbFnJfptFlpOToc2dC74TiqomVcrw7xz+nY6rBmQ7TB8bQ0T6uctzEkExWOn0801wyOh9kJJ+ZtozySWfOayF9/7VKxjVdQbLrLvUaND1SRtdd8ppvkBmj1odXGWq5x5xyQ8ceMNKWbRRU8yx2y6StXPMX2jj8sKzdhHIvU+MQhoRa7vdPoyy/UZbVqixqLJB44f5fEuPM+VZIvuGN03Ketv3Mol6vqLYtK2eyfTnZEjfcf/Mtkm9niWzv/NL2UxeRr3J7pMbKEjjO2JppvIV44WOLE1JaLmuSjIuQrj3uFe5bPmDWS1Fk+VBpy/79Qm1RNM3QFpJnjeSZJBE7Er6ibCsi88T1lKXrelQUdXWOeW0dH6n7i8inXvJxndha//s1o//6DdD/fqJ/ZxkXxZv1n2csY2xtsKgqog10vsltItvgYspnPWjKd8PaoaaNuY7ZD7rnVkVlZ2Hn/A2R57z2ORZoa863WnQbcZGMIt/QeZ893Xje6zrf0DbS9n7g+pwrdTY5ROygx5CNtkfc9bc90o2wvex2Zv0UGPWDdmOwvRnTm7a9ee0ibS89h3xNulGmF7vt9ZO8ctpHtsP95FXhzMuhf6uZc79iA/RvybnvLNuC9k3cC51li1HvoyLPeZ3fuvaRel9i34uc+W2gvjMSgge6ikAm4Rv72h7Mo6RfmTh7tIL69jWjb+LouQVfboIc55tl8q/mkqWt+auZbxNd7XhyFHUMtaNP2jE0r8AuV6qUi32Sl70vck2hgYmRullDevVO3eh7X1A/Dc3di2LQT30M+qnfAP00rId+QteFwztG6ucH0rOWa/247ktBHX3XtI6IG72OrOXR68havv46+m4DdFSdFKmjtaSX7dKRvn7KefZjMzrKjkFH2THoKHsDdPTjeuioX8iOOgUTTAsCGfwvkV5eUEdl/UpC16CWr/l5jvr+onQzuarSqBtkXfWtjqG+lqu+5MVv8nJdQwYlR9ZtHXGLXHWTa0iL7xNFMdSvaAPql9BC/fQzSUpk/X4nbrWuX8Q1oMVn9uoY6li9AXXcL8o6Bjq76iiTZup0Hd3ncMvPhnUx1LFuA+pIGZqt4/dwSSvOn2tqntzNW9v7k1Ym1kzo8d6Q7x7of0/qpD2Pbno+nHkeXuzz5OapeXKnrD3q0KWpP/Uess2ip14sPP+X1psn91fPhzPPw4t93uF/eV5dtiX9UbANYbXLZ9sop++5ZuRynL7iRK6zQW47h1xRM+lt45BbIXJJLaRX30y+2U7ffc3km6Xl2B6UfJtNj/Bg0+nt4ZCrbibfXRxyuQ82XY9hDrmCZtLLc8oZ6mFKr6KZfDMccrXN1DfNaQeGfE3prRC5ri3I1RvkTHZgLTfImdrNIGfSS57IpbVQviKDnKl81QY5U/nqtJy5fJ/Gkf+CeDXnsT88nDCTUEd4jPApIfES/MERDr4kPuZ5kdXEMc2NXPfIxjU/8oCt4v6xOZLN+V/s9ujGMVdy0KOx+2Fchk7XwQLiBoZSnkf/vfMnK+f99XMo53OuLCGsJqwlZFwabw0kHE6oJiwiPEX4kpB8Geck4QBCBaGGsIiwglBPCCyMt3II+YQSQs1Cb/6lt3nbxrL9jeP/JSWtMP5vj0sPdYxLf+rTzy5qSyfcbX8fvsTZN15SqspTOJWv5KL77p/4Jh985u/Cl8TmY0/k9Xv8Oxktv8dH+BeI0Qea81vJV+LEJzbBR6gldENnuWE6U1MBKorHH1soMxeULuLUN7eqHc1jXQ69/RTsk6QoRr0ha1j/bnujzsyy/QxrjbtkE3Ii10sdqI4=
*/