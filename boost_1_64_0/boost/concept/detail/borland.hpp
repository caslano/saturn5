// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

template <class ModelFnPtr>
struct require;

template <class Model>
struct require<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )         \
  enum                                                  \
  {                                                     \
      BOOST_PP_CAT(boost_concept_check,__LINE__) =      \
      boost::concepts::require<ModelFnPtr>::instantiate  \
  }

}} // namespace boost::concept

#endif // BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

/* borland.hpp
OvWyw6RbGt2tCJZtv629pUTvJY1n3X1AAOtYPlSvd25UJgRyV5p4Bk2HsnhoQgrlUu6TdldIzgGR22BopWvOVOWy4+sebZLF3FbYKJsCTAC3Htf18lbUGZcWhudocEMqDV4Caj6SKQYao02+Hzsc+BD64VJ7jJsRZtBa5Hz4KZ9/VB9e+Ye/1BmMVkzzLbyWLf5CISfIzJcDO2CPeHSQiHslCf4oZCTs4xKttwhcNpmLVE31olLKDSxVzvTwIHcXlni6+xqpgm2YVeWwcqG9vYUOQkSRYHoM5vSXTyfEEy0nHN353blnzaD/M+Z2g2qaFPUwDFbk1RcpY9FaHmGlnQDq24gPYDTUhgHZ/P4Easo78enQ4xW1cE5DoEY2JX6pdeYgc4LiUl4Do7vs3J27QL00VP4zFKzCa5uz2Pv24ILt+tf2e5iKRYw+XMZnajfq4xUZZR7YqZ4cjiPoAApQdTb3B6MoZjf3eS40BVEADpFxRg9alN6ZSVKx5zkE53NUv9nD6y3LtkIcDpG28sZCgQkTTjuVAuUaxNHfUsWHsAvFGR4NUjshMqvpBw==
*/