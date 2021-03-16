#ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_IS_PLACEHOLDER_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
# pragma once
#endif


//  is_placeholder.hpp - TR1 is_placeholder metafunction
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


namespace boost
{

template< class T > struct is_placeholder
{
    enum _vt { value = 0 };
};

} // namespace boost

#endif // #ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
1jsgL7fIYeO8oxY+TycHifGO1g/na7SQliBon3eBxtwW9hkX6jzxeTSavS/SSNvSPuNijhvAPgP1006DGeJJPvLoWOHSwsXGB1e0i+FGLTzQE2AnAfVAGW4aV01cX2R1swpy5XVGVgzdOjvMKATsKHt0WhyFvznCBzhLQPPKakDt3CA9SUejbq9ODvRcHJ3N9mm8sNHgEbVfpwaNBI92iJfo1ABR4NHJ16UaK0gEeLDGXeOwgjz5Byv5tS4xzHM=
*/