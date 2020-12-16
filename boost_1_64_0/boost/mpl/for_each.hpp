
#ifndef BOOST_MPL_FOR_EACH_HPP_INCLUDED
#define BOOST_MPL_FOR_EACH_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>
#include <boost/mpl/aux_/unwrap.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/utility/value_init.hpp>

namespace boost { namespace mpl {

namespace aux {

template< bool done = true >
struct for_each_impl
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    BOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc*
        , F
        )
    {
    }
};

template<>
struct for_each_impl<false>
{
    template<
          typename Iterator
        , typename LastIterator
        , typename TransformFunc
        , typename F
        >
    BOOST_MPL_CFG_GPU_ENABLED
    static void execute(
          Iterator*
        , LastIterator*
        , TransformFunc* 
        , F f
        )
    {
        typedef typename deref<Iterator>::type item;
        typedef typename apply1<TransformFunc,item>::type arg;
    
        // dwa 2002/9/10 -- make sure not to invoke undefined behavior
        // when we pass arg.
        value_initialized<arg> x;
        aux::unwrap(f, 0)(boost::get(x));
        
        typedef typename mpl::next<Iterator>::type iter;
        for_each_impl<boost::is_same<iter,LastIterator>::value>
            ::execute( static_cast<iter*>(0), static_cast<LastIterator*>(0), static_cast<TransformFunc*>(0), f);
    }
};

} // namespace aux

// agurt, 17/mar/02: pointer default parameters are necessary to workaround 
// MSVC 6.5 function template signature's mangling bug
template<
      typename Sequence
    , typename TransformOp
    , typename F
    >
BOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0, TransformOp* = 0)
{
    BOOST_MPL_ASSERT(( is_sequence<Sequence> ));

    typedef typename begin<Sequence>::type first;
    typedef typename end<Sequence>::type last;

    aux::for_each_impl< boost::is_same<first,last>::value >
        ::execute(static_cast<first*>(0), static_cast<last*>(0), static_cast<TransformOp*>(0), f);
}

template<
      typename Sequence
    , typename F
    >
BOOST_MPL_CFG_GPU_ENABLED
inline
void for_each(F f, Sequence* = 0)
{
  // jfalcou: fully qualifying this call so it doesnt clash with phoenix::for_each
  // ons ome compilers -- done on 02/28/2011
  boost::mpl::for_each<Sequence, identity<> >(f);
}

}}

#endif // BOOST_MPL_FOR_EACH_HPP_INCLUDED

/* for_each.hpp
jjSBcOtGAkhi+ZrBdJ7HoXFHmCA4jgTEJoKyJh5K+/OtA4WX9WlgFM3wZgJzVRpgTP5VP95cL4DgJRlAEMIKEHyYn34lCHY0IZ8Aunqi3LQBLYdXqi/aCcJxu1aelv6b6gepfUskHu3H6YcofGsv/piGC6e1/l2g4L3XJwm848YeKLzrNbyHS5PAe7PgQOH10vBWJ2vv1KsPFN4LJKKqmzE6YUx2d+CJHNDrije9qz1AT4CSASgrBArKpPC/TFhJR8etpKNtK2nq8Sf8cfmFUHCe8eiFjvOdnPCdkgiVc4SI8NZzNRHeRO3Sga1bzCsuWzaP8jEL5MSiID8Z75JVOWWJjsxlO+s5ua6qMyEC2cH2E7BYHvAdh+kPnAls0uvEdvsX/dWf1hP0V4j6Tm+549eakByMHBvOm0uY2PfkT8nItG+vnVBf/zbq66/ry46vr+yg68tto75cXZ83vr7dmWnWJ+vnCyTCCmeu6gXCC5LPGZ9tzD3KdKimkcN1CTVDmf1SPl5kg3Q8K/l01CHK1xzzpOfWYo9HcJqeCX49E0gM6giBKdbVPiEGY0IAeOrz3/PVfM7BPHznfId3ux929tOC7XIJE95DGl4l4N2ZDJ53dPrwLlfwwtyVADksGcjf9nOCTD3/NX5yr89HxUmAfe2KdPCjuGa4Ww7H4Xr3EjkKIuILbhBVOjcDWeeJrVZUY2OHW1Nlgn0F5eIqnrByyC/N/UdBHNcsSHv/4Qf9j5b1pJ6DvWwudYSOwFrsge+zPSTMT0+1h4RpB/71gG8JpW4tlGaCX+ouPZ8q9FTnwqHZJpT2Pw7D6Yz1KbGbE+OCHkjYHsIvYdZVmLPu+ES2I51boYOPpI7/dZ4pD2HAxqOabKmGTGL+Bu8MYRmFo7xV3fR9B+omqQabIDvylDhBFjvcY7VzfT2v+LX9ddQiie5Vz6tO64U6DBOYjMgGn4jAAOVl7/BWs6NX8NMPREC75hy9Np4F7POBaHN0lF/dplsakO0kf3dHPfpiJ+/hNmhy+L9ekNR/FSI49wMyvSfbF8KGLUbWdOM3uYcyvINaiSn2lHgitj977fxvZFy889kBB4fpAUWv1lj1HpGmrsPSf48EvTjux24yo1sNANS/iq+X1GMi8ti5dq/cT1Ekx7yR7D19Quc9xabAOSk8kNZLkleuYf3f2bJfZlM+KPI/vkBruCP9kBFXfXrKjKbzHDJVj8hpAmck4JwhcGIVXJ8+roL0U3o8OlxdMDkvm9kHcO83FkMKzV9fMYNsgfIeqTuGAyBSO6p4vpFhqJIV6qDmpWhW4Mu6yN2Kfz8iPv59eRv08FbgAOhhDOxfRtj15zYi2Ds6GRHcHLATQQxEkOua18FGCnANM61yP/VzAdhGqtsTAOfS4VpVkofaxuJdndn/Js9e5nZlMsAgGReA/WuW4/YEpemPHWUGokUA2tzqsaxBLs+p8y4WdIb3lnrUuR/HTMiuKVPzKIDM2VHvYiRl1w6rcc2H7ikz9iAdiIja92sjvwS1r+lPeN/wpP4NaxznGwF1d6V5dOGaoP2RT3DYSNeNt+w4eKsRm6NOMI3iY60D9JwIXcgp8+06mm+bzkBfW5azEpQ442LUoT0DtG20JPaWiigRx7Grh5m20SCcn+lzko++qt0fVZsioga+v9xxcuKJXY9T2cZO2oDWE7sMhFRwqgyozY4WyvpeHujykfOMOkGN+mEVJhKOVm86H81CjixEXV8V9REWTMPIUONy6vvLR3wJA98GPUyE/qOwXXoAGWBWfVZqkYEeHVjNjrPI4O8uOxmc28NOBrnhFUIG04gMnjhdk8ErlNM0jmi5yEkGMOgpUSGpe47TZACq+ME=
*/