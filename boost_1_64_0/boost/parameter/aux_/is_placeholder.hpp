// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP
#define BOOST_PARAMETER_AUX_IS_PLACEHOLDER_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mpl_placeholder
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/arg_fwd.hpp>

namespace boost { namespace parameter { namespace aux {

    template <int I>
    struct is_mpl_placeholder< ::boost::mpl::arg<I> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/bind.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_mp11_placeholder : ::boost::mp11::mp_false
    {
    };

    template < ::std::size_t I>
    struct is_mp11_placeholder< ::boost::mp11::mp_arg<I> >
      : ::boost::mp11::mp_true
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_placeholder.hpp
wBB0TjsnVN5z56ZlxM1NyLEPlqqbS12p/Edg5xFiPvZZ7vp1VfxWvX8zqUvx68I93Jbldl91XbiH0/yvV/5rXX5P+W/Wncm1R57Ry3N7OT7jNedUF3ukcfKbtzPQ5kDqy14v+uA1JStzriz8rVq2+hzl5yrMJN5XXNv8+rzc3Pa1iZYPte9G7PXcXJ4ruvwa6+V3kfakZ1jKOlveh/4b+3aqMbm+47KxZ2xX/f3NOh+gbONvUeWQPScutld4v7ixg8YMi9NqPmNeejpeDM8oqrv+hak6M6YXfe2V6b0XRP5N0rNmWi+zcW3gp2zg5rBpVs4Sh7xjXNWTFlpbG256XdP96/auLhyLow60vDSWvDiuHRtUvehpXn7PE15lnbn0cbly3AYj9riE9PTMBclJLvVxuY5j0Ps4m9mx4q9q/5aYkm44f+9W+1tZvC/zY1N+HOOI1cpPx999d7fZOdrgsv7u8vvBaCmUp2Uu4Sl0An+lJmWTnpk5Z57VuX3USRXmWrOyIj5z25lAmbt/Q+0vstTh/6PI1D6qSnlTRvq5/J7at453fXqY2rkfUfvXW+611FZ25tZw+mkaQj2ufe5h3h29RzKGrVvXtI4C4Fcq/DLLAounbjtVodzqmdaZHzyl9reRcYzD/60cSwy25Y3s495/w2bdxLZH2cCNWmG3gasVevl5v7qHPcJ1Usdr0afaGG/FlXWcPSfN6sTOWh+/71Th5nMUdSzppvbCErfUd4Xdlk1l1DGf/7jan2+Zy/9VKM+0zvV4/iM7mwrV7lX6qpw+lnL6tql9+0fDtnH8sJLBsKI8t1mBPCjb+JV6uc1NMIyMnT1Hm6385zB77GFaVsSnl1W5/ToyM93w7Ct5pb3tjTIvI8JXPbeUSZPZmEL366/GCQ6/6cnG8cQC5Wc016OupuNFPT09jsyMzJQU5TfA4DdA91v9mN3LhWuYoy7LVV1K+RjHh3LMgcaxoePYxG+A7q7yq+p+90rzuo/sY8/QZDlnYtFPpO17q173mFdLzVc3x6r8T6A0zedYiU8f483T60NM9Q22a22Vv0am9W+Mo6WKw54tZeBo3g4IY1qHZvWt+/XX8qgGhdbL8tcIBik/N/xb52mw0ea/yvEHSx23VPuMx2WPy7dKnRr7tqR+9oS/lPdHf4EeD6Q/NqlDmWg3nEM0nLm0J7n+36PClFsaksIOZDoeuKJMpe05rnlq/6uWh82evVYJ767uDeZlZxnOy0Nq/0JLEO3J39HnKrdI6qmDaT1LnPq1xVLl2vKO2n8vlsl1qvabql8+rPavs2Qb7cMd5w9VevG33357QPk5amlJvxrFeVPZl/LW+tV47zHebTxruWuTRIG1eJQV2MlwHdD7Pw8X+j91jkudyLVA6l3KWNoJ5YYb5SZ9YtvbLj+/Ky2aJ2e/A3H178W52vf0XO3vN5i/99/5+3XM3z/k/H1FY1JUfvbeXifkukXPNv/No1ub7RM+df47BOa/u+Ds9xWcv/foOz/NvfjE5BYb4p+sd6v3IbfA83990fn7gcx/p8H5+5zMf7/B+e+CmP8Oh/PfezB/35Lz34Ewfw/T1b9Xyfz3Ra7+dz7Oq/f8q49ae1gOR6O+jfTv6hz24jjztFNGvnd1U/PA6nsRqifu8zm+s1p4ff2sWter9nnAzpJWb3f7O5z6QB/NP2wA+8Gzyr+sVwWHZLsZvCjh3fHnDutAFT9sAutCzV892Bp6wy7QB/aC9aGWNz84CPrDcbJ/KmwCZ8IgmAabQiu8BmbDZnARDIMrYAu4CjaCd8j2nTAY3gdD4AYJv1HCb5bw28T/U7J/l+x/Tfa/pfbLb0w41ouCZFUeyFB3rfGn1l4=
*/