/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_REVERSE_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_REVERSE_FOLD

#endif

/* reverse_fold.hpp
x0A4nZ8etMefh1BXdRwrt9+xHTOOBe2/nwsZ3g4fgjuTpmL6bsYamb1NZidA9gjKHqJ9/TZml34vEodriU9T4hsiMUtLnEeJS7SV7nIWngMMGPH0C4Do7370KuDsML8KUPyZXwW07uNXAdDb6ZXBfl0/wgn18ij5EI+SLSK5aflf4D3XXvS+nJHm/jiywSLxhW2yl99TYpzybdONdKa/ouVt6E9TeImoM/CtyJrok3W9Rp/1EYlLtfKLuXwHUd5fGNfUgSp8dpv8qpQLNJ3Erj2jfXkjVRfvL7SSL2K/vUbLvExkHt3dY2/FuuSmOsISoq6DZ8pPopueo08Wr5ANJVJ9fUVi4QpZT/M5VM/cf0eXB4Nz15nFsgTuAD/2W+V3OxBVeS3+QltgtMjpv0rmrNRyogIXiZzjjTJnqZYTG+ghcn7Wcqq4wYp/H6tYl5iteJ2uip+iBjUX+96nu/YxYov5TYgPs84kJLlQYMMV0LMhu6fdYKscB7D/V7xt3gDguSrzxU+4Ayi9XOwFW+V2E+4Mwbmb+SVXvuySL2/IMh2hKrF5KuMRprnduWkETwSi96YZQfS2NA1Eb0jTQHR0mgai2WkaiGalaSB6fpoRRB1pOojigfkpeiYAKrUEjj1bZdxxgNlUUa7pxLFg0AVR0UEBTKAEmibuKtSLDh8TIO6tVggmEfpl4+z5IrtpghkmqqIpwVbZTc5Einz5
*/