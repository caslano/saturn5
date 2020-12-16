/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std_array_size<seq_type>::value;
                typedef std_array_iterator<Sequence, size> type;

                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
saA8XWO6l+paeokxXUNtuHz+84ksucRyIhFqBn85GTAH7qOMO/14YPd4fB9nAvhNCL+J4Lcu+GRi+Pev5rO1W0OjC9D/1gdfw70byHMscSaH3zhT0tX4JPAT3FhYD1PAUSKdF2O/7dRwKLH+0DljZHhMKZTX5L68Zue8pqK8RJzunmVVdpG8Yj+PjL+syYtz8mzALQmaGfAOBGFjANsTjhcwsOUAexCOZzaw5Vk3p4GtCtgccJJ/byzE/th5tN50wCkBn8zo88n0bNNqbFPZIXMCuDJT+mAtxj2nJeOIW/NRPMRV/B+qU6cUVaezR7affspPxFFlFf4bAHxz8N2By0KbZ5+uzdgBgxrLM/bYohpbh7HPDGw9xs5NaWxjwC4FbGAsjZUA+xGOU+NobDPWvW9prAnYWjC7nMnAtuG4r4+tsQM535uNMh/GuquMuEcDdjTEe9jAzgDsAcDuNbCzAfsZsCkN7EI46B7HX5bLxL0xwBY0sGs5jzsN7FbAbgLdkgZ2G+f7kIHdHpHe3dzGXzf891hEHk9GpPeKae8f7B/uqBPRvpaPHDNe4/Y17IpoqokFxy9B/qnxq+p6pXBfXTmyr77FedUbLbde8/5QPvXIcTIRafM7Mh/fOPnH5vJbN4uNsF2pyD78HufXrolYOFyEOMnI8fYDca0JF0uHgmYibhMbTUXY9WNpbGPGrhW639tOvFr3UBGqvOW1mmCE34a1fDbMzeW0IZ9EPtttwx0DcW8ok13dLm3mlLYwNMUIzajTgoz0+FoKa8RYask0nCg+kIYLmlKPawd0iq8A7/aUQrzw15bArTwu9dOJ/5i/ypDlSCPkr0JknW/DdohYUPi69blu5zsxxymqcu8mcbflVFVE3W73MHmObJ6/9wZelBWpplMsi/hyXASuBXZnQDcJY5cDdi5gbxjY86yrGNjbrHMM7DPWzWFgY09N2IqAHTGme6yZV1xkg7HENcdKW1ww7Ty39N90w6lP7LPWQZNZHMbCnz+8sPYSY1lxiEMc4hCHOMQhDnGIQxziEIc4xOFfEcaF34bWWFOJv+GZi1gT6A2JJ9Sbud5QotFIwYLPoT6x/HKo4FQbQ5XaFtsnupZYomfpxDKLLbf0aksvtmRyteRiyyUS6cVW6+5aYtneJbqWWWKZnh3HtKoNcb/GWnGqCeH+6CMqx8nhfs71RcvSXx5YMLfQnMl1YSEUfHDgOGulqazS1uW/76G75Wzj/PnlA1u1YKnlGEhC7FGA34zwyywK963Hyi3UnuKKb2pzDc/0xqs37bTbOlYc4hCHOMQhDnGIQxziEIc4xCEO/9gwLvxm5ut/WEdMKylgLS1c8jYsvn6fwJrwN6/fxappy/rHXb9X3NoWePUuwuzWslONBf8mksl0Pg/Lg/PJXGawIDYdjTQdB/mxo3m3xfHHieZrztbgR+DHtSLXaVnTAzeeFVpjinHGtyLXgyI3gcFphrgJNbesyU0N3ERWYD0lYBNboTWKqJ1E4jWtnZQwNkKXdTIrak0W5Tm55VsXhvoprMh1mshNaUWu0cT8p7JCa7EQn5pxiUpfTCPwfKY80MwVa6MOVahFcaYNcC7Xx3R+XFQi1vH0jMMOW3fEdZrJzepuydFtZIZIXreRGSN53UZmCvAeJk3czCHOVfU9S5ATSXJ9z2rxmqNEdgOIguWYzeqwFozLOXuYp5IwP4fVcZ0YlmfOMI+lnRu4uSK4WrEKe7ibbo3b9txhjaqDeaK4dtUueiWMO68Vuf4M484XzYm4yM8fyWu7FlB8/6DhFuQWNDltMnILGZw2h9rawoobGBC7H2QdLSLxdBb2tIrdpSnKjNNcNMyLOkAfLxbN2eA=
*/