
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

}}}


/* template_arity.hpp
MZKiLdLmR0VpHJg8DioDjcZcBRdfa4E8uRy974qFwc2nfMJEp6RHODjf5kO53g1MKTc5AQCkiOAWR1FSLaV5TUzLuVDBVdVY8r3IiHFSAbVKR90oW9xoFQ0mJWKOj4FqBRnF2dr4swCOSIs1otk9B1CT6uPqFFBg5UxBt5lEA/4kIxFcQFW3E6XWpBu4w1RqxZZjNNIuRmVFaM2v2dowQi+RijRTGPaWbWvEhNZ91QZQCii9GbzuSMwo6E/eM2ZmL8gYR18MNitrXz66XXf+KewiT6mcwcCjYJ2YRMds0JLUadFDdMY11spQidFAqgqYr+Ops0CpKuXUq/B4XBCVkdGxHlTtqLEfVN1v1lgN87w+XmJ7dwCAnpwj8z8DjIxOqgBZT2y9M0U3O5jldCSLeF2+4i3SjZ9SO0q6uqoClPwMDARCH+YkxTm+SLp4zLVZJZOtZmdngueU9z39Ndd8a4rTxWwqe6qMo9kIOJV6mZwbTObzI17nghG9UDkxgFR3A139Vi2QGYmwMgjWSXkdkq+42/QEC3m4EkCRJzFlbn6ziOujxky7RbtkhVAaoO0EiUTb5WOasxULeNks4ETtmldQhowRIyVcwT32G7UDHoV+TPmubsnx67sPNNhlcR3SeCCFuHJhKv7hipHVumBTeP6vjdO9vfMIts8cHY72jtiHauO7TEeRFmdWeiP4c0mHJItBOfNCUlID6vcb
*/