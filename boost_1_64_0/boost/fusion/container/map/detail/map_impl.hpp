/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_IMPL_02032013_2233)
#define BOOST_FUSION_MAP_IMPL_02032013_2233

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    struct map_impl_from_iterator {};

    template <int index, typename ...T>
    struct map_impl;

    template <int index_>
    struct map_impl<index_>
    {
        typedef fusion_sequence_tag tag;
        static int const index = index_;
        static int const size = 0;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl() BOOST_NOEXCEPT {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Iterator const&, map_impl_from_iterator) BOOST_NOEXCEPT
        {}

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign(Iterator const&, map_impl_from_iterator) BOOST_NOEXCEPT
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get();
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get_val();
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void get_key();
    };

    template <int index_, typename Pair, typename ...T>
    struct map_impl<index_, Pair, T...> : map_impl<index_ + 1, T...>
    {
        typedef fusion_sequence_tag tag;
        typedef map_impl<index_+1, T...> rest_type;

        using rest_type::get;
        using rest_type::get_val;
        using rest_type::get_key;

        static int const index = index_;
        static int const size = rest_type::size + 1;

        typedef Pair pair_type;
        typedef typename Pair::first_type key_type;
        typedef typename Pair::second_type value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl()
          : rest_type(), element()
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl const& rhs)
          : rest_type(rhs.get_base()), element(rhs.element)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl&& rhs)
          : rest_type(BOOST_FUSION_FWD_ELEM(rest_type, *static_cast<rest_type*>(&rhs)))
          , element(BOOST_FUSION_FWD_ELEM(Pair, rhs.element))
        {}

        template <typename ...U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(map_impl<index, U...> const& rhs)
          : rest_type(rhs.get_base()), element(rhs.element)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(typename detail::call_param<Pair>::type element_
          , typename detail::call_param<T>::type... rest)
          : rest_type(rest...), element(element_)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Pair&& element_, T&&... rest)
          : rest_type(BOOST_FUSION_FWD_ELEM(T, rest)...)
          , element(BOOST_FUSION_FWD_ELEM(Pair, element_))
        {}

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl(Iterator const& iter, map_impl_from_iterator fi)
          : rest_type(fusion::next(iter), fi)
          , element(*iter)
        {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        rest_type& get_base()
        {
            return *this;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        rest_type const& get_base() const
        {
            return *this;
        }

        BOOST_FUSION_GPU_ENABLED
        mpl::identity<value_type> get_val(mpl::identity<key_type>) const;
        BOOST_FUSION_GPU_ENABLED
        pair_type get_val(mpl::int_<index>) const;

        BOOST_FUSION_GPU_ENABLED
        mpl::identity<key_type> get_key(mpl::int_<index>);
        BOOST_FUSION_GPU_ENABLED
        mpl::identity<key_type> get_key(mpl::int_<index>) const;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename cref_result<value_type>::type
        get(mpl::identity<key_type>) const
        {
            return element.second;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename ref_result<value_type>::type
        get(mpl::identity<key_type>)
        {
            return element.second;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename cref_result<pair_type>::type
        get(mpl::int_<index>) const
        {
            return element;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename ref_result<pair_type>::type
        get(mpl::int_<index>)
        {
            return element;
        }

        template <typename ...U>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl<index, U...> const& rhs)
        {
            rest_type::operator=(rhs);
            element = rhs.element;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl const& rhs)
        {
            rest_type::operator=(rhs);
            element = rhs.element;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        map_impl& operator=(map_impl&& rhs)
        {
            rest_type::operator=(std::forward<map_impl>(rhs));
            element = BOOST_FUSION_FWD_ELEM(Pair, rhs.element);
            return *this;
        }

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        void assign(Iterator const& iter, map_impl_from_iterator fi)
        {
            rest_type::assign(fusion::next(iter), fi);
            element = *iter;
        }

        Pair element;
    };
}}}

#endif

/* map_impl.hpp
5/ADbM/xuhb74joMwg0Yhh/hZNyIL+ImXIybcS1uwY24FffjNjyO2/EM7sD6nAc/xVa4C7vgbgzAvTgcP8MoPIDj8CAm4GF8Bo/gy3gM5+FxXIhf49t4ArfjN3gA8zAPT+KveAqrcZydxtr4LfriWeyI53AYnpfjM9lFfivKb0jl+PRTjkdUpgtyfOajD17E9vgT3oeXcAj+jCPwFzTgFUzEAkzDq/gy/obr8XfcgtdwF/6B+/FPPIs6F7ZHAQvQDSuTp/JYDStiA3THllgJH8LKmIZ34j+wKr6Nd+FyrIY5WB0PYk08ibUwH2vjFawj53VPbI51sS3Ww0j0wgnYAJ/DhjgDG+Ec9MaF2BiXYhPMwqa4Bn0w1bXk8Z9TWrrTj6nkPkxl1X9J1XepTPstFemvdNN9lVT9lErsozS3pXup+yiVRf+ksuybZK9f0sqWjt0zuZ3l8gg6P3edN8GfEEyIIaT6OfsmOSfn5Jyck3NyTs7JOTmn/97pL2n/H92pQ1m2/2fVUrf/E7nO3P6/34H2/7zvaxS2/4+OTIzu1MGh9v+Sxv+/+H2N2zr+f1dJ32CnHT7CnD6F8d/dDu8u7fCt0FvcQZwZZwvzT7ZLHIPX0u4e8522HT6Q15Z2+Ib8L23p1jEGzv3LOs/abn7wfI1iYxaEnS/e5v7hueLt60+f07avd7W+9pe41e3rtscJjrFR1kYs2r6ejEXb1/3xpZsYTz3gBvsolX1iUuKZYrlfPt+yj26ujVzypsqvNt1rku4qSXe5pJt3wZLurbeT20s7SdrolXjrENoTPibt4MLj0jgxKbGU4yeMln2k/oxr0+0ubc0vcaLywuloGp/9mDVda/t8ZgnpZhVJd72N9vkcG+3zoTbamY0yT46/4seapJlUuJxpmZDC4ywWirXrK6/DVG3yVTVjPCRL/ybLsyQmmF4HWl8bpY9BkXHgNX1Uxpra+SPU2xQeNd4Qbe4nkMx+9q3IOhTuspOUsep4kTw9BkX6Djyh7DNT/6hJp2rI2OLa7wVf+aIZh14YjabxEb6w7Edrn4Gb3pdF+wzkFOszYL+vxUv2+wwU2dZY6cvj7DPg7DOg7TOQVdu0X8bOe6xcuQ73nzk+Pqhj+3VLy77PAL/R7PYZ6Cl9BgKwIvZSjSN+UdZ7kHBRd2vjiEcogfjstfnf6UrbFFbFpngXtsNq2BWrYw+sgf2wFo5CT4zEungJP3WR3z7yW0hJpxP/Z6MyrZU2//Xoi9nYGTdhP9yMw3ALjsKtOA+34VLcjqtxB27GT/Ao7sRvcBd+h7vxMu6V8Vc/w1q4Dx/EXByD+3EGfomz8QDOx4O4Dr/CbDyMBXgEKSvdUayJx1CPx7Ej5mE/PIkj8BRG4GmMxTM4Fr/FZ/EsvoTn8CP8Dj/BC7gf8/EQ/oBH8Ef8FS+iKwfST+iDl/EevIJ9sQD74+84DK9hAv6BKXgdn0IX9lsqVsAFWAkzsDJKm738TuJAstFmP1KOwzCsh6OwIYZjK4zAjhiJXTAK+6MBH8FofAzH4CSMwSkYq+o7I7+X+B1VvO9MH0m/vxz/gdgJ78euOAD7YRAOwYEYgYMwDgfjsxiMz+NQfB1DcAkOw+U4HC2f52A5vv1tfJ69KLc62ADbY0Mpx4Jy8htIfhuxnmkb8pWVpW3fC8ehHyZgZ0zEHpiEwTgJo3EyJiPB2rb/CqbgAnwSM/Ep/ACfxi3Spr8Hp+IRfA7P4XR5JvXz6I9p2BdfwGCcgbNxJm7BWbgTX8RT+BIW4Mvy7Ol0bICvoC++ih1wPnbHBfgA/hMfwjdxJGbg6/g2/hMX4xJchhsxE3fictyPK/AIvocncRWextV4HtfgNfw=
*/