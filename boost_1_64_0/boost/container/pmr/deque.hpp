//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_DEQUE_HPP
#define BOOST_CONTAINER_PMR_DEQUE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/deque.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using deque = boost::container::deque<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a deque
//! that uses a polymorphic allocator
template<class T>
struct deque_of
{
   typedef boost::container::deque
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_DEQUE_HPP

/* deque.hpp
/hJYCZnNrOxNbzmsytTJbIYV2ghrEjl/25b0GKyTzMts4fHhB2F9wsz3W2Hu7uicDR/t/xEWEHa39fRcWDIZr3Pb0DOGw0JkNrMnH/uPGxYm47VUn+C+C1YibELrWQmwSmHmm9OwOrIgs9/3vzkJ1iH6MOXtCd2w/m7n9RdRzP0NjV1mCc89VAOzyWxmS89bMwcWT+Zl9t6KvhmwFDKn9tKk8eMKsw/4uRv9zWLWKr5Xki2Mx+WS2cw2/f2qF2BFwuYvv2Q/rILMy2zkqIIeWC2Zj9nZbz4xDNZCZsHksweK9Sg2oJjn2+g6Q5kXZMD8ZE7LJahYPJlTe8mKpZNhef6X1u10a+g4WI5pjxlvL0+xsJPRn0LWXhuNl4aRN66HlQsLzZo7FlZL5mP28C1bJ8JayLzMjrljeAWsUxi/jutDTtiOFSfDrJ3RtbTefNouWJCMx60acdQWWAoZby9808TVsExh5neMYLlkcczuubD+ORzjylktH9P6M7/5BatVrFnYD/Pfnw7rJPMx21sz5VzYABnW3ydiu3X1DObcTHUe7Dw1A/sJHxn2ye1ke2/tTkD/kshwPvEpHf9enNj8HeJCZKjlM4q7+qp1MailgLX3OW+PrIwMdXbwaxmyCjIvM/M72bBa0x4z8zvZsBYRZ34nG9ZJZjMzv5MG6xe1RD2rQmYxG3bppNtg1nf02xDMrlt+zwFYMhmv5a73W/1YDxlk6MMXZOZ3smF5ZGhvC21/5poLVqhYqWmP2ZUbY2bBqshsZhu+uKIE1iBs/1ljYa42YUcv3rgD1iMsPOTNO2Cu76Nridk0/zCYLeyK+NxbYHHCduYtHwdLFjblpOstWIawsTeMexiWQ+a0zMJkHmb8+2CFIo7vd0uVuHJuYt9ayXOK5xlqlZz1Ss5GxZoVa1WsnczHzFwHwPqE8ffqrB+cc9rC+H7JT2YzM9smLJGMt8evAzLIvMyGnbz4KViOiPvv+eeMgxWJOH4dUM7rFM9nVZI5jYla0YfvP9/1L1iziGvaetMYWDuZ03rvFHUOD9yxCNYncq7cE38tzNUb3fet4+ifsazJeJ1fP10/DZYo7K5zJ9bC0oX9dHMPzJVDxut85PkxLbACYWeXlR8PKxVWl5paDasiCzLb/UzfKlhLr/M23SGsZu3dV8J6RB/2jm8YDXPtirabZt41G+YTxo8dCWRYf1+KZzKSFEtRLE2xDMWyFMtWLFexfMUKFCtSrESxMsUqFKsSxs8naph1ivu+dWQWM9fc+yfBmsiCzJ78dOBDWA+Zl9ng74DT9R9r7yt5/fejs1nC+D1vWzG/YkHF4sksZnweOpnHibmLVDKb2Suzrt8KCwm7MenuWliYzMusr3LyO7ASYctXPv4zrJLMz2xUU+lwWGN0HLtGoPMXFrc1Joad09K8BuvftqixdI5rgFlXzH1R5tpN+1ZmNf946FuYn8xmNnTEsdmwRDIvs68Pf3XBIZvjSiNDe9tjcgfbI8sgs5iZfR0sW4nLJbOZmecEYEVkXmZmTg5WrsTVivbGLLJOhNUrtTQq1iz6Z8YgrF2J63S02a5u1r+vY84ZvO9ENmDimJlv18JcfVQLM7OsYV5HC7kCZMi5g8xsY7A4MnvQ2LzpOFcKi+uOmT0YR5amWIZiWY4215VNhu3hm5h81/xvPq2DFZHZzArDt3pgFcKOu2F7PKyOzMvsXavuR1izsBsnN94J6zB1MjPvgMO6hJl3j2E9ZAFmp5/9cCvM2hNd575xdjMsSMZrWfvtv56GJZEFmR0zvOKTQ3auK5sM2/u3MeNc7Wff9D2s0LTH7JKrts2AlZv2mH25edcdsBqRs2LFNW5Ys8g59KU=
*/