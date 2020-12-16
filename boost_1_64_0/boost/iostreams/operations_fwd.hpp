// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost { namespace iostreams {

template<typename T>
struct operations;

namespace detail {

struct custom_tag { };

template<typename T>
struct is_custom
    : mpl::not_<
          is_base_and_derived< custom_tag, operations<T> >
      >
    { };

} // End namespace detail.

template<typename T>
struct operations : detail::custom_tag { };

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_FWD_HPP_INCLUDED //--------------//

/* operations_fwd.hpp
oN7cXz4mU36VX+VX+VV+lV/l14+7fqnx/9w5P3383x3nH17T+PuS1Q3poAHKQfVBjXM/lJsUjhnnsoOP108/O0HOg86x7++u9nRu8+XSpz/fvt9fk+J9xNlTpxr7uAqy9jFT7XdsK+aVxXychCpnpgnMC44T8y6mg3H8/Zt2EY4lNYgxHDgbFh9PiVNyDQ2Op7jhT9bwe3NzCSd684vu26ThCe4Bl6TNzSs1rq9AjSeuM4rF9cSpORKWvUmyb32pcZ1RxrjOOIa4zjhCXCfBv4p5vKmkeYEvTn9P/TlidpE5jv8F0sN/UvW0EH0wYWNORiDcp3Kz2Eg4OTYUX7lKbEx8qI4pLT1Kff7v5RnJpab1JjEfSmqHifuTq3v7EZ6eTFxrv+wZcAPccAznGe5Nkr3pjyndf6l+Uns/3bH3n16xw9Wf+eBdZ7YdPWNEyxVtvnl70vpe5f2nP7b/9OfqJ/3aHzOIlqNNsLHOf87w60epw8WsImp0YD8Tx5WHcbAJrKfzmVtrv1kX7TfrAVvAnjrvuY/eH4CrvboBXqnPqYZaps+prs9JhiiTov1yNeEJ2q+XDmupu7Vhgc7TPl/7/5aq3DLVv1DlLtb7y1XuCleufI/3MvUF/Tf0A/3SfUCjP42YWZ+W9/2UX+VX+VV+lV8/7Yqg5vwC3//s3Ds92gPw0/sATqVh1lH3ouaVLlcfp5Bb3Ll7jeS7VM5482eOz84MzIfjJjBXKknkE4iPWNv3qrrnoOd9h6qjxvhnpTUXmeOdRrjQnlbpQ6aifW5eo2LfqfhlzoxMU1v90ljMrzHNsN0Zd2aaGv48rVQx+52JMZv9M88mpES/DUfVFKKOPseyqol3YQ667gXu9/v3MdXlWXhn+Mld9FtS5+No3KUEz0jz40O+H/30aR42cvVHxaD6uc+kQbyzmqRPzsysBbLB8hRyz5yCaN/Bp5g7Ot/NlhZiV+PvzibynS3CXp/KLjHv5n+fb5X5TKqO4Tw41x/J6o9gmLaohce1L2Qn6kAdWLVYmLJzFmAUCFNmntcfkAj3inwPexjFzAnYzcudYl9jorLB+MgTT3v9CvESH2eZibjclH6NVmG+KyOUHSKrshMbCteIrRSOo2ejdiQ2HK4fG4mvEPbm696SYIrHs99n8rI89y5zrXHIjY70WXjnQX6aEo3rlkn2/qnS45s4Ur04X4+wF08DdaR9mDAo4/nASk8tlgb5ubMwLpGvTtU+mS4i3zLcy+2tQs1HbUG9g4pxHNMZdYqDPupu1FcoJ+SYvqiTUetR96DeCoVs6Yh/7HvVd9Wy3l7M94aIN1ktsIY+qb/DdIeZnk6yGU9tstLpbj5x6pq2oUZmUaiLJQ/YnpPTNrgP99xasg7ASTQV6F9Kcry9PXaJvSyTiqtDTJy1Xy3odjgibp9oAvl4R23XvIPx3MwQ+fU8o7ez3Anb5vvipr0Mn6p5q6eYNw13IdXH4+eZ1KUbidFX+X2I3y2dimaYEzK5qM2ofdx/BzuEKprBpMVVqDtQfwqF/X1Axmj96HIFkfIreBpK6ocy9Kd5dWT7OkXrzObF7lP1PpE6dEGqV4e272BUL6GWr9fO0/u0tq/X1tNb7uu16+TpdSvU8+XG+c84sbOn930tX6+9p7etUM+3e6mv17aLp9erUM+3e0KhXjuj74enCsMmMrWiMpMnZbpvXHs9quU6uJdKsT5Iybf+PP5wBD3Jb7q+Qst/pibOY5g78FFYjfLfu27J8j8xLz8XkTK9W8S+5ks84JfXpt7ZCmLeLNLPPO/0pxP4KtTnoR5mSriVeTo82FI2bW7OnTSrIMu01rw+QMznRpq4NYFzmllOffIGqlc41ew=
*/