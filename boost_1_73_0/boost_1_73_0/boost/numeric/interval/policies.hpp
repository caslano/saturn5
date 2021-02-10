/* Boost interval/policies.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_POLICIES_HPP
#define BOOST_NUMERIC_INTERVAL_POLICIES_HPP

#include <boost/numeric/interval/interval.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * policies class
 */

template<class Rounding, class Checking>
struct policies
{
  typedef Rounding rounding;
  typedef Checking checking;
};

/*
 * policies switching classes
 */

template<class OldInterval, class NewRounding>
class change_rounding
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::checking checking;
public:
  typedef interval<T, policies<NewRounding, checking> > type;
};

template<class OldInterval, class NewChecking>
class change_checking
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding rounding;
public:
  typedef interval<T, policies<rounding, NewChecking> > type;
};

/*
 * Protect / unprotect: control whether the rounding mode is set/reset
 * at each operation, rather than once and for all.
 */

template<class OldInterval>
class unprotect
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding r;
  typedef typename r::unprotected_rounding newRounding;
public:
  typedef typename change_rounding<OldInterval, newRounding>::type type;
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_POLICIES_HPP

/* policies.hpp
Xfi7OWpB9HSfOR9Vt89tcEssdylQf24VK4sTeo0lCrku8gOKCQZW1qYGN07kZVtvbasEN43Z2lj31MpaGix6ukNC6x02/jT+AlBLAwQKAAAACAAtZ0pSuorDJQIDAABmBwAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU1OC5jVVQFAAG2SCRgtVRtb9MwEP7eX/GoaKitwjL2CcaLKJ0GFVVTbZ2mSZMiN3EaI8eObGcvYvx3zk5KCwxNCEjV2rnc83Lna+LRv7t6GOHRKw3flC5aA2Jh9GeeuYez0/Qe7YdQV7Q+JhJjC7lPh3gcco9BgKSdymu/T9PHhK68N/8Te+RV6rcUIZhHTnR9Z8S6dBhMhnj+8uULPMPhweFBhGOmBJc4c1ytuFlHeJ2HyLuS3d7uW/42Andgcr+jWpbCwurC3TDDQXspMq4sz8Escm4zI1Z0IxRcyVEIyTFJFpfT+YcIN6XISk9ypxvYUjcyR8muOQzPuLhuOWpmHHRBcCLPhXVE2Dih1T5pczhuKus5vDyTVoNdMyHZioSYQ+lcbY/iOGuMJPdxrjMbZ5vy90tXfa/kkkxU7A66dnAajeURfGaESuei8Cs1hIJ1s5LCltHWDUmpPNYGlkvpuQgnuG1t
*/