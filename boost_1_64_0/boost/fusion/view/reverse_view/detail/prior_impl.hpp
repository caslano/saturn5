/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_07202005_0857)
#define FUSION_PRIOR_IMPL_07202005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct prior_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename next_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* prior_impl.hpp
LAv3UXetI+389VjAM+Q8LqDq4wGnYm6lys7Fo7Lz9j0vWMbGy4ulCEDo79sIGLgD/KDq1RqVVlAayG/peThHRPeOetRHVz61kvSsfibzvb1QCtMsISgbSh8enCZLqbAS63FcMu2gMy5qElt8dsV7Z1B7W/crruZY6zctJpV0iDwVw3ES8+7ZRR9Zo5L1THliYWm6j24SbFk6YE5G5UY/kzC+/mk7CvWS1SEsde1XfPVRZm3eAYMfaDGqr8NvE3eaa8TgLcCK+4LhTGO27sbsoaV8DzmEkKS4vCIDwOlnqsALwfjY4pxd9McWvPlBIZVZWFGxkEgJgPxacw1zFZHDRno4l7aJVqUa91tWiQivRPHZzQKaMRTf1l9+0imBkAKsCB5iOY5Ih5RFWUtxrYxNHBT36830I3AQmU6D4d8+PkYvCMUx4+d2+Ehcug5Ll28nxESVqL4JEmlNqHCon3E2EQCDW5wYqOiRXOnVI7m+hgFS4w8F+X878q51Ot783wyAA1nJCn9kh+obnRiydHoxEjS6ivOGmwVoJg2IbRKMlgjlRGB+rRmHLfBYJw==
*/