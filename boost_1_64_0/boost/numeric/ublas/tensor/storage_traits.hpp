//
//  Copyright (c) 2018, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen Germany
//


#ifndef _BOOST_STORAGE_TRAITS_HPP_
#define _BOOST_STORAGE_TRAITS_HPP_

#include <vector>
#include <array>

namespace boost {
namespace numeric {
namespace ublas {


template <class A>
struct storage_traits;


template <class V, class A>
struct storage_traits<std::vector<V,A>>
{
	using array_type      = std::vector<V,A>;

	using size_type       = typename array_type::size_type;
	using difference_type = typename array_type::difference_type;
	using value_type      = typename array_type::value_type;

	using reference       = typename array_type::reference;
	using const_reference = typename array_type::const_reference;

	using pointer         = typename array_type::pointer;
	using const_pointer   = typename array_type::const_pointer;

	using iterator        = typename array_type::iterator;
	using const_iterator  = typename array_type::const_iterator;

	using reverse_iterator        = typename array_type::reverse_iterator;
	using const_reverse_iterator  = typename array_type::const_reverse_iterator;

	template<class U>
	using rebind = std::vector<U, typename std::allocator_traits<A>::template rebind_alloc<U>>;
};


template <class V, std::size_t N>
struct storage_traits<std::array<V,N>>
{
	using array_type      = std::array<V,N>;

	using size_type       = typename array_type::size_type;
	using difference_type = typename array_type::difference_type;
	using value_type      = typename array_type::value_type;

	using reference       = typename array_type::reference;
	using const_reference = typename array_type::const_reference;

	using pointer         = typename array_type::pointer;
	using const_pointer   = typename array_type::const_pointer;

	using iterator        = typename array_type::iterator;
	using const_iterator  = typename array_type::const_iterator;

	using reverse_iterator        = typename array_type::reverse_iterator;
	using const_reverse_iterator  = typename array_type::const_reverse_iterator;

	template<class U>
	using rebind = std::array<U,N>;
};

} // ublas
} // numeric
} // boost


#endif // _BOOST_STORAGE_TRAITS_HPP_

/* storage_traits.hpp
ysTZ39nf2d//2e9fbP9fWTFbnv6f3tl/Hm6zvSMHc+lDck+iqqKMv9TaCfGrEJ+zScZH5+CUaUFpfZ3+vCml34n0dpw+pwFberFkkY/0u5BeQOl1DRX10dklConS7kFaN0qrr6zrP8D+DHYnphtn0ulE/GR51yK92KBdUKbi70P8hnielNc6xL8ch09fQSW7h+1Y+Izi8zZ9YPJp3hsfBlich/l9qnkWWFpXUkmXWpfU1EbnViyKlpX0d5696XOHR4l2oOjnft7EvC3EMT3qPJtYxM7vXiKcVs59y3h63iNUhROGPcGThNONn7EbSs9+x/6lvr/rOUrP5meNbxH+C9nIl+/XyhOjUT71+wrh9MVeZERkIz6b6/dlih9ANgRbpT+3l/cDc+TuXIDiw4gb7jXsOjxs18FpUwF3axqPj9IonXlu96q9glBIpqcRz1mIW8s8JUeUh+h02jbAnZrGG+OZ/N7fglHJzjLzzH1A7j/eG7dlq57PmcfzvSWXsWwda062BrjIFvfTR0R7MVo35G4rkoJsnTstuWwdS0G2soj+XFu2Cuk54CpbKIJoT+n5/Kzx/Q7ZYhmi30lVT5K3tly3v1HccKxxPdTfPkTu9LNsnRuTrXLEbfCzbJ1vyBan7QDcrWk8hhwwz27ot29IOQlj+7ouVBZIU3vO+UjfBdoTzBucIZ44G0pTctaV0wtA/yTRSznzA80XCA2W5fAmlblwCufnrjKXYD+wPU3vs6hfF8AtkLniaabMzW6YS9d0u9oPUB/MIfwk33KZZp6FSFrwS3bX3DR3WwMtS1Mo3eUeX6I9fVsD2n/n8jnsQhLG66Kg8w7nJXJDyWw7+iozDEPqSm6O1laTQU0yexrJdDnRZrrbjLSwfrbNCN+tdzfRw9YnL94eqB2fzffjd9qnAEuBsz2hHjWLtT1Q8nfZU0TTS3RPZjth9G9BUzZQjOtum8bvIErvKnCi6ioPTE9jfAkYLklX4zDsOSd2hsppO5H2TZnms8g2LZwe9rbiM9RGpO0A3KXST+s9kG2f0TdvfzRAj1HuHxqq3EfL5Xshrn+IV0q2R8dOQ47Mck0NKWwunkjnconpZrmiVWVN2I/5CDfgVk7wOTPl1Hfrd1cB7UmvRDkj8eW8saG0Mmk5cwi3nUs5mQ/L6Z4I0dbXus9vjGvKdFXDAsOGsB2l54g0N3tLpjftRHZExCm1j5ZDWd5cKm+CHHK5zHfF/kw+IxAx+8G70Y4jzHZMZmtm1LGI8PNFpvscwfySvwPGUXpbZ/syrR7zW1CZmkx+r2fLk2D1Xs/mtFVI03YRp23vm2Tshlu720nXTE/dTrp+elI7afBJ3aa0xmibA6j76lZOO2mdtruV0056LdkBNG+n26J2S2InvSnibie9aXrL7KS3TE9qJw1eqdunMm5SO+kvT2/aTnqT0faR1uAZcbGT5rQREXc76TDihkeab/8zbSet9Z2jrGwP5XfQEF6f7EvsE+fiN6m+8BOivVD0dZ8LwLv59clHhONus8P07usT1iPeJZz29lrWN8Pddke/C37H85fbeqSNvhuOcPqq9S/X5Wcc10lkqvkJvMdlO9e6J0DQM9u51tVpRdnua13Nc2O2c607AXFLsp1rXZ22IbvFa91TWndoWZqaG1vrphlr3YIZzcnSAFdZypFzBNEWiYvdZQm8m5ely2ckebcQffNr3ZEz4te6ZfQcSCpLV3B+ibLE61j69SacYTgTD1N8O65PL4r/tOgjMmmteQz0G1Gv1TQ/nBsKSpHyCOr/cYhfksMy1ceQKU7bkKPnHFrkBu3+Z77B3ORr3E2gPZiTZI3L6b7c/9wad1ue4jKQ71Yv5Hdwo0M=
*/