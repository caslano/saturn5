
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
pZ6DpR+GwhAYBfvAYTDN9BmaPkPTZ2j6DE2fYYv4DHdPpX4nsdbsJNNfaKb/fton7//ZLfP+f25wQzyyHa3M97d/2/vb/npPa6n3Mf33z73/ntbbfL7f4+d789ne+WzfrOf6QJ/pzef55j3P749neZ3n+BZ7hvf3+d3g2T3g53YzmclMZjKTmczkf9on6/8z7faWWv+/MNgie2EpsWll/bwzjij+9bD17vX/zr2kcxq2lMWKIr/XzT9FYcXKHnmvo9FZAEn1Z+8SGwaLDYOQ0diQYmxDetb89MkTEv1fwy+2aPcS9vDhy5bJ7jX8nfiPrPl2a7GU01ny4cX3sH9tK2/7x2B/hW/7p8RPbL79x6OZ4dAi9pe19rY/Fvs3+7bfXhrAvm8u+0PEfox2joWCzHyHzXtUD5nPwoko61+lHiFIHPUIelxbjxxrntVuddYkgDgQemMorzDboy2rxIYwsaE7Eo8NkVobnFvaOXfQa5mxoBnLeZnFdlthsbRhY7tq95SMPNC7zRKxN0PPXmeD+W/n23601ybRHyr6uyJJ6F9kqF9O/QD67W0/zn1pLw/b5hzkbdsJ2FZlaJt05R7YJud1k7bViW0dxbajkAnYVmdsW3ZhSUFAcU/ENo9zbM7B+vcLywa33pIC5WrR3HPM6J6RJHYMbKt/z4j0ZYcMnUDaYG/cN1x1qG+rf9+wNVUHhtie1KEl7h2uOlQfon/vqGqqDvbSgMbivrh/xLXTv3/Ue9dF7iDNex7SXg/V9tzVzvv+MQkbgqoVG7R3kBYYEwObcQ9xtVvpofr3kDg9m+VqFIit/txHOrbXv49k+LBBLgd7ZIc/95Gq9vr3kYombKNLm22bv/eR/ofp30dqDG2TO0kAz35im3vuaN0BRj5DI1+Qkc/NyEdn5Fsz8kEZ+QyNfGUt56vU94Ua+RID930Z+e76LnR8f1eHlWMzbmh//ODj0nuvfeX9oUY+28B9fZjE3EF5j5TnhUX8cSCMkkESIXFyBsGuMBL2hIPhMXAIlHLkXZD/0yknVsqJg33hOHgcjIeDYIJSToWPckZIOdFSzkgpZ5SUM1opZ7OPck6QciZIOROlnElSTjKU/eHk3YRrp5Sj7g83QMoJhyHwWPdxiBwXpnNcihw3FXaHJynHZRjqg3JcH9HXVzlukRwXqnNcFzmuq/RjN+W4Kh/H9ZDjwuS4nspxdXJcR53jOspxwfAoGOLuF9IG4/Fmk+POEn1FMt6KZbzZlXIiNxj37wVSzoXSv4ulfy+S/l2ilGPzUc58KeccKWeBlFMm5ZyrlFPlo5zLpJylUs4VUs4yKadCadf6Dcb9P1fKyZP+z1fHabXxeFsux10j4+1a5bi4amN9s+S42aJvjjpOq9VxY7xvYlc4UzmuwsdxmXJclhyXrRxXU2083k6W46bLeDsFzmhj2S/zBYzmCmjnCbSfojc/wGhugDofoGXnArjnAWjmAKj+f9X3nzxV9fcb+/prEW8fv9a/r+/b9/br6/v0xZfvlx9f48P36b8X372H3345Etrop1d99Br/fOC+eX2/vKFPXuuLFz+8ng9e438P0PfelK+9ytO/vse+dX/86qGI6kf39qGr/vNG37mNua7LkRpkJ9J5WjtLHJKHVCDVyA4kKJU9SZAcpAKpRrYjQSezdwKSgSw92fTFm8lMZjKTmcz0T0/7xv9fXDDYMQFgD/3/EZb2R7brxBx/NpNtZXH8vHeSldjrucSZn2SdPyEH5s7KtRYR5/+sdLvdMoT8MSG8/w135SfbuNlFVqv7OOWg7DmOY8I55kd0pA730uGOpU4p6ZklpZYIKT+vibxijjt/lTv/lKLc2az4txcWpZQ=
*/