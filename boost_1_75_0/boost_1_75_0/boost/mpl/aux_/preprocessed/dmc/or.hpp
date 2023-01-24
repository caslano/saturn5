
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
cppwdc4Om3r5o9Nx76h3WHJVQnp74+a124TOt/yJcVyoOyGlG+3tj/FXoI78Nqr2F1+C1aH9LZPE8dc+xG/br1uD+yK/OeivPogN0cJivm0ziI7s5+3ifNtm6Y23FhIzEOttf1NkFxt1mzxz0MMkSVL14K+7jBq6eSFcNq/Yc3wzbtiIZGhuWLekl5DB2xii9x8YN3Y3s92NldICiOLGx1+zMGoFnVYY9bxDCuhfbrrsurLBfqQru53Mny0MmeVHr4SFMAKShooZvi2RxGFIHzhGb81c4MTskbDXDY+3Oo8FCT7VpxbvIc5IK2D0yVX+JmDieaMupX+iPoht3lOsXvRMAwmDnvnf/C3I4mDKk5Nv0LsGu10cMb9kMEpoqOjcn5rox644FFCCCIwtdHtsJUO2/SCLpXXz6xd7xwrn3afqek6mO7xr/XitqSfpyhbSF+lqmxqbqU+eSsufz16XNypudMnPoI0jjX+Kw1bfx0QKjJ3yWnm/24W0jOtHBwgEoKKy4oMQfvNkMbIU5a9d4Oj4pakujdrpIt41pDmQdSVthQY0XVu0rRoXfOqqgBP9HW5regi1n6PwF1dlHEMru2f7lDTp8KrzOd9HzGTaqq/ukX7XykM1oXJgSqtG4TlS6Vz7ORPro0HQpwbchhBH3Nw/n9jegl4/BRL6e5I8OiMHhgZh+LPDwZ7oeTdHj6lLj/lcUYLRu55x7g3u
*/