/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
sfmd15U97MGFOzgRa3zdGLk2owxtmStXBdEncQCJILJIFU0FY8QKvfYMkrRblkBXf42W9BtuRF6hI1WjmcuaO/c7Mpp+ZAndWw4+TOeh5wYnbNy0JLUtCTnNyvyOQDSS0aadqtIEiVVhZUGBHV/vdZe3zaKq23ipdM11jf9WaOyOEXUTUPJqWvPpyeV47LtSt5muW5EoGCMmhud3ZSpqX46rKi4o4yTq6arW216jLefB5Tj02KFbmM2n4XQwHS887km3NPw7+DQbDx+JaH+rpMYSyWP2DlsdWx5UUatbCXV19f7z6HXt+GE/bdlY2/TpiNXwbr8nus5d59Pdialojp+IDRq1xpMGw+sWzImxVZp2SEyh5cKBur/xvtViDscOy7t7gk5SZbtkL9MuLx5Bg3vRqBNbNZxvilfj3hsJvLAbBfQg/O1bEt4KmtzYi9W6X4OlCBO1ceWnBhBO96unuZ5dhj6cjnlAOT+BMdWambfBumvFbibYTDTt1WSH7+HE1qk2xeRXH8+97I7djen81nrJdxYJVfxJwObD4Gw3+xrLGuYBwrTC8c4RnnOyW9nnQ7NHOQ1bCnyPHC0bzIM6H0TMbXBBqIdzv42+TWtLgG0v8xzkNO/m+BNysvdKsOuibaQZapbN+xzzHX5X
*/