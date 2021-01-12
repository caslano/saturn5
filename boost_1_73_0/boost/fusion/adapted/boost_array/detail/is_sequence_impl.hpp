/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
vearGvfHB16zF9i5tfNjgZnAxU/uA34g9gfg3n1fE7iz3oi3e3d4rxL7X1mZtHLbUubJfN62vC/km48X0HV2RKRVZLqMTzekCy0cae0MSGdrfxh1jhpJN/dFOV7TBDJhbDmYa0h/hztNg7XdkP3c67+PEDdHm31dCsXchfhLkXI2T8M6gkr1RAkrX5qkaG5BOBs4IcyJ9dl9zDUmZZg6Nb+5Be52x9sSnjQ1R8OXIOFbIvbL
*/