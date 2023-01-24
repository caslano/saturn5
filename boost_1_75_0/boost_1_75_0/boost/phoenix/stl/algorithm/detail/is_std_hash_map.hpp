// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_hash_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_MAP_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_MAP_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_map
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multimap
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_map< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_map<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,class Ty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multimap< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multimap<Kty,Ty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_map.hpp
T81kT0Q2y/TlSIYiqRWiM+RaMNCkU0bZ1kalLOPfMDgtt8y3xnM08rW12+4p6Y0gBitwNLKHhjTyla4z9YESvSJviTZrPq4nTNyrwtCENqyA/PcercUgQd1Sn+iNS8pVmfruyKI8pn/IMTV9gr3vAkxVxC2PD7lU2CUqAtSL0+i/3BY+qsUZn+78YOWwH1a2zojhRVtEMj75P4Ajo2/q1sG92DmEzWbEITSoa/3p1+uQ7iVP0pO8EUzwzxuvetLm/MIR0fbWes/x8Xaep8e0m3wPInGvuHptKO8yT4Mejd6H9KzjgsijIXhCkR0weQuemSfvcfita87PfHd15ttkjvYsTZO71iZllrWgAfMa9YF8CDCrdqFU11B+rsc9Q8ARwbsReEUk/i3xg/M2hQ1HWH0WiWTHH9uGJ6ddw2gF8zvrAc4n6PZ6yy2Z86OKU9qkG82yDGxUVspMOF8Y4Pgq8M/k/4jobqL3TxFeG0lQkiSMbkodFAjI/TAIFE1pYFhny0fWjcHcIcC+8as5BPInbDldCHTx3+n9L9ZVpP/mSh4kepcy/p3N4DfIncfObjAEW25lzWI+Fk8rddOn/Rk1FvVWQZpFy4VZ2Htuj42Eko2QnaCSsDuAtpq3xJ0pyHeRl+0/dJp3NBz/FsCV6EGUROcnEiR67+VFghctieisiGhRVm+7q4SQRIvovUcSnbVYFiEh0UtYfS1hsdjV
*/