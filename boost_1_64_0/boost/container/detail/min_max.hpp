//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP
#define BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

/* min_max.hpp
P5iHwMLI+Hoq75XJh0WR2TOrsqW/GRZL5s1sTbkva2GJZLyGM5cOvIQZhVwaN5hghGWQyZgNS0h+BMsk4+t57uIUGSyPzJWZU86lcjBZW8v+PYipmw5Tk/EaumeVngoLI+N5+lpPOQ6LJJMzy80yb4XFCtZ//RsvmE7IJWfFh4MwoxCn93sbBMsg47W36iTVhWWT8doPDou5AjML83VYbR4HU7azjOtd9s1AWBAZny/ulWk2LIzMg9k/yW/UsEgy3vctEU82wmLJvJj5/d5jCSxRiOteyVAbZhRymdq5YR4sQzDXA9WawrKF+rYt29QfZiZzZNbsZDk1TNbesg+tJ6xoBFORlWE25m5aW5iGzIWZd+Oc7rBwMl57j1WrU2FaMl57auP9KbAEIS67+90OMIOQS58P8Q9hGWS8R4unZFyEZZMpmV1fndYTJnWwXM+FG1KfwpRknsxq9AobAQshUzD7pL5jDQsnUzG7eH+SCyyWjNdX3/p2VVgiGc/z992jrsBSyPyY/We/1geWLdTwY80mH2FmMt7bHSa3KTB5R8tjwYVf/94CCyLja5103qsrLJyM197t+afDsCgy3ttlTtPUsPiOwnns7MCaMD2ZM7Mhm5x0MKMwpnxViyRYBhnv++vFqR1g2WS89mejD2yFmcl8mIVdT18AU4Zb7kcPVsVdhQWR8biu6hdyWDhZWWYO9f+YD4sl47ncsz3dHaYj47Uf7ZRkgOmFOOf6jTrBUoQ83QzqDJiJjPdIPuuADyyXrByzvGaLVDB5J8v17HTyRguYmoz3L9ZzZwdYGBnv0eiYO7/BIsk8mVVaor8GiyerwuztLPdFMKOQy5OYqjmwDCGXo41rLIDlkvE1+09z1T2Y1Nly39w5wXQepibj8+0acfYVTENWiVmQtsFjmJYskNnJnm9GwgxkfF1GvelXGpZGVpZZ/Zsfr8NyyXyZNZ/9hw1M1sXyWJAU5nEAFkTG55NsTsfAwsi8mV3/2H8DLIqM1x5f8++KsHgyF2ZNmiYfxn2qjuy3b++yetF9aqs02TBYRvfic06h2d785ADLJCvPbO9VP1eY1IOuaZmNzv9vDZicjMddeOZ7ARYixPk83fYrLIxMxSwnPXgETEvG87zePPgTLJ5MwWyI1TMtLJHMntmtNMflMANZPWbW4e9fw3LJHJj9t22aI8xM5sKsRrNPq2GyCLpWZJYqX3YXpiRzYxa6MHsqLIiM55n2IGkXTENWh1njDlffw+KFOGP5DRJMR1aFmdvXta1gaWRyZtMH/lQFlknmyWs/eO4jzEzmzMzrsLcJJu9pKw0vtPBCq+jkfQGmI+NrlrjqQQZMT9aSxdXb7/8UZibjfa+7aG4ATNbLVqrMrJ963jJYCJkTs+3Z0x/BwsiqM9Nu/hgCiydTMNvn4NEalkjmwMx96ck9MAMZX5fFMufLsBQyL2a9dbLGsEwyN2YJO1V7YXnCmBkLx3aDSb0t13N7d40fTE7mzuxiltQbpibzYHaq+wBnmIaM1xf/5HgbWDiZJzPVzA+NYVphvoM12ufCEsjkzGrb70iD6YW45YNGboClCCb/e2YNmEmo/WvIgvWwbDLed++Lu/rB8oTale/anYDJ+lhajzMfGsJUZHzMAQ5DxsCCyJTMdn51uAgLJ/Pmvf3l5RyYloz39tK6GmNh8WQKZpuymgfAEsl8mJV/2n88LIWsDLOF0W/KwzKFXIaM8FfBzGS8t+NaXxsCU/a17MPcZvI4WBAZj8u3Gf8IFk7mx+zgj9m5sFgyFbO2yw41hunJeO3e7fuMg6WQ8R6NujWhK8xEJmf2JfLfbSKXjNeeGmVfDSbrZ7n/qTZfzIGpyKoxW3Q=
*/