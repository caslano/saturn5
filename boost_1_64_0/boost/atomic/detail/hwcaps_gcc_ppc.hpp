/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_ppc.hpp
 *
 * This header defines hardware capabilities macros for PowerPC
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__POWERPC__) || defined(__PPC__)

#if defined(_ARCH_PWR8)
// Power8 and later architectures have 8 and 16-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX
#endif

#if defined(__powerpc64__) || defined(__PPC64__)
// Power7 and later architectures in 64-bit mode have 64-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX
#if defined(_ARCH_PWR8)
// Power8 also has 128-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LQARX_STQCX
#endif
#endif

#endif // defined(__POWERPC__) || defined(__PPC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

/* hwcaps_gcc_ppc.hpp
r6LUBd++itJXpspb6eZpXSlT0S2ElBvHVbkpXY/S9R7z6Zbo41IGHCvV91OV135r+b8me/4nSb+cefBEGvHtcKrvCwuK03LnFhcvV/n3APkdJfkt16X4i7XUHVNdGS597F6dJN3/lRfmGIs0SJzYQZwBY3F0PH73onLZpHSQ3IvOQoZxPWe62icPRX7aRtu9f6rym0z8UdpuwpMxN5Niq8nTQuK9F7uim8dpO0/GGKqvOdx7lNVWq02zWwTadCk2lbrZJA/AYDbdGWiThGdJfx36MNzSntgyMO3nmM8G97QXzV1QUBQs7W84pL3qNKbde61USNqbiKfGyEzSbux0TXvxak+B27Ui/pqE3LdY+tZd07WxlczRkzydiAwlXTFu6UpXbwqu+dld+TvfLz8JS9fvZ8iHrFbu9dv7PoRbvVPcGNvwvC+JDrRxllnn3W3k4R6kvjvYWGqxcRP29Y8Oz8YdDbRxlNfG1rI2sNg4GBlivtu62ZhLGOqW525nI9WP0ttI8tkp4cVZxgjNM+upHvPRUvlpqvJhTTTpaO2eD6fz+uos/fQd5VkUI/ZnvuBiv4vtYqf4i7GkOehz5kK3NFr7mD9rE/i8nG1+Z/mlkbSpx6Rr2tAP/ZzMe+Hrf0567aqR8QK9pO51QuaY15fPrgyLWW7fjKKfEMwu0YnV47DuUO62+l3+LJTy6vAur78VXW2N9Jl/G33mB1Qf+NztvTq92/urWzuvXp49/4dbTkT6zE9Hnzn3Y9W/NEL6zPMMaa+BS6TvqQWcLvocK02AS2FX6IE9pE90JFwOR8NVcDIshrPgSjhPjnvjOR4knjUSz9UST6nEc53Es1biuVniuUHiuUni4bj0pUn7BEx36EvLlfWr82BvOA/2V26f/6og/gvE/wLxXyj+cUtfv3yHgg8c+vpvl77QjXAIvBcWwc2wBD4AN8EH4X3wh/Ah+DDcJn2ie+Ej8DDcCl+Hj+v0y3cSTHJIf6L08XaEsTAJtlduX59xpvgfJP6tfcbdxf4esBvsKeWUAvvAXvAsces+6CDh9ZHw+kp4/SS8syS8/hIeosOrChJeuoQ3UMIbJOENkfAGq/BwS3hphrxPgyYSXmNlFz8ZS2HyXNgYDhN/OUiM+Jsh/prDieJvgkoHbknHJEnHVEnHZDgcZsOJcnyKcvvCL3UPX9Zh55yEf4mEP1vCz5HwZ8KJcnyKuE+oeOR9Do6Q8M+AY7wPSgl/NOwJx0l9z5L8uwAOFve54pb6J+9P1CmH+nee1L8RMAaeD+PFLf55f3Gvv7HiP07qbzvYXtz6+hf/vRz8dxF/XWEneCZMFvf6SF96pC/dpS/9s+Kmkf70OvanR69gbXkkHylDKpFjSPxK1m9H8pH1yDPIUaTJqqZGGpKDlKyK9LNHfpFf5Pef/fvm+v89GQWnaf7/M5b5/9WNxZAo3o3Ax0h2Gu+2P9XtN5YeyqB9lOInVbfPZCj31d5+OP42++BIhG+fZvGToudMnKPcbzv2a07m/CB1/g3lztb+e7j2a3aAaUrnHeVepP0k2/o1/fso0dF9iWR10D7NNJt+YZA+zQybridIn2am6Nr7Py/y9mnyf4L0V05TevNorxppjDWSdL/ks+r4BKd+S+XvmDrfWvdzfqnc7SmRmarv4CtzHwI++v4Jl1Mef4az4bPUoeNxoccrJPjNK9N1Rs9zpl5wXNcLPS/S3seZ49LHmefQx1no0sfpcejjLHHo49TzguQV5B3p09+NzEjn+viZ5dooUt1kqiyc6ixtm6KfqvviS5R7u2udJTnip5fum1+h3M/Y64qv/1md7yfXhdd/D6kvcr0avuvIo87/RPfdo6/77jOV9Vw=
*/