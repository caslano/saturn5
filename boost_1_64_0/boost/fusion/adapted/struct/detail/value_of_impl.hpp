/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : access::struct_member<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* value_of_impl.hpp
gViCnwVVFxNwPYf1Pkwm2IjU668sF3U7RbWJlbthkaQjKCWx9Cf6DYWVdX4w/5XxlllAvTF9r9m+bKFQNuYfaBd6vF+F9llKfxP5A0bi5grSBciPSwkWPVwXYPTUk5DS5VSfxNMLHjtQcap9EI3KWfhRS/BsNLzxHrLkHGZThBJxNsjlz8gB8DjhyUnssuLg9vz1U08Xp+jsAgVeqXEpLeInPXk8KVC9Sd6eGuSCp1kJ3v/BHKTzEFJFlF4cwUVNYkAok1RqwMFotdfpG+tapibAuW2Uqasu9/lMd7iqnmhT0vUZkv4mzRHqOgbiFOgiusIBh1mhYVF+nxM/Dw/h88g61jqOO8Bomp+l1NsaqXlIALMe8K2ZgggzcqDzUc4/RjbWuA0gdAbRALp73EgqRp1xmFmLiPVthG7i+rbmT5ACpn/pOWrlFPV1Gr9SmS1Pjmm0weWRuFPx8Rse7sV6eYKy4oUtEai7pVn2YW+/7TPxRVCfULdYKeaRnHvGzbpKdgzqls3KlkUFvB9/PUsWvi4l3iTNspllEBBX6MXksVL6uub0ILFYuKYhqw==
*/