
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
OBq9wZFdMh/3wnF9mA9yx6hXPMX0fowv2U/cYjwiNxKn1dCqH8/sKRi5vgpWV+DY3bk77tWZzxU/72mL6Jxw1rUJ/fba78zLw3uiwW4d8RyOhXFeWrcvX/4fFnJpbxvuZaV9PnyZyWWmz3jZ63rQ1cW6D19HP2paX6wNOpcZF/he9Z/GMV3Uikzx7ovtQ3zxe3a/bXd+HVeGjWb05XT4YdvY/M0qH9zjUmtNKLKc0LcgxLYrG5OQpIyF63t3cFfOKgK0U5280DGE5032By/oEHYb81Q3UDm5W/yDidOBnUs7szndxA6H6oINs11M46Rl4GCLcjWRdFQrgkOvMl6wyMDSKCufJ5X9jORUo43CFKel0hxbHx3/pRlHbS9OtlG1A7z86VYVzd0BfKrs2fEP0BZi3YABA8Bgfo/6aGwJvJpufkxZqMWTInwNyPWoqOT0aimaAmUiMrJdhLil96LZnDtnD0qxUuM/NbRhR17RJzXAgll/nmuT4vnLVMjn4yOch8CzpDNZBBJhpl08SG5NRHU+0Zfrr7tPGbnL8y+fINYZAfjRmNU1G1PXDg==
*/