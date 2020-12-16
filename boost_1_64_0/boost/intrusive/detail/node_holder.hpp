/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

template<class Node, class Tag, unsigned int>
struct node_holder
   :  public Node
{};

}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_HOLDER_HPP

/* node_holder.hpp
nEidudwngsaeBvgVvISLxe3ELSJ++mQ5L4ZxPIkaPJ/Yre6Jq3XnfOtZsqhy8ZKKymLX/ZWQD/ut0vW5XuUlLzcmO9+SnH0gu8vxF/m+zFsqzu253kxzUkfn+UOepFO1jQwUmS2enpzf23AB356M70U9Re5XnkHU7KWcpftg8H3LquyVIpfNDMczguYY636D1nHin8r5b42/q37X6AaXJVMueAnsoeEnwZv1eM9UGOG8+H2SjqeY26X4n8Mf/DxszjFNNb+PGOdSn4ddvzMmQs6N8T1F7YUcw31k3O2LhLMncezsjrjb8whvr6LzLVb46S/UXnjzO/vePC11RewdWXf0OXb71BwruyBNtafSVDsiTbV38p/av+ZI7IVsMeyF1Km9EL55Or8/NX7/zfgdbX1Dkr0l6Dvrf8t9fgN8Cn+G8Zt7hti3uA83yfidhkwN5aEZetLrf8t334Pwr7hE/f0+ejro76XIfQaznfU8AHdQ1xuN1nL14WZgsS+M071Y2upeLCfoHiyD4TA4XPZaUVsYXnSr3uQov97uuMFeUSt7VfSEedBKdy6cCYvVtsaFsBzOg0tgCbwKXgRvgwtgjdpSeRguUlsmi+FLsALuh5XwY4gOyddytW1yGewMr4B94Ap4JrwS5sGrYDlcBa+G18Efw9XwNng9vB+ugRvUBsomeCN8Bt4Mt8My+Ge4Dr4Jb9U9AG6Dn8M74GH1fwvXw5ZRhGt+85058Ixh6PmJxeXo+cnSPXdGwnZwFEyBo2E6HANPhuNgfzgeDlD/YPVrO9C55dwwXNrBAbXR8VfYyToOu8BDUOzfwD66N02Whlt665w508T1+vUeh9utenNJPwHO1vznwSGwEJ4Fi+AYOF/3rlkAq2EpvB0uhDWwHFo6K+Df4PcgbdKzHE6GV8D5sBpeCVfAq+BKeCu8Cm6GP4BPwlXwOXgd3AZXw5fg9bAOroEfwR96jT0xsupth2wI2vvhKUcOF6FcpiFXExUod4a5J0aEctmGXFVQuvcZcvkRypUbctneQLlMQ646Qrm1hlxdkFyBIVcTodymCOVqI5Arx+1SuQ/1+ojHFalcryh/P9kbtoT9YDLsD3vCIfBceCrcDs+Ev4VZcCc8A+7X8A80XG0a6XwOrhVN17RpNErTHQ1bwbEwHo6DXeF42B1Ohz3gJDgUToZT4RQ4TY9Ph9PgTPV/pmmWa/rDNP0YS4+m/47eH96FPvg+lPd27W8+1P7mEzgQfgyHqh/9ErlW9b+i+lvjKlX/LC1PHjwN5sORsByOggWa37kwHxbCO2ARvAteBB+AC+Av4UKt9zK4S/Xo3mY61sxzpObD3Nvs17oH1W/gSbr3Ty/1T1F/tvpzLF0wF/4BzrHKBi9QfzHcDSt0758VuvfPDbr3zzq4D96v4Vvge/AF+D7cCT+Au3UPoAN6/HM9/g89/hnc44wtkiftf9Nw6JC/H3n9/fiN8CR4k/a/P4aT4K3wfHgHLIR3wnJYA6vgPdr/PgAfgg/Cn8GH4YvwEd2T7VH4Dtyke4Q9DjuSn4dgD/gz2Bc+CUfDLXAWfApeDZ+Dt8Fa+BP4C20/MV4dN9FxsIPwRNxhLd/fkOsHP4cj4JdwLPwHHA+/gTLZMMp/HrzwehgL11u64N2wM3wEpsPnYBdtR13hH2A3eAD64OewBfwatoL/hDEwzevX2w3GwV6wNcyEbeBg2BaOgUlwJkyG5TAFXq3+O2EafAJ2hFvhCdqOV9nf4OEX2o7bGPsvfqX368NwkLR16kH3hpsOW8AC2FLvt7G6N1wcvAnGwwdVzv/e4K+PdvAlmAD/oH7tP/SbLn2NS/9RSb69cCnsBL8Hu8EqOAJeAsc=
*/