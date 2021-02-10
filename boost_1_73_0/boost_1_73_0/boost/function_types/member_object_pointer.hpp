
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types> 
    struct member_object_pointer
      : detail::synthesize_mop< typename detail::to_sequence<Types>::type >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,member_object_pointer,(Types))
    };
  } 
} 

#endif



/* member_object_pointer.hpp
PDYvC8znP6D+Q8EZPt9gqgXPUj/m+/AmqR+wZ6Xmja1zep/P32BuRk7SV4uEZ3N6xZVaspHvqGJVitvMwF5nHw7Pzk7hAI7eH5558IVJwXMIDZcLXt56cJ7YlT8z9vjoa37hATfAcn9LYZQJDVql5oGVHPA9FzGXmifANCRcx6VY4A8hwWQcUpFz6IyCaW/41YOHTMRZo2elKtCZqvIEMnbPoeQxF/e1moKVBlSKGlB/IrRBnZURSvponoPh5VI3asgJlmsF7J6JnC3QHDOQGVPoz61WXJU5RtJKVKxb8RoKPzPLnaim6M2SrUAVBoyCSnMP6LwHS5WIlJ4IES4W1SIXOvOe3UKDMmmpEjTP80Ydigqu6xA4hA1aHp2EAr0Xhh5aSU3WHjK13DqIsDaK0qqUaA5hwXOJQuA9qGTCS3veArG20qBsIX8lZc++J6AkegVuO4Re6MKCaaE9uOlFV6NJBDft8bg9jKYwuoT2cNrou+4NvyA3BFotgT8WJdfoRQliWeSCJ1vGf2mlO350BZ3JuD8KonkY9jvdcQTH4B6ewN+VJFp/cMHNxYLyDif+8Yn/Hhfo15wzvZprbijD+I9k0qgvvIJhe9B1dpXODjCdBvAnxBiTNBDz0ohUxMxwKxZOh6Mg7IXOb0LG
*/