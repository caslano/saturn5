///////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP
#define BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP

namespace boost {
namespace multiprecision {

namespace detail {

template <class Backend, class Unsigned>
void assign_bits(Backend& val, Unsigned bits, unsigned bit_location, unsigned chunk_bits, const mpl::false_& tag)
{
   unsigned limb  = bit_location / (sizeof(limb_type) * CHAR_BIT);
   unsigned shift = bit_location % (sizeof(limb_type) * CHAR_BIT);

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
void assign_bits(Backend& val, Unsigned bits, unsigned bit_location, unsigned chunk_bits, const mpl::true_&)
{
   typedef typename Backend::local_limb_type local_limb_type;
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

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline void resize_to_bit_size(cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& newval, unsigned bits, const mpl::false_&)
{
   unsigned limb_count = static_cast<unsigned>(bits / (sizeof(limb_type) * CHAR_BIT));
   if (bits % (sizeof(limb_type) * CHAR_BIT))
      ++limb_count;
   static const unsigned max_limbs = MaxBits ? MaxBits / (CHAR_BIT * sizeof(limb_type)) + ((MaxBits % (CHAR_BIT * sizeof(limb_type))) ? 1 : 0) : (std::numeric_limits<unsigned>::max)();
   if (limb_count > max_limbs)
      limb_count = max_limbs;
   newval.resize(limb_count, limb_count);
   std::memset(newval.limbs(), 0, newval.size() * sizeof(limb_type));
}
template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator>
inline void resize_to_bit_size(cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& newval, unsigned, const mpl::true_&)
{
   *newval.limbs() = 0;
}

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class Iterator>
number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits_generic(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, Iterator i, Iterator j, unsigned chunk_size = 0, bool msv_first = true)
{
   typename number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>::backend_type newval;

   typedef typename std::iterator_traits<Iterator>::value_type                                   value_type;
   typedef typename boost::make_unsigned<value_type>::type                                       unsigned_value_type;
   typedef typename std::iterator_traits<Iterator>::difference_type                              difference_type;
   typedef typename boost::make_unsigned<difference_type>::type                                  size_type;
   typedef typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::trivial_tag tag_type;

   if (!chunk_size)
      chunk_size = std::numeric_limits<value_type>::digits;

   size_type limbs = std::distance(i, j);
   size_type bits  = limbs * chunk_size;

   detail::resize_to_bit_size(newval, static_cast<unsigned>(bits), tag_type());

   difference_type bit_location        = msv_first ? bits - chunk_size : 0;
   difference_type bit_location_change = msv_first ? -static_cast<difference_type>(chunk_size) : chunk_size;

   while (i != j)
   {
      detail::assign_bits(newval, static_cast<unsigned_value_type>(*i), static_cast<unsigned>(bit_location), chunk_size, tag_type());
      ++i;
      bit_location += bit_location_change;
   }

   newval.normalize();

   val.backend().swap(newval);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline typename boost::disable_if_c<boost::multiprecision::backends::is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value, number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&>::type
import_bits_fast(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, unsigned chunk_size = 0)
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
template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline typename boost::enable_if_c<boost::multiprecision::backends::is_trivial_cpp_int<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value, number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&>::type
import_bits_fast(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, unsigned chunk_size = 0)
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

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class Iterator>
inline number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, Iterator i, Iterator j, unsigned chunk_size = 0, bool msv_first = true)
{
   return detail::import_bits_generic(val, i, j, chunk_size, msv_first);
}

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class T>
inline number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>&
import_bits(
    number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, T* i, T* j, unsigned chunk_size = 0, bool msv_first = true)
{
#if BOOST_ENDIAN_LITTLE_BYTE
   if (((chunk_size % CHAR_BIT) == 0) && !msv_first)
      return detail::import_bits_fast(val, i, j, chunk_size);
#endif
   return detail::import_bits_generic(val, i, j, chunk_size, msv_first);
}

namespace detail {

template <class Backend>
boost::uintmax_t extract_bits(const Backend& val, unsigned location, unsigned count, const mpl::false_& tag)
{
   unsigned         limb   = location / (sizeof(limb_type) * CHAR_BIT);
   unsigned         shift  = location % (sizeof(limb_type) * CHAR_BIT);
   boost::uintmax_t result = 0;
   boost::uintmax_t mask   = count == std::numeric_limits<boost::uintmax_t>::digits ? ~static_cast<boost::uintmax_t>(0) : (static_cast<boost::uintmax_t>(1u) << count) - 1;
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
inline boost::uintmax_t extract_bits(const Backend& val, unsigned location, unsigned count, const mpl::true_&)
{
   typename Backend::local_limb_type result = *val.limbs();
   typename Backend::local_limb_type mask   = count >= std::numeric_limits<typename Backend::local_limb_type>::digits ? ~static_cast<typename Backend::local_limb_type>(0) : (static_cast<typename Backend::local_limb_type>(1u) << count) - 1;
   return (result >> location) & mask;
}

} // namespace detail

template <unsigned MinBits, unsigned MaxBits, cpp_integer_type SignType, cpp_int_check_type Checked, class Allocator, expression_template_option ExpressionTemplates, class OutputIterator>
OutputIterator export_bits(
    const number<cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>& val, OutputIterator out, unsigned chunk_size, bool msv_first = true)
{
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
   typedef typename cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>::trivial_tag tag_type;
   if (!val)
   {
      *out = 0;
      ++out;
      return out;
   }
   unsigned bitcount = boost::multiprecision::backends::eval_msb_imp(val.backend()) + 1;
   unsigned chunks   = bitcount / chunk_size;
   if (bitcount % chunk_size)
      ++chunks;

   int bit_location = msv_first ? bitcount - chunk_size : 0;
   int bit_step     = msv_first ? -static_cast<int>(chunk_size) : chunk_size;
   while (bit_location % bit_step)
      ++bit_location;

   do
   {
      *out = detail::extract_bits(val.backend(), bit_location, chunk_size, tag_type());
      ++out;
      bit_location += bit_step;
   } while ((bit_location >= 0) && (bit_location < (int)bitcount));

   return out;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

}
} // namespace boost::multiprecision

#endif // BOOST_MP_CPP_INT_IMPORT_EXPORT_HPP

/* import_export.hpp
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
*/