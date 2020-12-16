
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
OARn4VBciMNwOUbgOhyOm3AE3o+R+AyOxiKMwg9wDP6KY2WO+3HogdHYE8fjOIzFaRiHt2A83ok6PIAJaCdzp9+EydgAJ6P038l1MZ8lmvffNeRte2yEDdAZQ9AFI9AVx2JjjEe38nlX5NoV1POumI33bIUtzeaD6YxtsRu2w6HoJdv3xmnog4uwPS7GDrgZfXEHdsSD6IfF6I/fYSDeJP1rfhiEASjjQ/k7J9etGCvlUYsYKel+qBrpxi3YGh/B9vgodsLHsCduxV74OI7BJzAaC9FwntvJ9SfOkP3cQIyW/TST/TRHN2yJHugh+2uN/bANDkdPHIdtUYftMAe9ZH8ZxELZ3xjZX22iTvaXKccjC50wB5tgLrbB6dgRZ2BXnIl9MA8H4yw5TrNxJM7BDabjYW3uU7JmHvqfMxxM+pbqTGUcLDGMOIl4J3EH8SSxZqaDnQ8xnKjL1PqdtKAFLWhBC1rQghb+j+Fq9P9PjK+6/v+PVOP/20o/eT90wSB820u5cU3d7s7uLfSTB9nY71SVY70rmqv3tFk79VmWj8qcxso46u287lS9dB7xJ9xMx2eTPrZfOuZ7C2848jklsz3dy+9fP65svzTdMbxXPt+0IW28pHr+vnF/IWxnLh5xL9/fKQtjvLdLO9xiTG9S/tl9Zvd2H7woDTIntpSP8mJ9Gauc76qUOa+Y7eco+3kUazYt388XFsaSv+5m2l82yt10+XOz5aVNTJedmlrufw6TE+Zl6avajcp5V9DMwnknfZ7W9F9czXPNwj34cg6V5v2G5qZlMd1s2bXFf3Ns+DpDH8q+5fVG1P3tYKPxKz8NP5w0vV/l+lD6V5ffIvmNKsK+RKr9BN6Xtv+h2BSHYSscgTdjpOre9y4YhcE4BiNwLCbjOLwNo3Epjsc1OAE3YgxuwVh8BONwB07EFzEeD2ACHsdEPI9J0lY0CZ0xGZvjZGyHU9APUzAA07AvpuMgzMARmIVjUI9TMBvnYw4uw2n4MObidpyOz+AM3I0zcR/m4WGchUdwNn6Oc/BbuWf+N5yH1Sjj+dgAF6A33oqdcSEOw9swGhfhBLwdk3AxZuASnI75OBtX4CJciXfjKnwe78RXcDUW4xr8Ctfi17gOv8e7sAbnwd3YCNejC96DLfBe9MKN6I8FGISbyvuS5DeG3x6zuRTU96g7YwN0RVdsLOdXE2yJzbAtNscQbIETsCVmYCvMQQ+cg61xEbbBO9ATV2FbXI3tcD164Tb0xjewPX6CHfBzvBm/QV/8CTuikhk/rI6BWAc7oQ92xoEYhOOwC6ZiV5yD3fBW7I5LsAcuxZ64BoNxI4bgFgzFrdhLzqvemHKVxnzn0d5WoLW5aUELWtCCFq6RUIOYeMXq/wmpjNWLN1T9q6DuX1zfrmzcqYdc8zgQ7YnXEd9RLkAaq+tg7Dw7MyEmLl6fHZcSk5U8I8HOhrGO9hROhj7TpO63zsJ+32W/KyzuN4UaV5w+QWf9Pp0dZZ+q8YW+Ul9wlX06E4+xzwJL+0zMTEioRB6NYyOVCmYiJc4/Te5RTklOSwCTdO2zkK4PSFeRpXSlGgrD6nRll96nbFO6ehnLy/7iY/Qh6SquOF0xuvQ0q84N9X6KLOznI/ZTUvF+DMNtrdlPfVU5yHlbWhaS79TkNOVlk+dW+dSwnG87t0unJzkuhU3pLpsm9bHPt7CvJsqYUkv7ys5K0FmRZ/X2A2Q+v94yLjRYzq3mlrY/w5AXq8fU2npuGdtL+K5wb7y+rL1j3yXaO6hf83pJr6Hu2W2X5b/o0n1ZreILZ2i3MrRrNN6Tl/97q6hdt+UOfHLhC08c5L5wQzvCwxsfCJtfw/5Cr/jOj6Q=
*/