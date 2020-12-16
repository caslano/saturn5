
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

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

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
jRU532Ab3I7tcAf64k4MwpdwFL6CEbgbH8dXcQHuwc24F1/A/XgKD+CHeBBz8DD+iH/DepU432BjPIqeeBzb45vohycwCN/CUXgKH8czuADfxR14Fl/B9/A1zMID+D5+gefxOl7Cb/Ey3sCP8DZeQUcuHq6iE/4dq+DHWBM/wRaYjUb8DNvjFxiAX+IgvI4x+BXOwK9xLn6Lz+J3uB9z8V28gefxJubgLbyDP2I15XcM3fFnbIG/SJvw3FJyTSXXWnzPoDy7ulZKxhmT38nq+DA6Y0OshU3wITRiHfTFujgQ62EQumI0NsB4bIgL8BFcgm64AhvjRnTHbdgEd6IHHsAWeAo98V004jlsiZ+iF/6GrbCUck2BVbEjumAnrI+dcQ0+hpTJ4I+PYg9sgz2xM/bBEOyLkdgPZ2F/fAIH4WIcjKsxEF/FIXgeh+J3OAxv4nD8JwZj/dKcl7A9jsbOGIaDMRyDMBInYAwux1h8GsfhMYzDk5iAX2EyOin9iLE6pmINnICNcBo2xenYDWdgL5yNUfg4jsM5+ATOxY34BG7FebgdF+BLuAjfxsV4GpfgeVyKV3EZfo4Z+B0+iT/hcvwdV2B59reVWBtXYQN8Ct3xGWyBa7A9rsUAXIeD8FkMwg04HjfibNyET+NmfB634Cu4FV/FbTiJ7ZB7xuH/+nlrcb7Xr8y7Dv8xz10L2za+OJ696r3bz4U68SWFkmaRdpIy3y15BlsylUwlU8lUMhV9KmP405//x8WGF0/7/3bOBusz5R7y/N2fVJrUhfSdJ9cfjSzP37sP6j9kQMiYGEaxComITRmTzDoTwhJSi9YeOf9zHJ+qv5ny4u9cTZv+qxLbCYntOOkTYnN9VBMbAxMmm9oGFDwmm2dLxNDNtE7+xjaaP49RfVY/B4+Qdvg3SvE9/BbnGYnJTRNTfJIpFqN6H9E+91LVT5ilbuRzuHyuonnmlSvvAAhvaTt2W7J8/5bl31vlPSeV5U2NEmQMMr5DnrKOa5bPXubP1y3rkM/Zln9vZX7+k03F+FEPK8lztLvqeY48jwqT8X4uWz4nyrM2+Rwu/37V8jnRYB3nbW1j8/rmy3Y4qvrMd6zvrLwl2+G4MoYFHsFP2Teymmi2gzJoZAHarKj3i4hIBo7UbA/GjjTFs9DDHM8CzX6RLiufIm0zJpAW8p0BzW3joQXNPfudKM9DX2pueR6qv5/ckXEOCdSmfUviONt6cixrXvGzcgytlWMoVxOX6egpRJ8R7fFTo4XN8SLPjPks+VeS/CuQFinPjFvY5h8dmWpkY0WFjeG5ZyHiUJ9b1Pne0cl3Mflm6eVrfeBa9Hwt56ykcvrlzdbLV3lwWwx5XtPJM508c/XyTImMjCiG+g0ur8lT2iIZPPPlGRKWktAyJCouLLoY8r0j+YbIcTaS1JqyVtHJ17I7Feb4V+dbU45/5dxnXZfOeVkd3wk5sAdIvfQjXadeMvTiS0ueEGnqulS0enFSxWf5XEU+h6H6HSzhdvr0fOipOr+qypFeQb8cBqP9ciQVcfsWRzl6GvXLUaai/n6aZLccCWHxhfg7wt4xuUDy9ZN8O0m+s3TyjYiMLtTfLuo8lbIflLIvUZddCq0t+1LlHKgTQ3xiAoGEpYYVcRuqy75a8g2WYzRIjtFsnXxNp8AiHp/VVPuNrEf32OwlcdVxzF8fy4grtGX+uExtZziDKC0BU2ITE0KUjo/3UTeWbbJSJ4YMYkjSiUE5VSuNxwrzu6zNN0Dy5U9s0xQg+fpb9kfbfHUbjxY1f9O+2VK1b6r3EYmnosTjQHpS2Uc08ShjnidGhCRGFTEG9d9orZ3yj0e7gjxzNXnyd/I990dTmzU=
*/