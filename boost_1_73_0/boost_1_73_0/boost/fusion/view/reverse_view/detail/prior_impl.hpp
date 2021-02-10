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
BCBvypfVqi5hh8Mkk6WpFjJTccKKYsmSz50urLg1QN94UpdbwjY8nbhITi63VJCxzTVnaadLcrB8cbMRtNtCYOESNhxWyjqUOKzkFDrIJpV91t0BxthjibHMYtkzvarWXFpCDipSX6Hx/GpICQw9IGeVTAiMwbLP7nCA2khEtlyUDTQdOolwbrA5hKhEaTppRNFYRIkmGXW3OJvMMQhJfoBo3DGyFUeY5po51YVKPhsHrZX073eYo4A8SFTKH4o5VkGFbd7tcjz+0CNjwuDH8wKgqbYO2OO0hzqagPSY6AZfg/ZuKk2ModdkBvaIU5hcXVycIFHjBsasKizu0Moonr47CXCbbD5+Q/bwvsOwfp3M09pIRyWyzt2EwumOpgtfnStIhrbVH+6zFk9nqNt46wx2azFF3xGFvmIupsN38dlgMYgxG4drA6cynmPLuhh1nVF0eV+dQJc6F6VaIBM/DvBd1+mwUMX/Kl+ptO2e/LzXvuoe9HvvHsp6hi7uQ4oDIXZ5HFd8i6fSpqGj4ExWpatojU1PS3AARWXcUp9pznd1RKk6abZvV8fVIp6+jd+P3k9n1zuq78H+yQvDG6seZyam7/fXm08hPslr9G5O06LfUZLDYnY18qDpzvghgmDjTXBMsW4IW3IawFJY
*/