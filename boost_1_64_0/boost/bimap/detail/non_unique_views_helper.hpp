// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/non_unique_views_helper.hpp
/// \brief Details for non unique views

#ifndef BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP
#define BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS                         \
                                                                             \
template <class InputIterator>                                               \
void insert(InputIterator iterBegin, InputIterator iterEnd)                  \
{                                                                            \
    for( ; iterBegin != iterEnd ; ++iterBegin )                              \
    {                                                                        \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(              \
                    BOOST_DEDUCED_TYPENAME base_::value_type(*iterBegin)) ); \
    }                                                                        \
}                                                                            \
                                                                             \
std::pair<BOOST_DEDUCED_TYPENAME base_::iterator, bool> insert(              \
    BOOST_DEDUCED_TYPENAME ::boost::call_traits<                             \
        BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)            \
{                                                                            \
    typedef BOOST_DEDUCED_TYPENAME base_::base_type::iterator base_iterator; \
                                                                             \
    std::pair< base_iterator, bool > r(                                      \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x) )          \
    );                                                                       \
                                                                             \
    return std::pair<typename base_::iterator, bool>(                        \
        this->template functor<                                              \
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(r.first),    \
            r.second                                                         \
    );                                                                       \
}                                                                            \
                                                                             \
BOOST_DEDUCED_TYPENAME base_::iterator insert(                               \
    BOOST_DEDUCED_TYPENAME base_::iterator pos,                              \
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<                         \
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)        \
{                                                                            \
    return this->template functor<                                           \
        BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(                 \
            this->base().insert(                                             \
                this->template functor<                                      \
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(pos),  \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x))           \
    );                                                                       \
}
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

/* non_unique_views_helper.hpp
fyYvyFPJCyPDg/hjpvG35hrHirnE0SoDrmQU1ycUdCZ8H/rLYG+tXQblC45SBuqemOseji9FP8bXxmmk+zpIfb3frF/kfCZpm2FyneyPijvFO5efmwfsN6CLF/tXxD65pbXXQ/dlfbEYe39Z6v4T3xJ5Vt13nB66J0XjgT7NlN2S6hlVpWSOt97F0fu0pVX24lLGQdu40TNKGmlcWzkJumYiGF9vvUcl7u4Td2PNHq/ieskb/GBPfD4T+82+bPdKV9w0iCOvab23hGvS9p6kbTau4sLTpvHRtC2oKPPOtm4u/hJM/FqKPnDvShNGY6tu15I3gTLY2KCMdou9vh81XueK/dkaz2D6fuHr6lzuw4+WvWSlaV92SRzO5B2VH+Fs7Hlls0vlGHOThzlSzm87kfJrT1rQz/wyx6obG8VPS3PPW0R/BvfsbdYGNHhXmDPnm9dJmcU117webe55mrWvqHpx8H4tnaB9gZUOsilQhEam0WhJ93mu6K1nRPYiBd4rcmi8roPRZ8eUK/KQvX1OF4vfIRHiZz9vXjndIGmaG6Gclvoe5D3VXd9TWfh9BybwvH3G++knqP3k0QvwlLSAWVvcfCfDU1WZAWZj/hZ8G9USP1+pe79dK/Qfq74T7uLQr4QdNawk7JqiqrMC+qbc/8vU0HvOgAfSAu/MSUdslxJSv10fusdqXYR36OYo79ANkHcA5vI+ErON5r0qz4d+j6h/6/z+PEidxEzrpPUOzxS3UsbW9wDu9Yz9R1zyH94FN/m/p5fa7+Wa8trSqvLyaiJq1V1X666+m9VPrjlb6aDo17rB59sNbbvU/Wla17APbw/VTXtzhtKfRH+jt69Vz+43sruWSVsrcUxMkXrNWiqrXlvvEn+KbNlYSeJ3sRX2DHkZBNuEFmJf5Xrn7VeZd0i6XfcrK2bptjmzvrKJ+F3q2u8yW87X+WIf54Y/j7qWyFpPqfHW5wuK3wXu2TxLREuen8MpgeepS7ZXv9ujpmL+FMrP76F/vzWynTICz9jdaV5fpuQodXzCcquO6xol6gR1TN9nukbJfA9oHV0Xpd4XQsoL80B56bOg6+S0HLTex6eIf/3WDa/bQ7VuH5K/fLf5tG7DuzvyHC9vWLcD/VlWNs1eGL1+q798s380d4V8w/oifasUG/dtTf1qJu5ZAaPrWhde6tf3adjumzrRXdzX+SK0zeZ56CVuqnwN66S2MXYbaNIRJ/dtin6YlFG+hLGA++i3Du3HPFJuPxttV/rdjGsY96ht0lyxP1Xq7UupwTArquaUV5tnYqSE2d31vo9wQ1Wx63ZnidtiX9j3L3FfZcU9WtuXCjfKfXKcuTwfNBfSThzWZ8BuQxqT9rcDdoTG79bUIfQH4BJtR3CnbUvktoM2wqwxLjzKM0QehjxDVRGeIWC1HdrvafAMrAltC/R5tJ+90Hf+IeIoqxW1PzQedQ0/tl9inouFVUtDO4H63sK+dqFjjYv83u+HkFt5/UANp53Vr51dvVDrdbGxzzbfwK+LfhhPihuynrbbcYyrEDfSqnEL6QvKvUPeC6sx91/BcNtrv7xwTjD98ytqahiGOkI/WNOqfnKOuv/CX26Nrf6q3TfKaKXrd3S99CLUFf7yqNL4BOLh76EuLCu3y0LHJ7QsfivuL3ZG8Ffjp2Fk2mMpZTyC4qfY2Pdh7ZnPWo+NE32G/O7mhLpruLbfyKp4X9wk44K1+9p+H6zS+kEfNYv1sGtI1yb89qRskxs1T2qa1CXRl9y0SYNxGlkbGzTjOaWdOvb+KnkTMnZT5I3dkDDtw5q2xUurXSY56YGA++nYjXyjEvfpi0LLhI80yiTqGI66b6/rYU3+67Og9tw=
*/