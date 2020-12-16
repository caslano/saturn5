/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM)
#define BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<nview_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::begin<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif


/* begin_impl.hpp
9oCIcyvZJ9GueclR70+TSFjxz4kAn0Vf4hE5oAcXKcD9+f1+1KNe2dTBzknh8pHrQ7SnMAYBrn87zCMugj3hYstP7D5ltR4tkKEMzruGQGKojHJTMAiQrTzCI56ENdF6/2+aMhVWwnwpUuA8muVuhCaR8mKEA8NB2scefvu4SpnvhP4iTI/jhQ0e0QnWgsEKEDjnxEF6NE9OtGu+xTOthxaBhP4iTI/9g2uj/F+K+He3DP+E/hFMj9fB0R4xAPgfYuUldZn5th7NlRvtyDFHD3ZDIPERpMER03N1TFQPLkN6kNMyekAZOHLMb+5C3egR6cD/5VaOXofR4Cdny0n8/NPGTWF+5CePjX7/V6Dv3yVn8PNfGwwFKLPTEAZjDzhkMBTJIEsesM/Vkpj85CrydaDZGtD3No8Ig29wpRUr8hZA7kGmXGbX+OOyh6qsSoz1ZHe+HBhwrGRSVAeuQjqQIafzvwejQpT8w+wmL+te5RMA7yUKcNnTj0MF+HSZkgz5eVy+YXVpFeXZKUyP/cJpHnM/+Gp0PzhNjouHP0zkqAWvCAwVqyoxIcLEAoMA59c87BHfwxpQqgCF3oXAeaocZ+tAMpMOAImEloDBgGyheR5xP+hBmQIMKl4yDm4Ay3ESforn0gN1xk0YKYPpsU80P8q/TwG2VOTO1KPJcjw//6SRwn+LEw58yiOuAf79ClAaXv6BHk2SA1rBfVeuWClxdAimx+vgWx7hA/4DCjBrXsOrsPjJcXa9Y77vvyZE1XbfMT+yhZdF+S9H/CfISuB/ER//4UApoS8A86P8snc8Ih9ig8MU4PLny7ZDvU7ZMU6AKLj2AMqi32Z+bAet9IgvIS5YEcmzvARqQcTJPOC/icsGDJUoEzVYThgXNBiQDqz2iHtABkHLH14aaif0qDwAeSTtUpl8oVDkIkE5pRY4MRhbaJPH3OG9RgFGj+tzp71M7kuCXDouf1BTSPomODGY+OBWtReCHgxXzy7LU/pB1FjUHQk+oUdll/DJgHY//I87K9kyXywBu7jSAkzdBPGhv0QoEfxCrrs7YfUzpWsA86P4WOt8sQL2hCoFuG3TS+s0h3+Kjm44PcvguMfbUOIvraNKqjSTozsZXfPFlbAOVCvAE0snAccHRB/gdjpHTqmV4aT+o+yYiVDEyqFbvngE5FCjALV7B3+jR/8QjUkQK+eoXQtEUnZKQihi14Je+eJnkENIAZ4fUAzvwn6xJgX+MJXhLjMQWUrkH5npY/3D0/NFdo7mf4QCvOS56Dw9+ruY5cixldT8W9nPQ4PqxhCRAGLmN/5RXb5YCv2BahXgxeq9J8JOKOyemc9JRv7LyS70OzFg+/D6fDEf9oOwAiSNH3aW5nKvaLLr0go+GQR8REZBzPwmRjA2X2xK1PzXKcA9PTpBx9g9YgjoQH9GHagh1wHA4LQJbs8X5aADIxVg1V33QD7Vb6LCrkUbxyeDMFn6BEKAayjel2/6G9QrgL973456dLeoKIB86yyGPZGuCK+Z2bz7s/PNOcEoBfj00pKFmqtfxW6IERdy3DFQ7euGVpA1yTOzozPCZ/NNDmEDyiH8Rdg5hNbZQToH7+pDl0OIEOD44HPR7/9aBZjt2Xi4Hv1Z9LHrnXF9/3WV4W4lIap+aM0wGFt4Sb7pmTtaATadXnYCnBCLtcB1SiKDP1RZURquUP+XhOtK64gOzDAOvAcsyxfJEB+4Tj1TGkrBAv5JtLXzCFMZemYCjep/Io8AIcC51R8r/xB6/FyvAAcerajXoztFXSLUektiyCtW6V3Wp8Q/jOpGshMDPjf/PV+8BO/DDQqw5Ny+x2gufxR+WBfHcqyLNoU11UT5pAgB9os=
*/