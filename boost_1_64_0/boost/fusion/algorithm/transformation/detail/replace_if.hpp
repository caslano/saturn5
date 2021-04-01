/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0946)
#define FUSION_REPLACE_IF_08182005_0946

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_if_helper;

    template <>
    struct replacer_if_helper<false>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_if_helper<true>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }
    };

    template <typename F, typename T>
    struct replacer_if
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

        template<typename Params>
        struct result;

        template <typename F1, typename T1, typename U>
        struct result<replacer_if<F1, T1>(U)>
        {
            typedef typename remove_reference<U>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

        F f;
        T new_value;
    };
}}}

#endif


/* replace_if.hpp
ZlUnDZXQkwpNYbN05WTWKGBJrjJp0W5somDCmMq1UHMyrEIPMGoczF7qevVd2fXDRnPLwg8TKFNo7/nrMq+SE7sR9bi+v8NjZCuHT5N2F4KhLKxvY9CKxwPm2DCmn7wf258d9KLE74OkH5qXdBJgh9DVlI3jx1itrvaicHO6i/xJ5hmm7Yu4Da/JwGhGwg+wRWnu3pJVmmvYtxZ9Sun18od1n45aTJ+yyf3+oVwlOiFj5x2iHcqT2nDVK+Xbh18eomqDHC0YDHJtdV29RQeUls+64a+j1HaCQzcUGXUGOHlUIQdatGBSSnU/pNK8yZ1RlBnKUVoR/6OLYUUhaH6GAP3eH/CgMfVHT1aDrO2nooaRhEsTKvP0XHdYKZnNd88+4pbT7gxpiYNVoASnpQkkwv7kpb+SXNvyWDy/yMZEsUegg/Uk+lZoJ0tirALbKO1wwawso3AX4opGWwgZgyl0/BJREg5+A5iSYR1ira1Cn/V2HifzD6E9iLd9aoFBFEilKpD7jUnSPc98klRkKODSgF88UZjFXjiVL9uTD6alsZbS7T3dONd9zt9Vmw==
*/