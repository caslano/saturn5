///////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP
#define BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP

#include <climits>
#include <cstring>
#include <boost/multiprecision/detail/endian.hpp>

namespace boost {
namespace multiprecision {

namespace detail {

template <class Backend, class Unsigned>
void assign_bits(Backend& val, Unsigned bits, std::size_t bit_location, std::size_t chunk_bits, const std::integral_constant<bool, false>& tag)
{
   std::size_t limb  = bit_location / (sizeof(limb_type) * CHAR_BIT);
   std::size_t shift = bit_location % (sizeof(limb_type) * CHAR_BIT);

   limb_type mask = chunk_bits >= sizeof(limb_type) * CHAR_BIT ? ~static_cast<limb_type>(0u) : (static_cast<limb_type>(1u) << chunk_bits) - 1;

   limb_type value = static_cast<limb_type>(bits & mask) << shift;
   if (value)
   {
      if (val.size() == limb)
      {
         val.resize(limb + 1, limb + 1);
         if (val.size() > limb)
            val.limbs()[limb] = value;
      }
      else if (val.size() > limb)
         val.limbs()[limb] |= value;
   }
   if (chunk_bits > sizeof(limb_type) * CHAR_BIT - shift)
   {
      shift = sizeof(limb_type) * CHAR_BIT - shift;
      chunk_bits -= shift;
      bit_location += shift;
      bits >>= shift;
      if (bits)
         assign_bits(val, bits, bit_location, chunk_bits, tag);
   }
}
template <class Backend, class Unsigned>
void assign_bits(Backend& val, Unsigned bits, std::size_t bit_location, std::size_t chunk_bits, const std::integral_constant<bool, true>&)
{
   using local_limb_type = typename Backend::local_limb_type;
   //
   // Check for possible overflow, this may trigger an exception, or have no effect
   // depending on whether this is a checked integer or not:
   //
   if ((bit_location >= sizeof(local_limb_type) * CHAR_BIT) && bits)
      val.resize(2, 2);
   else
   {
      local_limb_type mask  = chunk_bits >= sizeof(local_limb_type) * CHAR_BIT ? ~static_cast<local_limb_type>(0u) : (static_cast<local_limb_type>(1u) << chunk_bits) - 1;
      local_limb_type value = (static_cast<local_limb_type>(bits) & mask) << bit_location;
      *val.limbs() |= value;
      //
      // Check for overflow bits:
      //
      bit_location = sizeof(local_limb_type) * CHAR_BIT - bit_location;
      if ((bit_location < sizeof(bits) * CHAR_BIT) && (bits >>= bit_location))
         val.resize(2, 2); // May throw!
   }
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline void resize_to_bit_size(cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& newval, std::size_t bits, const std::integral_constant<bool, false>&)
{
   std::size_t limb_count = static_cast<unsigned>(bits / (sizeof(limb_type) * CHAR_BIT));
   if (bits % (sizeof(limb_type) * CHAR_BIT))
      ++limb_count;
   constexpr const std::size_t max_limbs = MaxBits ? MaxBits / (CHAR_BIT * sizeof(limb_type)) + ((MaxBits % (CHAR_BIT * sizeof(limb_type))) ? 1 : 0) : (std::numeric_limits<unsigned>::max)();
   if (limb_count > max_limbs)
      limb_count = max_limbs;
   newval.resize(limb_count, limb_count);
   std::memset(newval.limbs(), 0, newval.size() * sizeof(limb_type));
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline void resize_to_bit_size(cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& newval, unsigned, const std::integral_constant<bool, true>&)
{
   *newval.limbs() = 0;
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class Iterator>
number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits_generic(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, Iterator i, Iterator j, std::size_t chunk_size = 0, bool msv_first = true)
{
   typename number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>::backend_type newval;

   using value_type = typename std::iterator_traits<Iterator>::value_type                                  ;
   using unsigned_value_type = typename boost::multiprecision::detail::make_unsigned<value_type>::type                                        ;
   using difference_type = typename std::iterator_traits<Iterator>::difference_type                             ;
   using size_type = typename boost::multiprecision::detail::make_unsigned<difference_type>::type                                   ;
   using tag_type = typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::trivial_tag;

   if (!chunk_size)
      chunk_size = std::numeric_limits<value_type>::digits;

   size_type limbs = std::distance(i, j);
   size_type bits  = limbs * chunk_size;

   detail::resize_to_bit_size(newval, static_cast<unsigned>(bits), tag_type());

   difference_type bit_location        = msv_first ? bits - chunk_size : 0;
   difference_type bit_location_change = msv_first ? -static_cast<difference_type>(chunk_size) : chunk_size;

   while (i != j)
   {
      detail::assign_bits(newval, static_cast<unsigned_value_type>(*i), static_cast<std::size_t>(bit_location), chunk_size, tag_type());
      ++i;
      bit_location += bit_location_change;
   }

   newval.normalize();

   val.backend().swap(newval);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline typename std::enable_if< !boost::multiprecision::backends::is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value, number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&>::type
import_bits_fast(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, std::size_t chunk_size = 0)
{
   std::size_t byte_len = (j - i) * (chunk_size ? chunk_size / CHAR_BIT : sizeof(*i));
   std::size_t limb_len = byte_len / sizeof(limb_type);
   if (byte_len % sizeof(limb_type))
      ++limb_len;
   cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& result = val.backend();
   result.resize(static_cast<unsigned>(limb_len), static_cast<unsigned>(limb_len)); // checked types may throw here if they're not large enough to hold the data!
   result.limbs()[result.size() - 1] = 0u;
   std::memcpy(result.limbs(), i, (std::min)(byte_len, result.size() * sizeof(limb_type)));
   result.normalize(); // In case data has leading zeros.
   return val;
}
template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline typename std::enable_if<boost::multiprecision::backends::is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value, number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&>::type
import_bits_fast(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, std::size_t chunk_size = 0)
{
   cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& result   = val.backend();
   std::size_t                                                      byte_len = (j - i) * (chunk_size ? chunk_size / CHAR_BIT : sizeof(*i));
   std::size_t                                                      limb_len = byte_len / sizeof(result.limbs()[0]);
   if (byte_len % sizeof(result.limbs()[0]))
      ++limb_len;
   result.limbs()[0] = 0u;
   result.resize(static_cast<unsigned>(limb_len), static_cast<unsigned>(limb_len)); // checked types may throw here if they're not large enough to hold the data!
   std::memcpy(result.limbs(), i, (std::min)(byte_len, result.size() * sizeof(result.limbs()[0])));
   result.normalize(); // In case data has leading zeros.
   return val;
}
} // namespace detail

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class Iterator>
inline number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, Iterator i, Iterator j, std::size_t chunk_size = 0, bool msv_first = true)
{
   return detail::import_bits_generic(val, i, j, chunk_size, msv_first);
}

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, std::size_t chunk_size = 0, bool msv_first = true)
{
#if BOOST_MP_ENDIAN_LITTLE_BYTE
   if (((chunk_size % CHAR_BIT) == 0) && !msv_first)
      return detail::import_bits_fast(val, i, j, chunk_size);
#endif
   return detail::import_bits_generic(val, i, j, chunk_size, msv_first);
}

namespace detail {

template <class Backend>
std::uintmax_t extract_bits(const Backend& val, std::size_t location, std::size_t count, const std::integral_constant<bool, false>& tag)
{
   std::size_t         limb   = location / (sizeof(limb_type) * CHAR_BIT);
   std::size_t         shift  = location % (sizeof(limb_type) * CHAR_BIT);
   std::uintmax_t result = 0;
   std::uintmax_t mask   = count == std::numeric_limits<std::uintmax_t>::digits ? ~static_cast<std::uintmax_t>(0) : (static_cast<std::uintmax_t>(1u) << count) - 1;
   if (count > (sizeof(limb_type) * CHAR_BIT - shift))
   {
      result = extract_bits(val, location + sizeof(limb_type) * CHAR_BIT - shift, count - sizeof(limb_type) * CHAR_BIT + shift, tag);
      result <<= sizeof(limb_type) * CHAR_BIT - shift;
   }
   if (limb < val.size())
      result |= (val.limbs()[limb] >> shift) & mask;
   return result;
}

template <class Backend>
inline std::uintmax_t extract_bits(const Backend& val, std::size_t location, std::size_t count, const std::integral_constant<bool, true>&)
{
   typename Backend::local_limb_type result = *val.limbs();
   typename Backend::local_limb_type mask   = count >= std::numeric_limits<typename Backend::local_limb_type>::digits ? ~static_cast<typename Backend::local_limb_type>(0) : (static_cast<typename Backend::local_limb_type>(1u) << count) - 1;
   return (result >> location) & mask;
}

} // namespace detail

template <std::size_t MinBits, std::size_t MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class OutputIterator>
OutputIterator export_bits(
    const number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, OutputIterator out, std::size_t chunk_size, bool msv_first = true)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
   using tag_type = typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::trivial_tag;
   if (!val)
   {
      *out = 0;
      ++out;
      return out;
   }
   std::size_t bitcount = boost::multiprecision::backends::eval_msb_imp(val.backend()) + 1;
   std::size_t chunks   = bitcount / chunk_size;
   if (bitcount % chunk_size)
      ++chunks;

   std::ptrdiff_t bit_location = msv_first ? bitcount - chunk_size : 0;
   std::ptrdiff_t bit_step     = msv_first ? -static_cast<int>(chunk_size) : chunk_size;
   while (bit_location % bit_step)
      ++bit_location;

   do
   {
      *out = detail::extract_bits(val.backend(), bit_location, chunk_size, tag_type());
      ++out;
      bit_location += bit_step;
   } while ((bit_location >= 0) && (bit_location < static_cast<int>(bitcount)));

   return out;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

}
} // namespace boost::multiprecision

#endif // BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP

/* import_export.hpp
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
*/