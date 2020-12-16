/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_11062014_1726
#define FUSION_SET_11062014_1726

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/is_same_size.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/container/set/detail/begin_impl.hpp>
#include <boost/fusion/container/set/detail/end_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_impl.hpp>
#include <boost/fusion/container/set/detail/deref_data_impl.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>
#include <boost/fusion/container/set/detail/key_of_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    template <>
    struct set<> : sequence_base<set<> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<> storage_type;

        typedef storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler,
            typename enable_if<detail::is_same_size<Sequence, storage_type>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:
        storage_type data;
    };

    template <typename ...T>
    struct set : sequence_base<set<T...> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<T...> storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        set(Sequence&& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler,
            typename enable_if<detail::is_same_size<Sequence, storage_type>, detail::enabler_>::type = detail::enabler)
            : data(std::forward<Sequence>(rhs)) {}

        template <typename ...U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit
        set(U&& ...args)
            : data(std::forward<U>(args)...) {}

        template <typename U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(U&& rhs)
        {
            data = std::forward<U>(rhs);
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:
        storage_type data;
    };

}}

#endif
#endif



/* set.hpp
vqHv0FsW2hUPYSM8jPb2lGMBTDVpzxckvhexBe6UOP+OffAlHIov4zjcJfG9osZFOu86rj0S116J63VNH4dIma4vKd/Qx+EjieuUxPWxxPWJxPWp5vuzQebTwbi+yb1TtfAbbILfYns8p4m/WKb3MIm/OfkUW2AVbKmZ7vwVpvOV6drIdH7qdLJPBzVNpguyyL0lWAO7OqYrJ/tl9v01pkNlunLSN9cifXOxEw7DbjhcltsITMAoTMdROAej8U4cjU/jGNyLMXgQx+F7OAE/wYn4LU6SZ+XGYX1MwJY4GVtjIgZhEvbFZByNKRiPU3ARTsUlmI73YgY+glbcjbfiXszBLzEXq1L32/AmnIl1cA5641xsivPU9Uz2EbGdyXrWXtq7g7R3R2yCnbEtsrykj5Ls78l+YL6hj1Kw3KsZgn7YE/2xF4ZgXxyIoRiNYZiA4ZiO/XEuDsAFOBB3smJslP4wrvrC+B30sAwlXeL/+fx9ai8kbSSZ9Y/x6W3vIxOKZv1k8q/QV8ZP+sv0wgl93O83c4b/e/ZlOlI0KUf60azBikqfGTT2pymWPjWWUP6OPqjtWxMR6rp/zWaTPjanQimTZOxrEyz9bWLRSrpSv5vNfHaYtJH/n0dHH5x6/cz74WyQvjinSR5hmj45YVfulxMR5uybM4H/55EcfXTWhOn76RSGMQ3J0V/ndJi+z05k+NX77Xj2d/bdCUdH/51lWEgqIhn78ngMcK8/T5qmT08+f9tMOkw6QzLr4+M90NnPJ5o019Hfx9Dnp4j3l/AS1ovQ9v8hRTj7AMXy/5mkAukLVIiHlffK3/keFZC2k4pJHm/R34YUS8ojbSAdJl0keR/imYOkNNIy0nbScdJFkvfhsr42Za+yV9mr7GX++sue/8eJtRvz/L/xmmv23uWc5/Yrybn9+5QxPA9pzwcmJmTYTuqX/vyj5nq77vz2Oilvu1wPf07Ky9OXN5UpqXDpxzjTlqecP2x72L5/u9twPb5Veee116py7XUveayHteXL6Nc8qSHbjXOu+vOfxmc+ZMtYifpr9DHYEKPwdeLYoI+Da01XP08t1/8ov+Rz6Mo5xo+W5/L5Uf8iUhqFrDrifC6fv8mY57bnMkqefdLPYYzh/bmj9vdvyPvPj6nvTZ+ZOFGWeyzpTeWad5G2vkm5pXkWRAPDMpdrknKdTnceXheDv1x3Hy/jU47B31kBIt/WxpBSqmco1ZQYpCzD+NKp9rZ5W99WAe/Ie8M6uV3ielDa5l7SZeLyfFcblzyHIZnaujE+LfHpvhez35Xz6oYY/EyetbdfWT6GGHL87Rc63bkWoV6zMVxX3GBS5gHKPF+yTOUiqtT9+sttZPKcvYOU63ncWK5coFWKvY76Otp4WeWS18Xeolx/Q7n251/Ynnxx3WVaTJ61d4gyI0uUmZyRaN/iXXOZjm281VimbOOtxjJvUHneHs4+FT4k23081LFAVx7TBU7OTSnF9kX3m6K7nqV7loi63Z1WW/nMqszcZBx8/TYoR3Ntv4ZcTz+qrAMnDNcpS9EPTPd8GLlGfz9J+WAV6ZiynI3zjZs8y/mwmtKP66g+l8ZsOyvX8A7Yy7IUtdYvn10S2ycy1uZJ0jvK9+09bWyZiTmBtLUby8fkeqM8Y8W2KEyes2K2fPSxJsn194dJ3rJNvkfZH3rfGKuySXI3Vtt2uNSxKm26z16u5V3Ds4nOS5x95TpuD6UM8lg+0MRpfLJWKdYp189ncd1m6+R6/1aJ5RnSe8q6p4+F9lK+gKVvM2OfzQiT75qf9NnUtqOPrh31sYZXL7l8C5Tle7JErJmJboxZbxIrcZVi+drLtbxv+D0+LHGGyDgkXWQ=
*/