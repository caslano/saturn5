/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
n601QWOJJqVUrQerXLAorGYqiwSTYTVbSJ6EVUo6GZRbhN1Cyq2Ero0RWAvaepP6ImdZPUit8g3uOEuqZAdv51yurErHrz5YV0oMuZuTj9IFxFeDhkfsmPbIDnacXiTcB+oZ0H8XS9ulE07EgOpx9wDL8tA7h8/NZpUDvaU41ANqMPDPtC8+O/I/90KogF6nqNmsVMlnq2rPqvpaOe58Xl8Gczg8w7kJPlMnn2H3xPU5+zG1jmTOw6qpFRL7Om1kclXLnet8yE8zYDp9nAHB2ua/NEs2jB6UxNbQz02gyfhBR+6sftxAFMpzJcKyuMzceK7qYQGeb4uBNQeqxuJh2LUYLIBg+8EGDBYdddXufPiWyY3ZvWDiwSSOkEsDA7zPOKHYpQmBDHXZFsEgL7MMimon2selCbccxTOOK5QDWxupcK21aPnBV1noRp8V/O0t1Uldjfm0ua7pOr63OqUbuut3V0Nt4kq4of+ulf20XW3L21ecz4/r5fRxW3C32sNxf6vP3nfwb6ndjWlAmzIlOHOlSbpCexeh3q8LHrvmL3JcVn3GDvDaaXfWeZK5LdmuxTQxvN7pzrzv38xk318i/9uGdNvu/vOCgmkZnB+9rJNAO/f8Z4GXTtzFtCKkgbiCEF8PMH3lZF+x9OTg
*/