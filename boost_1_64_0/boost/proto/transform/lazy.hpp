///////////////////////////////////////////////////////////////////////////////
/// \file lazy.hpp
/// Contains definition of the lazy<> transform.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_LAZY_HPP_EAN_12_02_2007
#define BOOST_PROTO_TRANSFORM_LAZY_HPP_EAN_12_02_2007

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/transform/make.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/transform/detail/pack.hpp>

namespace boost { namespace proto
{
    /// \brief A PrimitiveTransform that uses <tt>make\<\></tt> to build
    /// a CallableTransform, and then uses <tt>call\<\></tt> to apply it.
    ///
    /// <tt>lazy\<\></tt> is useful as a higher-order transform, when the
    /// transform to be applied depends on the current state of the
    /// transformation. The invocation of the <tt>make\<\></tt> transform
    /// evaluates any nested transforms, and the resulting type is treated
    /// as a CallableTransform, which is evaluated with <tt>call\<\></tt>.
    template<typename Object>
    struct lazy : transform<lazy<Object> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
            >::template impl<Expr, State, Data>
        {};
    };

    /// INTERNAL ONLY
    template<typename Fun>
    struct lazy<detail::msvc_fun_workaround<Fun> >
      : lazy<Fun>
    {};

    #include <boost/proto/transform/detail/lazy.hpp>

    /// INTERNAL ONLY
    ///
    template<typename Object>
    struct is_callable<lazy<Object> >
      : mpl::true_
    {};

}}

#endif

/* lazy.hpp
78Xt9ReTvMaXmvb7JfyDxv13u/1+GX9PeM/fKPMj+MPCQ7j9fDJ8jfDXcLv+n+i1/z6EkWj8hc9WUT4fcbKX63vJ+/9t8XMTzO+2NrfviNcoLu9/64pHNPO73fCFmvndOvwp5fqpvD/vNvwJxWX7ezv+uOKy/b0Df1Rxmb478YcVl+kLTfEaIzX9m4X4CN3f58UnNWu8fQ/z/Yt4bzzD6/jE45z29894pvALcev62Et4D+Fbcev62F/wLsJHH6/s7XSvcbRm/taDH6WZv/XiR+r+vjHeWXP/WiHeTHf/I36y5vrMQnyq5vpMGJ+suT6z8ZSG8YtMXxer/uNv4amK0z+x5+fewZ9XXI7/1sykfwMmu361Hu+cKq8PKOcnvKPisv3fgHcAk10f6DjLa1yXsqeXj1KfL+81VmRqnm+GtyG/ZniU/B2nPN8Mby18PG4/3wxvKfwPuP18M7yF8F9we37gTNE+yfUb+Dma9cfn4Ms0/ZcMJl83aPpHbfH1mv5RR3ydJvx6/K2Wiov75/+BV+DZHsux0c74chdeLLwIt47/13iR8HW49W7OUq/xbNqe3nWMcn7h4QN9WzdOXx+rfcJ/akU7rmy/mu1bWe0Tvlv463hLM32v4l8L7zfWOf6v4TuFX4rb/acVXmOXsv5K9n8/w/+Gpyqurp/2Xu41/qy4XD/dGt8o/Czcnr/HHxf+AW6nb6WX5/8nn5/+CR/YeP2Xnb7mq7xGL8Xl/Q0j8C8NxcX9Db/BP1Fdzh+sZnyXYP4vx9xmEj4ST1Py/+mjnfV/0/Ac4SkjnPV/s/H+wmfhaeY7H95T+BO4ff7n4QOft2AeJNOp/0cdQ7rN8d2K6+k/a9YfXI5HNOsPVuILNdcnMm5gfKlZf9oVfxhP9vzSbvhDeLLnl3bHH8CTPb+0B74GT/b80gz+eNYQzfxIW3ywZn4kF888OPnzO2biJ7Ozdyo+8UhnffEsfKrwC/F0a/0nPln4Vry1df8Gfrzw0cOc/Stk50/SPJ8hgE8Uzv7Z+V+Kj9H0P9bguvDX4brwH9WHz8lWH34zXBd+Gq4LPw+fo1mfNxOfobgcv83Cpysux9dz8RM190+u0cZP/uG6+B/GdfGvx3XxZzygj/8QXBd/R1wXf1dcF38IP0kTfxU+URN/NT5eE/8S/DhN/Bvx0zTl61l8uqZ8vYBP0ZSvzAf15fcwXFd+++O68hvCl2nCr8IXKy7Hd9V4teJyfLcIjyoux3eLcd3fp9+J12rS9y1+piZ9/8IXa9L3HV6tSd/3eFSTvtBDuC7/8KAu//ByXf7h83X5h8/T5R++TJd/+GJd/uHVuvzDo7r8w3XHN7TOa5ytyz98iS7/8Bpd/uGLdPmHV2nSR+eC+y+TPx+iC15uX4+yn99ip687Xqq4fH5LHa4L/3FcF/4GXBd+7iP68OfgsfA7K955sBP+6Xip8FNxK/xtuC78H8zwxyk+IssJ/ye8VPgi3Aq/9lH695r2/Tz8IU37fj7+gKZ9vxi/R9O+5z7mNS5MEH+mlX+4X+T/jg5O/HNxn/DiQU78hfhc4etwK/56vJ9mfsZ43GuEdOUTn6wrn/gETfkJ4RN19RMfozn/LMZHac4/G/FluvMnrmufnsN17dPzuK59egHXtU+56/XnnxNw3flnPK47/0zAdeefibju/LMR1x3/d/DJmvr9Hj5BU7+zn9CHfyIeC7+v4ncq4U/FJwj/WAm/Ths+xRufrGk/NuATNO1HxgZ9+ANwXfiDcV34tfhczfzU2fh0zfzU+fgUzfzUNjxV8/ywz/Bv7W83vr74I/6h8Ltx+++b4duF/4hbqfkZ/0B4wUClf/Enffp247r0pT+pT18=
*/