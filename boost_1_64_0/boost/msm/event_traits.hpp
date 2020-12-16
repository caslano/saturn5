// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_EVENT_TRAITS_H
#define BOOST_MSM_EVENT_TRAITS_H

#include <boost/any.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace msm
{

template< typename Event > 
struct is_kleene_event
{
  // default: no event is a kleene event (kleene: matches any event in a transitions)
  typedef ::boost::mpl::false_ type;
};

// add this way in this namespace specializations for events which you want to use as kleene
// requirement: a copy-constructor matching the events which will be converted to this kleene
template<> 
struct is_kleene_event< boost::any >
{ 
  typedef ::boost::mpl::true_ type;
};

} } // boost::msm
#endif //BOOST_MSM_EVENT_TRAITS_H

/* event_traits.hpp
kSM5fdRqPp4Tg/9qszm0dKHxsUYf3asPR/SxWJblSuzMraFqnHW9XXu8nyE3b+zaduyHB3vfOr+QU7eoz/yGULJs9xXmLGM0t0XMSuaXWXO8MdbdcC+HoL8WzMNHbQ4F57al+/V50fYetL6xWTInVQ6XF0fI80vVdbPYfFF/f1nOiVGX3Mq92rgekHeWKVCierhHcvcfLLb2R94PR5m7vdfl9WQkGnIvWx/KPzM3GUexPv2hDpnGWmNfP4hxt+VKrzKWPqUfcvrM89yMGBlf6avMY0uW2SRWf1vr+ql6GrelZjw+aD93qLjLw/rdXv+5ZR82r8ipPnXuO8425Fnhj2Jp3nKPZd+zsb97dHMIZ4nti/XhGepzofLPk7//Pcj/2Kub8+1uYzyrDUliZNrE5adi3qyb+MUWjMOCeUDulOVNbMD7likVE6H6Ne38gHm4sD2kf9KMlTo+aHzZTpB3BfHN7Nuh38wrefXyetV3JKqX6/eKeXfaPnyzerx7fcj26uNT7YPi5obPJvwWjdhWzc8XJEIl7zjAsskOuf2o2I1uCQXb6NOn1Q1bQ5/PGkrRHT6rNM5dny//XP1857B0mxjo3+RPjfPYAX67YoffRBQn33HqKhlTm/y21O8dGz4ZQnnjDsv6rSp9kbneWG3uv5SXvibuvN7cNaUd94eQfiiE7BZ/18Xo79qjbyu+7xgz/ru+bt0PidEtLSG0uP4WjflfY3PpkXLCPJf8jbz/g+XNRZXvqdNF2vYNbXKv9zAkvufI6Qlz2Ig54pX66zvmxlvl1+3a6bt/QTyT71rvmpq59g3adYL8fl4sVGw7WKe+VR4cr11xY+wv2xznGa8nOW56ccxxTMznj7bxA9t6lrrZ15Rf5HVzV93rWWWVzlXuXVHfDzEWUptC6RFz3Fo590/bvU5/2Q+m/7ghVDrksHtv9L1fHY8zl75Kn1xiDv+qsg40NnrsG76zyVgxvhbljrqUo8r90daQKciTYfvDpyt7q9gY9+ES9yqf0b+z+iJuvF5k3bDO3+J2sVw+NGbuNA2bm7L5eOhWj752c/ODG0NB3JL+7rpzewgb5cmkebPmWENOlpq5eJRxcoDx/d14yPwu6lzcHHeasm5V74s2ut5tnphVxy/Yh1xjHr5Jzl9gHjBnVA9UrvXTVfcmeUwO/Nv/83ao183a/2H73ql46Gv+PndE+ybEaNI4qyj/MfvMH3nt2XK7YX/5SfuO5r3+DnWc8RLj/pGNoft++7sr9bd9kPunhKx7+GUXxO9fxv5Oc+FblP0p9e+Qy/4nttyi71v193V8xuu7lCPXSh+0/1GHygNef0QuhY2hWlLXFv3WYz+jnPARx1Mx9549XZ+/1rGk+b16imPlPfbPi3L9bHP+VepcNTbNp7ErHdNU1OUpjr2mjP+FA/WZmMiZrHXr3it/y/7Vvq5c0AZlFZ6urxb15/vMC8pL3ubv8+170+bX4JjqbPU5xu+5dcuhD5jnvmofdOhm43eHa1Ri/2Zl3u+4pPkbs/KistlYeanjnVfEQl0bq/vFaXl9yNk3lqe3i6NtaVvaPJM933y4bnOIXRE1rsx38qPbnBnuFp/PGm8tcvlZxsxRYnl687tFctmYiN2t3+VadV4bvJf5j7ofsy6kK091bGz+s9/ObNzqt96sf4v9yu/0qfW66lHHcsbsaebmD5nDEmJxvrz6i/jJ//Ck/eIftK1FzBbVtXnPpIYybxaL+4zTlxivpxqfv9EHO42HKds+0/7RMU7pVHP9+6zXnCtrW01MfFEdLrdvv9LYO9kYeY963r7OsbH97mPm2A599AzHJJ53XWDszunfk82lzXE+Lz8rLX6vR048Io4=
*/