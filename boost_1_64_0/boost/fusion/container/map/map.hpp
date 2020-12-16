/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_MAIN_07212005_1106)
#define FUSION_MAP_MAIN_07212005_1106

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/support/pair.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/map_impl.hpp>
#include <boost/fusion/container/map/detail/begin_impl.hpp>
#include <boost/fusion/container/map/detail/end_impl.hpp>
#include <boost/fusion/container/map/detail/at_impl.hpp>
#include <boost/fusion/container/map/detail/at_key_impl.hpp>
#include <boost/fusion/container/map/detail/value_at_impl.hpp>
#include <boost/fusion/container/map/detail/value_at_key_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>

#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    template <typename ...T>
    struct map : detail::map_impl<0, T...>, sequence_base<map<T...>>
    {
        typedef map_tag fusion_tag;
        typedef detail::map_impl<0, T...> base_type;

        struct category : random_access_traversal_tag, associative_tag {};
        typedef mpl::int_<base_type::size> size;
        typedef mpl::false_ is_view;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map const& seq)
          : base_type(seq.base())
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(map&& seq)
          : base_type(std::forward<map>(seq))
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence const& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename Sequence, typename = typename enable_if<traits::is_sequence<Sequence>>::type>
        BOOST_FUSION_GPU_ENABLED
        map(Sequence&& seq)
          : base_type(begin(seq), detail::map_impl_from_iterator())
        {}

        template <typename First, typename ...T_>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map(First const& first, T_ const&... rest)
          : base_type(first, rest...)
        {}

        template <typename First, typename ...T_>
        BOOST_FUSION_GPU_ENABLED
        map(First&& first, T_&&... rest)
          : base_type(BOOST_FUSION_FWD_ELEM(First, first), BOOST_FUSION_FWD_ELEM(T_, rest)...)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map const& rhs)
        {
            base_type::operator=(rhs.base());
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map& operator=(map&& rhs)
        {
            base_type::operator=(std::forward<base_type>(rhs.base()));
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename enable_if<traits::is_sequence<Sequence>, map&>::type
        operator=(Sequence const& seq)
        {
            base().assign(begin(seq), detail::map_impl_from_iterator());
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        base_type& base() BOOST_NOEXCEPT { return *this; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        base_type const& base() const BOOST_NOEXCEPT { return *this; }
    };
}}

#endif
#endif

/* map.hpp
8DNMxs8xDb9EeW+ftKOhfY1879Xv7ftaSQe/QSN+i8FYhAPxOxyNVbzYXlhVvn/V8SjeJt9Db/ke1sBvsCY2I61a2AFvx65YW+rnFYK0j6HdTHG+/JTjRclXPeYzt0fBXuiHw7EhzsRGmIONcRU2wb14B57DAKxMnC0wDO/EsdgKl2AbfAqN8n1vi29jECr1qQMOwI6YhZ1wIXbGPOyC27Erjib/PXAa9sTnMBj3YAgexd54DPtK+Xe4SVsYaSND+TXv4dwn++P9sj/Ox374Oo7CA/gSvoFv4Jv4Hr6FX+Db+CO+g2OI+12chO/hfCzAxfg+rsZj+DQeRx/ycxKb4GlsjmfQ8r5FN8n387K/V79vcYfke6fk+wXsgbvwCXwJ83APmtt7qOI13KUf7waJd6PEu1ni3SLxbpV4n5F4t6H87knbC7axg9+9TyTeT7ENFkq8n+FgPIe78ALWZdmL2By/xkD8xpqOtIeQdhK26cyXdHIwCBfiXbhY0lmCd+MyXInL8WN8GD/DRySdTHdpgyBtE0jH/B6MRFSGhEqkg/diO0zEuzAJB2EKjkETzsFUfAjTcDWm41bMwN04Bc/iVPwcM1FJfBrWwvvRDxfiUlyKK3EZPoHLcQPmogf1aD1Wx41YCzdhM9yMbfBFfApfwWfwVdyOe/FFPIJ1bqE+Y2N8H1vhMQzC4xiCJ3AYfoD34ClchacxF8/gc/gRvoAf4xn8BL/EQryC/8Jf8DzKdpY2CPwmO9jOP7KdauJl2d4/YQu8gq3wZ+yDv+A4/BWn41XMwt9kOxdUIEg6Pl7F6Sj146C8n827Ir/fWAODsCZGoQ+m4O04E2vjY1gHn0Nf3I918SjWw7NYHz/HhliEjfAnbIxKvW+C7bEpDkd/nI534EJshg9hAG7AFrgdA/EYtsLT2BpvpQxtsAEasTm2x7HYAaOxIz6CnXAtdsMt2B3fw3/gJ9gDL2BvJV62Ux+siX3RD/thMA7AbByIi3AQPoGhuBGHYj6G4SEchj/gcFQu8I3ApjgSJ+EYXIxjcTXeg5swEo9hFJ7GaGQdu03AvhiDozAWIzEeEzABTXgvrsfJuAuTsEIlji+xMqaiN6ZhfczAQJyC7XAqdsVM7IP34304HdfhTMzD2bgb5+BBzMbjOBc/x3n4Nc7H33EB1vXke45tcTGOxyWYhEvxPlyGa/Eh3IiP4tO4Es312k3aVeB22R/XUeq1m9y7Yr7GuBaNuA6D8UkciLk4Gt/EWXgYn8KjuBPfw5fwhNTvD/ATPCn1+0O8lTRPYT08gy3wI7wTP8Yu+AlGYSHOxX/hCvxM6vd5zMN/S7ni3aW9BYyX/XJL83uc5XxUyvUdtsPvsRv+iOF4GSfgb5iHv+N2dGO/8xVUwCL0QA/irIi+WAkD0RPvwso4EqvgOKyN72E9PIH18ST64acYgMEVyCv2wUCMwdaYjW1wBRpxFQbhNmyHu7EnNleOczAQe2Nr7IOdcBiuwxG4AUfj2zgGayrfG2V5jMAWOB7b4wQMwRgcjrE4GuNkP8xvpLSbQKlH3srvqdSjW2X/Ww2NeBsOwhoYg0H4MHbATdgRT2AXPImRWJE4o9EXJ2A/vBeH4GRMxUScgik4HU2y/86rIG0epC2Ekr/hSv2uINezKkt9wBb4A3bDyzgAf8IR+DNG4y84Ga/i/VixCvUSK+Gj6Imb0Au3YGV8CavgIayKP2M1VM7/q6M/1sYgrIu9sR4Ox/r4APrhCmyAq7ERHkB/PIt34GVshu6UrTk2xQBshS2qSP3CezEQ07EVTsHWmItG3IpB+Dy2w33YHg9jBzyLXfAy9sDKyvE2+mAw9sO7cBj2wkkYguuxD24=
*/