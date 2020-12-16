
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
MmSXsb9kZxVRS8m8y2BlLGuWnI2tTPotzPqdMiEzqKUcqsmUOTmWepqkFVNPZVTU3KiiQALLwQIN1NQ6bQNooF3bQl3tpLLSqKwsamukTNc8fSwYfxIa3TTqa5Zk/hdRYcv05fpKdmoTe3VDtFfBDjtBD2ns1ixqbaRhsmPz2LOF7NpiuHoZFTeXmlvEvl3Gzl3JXG5iMm8AP7WDnbaBOFLATBngpRywkgnmyAMjFZqTzGImdxkIdS7e+SKm1TLQ6UqU4yaw+gaQabu5BVy6Ex8xjfmVBSYdaZkg0jxrLHh0klUMGi0j5TEXpXgRSHSZtRwc2mA1gUI3WEr2ECWXtSz4hp4gX5JlKrYxtzrN6ARuVG1Z1FsOFTfSVd2vnxsa6xbInIkqsUymTQW1uOgrD0OmTgNz57t8l3CXE7Go692adTika5lCG1DPWpm33+VN49+sGurl69XyFyslQ+pjokybhrBRHGSmgjjH1LY4xuxo0caGKO380SGoctvuE+2ChHehYJ5ikTzHUp5kOc9S3uwuyKABFT/pvCzn/tq89q5s/MiuPHxRl0a3SO6MOwFdZjFBC+IV8blovvVy3VSzvFVlrl8piGkLLkk2E7GQKgYl0ccaBb3Ru6RW6VjcU1OXB57W5XjndvnbZeJm14pz3RrNtYIhykT2SLp0+zypwnLp63RweXdYhEIVmTSqYXYh0RLRpejVwg9gAqDoQvZxpdz3lmhfyfvEKtmbDTCjThyVHNEwJwkOarSbBEWCekA8RfL96SZwzg5np8PekX2DcyV7pZY1BKewN9rkm7+cK5A3zUc7gF7Z9XVHN+6DzVlDQaKzZCVr5AudrKfsiGg35OPyFgkaXdSFOOiTdMnk6WJVzlkVCw6tlt64TqaEIjjUlFU2E650uwjnz5JORzJAsgBdOYCiIYL5maAwlzK1Am5VKXNSZqRMxsg3SNPS6WzZWo6ghALBCWVaOT2tkq6WS6/CQaAnNQqPyTFGsP6TxEFYS5dRSoeIFlDCzqti59VT2230jFS6hUqfmEiHMO18W/y36Cviuyd+O4mPLU5U8ZPcIuq7Wup5paDH5uiLK9G3RqMKlrXf5sEbZD12IfL6MFlHzVJBZC3QOodEM1HNlnsvVwu4p1rBO0rzEMXcQ1F4+iTIW+0O4RKK8IhMJ+kWquIT5sv3CYrky+floJS57I9qZwnXXgcebhQ83OK0cQ+dsmNS3WQHy5be5UrXKnAnclcl0q8q3ErQcbX0qrqoT3F/G0ARHe4W7lPxUsDImV4Wd5vsX7nSuSZKzyoV97RSulVNtBNhBU0gZnqVrIcSS40leUSOIOZ8OeuCEp+sbulgtVLhjcmuJTu2U2Z8quDmiE/m4l8VRJxS0HMF6HlevDrau/LdrLUy+9tk9+6QeS+zHhStSnIquaMnsqeLhWVVsa/hWcKvmnFyW/0OeQOlIowwMzpBH7iBj35dkHRchX2Vy56vEtZVG9Sx9xsjXCA8sVOwQWqEsuXZuyDtCCGUCGesCCtFnagRfaJeFIpm0Sg6RKVQEugUgrpBTqJV5ItaQWeSKpLeJHpFY1KxkFRNZ5JBtw1RtuwJf05qFoJNVUEN+bu1AbQLqbAqwaO1gkQbpYO1iEPXKd5cupYByx4Z1Rk7chJ4vFQrkzqrlrfG18n74tdqyY6/Q7p9up4JblB1UxA5Th5YvAqsUAOmXQ6qbQQrNAtb75D6VOSN15ld3dI1fFTCAnpmER1zmlEuE7hK+matOIGNUsUtorR0isaSKnMlW3QVVxQV9AmmTIlMmAo67DyzWqZMnfTatfJNI2Y5XXeHvF8jHf0qi5mughVy0a7G0gWKwAql6Faz6MdVYIU=
*/