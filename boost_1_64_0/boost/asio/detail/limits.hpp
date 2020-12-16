//
// detail/limits.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LIMITS_HPP
#define BOOST_ASIO_DETAIL_LIMITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_LIMITS)
# include <boost/limits.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_LIMITS)
# include <limits>
#endif // defined(BOOST_ASIO_HAS_BOOST_LIMITS)

#endif // BOOST_ASIO_DETAIL_LIMITS_HPP

/* limits.hpp
JozVTT52pjHoCvf9whh0le/GUN3g1zFMt/nIS8ztzeaEa5c6bvRlXek3GGyfOi9D1fYm539lTerwcVVrSYfLWK5bfNDlnlld4l9goq7x36+0n67M9rxgdGznqVeZZx2+CkN1+FHsrbNXd6UzMdecVPmPWKSb/NI11oAOH3St9aPD49DW6TrnwXjXUuKbMUE3+IZfO6YOb3u972gdPhb9OneD+cMkXeSv/8a90xV+ELN1utH1YcJvzRUfdpNnTTd45M3Oq8t8OSbp8POYqsOvYbZO8/weQK8Or0Neh38z3zXo4i1+nyCncwv8lsbGuBb+O7K2V2/tSs9ine2123z3Ykgc/3fmDEt1eNxCz7sOT0Ga38OOh8E6/MPbjUGnO/yeR0nX+abfuzbd4mzdWtU5fgtTdfkPvk+xRLd48zudVxf5JCzSZZ6BubrK87FQ13kZ5ukmr8Fs3eZ97jK2W3o2ea9F1r8Oj8FIXefZd7s23eT3sT7Gf09X2hUDbC/w6dhoe4VvR5ftDX4R62LM/CFW63SvtYGVOsf7YZUu8HFYoUt8PiY6TpWXoaxbvMVi31M6xwdgpi7yDFR1jR9DTbd46z9aPzrPV6Ou6/wxlurcfdYaVurwmj8Zsw5/hAELjGGJ340Yohv8AXI6e7/f2MjrKt+BPt3gD1DQ2Qfsg6Iu8o8wTlf4HpR0k/+Nsk4P+hym6PD+Ddelw0diga7z01iiW/wRlursQ77TsUKX+GKs0lW+A6t1g1/BOt3mnR52T3WBT8aAW+3DP3jE2tDhPZZ6b+hwEWN0+EqUdPZRv+3RpYt81jL3SDf4TUzR6TH3arl1qNvc/bjx6xwfg6W6zNdgpa7zRxhwm32eMG8YrKv8Cobp9KTvCOyty7wMq3y2xReucL26zm9hvU5PWW/YqIt8Ccb4bI1fxFjd5h2ftv51ke/FeB3e7BnPow5/punZ0OHPY6EOj0BDh//wrGvR4X60dfvP7v9z3sm/69nkNzBCh/d8wRh0eD9M0uHjUNGFv1gzGKBb/Hy/Mejw9/5qDDr8MyzVbZ7wknPr8IvYoMM7rPKuWdizyUegV4cvxghderkr/QtFnXvFtWCibvGef/N7URd5DmbqOr+Gqm7zKS1r9Xb3i59FTbd529fsr8uc+bvr0gWeiUF3OA7/F3nbs6udH4N0iW/GON3g9Lp38UL78PFYrsv8PPriXHzoGteoS3w/SrrF+73ht2uMny/HBtvr/DbW6uxazyDm6CJ/8k3Ppi7wEvTrFn/nLefVFf4PFuviP7y/Mcfxa/zJdd4Vtuf4ImyI7bzF276DYjtfhGZs53+gbXt6x+9MLLA9z4ejrkt8BWqxP69FRad/um+YEmPgCzHCfFb5yrZ50C3+AEmnd30foVdX+D5M0E0+6D3rX9f4RczSbd71fWtSV/gT/7b2dJmf2+A7SOf/4887H3qmfu84fPR/HUdX+L8bPTu69D+/lzBBZz8yNymTJuk6/3uzTBqui5/IpOcxTKfNM2nUgExaFePhL3wyk1bqAi/DRt3mMwZm0npd5Re2yKQun80PyqTfY4DObZlJm3dk0nJd4AfR0C3+SWcmVXWN7+7KpLpOmUz6GRbEdm6gXze5uzuTWjrHz2BivWeTOz6VSWUd3gczdYUvymbSXN3kPbbKpF4dvh95Hf4rRuvcp50XJd3mMz+TSQt1je/DEN3gl5DTucGZVMG82IcHfDaTsrr8uUz6GO2Yh60z6fsYFNu3yaQHsCHm//OZ9FWsjXFy2s7+usb3oF83+AUs1y3+AE2dejLpc2jpHO+Dhi7w8xj0hx52v76QSUN1+GLsrcO3oajDj+TMoQ4vR0WHV2G2rm6fSX8=
*/