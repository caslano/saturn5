/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_splitter
    { 
        typedef is_interval_splitter<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_splitter.hpp
ZtSeTa89n93nIt/hVb0vnvrFL28Mvy+0p6jjlIxxSzulB2z/5WdoyrBUgoNTBg4kODB52GCCA5KH6PjU5IFDCaYMGgA8YHLqwKOt72uRMP0atOfHYdgSND99jhaO9nL1/+uvdxgtpxMaWtFsf1CEif98/IP1fHhT/A4CJ98vtvIb5Xz2jx1jtJ9Ak+0qFP549PPZHcjP4ZMs9ti6A0fn5BnXCr9k4BBW4IStM+CWjzLtHXTALx04vuuKn+ki7BLpu+USrpH4bljgOD/hb616stX1yA+nnXEtpTzapLjYLgLj6GUx/PEdV5yf5cDZRflwua4S+WZcF1E+sn6wA7+7gXu9HcpH5LG7XD7imzuRR9at74Xf/UoeN4p45Xu0tgE3oIPVht5e4M49g+NFPN9Zy+4dild5kpEvFXcQ/hwiv+J7YCy2BShsPXwPHiQaIMXdEvSmih0K5PuIdihmUBxyHf1kTV8S3Mz3HMdA4JYjbRzHWiWOdCUdhXCvhn+57GYA93oXMx2fKHGEf/rP6WL/qx/St9YVgsW7z1tUoZWJsnAX5bgzirJyYLmSD4uDWOSvYG1C5F2/ELlIV+/ha4/oEB7d+UN0n2K3H3Hq14NpPmh4eQ1kBRS4/BrBkkhI0/0409ImFsDAmE7nU9GekpLKiKekht5hdddHFoF0uuahMIXuQvMEPt+zFEUCyC2OGfKZZ/Jv3Iolgphh2AvCiquh4Td2yZTL7Ran+cVJfqkcbTG7A8LmgPBP9nKLxDkRcYWTZpad+J7wSyduoeqohzlqH6Hhr8ijBVPqf87dCIOyL7WGGY5TM+KMSRGVJz1GEKh8Vvn1ehU64gat3B8gCLUcf1AY0BU2GSiLspt1AtkttJTM7+nlIPzoVgsNjJ/PEBoBDAf4RjN5hhyCb8R7SSBEevl0Ppa4jj7mF0FtNYgwGNL5JaZh7tO02LVa8kVM0P2UT2Qyjl1kn4t0wWCaXTl0qtBUU9lQIw14xYHIqMMoPaDj0JjrqZwwdEDL5KOjIt2xE7doBnoaWI1N0Jkmp8/0op5Fjli8hSsjYRSpyR+s7yjavqJZK9q+jGWcnp+ID0pcQZ+X8XrmHPqF4Q5uZeo5YuSXzB6YKZb8RBGDhr+ogxqPoksn2pWUGPkeLNW4GB5iOaS9EtEV+xxQzhIlwnQjsTUa2ccXIU35QPmTD6czXsKB3xzEb2qhEb4yaN60xfmJm0bNeoi6Mghp6AtH9RPM3IBUvTtvbTtkVZ6IA3wstKCZV8XhaUgF6PLCi5+i5SDUToVAKyopFm4qE3Kx3EKtsRULFgDMhyz/xLXlfplmkXeqB3+QZJEue1nf22QWG9sTgIRShb/N0ofoFhK4b4lPI1kSnyb3U1FNqNaLRgCsFa8zvOKX60bGyQWlKXEonRDTYNK9MurjLzOeDLmMLRLtWKTfwJHwERURH6/FwUNIiXgFLjQTyv3UumS/ermw7GYJJsKVgSRywD2vOo6g4Dzi4PGAjpOHFgrNKFkFJw892D/xCht95CbPaZNpaGqiiKVwaYVTdD5Wxgpx/VR44+O5ulUaWFvF6ZmQxjTx6FxVKo3rQHwvPl3pj+P6UdlNLitUZtz4EQ60YCGJADryana3NvU76jdUWqwi1G9T2oVfqf0rxmnwSE1fLU+VHp/JVD/MbPFpKtOpdCEn49NEjx6fpnkYzzaSUBYi21yFMp25qt5jPutKRw8twebisTnfAVaCrsJfoid/OHkgfwO1WmelBcmWwwYzpFvRzGvKvDom3+iL87LS6ey0fDeeQc+lsjZINvlyOr50T/9avfOIUDBr6w9otdZMljZN1OdsOwFpbvcT4EmAvZol2tsATgHU10o=
*/