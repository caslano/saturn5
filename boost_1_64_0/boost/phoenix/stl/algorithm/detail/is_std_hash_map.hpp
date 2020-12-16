// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_hash_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_MAP_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_map
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multimap
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_map< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_map<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multimap< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multimap<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_map.hpp
Pjn1L1jeZ1EqOdW4vLfqbL+8R9rkkZ2Xk+ttmzYv7zISQw4lna3r0X8p88iSg2z3eZmD/XJeud6sE2iz7dPFXC/SB5ly8vX4sV1e7jEYj0fulzxWSPtdqu47GPPIc7LqTqlV/ed9SHzLeWv9Mj6+q7vgIamDg7KPm9DLGDvHoayXWL5ZRSp9TmpaptftRM7ja/u55pHpl52zktdEyWs8QwV5xfTW8po6aurUsZMmuo61ZyTm5LK+XOCoTrsJkpxKWTCl49KWn/B68o7Ryn5H3jFqPN4de5V7hCzi2j3xZylQWplfYlKSw+lNPyjPqjG0jQ8kTguJEyrPJKrQxUlO7hWfmuXdcmt4d6jMD2Ucds9dyu8m7x2S9jmK4THlOQh91Bx8v+5S8qjWdZcxrng8P950PP+LbtZ+djXlnLr82BrPcV/M5H0dGc7/RMi7DyTW0wy7iVWkxarZ9Z0p8h5OfVurkJh15PkLtZC2xssE1JjuKfMmjlbv1GvHq931+mGw+/MY+dwpxP05ufL/jceDu1uvOz2nrN/6q3n5fs2p5Ge7fS/x2Y8wHQeSeRGjxZdtelnle7PtmCLx9fNhTA/7Zd6pi5eVmcleafXjyHQapuuCxPmP1OtPDOep12J9HOcS3UaXd/WaW1mvTCeD+domaRdn+xvbxRVRWrsw5Jva03Ttr8yH8ig1X9+v+9XPhx4Sr6CXvG+wLvHEbcQLH6CLl51+yfd7q9f4Fg+inO5zHJ/Va34D+Lf5etxvr9G+064dvY3vzNfeXsd35utnr6z8Tiv7Ew9tMF8/+y7fma+LvZ3vzNe2Oiq/08oGVH6n5VJB3RiuO+W7z7TvBrg+H9Q+R7k+79Q+93d9Xqt9vprPxNY+93N9vkH73PeS/bs317VeMF3XOknmz0+hxnYY2tt8Xav0R0PUduH7Na3yfmSvro9U108lktd8eTd1Ck4irwR9XnI9qzfHXi3rcLmXIjkrgzdEV+b1M7EIYFmvj+ljuqZU6isyWs3L9+tJfakvNa/wvu4R9pB+NoLhAnkVmPLKTc9JZOvHq/tPzM9jDGfIy0mc58Bg3TW57qOLWdlau9Rfqyvfhcr2opxOcH3XCvMYktliNLeDszJdx6S+j6jbjLrpyopPTcxM5p6gBY5q9F/6abK+l1t5dlyHvsRjuJLvJg2Tfk2ecVfMyFnMlKLa8+AChhnX/Uvk8/cBxj64uJ87ke1yvUcR/ieUaRlWOS2cA6jGNNQPHH4tZTw9t1Ge19ckUJ4pKbnfzv/n695Fzu+VaTa8DzzNVP9drrZep9wzkHY1Ws3Zt2uUJddLXqM8XPKI6i/nZqR9T2LormxPj6nMI9+ZxZliNh65k4u9m1z2PxO9OcYjOVW9X0Mb1bdv+g/64rmOdLV9y+/S5XeMi/Yt1zPIb8LlN075TTDfdZA6YKdROxqktKUZY9xt6ddQY1t6QeqjrazPW6Oy/V6g1Yd312vLtNtu0/hdp23TGLbrY6PcIxov82Qcw0XydI7XclCu99VfcOHw5rq5FFN/2CSgst9oos4T5hHVaGizpZJXY8mrEcPv5FVmykvpEH3pBw3XsA9w/3CLxNvAsIf/KbeJFZ+Yx5WDyuHHSz/70VPfezfjzlD2zOS7ALxH+S7HuSCt1qXXX7MGuoPsl3xLGP7kt8UTzPnKysKHZTpIW35s1hP1PKwn6lnXE8xv63qinqwn7KfVeA2gTGs/aQd9pH0WTTRMq+4kFP+cl5WbluhDO61Vy+t2mnqN9Zq6WmG0HS0/3+4JkO0Iw3z/WmLNllgzGWoTq8Icy8EhoZyk3JxqxasfOHaS5/WQxJf9A+u57DrEd06yxud4is/LpXZOwBI=
*/