
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_CONFIG_CC_NAMES_HPP_INCLUDED
#define BOOST_FT_CONFIG_CC_NAMES_HPP_INCLUDED

#define BOOST_FT_BUILTIN_CC_NAMES \
  (( IMPLICIT           , implicit_cc , BOOST_PP_EMPTY                ))\
  (( CDECL              , cdecl_cc    , BOOST_PP_IDENTITY(__cdecl   ) ))\
  (( STDCALL            , stdcall_cc  , BOOST_PP_IDENTITY(__stdcall ) ))\
  (( PASCAL             , pascal_cc   , BOOST_PP_IDENTITY(pascal    ) ))\
  (( FASTCALL           , fastcall_cc , BOOST_PP_IDENTITY(__fastcall) ))\
  (( CLRCALL            , clrcall_cc  , BOOST_PP_IDENTITY(__clrcall ) ))\
  (( THISCALL           , thiscall_cc , BOOST_PP_IDENTITY(__thiscall) ))\
  (( IMPLICIT_THISCALL  , thiscall_cc , BOOST_PP_EMPTY                )) 

// append user-defined cc names to builtin ones
#ifdef BOOST_FT_CC_NAMES 
#   define BOOST_FT_CC_NAMES_SEQ BOOST_FT_BUILTIN_CC_NAMES BOOST_FT_CC_NAMES
#   define BOOST_FT_CC_PREPROCESSING 1
#else
#   define BOOST_FT_CC_NAMES_SEQ BOOST_FT_BUILTIN_CC_NAMES
#endif

#endif


/* cc_names.hpp
IhZkAa3d0cMpEW/LDcXv31+4I9GIWp1yOLG0UFRYN+X0oaU8NzmVWQ3/mvaLJlayeAsnxV/H1uAA7nR34bfUeNa42zD4ZQl3hVUhY8cBMdM4lHPPnmHm9M58o3aZam3vwGdHPne/Pwj92qSmM0hih4VRgmPNm3z+CP6sVeBflUgcsyvi0dztsqGiGwZHN/C8cSqrh33Gnp1b2FnWCKUHmRjtMgXPqmNwO7un8CmsgebEd3K4bgWnXvOUYSq2LJwRwpd387G1a6jc0qIRG1Z0YLcXUzD13QhZeXU0LM7fkoae76i0dBpnnvuCvZp21Pvkh/1B74VZnQ0aB79m9dTe0N/fXpbrTMD47epyzxFH9Dz6XBYM6MHmZb/lv4tt2Q895Y9a8pyekmx8V4933lvBIS2b/ESKsHE8yHlPreVHw7Ms+ApRaFzG4LUH6fXgDmafMJItD45D+5im3Opijy0tposr64zo4zSaVT5puLUxhGFrK3FtpIsY8uA6z8SuFXqLNqKTa0u574AT1w0/hKeu7tjr2UOm7q/Hl5eD8efhfo50UsfPD6dQ+buCE893oFutPm3cHGjhVyus37dF/xkDWf/kDF8YdpK3ezXtk56mWGzVl+r2NrJ7t7bM+vRC1kZlo3hHFZ5vVYHTmCdUM//Nyi1+wkFjGh7nGMpZN0Jw+fVOsbe9I3IGhsqMpNfwdN3Lg6Nj+NxgouwQboRwvdky2fobVbfZsCSr6S66dOQ6Xy16G3xizMdoPu+iDO9+q/kkfzvuFZ3gmiBHef/Fa04prheNa66w4oU7yzbXMc1nLlRatEZ1dzNRZbuNAeE7ZE58MQY3Zb+opep4k3+SyydocserK/xhk8XN659zd+vDvPn/rsS8ZFB1qFzvvJQ+wyvYZ+NS5oyPQ4XhTj6PUEbn4a0wqN0LOeyrHm5aBIllER/QzUFPft3djmpmJ/Fm9W183acpPePP4v2o0Qw8nQHrz1PE+2Pb8dTCQxTFFcHyQ5y4fmcvVVvZUelxKHxuRws1477oumGFOP9iBJ0a83EkOJ51yYdllIUVKsyc5dKtJug9tanvenEzFd07yylZS1gpvLCiKc97l1siNHMbRx47LcNbzuTZuy5izrXNsDz2TphUfaZz5y6sSHJhG78/0k4rE68v/5NWrUvxX+lkkepxkvqVp8UmoyGwVvHjnZujMDTRh1s1ekFXabtQH9aZ39tcpMfIcPjsrRZHF/tyuM1UPE5tzyHNJ3G61xzeMRgnHFQN2XrpdiivnMRR0Q0I08rBoBM+0mB5JoRFLD09YnBstq6cWvgZo14+5nnnCOqWeouLpT9gWX9NhNjsoun633Kvog8vJe6Qk3/vxdemGW7e+Tf1xhjzZG1L9BlpLJY+nI1NEXlo6aZEq51j6TJzEQsTe9NguxU9Dm6WnjYXYHN/ivxj4sXWL5OF4jUnfOvaWp57/Ab/fQyG69Qqlth3Edav+/HDzfuiKNuPs1JaM3TsEyTn2sq//wbTfZ6HaLxxjGGFx3ji13AaXVsgOmVnMrz3KvFUEF+WDeQZwwoc/fgWw3p0xt+3XcXYCFvO8L+LsXeLOXWQmpjzwwIPr9VzbH4+FXtHiYkmM5GUacLdkxSx6EQtyvOMYdJ5ipyZmYn2CtnyxPHV2Lr3t/B0GMlRVW3E9nfBXH9qhfAfeJMNN57ImVcnMa/uvVAzVcTJ3L7YvdIeL9s9Z8h0D7iecmenmX5MSL4mAvc2b2Ks1rJQtS2dv/UWx/aXMzDInMP4jOa7v8qjI97Tu18tbmf8ZdlUI7jazGLCIzMZYTCCOV9uwfBeLewGPpddb61FxqcojJt1EgvunBB/S9fBf0QJUtUmYVs=
*/