
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
ufg8zsWXMR9fxUL8BOfhVzgf/TmvCzAQF2JrXIzhWKzUCy7BJFyKI3BZzTNW5b5LKZv6GavaZ/cGY0cMwUhsjT2wDSZiKF6IbXEKtsNpeLr1WcZyrwTLCbbzAX6WfH7FQPwNQ/F3yfcPjEYSKO6jgLHogYPRExPQC0fgKTgVT0UT+mA+NsVLsDkuxpa4DP3Quj5loGvrbFZKvGZ1xKsKdG2dTUOQa/HCglxbjzNe4jWrI15ykGvrcea5GK8kyLX1OMuCal9ns1jv82zQPk99fsb/q/9z1HpvQxZhNWEH4QDhEMHraj4XhFGE+YSthAOEQwSfDd6GSMJQQtoGvd9U3/RN3/RN3+q/Ndb4/+n5eQ02/z9RNQbAT8YAeBM8JRxW+gV91P2OyYnDlP6fWttO6fuxWdOsQu7Dd5BHCG7Bs5Sbbru0lZ60eSxsVp1+lsv9mtXttDIe2+Vx4pY+zHhKyYPW0rNVfcu92Dc9M29Whjy/sJ3BslaZZZy4/ZjwDTbr0+2o6R+09imONveFZRhCeb2R15fI+gc1i7qRvvRH2vZ5l7JPsw6bjG9Y7ke8edVxNvNatX4bcfr7JzWtvgchL/PrW62v9XHoehu2+23Yv1WvnTbpVG+fXWd++/AfVUeuuafTu43Thh1pkO8k9JY2Fg9sR5A+pmJPDMBjeNQg3zPy/aPEb8ufP5H4IdI22FHVNhiOnTEKu2A8dsUkjMLJGI3TsAfOQSMWYi+8AnvjOuyDm7AvVmIMfoqx+C32xxN4FnaTcdWJGIfn4WAciwk4FRNxMQ7BNTgUN+Ew3IJJ+jjqBm9TOBntCeUrvU9Km4I+lrr+bQkHaAs4rLcH6Ju+6Zu+6ZsbW2Pd/zOOs8Hm/w8N4Pek3KNHy/1/c4InoSnhDmW8o7fco2sG/c3MKDSai1JgcKEtwHJ//oeM+VTPr98v+faVfHsT7iTfKm/bMdhDxiWfx4Bk5fkDbuQp40xrHdesnkdA2ax1MsvDcdmMp9iWbUZ+Jqv0Z12cIwVsnPL5eNqXbzvlK669fCybXv/yfRzoevm2eTquv8o6ysei9vUunyv1Z7n2hsrg5V5SPiPhbsoXdqpt+bJyp6dnmYd5u3O925YtzKvuslnazI5L2YYTWhCGEO6hbGmasvE5NH8M+UNO3WPIA6Rck7nRtXx4g1VjGs0pMXDcbpw4wXYseeY0GTds89yC86W8Ywn3Ut69tuXVnOu6x5Db1aWUK9FcDkb+27Q1Bsm4+25Sji6EMsphrGlrjLVM6THPtXFhHLulDDJ/RjOnQz1f5w+2MPM+ZYyp3ramt62537bWe4Cy/+VVZanf3Xv2p591fOftd0I6D2mctjWjQf69x+bStuaJ4QRly5C2tRnYFGfiMYwnVMn7+sr7vLGPvG+YvC8JI3EE9sSzsTeeo0rHeIrzdCIlnS6STpSk003S6a5Kp7iWdAZKOoMkncGSToKkk6hKp7KWdHpJOr0lnb6SToykE1uTjvybwnscpBMo6QRhZwzG7tgajdhGlU6apDNck472eQ1jsSOOw744HofgBOvzqeV7Wb6vbZ9PPVG1lseZmIJROEWOayrGYCqOrRnvxPHK9yx2k3S9MFrSbS/pnoGBGIZdsCNO1Nss//Ftlo3WXqmPf3K5zdKPf4BjCWmE1YQKwicEn2u9DdGE8dfq7ZmNsTXW/P/0gpy/PP8/1ODr34zfsicWefEbVX6aF2TMTS0sNETI3yUvVv3duQlDUocmjE+wRGJrTzz/YO7xzPH4ZU43+Iz0oqxC+fuO/P19EcxRUKdD08E4fnxPK5yWZYkzkDTCim3iqPLpKPmYlDjm2beO87q1M+OJJR1NU4Vk11GOK3w=
*/