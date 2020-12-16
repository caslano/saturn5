
#ifndef BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename T
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , eval_if< 
                  is_same< T,typename Set::item_type_ > 
                , base<Set>
                , identity< s_mask<T,typename Set::item_> >
                >
            , identity<Set>
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
+x3sNGuQ126+bpb+V8hY5Afup0WMeUZx3VuM+Ttwvy9lzDWEx43y+cxuV9bAZcz9EWtV3VhoEbdX25hXNK2Pcu+yL43hs5x7mhqLPs3H9P0ot5W1eshY+E0ed1sac0zknD+BeFdyPtqgvf2sXzto0Ib7aUdjPjknx0ODNRxvd9iVa/le0GAb++JDuX2sS1/4dyvnfJAxp4ydw+HfAC73Isr1ZzYGdgvmITbBmKcT+zwJdsfwsfpGPozZrP1b8DmZy82ELiPYvzmw+zHnd6Gx4DC+Rl+Kut/weWslmGi6Dj6bQ9eykLHAdC73MXQpyeU+Q92B7PNOlOvCuuxFH8rL5Q4hjvkc2+fG4tqzja/A5nG5U8YcI1iD72HjEGt63li0DI+xP0OrHVzuMtgY7kN58lscndnngsYin7AvhY05ljNzGvM/x3Hcaiwg+pUz5pzJdSsbcy9m/6oZi8q9/e2w8TXXrQdfVnPdRsYyZ3G5u8GGsy/3GfO+zJo+aCw4mo/pR2H3JF9jtgL7g4+Pp6BVa+5/z6LcPu5Xz0PnVWwjDhrs5uM30ZjnYy73Atpbwe2lIrZxPL5kIDa5VxuIukdYq2GIdwJr8Ffk6DCPzy+hvdXsy3iUO8DtvWosJOPp64i3FGv1JvpGgTzEZiDeQVxutjGfzKssQLxvcy6DqJvEPq8wFufkY2EtcrSIr3M+hM+nOb+bEe8ktvEp4v2UY/s7YpP73z2oK9cWB8E+YLvH4Ivk/Ev40pV1+QZ1Z7AvZ6BBNy53DnXfY/9+MhbOz+V+u9IPyO6Vf4casPYFjHlmc3s3GQvI8XuzsYjc75c0FpV7xLLG/HKPXcmYL4HHnNvQnvTJWrAr18914Z/MHzRE3YWs813GwpWYNTMW/JPvy5rDv4ls9xFjmX24//3FmPszmf9De3+R+T9o+iP3qw4o9w3H0QU+P8r+JcDn0nxPkmTMK/00BUxymW7MtZH75AD4fJrzNtSYoyJfq4w05oznY3o0fJZrmnHG4qaxfq/ARpA1mAJN1/KYOB2xjea+kQkb0k9nIY7KrMt8+FeU+8sSlJO6y405MmX+D32oDY8RG6C9XA99BHYX292Kuuc45zuMRS+yBrtRtz+ftw4YC/VmdhQaHOf2voAGotXXxjyLue53sCv5iBpzJHBsF1EuyFr9ihx15D70J3JUirXKXxDXJVzuRmOudTL/Z8y7heuWAJPxvgzqFmVW0VhY7u2ropxcJ9Y0FljAutQx5pN7oQZgMu/TxJj/A7ZxL2Kbw8yDunIt/zB8eZXLPY66UzhvTxrzjGYN2hoLVWOtnjMWuYX7aWe0t4/LdTMWPct562kscy1f7/aGXZlvSkN7p1m//ojjK/Z5CPyTuf8RYN2Y/Q3tVeFj4WVolZ/PqwHYqMw+v4b8yvE7DflYwj6/g/ZqM3sPdWUefR40GMP5WAyf63Ld96Gfi+uuhl2ZK/3AmPcgXzdtgqab+ZyyBb542O521K3J/XkX+um7nMv9aO+IzP+hvYbcTyPGnCu5j59Ee3vZ52+NuSewjR9QV9gFaPU7t/cLtGrH8f5hLHgfs3yFjFXkXN5gzLmYbRQ1Fi2an1hxY3HPcR8qjXJ/8LFVAe3dz3arGPPv5nhrGAssY7t3GAudZxtutOfnHN2JukX4uLwH5dZzbA8Yc8v8RgtjXnmm9Bh0Gcbn1dbGHD+yL08by1zHNtobiwzh9johDjn3dAWTa9se8DmebSSjPZkH6QOfH+NjoR/yIf4NNuYR5odWm7m9UYhDcjkWvqxhrSZe8Y+1n4y6n3AcU2F3Huf3bWi/mfvGu9BZYpuLOF5htshYVOaMliGOAsxWGfNn8rXUeui8mnM=
*/