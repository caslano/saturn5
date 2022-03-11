/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BOOST_TUPLE_ITERATOR_09262006_1851)
#define FUSION_BOOST_TUPLE_ITERATOR_09262006_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;

    namespace detail
    {
        template <typename T>
        struct boost_tuple_is_empty : mpl::false_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::null_type const> : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> > : mpl::true_ {};

        template <>
        struct boost_tuple_is_empty<tuples::tuple<> const> : mpl::true_ {};
    }

    template <typename Cons>
    struct boost_tuple_iterator_identity;

    template <typename Cons = tuples::null_type>
    struct boost_tuple_iterator
        : iterator_facade<boost_tuple_iterator<Cons>, forward_traversal_tag>
    {
        typedef Cons cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Cons>::type> identity;

        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons& in_cons)
            : cons(in_cons) {}
        Cons& cons;

        template <typename Iterator>
        struct value_of : mpl::identity<typename Iterator::cons_type::head_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename value_of<Iterator>::type element;

            typedef typename
                mpl::if_<
                    is_const<typename Iterator::cons_type>
                  , typename tuples::access_traits<element>::const_type
                  , typename tuples::access_traits<element>::non_const_type
                >::type
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return iter.cons.get_head();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef typename Iterator::cons_type cons_type;
            typedef typename cons_type::tail_type tail_type;

            typedef boost_tuple_iterator<
                typename mpl::eval_if<
                    is_const<cons_type>
                  , add_const<tail_type>
                  , mpl::identity<tail_type>
                >::type>
            type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& iter)
            {
                return type(iter.cons.get_tail());
            }
        };

        template <typename I1, typename I2>
        struct distance;

        // detail
        template <typename I1, typename I2>
        struct lazy_next_distance
        {
            typedef
                typename mpl::plus<
                    mpl::int_<1>,
                    typename distance<
                        typename next<I1>::type,
                        I2
                    >::type
                >::type type;
        };

        template <typename I1, typename I2>
        struct distance
        {
            typedef typename mpl::eval_if<
                boost::is_same<I1, I2>,
                mpl::int_<0>,
                lazy_next_distance<I1, I2>
            >::type type;

            BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct equal_to
            : is_same<typename I1::identity, typename I2::identity>
        {};

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(boost_tuple_iterator& operator= (boost_tuple_iterator const&))
    };

    template <typename Null>
    struct boost_tuple_null_iterator
        : iterator_facade<boost_tuple_iterator<Null>, forward_traversal_tag>
    {
        typedef Null cons_type;

        typedef boost_tuple_iterator_identity<
            typename add_const<Null>::type> identity;

        template <typename I1, typename I2>
        struct equal_to
            : mpl::or_<
                is_same<I1, I2>
              , mpl::and_<
                    detail::boost_tuple_is_empty<typename I1::cons_type>
                  , detail::boost_tuple_is_empty<typename I2::cons_type>
                >
            >
        {};
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type>
        : boost_tuple_null_iterator<tuples::null_type>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::null_type const>
        : boost_tuple_null_iterator<tuples::null_type const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> >
        : boost_tuple_null_iterator<tuples::tuple<> >
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };

    template <>
    struct boost_tuple_iterator<tuples::tuple<> const>
        : boost_tuple_null_iterator<tuples::tuple<> const>
    {
        template <typename Cons>
        BOOST_FUSION_GPU_ENABLED
        explicit boost_tuple_iterator(Cons const&) {}
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Cons>
    struct iterator_traits< ::boost::fusion::boost_tuple_iterator<Cons> >
    { };
}
#endif

#endif



/* boost_tuple_iterator.hpp
5xhec09q6Odl6kCb6xd71cfNzG2Hj8atSd6NzlRvAlRNK07NfbFuhuKGY5CuED9tZhfaBiAApiXE3SLYnRtsex+ADidQ9gXwiXZAAlQ+LTqFPBBTUSAHIMEjsAVeP9s6H3Ud79fxZw68NHacuZwevjbHtq9FQYN5c3UDcVezUkYCZQx3PzT0E+z9iKexAbfn226Vuz+v+/FQxKJ8adw2RgbHImv73798WlrbCRn6GfGJtDGc/ajBf78sOeBhpgFt6llP/Gt1vo+vzl/I5Xhyczv5mHze9waKnp6MSUdwMTFVISHXkSYA6diD5YoOHTC40zMCB56Tmftyub/3hx8PzxMuibfLujLjVtSjU47cTEpVSKkaSfbBPaIVuDw/+IJjOgZWDP/1pcl/epk9H/5rGFPuWQ3bnMWp5tNS9ygnKWJmbqASzKRFxNkDC1646+WAAQP7ipL5cTK7+jK6PZxIvRxiNeeOilsxj0EldzUZrzoYahrJ9qi1p5iJChU2MEg1+FPzcOxPB/vt1Hn5ZbRYNFF5+UfUnKsJ/UJJLBIV97yw0kMwlYMhVhiq4ODMLpaOIbwjVOfm9Vjm8GNkUjxJdDWscdallGYJH4M61cUkWIWsvkn0ERjnVoFqdHUGDxjYevxHr/LtWuX8w9gzjmyhFp4s5zxcuzwJhwruetpAffTDPCLiH86LAlVibJPgZkYmpg2u5E+P4utDRbb7mEocGXIdPJWcuwSalbB4VPv1eaDqvyWaBHOcMVEJ1/wuTaOraNajPjYV/jwZH2+VfxZEFxsGw+duA0K01sXjdbwxSp791MrRvP2CwQrXZ3YnGF053Z+roiNz1oq3sWJ8XETdbP18i7Ppdf9w6Uhciz1Vhw2ZRcc5Wn0hlhNjWUfWboCx7ZKe/uatvtrHOeLFguvi5ufZlU2vHohDOV6f06U43skkCNNgYwmxlhnCzrtxYd3PRX3vrljYxybiRyPTwXtk27hn1QzAoBNtLPze8JppJI2xpgHhSHjosvDmNRvz341ehtW8FZ0dPFF+ngMX0/5vla5rnZgZiQJTbazi+wDL0nGKVFMEofkSQ3f7hJrdOn85xlfH5b2noO8v4g+6p8vqlvMZtVtMqiVL6WXKuM0UzIoag1uoAov5ei0L7ppr/uFA/1rg3ZUAdvHAj8P+Y8A9E24GdWAYdCBbS4E3QAJmpHBTYEKVgBswgysA2LdbZnd/Psfj68dz8aKo1U5yeVZYGpXmuBM19+IjdQoVzf174Ol4hMa8uirwUTdy+h/X9wv5sbneHD0vDi7fFu8jFeUXH9FDCTvLLqoqpdx4VLII07tgE/1MaDhb4MX4Hz7X57QR5NtSM3y4ON3LC87tNSZ9Pc7MrNWE6tpE6sbBIeM/GQUkSNsjqMbG1q3+l6c/t0lj/nxsX3ZWV/sOc8t/aMuwrdAmocSdmDaSDqlNFqoZDHUcBCAgby+DRtcEBt69NpXN/PV4Pu0qfwYcPlr+PJVhS6NPOok5q1xPNKg2hk8zyOEMsScfif7uWzbVLEf+crFfPtW32yZjhwUblzkl5hfO6FLLRevgXEklqoxB1QhiOH+whIbndbIZW+NzKK23+XFtfbk1PxzqH7XMdyrel0Iag+dtNL2VPEqic1Av8NGj4Qk7FnRxGPy/n8zqXXs/rWvON+cr3Q9H4MGc69xKc60k0qlTYM3FW0n/TRkDMQtRNgzoCRFFhjaMrAXMPLIWH2zOD7Yhr8ODqarDk+Vaxc+kRYo1hlxLRkdieJlR8NGtyQoELzIoRMc0hH6uWt20hUS3HU7Agx/WuYnkVcZlU6NGmzByJ35SG0toEuI5CmIQzueGNghsYmRc3q7nJn5eW3xuOr4NEZ4vz/5dfNp6UxqVSNX3RqpQOsnAvMDChkFHsj3HYI6OCQz9dFZ9dhX89OL5/M7fcyK/NPHtt4H05chayzxSxTtMxASKgw2ChERziabc8Moze/vpIHrlmvPzJXn9Fug/hruY0FrQiVh1QKtVjagId5uEaYiDbURCGFCJBtzQEhf+bjh4cQ28f4c4/85/KYGLa+FqW1eaVkArVD1XwLNNQrQqgACCjhBTmeaLfpIb/m6I/uK6fX9nuN8B+HTKOtSitWkdNqNYbJS1VMSDnYRgVAO5RkdwscDIuT2KM/0L31RKD59l84xt34xZvXQxg3IJZ3ZlK7mljVaTQ7ekBGIFDaHFMk3XPEN3t9I2D+yvD9g7C0gPD+wOHiBt2y9Fy6ANA2MGRCuVT4M1jgAUSSAgAWCBAWALbDH+Q6PzZXqw9VFQMgZuXssam1txpjVujSFLexk+VYlCbnZf7OjXjWCfST+Ja2xq/rt+abf6YnN/2Bo+3SxuDFcLqmJ6yKm1Tu+rxJWgN+DKqYcjZfxEsvmVz4QLCuoxqLVh304HJ+MOH+rCRvFxcLoX1vwau93Y+lw0cpbxymjQx0zuhVC+A4XsgXBDBjTWA57aiJ7r3jrsxeH6MDE8/q47lvR+q2ie69jd1FOV8LK16pBMHjkZfX2B7OywoEABtzAtLm6SHe6Ohu3A4Pk41J9LCY9M3Ae9bUUbtjTS0nUKoaQOGI++zQfv4LGg4AC3sCxudore6Tt/8eOe+zD/fawvOtAS3j9vnH7LLkZsKaRla1QanjsCG35HEu7etpAQb0Y1CZtu/XIp/7b1fxt6DrJ+yiiTTkJ3MhJXOXhei5+UMCMLQzu9xD0IKSU2xKBm0LD/qE+v+jp3ON/87g7DzVC/VJZLG6E9khJXNbxuuJJSFEALwzg9xTsIySe2ZVArxbqvWy+0D2vahSnetVfXq4jj1STLmYLEl9tvpgaiJqrI0LnV0EcvaEOGNQ1pZVqJ95828+NNvvci+GfXdaDUY9LCYkMWxp6MtFSZryqCxMTBEYIvdQZaREhoIQ3MzHttm/j6VH/wFPBoJ/5a4jWgRenNRu6gIGobM5IWxcPEcaahT16QBgsLKaZ9A369S8a8UGeMWPcufNPyQLfMqCb9ZeY0LkwZvKLx0iiRBhPbNLiqtgdaQCj7N/Wj/6OV3VPszjT6q5Hfo2nbvii1VUsqe+YZR8bNWtVgkih7gaPVSb+8H1pEFCu/xoXl6JbZjz9aUe8p6ab1Q6fySYd6ZNbMODQRscYp7B4iyyU2ZHBVZs9UQPRKVNvSfrcF9Dvd7cMJ4qMR3bcN1rNixbEEhC3HljneZp2mjSIKoKwh5tgFuHeVj8oIfkNJWvibz/a3Akyp96S+bMjQL2dWp2LMmmDDkt3aJ1wmi54VN71QnG341G2rBKNtIP2N3y0LnAsLMPftz2Ez6IHToAMsbQwMRMnXBEwWAbLEEbiBhugGoAIS0ATKt72va3De9UrbaZ7jLed36ah+UdGb0rFaHg/8ZKvo1MHIGggPL6kP5kCaWUe1NbQu7Wr5/GFtfVe+/cyKJYa/BK9NbcmbrMqTp8WNmLOKUlKDKGLGJHRMNiCMlXAezae1YTnKM4bmf5LttsTv1d91ben+Z6L3pmP1rdDdKYuljkg0AXFCSeEn5I7fyYwE2wB0u93Z6B8t97nG/thZ86Hn+3DceJHUEdJ0Mb3vYVqlooaGlIo4HVnyV2iL13IWgmVYSfibleteWf92s3Xlw7VFfUpK7vhkumKZGPxgoyTRqYCBmYMjVgjOcWw+O4cBAfpup6bl8/RswL6H1n6j8nYZVZ9uSnNKca78MAxepE1qiCo4O9qAHxST3sG9gIszn3babVxisS03k72G9MXKmT6ttMaUfLbyeMgxoQbJL4SAgji9kMAbypEiMwkXCmgh3h9G/XNN+bWS9NIu5kJJ8lMr1keNFCv6sE0y3RTIywtBUHAQymGWRZwCy6hRWOy+99mk20p1uyqiTwWrKZU6VxUy7ECjRulHiZCSd1xZbhTCAU6FHJpleNzm9uaa8gK/C1m/ZXinKtUuWaT6BMJcOV3Y8bvGSCqkn5sYoopgCJSDuzIJE8son9AfP/Zjg9h7mahTG9mrIrgtcyhbERRmRFGbhO8YSMeLQUrQDeWg2kKulCIcz+KyyXAvznA+7aYenfZzBmvFy/GvU+xtciQLwuk20Wgq1N9zwVinRlh8czlXJjFBF3cituH3BdTPwvVbO9YnJUZDzk1vqhFbgpUS1WgKZI5i8PXxCQS+2eCLdnzQ9RpCf+xC33MyXvvn9ep/GxQDNSZdMmUE78a42iT1TIGuWggicmAPjmAoZb67E7dDa3O86ea05dwts5clsVPr9RUoWYEaVWaQxSoQUvBMqUmwr+2+KGXbFONyw374jd9Lpl/V659yMW8jRk0lNIsVKIeBGn/IGgQrDPS18mujm8NuS0VdF96TAlp3KAH6YIHxuwLLaPuvtfaMIB2IsNNVAL8cBZowKBCBKgQDokHuHABGIAWEfxsq89PJttK3VVXxmzQYnYlzDeXlGRwKvMhJK3hZKvMxk9eQ0XcQaF0IFW+WDZjKiSl+rlN/Gyx/VVaHuuIHJ7ehykofMj57DqltLCz1WSTTV6djvm+gaPgZvBC2JqBLm9MS48+x0AL1FN2XyEx6c9WaCihzOBMY6ZQawvnj6XoXLuV9YVQjHstnB5Y1ozCX2O+1tYfGyms/xe2Sq0ZW15srwOX4RwHr8uJoUpkycEofCiB098o/yFgwjIvrXPrfZ2dvG2vvjZXfdopvYm47VlLvMjqD+SylpCyN2SOSL09pHwivGOpY04CgbKvxfa4s/pbVvoqqnZrJbbkprYmF2ZFJ8FJE2kKvptN7LFyi+4eU/QblzwwoGDAL61rffe5LnwACLP3TfxWeG6l+7BRHxdTuraS2XLJdFJBWsAYpjd/LFiOg8LMR/hSvb+YP/Jb+tthCelhO+soFNugU9KYjasqFc2DDP0p2zhIClEmZJ5ekD26I7RyKBmoUzIc5lNcZ+tgq9NTIN2iTq03DVZQFzI7dhJYK0hA1yZISZYdHOxKAYGKBggpmYAY5v8OP/bWkPtZBrvrkDUrkCrNwWhLnYsMAMJKXM0RD9HmG2NB4Tw4IhjbUNAzkTp8w11EedmGuuugWJZLe9BFNCYjcyPxHSXEqQp0SGltMbPzH2gNjqko6JVT3nIq7d9LmEP8qdJ6qkz06SI35O32ZQpnRvy+kFzPC1uQImSLu8e4Cn2hOVLNooEuL0s+d2e8lhM/uhR83QlfeqObEA17M0xV6R0u4wDQG3IXzViZ7aEAwkYbVHzk/6yLfSnJe+pcO1T1XRuS27CsmzCiceA5WSENTmSwWLJEb2IMi2In6Hoq7G9yFm+cKvIdqIN+mv29CqYtKUDZEK6X6ULYwgclMAxUuyBlxfPg14oGW9kk1xz8tMzfGOddNTlXaIanoTNOpiYJJDWRfSEOlCEVIoXpUuvSj2mFh6z2iAgGhnwu1LwV6P5YhszVC2w8ZXOSJLzKjNzcpZywhV3RmN0qLLUbdLR4YtFA2q3kiyA19qvQ+dDkeGdzNGTstCUvNSNqMtDP4MKpt9YdSXyPnIrmDM/oALwVr+QpkCjP3P4qs/zpMzkzlVrebT2BNlyO7HbSyGRESlwYTU95DypA1nXBkA+6KNYcUS39H9iKvI2nJl6mt1JnHTlfT80gic61CLAjOv4OJyW+QC+EDUDiaAf2Kttn/C+7pPFWWnHrY6uS2NEVPeZOObKaUFPKXkEGmrl7KyxK7S9qH8AmGXt7AMzVqTUqbXJEfcZ1znrwpRtORkdFXI5GPPAYmPDBLrV9i58gRSNrvBnWAGQELZVufmLpVbcmTmsw7PdqVnOoul9FUHJaPKAEmNKSlkauwF8BKIBnzvEOUqIyBnXQhp+9TT/OlovTIzXLl1u2p5alHwmYmjcCAOGZv+iP9ZWEp0g0ThkqQXcG2QrH4O7Sq5TxUcFxb2i3UPLZHTZ6Rig4XB++iD9oYfaB+ICpF4DHhRIbVl61pEMnC9He52+trXJwaHTdtrW2eM15KzTcKcZAaPoWBsDRQkPrtVIiwY8LNiq8p2Uwrkn24S5gOlhG9NWWXa1cgXkYEkXJ6K+H8JS9mY4Qk9WtnIdK6ORkPE6Zk27s9aqsslx8pLOMkbFvwQE+ZJhXtLw5eoX+0NOpMezdcgIDAhBsN01aojvn9VgHvVqJnadXxMKKdJJzRmqWAB6l3R1BLoatF9IOd8UGUD84qyGdGOzUejnQb42Cm+fl4/SoM/Cig3KO/9iWJ9BSQ5Ci5SUY2/hCdEaD0z39KkKpN7RDwtoJtil5yPnUk/fSD/bMPPYlR3eXOnXRi8dA5X0I52Optor6ql0QeMLIp4e0EAi/yZdxvdTRIb4QTpg5xpmdUht9ExpCZPhwTZO3DVYmhla7A1ZBjjB3AeF75oFxe3O+VSa90E56KdLIuraKaIuIPncbb15rVLTb6Wajul9WRn8W6zu+yX+JrWuLJtPwRD91FR+OcYWurnubILvDTLuOinrxCvLHTuUR7N6yC3KKz2OYw18i4Kz5pvT+NL/42FdduOs6gF1amEkeWvp5/RQeb7aYjGVlUcivHFv675qVE4Nj4i9T81GcSuNsUylfRlUuddUtRSS8VmTrUWNo+8RXdbtZZHEwh4QqfWCDBk46NehDOFJR+vUO2vp2npJ1LbW03lqobf0IXVib37+Ajg1G2d78ExC2zqw8m5HRIhwINjoKYGfaNtev6T+dzReOBms1ASHk08v4EMo8ovvDCGTUNIUjVtiVTM/ocnnBDvThmwEBXGztn13dR52dG452bzckIxbKSxycJfSU/R/dEmrIQhIQr+dTfGx9vkuVBNFOAhXj9pkn+UjQ+RbMdpfJZcVIc+Di8U9FH0Icsn4wREK1Mbr3QwXsDORQIFFODQsI+E3QfiSmvxOJeTHR/Qik3Ih2WAeRnpjXZXsAREKfKMHMYrKE/nIm0NAmhYpmy35zcX75ak8imnzEa6x0U/4w8xjnyFscgrIqVo8I9WrjpwGKO1ofG0RCS93+39Am593i3vQimE7Pqs26WIw8O9yD8rbE728KkyIjcihs6pmbkuZ1QIMYPOb+ZVH+ZJD7Z6O4SBL34RvlgUPl73w/MI7JOdUbErEjhSQU4Hm9qqGEU0/afOmjkHnlo38TxvgKD3CQwPPiyuAeJHphbsE5tRsAaN/dosfX7a0ITaOPieb2/ubaJQ/5po57VMJ2Il+5skZ0YgfyDL1eGRtg+iqIi4i3gNGCmE84ASbQwbRPPWmagPdJP/skSHbUEuSle9KFd+PsdjwzxsL2zoiLpWOaof5hON7CTCL0khnKOf1Jl/bLEPIofO9Eu/cgmnzRALiDmOrL2FW7NtUWalTqEjRRGdbx9mUxu+yRTN7NU0sIiyq2hTheVxor264V5NnMJpsC4iuMB5AYwxQuena+fxhFwiwfk9Pym3bxyTu4ELP1ZV05cko8bHKaGeCTc6y176hwJBwhGfPVRrPDH9MJMCr7whw9kM9eFS9aXNQ4XFUfHBmPgHx47/zxd+j5BQXZS3nQVKXZ1PGuRROlKABuQfzj+wTfqzA3PtAtVzTtFzTMwk38lf1FCkeUrRGLvxcLEOBQ4ENymICAvzuXUsL48+iBt/RB2mUoaz8wqKDnt6CAPUh77OvCemI/ZMRzRcKNaoB8FnGtyKgjA+ZY90OIfXuJFTNmBouWYm+IYkMB6UX9MEI3hGyRiD8USTeL0cCywgIIIXWJejs+DZ+lOU+VBQ9+GmeIbU8c1J5N5FX9RGsS+6zZq61dBIR2d/wMumjjQ+kPmiHprDJUX3mQfWjn7DymW2WjUV9QXRfAPfNHajHzMsDh3+798B6ZxrApzmIWdJt6Sux6a0wiSJzONA8/cTw5lphv8DeljNi9wlEMKq2T16D/Q8BcSYJqFj9FuEjonHxZPyIqDMQhvnLUmCYhsN2OXBSDsXh9oHYhLFC8Y4CjwUEXpQvEfsAIbm9xuBMc5NPsNIo7EMl6x6L3jR3EfzN6UfrB8R0TZZVDXSNcQp4K2lKVmuxNtwI72pozwpAfWhgXmHlvGMCf7AD92UCU7Y11/YcuECgpxcdoVqJkgov9utjGT0l3YyhwRO44/Mexo4hkn7LsP520ID6x+eKB0GKpQnFqAc9emkGKavOf4RMH7U6PzJDvVhYDn7X/gGyvFviJ3VuDB8tWGcBRDHSMcW8yEZCYJiknw5vT5oc1qYz4kkOx5cXzR5LWPP+K9vJwVdLK9EkA7xlol2zYXgaJDFQbAxHt1sR6NAX/XmT6CIy0sM3xa9p4qlm4a+sugoyqeHioEN8kKaopxZzoWiJH87eWPOH8eaubHI+hJQMST6q4L7cg76cIzLYT/GOoqf3blYxPlsICapNmYD4ZmJQh06U3Ch2vvSezYSsunDxuQh8RB16hn9M+iizTFxVMKACYvki2OBbMpp4Ns9o6ysN2+/PAC+JY68dAH6kIyc9cycE425TyBPy9NX92XhXIIpbTooRDXhXOZY5vf8Ku/lAfypW1qp29oRwLjm2HnnWTiPLJfkmWsHrpE33suyXctxHlxyNciiV9xv0/Kf8DtOicseg/1n8DUeiYS9B2m7kUntxUIQ+NsUGHwiibNBXcjxF4jdu3P19XuG+37l7XbaIUHlqb3MsUtLMktJcFzQHg5IMaW/yoqN0DFLdVcgg4eTYa9RujyQxTU2XZ1HxYddPmdYW5BOQYBDuct+rQ3eMGYTXQq0ILLuTGZAyxmg7yIi6T0nap9F5DhSyvgm4nnn0zBfYW7fj1b52yIRuSj+hxMQZEK7UaErUnsGsN6JC64j+22Aix2wfozvMgywlh4VO+ugR6rGwZJE6ysdNVdWIARm0E88fdC3qiypMfXUNN+vQIeM2L1y3juL0nU8B3xzqedjgNupt6ZjMp6h7iwIg4zxgRA0BLrBqHQsrbcAXDpp1bAIwzrJ4akw1rY8uGJehwZOqd3yVqXmPC+DjN3YyCn0qqAcG8oSfcJ1Q1jUS2ISG4BdGyiRlgPcJfDEhdMbz9mmlFcglAOhwHFej9MRVWZ55M/yuSOQ/FLxr46MIj52VVRcf7QziMduxHvaFX/uiqosIjgNacBdSPgGfcbFpXfDLR3/5E+rFHOM6wWwQfeM6Frh/dyx949YjkKeBlFOe0mjBATk9DNdpdw8KA6zqyv2F1KQMCiy4Yi0Xl8m3oady3aH7qAoaRrQ0UFijEYGRYWoYszi3H4gmr17n4=
*/