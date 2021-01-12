/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
h2PUD8G8fYW6Hez3jBa1R+vj4Ls/om5IZ81Vz7iQ9hOXJ2eZ9nNzifYzkwn20DuXSJp0knMrDo3F5mQ9t2JxgTOyjnfOOMIvvzm34inUF1nm+zEj9yWEOB4OR3og+i0Z99iZNXOzTj4oZEa4Fqqa90X8VumPHE4wZ2GY55Fqw7Bv2Gr7S1+L1zk+4uD89oEF10P2pKIn/SE9b+K0rrebfo7oS18mqRL6po+j/Wv0ae9K7M0q
*/