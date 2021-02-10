// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TEMPLATE_PARAMS_HPP_INCLUDED

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#define BOOST_IOSTREAMS_TEMPLATE_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, template<) \
    BOOST_PP_ENUM_PARAMS(arity, typename param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#define BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, param) \
    BOOST_PP_EXPR_IF(arity, <) \
    BOOST_PP_ENUM_PARAMS(arity, param) \
    BOOST_PP_EXPR_IF(arity, >) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

/* template_params.hpp
YZLnMLxaCa6tF8JZZIltUaQdKE0bNTC3EanL/ofiXGVRVH97dXmQDxtof+Lt0XJAOkobfGxcHmUsp+6E8yWGOs3XGRJEUN6pnOKVFXu9Tr/rNy+u3pSVDuhlhf6nTq8saim25P5/lGPJ+bnqSWY1tjdD/PCESDXAO3r5Oq2u97F9W75QQTtKx3Qw6d52jvJRkI+Lrt/ContccDn5lDj1ihPipRbidT3Ko9/uTg96Tpl6ZJvI/sfu6Mj6jlGOCiJdDgkRSvkFofn6upTVglTKJby/HUxLGSxIRz62hsPxFx/fPh9D/pC3UxyN/Wl7H7Di8ZDdbzeabw4FckLJQusGjbpkJKeUAzIZD+8blxevy1HZUcvC41GXcAog3c36ZY0yq6zW7rfwvyxf0Col2PL6nenNx0oZbqm/qTN4o0FZmgi/yXZrOBlVao4ov8vzu8lkPJ11O377bvq5W1E94lagT1Y74N5i5+xOK2VQYR537C4WVSqq46694xzCb+J9OsQePR6ybzslfNPjjl3ai3dSZephc4R+y7sftYvftpUWeYJ7chv6e7cCFV8YdsKjTYo2sH8AUEsDBAoAAAAIAC1nSlLMkNKZVwMAAPoHAAArAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvd29sZnNz
*/