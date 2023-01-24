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
fDiJzUulPuUzDIr6YrPDJJQPd1NM4E4+jWCF+Nx09ITA2MI/m4y7HooY1M8qnS6uXiM/U1boK+oILAv7K+l48McJIl0aQlo8PYEOxXl6orTXJrEXEG681NKvkvRsaV7lPfVNG5+L8/hcjEax4qmR9GvQbUF9ziYypaVOQlxxOtKVooX2euqQcZJKmxQjxIIkJsR7LkGI6CI8udxL9Zwfzy3Fh6LjExvaY1JMqTEgKSGjW6PaN7GZ1ELlqHqpr2hgmctCGjrhJjG1/ykNoTFK/SKz275CfWrZF/GGUhp9kGLT76YmNcNe9VIhZlWbHWuWHZsVcMX6hjiGfutJP6KVH8Fmreqb0CxvJH0w4vJARepdffG8Di/Y6xSEoEUJx9JXTfHzAE6lNEWg/sefQ4Ly6EpVv0D5AUYYyG3ToUhK1TvvN5pPHf/zuLixf2ZcIkk3OWMkvWjpRNK6PpeTFAf9b30ETXs7Y4MObRcT+ThsUjj4v9IHv4czRqA7LTz4RydaTNGf4bgvoao0R2zcv3EkNrJPXCOv6tzIwV00EsY9WW/jAxOpjUbzeIK2SVXLzfFEFgacu8xCM/BO5yEgZyBdb/BPvKvtLJtcOOZ+jtx9HHvrXbhTDA0Kr8AUdYLEDc/2+/Th4Qmf4ogbngs3kfLHJbQ/AyfGOr7Q3KnjV/c2NEDGyEi9Ra8rJiQuxxzqchWNCMy4hybERmS/iUfE
*/