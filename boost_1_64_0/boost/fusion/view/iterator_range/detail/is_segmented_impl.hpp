/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    template <typename Context>
    struct segmented_iterator;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl;

        // An iterator_range of segmented_iterators is segmented
        template <>
        struct is_segmented_impl<iterator_range_tag>
        {
        private:
            template <typename Iterator>
            struct is_segmented_iterator
              : mpl::false_
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator &>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator const>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Context>
            struct is_segmented_iterator<segmented_iterator<Context> >
              : mpl::true_
            {};

        public:
            template <typename Sequence>
            struct apply
              : is_segmented_iterator<typename Sequence::begin_type>
            {
                BOOST_MPL_ASSERT_RELATION(
                    is_segmented_iterator<typename Sequence::begin_type>::value
                  , ==
                  , is_segmented_iterator<typename Sequence::end_type>::value);
            };
        };
    }
}}

#endif



/* is_segmented_impl.hpp
R2lf6P4t04JP6V5qHqw9xm8okROzuExSlfFo+ngyxXHtqIf3Cxv1FkGqcp5qn8yK6dwY3Y1BjiuDWRmdLrUPZZKUZhtn6T/Wh9n6HOvS9+Kj2M+ESvl/ORbRtzChZcmDMsvKyGfrVoypjsn8nO37S13aJ0IGivsRa3+JDN+u7fuhy3c2E1kclZlg1t5jPH+8Q0jyKWHwFHp7JTjo+41GsJKEffZpIidnovBUUXoFlTNdiC3791wZz/RVLgOZZWyMSlOV/ZW+tXEkz5RFiV7RldlBZa8Ujp7P/p3ISFjg+UEQcU5ltAR4eIZxmfoPK/gvKoqkrfPmHbhT4JE90FN+uFSLv904bcyVJ1mhCpnFZcooN3A4cd6Vy7Poe3phJ33zGUXbpe+S/wj2iJxA6B2d9jWbVvsk4J01+HlUx3/mmWppb/aHqE+qpqsw7+Lb4QZjniLtXcV1+VtnNW7FZLG+t71pwqu7sVXmkG42KGxG6JNxZEKHNiC+Nb91aE4pcZ106y6ajm+3Yt2OLUC62bvQd1KG++j/jndXkF6JreZbk33Yu2k6PBtalVgDJ/ED7g40jDOgm8W2yET++B4ao5Wpa8ZldRNhQl+9J9K3Nvb0OtCElcb833ovQteXY5DWuTeh6XsGSPssoZklNtIedozQzB4T7mvdB2mmIDpH8kZYg25ydejX70vpJmeH/ltCH5kSuPsLfz6u6cbydUcwKscO7fIDgKbXpL7AgOlYLoeGF/oc3ic+0KXDQtddCzs0d0MC2+tBLt1cbkDaBx2aXSA/2vI9uKY5A7FuL8R8oo3B2NSPt3Ie0sZgOR1Zn52KM+VFzJmHtjHNcn8dMWgs6mI74+ZhLQy5Z/n1Nn3qXo98eAtni4yYH7UxtshYnpc+osI44bHJfsbtFh2rjTbk0iMNBg7iYPvTGUt/pemjjsNz+YRD291GHv4oTK/eUHPOnu/xIuLvGZQ8KouEhWXQ2BtcdfcAUh7qGBUhw+C7LnbhgosNk0AkWRExjEhL4uW6+UsWZmWmZAaCxer5JRqPFHlOuDwFy1Qc5zwKmAleQ7mwTGfcMj1TeHmQF5FgbnTnwq4PT76o8W4tL4OCi8Sil3gIzsFCQZCWdlxol/dsmkgeJmHGMC5HjVf49pqLP6OyyCukFGw5ROzkDtyJC6StskKEuZflrBm1F2P2urLPmZDCIhYmvoj+SMD+xCl9ZtXKZ0j7hAe+ir2iYI1ovZjPTZpPGsWQQezmc5rkg/FPKF/up0EmuMt3ZirfRylfUUhordDlWyJ8Vm/eepG+RRd5PC9jj5nmE4FbNczrQRfpmiDKEiFlyNm0EMROGzKX71yU+4nvFYo1og93YoxZ7NZJMVl4eeGHkl0UPCwhzs+0OLnfvODmkZY5jJzYZ8KjQ+CxVtcYGZeJKCXnBSPBhj1cowKWxG3OCl+kvs9aYYbpevO7LyJtDEbC4xFwLXsqoU3c8TAW8gXCk3EvDfySYaykaTw/pvnwjIcqkqUtnsvkod406hSmScI9mbFpIYwdffst0bcoTkI/5qWjb4vn6DiyfKR/fOF7fh4VrBH1eLJ+/qubzzPzIFVhmud6uTZy1yGI/yfBB6mXBEEcM305lODtmmPhxTRee5H7mRcI49NZRfqxcXP0Pwor4V/4/rTLn7NApSXPE2HWk1P4bf7I/0TKX3hFmPNCmCXPnfhxv8XlP6dUUeahktgPlhm7wuabuHx+xMAQqiDiivke7KxDtK0LyyuihPqCDq0muEn/L/s92CL8nBU6Vk4eSxbu7ekYSbA0WurbdXhjr/2my7sUS2hx4VdhgZa2wXfA3oNctjaK5BWzxE+9KEkl27D7DrChDw20ZbY=
*/