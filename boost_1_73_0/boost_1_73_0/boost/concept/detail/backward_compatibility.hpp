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
JcidIK8HiTqJuQFmMdBfRdAdcj7IHJALsD6QC/F3gYQuK4IfQA3IS2xcQFQR/JYXB5iVoKkTsxJMBSjaCWPXCrZQsMWC/UqwXwv2iGC/F+yPgu0QbJ9gBwT7ULBPBPtasO8EQ4bHWK5lsJ8KNkCw4YKNEOxqwaYJNlewGwRbI9hawTYKdp9gjwv2tGCvCvaaYF8J9q1g+M7077AN1l2wXoKthBRq5bJUVKcCaq/ke0XyfSTYXwVLC+GMkf/zQhM=
*/