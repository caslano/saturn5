
#ifndef BOOST_MPL_IDENTITY_HPP_INCLUDED
#define BOOST_MPL_IDENTITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct identity
{
    typedef T type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct make_identity
{
    typedef identity<T> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_identity, (T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, identity)
BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, make_identity)

}}

#endif // BOOST_MPL_IDENTITY_HPP_INCLUDED

/* identity.hpp
Nvx7gVtqFrKEJ+YKlyB8XZm+u9pMn0URbj3lm0rKx8z3EWHGhzaSXjGWS+1Hw2tJuQil4Bo54EWe8o0E9mPSF+lGT2gNRfLtHEF8DMCjv286nQYGfpGg/GXefeuAB/lD/Bjy/KkVXT21CGFVZM/FtdAnKy72kattllgjqF/A/tDyGDfTd6ycx5q5FRcon8zHRDiFztOvrhKnyY3iZwt+CpHXj3gGIv4D4U9+bJuX0Pqm8fr2u9oPtL5tu9m6vhUDcC95ftQ1kKKQc36qJHzRk+vUa74hlrDTUQuOqNfP7d8SZqxfZ92csX4tISU6LV+VR9MXN38ZR1+y6Evhsgd4ceCYmcrrvVguvNYV6l+UAlmPFWqqwg1+XUWQBn3aXHNR9huLMq3WP/k6esSb9SWUgU/FlwDCWFRW1piLSrZoKHNR8fZ/UfE7Lip+Y1Eh1BYVmYuK37Ko+LMHFsnlw/mY91+0kYViu6hiDuhE4a4uqZio+7+nrmWOJOTMs8DYIrXLnQ6XrwFsWEgv4b7AcvxlcBEB7hKA23aDAvekC5sZTEr0W+zmXUtlA9uPTt/Nu9U2etL3LLt5ryp+p1H8iPTiE36sdvPZ2aNF2ct7lc1SZV++Qe3mAwpuiVPZ3feh7Ec8Wmb8g+rM/fsoufuqZG6qfgSMTjGoFgmCX0r/TdSnX69iUH2GOB8BicQOHvxaCrMBhy39Yg/W9gF1jfGN4P6vOn09p8HFwir+t0X8b5P43xpjrS9aIplnY3XVRtdC0q2tFi6/EWtRSMsxNDT6X8SySPnQcDx9ERZ6vRH/36z/Af/fwgt/pZ+WaszdLXyz+1veAngRH37euRASymN6hQshVPTPLYdcoP1GddUmrrLYLdZysXPgxX4LhaG41FzsL0aBLWLBnngvoCLji27TgTo8kYsi8+40l/uxbtYtbsDijMzyb5mZuZCQW8SK/9KPTMBvQDZumGFsB8ZYQLYgc0xJ+cb5R4pg+JvL9PsstR9yKbTUygkYbT8wYdxqwphWG1prbPz0h79p7jsqaDH10A1mqIhW1/FhusocUyuQEm3eYin7udiEWivCV1nyjqWWOAet6BceAQEZy+l0I/TvGjdw2TRDf+EWcAe2TPcuxne0c7v8Xr5lhl4tvldMZnj63TOlCm2N2Ly8WP2f3Ly8j48Z/+gmGf/kvpvERWHq2sLlATCeiCFicpi2cx9JYlJxeVpmIDbSFtI4kr6ju0dsiLDI5bM0T6lJxQOgb1+KIZHvqFGK72DFvj9l3WXt7KRWqve6PU+WUUs7dQ9LyqMXcCv/+pdq5eORAwq8wDE1Q787grlFkG+hvMz4hTRKJeEx847BS6ZuvJIr8oS7+ZVcC5ite4UW2xnJcvcG/DkBWCygpwJlp43hBQLDD6qpeH8fc/+3iK00FjHJLlmVtmJmxSYIcVRRAW1C/AZ13pYbW0h0L/ImIC8b6B86ftF9VXbxIkW4sJIy/7zpcPsOG9U7RGxhURSxlLLV6346XiSFK4vY6wgeS0hFli2Ta+VRi4BpbG3/yWnQ4wBd0ABJil1y5yHp0XZ9Oj1O+4pJjzHX94Me0A/XUnu42jHY0Oyy6iOok2TqnCOpkwR14jDEENSJM3VgjAjqyCcUsdfZSKPyMEIKR9NuMHSCyBhbJyIbCNKtVqR7dSE6xfMsUkeJiK31JBL9kgpfJX0Qn3m7r9h+Cf5fqhL4KC6+X+OnTPqFr9bk0kiTgloJqMH+j9FAPsZ4nkI6a/2pG3k8l91xyPH0L0gfzz982xzP0vl9jyfoOa4sMnWp7OCdQl0u6RyJqPQbLem0k7tVpX/bkn5iWWSzSj/Hkn5yWaRVpRdb0ieURVIq/Wg=
*/