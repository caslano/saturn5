/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_CALLABLE_WRAPPER_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* callable_wrapper<Sig>* adaptor convertible to pointer to wrapped entity */

template<typename CWrapper>
class callable_wrapper_iterator:public boost::iterator_adaptor<
  callable_wrapper_iterator<CWrapper>,CWrapper*
>
{
public:
  callable_wrapper_iterator()=default;
  explicit callable_wrapper_iterator(CWrapper* p)noexcept:
    callable_wrapper_iterator::iterator_adaptor_{p}{}
  callable_wrapper_iterator(const callable_wrapper_iterator&)=default;
  callable_wrapper_iterator& operator=(
    const callable_wrapper_iterator&)=default;

  template<
    typename NonConstCWrapper,
    typename std::enable_if<
      std::is_same<CWrapper,const NonConstCWrapper>::value>::type* =nullptr
  >
  callable_wrapper_iterator(
    const callable_wrapper_iterator<NonConstCWrapper>& x)noexcept:
    callable_wrapper_iterator::iterator_adaptor_{x.base()}{}

  template<
    typename NonConstCWrapper,
    typename std::enable_if<
      std::is_same<CWrapper,const NonConstCWrapper>::value>::type* =nullptr
  >
  callable_wrapper_iterator& operator=(
    const callable_wrapper_iterator<NonConstCWrapper>& x)noexcept
  {
    this->base_reference()=x.base();
    return *this;
  }

  /* interoperability with CWrapper* */

  callable_wrapper_iterator& operator=(CWrapper* p)noexcept
    {this->base_reference()=p;return *this;}
  operator CWrapper*()const noexcept{return this->base();}

  /* interoperability with Callable* */

  template<
    typename Callable,
    typename std::enable_if<
      std::is_constructible<CWrapper,Callable&>::value&&
      (!std::is_const<CWrapper>::value||std::is_const<Callable>::value)
    >::type* =nullptr
  >
  explicit operator Callable*()const noexcept
  {
    return const_cast<Callable*>(
      static_cast<const Callable*>(
        const_cast<const void*>(
          this->base()->data())));
  }

private:
  template<typename>
  friend class callable_wrapper_iterator;
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* callable_wrapper_iterator.hpp
B93vf6BMNgBID1/jO8K4DwqibFgTxdd00C4Tj8agQcWuB902jDPTsVaJXxwgom65m/y3eH6kHQTx6j8dTC4AWSTrFiItH6G+XbVSoSrL/+L5oTHHEuCZ0M+Zrz7UHif7aGmnszJoun+ua5An+bp4DlgrW8EEmxtaAW+u8GSujJLHatCtY9X8sJ0lrmy0Gnq8xgsmro/V8D067slKKje/mHJuX5M+1lEuxyy638J9a1CQ/og/3G+Mb2mraqGVxqp4HJIr00XYF2HyF24TO/tNPNns8XjlQI96kRV/trjt0b7Xq9GBbGUPyg2X1dW2N5DBWP31yqT3BMjVwYvmR/fzcOzfkcXh3o0t68O0nb7cjNAN8awvOOLnxdDMONvSZAVZ8VPGZ/W29ro8X6tuaBdDtBHWOTJvqdzYFq/IlumHVrc5roHca97V77Da1hieJKMPWFdfusrygbqt7fQoXFSaNn710vnhXEFSqB+9MkuHY6sHnGWND2oLW+b02+pG5PGbCtsvjuhZS0gJ0s9rqcMelMz9f1IOk/sb3Wuqvfuj4l3jqt/frs2TSWTJfL2ll/bWTW3tFqNnafxpw7kS7V477/Z9oLZhPTwbmQ9b9VS1I0r1pnbbuVzMTfOjckQhFEs+PnMsMcxlfeVTOXaXScR3hvpYtlxeSRw3ctQq2M239S+1u7q4wJXNCk54mDtDqKmTD3MEBHG6vqVVuvgyeAWo9J7h1HBKurg9yh/tPi1+aEoTDO4pHg/DdMUqmFabX6curyKv7qMRvhWOf8dUxoxRd0XZJjRW/zgSI50qV75nvp3nqgKNQ7+M7F9iTLnMr8HwsIDlGTJc5R+/nV94fmGPYb9zbUOiQ7qDI7TXKQ+hfFReoMLykz/a9gj591+gVW9al2giB3fbOY3vtUzSsoGpqYq0Sv2g2I3tnge5vvIPS14mc8wOc2PJpX4/aWhr20S3cxcL2xh8qhqzfP8rku/c3HT2gqh8Jbd/ny6McouAC/F9gfH7VSuyuniafLytoSlOfzKuTl34t1VXOEd3dbN4gRVj1IzbZ5/I/dC4xyDg1p/tuxitvYFZStYHkoyFQTDCthqrcpPEYMzYpJzTH0NaWtysN8vvk2g3HpFMmFj5XmRlIVZ1ZieFynuoV/3Y5Wkl9QSGVFvqi6sVP2YX09bmloZa+d2aQFeMhptbNiKzryy1f+kC4wMwVteIiEFsYmG4f0B17+H7FldOlYtZ5bJzWpOPcF/jT04cPGrnDvBgx5kmyabBGr2xRhBlZ7u+UD+3/W2LfEDjfK6/aSysb61r29TYDp7cEHuz7hXeRLLDjBuXF/BxVRvqK5p22iNzRBwQxtJF4XmtKd8RYU+rDWudJByoiGM2j2FyKHftWhCKG6HxeBd0e74WnoctUK5Bd+a7NT+08yo7qCivmii1fArToaJm+RX+qDKmc6mtjPqbmde+eEGB9RDDo/yrL09GATQO/BBd+ems/HSAMjjV8oS3+INNaD+yj8kx1NbePF/OnW+81KKH127OgP48Lx5l9fAysHHy2qY2DTGR8zCFk9DY9mmPf8aR9vqW2pAt2ldV2L5yawE92sKFx9vG+mx/c9d/snUs1ZwictOG5hXz5S8JqH2pVSsIN9iVvIWbSIjv5/kM2VaT7hPz+NSaWusWN9EQX3/WGClbaaEu1Ec2N7Q1WFmtW99XaNdOipyIub36bm5c0foQYwzVIZfWyjYB9pZFtL6qsS0unzVxu1GB2/WHO0LjZXie8K0FEXlMKA+atDBhf/z+gnA+rbLKs24pjcjfQvPpHy2YOQe2x+SfCGv7vauL27jvBxHxNhWK3apIOlb+yVYS3lVyzhOvlv/VtjA=
*/