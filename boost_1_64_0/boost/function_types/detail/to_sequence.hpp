
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/is_callable_builtin.hpp>

namespace boost { namespace function_types { namespace detail {

// wrap first arguments in components, if callable builtin type
template<typename T>
struct to_sequence
{
  typedef typename
   mpl::eval_if
   < is_callable_builtin<T>
   , to_sequence< components<T> >
   , mpl::identity< T >
   >::type
  type;
};

// reduce template instantiations, if possible
template<typename T, typename U>
struct to_sequence< components<T,U> > 
{
  typedef typename components<T,U>::types type;
};

} } } // namespace ::boost::function_types::detail

#endif


/* to_sequence.hpp
xUvdMI5af2bDqTNsaSVBMu8yOp0OJRet/Vh2PSw2anx5jy6jxL4RvzhvOs2ayu2F1WRbnF+F7twkNj6muOGxtYY0wL2gKNJSYuKh5lSpRnOO+OtyKUcCJUiki9mmePONrNV2lqfvMXAfGzzAizPX8mSgy12iu4pqg6zkzn7x+wd7xwEeRbGeS4IUFYIgRUWWTpBAcikk9FQSEpLAhSpyXNlLltzdHrd3KSjNghSfoKLCQ6WIUgSMDRFUEBuiKD5RQRGxUcRCU0CQvNmdf29vJ3vJXULe9977+D9xMn+bf/75p+7ezozYnT+9YdO1S46aUv7PATsiJs43vtx7+s0HlvyRnj12WXpx2+ffaNtjsK3347+5l046233ouwWv6YZsbGxKGOias8q9c+jcNxeXLv/UVlCrH/4aOef+e7b3faxk5ke6rHNNn9k74JUPtsx7Ytimbfyrtz6UZG1Kj0ex6/p8H7b80+sX3dxy8NLGkSf/ddN7m0Mdjz7q/MW3r00s6fbjE9dbrKt/WnJdcv9VbYoPGH5btfXod9nlqacPlXGfHP9g3g73Ro7PCh/Oej7twG3+ZVrRbVt6NRl0+nTlvdOPu148dKO/buMLa7oenJUyJ2v/N6rxiLb/Ha44PeHQS+XvbJ64bvytvcZaGv2zT6j2d75h0M7kCY12r0kdtOmjD4ZNXrPP3K3kc67N9Kiy2ei9CR1WlvdrM+4fH9+2YPhvD3Ze2O6xpHUtOluEfnE52Qc3T3HsuvD4/N2lWevSKqv8YJp5b+yuIamL/xz6Syst+28F+38c8PLkk1uu27Gj0lvx4OJZk8/rb54+s0oB8vcsJAL5u0bqpRKdfcDBU/NS9n5R+HBr7+6p677u++L0Dv0qTPftXNy7WYu/Hht4cO1s+0dxW6y3/Xqh0dufjRs7aEiPi28MGPja+uennzj24/Fmd2xyDi3cbbh2RWbhS8XtPu5cknzpwzvDTm2iyn1q0j+X37Fo6sVPR3Wfu+jJawPV79jLujYRTQ3huwfMWrrktsPLP/znkTb1qZ9p5nPF+rH2bZc/v37pya5PDPlt3Gs5K8IfmHYs94F7+vZOer7pgft7uEYyH3TaNump7lFTBh48fWbs2BU//33/lpijt+u6/fj1z83fZxwrLukOVM7WL39l9CHn2cldplct+HErlCuX+MmaY+PTyva13pHU6fVxjCVQ/aYLnjYLL8dP3dzsvtI5Kxd7P9u+qqo+9es2ttFfvWJshS+c/TD8izUFT1/XTRe2b8n9bQ9svfE5x+Ci4k0Pttv28CefoImL/7nqvQNZhr1HJm87X/jCBwXG4xPaND4yb2Hydde83mH0bRs78wP4T35c4Jx979Ln2/3wq/0MVe7jd5xIeenZRncNTOuUOYodSdePkfvXk4lN5hyNeGSKrfy7Vk92f3X28hmLqjAAGWnNg7XQL014L2H/+v6PHH3pxBujS5fMeZ3tcE3lR4bKPwd8PHBwj39Nzilp++np73qnDjv/+pGfLKuHni4Lnz47+kTcirMrkzP2L9n5WP4Pqd9fvmnmsgePnhh+V4un2tz2cdzYkthJH3+4eWhxv+0j/4DyURXA60f+2rim7VP3nnlt985Llm4jtfpjc9ngP64Ne9D3BmRUhLt8yAtf39Vru/mHSbZZpW9uZBaocnPZp85vjUhu89uheS1dt3VumuVOXjph0tGS0Rd2nlyy9omfnr+/645Vg5u3OOdFIFfa89sNrOldrfIjEIYeY1e29JVvaLNj0rX71OWbeuzMbXRmfrP1f05sfrL3yEOnZt/xyq+eS2/n3vdl05ynm71y7OGXv7M+uffhOWkb92T+MbdPv2GHzjgfdT4=
*/