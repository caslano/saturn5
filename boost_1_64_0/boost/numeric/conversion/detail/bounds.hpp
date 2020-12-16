//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_BOUNDS_DETAIL_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_BOUNDS_DETAIL_FLC_12NOV2002_HPP

#include "boost/limits.hpp"
#include "boost/config.hpp"
#include "boost/mpl/if.hpp"

namespace boost { namespace numeric { namespace boundsdetail
{
  template<class N>
  class Integral
  {
      typedef std::numeric_limits<N> limits ;

    public :
    
      static N lowest  () { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N smallest() { return static_cast<N>(1); }
  } ;

  template<class N>
  class Float
  {
      typedef std::numeric_limits<N> limits ;

    public :
    
      static N lowest  () { return static_cast<N>(-limits::max BOOST_PREVENT_MACRO_SUBSTITUTION ()) ; }
      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }
      static N smallest() { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }
  } ;

  template<class N>
  struct get_impl
  {
    typedef mpl::bool_< ::std::numeric_limits<N>::is_integer > is_int ;

    typedef Integral<N> impl_int   ;
    typedef Float   <N> impl_float ;

    typedef typename mpl::if_<is_int,impl_int,impl_float>::type type ;
  } ;

} } } // namespace boost::numeric::boundsdetail.

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////

/* bounds.hpp
jO0XZawL5JnhwdxtnLOdn0r0K8U6D5PPe1p4L/d8epiMUeL/3vbkGqDcM+Hyw/ecD8o9r0zqaMoaCbMXls+lbyDXVJgc64yrqS2YnzDZ92cOFbjGxSrP07cK19ZbpZ0dza+sYA4q1zUb164KzwFKO0OyFtZhnilWpsvr48wlmIUc66KDTViXlP493BGygXmm3LNF7VrezCWYlbCZe8Of8J2/0r/eo8KZSxcUKzOgkrY2KtZk4r99mYPK8+J6NQ9hDirXxUc+YvyeKteFrAh9zD2Y0nfXhbO59uua5LQv3ouCuK4oVndixGCemRWbeDHTjjkIMxPmUqRQJZ4pYTJGbgs/x3CtagIX9nyw7zPWM+WevavvXstcgpkLM77xuAfrNUyO2eqnM6OZZ0ofFruac8zGK/dc6z+Be6kk5bo55/a4MAeV572vmfqA+wnRvyr4YHrGD632wEbq/q4dlf/MsWFntXcJkbwnDOM0rAWvGwizEbZrx4x/2QeYnbCig1+2YU2GOQkr9cD8OecDzEqY98YaU1l3YWbCoi9PSefeBmYt7N7wNdp3+ko7zxXpnMx9j3LdtA15tH2yYtYHejRi3VWs4vVNEaytuIODsCaF/Wczd2H2wrqOqRHAc4diY/vEM7ahMPm8XSOMWJfCYBbC6ne1Xcb6qdgT41l1uS+HyRg19awzhe8EYLbCnppt38CcUKz2t1+RXKeVdvZusoE5mARzFVY31xVn7mlhzsK+lzP/xdjCzGX/muXPyzoIcxM22rNmPtYlxUYcjghhjJAdPsKe7z59jnGAyf5FnPeezzjA5JhtXT42i3tamKmwoY4t3jMOyj0X9Fm3mXspmMzrAQfHbWQcYMbCXkcH+bMuwUyEtb9c+DvXP6WdfbxfVmLtgemF/Ttl/hPGSLnnjYfb4nkWVdrimcfVgXMaJuM+WOfah+sfLNhglfDBuovfOdYZMBdhZuvy8h3EG5iTvM562OT/7M9PopkJa/ZgLd/b6GGmwmZNXcm1ygVmKWxp3nvTubdRrNC2bczPYMV+xTeJY07A7IRdy5W6jjmhXNeo6pStnH8wa2ElxrnzvBILcxUWsV93hfGDOQtzNT9RgDGCmQi78U+Zd4wRTI71Py1DfrDuwvyF/ag7wI4xgnkKa9XqynrWQaUPuYs7cm6atsh53WNbi0yu07C8ws5fK1CE5yOYjbCG7kZ7OC4wOdYp+0eHcS2GeQv77bFH+5khmOz74ZIfX/BdJSxQ2LvfTRiHK7Dcwk41qujB751gXsI2bh23g+8LonQ6R2FbQxs6cS8McxDmbt1lImu5Yh3DDuzneQxmK+z4jtzVWQtgcswqWmxy5DoN0wvLf3k3a+RkmIzfKpNZwcwXpQ/Tn4SHsl7D3IQFbd9clmdt5XnlBtziHLsNk/ELbfOjAddbWD5hd5/7FOd4RufM60qbZpXjvIXJewa7ty3BsYbJPjT/uaISxxpmJezrjkZbmIMwP2EeOwNiuP7BfIR5N0vU5hjMQlghmxb8bncZzFPYgh3V+J4hDeYubPyv+ikcM5ivMPvOkTb/ma5lzrh/e7qS67seJses1bRDetZBWLDBKuIDx/dLmrJmwWyF+Z3VjWIOwgobrAI+yOXl85NzDGYnzK1Jtf+x7zBTYS3mh/Tj+qBYmaGHOnNuwsyE/a41lrFNhZkL++k4vDbfg8EshJ08m8K+pyn33NJ8dC7mLsxK2LzlfT+yFij3nLB/whHGSGnLkNYu//DsJMa6/J97dm5A82il0xUw/FxlOXywv9/kCoxDK7Yz29xTz0QxP2HBwjp5n3HjHgxWRFjb2EvMs/3iurL4ILlNzF2ut7Agg4UaI87t9lqwXsc=
*/