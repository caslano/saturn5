/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910

#include <string>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_continuous
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, 
            value = mpl::not_<is_discrete<Type> >::value);
    };

}} // namespace boost icl

#endif



/* is_continuous.hpp
cVjGWlWGnD4WGUBPl4FRgU6U78GeMSaBZh4ipU3a6VljpDFKWIPRvufy2ravAdNVrtx4nyMxm+M2Jni8OIYJbqgPnQLb+LpU9KEh7wx9rUbrk3RWxhdMf8vViqwvEcfmOdZFRcqGzUshajQBc9qeM+1Z2nul8EBCHrkGkAPPfyXniuHtsXLFYhpeD6o7ODTRY/GzT2ZAjUVgKk1rNTqtW8fSaxKLYNNNaxjBOzMFZywVAOsbceCpk3xmUulTNQzaqCymhrytKl5dluh76Vvh/GSJmkxeouhwWaqI/dBwvFTi/r6e9YuVyoOH8lyPHp4zqdCQb4drXKPjjDGdWcF+fbXGpCqtZFaXCe1OaEw6nxRE8lscx7FgoUWJM1TiDGfao2OPmYjVaZFxoe3Ac0+hWC/VqtUS0RXgRYyO103lbKnjnsPKHe/ojmzCBA4lCbBfAOaMdXYTlv8jHZ3hcGhDp9MqAmkP4WMkGWFdv4T9vmk4lTZGjI7ONTafQXyGB9RZ2Y8xpzQ3oHbmmAaTsnw2x7CNmXFIA1KXQRDXLyJ5IVOn5seGE9BJS2X1fCr0TolIKWcqOtbdWcmYZKo/nohKRfoUh3lQWczTtYF5qDGFJ9IV7lwfAorp0aAefShH+iDxEHQUrxi3eAqry/CMJMY3mZaS/2csRPx1rhiRgaR82yc50isypHjIm6ZN8T5AOS8oom/dGUzEsoY1WawlRCSyZFjV61MkkT9E+KXU2BGjPgHTGkI/wndKBdnmcHwx0+jp+KIPqfhxfHU7DRtgf26VMhuK7JnGbp3fy6MmhH19MtzqefVNl3VXdGCW+oiGFN6L0PbotJ7fEQnNzhtTeaVc3N6z8cV904QOXIRv2ILjORTGfxo/ftzHkPjcZLT7yOC+iIzMLmOkP+aXB7bzGzRdn0mPTDq45rlxdZ5Z23OCj8ZiH0RO6+n8s7WxTjtrm/J5qzgNiADqvLO2K42+6Gt8zHE23u25gl5MnqPBbelu+lxURo+PjAK80WZl3JTZ7EXrAHK0atDrnJvN30b6trb3fYyymNFWaH6y/LVAfkNmA/pcMy/G2zMLL5zw5fJEhbesLUTrtTVzyI9PFQUqVoxP2fnwXrS1lTypKz73c0IQzCFfPlrAeaMpGm/8+rR/Vs8DkRuz0PfAMa7bc/+xLjSq2/AxQPzoNJm8H+Rr03I53V6TUH1uEJOZo6FXCctnkynzG0j1ZDaPyzIqezKb88mCZF6l50+EiSxuOVXa3OaXVPJLmGM2JTC3NChfkoqM+eFpg/6c8+BXTG4D/7kH50BazMsK1ha8XNHSZhankU2YTAN8M6eJzytEnlcehsq6SPwP5EYI0URuXaezDqZ1LuZRrEriQyAyLLOIUGY16n6wzWWAzbDA58jeHO+N0BlwTMhgMbGQVuskzNkRH1Avkxmg0+pCSJVvZ+FB8Dn6z/bJ69NJoTQ0Ut0WeXYAfhz6gnLTBOYKLJOcGVvrJbyPTljwyuFQBuzWOPseXDlEZhCd+NDVc/Ukx/tujKiEZngMdtDsqU6psjxSw6Ut7LWKqOS4WaKt973Exy4HKXtWT4F+DZ+j+V7Zo1pSHs+U0HPeKzh5UwKF4HEsJI3qLcLpoFeuJ5/ZPMn0DUgOn6f4f04g5XA2ChymqXAkLLWo592hE+naGYliKj7UVIaUVcIHN6g7t9LwkTjcm6Y34uv5T6UGDIfHYCaxeY2ikw62ruWuA8k/Blxe8ru3UnCjYXGCD07yWjmY3KG38GoL5hwpep3CITDvY233jooottR5dKebQzAPmX289cTw/M+pouqeCj2obFOyNqBvLodzuYlaFvlj/5jp+DqjJQteDP5OR5l66f4=
*/