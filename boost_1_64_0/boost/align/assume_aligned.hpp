/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ASSUME_ALIGNED_HPP
#define BOOST_ALIGN_ASSUME_ALIGNED_HPP

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#include <boost/align/detail/assume_aligned_msvc.hpp>
#elif defined(BOOST_CLANG) && defined(__has_builtin)
#include <boost/align/detail/assume_aligned_clang.hpp>
#elif BOOST_GCC_VERSION >= 40700
#include <boost/align/detail/assume_aligned_gcc.hpp>
#elif defined(__INTEL_COMPILER)
#include <boost/align/detail/assume_aligned_intel.hpp>
#else
#include <boost/align/detail/assume_aligned.hpp>
#endif

#endif

/* assume_aligned.hpp
NA+NFGODraxVvNQJiaiB2U474XGl7ww6pvWnnwIow8tfdlxoiUm9kl1Q1MbUgbFOToLFSLroWZie1QRKePWjkMFglleL9bCCrxJyTG8wzV+Tzqc7JyquN7ddCRk4bvxN5a17UKe2JRYItaov/qSL8qbL0VRnVmBE7oGUxQPMx51tLI/21dfHySTspOS0Q5L+fet/EQq0xzzdbe4lq9Y2NQJO4CeMZ0n0umwC+sYsRGFXNxhEFtMtCqUG0byFqVx0t/3GmsSQSaMiSw4DMJhymi6UcDZTv9eRnKCOzpwllFhEkA9Ea6kd4+/sXJQ/np+rHTx8yoRHrIxBEfzJ8WlGfyPi4lCroaf8ELMA1a37SDbt7vlMV2ies2YKe8BM+pCQZiqGOOSQ8LDTkGFFXy1pDY3HtuzhfJrUMheqQswhjN0YYyu746jTo1xIbXw3DGuFR3PnTgtONI9FApVyY6WXkwmT7NzQNt+v3AgjxDDAa+BHFwIDEMdzUI5VKkeyisnar4TPo8sQBExmNpTvGNkLCMs4fotoqOzdSlPHhzdwz7fc2r9rS5pHUaS4ZA==
*/