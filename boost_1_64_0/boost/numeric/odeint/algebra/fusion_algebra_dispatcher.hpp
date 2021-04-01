/*
  [auto_generated]
  boost/numeric/odeint/algebra/fusion_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/numeric/odeint/algebra/fusion_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>



namespace boost {
namespace numeric {
namespace odeint {

// specialization for fusion sequences
template< class FusionSequence >
struct algebra_dispatcher_sfinae< FusionSequence ,
                           typename boost::enable_if<
                               typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef fusion_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

/* fusion_algebra_dispatcher.hpp
ekweCisH6He+EPKURwEM3+KkFJsKfbDF3947zrXfqwIUcUWMp3eBih8gqy809A6sGun5UOlYWCzBuJTVE+gJwcnSuCHr4sOYVnY+d/hvS34M+Vdre14WlwOm5B4KOL/rJkIW1/2tJhtZiNN8r39f7tr3pflo7zLt8j1kXmvi5HkTkwPLh0cjYpPIEKsGZ8yYGUUqMOlWqfjKKf/suBn7G8VypErqsng277n5/vFFC+fMbkIl+08bJheBFn6IyPjKeHDW5zF4BtPTjBi8r0k8GkUJAU2B3nRdNAGHEHTd33HRYQGOU7DfOtBlj22gCpsB7KdH7fyxL4cjvL4F5GTez0V9pGTmIAUfmiarX1tWkGXwH/K/Smst6KryWFys1B7WApH8GxfSFJnf3yTF8QQyUeGHZ6Ah+58f9ucVhOZeNlNJsBtD4knz6Fq/y/SFCN3F09VIdN4P3pKgBc+7BfZZmVYoiViemg1s45mw28WJ/nBzsr2DVOY2VpCP2h0uMDHJKkICbWgIRdpxs2C0SRtjThI5Kpr4l8JbPjVD7usDJqPoOdiwGS9YuUmK/w==
*/