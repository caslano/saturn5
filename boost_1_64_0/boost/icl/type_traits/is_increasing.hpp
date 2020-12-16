/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416
#define BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416

#include <functional>

namespace boost{ namespace icl
{

template <class DomainT, class Compare>
struct is_increasing
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT>
struct is_increasing<DomainT, std::greater<DomainT> >
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_increasing.hpp
J4bSgDGcy6AmKHD2HrvxeP8mbDx7+Gg6PdLfs5VPUXswW2BAg21D6XufMMc12Hr8u96u6ktb8zl8+WrxEtfyDh88/HM8G+Lx2J+LMpey/wt0hrsA+zmU+oB7tZ3BGT5lmpHjnRodkznJ4OvvaXjl9Nd0HHqLGne1jjuPTu+e1vSBY9IvMNrFJLj0Dv45hc5Va1DVKedvCgiFIi+H/SE1Tlof5y1QFSY7tiqsn5fVKmwbHyxmmKyyJT/uqrvORRY4ehDSZLAnE3Dm5/iYlg/EmwvO8HGs4biiLIZr/ZKWec11DkBGbhlSYdx7AWM4wyVZFSY9XGCUheY4t6lUlK/t4sz543xlaoqh4Mq4YtFXX3k5rOw10yqWr7fnU5XKOjdb4fUq/5ETFsW2unnN5+2LGqRggtRxlJ63GMNpUPv4tr1zKvWo7nujiLTy5G7DOdDW1tx+fmtmXizrOKo0n6U47TnbJ+5JKpeR0Mgm/rq3S+PlxqHGQXLNBDCdNDwImg97V/kAqV4dAFBtcJ6UPk314IrjlbUvHi3KSA9HCXv6w9ZObyQVN+dGwniMPXnaa6U+qdaCLx5XZxkwXH443yPk+rqe0/bgbj0SUFvns367PHvsa11FswUscKemBLrG5zeXMamODrMDEyh66rt3T6hO2FvTVGL4xfAsmMYwxNDfK+qNbllt2Ce8r7n66j179qxh+Wvwl6KvzuMI29Vj2d1rCo1yKeD/6+6mf0dojjNKH0vJ/vLQJqcxkTB37v5AJdAImIFSwAj0BbKBeiAf2GM/TUBieO4N1EBRDYzjPYv3QqAYyAGXCpiATFLMpk0iVqU4JBBmtl+y267rUeQRtxAMBeKBXuRkIJAQAuRlODDI8a1IKwHKJMJwMyUwT0BIIz5oY4fxLr/YNWifutNVvz3115P3+96Hft32i3/ufdyR297w2Weuf+4jJ1MvHR3IH4i/+O9vWf66J/zpBR8cXpZNlF9yj2c/I/KJl3X/6vkfefo9z7/qIQ/dsWvoOelvmq/88s4PrLS2nWh9x8Hf3X75xBce/KhP/uSrPY8+2/7WjR9+WPVTl32nt3j3xz/89w98/c3XxRZcuPfn/nzot4/5+cJPf+PqU2MP+taiO375/X0jv/nL/nfVb1o7+NRHvPr+X9v9xPv0Nza/6cxTWlbccOet56KVe2354ulVL39f8s1/rG147bXXPO+K48ee9o/565505dbXhENP/tvhH7/oFe+92w+uCo6XPvb5rwd+9pUfvvHG1bn7znvs9h+98J1Luzof8O6Ofx/9eN+SzEff/6U1n/nDdzf99G3X71n8dqPwr2fd8p7AXfjh72XYZwMkPg9hPsICBPkt5NCCkP/NfYI3nFwe3HliafDMp+AruGVpsPvjS4P7bl0aPIf3wM1Lg8anAUPYiTBTugbo9gF/Ds+d4DuBsPOTiCMs4/TmBf7/ftJ96Sxn2f4zYXOwEVaWQiZLDIqR4BNvdEfyNUbblXm6iU7OmPNlo9fQu3OCKzHlHDICiHhtmC9rYFDhVbn4pJgKAgxThjBe5T3ivJtMxCg3DjTPF8wx2P2iyDHa+oe2RfG5n4E/D6Mcs5BMTfvggf+eiNGGk5DZiZJo4GDW2qXTGXvwjjdOARDnb9I4cF0K24xsqWHIR0DtUzYs3NlMl65jLMSA0UvfqAkVfj0xTZ72O//NZr1uYb/KwtZmH+Kizy8P/n6FB2tFWKLBViAEAbvHfT3YSoTWj7U2wQyEPg22CqFV421DWKnBViOsYpj49Y5+FnE8D+O5nfv1TOWca5lE9uHPOf6pfXiKbMFdAEz1T+0EL/nj9fsxCDYPoQVh9ec92HyERQjdgMn37ws=
*/