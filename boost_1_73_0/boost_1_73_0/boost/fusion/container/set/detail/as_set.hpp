/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_SET_11062014_2121
#define FUSION_AS_SET_11062014_2121

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size
            , typename = typename detail::make_index_sequence<size>::type>
    struct as_set;

    template <int size, std::size_t ...Indices>
    struct as_set<size, detail::index_sequence<Indices...> >
    {
        template <typename I>
        struct apply
        {
            typedef set<
                typename result_of::value_of<
                    typename result_of::advance_c<I, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif


/* as_set.hpp
WI3pAryV9cNEtl0gDKCBZJycjA9eNoSfUpApDcDZjumdOkCt4PcFY8cRPqajnwJK6mhYO6tQR/gs0rlIY3m5Z65fBZEfbhbYt7NwIWSbS/1sX12SLM1DOvfA33vxJvWCxFuikxY8XHebSYBH7+9ZM9szppjNeLaujSckoQBJglSQBK2AApK5FxEBEqKIa91EY0D1GC+39dRXZyH8/foALJh3EmQqZBw+VlDzS4eAbd2xxrdHYIsWcNGNTotcy/LPHnp+6RB41fgA3p/QFJf7dguhre1+q86FlPnxOoERTcvysWTjccOOjvtMc64qsc/DVn9dBbMGGq5IUIIWBdkfairISrRZQ0WwZk/x6sswhqmOP14yLI2pomwbBfMavw8zHQlcsgXENQ+B7TerfSkw8Sgi9hRkKwjXFzBUcLs6QKauD72JNoauEGfmWqzj9LlX3BN9Ytl3tGIThBOLVvNRQYRwYnhFBsQY5TxotSB1VBWoGOZx0Jl/qG68p/kluDugFo4V10sK154xqnMMaKbh4cK6Wg2BbJNQH6q1KJgsc74oriZ6Ko9uQ7H2UjlvqA96nbnqbpyISMrwnFySBSZNxxkfLs02HiCMackFrbJaUmivsFbvHkE8EesjiE/1SQfx/O4xxB98+e7iGPqf
*/