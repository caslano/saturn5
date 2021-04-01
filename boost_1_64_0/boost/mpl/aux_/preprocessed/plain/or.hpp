
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
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
3rU6hLrcIsRzCfA+3JSa3JjUQoM7LFqZedyFEyoKzXqW3bs1XUreqjkjI51J9lfpjVMRv/I5iqWYjyYX6ti5jH6JrjWjxPrjnHipoROvnGafgzD5HUPuh7rN/al19hlzkb4FDjhvLGrq8It/fwgU+4dYqMGsVpTsiGd89jElZmWNJ5efxhwch8MbrdTbaGU6GLNdMqj+DckGtRAC/e9zhGggaMVlLqzaJZBlAl3nbHAZHQdyehGLpJj3HFo9BoOOkbJE7p+QPzfcdLZ4xFUAHe2YKPvfui/rLVEa9rkLzEKDmbmv7DUDhz+GFQ8Wd9AD3EJog5Jqf5PaFvPVIU/VwkNXl/f4kQd+tlYgosLDZo3DVJQk0aSg7xIQSksRyNIO+3WgAa4GCMBrukgGtdB6TVCXN20lb/9n0OHDiQrI1Xfa64RC6AFbsRgfRGo0Q/OKWv0eVJ897NRK92gCgsFY+1VdcKJoiEAOqwiyxniajDGKyqCcYNPX7sKLGJfkVtOKsY+W+PqnM6c3UoOkMAMnxzKEBVLoh3mtrTej1lP17qe3grPaHPnR6r4Cpw==
*/