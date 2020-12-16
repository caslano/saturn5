
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    ||  ( BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        && !(defined(__STD_STRICT_ANSI) \
            || defined(__STD_STRICT_ANSI_ERRORS)) )

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    *BOOST_MPL_AUX_STATIC_CAST(X*, 0) \
/**/

#else

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(X*, 0)) \
/**/

#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

/* ptr_to_ref.hpp
iAnif8//yy3pt6b59ezvn6Ug/Ddnub+HN2/81/y/0rY52Vj/tWxO9u7Ov2n8o7CC8N8K+2f4tx77nfev3n02Xta2tq6/09z+Cy+BP5/rxk1/y+Ph4Pa3Orl5OfwZ/wdPQfifWv1X/HdjCK4dWx3VVH+3yO+0P2vz98r8Trdz2iowWX7H/43WL27//Pw/u+T3s9+1/Z3m5rxt63ZBzn/O97vEAkLbXZ22yf0VXRT4Dv55MsTf5dzpH+eg/TX/39M3Ojhv95LbJMgoJ/AfdN/wT+46+OejUf7exr8ACputm3/x27bR2tHd+c856D88bf+Z769rq2BscBWAntv/5OPluN3a8x/4lvs227/q2l+l+qVQ/4QkBFrO1drV6898v3j/Orxpm/W/MxFgIf8inta/3Ij/jY7cFkGTCLjvsHaTc3cTvPn7EsjQPwj8M11BYX7V7ZebpqB5BM7Hf1X/f62M+y8c7T/q8FdZEbTQr2r8eUSSoAQC0bMRdMuv8v3nO+6O/7PmguvvDWst6Hyvf/Xb/D914q/f73Hj3zCY8b8Eafy/sf+zW/9vvfvrt/4XqX/iMvGfZGeCICxoi78HBVj8VNttAg2yBHpYjqWCv4ZQgyqmQlcQMvxtI//ykF7h5LRty8Ztzmqqpo6Co8C3OP2jB4x++RGrqf46eP6f4kv/cVrSr//3xf689/4ziZPgEtx7/noP1AhlGZ8VqHNcNrMqn4kUQy3K1pkLVcNYVh1rSIZzY8hdazRMjswnD20xXHArIuGQqdhV/436hxyCusxD3P1mCP9DE9n9bxLkfWUn2fjrwqswXHCGjSyd3xyFUPMF1Fp3ny0QvY2ctv28RS+dmlw0aRzNJr3kO9zv9U14yPjw3n2L6LOqEa3MfUxvg7tJWtmW0gpv8SFmW2Gaf5YJudmgT6ImvzrTkUpuD6Gh6Vdw9PQmvrookVx3RrHGyVfgK9LKipqbkCRUBhW7uSSs85p62TmSSZMEFdtn0oKIFkgobaO6lS5MVTeYhtj1g+pmRsYsnsmflKXB8ffYLPMG2vimBxO79fHiyjISm9pKxkatyChaQkPCuqBobEj3V7pjVe0VnP7jNcvOi6UTOoaUVD2YwoxtmGHZF+RccMXU0pOImvSZR0VvoeR+PdzWsQBiQpfQ2BpDIyPOsI1H+xM/u5Drd9XCTFZV4CsXTQ+ktjB/HX/KVF1JIjdDSLH7GdyMo7G33gU+ZuFYo/sEPw3PYiR5wKWbQ2fJVNSXTkKdZyo7pjsJ+3a1sDT7x7RiejupbeeklnYRvYYkQWdFNOuYIwt57elcr/kBpgR9ZzHeFZBzHErqkheRWqSPxutW+NI6g802D4EpVtC+aFusO+jJt+y6j9s3tKh74kqc3KPErHraERExj7cGakFu1mlMuZRBBwNvsr2r3iLt5gnefUWMdF2GUWWqBun0/cz0hA2w6vQ2PvOSORzUy/jA65L0aLIdtR7Xp9hQHzp3jUFt4gcc0RqDECcLds9UD4fdpsI6YjBJ1cpApeQ9XJY08azIAXRH2YrEBsrAL7uL62VpIGCcCfex00RR22UWW6ODNzFLMU49AhuMZNByupAKM/PZoqkrMFR7Ipvxahme7T3KrzhJ0Y0xqvyqYi4t7diO/IpIBPolszmTpfFsvAbLkOiBSt0b5p7mjts37zK4lkHZMhzfJ86Cz8AX/Nu1HZhcIcdXNA1FV3QOa97dRIe0KuBvXkQzDwhx3aEPSOxFMpPPLsE0tVdMsf0iXo0Q5mdXK6BE/Sj5eBfTSs3RdHVgX5R+N+M98pqYWRRNgRtnoUpOgofPb4LMkQvM1cMHnT3d2Gj5iHLC3nM1pTsIHtCPOyS8occ=
*/