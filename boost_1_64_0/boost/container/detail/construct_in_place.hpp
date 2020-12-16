//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP
#define BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/value_init.hpp>

namespace boost {
namespace container {

//In place construction

template<class Allocator, class T, class InpIt>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T* dest, InpIt source)
{     boost::container::allocator_traits<Allocator>::construct(a, dest, *source);  }

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, value_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest);
}

template <class T, class Difference>
class default_init_construct_iterator;

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, default_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest, default_init);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class Allocator, class T, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, emplace_iterator<U, EF, D> ei)
{
   ei.construct_in_place(a, dest);
}

//Assignment

template<class DstIt, class InpIt>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, InpIt source)
{  *dest = *source;  }

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, value_init_construct_iterator<U, D>)
{
   dtl::value_init<U> val;
   *dest = boost::move(val.get());
}

template <class DstIt, class Difference>
class default_init_construct_iterator;

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, default_init_construct_iterator<U, D>)
{
   U u;
   *dest = boost::move(u);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class DstIt, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, emplace_iterator<U, EF, D> ei)
{
   ei.assign_in_place(dest);
}

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

/* construct_in_place.hpp
uzDwv74wBRnPnWm4TAvTkPFziC5zyh2mE3JHO02uBTMIudqvSqbAcoRcZIh5D8ws5E7W2Z0IKyDj+1LCt9MCmNNq29xDr9G1YXIyX2bzY1Zb6ymF3PhZCeEwDZmMWWrQ3iRYipCbdefVZVg6Ge+zbf3P3WFZZF7MSobFDIblCjnnRdMKYWYh5xTetBGsQOjTN69LH5g00/ae1ihNWgCTkwUwG5ctPwhTCbnwJYqyMA1ZIDOlvoQzTE/mwizezxILSycrxyz41/wesBwyV2Z+Pgm3YLlk/syG35qbBLMIfeaUMe2HFQjzrV0YthwmW2Ob21DC0x0WSsb3c3tmRylMJeTG1RxgNQ2ZH7PIPlN2wFLIeC8FdxenwzLJ+H5+vZq6GJYn1GtTOOkpzEwWxEzfPKkzTLJW+J4yao0JJifzZdY6odpymJLMmdmuaR+jYGoy3udS09bysBSyYGau7xdWhGUKuclNX32F5ZF5MTuyXboZZhFmKOEQ0AsmWWd7ndXf1m0PTErGe7n412prnxFkvF6TkZ2ewtRkfD97XNh7B5Yi1NszyudfWBpZOWaGkHJXYFlC7jfJCusMRrIAZu38r/rCLGSuzPo1qrgYViDMd2LT8Akw2Xrb+TqvWVQLpiDjuZ2y02aYhsyHn1/Nk4kwHRmfb+LWMm1g6WTOzJ7WKzEblkkWyM/hevV+sDwyvi/eO5o9gZnJyjNb5F31EUyywfY1dWRBvykwGZmc2ZM54xrDlGTezI7rb96Eacj4vnhWnzcVpifj842aeMdaL52M78u5oKpxsByhzycX/6oFyyPj81Vbtuk5rEDoU7u6SXmY00bb/ZzUxXcyTEHmzOvNjC0FU5Lxek9vB02Hacl8mR0b0LwyLE3IBQREzYflkPnzMzroUhFmIuP3itH+N1vCzEK9y/828oe9F3JV7SoXwiSbbOu9iJ/zJ0xOxnOdHwc0gIVuEr4zLZPdHqYi4/emlVLWtIWpycrw19TdK+WwwWT8fcAXwz+HYSlkfL4uta9VhBnInJg97hjpCssi82LW3Nl5HyyXrDSzno1U8bALwgzvPl6Ihpk3Cfcvq5McYO+FGUL9lv8Bk2TZXruVt7/5BSYjc2WWds8zHRZKxve63pn/LYOpyNyY+TRr/QimIQtk1jRy63KYnsyZ2Xjv7CqwdLJgZk18p0yFGclcmE3OPnkVlkcmZ6ZwWW6tVyDU6+NVwQKTbLZ9PDRp4OsICyXj9VyDNEtgEWS8z/hSN0bC4sj4+YVoIv1hWqFe3M5m+2DpZPz8vhqlL2AGIef7bks7WK5QL7FbqUxYHpkDM5duZzbALgj1Du/r2A12TchdP2psAjMLufWD3kfALGT8WqoTUuMWrIDMidlBr+mHYZ+FGQa2GeYBc9pim5MnOk+F+ZDx3Jo9rQJhcjL+GOs4PmgSTCGs6X933SiYksyZWdLrKmmwGDI++5yCN71hGjIXfraldyyFaYVc3SXdMmA6oZfykS+uwcYL8+XVerIZlibMp+5ddBm2UKgXVS/wBSxTqJcTPHsGLFvI1ZN+sIMZhXrHHAyzYSeF3Nj6/mEwk7AvG1fu8IBZhNzmptErYPlk/FoKrNEiClZE5svMudTpPJhsq229TuuVlWChZDxXomKSF0xFxus9K7MtHqYRcv/sLfgFlkLG9/PXqG1DYGlC7kt6rwJYFhnfT+9OB36DGYVe+sWNfAzLE3JbVkx7DTMLs1ee2LIRLJ/MmdmBl6X6wIrIyjA7umJfAkyWbbvm62mPHWChZDzXsoZ+Okwl5CaZZGNgGsH2NMvuCdMKdnjI5U2wFDI/ZqWi/0qGGYTclUa/3IZlCblPRVfTYXlkQcz+nnQ=
*/