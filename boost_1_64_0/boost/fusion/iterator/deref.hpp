/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_05042005_1019)
#define FUSION_DEREF_05042005_1019

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct deref_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct deref_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template deref<Iterator> {};
       };

        template <>
        struct deref_impl<boost_array_iterator_tag>;

        template <>
        struct deref_impl<mpl_iterator_tag>;

        template <>
        struct deref_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct deref
            : extension::deref_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        return deref_meta::call(i);
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }
}}

#endif

/* deref.hpp
YTP1xNsz16sDCIeXOYueMt1ZewgNfI1ORbMuoilT8s7EnRgaeX+zUf1YbDTVkn2cZgiQZe0XljlSEnFCF0zvBvM6O3grsN1fBq9tCnPHivMUr7YOMEExppFVBAYvLo0SxRjb2gLXo4rpYgEIyjBx8FFtM8wM9ogZ8THBdiKzZyPOpNDglD1kmHZVxsMCXPWAii4JTSyJubHadA/PUAqhXHhdbulAL9XdTQltWiHSDBW8eZuxkepzfAixYYnGXG5QUxjsvLv2NO55J/TpoUV7wuBUZvM2WLQE7wBU1f5WVA8EvlYMv2qRFr6R8N5H0LUJmA7wH5Awnw8kmYyvcVwmLz2naqgMQdrRa8PjxlbOqXqs+WB8s1HlPlC3gJLbGHBKazzhXgn2uOwj/r9uBu1HU17LYKmyjoy78kAyfvvC0n+EyjocZAv6Rt0zVHdBYSN25QDbB8ZwLf5oAq4oMKr2F2XoGVKQcLEmOJRRgIbDu/J1/bLbFPNC/X5VwFGnnl3fIo3umHqBSZC/JjQh9O71vJIjVXmNUKiHvxMIMOSgL2K1Lo8+QqAvDI4UMg==
*/