//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP
#define BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template<class T>
struct char_traits;

#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1800) &&defined(BOOST_DINKUMWARE_STDLIB)
#define BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
// Compiler bug workaround. Previous versions (<= VC11)
// used dummy virtual functions
#  pragma vtordisp(push, 2)
#endif

template<class CharT, class Traits>
class basic_ostream;

template<class CharT, class Traits>
class basic_istream;

#ifdef BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
#  pragma vtordisp(pop)
#  undef BOOST_INTERPROCESS_STD_FWD_MSVC_IOS_BUG
#endif

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_STD_FWD_HPP

/* std_fwd.hpp
ot9tJv7ent4Gnynl9m1ZEsVRbMmuREr7XSj5OEvniiGeFUY0+OpqW491LsixSayTXIOSXWtcYsX1DymH+6Ss4qw0e5x1KnvH/0ZxnTLdvnVrYJVL7gIuGV3XS+hd9d1sTdZ+9vcp7tfMluZdtPdi63iMb5Owz0fNN+ssjY72Rln6wXE9LyW+fPB9rfj8S/1Bnr8JT1Ph2QSebxSPuTQvOsIfbVZUREd4tBw/EUNki3cfwnyrwtRdWhGM9+/CE0zjcfB8p3gCS89Ee+taaTxZ6f1Jk+Ub0aUP2D4SrfyNaBqe68sYshf0hOiq34NOgZ6X7/R+EDwdgn9ld332pLsNrspzktrTM8lfciM5SmMGyVlrfeJWchN5Kvv7bmM3dHIab6hP/IrdRK6xe1IV41Cy+zhU+ZtB0pG4HWqb3cLJ/PyGPL8w2e7/3mS7DfA7eb6kodgAp9j3pA+fYp8PTpzi/j1t4pVcqM/I3bgPgYaCp2KqHhfVyd2Z1Npd53pUTncS/69cxkeOy352slNe3Uc8fqtvb6Dn7kY03JzjqI7T2R+17ex14plBe6P2TUHbmBbcY7TEIBvJVOjwcGP71vW12mPkn1a79X31/qnTRAebEN45UuGu+QXT9P5UrXfF/Bvr+rYzp3VdUTt6md6BtaDgXhR5Plhp/+qQTOd37TchTPE03a5KKn3XPoH2mpZU9V07wtb8Xfuyafq79qQrka4ra/dd+z/UPqVafNeu0hxPaebyWDXN3g9/Pc3eDzdPc/82ZG0OR365h/WYNGCZyuOVtvKiqREOmsmmMtPneNts2a2nqzBNrDEwjZ4jXMqU45cxXs52mVlSVKDtI/Mzaex19sFKYZOpX5cVwdXaI9GY/Dt5FmLc/ALUD/sQ/gly6ro6Lns70LpRS/L/2ShAWv4Ccuq2Og59Xnkxjg7Ok31bImeIZxFSM8Wp0+o4qvwGqj/5R8leZjlTjI6T0GltTmWWTPsbToBEn5J6qBOq41h69hwKc1ml70613nrhlazrlyKnH4N6mjGu9XvM9WwZnf519J4Yy86WSfH+YFZn+3iaeMbRXHJEJupihsix7OrlWFPhnyj80f6Kp6MiolpWu89CwqwMvmNp2xq/oVD8MdnWt7Zv0PcfCB+dHbRHHarV3q1DmTXve/0r8fSkNISmOzU7mO4t1aa7Hdwi4fZPfR4LZI9O24ZafksR3Bc5m+pqlBkJq8hMY7rxmjG/Vt9UNLCff482qG1FpL+QfNC6VTKNEdTvWbeyy0T5dkLi0/3RvieE27r7eeEiV3+fyXLzsMjVNzLdbUwbZ+rvIPlOBJajJ6a7yNHcQjc56m5Lmu4uJ51yUXidctEp9zSvQ+455Zvwuss3pyzT/NRv1+Wg7HK5bUYZ1ffbcNpbsK98Pz28syv/W+0qVAdJKpD7XeXbwWeBt6r9rlm2tkCHm9nbQQ7ZPi+SPH5A/M8ZF0AXbQ3qBOoFmoTdBE+579eQd0CKWO2lwPp+Zgb53W2taw+l5wucbUnHQ2krNyieTBSeS1vSvA2sdoecleTazmkbRTwPeRZjBOyKsXif695Ae1zlwbio1vQazVzi+Y0nOLbOpOclnrpGqeQNp1Jksyx1tk973tZYbV/vG55C/rM8+QjVCiPUDpDTrqTjsa/96z0gV5L/Bs9c5Kwlxs3HQFWN7wuJN4rqrVyP0XxuIuXlUnmWvCEllc5+s75VeZT8u+izIxxnwem1f35XVj6d/yRp+WcWr9/48V990PmgFtBd7gRWd37cbRSumacbdI9vQNeasY40O78t0WNb3xmKZ7zrNwgHKHxDhMczfj1Pzx3A25DkzCbI3/Q5Mgbm1awfKP4FxE+2j3o=
*/