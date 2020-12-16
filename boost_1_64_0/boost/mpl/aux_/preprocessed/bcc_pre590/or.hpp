
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
358e7/9Q5+KRBZFt8+4+AX+fzd7dNh/Zlu/uuxC7LT9WX4d/mu3/soDt/5pNH/v47RsmnnJe0jtza77f+IeWsf2nevQuqN+YbPv6Utl8rfP07ga3cDmvp90G2iZyfjvYzpum8zo2kl+BR+86egfKDondurtiqfbVPjcDZDsfqNise8Hz4CA4G+4tn4PB8Am4D3wa7hvUy3qX0G9hZkJkm+t8nde5ifNqbPUxM+S8Nvb1e0G5jZ3H76PkNnFenyjPy4zivB4J6v/1u2Daobv2iTXHUNmEh8lHZLh8RNI92v8CDoAHysfhIPmGZGgfp9Gw0ugCb5IvyWOySX+p/UBq5UNilDjMyDF6wFR4OBwIj4T58Cg4ER4jG74XVsiX5CKYIxt+LrwK5mn/pnx4NzxW+zdNhM/CAviiYt2+BSfBj2ERrIPFpr2hDy612bLnfYgdj+T5qDG7dmw27ZnPxe3aa2vXXtv4t81h25733L/Pvr3kueazcdc+Z9m52y9oHlv39gvi9u51tXf3+Aj5pFJSJelB0hLSKlLKx9Q7qYg0kzSftPzjuO07fsSP+BE/4kf8iB/xI37Ej/jxzzlaav3/pIp1X/+/o2z/PSzb/0Hph3vHjR1yQLo3M33MyNHDZf637Pq3JXka1jWPcrGvf2biNcmuH5pR03Yzp439k+RwG/uCCL4ESZFkFjYd46/exp6ZHWZjbyhrDxcb+zITizWSXGyg0dj37TKekIxtJKMb6UsT79qSkYfNK0xONDLq6/PzkLhyyyhMoS8Yt8ycy6JUh05pKBIa0/crE+8mQbb/vHXT6ZMQnX5Ep5IKZ2zHOukwSzpcQ/rG1L1HOpStnQ4dpENdB+f+Ee2llz1GSFJwXa/b3gYtaqOL1RbnbuP659no3G2PkW137ja3yLY7d1vcv2d97sKAje7ZTT7sfdnUP6ad9OERV855+aobW85GZ/Xr9PdN2NSSGrHlbWc7L03ndWw0P/V/6hcjn6c+SX1VpPOmetRvwFk6rz0sstkaE7W+tJtsgDvAXlpX3BseCHfTOsM+8FjZ/kpgP3gG7A+vgHvCa2QTfEI2mf6fGLsM6ZPmXWcYt8msvU0mbo9Zv/aYaZ+0nE0mbo9ZN3vMLNpqAWm5abNPqW9S1qdxm0v8iB/RHi3l/59b4msW/3/NAdB3Bn37jVvx2KwxQwhfO1aTAIE5gDttcwCZLnMAP5DP/D+7mrFZeEYx+tl/r/GhfUy6KMIcQOnvEWTG6Gu/5tDI8wB9XOYBfjS+0JHKG4O/ff14t0YyRmpvqnT520+jfPK3D5cTxf5U0fjZd3D62Rs3+4b97kxbBG64EH/4zERXf3iO9eMPX53o7g+f6lm//vANPtqq5Ar5Jk+Wb3IN7SPfZLf2iSJuObFR/+y61v7JgaL6PW7tpf0tnXv5rfqbfIxjnb/4t89TxH2MrfmLNUkBuf0PX3hj9h+nDm2/+3dbbXjh3i03f8FvUsT5i52D8wj6HXGfv9jJ7lOr/Do2kt8Ij/pt9efZIbHSestndTfYUfMJu2g+YajmEdLhHkG5HNH5Bqd6mvYNrjFJ+lXIp9bM8S7WeYOk397yqd0PBmJ+KjbAEDhEPrcF8rk9ST63lysmwe3av22u9m97Qb64H8oX91P54i6Do+AaeLD2V8uAu8JMxUg9xMiDY+BRMAseI1/cXPnglsAj4GT54i6w+cJuv4wx47J/th9s6bL/z7xL3Bd2/c+9tNS8S9wXdt3nXqYv4zvSEpIJlNaDNIJU9Hl8/uXfdLSU/T+3MMcM/9dp7F+/9v+8cYGx/5jR2YdrAKNRv3lP0TmLbOcMSx+T5R2Zsf/o4FbNDl+BOUn8/mvcPM0=
*/