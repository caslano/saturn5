//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CHANNEL_HPP
#define BOOST_GIL_CHANNEL_HPP

#include <boost/gil/utilities.hpp>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/integer/integer_mask.hpp>

#include <cstdint>
#include <limits>
#include <type_traits>

#ifdef BOOST_GIL_DOXYGEN_ONLY
/// \def BOOST_GIL_CONFIG_HAS_UNALIGNED_ACCESS
/// \brief Define to allow unaligned memory access for models of packed channel value.
/// Theoretically (or historically?) on platforms which support dereferencing on
/// non-word memory boundary, unaligned access may result in performance improvement.
/// \warning Unfortunately, this optimization may be a C/C++ strict aliasing rules
/// violation, if accessed data buffer has effective type that cannot be aliased
/// without leading to undefined behaviour.
#define BOOST_GIL_CONFIG_HAS_UNALIGNED_ACCESS
#endif

#ifdef BOOST_GIL_CONFIG_HAS_UNALIGNED_ACCESS
#if defined(sun) || defined(__sun) || \             // SunOS
    defined(__osf__) || defined(__osf) || \         // Tru64
    defined(_hpux) || defined(hpux) || \            // HP-UX
    defined(__arm__) || defined(__ARM_ARCH) || \    // ARM
    defined(_AIX)                                   // AIX
#error Unaligned access strictly disabled for some UNIX platforms or ARM architecture
#elif defined(__i386__) || defined(__x86_64__) || defined(__vax__)
    // The check for little-endian architectures that tolerate unaligned memory
    // accesses is just an optimization. Nothing will break if it fails to detect
    // a suitable architecture.
    //
    // Unfortunately, this optimization may be a C/C++ strict aliasing rules violation
    // if accessed data buffer has effective type that cannot be aliased
    // without leading to undefined behaviour.
BOOST_PRAGMA_MESSAGE("CAUTION: Unaligned access tolerated on little-endian may cause undefined behaviour")
#else
#error Unaligned access disabled for unknown platforms and architectures
#endif
#endif // defined(BOOST_GIL_CONFIG_HAS_UNALIGNED_ACCESS)

namespace boost { namespace gil {

///////////////////////////////////////////
////  channel_traits
////
////  \ingroup ChannelModel
////  \class channel_traits
////  \brief defines properties of channels, such as their range and associated types
////
////  The channel traits must be defined for every model of ChannelConcept
////  Default traits are provided. For built-in types the default traits use
////  built-in pointer and reference and the channel range is the physical
////  range of the type. For classes, the default traits forward the associated types
////  and range to the class.
////
///////////////////////////////////////////

namespace detail {

template <typename T, bool IsClass>
struct channel_traits_impl;

// channel traits for custom class
template <typename T>
struct channel_traits_impl<T, true>
{
    using value_type = typename T::value_type;
    using reference = typename T::reference;
    using pointer = typename T::pointer;
    using const_reference = typename T::const_reference;
    using const_pointer = typename T::const_pointer;
    static constexpr bool is_mutable = T::is_mutable;
    static value_type min_value() { return T::min_value(); }
    static value_type max_value() { return T::max_value(); }
};

// channel traits implementation for built-in integral or floating point channel type
template <typename T>
struct channel_traits_impl<T, false>
{
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using const_reference = T const&;
    using const_pointer = T const*;
    static constexpr bool is_mutable = true;
    static value_type min_value() { return (std::numeric_limits<T>::min)(); }
    static value_type max_value() { return (std::numeric_limits<T>::max)(); }
};

// channel traits implementation for constant built-in scalar or floating point type
template <typename T>
struct channel_traits_impl<T const, false> : channel_traits_impl<T, false>
{
    using reference = T const&;
    using pointer = T const*;
    static constexpr bool is_mutable = false;
};

} // namespace detail

/**
\ingroup ChannelModel
\brief Traits for channels. Contains the following members:
\code
template <typename Channel>
struct channel_traits {
    using value_type = ...;
    using reference = ...;
    using pointer = ...;
    using const_reference = ...;
    using const_pointer = ...;

    static const bool is_mutable;
    static value_type min_value();
    static value_type max_value();
};
\endcode
*/
template <typename T>
struct channel_traits : detail::channel_traits_impl<T, std::is_class<T>::value> {};

// Channel traits for C++ reference type - remove the reference
template <typename T>
struct channel_traits<T&> : channel_traits<T> {};

// Channel traits for constant C++ reference type
template <typename T>
struct channel_traits<T const&> : channel_traits<T>
{
    using reference = typename channel_traits<T>::const_reference;
    using pointer = typename channel_traits<T>::const_pointer;
    static constexpr bool is_mutable = false;
};

///////////////////////////////////////////
////  scoped_channel_value
///////////////////////////////////////////

/// \defgroup ScopedChannelValue scoped_channel_value
/// \ingroup ChannelModel
/// \brief A channel adaptor that modifies the range of the source channel. Models: ChannelValueConcept
///
/// Example:
/// \code
/// // Create a double channel with range [-0.5 .. 0.5]
/// struct double_minus_half  { static double apply() { return -0.5; } };
/// struct double_plus_half   { static double apply() { return  0.5; } };
/// using bits64custom_t = scoped_channel_value<double, double_minus_half, double_plus_half>;
///
/// // channel_convert its maximum should map to the maximum
/// bits64custom_t x = channel_traits<bits64custom_t>::max_value();
/// assert(x == 0.5);
/// uint16_t y = channel_convert<uint16_t>(x);
/// assert(y == 65535);
/// \endcode

/// \ingroup ScopedChannelValue
/// \brief A channel adaptor that modifies the range of the source channel. Models: ChannelValueConcept
/// \tparam BaseChannelValue base channel (models ChannelValueConcept)
/// \tparam MinVal class with a static apply() function returning the minimum channel values
/// \tparam MaxVal class with a static apply() function returning the maximum channel values
template <typename BaseChannelValue, typename MinVal, typename MaxVal>
struct scoped_channel_value
{
    using value_type = scoped_channel_value<BaseChannelValue, MinVal, MaxVal>;
    using reference = value_type&;
    using pointer = value_type*;
    using const_reference = value_type const&;
    using const_pointer = value_type const*;
    static constexpr bool is_mutable = channel_traits<BaseChannelValue>::is_mutable;

    using base_channel_t = BaseChannelValue;

    static value_type min_value() { return MinVal::apply(); }
    static value_type max_value() { return MaxVal::apply(); }

    scoped_channel_value() = default;
    scoped_channel_value(scoped_channel_value const& other) : value_(other.value_) {}
    scoped_channel_value& operator=(scoped_channel_value const& other) = default;
    scoped_channel_value(BaseChannelValue value) : value_(value) {}
    scoped_channel_value& operator=(BaseChannelValue value)
    {
        value_ = value;
        return *this;
    }

    scoped_channel_value& operator++() { ++value_; return *this; }
    scoped_channel_value& operator--() { --value_; return *this; }

    scoped_channel_value operator++(int) { scoped_channel_value tmp=*this; this->operator++(); return tmp; }
    scoped_channel_value operator--(int) { scoped_channel_value tmp=*this; this->operator--(); return tmp; }

    template <typename Scalar2> scoped_channel_value& operator+=(Scalar2 v) { value_+=v; return *this; }
    template <typename Scalar2> scoped_channel_value& operator-=(Scalar2 v) { value_-=v; return *this; }
    template <typename Scalar2> scoped_channel_value& operator*=(Scalar2 v) { value_*=v; return *this; }
    template <typename Scalar2> scoped_channel_value& operator/=(Scalar2 v) { value_/=v; return *this; }

    operator BaseChannelValue() const { return value_; }
private:
    BaseChannelValue value_{};
};

template <typename T>
struct float_point_zero
{
    static constexpr T apply() { return 0.0f; }
};

template <typename T>
struct float_point_one
{
    static constexpr T apply() { return 1.0f; }
};

///////////////////////////////////////////
////  Support for sub-byte channels. These are integral channels whose value is contained in a range of bits inside an integral type
///////////////////////////////////////////

// It is necessary for packed channels to have their own value type. They cannot simply use an integral large enough to store the data. Here is why:
// - Any operation that requires returning the result by value will otherwise return the built-in integral type, which will have incorrect range
//   That means that after getting the value of the channel we cannot properly do channel_convert, channel_invert, etc.
// - Two channels are declared compatible if they have the same value type. That means that a packed channel is incorrectly declared compatible with an integral type
namespace detail {

// returns the smallest fast unsigned integral type that has at least NumBits bits
template <int NumBits>
struct min_fast_uint :
    std::conditional
    <
        NumBits <= 8,
        std::uint_least8_t,
        typename std::conditional
        <
            NumBits <= 16,
            std::uint_least16_t,
            typename std::conditional
            <
                NumBits <= 32,
                std::uint_least32_t,
                std::uintmax_t
            >::type
        >::type
    >
{};

template <int NumBits>
struct num_value_fn
    : std::conditional<NumBits < 32, std::uint32_t, std::uint64_t>
{};

template <int NumBits>
struct max_value_fn
    : std::conditional<NumBits <= 32, std::uint32_t, std::uint64_t>
{};

} // namespace detail

/// \defgroup PackedChannelValueModel packed_channel_value
/// \ingroup ChannelModel
/// \brief Represents the value of an unsigned integral channel operating over a bit range. Models: ChannelValueConcept
/// Example:
/// \code
/// // A 4-bit unsigned integral channel.
/// using bits4 = packed_channel_value<4>;
///
/// assert(channel_traits<bits4>::min_value()==0);
/// assert(channel_traits<bits4>::max_value()==15);
/// assert(sizeof(bits4)==1);
/// static_assert(gil::is_channel_integral<bits4>::value, "");
/// \endcode

/// \ingroup PackedChannelValueModel
/// \brief The value of a subbyte channel. Models: ChannelValueConcept
template <int NumBits>
class packed_channel_value
{
public:
    using integer_t = typename detail::min_fast_uint<NumBits>::type;

    using value_type = packed_channel_value<NumBits>;
    using reference = value_type&;
    using const_reference = value_type const&;
    using pointer = value_type*;
    using const_pointer = value_type const*;
    static constexpr bool is_mutable = true;

    static value_type min_value() { return 0; }
    static value_type max_value() { return low_bits_mask_t< NumBits >::sig_bits; }

    packed_channel_value() = default;
    packed_channel_value(integer_t v)
    {
        value_ = static_cast<integer_t>(v & low_bits_mask_t<NumBits>::sig_bits_fast);
    }

    template <typename Scalar>
    packed_channel_value(Scalar v)
    {
        value_ = packed_channel_value(static_cast<integer_t>(v));
    }

    static unsigned int num_bits() { return NumBits; }

    operator integer_t() const { return value_; }

private:
    integer_t value_{};
};

namespace detail {

template <std::size_t K>
struct static_copy_bytes
{
    void operator()(unsigned char const* from, unsigned char* to) const
    {
        *to = *from;
        static_copy_bytes<K - 1>()(++from, ++to);
    }
};

template <>
struct static_copy_bytes<0>
{
    void operator()(unsigned char const*, unsigned char*) const {}
};

template <typename Derived, typename BitField, int NumBits, bool IsMutable>
class packed_channel_reference_base
{
protected:
    using data_ptr_t = typename std::conditional<IsMutable, void*, void const*>::type;
public:
    data_ptr_t _data_ptr;   // void* pointer to the first byte of the bit range

    using value_type = packed_channel_value<NumBits>;
    using reference = const Derived;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    static constexpr int num_bits = NumBits;
    static constexpr bool is_mutable = IsMutable;

    static value_type min_value()       { return channel_traits<value_type>::min_value(); }
    static value_type max_value()       { return channel_traits<value_type>::max_value(); }

    using bitfield_t = BitField;
    using integer_t = typename value_type::integer_t;

    packed_channel_reference_base(data_ptr_t data_ptr) : _data_ptr(data_ptr) {}
    packed_channel_reference_base(const packed_channel_reference_base& ref) : _data_ptr(ref._data_ptr) {}
    const Derived& operator=(integer_t v) const { set(v); return derived(); }

    const Derived& operator++() const { set(get()+1); return derived(); }
    const Derived& operator--() const { set(get()-1); return derived(); }

    Derived operator++(int) const { Derived tmp=derived(); this->operator++(); return tmp; }
    Derived operator--(int) const { Derived tmp=derived(); this->operator--(); return tmp; }

    template <typename Scalar2> const Derived& operator+=(Scalar2 v) const { set( static_cast<integer_t>(  get() + v )); return derived(); }
    template <typename Scalar2> const Derived& operator-=(Scalar2 v) const { set( static_cast<integer_t>(  get() - v )); return derived(); }
    template <typename Scalar2> const Derived& operator*=(Scalar2 v) const { set( static_cast<integer_t>(  get() * v )); return derived(); }
    template <typename Scalar2> const Derived& operator/=(Scalar2 v) const { set( static_cast<integer_t>(  get() / v )); return derived(); }

    operator integer_t() const { return get(); }
    data_ptr_t operator &() const {return _data_ptr;}
protected:

    using num_value_t = typename detail::num_value_fn<NumBits>::type;
    using max_value_t = typename detail::max_value_fn<NumBits>::type;

    static const num_value_t num_values = static_cast< num_value_t >( 1 ) << NumBits ;
    static const max_value_t max_val    = static_cast< max_value_t >( num_values - 1 );

#if defined(BOOST_GIL_CONFIG_HAS_UNALIGNED_ACCESS)
    const bitfield_t& get_data()                      const { return *static_cast<const bitfield_t*>(_data_ptr); }
    void              set_data(const bitfield_t& val) const {        *static_cast<      bitfield_t*>(_data_ptr) = val; }
#else
    bitfield_t get_data() const {
        bitfield_t ret;
        static_copy_bytes<sizeof(bitfield_t) >()(gil_reinterpret_cast_c<const unsigned char*>(_data_ptr),gil_reinterpret_cast<unsigned char*>(&ret));
        return ret;
    }
    void set_data(const bitfield_t& val) const {
        static_copy_bytes<sizeof(bitfield_t) >()(gil_reinterpret_cast_c<const unsigned char*>(&val),gil_reinterpret_cast<unsigned char*>(_data_ptr));
    }
#endif

private:
    void set(integer_t value) const {     // can this be done faster??
        this->derived().set_unsafe(((value % num_values) + num_values) % num_values);
    }
    integer_t get() const { return derived().get(); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }
};
}   // namespace detail

/// \defgroup PackedChannelReferenceModel packed_channel_reference
/// \ingroup ChannelModel
/// \brief Represents a reference proxy to a channel operating over a bit range whose offset is fixed at compile time. Models ChannelConcept
/// Example:
/// \code
/// // Reference to a 2-bit channel starting at bit 1 (i.e. the second bit)
/// using bits2_1_ref_t = packed_channel_reference<uint16_t,1,2,true> const;
///
/// uint16_t data=0;
/// bits2_1_ref_t channel_ref(&data);
/// channel_ref = channel_traits<bits2_1_ref_t>::max_value();   // == 3
/// assert(data == 6);                                          // == 3<<1 == 6
/// \endcode

/// \tparam BitField A type that holds the bits of the pixel from which the channel is referenced. Typically an integral type, like std::uint16_t
/// \tparam Defines the sequence of bits in the data value that contain the channel
/// \tparam true if the reference is mutable
template <typename BitField, int FirstBit, int NumBits, bool IsMutable>
class packed_channel_reference;

/// \tparam A type that holds the bits of the pixel from which the channel is referenced. Typically an integral type, like std::uint16_t
/// \tparam Defines the sequence of bits in the data value that contain the channel
/// \tparam true if the reference is mutable
template <typename BitField, int NumBits, bool IsMutable>
class packed_dynamic_channel_reference;

/// \ingroup PackedChannelReferenceModel
/// \brief A constant subbyte channel reference whose bit offset is fixed at compile time. Models ChannelConcept
template <typename BitField, int FirstBit, int NumBits>
class packed_channel_reference<BitField, FirstBit, NumBits, false>
    : public detail::packed_channel_reference_base
        <
            packed_channel_reference<BitField, FirstBit, NumBits, false>,
            BitField,
            NumBits,
            false
        >
{
    using parent_t = detail::packed_channel_reference_base
        <
            packed_channel_reference<BitField, FirstBit, NumBits, false>,
            BitField,
            NumBits,
            false
        >;

    friend class packed_channel_reference<BitField, FirstBit, NumBits, true>;

    static const BitField channel_mask = static_cast<BitField>(parent_t::max_val) << FirstBit;

    void operator=(packed_channel_reference const&);
public:
    using const_reference = packed_channel_reference<BitField,FirstBit,NumBits,false> const;
    using mutable_reference = packed_channel_reference<BitField,FirstBit,NumBits,true> const;
    using integer_t = typename parent_t::integer_t;

    explicit packed_channel_reference(const void* data_ptr) : parent_t(data_ptr) {}
    packed_channel_reference(const packed_channel_reference& ref) : parent_t(ref._data_ptr) {}
    packed_channel_reference(const mutable_reference& ref) : parent_t(ref._data_ptr) {}

    unsigned first_bit() const { return FirstBit; }

    integer_t get() const { return integer_t((this->get_data()&channel_mask) >> FirstBit); }
};

/// \ingroup PackedChannelReferenceModel
/// \brief A mutable subbyte channel reference whose bit offset is fixed at compile time. Models ChannelConcept
template <typename BitField, int FirstBit, int NumBits>
class packed_channel_reference<BitField,FirstBit,NumBits,true>
   : public detail::packed_channel_reference_base<packed_channel_reference<BitField,FirstBit,NumBits,true>,BitField,NumBits,true>
{
    using parent_t = detail::packed_channel_reference_base<packed_channel_reference<BitField,FirstBit,NumBits,true>,BitField,NumBits,true>;
    friend class packed_channel_reference<BitField,FirstBit,NumBits,false>;

    static const BitField channel_mask = static_cast< BitField >( parent_t::max_val ) << FirstBit;

public:
    using const_reference = packed_channel_reference<BitField,FirstBit,NumBits,false> const;
    using mutable_reference = packed_channel_reference<BitField,FirstBit,NumBits,true> const;
    using integer_t = typename parent_t::integer_t;

    explicit packed_channel_reference(void* data_ptr) : parent_t(data_ptr) {}
    packed_channel_reference(const packed_channel_reference& ref) : parent_t(ref._data_ptr) {}

    packed_channel_reference const& operator=(integer_t value) const
    {
        BOOST_ASSERT(value <= parent_t::max_val);
        set_unsafe(value);
        return *this;
    }

    const packed_channel_reference& operator=(const mutable_reference& ref) const { set_from_reference(ref.get_data()); return *this; }
    const packed_channel_reference& operator=(const const_reference&   ref) const { set_from_reference(ref.get_data()); return *this; }

    template <bool Mutable1>
    const packed_channel_reference& operator=(const packed_dynamic_channel_reference<BitField,NumBits,Mutable1>& ref) const { set_unsafe(ref.get()); return *this; }

    unsigned first_bit() const { return FirstBit; }

    integer_t get()                  const { return integer_t((this->get_data()&channel_mask) >> FirstBit); }
    void set_unsafe(integer_t value) const { this->set_data((this->get_data() & ~channel_mask) | (( static_cast< BitField >( value )<<FirstBit))); }
private:
    void set_from_reference(const BitField& other_bits) const { this->set_data((this->get_data() & ~channel_mask) | (other_bits & channel_mask)); }
};

}}  // namespace boost::gil

namespace std {
// We are forced to define swap inside std namespace because on some platforms (Visual Studio 8) STL calls swap qualified.
// swap with 'left bias':
// - swap between proxy and anything
// - swap between value type and proxy
// - swap between proxy and proxy

/// \ingroup PackedChannelReferenceModel
/// \brief swap for packed_channel_reference
template <typename BF, int FB, int NB, bool M, typename R>
inline
void swap(boost::gil::packed_channel_reference<BF, FB, NB, M> const x, R& y)
{
    boost::gil::swap_proxy
    <
        typename boost::gil::packed_channel_reference<BF, FB, NB, M>::value_type
    >(x, y);
}


/// \ingroup PackedChannelReferenceModel
/// \brief swap for packed_channel_reference
template <typename BF, int FB, int NB, bool M>
inline
void swap(
    typename boost::gil::packed_channel_reference<BF, FB, NB, M>::value_type& x,
    boost::gil::packed_channel_reference<BF, FB, NB, M> const y)
{
    boost::gil::swap_proxy
    <
        typename boost::gil::packed_channel_reference<BF, FB, NB, M>::value_type
    >(x,y);
}

/// \ingroup PackedChannelReferenceModel
/// \brief swap for packed_channel_reference
template <typename BF, int FB, int NB, bool M> inline
void swap(
    boost::gil::packed_channel_reference<BF, FB, NB, M> const x,
    boost::gil::packed_channel_reference<BF, FB, NB, M> const y)
{
    boost::gil::swap_proxy
    <
        typename boost::gil::packed_channel_reference<BF, FB, NB, M>::value_type
    >(x,y);
}

}   // namespace std

namespace boost { namespace gil {

/// \defgroup PackedChannelDynamicReferenceModel packed_dynamic_channel_reference
/// \ingroup ChannelModel
/// \brief Represents a reference proxy to a channel operating over a bit range whose offset is specified at run time. Models ChannelConcept
///
/// Example:
/// \code
/// // Reference to a 2-bit channel whose offset is specified at construction time
/// using bits2_dynamic_ref_t = packed_dynamic_channel_reference<uint8_t,2,true> const;
///
/// uint16_t data=0;
/// bits2_dynamic_ref_t channel_ref(&data,1);
/// channel_ref = channel_traits<bits2_dynamic_ref_t>::max_value();     // == 3
/// assert(data == 6);                                                  // == (3<<1) == 6
/// \endcode

/// \brief Models a constant subbyte channel reference whose bit offset is a runtime parameter. Models ChannelConcept
///        Same as packed_channel_reference, except that the offset is a runtime parameter
/// \ingroup PackedChannelDynamicReferenceModel
template <typename BitField, int NumBits>
class packed_dynamic_channel_reference<BitField,NumBits,false>
   : public detail::packed_channel_reference_base<packed_dynamic_channel_reference<BitField,NumBits,false>,BitField,NumBits,false>
{
    using parent_t = detail::packed_channel_reference_base<packed_dynamic_channel_reference<BitField,NumBits,false>,BitField,NumBits,false>;
    friend class packed_dynamic_channel_reference<BitField,NumBits,true>;

    unsigned _first_bit;     // 0..7

    void operator=(const packed_dynamic_channel_reference&);
public:
    using const_reference = packed_dynamic_channel_reference<BitField,NumBits,false> const;
    using mutable_reference = packed_dynamic_channel_reference<BitField,NumBits,true> const;
    using integer_t = typename parent_t::integer_t;

    packed_dynamic_channel_reference(const void* data_ptr, unsigned first_bit) : parent_t(data_ptr), _first_bit(first_bit) {}
    packed_dynamic_channel_reference(const const_reference&   ref) : parent_t(ref._data_ptr), _first_bit(ref._first_bit) {}
    packed_dynamic_channel_reference(const mutable_reference& ref) : parent_t(ref._data_ptr), _first_bit(ref._first_bit) {}

    unsigned first_bit() const { return _first_bit; }

    integer_t get() const {
        const BitField channel_mask = static_cast< integer_t >( parent_t::max_val ) <<_first_bit;
        return static_cast< integer_t >(( this->get_data()&channel_mask ) >> _first_bit );
    }
};

/// \brief Models a mutable subbyte channel reference whose bit offset is a runtime parameter. Models ChannelConcept
///        Same as packed_channel_reference, except that the offset is a runtime parameter
/// \ingroup PackedChannelDynamicReferenceModel
template <typename BitField, int NumBits>
class packed_dynamic_channel_reference<BitField,NumBits,true>
   : public detail::packed_channel_reference_base<packed_dynamic_channel_reference<BitField,NumBits,true>,BitField,NumBits,true>
{
    using parent_t = detail::packed_channel_reference_base<packed_dynamic_channel_reference<BitField,NumBits,true>,BitField,NumBits,true>;
    friend class packed_dynamic_channel_reference<BitField,NumBits,false>;

    unsigned _first_bit;

public:
    using const_reference = packed_dynamic_channel_reference<BitField,NumBits,false> const;
    using mutable_reference = packed_dynamic_channel_reference<BitField,NumBits,true> const;
    using integer_t = typename parent_t::integer_t;

    packed_dynamic_channel_reference(void* data_ptr, unsigned first_bit) : parent_t(data_ptr), _first_bit(first_bit) {}
    packed_dynamic_channel_reference(const packed_dynamic_channel_reference& ref) : parent_t(ref._data_ptr), _first_bit(ref._first_bit) {}

    packed_dynamic_channel_reference const& operator=(integer_t value) const
    {
        BOOST_ASSERT(value <= parent_t::max_val);
        set_unsafe(value);
        return *this;
    }

    const packed_dynamic_channel_reference& operator=(const mutable_reference& ref) const {  set_unsafe(ref.get()); return *this; }
    const packed_dynamic_channel_reference& operator=(const const_reference&   ref) const {  set_unsafe(ref.get()); return *this; }

    template <typename BitField1, int FirstBit1, bool Mutable1>
    const packed_dynamic_channel_reference& operator=(const packed_channel_reference<BitField1, FirstBit1, NumBits, Mutable1>& ref) const
        {  set_unsafe(ref.get()); return *this; }

    unsigned first_bit() const { return _first_bit; }

    integer_t get() const {
        const BitField channel_mask = static_cast< integer_t >( parent_t::max_val ) << _first_bit;
        return static_cast< integer_t >(( this->get_data()&channel_mask ) >> _first_bit );
    }

    void set_unsafe(integer_t value) const {
        const BitField channel_mask = static_cast< integer_t >( parent_t::max_val ) << _first_bit;
        this->set_data((this->get_data() & ~channel_mask) | value<<_first_bit);
    }
};
} }  // namespace boost::gil

namespace std {
// We are forced to define swap inside std namespace because on some platforms (Visual Studio 8) STL calls swap qualified.
// swap with 'left bias':
// - swap between proxy and anything
// - swap between value type and proxy
// - swap between proxy and proxy


/// \ingroup PackedChannelDynamicReferenceModel
/// \brief swap for packed_dynamic_channel_reference
template <typename BF, int NB, bool M, typename R> inline
void swap(const boost::gil::packed_dynamic_channel_reference<BF,NB,M> x, R& y) {
    boost::gil::swap_proxy<typename boost::gil::packed_dynamic_channel_reference<BF,NB,M>::value_type>(x,y);
}


/// \ingroup PackedChannelDynamicReferenceModel
/// \brief swap for packed_dynamic_channel_reference
template <typename BF, int NB, bool M> inline
void swap(typename boost::gil::packed_dynamic_channel_reference<BF,NB,M>::value_type& x, const boost::gil::packed_dynamic_channel_reference<BF,NB,M> y) {
    boost::gil::swap_proxy<typename boost::gil::packed_dynamic_channel_reference<BF,NB,M>::value_type>(x,y);
}

/// \ingroup PackedChannelDynamicReferenceModel
/// \brief swap for packed_dynamic_channel_reference
template <typename BF, int NB, bool M> inline
void swap(const boost::gil::packed_dynamic_channel_reference<BF,NB,M> x, const boost::gil::packed_dynamic_channel_reference<BF,NB,M> y) {
    boost::gil::swap_proxy<typename boost::gil::packed_dynamic_channel_reference<BF,NB,M>::value_type>(x,y);
}
}   // namespace std

// \brief Determines the fundamental type which may be used, e.g., to cast from larger to smaller channel types.
namespace boost { namespace gil {
template <typename T>
struct base_channel_type_impl { using type = T; };

template <int N>
struct base_channel_type_impl<packed_channel_value<N> >
{ using type = typename packed_channel_value<N>::integer_t; };

template <typename B, int F, int N, bool M>
struct base_channel_type_impl<packed_channel_reference<B, F, N, M> >
{
    using type = typename packed_channel_reference<B,F,N,M>::integer_t;
};

template <typename B, int N, bool M>
struct base_channel_type_impl<packed_dynamic_channel_reference<B, N, M> >
{
    using type = typename packed_dynamic_channel_reference<B,N,M>::integer_t;
};

template <typename ChannelValue, typename MinV, typename MaxV>
struct base_channel_type_impl<scoped_channel_value<ChannelValue, MinV, MaxV> >
{ using type = ChannelValue; };

template <typename T>
struct base_channel_type : base_channel_type_impl<typename std::remove_cv<T>::type> {};

}} //namespace boost::gil

#endif

/* channel.hpp
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
*/