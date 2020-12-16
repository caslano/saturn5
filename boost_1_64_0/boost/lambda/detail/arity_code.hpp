// -- Boost Lambda Library -------------------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------

#ifndef BOOST_LAMBDA_ARITY_CODE_HPP
#define BOOST_LAMBDA_ARITY_CODE_HPP

#include "boost/type_traits/cv_traits.hpp"
#include "boost/type_traits/transform_traits.hpp"

namespace boost { 
namespace lambda {

// These constants state, whether a lambda_functor instantiation results from 
// an expression which contains no placeholders (NONE), 
// only free1 placeholders (FIRST), 
// free2 placeholders and maybe free1 placeholders (SECOND),
// free3 and maybe free1 and free2 placeholders (THIRD),
// freeE placeholders and maybe free1 and free2  (EXCEPTION).
// RETHROW means, that a rethrow expression is used somewhere in the lambda_functor.

enum { NONE             = 0x00, // Notice we are using bits as flags here.
       FIRST            = 0x01, 
       SECOND           = 0x02, 
       THIRD            = 0x04, 
       EXCEPTION        = 0x08, 
       RETHROW          = 0x10};


template<class T>
struct get_tuple_arity;

namespace detail {

template <class T> struct get_arity_;

} // end detail;

template <class T> struct get_arity {

  BOOST_STATIC_CONSTANT(int, value = detail::get_arity_<typename boost::remove_cv<typename boost::remove_reference<T>::type>::type>::value);

};

namespace detail {

template<class T>
struct get_arity_ {
  BOOST_STATIC_CONSTANT(int, value = 0);
};

template<class T>
struct get_arity_<lambda_functor<T> > {
  BOOST_STATIC_CONSTANT(int, value = get_arity<T>::value);
};

template<class Action, class Args>
struct get_arity_<lambda_functor_base<Action, Args> > {
  BOOST_STATIC_CONSTANT(int, value = get_tuple_arity<Args>::value);
};

template<int I>
struct get_arity_<placeholder<I> > {
  BOOST_STATIC_CONSTANT(int, value = I);
};

} // detail 

template<class T>
struct get_tuple_arity {
  BOOST_STATIC_CONSTANT(int, value = get_arity<typename T::head_type>::value | get_tuple_arity<typename T::tail_type>::value);
};


template<>
struct get_tuple_arity<null_type> {
  BOOST_STATIC_CONSTANT(int, value = 0);
};


  // Does T have placeholder<I> as it's subexpression?

template<class T, int I>
struct has_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = (get_arity<T>::value & I) != 0);
}; 

template<int I, int J>
struct includes_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = (J & I) != 0);
};

template<int I, int J>
struct lacks_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = ((J & I) == 0));
};


} // namespace lambda
} // namespace boost

#endif

/* arity_code.hpp
2jXxBS3KHozduvm9Q2mV64mW634MfJb4S3nf01xuBLwYGATsQ7tfX57N1g/YAngJ7aeJwO7AJOAArgcYBLwUOAI4EJgBHALM4nqEq7kOoQSYAlzMdQhfST/Pds0+SPQFmkf5QmgvDAfKmlRgBLAFcA3wfOADwJbAzbSP/RHYFvhX2oOP0O57PuJP4Nl9XXh2X1eenddNy8N6yjrvK89o8ImsXN8xA+gBFtDefBXlm0C780RgLDCTZ9lN4lmIWbTjXQ3sC5zGM/WmU48FLAfXXYEqFtQNlAqad5d/Htt/+S//5b/8l//yX7/0+H/G5Ek9uv3scwDN8f8Ey/h/C8cZ7xp4FwW+BFxgjkN/0OP/ypS9I1HwWL+9ZR1fJ502w+y2HYMgPt9vZxUV8ttZe3AexDzx/4P+dtYceQ7U3yboK3EXy46uxjzfKkXcXlVNsNPuZtXdfuzKdBtxbIDxPXYWF+bafiOhOj/HybOzcnOyi/JyKmU9BFkXCc/TWtYSeQ6y+X6JXb7xJYisyriOIq5S8X/c8I5N3pY8dddneHlkDNHQ9ptD1rgLJe78ounUaTni/qP4X6vlDJW4IvT46z7xv9V4QB2y+U4R4+e4v7St7CYUvgrEzbkAmTlozLHYs8JfaBiGW11lhIlcLYXnGj3uawR8XPgGYmxQTzXi2PF4pZuRpvbSjeWLZ5SvZXyYpxozP+3FP8zohdXUm9RQjhsN9Vtxvwr1bqRl/+/szGtyqsa8g4Vnsfjf2tasK4VTK2UcIHqW0b7wDEF6AyAPv4Xyg8gE/V8v7uF4wkVZ/6SiNb8h/JY8SLnsg+6OSBzDDVPXPYqSlOm2T9zCdD1RqCfWMexi8ffosfbd8jxEf8txmTwvMByYazHTOYw4d4vb1YalHBKs3/lbIf53G89Q58iLNR96f+1EzoHF1/G7Z9XmO9hHVPseCNs+z7SCn+nGdkn3UD03otufxBGu45B2pL8tVWi66fofJnUUdRZu2SaP6P1WeUY5+4zjfy/j+IF3vFe45KaVC44+8lLoqbVleyrH8Zt0O5A+Ui6exS5XBMeVscD+HBffyHHxEq4XfZTj4peA7YDfcHz8d66XDkS88cCGwM7AQcALgKM5Xh7H8fI0jpdnA3sBlwJ7AzcC+wCfBvYFeizj12X+cav/8l/+y3/5L//lv/zXOb9+mfF/TtYkGf3/fPt/hj7DWvapy7WB+7nWgW40z786pcf/Zsp69G839m8C/JXwL7cd+yMu+7E/xzJ/Ff9LbcfvCGtjt7Ydu2ve+npMl13t/JoD4t9cu7lA34tbrMR3EmOEqrFSntdGKrwvCl+olnmFPLdXFv4EK/8yxus7hgqqw/kntY6b6Oax2o455jmpxzjZMr7pyjI+6jjzrKM5qD8p1jke1JUZ+bPrdMaQd9z0uYybdvY4vq9B0ZNx31wcGNTi7S8w2OF+bZaH1C1c1fdrR/BI4kjue4wBypktwJs5nloHbKn3N1JenQ/u0/OxV4Zyf2MYMNQyDjoK8tztHwv5L//lv/yX//Jf/st/+S//5b9+3vXLjP+zzpn9f5LF/p9C+7+54L0ZsAHwZowrd/+9amyY9ZP2//4yHnV9b4Y5QPssLnl+G89l6ikVaTs3gHTs5wYYZ4PvTP/35DkGz6fk+SO9Rvi4PL+N8f82bV92kidK3Ws3p8A07dcENJZ0yQOt9EXa3Yy3dHj61bRGwG4NAPjt1wBEcS6hnsj7F6M57NUHESLMGGln70c8tvZ+re8Pxf+0EYNYwowPbW36WnZ9djnLlXmPseQ9CXqNN97T4WMs4a32/yjOAR0Vvy8QIlCdQOpvGM4a1wCkS56dRqj6UK8BuFDcWhg=
*/