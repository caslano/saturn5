/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2010 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_sparc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_SPARC_HPP_INCLUDED_

/* caps_gcc_sparc.hpp
Aa8qkbCQWmfVwjNoU2JHDpMPhCr1H1kpmbNVmiXuAxafRtN1nbk/iJHsp+cZknXNChXYZj1BHz5BVvXCUAohYcwxVEVq1JGi2kKsavOfCj3OOUZiDXtNJ7y9XFEYLc5VZxmazc29RD977ivusMOyO2GSiMvt9vwTMAoXVGm9r/QnydTt4hd6b6sjpMfT1JytWtqT0gInlMCiSHldJepxgPntfipv+bKR66sKyKeUyfXmG1BLAwQKAAAACAAtZ0pSFHMVos4GAAAqEQAAHgAJAGN1cmwtbWFzdGVyL2RvY3MvY3VybC1jb25maWcuMVVUBQABtkgkYMVXbW/bNhD+rl9xMAqsGWTFydKlLYptbuI0Rl3biDx0QVO4tERbbCRSEKk4Hvrjd0dK8kscNBsKzHmRLN499/bckQpuWvDzD/t4AcHBdz9T+zfFD15rpXGhvvLI7FeYTr+B+0HFG7w+wdQhrLW+TQ/gSVrf4LnVmla23tD9dPoEczfkJP07JOWbKd3iE6dZ6Z+pfFWIRWLg+dkBHL169RLacNw57vhwzqTgKYSGyxkvFj68ie2TPxJ2fx9o/psP3ABLgy3ASSI0aDU3S1ZwwPtURFxqHgPTEHMdFWKGX4QEk3CYi5TD2Wh83R++82GZiCipcFaq
*/