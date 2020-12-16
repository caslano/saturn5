
#ifndef BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_iter_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

/* reverse_iter_fold_impl.hpp
id2f4HhuHGksn4ZbaauQfuw1sx0XSH2ds+CffppW2PlTYPVziDU70YShG5GQoMLVZiymH/fukkVUFd3qqmL1AtvbYPYMnqx1FzteGuBe60+aO6gUjxbMoia5q2xqWS1eb2uiofMa6OL0JyywVojUX9pjcUsonThdxlsTkulHxjsud/AtlQ4KYZ8fGWOkgg0f3vQEcz+VU/vscTg45CCd0ZLBpJb1vLdgfC2UbmPjyxPp1EtlLjEwk76NncFDB0eh7bYQj8rSRJxfH1I4MotOtJXBU+0IlkcqsdDmo7Bf18ky+vfGvH1f8Ha8FCSen2fXRqTSGwHuOjH/At3h5yhhuzqyN1fyl3oaAvxvIitVfgjjN1/wJj0PaefP8z8E9su+ahd0352Hd7I23Cj+AjSmJ0HiWX86UPUQ4VmnqCBjAGdPE0k10IVZ3lyDa3eCYXnDBZPMi2lfjx15B5lyoe86tFxlPCvvVQVr/xsw0jDH3FFRLPdqOa1begBHxtymy1JhbOaJmzigaUyl460FOJ09aXYa4Fr9NCZseocGb73A9xeY0K27QWx8ZSxVbP3BWp19MK+vNeZtqaFjcwZgjWYVrSjowbLieHRWPGFuXgwKCZ6Qu5BGs+1VKFxpGOxyJrHZi1djd64J+QcLMPbRN1Bx4CF6VxZjr+4H3FiVzHdF3MLdXYpsYcwQdP24zZRm1uD9+cmQbHaE2vGDzEKoGaUpdnyBlBEmfM+nSq9IXJwtC1MfTSxUXM7qhNPhUHmGZnrMo5cRqagZc5z49XZWc6MGY+1i+PVJy2C3fim793kn3RObCwX2HAOTL1CHAJc8X7+OabN7VKB6kYUdnU9nv5RiWKwPCg/sZAv0VyP3bDKLWDcJJ52EaHzvViqhbro+T58Wfzdi3YniNFalhtqn/qBT8srM58xcslNYStbNkdiX5kkuQVdJorCE/2GZTz1Cc2HZ+zl6y6TQ/AeTSFZyGPzDjGiTZ1/20DAU6UnqNMTkGBpWzWTVygkIUlKiFtVpuCzOMTRcMA/JbiW9Dkm01PnRDRVnxNv8IC/9TnwVOcLbayKp7PIN/uPARRoQc49iJ1ylyHMj+FeHtVQp5czEiz7A/sxtnh0OerhhC5mH3qcbOru53T0dqJSORk/iWaQvq2ctE6tQ0CTC9gnWvePcTUk32xJTA56h7aQZYmfr8egqJdIoXkA7ssNI4ZYXz5smQolv3gkwT12i5WGse38jrFcFssHGegjYew7bLWwxJewATiacoTWT1kI/cirGD3amkn3WVJ4jzW9MV0GlWRD5DdJEXuZlytyeT3ZL37KnhSnUd8BOXpmrSWMcn/Afdu6ore7DPOf0pYqsFdw5cAQynj6jA8En0DTzOs1V1cbJbZepfCUj5+AaXJBJRZ7VPf5tnz0sIlVZjnUEHEVX0SH3RHIreAqh5yn4FNuf32vVQrOnOLfx3kDxzx7yqU1FeBCoQhsu78D9NHnmNmwKde01gLOwNxWp3OZxjWOx7vEm/rP2JfXWeMaUbKaibJw8Xc5WhOWuLHZ60jusNwjknq8eYOfjVrqRtoz41F6s+9J9rPCXQK5LHHWNzuAGZ57Ta/1FlCdlgP6DxdkbE0Mye51Ju7/aU0uYJz3xaqL9AzRIodybjt3U5G0DRkEH1kxBVpHcmAVZbf5Aj89qsMzYNjx/PpukEpVhbhTFlAyL8S2iEZLKJmj1Vec1e8ZR53YLtivAA9d4JhP+aEqOSR/Yj5F34N9lwVfc9YPhbS0k+aXCdvo+7jDqPSoa57ChGxYDw6MRNHAY+qnPpCHmoUgaq4EVF3dQ1fsm6msQR95uJJCrdnT31Wcl5fdQIG9Iij5JyLB+A9c=
*/