///////////////////////////////////////////////////////////////
//  Copyright 2020 Madhur Chauhan. 
//  Copyright 2020 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_ADD_UNSIGNED_ADDC_32_HPP
#define BOOST_MP_ADD_UNSIGNED_ADDC_32_HPP

#include <boost/multiprecision/cpp_int/intel_intrinsics.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost { namespace multiprecision { namespace backends {

template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned_constexpr(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   using ::boost::multiprecision::std_constexpr::swap;
   //
   // This is the generic, C++ only version of addition.
   // It's also used for all constexpr branches, hence the name.
   // Nothing fancy, just let uintmax_t take the strain:
   //
   double_limb_type carry = 0;
   std::size_t         m(0), x(0);
   std::size_t         as = a.size();
   std::size_t         bs = b.size();
   minmax(as, bs, m, x);
   if (x == 1)
   {
      bool s = a.sign();
      result = static_cast<double_limb_type>(*a.limbs()) + static_cast<double_limb_type>(*b.limbs());
      result.sign(s);
      return;
   }
   result.resize(x, x);
   typename CppInt2::const_limb_pointer pa     = a.limbs();
   typename CppInt3::const_limb_pointer pb     = b.limbs();
   typename CppInt1::limb_pointer       pr     = result.limbs();
   typename CppInt1::limb_pointer       pr_end = pr + m;

   if (as < bs)
      swap(pa, pb);

   // First where a and b overlap:
   while (pr != pr_end)
   {
      carry += static_cast<double_limb_type>(*pa) + static_cast<double_limb_type>(*pb);
#ifdef __MSVC_RUNTIME_CHECKS
      *pr = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      *pr = static_cast<limb_type>(carry);
#endif
      carry >>= CppInt1::limb_bits;
      ++pr, ++pa, ++pb;
   }
   pr_end += x - m;
   // Now where only a has digits:
   while (pr != pr_end)
   {
      if (!carry)
      {
         if (pa != pr)
            std_constexpr::copy(pa, pa + (pr_end - pr), pr);
         break;
      }
      carry += static_cast<double_limb_type>(*pa);
#ifdef __MSVC_RUNTIME_CHECKS
      *pr = static_cast<limb_type>(carry & ~static_cast<limb_type>(0));
#else
      *pr = static_cast<limb_type>(carry);
#endif
      carry >>= CppInt1::limb_bits;
      ++pr, ++pa;
   }
   if (carry)
   {
      // We overflowed, need to add one more limb:
      result.resize(x + 1, x + 1);
      if (result.size() > x)
         result.limbs()[x] = static_cast<limb_type>(1u);
   }
   result.normalize();
   result.sign(a.sign());
}
//
// Core subtraction routine for all non-trivial cpp_int's:
//
template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned_constexpr(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   using ::boost::multiprecision::std_constexpr::swap;
   //
   // This is the generic, C++ only version of subtraction.
   // It's also used for all constexpr branches, hence the name.
   // Nothing fancy, just let uintmax_t take the strain:
   //
   double_limb_type borrow = 0;
   std::size_t         m(0), x(0);
   minmax(a.size(), b.size(), m, x);
   //
   // special cases for small limb counts:
   //
   if (x == 1)
   {
      bool      s  = a.sign();
      limb_type al = *a.limbs();
      limb_type bl = *b.limbs();
      if (bl > al)
      {
         ::boost::multiprecision::std_constexpr::swap(al, bl);
         s = !s;
      }
      result = al - bl;
      result.sign(s);
      return;
   }
   // This isn't used till later, but comparison has to occur before we resize the result,
   // as that may also resize a or b if this is an inplace operation:
   int c = a.compare_unsigned(b);
   // Set up the result vector:
   result.resize(x, x);
   // Now that a, b, and result are stable, get pointers to their limbs:
   typename CppInt2::const_limb_pointer pa      = a.limbs();
   typename CppInt3::const_limb_pointer pb      = b.limbs();
   typename CppInt1::limb_pointer       pr      = result.limbs();
   bool                                 swapped = false;
   if (c < 0)
   {
      swap(pa, pb);
      swapped = true;
   }
   else if (c == 0)
   {
      result = static_cast<limb_type>(0);
      return;
   }

   std::size_t i = 0;
   // First where a and b overlap:
   while (i < m)
   {
      borrow = static_cast<double_limb_type>(pa[i]) - static_cast<double_limb_type>(pb[i]) - borrow;
      pr[i]  = static_cast<limb_type>(borrow);
      borrow = (borrow >> CppInt1::limb_bits) & 1u;
      ++i;
   }
   // Now where only a has digits, only as long as we've borrowed:
   while (borrow && (i < x))
   {
      borrow = static_cast<double_limb_type>(pa[i]) - borrow;
      pr[i]  = static_cast<limb_type>(borrow);
      borrow = (borrow >> CppInt1::limb_bits) & 1u;
      ++i;
   }
   // Any remaining digits are the same as those in pa:
   if ((x != i) && (pa != pr))
      std_constexpr::copy(pa + i, pa + x, pr + i);
   BOOST_MP_ASSERT(0 == borrow);

   //
   // We may have lost digits, if so update limb usage count:
   //
   result.normalize();
   result.sign(a.sign());
   if (swapped)
      result.negate();
}


#ifdef BOOST_MP_HAS_IMMINTRIN_H
//
// This is the key addition routine where all the argument types are non-trivial cpp_int's:
//
//
// This optimization is limited to: GCC, LLVM, ICC (Intel), MSVC for x86_64 and i386.
// If your architecture and compiler supports ADC intrinsic, please file a bug
//
// As of May, 2020 major compilers don't recognize carry chain though adc
// intrinsics are used to hint compilers to use ADC and still compilers don't
// unroll the loop efficiently (except LLVM) so manual unrolling is done.
//
// Also note that these intrinsics were only introduced by Intel as part of the
// ADX processor extensions, even though the addc instruction has been available
// for basically all x86 processors.  That means gcc-9, clang-9, msvc-14.2 and up
// are required to support these intrinsics.
//
template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(a.size()))
   {
      add_unsigned_constexpr(result, a, b);
   }
   else
#endif
   {
      using std::swap;

      // Nothing fancy, just let uintmax_t take the strain:
      std::size_t m(0), x(0);
      std::size_t as = a.size();
      std::size_t bs = b.size();
      minmax(as, bs, m, x);
      if (x == 1)
      {
         bool s = a.sign();
         result = static_cast<double_limb_type>(*a.limbs()) + static_cast<double_limb_type>(*b.limbs());
         result.sign(s);
         return;
      }
      result.resize(x, x);
      typename CppInt2::const_limb_pointer pa = a.limbs();
      typename CppInt3::const_limb_pointer pb = b.limbs();
      typename CppInt1::limb_pointer       pr = result.limbs();

      if (as < bs)
         swap(pa, pb);
      // First where a and b overlap:
      std::size_t      i = 0;
      unsigned char carry = 0;
#if defined(BOOST_MSVC) && !defined(BOOST_HAS_INT128) && defined(_M_X64)
      //
      // Special case for 32-bit limbs on 64-bit architecture - we can process
      // 2 limbs with each instruction.
      //
      for (; i + 8 <= m; i += 8)
      {
         carry = _addcarry_u64(carry, *(unsigned long long*)(pa + i + 0), *(unsigned long long*)(pb + i + 0), (unsigned long long*)(pr + i));
         carry = _addcarry_u64(carry, *(unsigned long long*)(pa + i + 2), *(unsigned long long*)(pb + i + 2), (unsigned long long*)(pr + i + 2));
         carry = _addcarry_u64(carry, *(unsigned long long*)(pa + i + 4), *(unsigned long long*)(pb + i + 4), (unsigned long long*)(pr + i + 4));
         carry = _addcarry_u64(carry, *(unsigned long long*)(pa + i + 6), *(unsigned long long*)(pb + i + 6), (unsigned long long*)(pr + i + 6));
      }
#else
      for (; i + 4 <= m; i += 4)
      {
         carry = ::boost::multiprecision::detail::addcarry_limb(carry, pa[i + 0], pb[i + 0], pr + i);
         carry = ::boost::multiprecision::detail::addcarry_limb(carry, pa[i + 1], pb[i + 1], pr + i + 1);
         carry = ::boost::multiprecision::detail::addcarry_limb(carry, pa[i + 2], pb[i + 2], pr + i + 2);
         carry = ::boost::multiprecision::detail::addcarry_limb(carry, pa[i + 3], pb[i + 3], pr + i + 3);
      }
#endif
      for (; i < m; ++i)
         carry = ::boost::multiprecision::detail::addcarry_limb(carry, pa[i], pb[i], pr + i);
      for (; i < x && carry; ++i)
         // We know carry is 1, so we just need to increment pa[i] (ie add a literal 1) and capture the carry:
         carry = ::boost::multiprecision::detail::addcarry_limb(0, pa[i], 1, pr + i);
      if (i == x && carry)
      {
         // We overflowed, need to add one more limb:
         result.resize(x + 1, x + 1);
         if (result.size() > x)
            result.limbs()[x] = static_cast<limb_type>(1u);
      }
      else if ((x != i) && (pa != pr))
         // Copy remaining digits only if we need to:
         std_constexpr::copy(pa + i, pa + x, pr + i);
      result.normalize();
      result.sign(a.sign());
   }
}

template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(a.size()))
   {
      subtract_unsigned_constexpr(result, a, b);
   }
   else
#endif
   {
      using std::swap;

      // Nothing fancy, just let uintmax_t take the strain:
      std::size_t         m(0), x(0);
      minmax(a.size(), b.size(), m, x);
      //
      // special cases for small limb counts:
      //
      if (x == 1)
      {
         bool      s = a.sign();
         limb_type al = *a.limbs();
         limb_type bl = *b.limbs();
         if (bl > al)
         {
            ::boost::multiprecision::std_constexpr::swap(al, bl);
            s = !s;
         }
         result = al - bl;
         result.sign(s);
         return;
      }
      // This isn't used till later, but comparison has to occur before we resize the result,
      // as that may also resize a or b if this is an inplace operation:
      int c = a.compare_unsigned(b);
      // Set up the result vector:
      result.resize(x, x);
      // Now that a, b, and result are stable, get pointers to their limbs:
      typename CppInt2::const_limb_pointer pa = a.limbs();
      typename CppInt3::const_limb_pointer pb = b.limbs();
      typename CppInt1::limb_pointer       pr = result.limbs();
      bool                                 swapped = false;
      if (c < 0)
      {
         swap(pa, pb);
         swapped = true;
      }
      else if (c == 0)
      {
         result = static_cast<limb_type>(0);
         return;
      }

      std::size_t i = 0;
      unsigned char borrow = 0;
      // First where a and b overlap:
#if defined(BOOST_MSVC) && !defined(BOOST_HAS_INT128) && defined(_M_X64)
      //
      // Special case for 32-bit limbs on 64-bit architecture - we can process
      // 2 limbs with each instruction.
      //
      for (; i + 8 <= m; i += 8)
      {
         borrow = _subborrow_u64(borrow, *reinterpret_cast<const unsigned long long*>(pa + i), *reinterpret_cast<const unsigned long long*>(pb + i), reinterpret_cast<unsigned long long*>(pr + i));
         borrow = _subborrow_u64(borrow, *reinterpret_cast<const unsigned long long*>(pa + i + 2), *reinterpret_cast<const unsigned long long*>(pb + i + 2), reinterpret_cast<unsigned long long*>(pr + i + 2));
         borrow = _subborrow_u64(borrow, *reinterpret_cast<const unsigned long long*>(pa + i + 4), *reinterpret_cast<const unsigned long long*>(pb + i + 4), reinterpret_cast<unsigned long long*>(pr + i + 4));
         borrow = _subborrow_u64(borrow, *reinterpret_cast<const unsigned long long*>(pa + i + 6), *reinterpret_cast<const unsigned long long*>(pb + i + 6), reinterpret_cast<unsigned long long*>(pr + i + 6));
      }
#else
      for(; i + 4 <= m; i += 4)
      {
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i], pb[i], pr + i);
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i + 1], pb[i + 1], pr + i + 1);
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i + 2], pb[i + 2], pr + i + 2);
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i + 3], pb[i + 3], pr + i + 3);
      }
#endif
      for (; i < m; ++i)
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i], pb[i], pr + i);

      // Now where only a has digits, only as long as we've borrowed:
      while (borrow && (i < x))
      {
         borrow = boost::multiprecision::detail::subborrow_limb(borrow, pa[i], 0, pr + i);
         ++i;
      }
      // Any remaining digits are the same as those in pa:
      if ((x != i) && (pa != pr))
         std_constexpr::copy(pa + i, pa + x, pr + i);
      BOOST_MP_ASSERT(0 == borrow);

      //
      // We may have lost digits, if so update limb usage count:
      //
      result.normalize();
      result.sign(a.sign());
      if (swapped)
         result.negate();
   }  // constepxr.
}

#else

template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void add_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   add_unsigned_constexpr(result, a, b);
}

template <class CppInt1, class CppInt2, class CppInt3>
inline BOOST_MP_CXX14_CONSTEXPR void subtract_unsigned(CppInt1& result, const CppInt2& a, const CppInt3& b) noexcept(is_non_throwing_cpp_int<CppInt1>::value)
{
   subtract_unsigned_constexpr(result, a, b);
}

#endif

} } }  // namespaces


#endif



/* add_unsigned.hpp
tQJcsFQSZR3oGmIvsjGVl8TeF0l2e9fFX7hc4bp//yhy7SoHHI9/c1H6aQu4Lrz8wKhG66IdwkAeNg3qwO3VG2vSlz7GRDBCORQwugwqGN8tiMXfRD4MJoWRAbSk8KQLygTOW94JJLPo9hyyTMe8TCq02WXVtHdjL5bw4CcMPCnS6yE+A9MPoYy1jsO+GsdV3DV8nOt4q3yTBvjxehJpSTrSN7hxeYkc8jdkSXHxCWmmOCPxhECJkvgpcs7cQ6wETYmVOB5ppKw0K3mmiEOKBGWJGqL27EPEhJ14FW7ldhLwBBnyN5zxVkk8AvdwI1pJflmS52CoWqspzrl3TfB3z1Bi7kB7FFUMB8EzEBuKbH9F7MaLXKhmPgrtfvhi7CYjUySQvMe+eoOLuH8FjwEuFN35vFL4OLxdOoLiST5z6bjzbiBlDKbsSd9u4or639cUmoLwSdV3YX0XYI9C62jveTBDBxrBaB+FS/uK1UKdwIpge/HVQhf1l5/DprKoKYwgxuQ4tqgpSWFMILlCqhrbP02uzt2ymvqvzlh5MKxhFcIM9frmmQhzJtbKIoJeS0NyDCQudlkpRCQHbDa3SWT9khhbw02VkokuvdqyEotFVz4L12RDPv02LZo2LuPT330uM3cvplktGU2K6rLZL7wnr69ZB6WjfLG56kMU4WK+YLjNMbXELPzTeYa1+bM8HXgNucBcjTQW0cpJ1QRXf0SJV1dKfI2j1zb4SLtPSqKuWJVtTsHSlBVbuBGaADO8EUDRTvItxzSFH0CnyB216iX7fTBgjpeAaa5Sdh21T/RUUVHzMPXadq6GjFk4+xrtldlHPZJkgjyuhlJg7zUkQP5uCECiRVq7VPSY4v9zb6lBSc/YjOMoJmFUnalPcfMvv4V3y69SaffIpiRvT0qgGJPK9t2VdfJNNuVURDIWOxYVRGxTlVM6bx1mDaZk7kLIVerCvqlkTOiKu9SRcUHf32KiV99kblssW0H5o2Jjb6yDMLcewpPVx8Xm30kPnqFAk7zp/eJliWqC2yzSTOg4UaFhrsLptPt3TtsQ68kM/B3Z2BaintQg+O9RC8XO0Qpq007ZmM4OFT3buX+FtJZikoZKxRDjpcealm7tpJaqPhYNfUg37PYjBY06vZQXLLuNQYVqz2ltA7tiPGKEFukGKRSpTkWJZMCMplg3fnpIIomiw0iDL4rbYjxYTKVJ22CXjiN/v/YJlZainBSCpvdmcdmkbKJrlgfysnE9mmZHK7e4SwY9I9bBmRRpqroTl+Whx1ZRyx7yfSaxwijOF5uCEMa2QZ41SVVxYBMHh7RfAwiGtF8dyGtESA2BFSjBZAg1dAWSHhVSQcEuJWLGvh4lUALRLgVehNjgnAREhH8u4hwzlMuCgBzN5pCwLNAUiZAMTldUUIqGhiQsZfkuCWwSSZ8ESBDJQCg41+WfReUqntOp9SnU167mtlhD5rEKf4FQHoMhEnUTBobH6D0B4H6tE9cSd9TmRawCoi2UaDYqGVwO6HdSah/RYsueit0ZlNYqcpM+DSL0Bj4zT6mG6aqVHRYnIm5MF7TObNpuVpbyOMXrq5yNdUjuua+fnx+gcEAA4F8gv0B/gf0C/wXxC/IX1C/oXzC/YH/B/YL/hfAL8RfSL+RfKL9Qf6H9Qv+F8QvzF9Yv7F84v3B/4f3C/0Xwi/AX0S/iXyS/SH+R/SL/RfGL8hfVL+pfNL9of9H9ov/F8IvxF9Mv5l8sv1h/sf1i/8Xxi/MX1y/uXzy/eH/x/eL/JfBL8JfQL+FfIr9Ef4n9Ev8l8Uvyl9Qv6V8yv2R/yf2S/6XwS/GX0i/lXyq/VH+p/VL/pfHrz6+/vzR/af3S/qXzS/eX3i/9Xwa/DH8Z/TL+ZfLL9JfZL/NfFr8sf1n9sv5l88v2l90v+18Ovxx/Of1y/uXyy/WX2y/3Xx6/PH95/fL+5fPL79d/xj6qlXMTR+To9ArD48I+SJptqaSl2uPf4LixQcMFRBNtrLFQJ29meHige9W5t/egZ89R/jZMqtWT1Jq/MZ+w3EVdVU0L19Y3APihXnO0fmXxO5zxhoL8AQTRl56xfWH+AKytdbw/S31R87KpUe0NmqkxSTTvHPtjC98a5DIkcsb6dYsyV1IzHOT+0lCO3haL8ClSs3Tv4szl4ZOK0L8FmOrGcnv5EItO+Hu52XLM7dZD5fok8nc1po5/KcM2Cve+K28Boqrjg3Kt3/+6bcQv9ETVq2G1kMG9242d+M8+/rHt9jXkvYKFbPYP7bi6YzCGOMKD9nmq+mggoYoTNGAgzeNOaHrwmwThVI0Y/pW1RQ8Z65B83vtCcYptty/D7rtMPgV0fYk9AsSPFr/zk+7cc70kW92vcUAdmTiqQRkcfsyC48iUOfVzTVzDsduUP/KjpI8drP7iIIHjyE3pBzxZmGffnbBpx74OkxLf9INfrGPbVJFMgqWIml31298ex7pm7dYsCYkkNDfDsvOmx4Fta2cPAEt6Cc0GhD5QYk54Z49J3dNRPIhj2rzjpyMexP05O8UoHJ2hoBs5dYFBYtzd9mlk8Nuhhxo5nU+O8WXs2CkcQ6ebIWGir7lMcQG0Fbenu2U7bfZ1u+Mi9np5nyosr43dCRrP5fdu8/A4W05FDi2NLdgph8Qqo+ljUXvMyuECQQm2Ami/JGnJjy0Pl3yMLinb1OcSPpLLGvlIFz49GOLt4naHyHSkRkER8jJo/2f98mB2vnLVNJeEK/uU0fKwomDLznoQNqwDNqZkVMydyOl4zKCw+B5+9ZtQ5ccES3ONYhUWxed96EKpwmO7mSX/0IfoWYSL9b919Y3PaC9UTceMUJ81mlm0BptUrEZa405jUsY5MstJqd0YUoX59eQMi87FhOoUTMM0Jf9gcBXhMjmFBBz0j94xyPeLfoCYi/sgIst0SeLCc+k2TNzCgc57oEOoUradb4LO0/sO2eLTGawHAF3Nxpemu2SSjb+nmfvboDeRvePL9YNDny847CnpW8pprzS1k1rrG15PFJTM0E5Vbqzc7x8d3w+AZQgq3KKF26qO0dMZYupNeCif8HbB0JnK1WBawG+Bc+iDH466/bWmS1y7odzDI7xbn2/9lzrFoUkfokvZ6+WyN/Ngq5tdyfN+4ZlViBnVaNwym/EddfMIznGcgQjRosoempR8m28sBsacbm3aXPpsk+eK58LO9yx+BjX1Y99Et4FsexRyCTmG/uAT10lZhrzm0llxjuv4R2xRhtO3q+aVcM62iOvtx6gQIvc4SRdqfV45J7bu303MHofWn1klfTbuHrx7SouBN8/FBx1dBXj32oz61+jg4yEz2aNkSGXl9e961mRPBuzycpyun+J5+w+RUlfsIxbicRtEa13fzz83uC4cs9/n9DtivDw13w6vkAA+oHcaUtNHQO/aImcn1fVMzEK2nG/jgbjaL9htHeS4x6CP7T9cUxqOXmTFYI4dD1qEX8lysZwVuTXxPlKVs5c3lagJqZDRe01v8C0/fWrM7mnNxYElbsitOZWVVe/OyaRGSN+42kfQvp+PLxvj9D6T/TeNtE+rk7eXR7ngHRO/bb5j4gfgCS9C5oTuf38m5qulfLRtegkgnsbgSECGdSaDsg1SqmPhIuzoN2GX2fAGrUCsqfVAugVCb3Co5e6lZW67VZnPVr3U2mqz5aHqNZllAJOAAjFds9K878M1XGFeYnZ4/eI+M+NTl+9j032D3z01y3HCw98z+7L68HWH87mgrt5eW+Ogq33U0zHh7Zz8cU71sqx6XVm5+X90vP0Iax+19mN33WnWVH4e16qrr2+wVjE6tN5Fp/uWbSx+4v/r/dlEZmUVRlZRd5cSe65eUt1294yuM2QgJmBlreljZFtnzBd1IRfhfzvfEG8pcxZXH6FRKfiHZbqqu8n/Xrh6gtfR4/uSkGgPLI1+nrvD6Ko+crjGviCTwOgJFpNu9GZQotNKdVSl2RyNdb+Az5fLHvLm1fbwlKRd7Y6eATak7eV7ivq44avD2Xv477EyfrgQ32Peoo352aw3JUAdXsn26Hojjtdlw/qPpPOXSH186oz1pRpq+HGrz+vOAR1HicwGu9UTvrytpUoO5WZjCudKx8tyvWwjWHcp7rzv7c/UP0XugqP6eeFWXgTlOA3n84Gt8ZEl/Ouwjwful9pNn6vKAcz51ePxs/7GQ+jcL4uNxclU9VU0XO2nKO+tXfM/z0OE4A/ovg9f58mq0Hw1h89WPSZYnQPnNU1VNQ6fJRZ0sbNTE13i8ZyE1E3HTMi+BnNFSSda2BMTzLNwOs+riCmPMwznCjr1bZ6rpy/IWD507z7pDS2+9yFgo5KqUzkY8B+l9HDcRsjosFnu3hPEjh+8y00vy4DC23SVUt8Ody/iR7OmWWs02172bBv3PquDjIsk0KYR+Dyfqd7mxGzyU63FvCNoUzsf0X+ZjidjXS7fScTYDwfJpW94FQwweDxuN/hTRVRoI4V3xJOWuu//fEdG8iCPYphi5LhX6c+KnZUf9DLDsy713EWf7IGbXns8LLbC/xwkf95s996Un910ue/6F66KCFu+yHgVX0s9ZO+wMj+4avZqPkr+Ox66uomZyagfp/M4b+6elemyLPpyDUnaKAWzxU1YfHxG5/d9tzeeOc5IMI+uteVyaPuqV7Qm1/m2ERV0+hanblHD42B4QF/RnEH4uveYPMmx/tCfhL/ZCLa9JGz/Am37mwLbyi9dQ/ksayd7+brQA1yTOf/lktJEvvEy8BTBOt+TraV82VzkW+VNfIZvlOuK2ArfwC+rh9+ge9dlSe961WpL+gV8tSnqhXvk3TPp2Z2o5RzLYzb0GtSVQ/KUX1jWXhl4LhxpIMqI4uyOKNqdLLeBp1N7Etkvgf6wmXTfy4F09oWLuifVbEU0tRrjBqYO517Q+j53VEo9tvM1U1GT13C3lEF1vqANiJqt65nh6/pcEizVvR0rlV7PYeV9utzKK/WtZjUGfqvFhXPI3xEglS/cGfw+x+yjNUQcZF48uBxKp20UQDeR3re4DbFqGSl0IewZmt3q/5xdm0fBjeDcVHDCMbpVUkwdtGNbOFH5mjlcKTTqfqGEnANgW6bSllJz3kzn/F33HaSuAqXFzme/2LHUuyxP6JDsHkWv2apYzB3uo6mF1K1venDPJXXXM1LSofKOZCNmMlI+IEpQzjTRImZQV94eQhFPrn/epq0SWKFpVO6iXOKWJFzY9cgUu5IYR06MiwLzSGI0SJF27Q/PBel9G7aUKvVHqVrfRpLxXXxeMcNiBB8vt2ba/zVID5jjUIIFBDxitD8SR2yQpyBq/+csmhK4Qb+PBKPvvkwbfClH+lb/YJAOAFegpGf9BdDrUYAnVLUbg8vtE+1qZ29U3gIiMI98b4sVnLLQcJPZTpPPDN2YUwzazBVkT0tN6m9D3vB5mO4LDot1mLLbCuuwJv5o1iqzmTV0z7hcvwim+Zo3ljyQunuckotqah4QWH3bzq4khrxeWslAmWzsquLI6m7oyn5cvskzIfvUvFtxMOgg7E3UfvyC3UvVwmA1TMmzsNJSWAlDTgqsfftFhow8wibQ4YmnGgeQ6KkhVgZOgDEAe2YmL/Gd0U+j8tLdwLYfYd/OJJVYkTh6lmLbKErhCwkNhvhrKFaEtwcSA95hPKtJJwF8NZ+KO32dSSuzlFKn+i4nVV61rEAVhPkpU3zptDSODudmA2AS2HmF71dn4KO+Whusk6r9igZkSwytgzsSU91EOyCb5TEKnNpytVNmRJTvRkcw0JOdJ5JSdwBTDDC90N+FtxSIK+61V2CEzIno4Y09VGoFv63X0vg/057+P2joD+YNOPIC5G3MP6SDXxrB61obC6f+oPSrkTKtf3q64OJ2w2kYsYlZE8WowGDn6uSrRjVqWQccRsZJEXCaQKzX39LgYYLPWp2c/mhJ8gyPrpU7pG/n3eZB9xn+U2kP0pbtUXqd2M0MaqLEyiYnLN4nCFaRNGfAqS5aVFFijNrKcEFpkk/OKklo1gmuITFLEjK0TL2PSFfTukYpTKY0hgQLFLMEeBtjjPJyd5CsL0j3dA/OGeAgBb0IbR6nUeM4F6S9AD5sVu0+MnkfgBacQ0ctFCR3o4QIoelSA/DiWSvl4UVN0eVfqa3tPotMV8wyDq0fZtGcqhPdkiCl1NTTTGSZ7EMAACz/05Nex8Fkn4Z5rCiWkNaMkYQxhvYrZW29AjK2f1sWj2QVMcjKhNqXTjtYJtgEdIn992SB54P2T0XJSqrd3h7FpyQas05egTgsrFVitnx/nKE5ST2+qsAtcSoNNNAK9GBSqS/PhvhYtqGnDHsw/VtJRwPP3VkMyeZnJfr5rlD9RBhAzD8aK2oJ5q+wJevmOMWpzBLkVAqHZL6tKdy0roTTUmYh5F/fV9N/tmaz86q89qgZeskEU3Br3mmfhHUcXNFyDtYI5RSOxZZDVjUo78SSvZEn+nkf6VuD2GAHYwcvNz4/VTfBvGs0a1CnBK8axp5+8La9ZJs4fE/Su9x8sLu1PFU9ugpua+cpjZxKDNonZFlnP1ygYFOJdaBOF1q+n2acI3bcKYEL7CWoEn9QTdu5ajPCh5y/9/rNBt7Dqtdw8Hin4Az5zC9vL/gWFs3DxWvCq63vLjgw9J/S3gdn9qNtmEpIJlI+md96aZ98zpCe6J38SbvlUCKkLY2WT2YrZkILIuK73tPwptz0O2NormZIAMwIlkEJZs3aPQmUAYyDRyRQyPlsOIEqrKh5Sg+UvHAVfaJuGTLfcWbNYCD0XvH01Fs+8Ii8zkHtNf6qXMfT1TdQ+1gjoSWlA/r9paHX0dZk8HWTntsDFnjbEhDWMLxJNNWJ4+keMFK1iavSLRqC/Jwu50pkxd+vPXe0cmbnofFeIMfXlEPCmFjWa2YJKpPuo1IhEAaOoxss4Sq8a+pHrrQQNyCWY107f7ByBtecrl+mK2oPuq5Hzc4tXszbdLiVNcKCWTbeNac2pggVXNb6+/TWwFknRloFmDP8FjYI92F3kVy56xWO/UgkorWLeR1jRpXk1Kx5R5j6QHFHR/K9iETNAlLeCduFOREJwSZMqn+FgE949/mPhcvPd6rKjg7iaEHqBQo2Qj2nLC3HZW/MuZ4plVE8UH894qPQetxGBfAuMJO1s+vfose6Co90HGP4xMXZH6NZD+yymR1ogVvfQkFSFpcfURtbOz1eS6wS8VHvQWJa2KZttkH+3OdrT2m6aZDrt7fvNEzZkicK5mrApJueC7xZXGrDaGh9dA+kDoJzsb9kV05sl/xH88nEMKcGF66hgBu45qvJq1JqcxEtMxB35saTERBLBQd1vLRo+9bm8D7BG/AQdv6mVMd88mMFoDJ/N+MrDYwPIqAqB3Gir6IqmeUGjdX2r8QaqdDPkaK4jCDty+LmBYP6vWOQIwyV+ldQ5yigvBNcjsfkDYh8MIoF1Tk/R+EUkmb3pBEoSn9jhVyDx4jYD+493PNLfmY4GPP+wnsBCA6TI9VcvWbTywR1SX3L3wJt9pbPFLCQ4cFp/Je6+SfB5/VsrD5dSdtPVmlF1gP11tbhFvOkhr8GGUCKNGrsc73xIQBfkXVHAevIj/ADwFVCQt+CDIl/s2A0p53wLnn1ysRN0CtSgIaZNMuz
*/