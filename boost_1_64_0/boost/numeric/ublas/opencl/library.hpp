// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_library_hpp_
#define boost_numeric_ublas_opencl_library_hpp_

#include <clBLAS.h>
#include <type_traits>
#include <complex>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class library
{
public:
  library() { clblasSetup();}
  ~library() { clblasTeardown();}
};

template <typename T>
struct is_numeric
{
  static bool const value =
    std::is_same<T, float>::value |
    std::is_same<T, double>::value |
    std::is_same<T, std::complex<float>>::value |
    std::is_same<T, std::complex<double>>::value;
};
	
}}}}

#endif

/* library.hpp
Nwa4HUNPrMnKDwDyya5nEw/TlYZ5xe1Vci5jbitcfdpc/zIy7SzOJDFO/9byJXf0nMu39rVbBe+8qMISajWSh+v/JatUcoWBKqSELxl3Na+8dYKuBB8BJzKrWJDuwlXoSAaSQw5/UGFeo4WNdBk/2PZWm5PaXc+k8xZkYzoivjSXdcoq2xhHF8GXJ/O5i68rxY+H+FtlZECatfrivahRqVj58bKB+pYRaQx9tYvGwiDKqIgO1SduGorfBcJFb/3OtOPYcMm6iNNDKuq62gqDl/LSl17Sdsn2Qt1AYeH8CRVPDOw8taasfaBeN7Lufs3ymqd4XRjcuSzYLCRpMCIT9v7u+0gc/LKbsRnisJ4EBAJQSaS0MpVEYyp0JYMQVWf1oj/rHcnv8wB1oUSJm2B2MgLePxzVR4XPJmRagqveFFfNvATD6Iv/mdcaEvKCKXLlwBSF/WyZk9ldXXvgjuApooNczgmdj5SQTJThHPf/qaGPP5U40u5KeZdCGQ690P73D0VnlRtZKei4RsELdmTDRLesAyRqlrTIifEn1VGZ8sXCWxsr+Ok8OZ9keA==
*/