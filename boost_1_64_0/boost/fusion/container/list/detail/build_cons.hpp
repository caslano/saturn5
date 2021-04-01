/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BUILD_CONS_09232005_1222)
#define FUSION_BUILD_CONS_09232005_1222

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_cons;

    template <typename First, typename Last>
    struct build_cons<First, Last, true>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_
        call(First const&, Last const&)
        {
            return nil_();
        }
    };

    template <typename First, typename Last>
    struct build_cons<First, Last, false>
    {
        typedef
            build_cons<typename result_of::next<First>::type, Last>
        next_build_cons;

        typedef cons<
            typename result_of::value_of<First>::type
          , typename next_build_cons::type> 
        type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_cons::call(fusion::next(f), l));
        }
    };

}}}

#endif

/* build_cons.hpp
ApQ9Y1rS1jog6tVBQrIGn3n7N+7UQ0WedPaFviV2//ngub7q2tynOZQC2uTu+LfRm3xJUV7GZpgVwx8vL3ChZp0wzu+pryUNqckzRsvdP46amo+MIgmEi7k/vMLBx4eBJY6txXfKANWP1648Lt3WYQNAeIqJDiPNHQeFsKYdX+QFkYWs6LNI714OFkE7nTMxe0+xy8xR4dhDTQOOJ1uA9jJcsj8iJdLWF6NCVJEv3muXtMg7RWgejbhoU6IbkKrBBOEJosF8mwdvJ9MPW1xX6zu3Pbcw0lV5Q8y19CYCjUB9MugLQu6hFzxO7F6aNgwFPAr6s+8Mx0PZz3jPVDS73rKxodmhwGFtQLsdqYvjuGGj/cOFoXG8jVUgih0dto1l5gbteL4y14U7bEnDQaYMcDrjskZSnrwDPud1ihr0GIwtZjz2EjSijLSQEUPOmMl1Q4shNhFHh5A0aEl9vp/z1MBisT4r2QoqQbXo42akPHZNrET/7mBQvJrLgIhX61R9eridt+2Gnc58oTVhzwFG/zHbiGphQrk2woRmcIvWGA2GWLZ+yrkTHHZpQQ==
*/