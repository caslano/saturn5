/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_10022005_0559)
#define FUSION_ITERATOR_10022005_0559

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/iterator_adapter.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/mpl.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

#endif

/* iterator.hpp
HJmQY8c1csxPyJHgu3FfpPp+/D++8zrhqzSOY+nOsb/HnJitPTdcEf8fWfw97PG8m+rdKamu5VKtv4/l6BXx/XD/zfnc8rXnc+vWbSba4994XBH7XnY6333YWM6Lz4nMf14muV6I+zj1Wrza+OsY+q+l0T1BI/n/dZ5eez1YL8n/Y9I491ybk2Lf2a+VZcs60Za5yZ6LpVhrFl+TlOw5XWYs16WzZqrFJh6rUrxbJSFjQufad9um8a3n+DnZ8ngZ4xkft+64s/Hj5rrvaibq/8k1V62dk/43OP69gBaJ/cR50gbHoU04Z2yQ5rdTYt/dj73rJ378TczZ+HqyeH38uUf83ktMrnS+CRMrY3KlWIOemJ8brCNP4/pto+/8TNCMHZeSfos7vrYge8uofZ1+UciQ645VtXRjvoi/u+qHONaH8rusf/1X02mQ5nfP0s0z6Z6zNE7jXXC1+sT/g5/qv/Lx/VTPJ9JZ7xSbszG7xt+lHKcX+05uYj/1dx/ifomX8fmQyM9T1553JfJz0nm88WNTYt1UbD16OvNz/Xcrx9c9/YDv+NjwnPs73J9aW8bs/h3WZielGzte1+aR+H/Ra8vl8XesxO9Nxsvaa7TE+HTuoa4fn6mPNYn9+DEndqxOcixJXBsl9jdhLUS6+eS7rrWI5Y3YNXJCj5g9Uvs5HqcJe8TzUvxeQ9L7K3GeiRiPyR7/zvTyNHRO5vN17zlP/g3c9cvEtUDiOj3FN2vjz45jczm+viL1dwES9fFvPXeLnT+kOM9I8u7CeHvcngm6G76/OC5vPHcti82R2nv0sfU4MR+l+G98Gvcv032G0eJ73muKvRt2o+9UT5mn4/de4u+Sidcn7iPE3uGW8F/8vb2JOGyW4h1c8fPX+P/t4z5I01ZVaR4zqtL4PlaiTHocTpmb48e8+LlobHz8HkHtdUE61wkJ38Vy2caPactTxHp8fqZ7LE5yzyd2XRy7jtyEfkGOdO65pyPnf3v5/6JH7g+oZ7rra8N6jO9z7rfR7wKkce7c4HuuNWqQxvrZeI6u2oRjSzL7L0+8e3JV7bsnY9cmf/+fz3f4D3fY35Rj2/r0NmWdboMfwK5/P0f+Dsfs2PlQ0u+ur4jfP4+dH34XvRJ0kn9nOX7+swn7a+WJrfH6F3z3J9DdlHjaeHv83D9uh3gcxuVI6LsJ905i/JO/XySN50xr/JbGtU/jNJ7lL0/jXkzCHrHvOSXvVxWXM41z03TOWZelkQ/CfjrPV9fsx+wd/4bn3/XehHy0wXd30shXoT6d49jafrF1ak02vj49yfVMLI/H3j2wCdfYyfRKda/sh7gXGOikc9xt8D3zwfdtj93jS5xfx/5vlFjHlVhXeXPsWih2TRvjFXvHUFXi3bHx52fxNeW16/fi78BK/d36xNjY2oB/uIZIrI+PrRH9x+vkhAyxtXSJder/fJ7E8kvivQf/3B/prjdsnt75xFq9+q33jDt+ryBRxr+tFZ+T8bL2GB+v/y73fhpv4nf6NzXGv297bE1yLO5TrXNP/b/muP0T9w4S975qY2xD+65Kw/cpzk0T/oqPT9QnynS+35rON8GqUu2nUSZbFxa/9qm1f8q1wCnOwVbEz1U2Ye61SGN93aa8m+S7nnv9p9vj76lJHNMT9fF3vNS2J+J4E+zXIs1zrP8Vu8a+WZr0O8sravfj64vi99hq6aRYm7Ep18rfJZ+sSvY/gTTGrn98+ne8U2D9Z+OZKd7Rlhm/Lkzj+NtiE2MvXXk32p58HUhinv3za/n15086z4/+6fPHLdhsu6Xbzk/i+6rE+8Zrn+HE/0O/Kc8d0j1fSGb7dd8kTu+afv15WVu28m7UFd6Nmp0=
*/