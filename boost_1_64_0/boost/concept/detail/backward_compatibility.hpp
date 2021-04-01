// Copyright David Abrahams 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP
# define BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

namespace boost
{
  namespace concepts {}

# if defined(BOOST_HAS_CONCEPTS) && !defined(BOOST_CONCEPT_NO_BACKWARD_KEYWORD)
  namespace concept = concepts;
# endif 
} // namespace boost::concept

#endif // BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

/* backward_compatibility.hpp
/KJnJ1nxoF3svMvNsMw2hN9Id+KFL8TUOTlZfD9TNgP7ZQwI6pMuyE+2WYmWzPYczeguwNVAKxvwdbEypfb2hGtcU+1tZ3FUE9nQyGG6YmFTkxqdEyMyPn+xVaFiN15OTpY+MNH1tD+EXZBZpx8IFAjQPHd65G6Ko5rDFZ2VOOgVz0qiSSyoczoUx2dJy9fYnzEAvBqq5u/2yDszcdn3RveL4DTdT3LFWSAXQBbIpBhXAx2UFQjI6OqTqWLpmmeYxlJhg0405qN26iYF3p2b8Oz2LaP7zacCgRnpn5Wgda1ykPWuHovrDF1jNwqPum2M+u3y5DvnaSTzY7jIfVYUVnHt6Tuublulnds6bG6Oa6MRxtjIpAIymLQk+B4UYB81K84GYoo2u7VmMjSDNxZOuJS7WdxLR2sAONMbIfzGHdEh8zGGH1x0Xno5GokIzLYMEOHlAxlcx15ITQuaFvlV1QYJNIoc+G47ahS3r8gzjxLdlXA281M4xoulhgcvZHUhgU/ilV0Fc2gqZsddQ4LOC9d4AtnoNcr1Swz94RdWFNd8z9gAKS0NZCTaXw==
*/