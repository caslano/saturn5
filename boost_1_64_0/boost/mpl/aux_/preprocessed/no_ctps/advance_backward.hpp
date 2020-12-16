
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
OBijMRVjcC7GYRZOwr9hPL6MCfgpTsX9mIiFmIxFaMRr+ABWUv4OYAdMxa6Yhn1xBt6OszAGZ2M8zsU0fBDT8SGU94lJ+xFTuxIit36f2COsZ2qTiv6YiV3wUeyOCyQeyhppB0Lek3KwBf/2RWUaKvk+HP0xAm/FETgER+IYHIWJOBofxnvwKRyDL+JYXIPj8A28D9/H+/EjjMK9GI1fYyx+g5PwHE7GYkxAJbFTsDomYiBOw66YhHdiMo7EFHwAp2MapuHTOAOfx1m4FGfjazgHv8IMPIzz5bndQZ207cBcKb/8+PduOd/L5Ty9JOcpFwPxZQzCV7Av7sBI3IWPKNvjJtyLW3A/bsWDuAcP4WE8jIV4BJXfg0exAR7DVliIBvwGg/AE3oYncQqewifwe3wBz8hx/4Dye07agnBP4uD33AtSPi+W8nmJ/B56Ee/HZVI+L8fp+BISL/V3Je001PmrOf/2RGXaoidefBf9cSv2x/fxTvwAI3Ab3oMf4v24HefiR5iJn+CzuEMvv6vxDdyFBfgpfoWf4VHcg+ewAC/iXvRQfo9gTTyAtfEwNsajGIDH0IDHMRJP4AI8hVn4vTxfPI3b8d/4I/6ISruV8yjPeaStB9s4eM7zspyXV+S8rMBAXCnPVVZhCK7GMHwVp+A6fALXYw6+jstwI67APNyJm/AYvokncLOkK10n7TnwlKTLGxMlXQ/I86cUef40HYMxFftgGt6FM3AUzsQoTMdlOAcP4Tw8ig/ht5ghz7+26KQ9Bn4m+/fF9bL/i/J7uVh+L1/ClnhZfjf/jL3wCvbHX3A4XsXR+CtG43/k9/NvmIG/o+nck47nwQNfwsq4Cj3lOWlVfAe9cDvqcSdWk/Tn66RtBfaTcqK+cn7N9U9y/mrJ+astz+985PldXeyLDfFOHI3D8B5MxrE4F8fhPLwXl2MkvoYT5HxOxPMYi79iHCq/9ydjNYyX57gJ8vw2EfvgNDmOeJ20ucBhch2qY6QcRyW5P/ZAX6yKTdELA1GPBqyGfbA69scaOBC9cSjWlN9pmTwwXEnYTjhJ0DXV6/wJIYRRBCMhm7CGsJ1QSLhG8OMBYzAhgpBIyCKsJOQTjhCuEHx5+GgghBPiCZmEXMJWwkFCMcGHwWQ6EcIIsYQMwlKC7fjVPpw49fsz80d6Wt6huXWrl8Mxrbdykm3HtT7CuqVjW2NYFYfjW/flwhSwvaNxrkcleem8iz01x7veEqB3aszra6TFX95zuZvjGcDD9SNnPFVjYTM/QF+u8bAD3/PinZZlj4udZ/O+yitGL7vxsb0peEYlcs7GsS/Sco3gz8PkvoQoQgYhl5BPKCQoD5gDCKGEWEImYSVhO+EkQd9KrwskhBHiCVmENYQdhNME79bkB0I4IZGQQ8gjFBCKCD48uDYQIghGwiLCZsIBQjHBpy3LCaMIqYRFhM2EA4Rigm878i0hgmAkLCLkEQoIRQTvQPZPCCckErIJ6wk7CKcD3WOEuyf35J7ck3tyT+7JPbkn9+Se3JN7ck8l058w/n9swuS46anKCwBuaPx/ZSzvvHrUrZnH264kdQyEmgTT8+3Oyvj2tXQyztwA05511x8/xdwnqqGPqZ8l6Sntu5amk35SKP24TH2npsWq+kDyeXrC7Djzdn44xl/6vMk8f2yp9P+aZuSxcem4W6ENS/uMFav6oqvH1AvxsO8r/VYnZWx9m2MdlJAUneh8H0P1vr1tjstHdVzq9Er6rMYUvCbpe1PSt1HSl+8wfRPi0nXX76dW3jReUaVR6fdY+2hJ/c0u8oby+Xb5/Cmf1eeY+kzT1Iqg/LMF4TMlPx21OYY76RWou/64hbbpl/ykzhc=
*/