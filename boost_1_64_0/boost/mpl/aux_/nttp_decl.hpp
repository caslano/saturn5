
#ifndef BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
#define BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/nttp.hpp>

#if defined(BOOST_MPL_CFG_NTTP_BUG)

typedef bool        _mpl_nttp_bool;
typedef int         _mpl_nttp_int;
typedef unsigned    _mpl_nttp_unsigned;
typedef long        _mpl_nttp_long;

#   include <boost/preprocessor/cat.hpp>
#   define BOOST_MPL_AUX_NTTP_DECL(T, x) BOOST_PP_CAT(_mpl_nttp_,T) x /**/

#else

#   define BOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/

#endif

#endif // BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

/* nttp_decl.hpp
XXjY9nPIjmebjx0ftc5+9MJ57aiPdfsvPO/+rfz3QMvH5RqW3RbktCFBvieozLyjMzVr16V9X97zxcEVS+7/xTF9TYTX4Ad1KVlBpPlhq6yeNwp6lr3psEhdZ1b85K3VbGcddY2e+2FyyiNehaKenXscb5tutt3nmOWGl2+yHrXcNLGRxuN+kys7eP6apTWTHZ9L87ddOyXyP85L2R+d8fVNowqFz7zmjDu4WpDeKirCJv1t8N3Izq8PtPz912tlFJVnjX31rdXwSZ8vvC+8dHzk56MFXyKcb05+m57f0eHpvMh7jWpIe+0+/CL03e6w6Wd5obP9Rp3IPFCx5/f7/s7C9Idnd/Xr2+zyxNuKwRtPR3rUP/WmyZGP44VLO7c/EV2RFyOkH9ZecVM+9dyw3u/evMvlf8rNT/YMvrjjRDfhnGqZVpfTLibusLD83P1qr/zLN+/tbdixV/nf557r2bui4v7tW9m7xkmWNbQIy+n6fu6vk/5yV9JzxLIU/vXcqsOiy1weEiPd0W2mz8qXOyOnSF/lbL2YLH/n9Mg/qNVS58Et0puqx6eM9/wwy5+/5WVCt4dthItsvezLzvXzyQhQqEUO5geOiI9PLVoyYaRSElR5uvWwZreb1Nqh2jlzQ7XLq9tm1rIZKZq5ecmKJp225vW5t6yP73nfyvmvr04MPXIt8OO9N0q/2GqPK/9ifnR17YgxarFP0dhe1eYPPnJqEj87TnXm1I43eQMUSYPm0KtTFvteuzMom+dycH1/l9VPXnsF1ldV7W/btJbq3ZvveTUDPe2mOV0OdP26O8rz18oNyiRmreyvuFTx+tj6s+OrDemWqNj2JGx8kLnPxNp+HUZs+fYl4fuuYfv5Dab1ii/a0Ditk5hnb97k/Vv3di3rrrOc0mVrj5zCi5EaYZsCUfcy89Zd7ltr88U675LuvYsZNzqeln06fTYs+/2kRtGCLm8+vKsYN2pJaurGTiH2MY/6r3yWcHuU86YheQ7RrdZXbDm+8be71aLm725ID1n/dp7dqUv763yPburTMz677LJXi2S3Ptb23/O8ejle84zfnfdW/Vb/4Vjz3pP8w63ieyaH56/7njCwk2/INuHNzrEXCh+9+G3Gp3e3YzY1jfJbGfDLKLc7hcJr83Z6R/Oy+j97uimkp+sg82X7n91ZXvBb75dj90x4FpGxJr1m6+yBN13fz3jjvm3yZIn/K7d9rWrk5B8p+xa3zt5b+Fi4su3dBoEnL59IivJe7lfjr1VWXux6/FuXalWWR1ZPfex4bVyq0m+deRfJpHULtlIOs/pE8iLsF94eZPnmWNsXic1ca1w8W+VpxTN55X5/r6LXnU2u0fFr2poyc/LvDnl46ny2pu1qx1Z+PqMCPC/sys+1yoxdW6O18OrzzGVpZ675h1hGBfKWtOvfcc8+6eAIq6anro7MnKRWPg4/Wr7w2qLXLabfCOg/bfqFl3dCRmdELlguPPb4Ts3JWwPsG4yZvSEku/mc/fU82tzt6m1TtvXjRYrchy+unpr5YUts/ZSVqzxzzZckF5RbN3fNyYG/9Fuzo3Z9p1T5otApo6OVDttPe4zLCenZcvK3KQ/222VNCd+5v1n9M37KTXYT56xfL7u2L6Tws7Iw8WvUo4gW68sfaNL810e1lj+soEnx/zJSeGzh/nvTU3nWy+OTzo/KadQ3P2hh3YeTT9nPe7bM7ev+5okZsb4C8YIJdvXbHDt0PLvXAccN08ODDg982zvbov6d/YpZefP6HQ3MyX3dcOGAc16poyqc+v4XxYiXU66vK3vAV+3UoE7RhAY2LRpNfvxgbpqb2+sjyVW3apq0uqe2k/tdWf9oMt/mTe0=
*/