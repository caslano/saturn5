/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410
#define BOOST_ICL_TYPE_TRAITS_IS_DISCRETE_HPP_JOFA_100410

#include <string>
#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4913) // user defined binary operator ',' exists but no overload could convert all operands, default built-in binary operator ',' used
#endif                        

#include <boost/detail/is_incrementable.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_discrete
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, 
            value = 
                (mpl::and_
                 < 
                     boost::detail::is_incrementable<Type>
                   , mpl::or_
                     < 
                         mpl::and_
                         <
                             mpl::not_<has_rep_type<Type> >
                           , is_non_floating_point<Type>
                         >
                       , mpl::and_
                         <
                             has_rep_type<Type>
                           , is_discrete<typename rep_type_of<Type>::type>
                         >
                     >
                 >::value
                )
            );
    };

}} // namespace boost icl

#endif



/* is_discrete.hpp
RXC/0WR5dTMF26D5Ez2Z7H4gmIXTsTqdyPScESwPTmVdjtQR2jsV0Xg9XUP+wxof6kc7jxbW05a6obswsSVUs7S01Xphv7d7QYsRS/LKWZcpdSRyJypy/TPilj2++MnbapHHW0iFv5GLrMObeo4JWso+lXWdnk9FzjUB69hBXGSD3dMo51JkhfTrHFNXE6GhfSTs0dNAqZ6blW0rb18yHMmg3Nr5WW3bSj/TBCZnVw+cBn2rgLu+J0pyI5GX3lr/9DBbbF6Xzzk9cM6UHtsT2Dal/Hxq0c+ONBtBPmMnlUFzjim51Vjdz/QpO32yTmT6XEQ26Q33ul09La4Ik1PyTYfLrKfjJ11vd+JWyy8ONn+aEOWpo5OrO8Q6Ib+8d7fRbO0zvQhtXE1XsSAvnzVzrnlhfVF9w/lLygNXoeRB91drt21KnsQSuM5q/9s3VR5n/m13ZtpJ16vSuS9WP48p+RSN8uySs/VgzSJfrx5s8blMM6bD1aHmSab8alnwjXLBVO+5FSLVHqnHdfHDV9nTcZxhP93CPP/i9FxAb++Nbu7a25xX2j7JYhD18mE4OzJGD9Hqeq8zgD60NeXS+ORA4+A0tqb0ZGaVUeMDDGnVHuDq07XrNX3WFNdogAFVb9TkOAOfGvBkrFm7fm5pRz0ejL8XSTfJTEZUS8uIDRqPnXN5e9TzgOG5pslcwrd2ml3X24THzWk6rNPJuKnl3TkjpNN630Fg1OG4xuOUM/REjT7X8DmbnI5F1unNqPFls45+DQ15MAz8BBveNDLUnEae91T6B1Iq3KrtVvZVqeem4XnU81ekOHdrgwiM6phsrE4rO+ZGlrd/qojU6dguanLZMPnQV4t5b47EcyKdBhfehfhDZaZjt66edgOHq9zbBkNd/AGbKr9RvzjfhvUKXx0Or0K1hlM0kqg/rzMpRJr+vEj4orwzpQsfst52IfJlFGsNnZYrsJkWY513VY5O7yO75ty/SFN/nR7j4nT56VTavfU+Vsji/0h7CGXaG+5oX0tAnT7u0eM8Kv4HfW1mer4DcVoaOh1dSs8zIrW4nIY/vdwVrzLg698xk0/Yan1T6p2T8fy4vcyg0zv3nPPlsJ7fNxzCBwY6bbmEO1hwZUof/HB8XEryEw7hAwadnuulz/nKkL/97d+c0OnQfaBk7pFlj9ZwbkCBtcWqEZNW1FKFdwF0GWYFXjBerMrpL/oBis+nsdTyz9u03X36iyNX18jbZE9gHx9NepMpXQZ0bVu2NKGl9fh0UqOj257ghUJKdi2zKE4r2ZQWn8FSHM3++R6RG1SZhO/dSRWwWHTc9f51hBUiqpIuYJWxJtXH/v3p9HweXF9i6+k5nkef9OwXdnuSEEtJU5h0HteH3nRnJ5Zg+BNIfvRkoiyxUHSRsaQBHoOZ/HjoE75io9ysLZwW3b1SNCXJGdOEd1a5XVhNlwVw+rPw05FyL93hPQD50NKdxDSkscHz0mEG3/JxV5C/l+FTPuaezqs0OPTM8ivbrGl7R36YXVlX7aIDE375RZp2Z7JkTtUPwpi3i+XDU3fTYU7+rVmzA/9Xa1iEWqVQeE14TfvYDuejvB3OX2Gw6JnBV45rnNGC+a4sTdBzuOdxGdwRlnFoAWAYvGWoEi+en6i573RlcwanIzN0G84UgAyvFPORUqU5DrlNcYvxmGrgflsYV/e78V0VnOMzQHNJ5cL2bFO57o6wAGEhwiKEFn5/BMJV/B5F6Ob3HoY3EHoZHkPYiZBhmgLLWYawm2kaCBa9M3wPwgTTH5wXCMxDoPcjeBLNYTyvn484AsHfgOeb+f2NeL6F39+E51v5fTkVhHlXKO/3wzvR0Pv98X6E3x+A9zc=
*/