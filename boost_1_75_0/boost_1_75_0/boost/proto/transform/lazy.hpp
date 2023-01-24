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
zB5ZLARVwZK4It44hXXCOrPTvN34GLVcYuWNk+S5T602609tb+UgSRFFZWYzJFmtcZDXzHyrVtsxCR8Vtf4bKGuo6hk/JhSwhsIHvYRi9r0zsB29w3tGxUmhUP6ZmyiACV7YHzmv2vLZ8wTwn1EU4pybnPyTYd9K+xSR9d9CSZHr5cgQzWdcJMr2lX9c7TbELfot1sZX3wou5NIORf98WBaF4/WniTDGzeewLoTMdnTuPfZ3MOBOgNPVBBVBhxpJfhZwDuBJZ31iZfmCQpvwkbuCkNwr3kOHaIjvIer8oi3fH6CMD+7xe5wIaMYs4wtznM03ENww5j1WiVRT0jBfwBoTSjwVBWp/gJ6HMm4Su5xyLL7wc7N6JjF5ppFhSkdFvKWxR6Jw/06zj0lr4r5v/y+a/cT3L5qVdrC1dub5d5ot9Nu7NCZmnmvaG781AjFPLGO7Q5m0iulT7yRpajmNGDVT6bONUlk993fZe9oYY/VMaKiYE7Wbm/LHHeMof7zQvIr2Ukgvj4zrdP1S4jBH7BBXgofz3iGnCgF0XBCsWPiUWN+3lr1hTA0Y/jgPeGNDHdp1fXnQky3gvrW1dWaO0p26Cz29RaCmJ+cl9UbEWRabydWpFAUrs8Ol0wEs73FGTgY5F8ZYEJQwy9/8kz7w3V8r3cQVGCfhWEUEDi+W0e/QTiNxG4gtIs42Yp96eFBT8EuFsezXTdmDVmyR
*/