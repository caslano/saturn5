/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_LOCKING_HPP
#define BOOST_FLYWEIGHT_NO_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* null locking policy */

namespace boost{

namespace flyweights{

struct no_locking:locking_marker
{
  struct             mutex_type{};
  typedef mutex_type lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_locking.hpp
DF/Jahz/cdK3zALfq5sYvizEt+gf8eEbY4Hv8i8Yvj2bcfx/Fx++Ix9E42tN+KoQ3+f74sO3ygLfY18yfD7ElxgnfZMs8BURvgObcPzHSV8a4dOeXBE1/p+3M353vk/w06Pg39hiBz7E4cv2meFPsVX/GA4/JAp+rK36096P7s/6B1h/XvUY9OeV38TXnxv2R+O7jfC1R3xPvhUfvmmETxv3vLl9rdbYaV9fDt82Cn7gZjvw4fcI/uE1Zvhbn7MDv4rDXxUF/8wmO/DTOHzDc1Htt1V/Xw7/QBT8QFv1h99l8ApoTUZqA3zIJKlcab79FvCv1gP8HW/agp9mAX/4eYBf8JUt+L4W8LUIf4K9+sPvRMOfUovtt1f/Kgv4gy9g+/fagp9mAb9/H7b/kC34vhbwyxD+BHv1h/9B4+e6Vebxc4at8beKww+Igv/oxRjwuaz9BB8gPT1ITsxOIror8UO+epBU59xzPfCTMRXWUf5f9in13RKjvs8/Uev7cXd89dH6vy/6+9Tg/Hj4C1vfZ4wF/AUIP2iPLfg0C/j7XwP4Xvbq3/l2NPzlCP/c323BhyzgK5Zi+/9lC36MBfxIhB9kr/40C/jUbdh+e/XvfMtifduK7d9tCz5E8Fq/e8zz4x9P25lfYzj853eb4W9Zbwc+jcN/+7oZfoKt+ne+SfDPR8G7bNUfejO6/1DYrz0cttV/YyzgT0D4Qa/bgk/j9H/9ZFT7/2aH/p17Cf7ZKHjXOjvwIQ5/bhT8P56yAz+GwydFwd9i6/yWxuHnrIpqv636d75B8GdFwbss65emWPqSW00opCMSKf7TErZHuyz5PVt5/Tsgh+6UOLU5TxmXaVd4kPRe4WVywleYsBUyOjNrLj2mfw/oNlYs3IGh076FXY2yXn3qWFxDUe8/7aGuQkWB7CXPZ/V275MXc/i5CC+sN2++IwZ8TdLQ2akOmU2o2nNUp2tkSLZV3K6yaf/0dwL//jP86HVmO6jkAxybnf2Po3ryM7N8+dEGO+NvDMErcOeLdaup/vjhD9Qf4n10Ob1b6792M/z2dF7a0PvtChFnPWRPiGglT790Qu0spO0iTlsNI+twILSGBbBbh9YU/16phywMgPKS/PcO1ROr32G3dnC4qwWf7AgPpkJ+2CPIfaFa8jTFuzAZLL9gvgerFn+ogwiFchsZahmzr+yo3ojVY/HVaet3SYnuZQUi8zE1UF9WOlOlDMZY4Sz0WtAjYgmKSHEMK/jEcYNtpwvJbE1qlJTGC0T4qllXXL5t13H/Kd/TuAreAs3UY8qpwV5EAClyAUp098UpJ3o/KegKY/QXTysR2Ql7dEX7llwiNtMnJ8JHOyV9JcIgHSeFsBdxBrvgn4TM+Qegg/ExKXP+owDZOClBujKootsu+nuV+g76Cf2ZhUNVXu+ExzlVAjKUsW1dBhBRXacg22NC/pjpfanpfTl/b1znEolJwnNnQMsGLvbcQa9yRc0WueJ+sZqlg95yvQtaRomrn5Eu/OZW63aOtfish9tbjK8E0A6cU3IsE2XitQqWKocsUCQLjFYKLNULLJIFcpQCyxU6ltOVJPHKeqKsHY/UXS4czPkW5pVzUv25zNquKZ9+udq2NmI+L6b5zNP3Q7pyZ+v75bTDbNisW0RdlmCqPF1UTjB/fpTN+NOxLHZxsM08eJoYbIUJ0Fa81TQDpq2CIVVggHD44zCLgknpQcf26xeXq3DMwGxyO4InqUkMJlLoVoKNKTW4RQ2NoWhUHroVbkbl4c5wp/C8avyo2t1w8BUJ1Ziw4J8ygeJ3HLpbT1iOCQ2QABN8ymt6OnM5e2Emn+N2tpL/y58a/2kHsRJrlij80WW3Ns8=
*/