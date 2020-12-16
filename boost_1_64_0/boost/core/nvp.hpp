/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

namespace boost {
namespace serialization {

template<class T>
class nvp {
public:
    nvp(const char* n, T& v) BOOST_NOEXCEPT
        : n_(n)
        , v_(boost::addressof(v)) { }

    const char* name() const BOOST_NOEXCEPT {
        return n_;
    }

    T& value() const BOOST_NOEXCEPT {
        return *v_;
    }

    const T& const_value() const BOOST_NOEXCEPT {
        return *v_;
    }

private:
    const char* n_;
    T* v_;
};

template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) BOOST_NOEXCEPT
{
    return nvp<T>(n, v);
}

} /* serialization */

using serialization::nvp;
using serialization::make_nvp;

} /* boost */

#define BOOST_NVP(v) boost::make_nvp(BOOST_STRINGIZE(v), v)

#endif

/* nvp.hpp
UoOHjGThMlMnqF2vrZna9dqaqV2vrZna9dqaqV2vrZma9aLGrFkv4qlZL+KpWS/iqVkv4qlZL+KpWS+eiGq3RbVSu16aJ5i/D4/Sf5l2SB9gdIltar6js31zvfcakj2RuO9+e917In2bQu+JToN3BFQ2WsLadcrAMrsX4kskt4X8m4k/oOmhxaytEMtlFN1PUymWC9P5ju72pjANyerc0tUk0Td3ZJoCWUcPFytT5VJpiv2Lp7OPY4Xyszawx8+pE3Yx5v2HRB/H8o3hOwIKWm/GzTMEfKLAdwyBb0UaH23c8czpPiKf/MZhpcxrPuesA1ZFpgyrZH6+915bbpQi974CfyToYI3ExzrA/M8S+cJ6LcgflrduH4XuF1J//IzoBzqH8++L02kfqInDsNq8DyB/IH4zCN4cLnV5KNyc/b72RrhPotC8Gzv5R05arUrz3emNDlalwumsuQ+dS/iDyQd0ubpXyHfLtzJtEmgPZtqLgLaDaLNEawHaQ5k2CLRBTvtaoA0x34vvZmn7me9i4DvEfMuBlmVaBmgFpl0AtCLLu0LR6r0zQW1fUCsgavq7L9L8zW0Dfedr/tJsJVfwkgawLLk4k5uazRdqcNdkiw/ImbntSJRp7zjPYHPdXW36W/RtlQJZWVRgDi7D8Qs1ulhA+sg0efij5rq0UR9XIrEveTW8f7g/2zM0tGtgcCdR+4b3ZA8MDHZm6O/Bvv5t+3cA674L9/b39A0DZXBPtu8Q+a4GevmqLmBDA730L00e7hvY+6CRFiofFtCUMN/0b7Yjuqfj6ayOlhiheWeErytFbR3ZjpEWW44aOR9fhgSrPA50NrcdzXe1b21vbtsRqf9tp5/55raZ0lRpogTKoNsXRq/x76x61p1Vh6i76Q8al+66/CT1JoNGwB/QaPhD+vkR/dyN/n0K/agx9sfN1G92FqvRSEd7YtP056b2TR1dnVs7N7WPHC3OVKpUrn2k+YPePPx9HmN/Qr/d93mj2r/IEyF892djcO5CzxFnSjm6PlKVZOSm4SwoxKpTUYBfutHEaSIWWmyq2QW+HxsF+OgoxkuYDXA+GlL/7O4yY/bRNL4FZeUL9cliPljfzAc81dEJwhfQLX2f2yjX6HYl6M8/a10MmHkCCfhj/DLoFUnYbrSV4Iax+1anfOE8t1o+m+PzXpin1wQ4NbDiEcuxJSmHgDEUpiO9BLb7eFt3gtEu6J+dmUB+IZcufwLtOsBku77c5j8h2e0xBw/KZ+OcpPEtKCtfqE+WtduWtHJzmBO0q6cDD9i20dsy1BuvVdGeGQvOf59JcolG7mka3MDGngX5SWPEYpAp9YPnYHrsB256TBvYQMnYB8QTJrnFSK2Cq0XaK1JAWorSPEWvZ727li+2+ZMYtgXQ+ZUejm0s84RtF+Yjt91VAY/cdgQG989eHqRlDki/EtL7MRKvDtPTkjyOCBiMacQgtuWrAhmKy6Z/jY+zrQTtmT6eaP8hg4nc2041ch13eIuMz84YDhivQb6tXGhr5Pc0ZUvkv8nWi2C0kVD3xBDOFYChXi9oZP3ueC91XP27/L+t5xtZcWveppW0djuR125r6eLN60gjr6efa+nnKtLvOURrIYktveePDFVKE7Rpbt5enKJc1s9t6d4wcoBeNZaORgsv7Wan77QId3Xo78HPPkuvD1vp952xC3L0BT6g9VY275HfspH0dIaOsfPghvaRY8J3cs49C/0H2J/GxmFp62N8rpmgLgZLAvCzLdaY6UJuGhxW+Hv3VM+vUT1XEc9D6n2HquppPKeSv6TzLFzL45okSYW1bpFwXPSR/DSeLcAj52NrLOPVykI4atmMVYBbTcv5o8aVvt8=
*/