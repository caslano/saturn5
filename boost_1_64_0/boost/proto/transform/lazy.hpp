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
9LZweJP043C6Dyo22n7KCMzvBBqc6MYizzmysdisIbE20Gnw5ruTrjEks61KUnsEdbhb91TmwKW/x8WeZO3DY8JIECvqDGM8We862G3ATYBBhfXz85okowUtkKMguKL0mgQ3g8afddClqb7u6nmWlLnGmNXUFE9hLBayE38GrFjXImjBLq2gtDvh4LzEbSCVtGMvZjr25g+wIWnJYERYpaimJ41mtLUOXUUY9714LLpjjVsvSmsvCWMlp3wXCD6hVML45/rGJKiX/BS2QhxMgtm8sLNCa7X8Qqg6aCR+lSHW20jsoUczhL8GdfAsLI8us7uRBSwVtlFMDHOGp4AsNrwOnsAWZzcDofOqnk+Esj4X4Lfe+ElU9E27sv8p+LYRXQfrGFHFsSAksQWJLnq8OD40am7lJmf9uDEZ+dz85dZpa1b5KuKCTm9rybyi3lRS9hgH5gUDXJEhuDanoEDPx4e30bDCpVTuQHt19I2oEf8qXac5Fl9ncPFvkjQnPOWmQ/dip8F3WvzP8W5je0lcy8Lq2Ik8WDVqAiM5w37NoHyPgzUX4BvJr3BTsQ==
*/