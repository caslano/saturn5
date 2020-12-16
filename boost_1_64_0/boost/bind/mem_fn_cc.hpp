//
//  bind/mem_fn_cc.hpp - support for different calling conventions
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

template<class R, class T> _mfi::BOOST_MEM_FN_NAME(mf0)<R, T> mem_fn(R (BOOST_MEM_FN_CC T::*f) () BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf0)<R, T>(f);
}

template<class R, class T> _mfi::BOOST_MEM_FN_NAME(cmf0)<R, T> mem_fn(R (BOOST_MEM_FN_CC T::*f) () const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf0)<R, T>(f);
}

template<class R, class T, class A1> _mfi::BOOST_MEM_FN_NAME(mf1)<R, T, A1> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf1)<R, T, A1>(f);
}

template<class R, class T, class A1> _mfi::BOOST_MEM_FN_NAME(cmf1)<R, T, A1> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf1)<R, T, A1>(f);
}

template<class R, class T, class A1, class A2> _mfi::BOOST_MEM_FN_NAME(mf2)<R, T, A1, A2> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf2)<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2> _mfi::BOOST_MEM_FN_NAME(cmf2)<R, T, A1, A2> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf2)<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::BOOST_MEM_FN_NAME(mf3)<R, T, A1, A2, A3> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf3)<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::BOOST_MEM_FN_NAME(cmf3)<R, T, A1, A2, A3> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf3)<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::BOOST_MEM_FN_NAME(mf4)<R, T, A1, A2, A3, A4> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf4)<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::BOOST_MEM_FN_NAME(cmf4)<R, T, A1, A2, A3, A4> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf4)<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::BOOST_MEM_FN_NAME(mf5)<R, T, A1, A2, A3, A4, A5> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf5)<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::BOOST_MEM_FN_NAME(cmf5)<R, T, A1, A2, A3, A4, A5> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf5)<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::BOOST_MEM_FN_NAME(mf6)<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf6)<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::BOOST_MEM_FN_NAME(cmf6)<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf6)<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::BOOST_MEM_FN_NAME(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::BOOST_MEM_FN_NAME(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::BOOST_MEM_FN_NAME(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::BOOST_MEM_FN_NAME(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

/* mem_fn_cc.hpp
9R+SsurcBbhA89MIztD8/FzLfaeW+wEtd7WW+yEt91Y4Dd4HL9Tj+fBuOEf9Os7pXAJ0OcQ4l0B/mQQTYTpMgmLTGw6HraH3/rFa0+kf4v6xDXJxMBUmw3awDWwP28EOsDNMgz3U30f9uj+/fr+mDTR9+/78nXU86arxu2n87nAM7KnjSC9YBvvAS2F/eB3sB2+FZ8DH9bj2p/ptl3uREP3pQC3XYC3XEC1XJhwCz4Znw7HwHDgMng+HwxlwBLwKjoRXq9y1cBS8EY6G6+AYuFHD9XlTv3cSt7bn1336nFCLXJXKJeAq3c77+FeHKVcTptzBMOX45qJy+APk2tvkMsKUywpTrjRMuSqbXKLLX+5de/2FKVcTptzB48jl2evv7fDkMmqRO1DP9YPvge+z2+xksznYXvMBXLCdZicbzXabzKfeHrPdFvP9+NUGs83+st32Mi7Tbm/Z2dbyFlyQbeUgu8qhbCo72lMOaUtZbSiHZT85cWhou8nO9pKNrWQ/O8k7LHmbXeT0YcYecoAt5BO3gRza9rGT3eMgW8dq5zj0XvBLl4SwbXyCNo1rs2E8LoTtYrVb/C/Z013tFPvZKHbeu93PNrGxSxwd2ciVjsvCLcZtxtXgDuCi6zVypeEycTNwi3HrcY/j9uKO4OKjsGOMy8Ytxq3H7cQdxMXWb+QahCvAVeGqcXtwB3GxDYiHy8atwW3HfYhLjG7kGodbirsftw/nakg+cMNxBbjlDevsJdf96n51v7pfOL9/kf2/OXmnaP//NxJ5ttI5nHybkl+mfqMfiJtizWH6DffDAfv/j5gnOSosGFu4JHD++jcpst9w4Rzf93tNI9Zp/rCGZ0r4WN3zu4B/EzR+roRnUDbGe1eMmd+5j/y/dQJrY8kb76zIm/P8fVMf8VZj2t7Z34ebQX1sqq0+ZBUH2Q+uDy2PpkHKrXhbUMDOW+3kOHufy/HV5C3S1Y+njqlwFm6e2goq960N0LozadnCK+aavSsDwi9IlTm0FewzLOETbeFxhP9R5mcVl5cvRMDWfumPIaP78p6H/0GJEy97VXb238dS03Pb8lM+b74trYGSVrRJ62ltW92/3bZfvkkrSC9O0z0t75TwrWHbkAhs/1hYHrB2IdEcox5VLhVSdxyTuqMdm0m5qS+OaX359EzjS7n97O1tqe+SXw0uCfcE7iLSrZQ6qQzagFKudJYLi3Y5r8XW+B3MfqZ3if+uoP2/VWdUPtXMTd8k/gdCXr9ZRn6wK2AfbzMP+5iEtzW2ibBd4KljDU953GPPLIr/7LYL7pF4U/WYW461F9k2sn6wFP+DInOHbW9T0vbu54rMYvieyJQg4zk/+ZuX79nS2OzZ+ojI3Kzp+GRIytjg/JXI/MwVat/eRNhW8hahfnYaFn8Hs67oDoT249rS2nlhrv/o/PjJ7wdt0+eAPX2pI/uevjiOab2pTgbYLCzQfj8HN9Oa9/j48XRSOjnZiTyUjqGTGr+5K077mTvFP9HVUNeeDvXYICUN3ZfexClwdSKer/8oXThnrkcmyybTwxWj8718a236h7G2LbAeR0HywjHNC8eyzDUs5/arr8Vq/w+P/GJx+anwiVrri7XDjvWl8ZuF3ZfZy2Eft9Ia6zdHXQ/0Ba6Q/GXUnj/Wy85m5ArOo45bmsZbrj5oyg3kNFnHrSI5/jTX/UTGq6Guh3XPdm3jhTOlZl3G5tUokX+XdmZ1Fe5Bn507PUeirlPS+LZrOcvItEDGM4aMEP9f0XMdV0yeogPHTdVHTYNaypD7Eo754oQeC3XMWSIyv/Ib80jL7N3M9Rs89mm+14jc7b4xLiBukcbNkLFufvEcW599ucg9oH6TV70=
*/