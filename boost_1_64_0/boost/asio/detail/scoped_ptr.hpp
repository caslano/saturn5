//
// detail/scoped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_PTR_HPP
#define BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class scoped_ptr
{
public:
  // Constructor.
  explicit scoped_ptr(T* p = 0)
    : p_(p)
  {
  }

  // Destructor.
  ~scoped_ptr()
  {
    delete p_;
  }

  // Access.
  T* get()
  {
    return p_;
  }

  // Access.
  T* operator->()
  {
    return p_;
  }

  // Dereference.
  T& operator*()
  {
    return *p_;
  }

  // Reset pointer.
  void reset(T* p = 0)
  {
    delete p_;
    p_ = p;
  }

  // Release ownership of the pointer.
  T* release()
  {
    T* tmp = p_;
    p_ = 0;
    return tmp;
  }

private:
  // Disallow copying and assignment.
  scoped_ptr(const scoped_ptr&);
  scoped_ptr& operator=(const scoped_ptr&);

  T* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_PTR_HPP

/* scoped_ptr.hpp
KGO4sYzJF2Y/M1LKAeGoJzwDZjH6mdyQJ18ULKmqKgdJLP5guEzHvWJFtZVDJBjv1yENUher/nPteKwyP3NQ83pI3sHjKpcU1x08dlp4h1iTZZPfSkfen2XTm2WzpYmyKahcGqtsGK6/Z9kks2xIgz6/dZPlQ7r/SfmY9/IdjtORXwHTnueLL0D5vOhdPnIvn3fZMIzjHsz3xI67aOUleZ+EG58kZaaiYd9ihhvpUVb2HX7vCM15RiLSnm3fo8qwKdH3QHMsygkr/yTXu0c10qPYd2rGC8041EO8pTu/rr2uj6IW3AsYXSf2vVHjpd+X/LaIX0+2jr4fK4z6aAx710d9MUScmG2Z4Vg+wch+Xfybb8ek+dp8apZJ0O7fvMskYtx7uo2OuBqmPbEdCmi7q0zwiPFSfTcdxw74KTd77HhI6M9l2ajwLBuOg+1a6btz+Z6do38/NT7At5EX+barboMJmriE558vAE7CBsOsVs58XFha59FPP9LRrrt+zM8UCTfbf7a0MryYBfMlzEDk5VswR2B03vgN1nNdOLpPn2nRxPnJS/hbosde8sFE8Y/3m3LTYrkfu3kZSI19w1o7xj6OaciTzQeUierCrj7M1VdlttWRricfVMHMGo10t/EoP/ZVkWWXzLKbLmHON3IRP8uI8XSWMLXR/RT9U6x+Y4rYlxv57NtyJJVlKDP7ncY8ocnHSDDBkjdPJrWs3DzKyZIda+1+xVVGJ9vpCML4UBegOj91Ajx2yFVG1UU1taXyrq5bDigvq7T7DoYZbved4i+Psdjv0ccrmucoj9nyWgrzf5n4v4hSrTF2Gx1YLj6jKkG/O5BkDNbyP+8i7coxdKiE6+WbjfnOBnztVkg1B4zJ1t2kH4l/0DF3WGHfky1+W31ZvtF0M79Xb4w2+jrnGxY/jJEwN/iGMcx0K0yZhHHcoVdXVId64PzoLAl3k284w8HGcJUSLplzMkPzX60u7wlSh20k7EFH2VW6eOcciScfY8AUSz7OjufbdSzHEqFZaKSjHPn2MN3WIVRI7nsegHZT0g61l2xgFXrdg2Y/vojy7XDYEyjfvjlY+nfByN+UeeHWcpm3MSGq3XNM0LyW4poLsYwiZJRy+Re8BJNKOaf1WNReW4unC+ZPnqda/pCC0oqisnJD6rhK2r39ruB3hX4s+dsM30Xq9qCKWI19tfYbEVvEP8Eq+5vFPlnoF2Y6ZQ2+3Sj+3cQ/IHV+IVQR9nzobvGfKHVioAxOwHynL+qk3beMyDpJIU0G7LMHgabNzIRQWyOajmPVm/2w/twTZ8eAbw9ufqw6jWNVlfQtDa7xdnt73lcAczrPFn4PA3fiaXZ5Fy8rLV7Ownbeb86yJa39FvdZYr+CfY3WNSy37x8lfW+rrIaLfauRzHc0Wit6810ClvcwoZlnDLPlQcbTw3qzaqPYRyDMRMiD+m+puAX1Wxx8p6fowlrr7ZCs0+z3+susODNEn1CdBHt7lAfyEBgb3x3XVraJxz8Y2x15412dLItpTIPYrTQN5Pd5d6fjXs654n867Sb9UJfu4Z3BLWl/WrbiXekR80td/pxf8u0GRxmzXdaLu1k+ZyVdLGmBnmxwhG4iRX/4cfLMHTDXjhRBLYJnllVh1PHiGdLaPNNX7Ju8eYb0Tp7pLfbrm+SZHu0ieIbxOHmmTuwjXTyzqF3TPJMh/t8nz5hxZkha7pE3lqpLS2soB1tv4ZDOfitJeGwH+Kuu46nx2Mh2Lh5jHgbF5LFx7Vw8RvqO/3MeM/VgKDO4WWUmvFfWzpv38jrpBJ3J+ZJK7/XgvaNRvFeG0dWT90ibxXlSNK/Rn7xFf+ZD+Mim8eSRMoe/o3ybfbc=
*/