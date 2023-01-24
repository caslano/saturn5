// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

# include <boost/type_traits/integral_constant.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

namespace detail
{ 

// Here we implement the metafunction that detects whether a
// constraints metafunction exists
  typedef char yes;
  typedef char (&no)[2];

  template <class Model, void (Model::*)()>
  struct wrap_constraints {};
    
#if BOOST_WORKAROUND(__SUNPRO_CC, <= 0x580) || defined(__CUDACC__)
  // Work around the following bogus error in Sun Studio 11, by
  // turning off the has_constraints function entirely:
  //    Error: complex expression not allowed in dependent template
  //    argument expression
  inline no has_constraints_(...);
#else
  template <class Model>
  inline yes has_constraints_(Model*, wrap_constraints<Model,&Model::constraints>* = 0);
  inline no has_constraints_(...);
#endif
}

// This would be called "detail::has_constraints," but it has a strong
// tendency to show up in error messages.
template <class Model>
struct not_satisfied
{
    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof( detail::has_constraints_((Model*)0) ) == sizeof(detail::yes) );
    typedef boost::integral_constant<bool, value> type;
};

}} // namespace boost::concepts::detail

#endif // BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

/* has_constraints.hpp
7QomF7hlhVXQcv8cbQXGT2KhViwRErgChWGmpHi7KzK8XTujt4fgdRrf7GHI7IV0fEVar5ryapYxl+in8suDmSrH7noC2GjJuxW9in1CrxiTVsn90hGhkh58jZLJyXX1ZK50ZJ+fczbDV0pNJl3GQih8tYnJ8K5qmsY3CNog2gcVPIt1VEDV/zPyv03T5s4KuCE9i7dBHyybhWcemv7Ow+SdmzDuBC7CnxqPBZfxo0fN770EhV81sXn62rS2b7ZLr+LPUCeJSznLnNf+bpq84iq4IZ3AW1AHddowXS8dNz9/KxQa/o7zf39nrfuA+Eb6jEo6jpmCFgKslF34kBnWw1B4gsPaPA3W3Vg6BJ3SRfQHs9iYn/m7afYF78INMRsTq9fZbE6U5mnfkgM3oNnFs9hMFZqfJ2eUbyHPf85sVLwp384wUu0SHadW8/P3QuGfm7n9Y7OVgTyNpTN4LTnwNHP8RzOcCSg8z+EQNyKSjUS6LKaynBnafN78LokLcKmZxwXgbW7UoN0qiR/K7H/v4r4zroXMDXcR36+HYZmFOiezUVKqQiF8DuUR/686iYOmkTObFv8YNo8CeHQe8lTDL4y1J5KJa5azZA5a1OlEiwDHLLI50FyuY1sH1RBn88FHIDMOSeRxjQkKYIdChqUvsLBMXEKkK8jmFJCzytG+IKmFzXGUz8CryTfhAhuF2e/BeXL/Irn/gSXustQC
*/