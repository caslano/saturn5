//
// impl/execution_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP
#define BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/service_registry.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

template <typename Service>
inline Service& use_service(execution_context& e)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  return e.service_registry_->template use_service<Service>();
}

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service, typename... Args>
Service& make_service(execution_context& e, BOOST_ASIO_MOVE_ARG(Args)... args)
{
  detail::scoped_ptr<Service> svc(
      new Service(e, BOOST_ASIO_MOVE_CAST(Args)(args)...));
  e.service_registry_->template add_service<Service>(svc.get());
  Service& result = *svc;
  svc.release();
  return result;
}

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service>
Service& make_service(execution_context& e)
{
  detail::scoped_ptr<Service> svc(new Service(e));
  e.service_registry_->template add_service<Service>(svc.get());
  Service& result = *svc;
  svc.release();
  return result;
}

#define BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF(n) \
  template <typename Service, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  Service& make_service(execution_context& e, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    detail::scoped_ptr<Service> svc( \
        new Service(e, BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
    e.service_registry_->template add_service<Service>(svc.get()); \
    Service& result = *svc; \
    svc.release(); \
    return result; \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF)
#undef BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service>
inline void add_service(execution_context& e, Service* svc)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  e.service_registry_->template add_service<Service>(svc);
}

template <typename Service>
inline bool has_service(execution_context& e)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  return e.service_registry_->template has_service<Service>();
}

#endif // !defined(GENERATING_DOCUMENTATION)

inline execution_context& execution_context::service::context()
{
  return owner_;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP

/* execution_context.hpp
s3x2DbLVA98TfiuWU6YHl9z2bF/iOYZITzT6tIizTf9L6b0gXeFG/xWxppNfIz8MtBG0CR69v8y5rYnBM9sU9WvboppABrex3951XF/Vr2nqCzc7wOFrfnltWYkUyg+FaMow2ovxn/PpYFdvnN5J9P81FJ4JjSBr6onO7RJ73Q8SzmWYx4bT+N+INj89j8e74TTc+fweZzqN6Yj/cZ7q61NgqS/VON857jlo6pj05m+v2fhJLGKbPho3naEyz8r5m6bOMZ2ELwIcJGrnwbBfG8pPooDo+jm+k+O53tW8Mi19BWZQWpbja7mlfs7F8+N6Svc6XpBTOA7zAor7N3zeXjCcr8HfAb2upNfwd1YqfkfHAqw3xuPb0ka5K+nj7+ldcFctw6dEGp+v0USPvsHz+gkUHiD5KRzMLw9r0i/k3pTXPjUvVgU+vnvyecJ9S/5FeozoJ2joR0q/SN/K3cyyxevZFwjvTfkUaBMpLkg7WjolzZfHSl/JPdkXRPgY4UbTsunKmfnTpaAvykGie1X+mvmYq8nrMow9X8s5iNeUo2Y+ZYOA6A/9qR7Gy5OkI6JutlMefxH3Pq4iHFnuBctUg9TVrs5seK4sL9XsGRdTXl4Ow9uVwi2pviISaJ2DIga/gfuU0scib4St68p2f/onou3L9kmVtgP8AcbJlfI46ag8nMbDUgj/7gXq+j/TvHZinOML1H6eZ7aFM87pBcLXol19kZ6+3UJ1PK1faveOvIViPrzB7h1TF4p3tK3/MJA2DrixwN2j2DZB3y8m+PTHc74GutPRp0E/IAb8egNr88sRnoxnCp6pzfzGNhE29ZupjqU08ucJKBVyK7PzF9n6un6+3fmw9dxvyVV8pp4jMM7GqTrs76zDNBcqGfVWBuutEYT7u+zB/8vx/BNPqYwZluyUDgl/XDXPRNO8LIl1z3FKv0Lui1JdAS+MX2Hf7iKznyJSwt9EOrRvhNRVPxdj+v5vkB+wDb7Zf/IKws/iMCwJShgh2vtGAUsX8/c6LXMk0/c6jLNiMduhPHWPG+1QSYyzZ7GYk/2mfOAXMd5+TuZnmmOLNX5G/fXvPLNYyK7JB5j34Emursj+4+eVGOVo2Rt6OTpuCPd603odt2dJIPOjfObfi3huVM7GeVMrV+xOF+p8Y8JfxzKk0ne22r/ktIzg2cYUfsz2DEQ/4A+E8zCFZ4k8Ui3s9/zdKqU/TuFyxtedW2H0PxR3ITMu34Wcj7D2m9/CqjlCn/5GeOk0J6pD//QsUW0RN+j8wQ9fDf/nJaqurLvVKAu6+Xt6k/76f3j+bnWO/jCD/T5Rd+a+pm5Yvm5ssJafqXV8vjnpJUDWSycIv854kZpJfhJZfk4Rvsvhw/8JeCSH0Eecl18/t2IfydlHlLTb5GtkjKG68Tb4PX4W4TTIDsxyX5Ld1Cb70B73XqOOP+ebxrhKxnkFE/SBgX23O3DWVox7rnuo+zL3dHcnNLA3Iryl0wfrQpizHRyhfHgicQZXd/cs/M9yD8HHcB5nmDtd2UJHWpi7C/Ajw6fgcJzweGeL8NHOOESFeXDIQggfZkudeNcRvU/5BgpPkTvL3cQcsobiyuRUnG5m52f+b+Cwn7k4e6XlW7RWJz/zJ6T+Ym6ykuJ9POdU86+S54D6Kviad5Xb2/qbLyfcH8DxB+Q/joU806+w9Tf/ndJb8D3aAt/O31zMKRsILwvzwP4cp/JaJE9DuZT+ugFtv/E67pNoW48rCV7nFnv6jLsPuMLvfJve9pN/Fn6i7x/R+4hHvaX3Ce9oCPficBWHRxnC6zhs7J951weY2c3rzTtVP5W3Nf0T3xY1tT5/lPDFeofp29qtM5Fu9Bunea8=
*/