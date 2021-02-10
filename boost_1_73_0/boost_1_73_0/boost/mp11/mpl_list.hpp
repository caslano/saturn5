#ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED
#define BOOST_MP11_MPL_LIST_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<mp11::mp_list<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_LIST_HPP_INCLUDED

/* mpl_list.hpp
3zn57ozOikXbCSeUnvHnfOxtxg/mgJPcR5kAHUetWnBKMbXRaZ4HNfwHyVxF5vbDb1BLAwQKAAAACAAtZ0pSQag6sZ4BAABvAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MVVUBQABtkgkYEVSXW/bMAx8F+D/QHTo21LZbloghmAsS7ItQLN4sbuge1MspjFmS4alNvV+/eiPNg+CJPJ4dxQlHFqXS4sxE4U+Gtr+Yns2jbIx+5Yl7Of263b5xAS/hAUfkJ8gxeYVm4ktFDLRYF22lFXSyQ407rb4R+TTkCLDUVTKVTELg1sIff/Wn/qzwA/v72aEGFKCj1wksSgL1G6UyPtLR9oLx+zo6o53vIHQssLeNyhz1qWRCjqvcC7cCSZrQvABAiI3VSW16jkizq9/bNNsnUTXVJxsdxk/lLKkxYNp0FUK/lFAx9EH+fuNTXFsoWsW5NFhA+6E0L0qnKSFA6KGK3sy7oqJ1x5LBHVjnMlNGbPHdLUDqY1uK/NiPZbM0xTI0Rd8k1Vd4g2pUnS/9Nhiv4TRlMc2y2wDZM1j2VOygrXH0vWf1RDZrdIMfI/9elxnHrm9qAnrlHkh4w/SusnGqOJYoIpgj+oz+DOY100/Ewj8KLyP7mbwfUMU
*/