/*
 [auto_generated]
 boost/numeric/odeint/algebra/norm_result_type.hpp

 [begin_description]
 Calculates the type of the norm_inf operation for container types
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename S , typename Enabler = void >
struct norm_result_type {
    typedef typename detail::extract_value_type< S >::type type;
};

} } }

#endif

/* norm_result_type.hpp
dVBtTe+Nl7PFXKuC1OjvclEEef9rN6BRmu9MuOaEWvM/SOQ+p9U1biuyWheegS44PBeKAGtNcDyn0/F8N/YCgq6h8P01OFHj0DcyHK0zJ9dwfkbjKjpBRS8BbTSGmlwOB0e6vIRvBoEsNlksf0szFtaLyYRlMHhQgxj2lEXHBF1GHSNcbvnOQm/tqjq0pDcfunpQKisNIuNSDjvFHrZ73e1j93px9Kr4nl9Ff0WfAVBLAwQKAAAACAAtZ0pSYjM0WnQIAAAQGAAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTkwMC5jVVQFAAG2SCRgrRhrc9rG9ju/4sQde4QtG5xOO5OSZC5xsM2EgMfg5rpJRiOkFeyNpKXalR9t8t/vOburF4bY7YRMLDh73u9VZ//HfVqwD49+PP3fww8+NcVFJv7HArUZ2/O+gvmHVJ/w+ZiQDlQkX702PE7yFRxN4lkpL+m75z0m6BPpRn86RPnJo68IQTKiPBGr+4wvlgqckzY87x7/DIf4eN51YcTTXMKYs1iyFE5ZrP7i6cKFlzEd/Gfp390dSfbaMpotuQQpInXrZwzwe8wDlkoWgi8hZDLI+Bx/8BTUkkHEYwYnk4vr4fjMhdslD5bE5F7kIJcij0NY
*/