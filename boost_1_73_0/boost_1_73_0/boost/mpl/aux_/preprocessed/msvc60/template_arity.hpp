
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

template<>
struct template_arity<int>
    : mpl::int_< -1 >
{
};

}}}


/* template_arity.hpp
3/QDn1tI/ZViLfm5vFSOSMKVarNOEEY2Xo+96d61ebgjriaeiPtDUjMILucHk6eUSZUWmUx5i8nplSoL6+V+la/jZEI8NVervWB6uxzRlaGj9rzlcNk7LCyJLNVlHSxTKmHyPZN35qZgdFiQTu2Ja9vrZanza7Zjs7bd63VmPbErdKURWwxK+lDSCJ88UfI4GpWRu6gPzb4/ng9bPbyztDqu57fUIT+ROmu6l6Q92oEbdU4PVC5cwz1oHW2M3NyN5q2dv8Xs/ZhE4mlrmI1XxKa+GuzrafG0YAqF6w5SRguGwYF2Ql6NDuJatbs4tm0mi3ExnIcaNUoOc2uLHVaLfrAN+7m5WecIxtS5YLMFPW7SL/EuvqE0W1OVVHgitQmjLVd85o4pdriQ0oLeNkbM1mNHIjjQxrw7h0tf2/kRvzyQY3w4QDb1tS8DMNQ76bHBkvVcKDKnS9aH6ULllaYpdaa4JFI7Q5qOBd/3tlsiZGhhQ6q4OYuMWON0vk9udcLY2gg9ZsGxo9O8Kg810uMX6Zw/eD2LYi165/JUqcrBasYbzeVhUE73qaf4XCHmIFxNA5/v6VuhKPbmmuDClEFkcp6TPKVN6MmgN1hLeV1fy61xztP8NFl7cJqkC27MzTo2niRYb0zyKs2ONoy9
*/