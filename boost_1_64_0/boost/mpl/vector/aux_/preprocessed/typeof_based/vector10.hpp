
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct vector1
    : v_item<
          T0
        , vector0<  >
        >
{
    typedef vector1 type;
};

template<
      typename T0, typename T1
    >
struct vector2
    : v_item<
          T1
        , vector1<T0>
        >
{
    typedef vector2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct vector3
    : v_item<
          T2
        , vector2< T0,T1 >
        >
{
    typedef vector3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct vector4
    : v_item<
          T3
        , vector3< T0,T1,T2 >
        >
{
    typedef vector4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct vector5
    : v_item<
          T4
        , vector4< T0,T1,T2,T3 >
        >
{
    typedef vector5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct vector6
    : v_item<
          T5
        , vector5< T0,T1,T2,T3,T4 >
        >
{
    typedef vector6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct vector7
    : v_item<
          T6
        , vector6< T0,T1,T2,T3,T4,T5 >
        >
{
    typedef vector7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct vector8
    : v_item<
          T7
        , vector7< T0,T1,T2,T3,T4,T5,T6 >
        >
{
    typedef vector8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct vector9
    : v_item<
          T8
        , vector8< T0,T1,T2,T3,T4,T5,T6,T7 >
        >
{
    typedef vector9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct vector10
    : v_item<
          T9
        , vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
        >
{
    typedef vector10 type;
};

}}

/* vector10.hpp
X1OfA4o0iYp9gU3SFCn11HNNpKgyJf49Y2OPHFNi37fuuSdpTmgzZu7U+mKHPA2GhH/gHLZIU6LNhLkfyhf7FKjTY+FH+mCfY2p0ifYdY+Wn+iFH/cwvrPdfuf7pMmPTeklxRIMS58jzgBlz57OW2GDRutikQJM9+wbyF5avqnF3yf/JNgfmrUDJe1fNPU89Zszf6z/3NU0+fv7gWDz5obX3c+OlyYDA/iS1oXEyZe6X1gjbnNBmRPRX8sYmiV/LBwu/l0eGRP/gWmebIyp0mDD3R22yR44Z8Yl9TOQ39iPlRGk8C2ycEVeKPsFQn6yzR835Pbacc0iRFts/lnPaP3Gu+HIciK1Ag8nvQsFG3zxSoE6fyI+NjQw9Qv99vsc6KYqMmTO3VW32mDE/sibZ45gGQ2K/MTZ2yVFjQOS3csQ2Oer0ifxO/2xxRIVTQmNxsEmaMl1CxjKWs+XHGz9F9p6oTbb39XsgRv+vbua/9/LX6DEldkHri032yVGmxYC1s98hk+SIHUq0WPWZ1Qmd62vPva1hay7TlEv38DYZE3e/bp1Tjq6jbdqMiTq+wCaHrKuTIk+g3f2LiIcTWmweeH9STvnfPf/rZJ5y/mBg367tQ46p0j8bv1ycPjlw/5I1lpJ7+7IHcsrKU+VXP4EczdRJPsU6Y59jmoyZPzCvTB9j+7HeE9gjT4MhMe0vsUWaEzqspOSfPHWGRMWU2RcDfSJP+u/zOIn+9zmcO+So0mNGQuxrLKu/zREVegTiT7DGHjmqbD9aX5RpM2fMXfdnTwid3/sCmZueN6iaw5V9bZ2Nkx152bMvx67PPg/+ey9zjY2Hnj8I/ff+6jVGMXN/SWuENVJkKdNhzMJ/n3GQoUjy0uqyQ5oCNbqMicw5zg5pWv6/4JOmsTm3SZRTAnWTc2K7krm/vH2XtV7O7te3vXtl7V3NuC4njqsYr9fxy/j6rM4BdWbEHd/hiBNabMXFpI06wRW0T+OK2mVfX3X6JLS5Rpm4PlbY5oQJc2JZZpsMbVJXtYbFVfd3E308ZCRIsMoOGUq0GBHxd0sL3JMDCkz9rUX8av72iW3SFGnQJ3R1n6mxxh45qvTIX/W/zxG4hrFdU0xMWL6WcXNIiSZDIu71XyJDmSNrp312nZ/NC2NW5HWPPE0mJOV2KJdRuVzkkBItJszL7QbzcrtOijpDIvK8xA55xv999sIqdYZEz+aWFCXiVzcX5MkaX4cxSWOriDkxrx9SFGjQJ2Qez2GdqfHNqbvMFgVjSGpjj0X52qdOMC8f5nctKQ6vO2d5sQbaTEiJoc6ADceP2RDHASW21Q8l9XWt/9yL32HC3LIxsUuWOsmb6588dRL/ve++w4zELcXOASXaBCteM/rvffWr1Oizemvtk6VKjxmJ22iHFEX2VuWNHsF/75PPUiF1O2OiwYjY7eWMXfLUGTNbE9N/72Wfkbqj82gwsYZiNzXPbLNwE/klz5HXZdoMCcvNAhvsGXP4LG5xhPy/jhvqny5rn8SK3NAQf5/IqrhYEccOeVqc+Hu+Dulr+UyeDjMy2l+T4xN9FLTTJOv8ebGvkaKmvx4T+mdzcyv93hZjCpyXO8ux12te5wOf/dNhQszfp0Uv52/K2KC8oe27y989xMk2of/ew75B/k7yeBdjV460F1VukKLG/Lr1cWfn31WOtVW9m9i0t+zvHDc5oMBB0nVPlR77zllyTpoyPdyn73ff2qb1EDnV/oxtx0Jnx9gjS0edKSXxHivX9LlHjiP7RupE7K963fR6wIHxTLweaTvyULljVfwpCrSYsC62Im2mJIx/nX0KtDjnbjzUseuJ8Uau/RsbMw1j7TMzxvg1zu2eF98=
*/