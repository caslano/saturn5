// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unordered_set_view.hpp
/// \brief View of a bimap that is signature compatible with tr1::unordered_set.

#ifndef BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_set_adaptor.hpp>
#include <boost/bimap/detail/set_view_base.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief View of a bimap that is signature compatible with std::unordered_set.
/**

This class uses container_adaptor and iterator_adaptor to wrapped a index of the
multi_index bimap core so it can be used as a std::unordered_set.

See also const_unordered_set_view.
                                                                             **/

template< class CoreIndex >
class unordered_set_view
:
    public BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_set_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator
    ),

    public ::boost::bimaps::detail::
        set_view_base< unordered_set_view< CoreIndex >, CoreIndex >
{
    BOOST_BIMAP_SET_VIEW_BASE_FRIEND(unordered_set_view,CoreIndex)

    typedef BOOST_BIMAP_SET_VIEW_CONTAINER_ADAPTOR(
        unordered_set_adaptor,
        CoreIndex,
        local_iterator,
        const_local_iterator

    ) base_;

    public:

    unordered_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}

    unordered_set_view & operator=(const unordered_set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }
};


} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNORDERED_SET_VIEW_HPP


/* unordered_set_view.hpp
B27vwoJaZGExTDsE2S8ah+nsqavl2g7dPfnvOPT3cG4dbq9jNhKnoD6f3bW4weT5hIPZw3EBbEvYewq4ln08ApNPGBwP5XgqZiPH2zHjkQvq/8lgwl6OPR++fmdIH9BU7Anvxxq9QMuwL0FuCX7WYG7GbTPsgcw6jldxzqkzaDruG/GzFbORc9NJ1zbOZZxB+ji/CJPP8c3wWcw21S1UjttO5JN6I8Nx0ij0AsE87OvgVFgaoXNoK+7rYQ9kN8O0LxtbQzFbOC7ArRSzk+Pdd4b0ES3ErRPssYD6glmEGYp9Ge6rMKuxFxPGNNy2cFwLl5CGZzm3G/s2mHdmQIdR0l34t8OCfbE79Bm56jLaqfqMpuF/M255Y0J6jarhMsw9mEVcfzXXTMN94Znh+o62YVZwPlLv0bNnhnQfbeG4jnLIOAt/mB64TYVu+pAW4F6J+xrkl9jEbMC46Ulaz3WtcVwfP+8ivxS3dfYx7m1xT/gg1tqKfTf2gdiTzibumGLVrTSe4xWwEjr1LN2D25qz8cdxxvbG1rMcv43bNpi8EHeO++KevzBcH1MxbuNxK+C4GqaNJw9hUEfTAs6vxT50POHB6bBW9TYlnYPseK6LWYp9tG1Hfh1mCybpK3S2Ywox5ZjFmJsxz2K2Y9J2cB4zFVONWYxZgVmHeRezB5P9NfURMx2zELMCswGzFZOxk34aU4tZgVmP2YZJ/oY2ipn0zUF9Ugd/B38Hfwd/B38Hfwd/B38Hfwd/B38Hfwd//5+/f7X+/6D+v1JR/nfguv96Z1qhvQV8Zv1b3j9oq9+XF34WL3sL6Iv+qkitYk5Fred3ouon1byrfKh+x5XXgL2rI74dN3vsV+pz6WEav0GYh4lfncYv7EME+QCwaEZVtec3gOovxXLbI3+iOT+M9fsj5FvXbK5/EQ+d/Cl8lR0bn5jAp9ocxKHMQMJo1D5wjVLHN8WXSRg9yQfWlzD2d5YN/cY38vu1gdHfSJq82a16G/trQP0wj9p7A7jmDZ9D5xeVVJ5a45U36q+/nG+bEaVvQM/zfS7nN2i6CT60T3NEGCMzJQz2DNd9Rt3PE0joGt9xPrh3Gvnl3OdB/fqkTll7qVMJLnmZDEmX+QY1HbcMSFqi9uPIhsQPd4m/uOUZN4lzuE7CWEt+cY4+4TECyd7mWRZVpUXyLadXeajfuP1KrzNu+XHRcVuXjbtn3OSLcImdV9zyDzBuYzVuG13ilk/cCrzjVoO9pHY+H3PWk3cFv1D8FjTSRqqeJmCesPvHeuOHvYguwSV+qRI/9U+orcxeLD5rlrg11T06VO8SwUjbCPmR9veStL+Kmpr5zvZnZBxh1MyZq+cnO853o3/bbGc66buERpAYm9glsXNiN3v3pDg2mkrsJB1dI0Qi+zmzV8tUCWus9G/7k8/BNkk8cZO0mjZJ+nDT9IXapMqSpohyWmIHrt/gttD3Pp7EwxrXcpJdD7ScpF/1qkfqP9N8b/2c2AeF72dLMM59rp8WmQFabhoGKUvnvhiL3EoSeEsq7xTRl7RL2/s3t9H3Bv1Gyf37ZHNvX5io3yfEEAa8HD5l90mfu+YJh9H5kK5pGiR+zovpy/8ejOaPhpWpusL0O3CjK2ykfGt9pMjMibHDvqKF6HCxuxazR0l/Ob8opj+x/ymkw4xfCRt/hPZh2PxFvH7HPFK+9R4r/k6XcN9OlXBLJc76vX6xnD8+JpE9J17ByLehcv1qrh9qi4Ml3Obcr2Mk7HJnnM238CWkKrSv3gbx4xe7femXTNywc9RY7MmWvXf/0gTKoAnvpFLeSbGnxzf2N2br/pjE8fzHxScnJWSzh38ara1NjPkmexiyE+w98FM=
*/