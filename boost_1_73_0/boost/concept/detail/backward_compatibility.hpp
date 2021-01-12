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
v++cpZrxpezuPuRZdn3Q3cvuDnT3suuM7l52bdHdyy4W3bvs8FWXnfv65mdKGGpbh5RC5iMREdTl3LIbkpztetxT+3q/s/BVFmrfGz3bvazCH/b1bCf7+ny20+9H1qo4E3w+18n+Pt8N5D9shhVX+Tqufrs5JC59JT/Tj6LfGbhWeDb0vpdUusVkHiRrPK7Tbugt+DesefzPvjMgrsoj+cau8q2ew45JPfpUnssuiH7K9Vwm
*/