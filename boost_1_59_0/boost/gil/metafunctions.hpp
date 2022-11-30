//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_METAFUNCTIONS_HPP
#define BOOST_GIL_METAFUNCTIONS_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/concepts/detail/type_traits.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <iterator>
#include <type_traits>

namespace boost { namespace gil {

// forward declarations
template <typename T, typename L> struct pixel;
template <typename BitField,typename ChannelRefs,typename Layout> struct packed_pixel;
template <typename T, typename C> struct planar_pixel_reference;
template <typename IC, typename C> struct planar_pixel_iterator;
template <typename I> class memory_based_step_iterator;
template <typename I> class memory_based_2d_locator;
template <typename L> class image_view;
template <typename Pixel, bool IsPlanar, typename Alloc> class image;
template <typename T> struct channel_type;
template <typename T> struct color_space_type;
template <typename T> struct channel_mapping_type;
template <typename It> struct is_iterator_adaptor;
template <typename It> struct iterator_adaptor_get_base;
template <typename BitField, typename ChannelBitSizes, typename Layout, bool IsMutable> struct bit_aligned_pixel_reference;

//////////////////////////////////////////////////
///
///  TYPE ANALYSIS METAFUNCTIONS
///  Predicate metafunctions determining properties of GIL types
///
//////////////////////////////////////////////////


/// \defgroup GILIsBasic xxx_is_basic
/// \ingroup TypeAnalysis
/// \brief Determines if GIL constructs are basic.
///    Basic constructs are the ones that can be generated with the type
///    factory methods pixel_reference_type, iterator_type, locator_type, view_type and image_type
///    They can be mutable/immutable, planar/interleaved, step/nonstep. They must use GIL-provided models.

/// \brief Determines if a given pixel reference is basic
///    Basic references must use gil::pixel& (if interleaved), gil::planar_pixel_reference (if planar). They must use the standard constness rules.
/// \ingroup GILIsBasic
template <typename PixelRef>
struct pixel_reference_is_basic : public std::false_type {};

template <typename T, typename L>
struct pixel_reference_is_basic<pixel<T, L>&> : std::true_type {};

template <typename T, typename L>
struct pixel_reference_is_basic<const pixel<T, L>&> : std::true_type {};

template <typename TR, typename CS>
struct pixel_reference_is_basic<planar_pixel_reference<TR, CS>> : std::true_type {};

template <typename TR, typename CS>
struct pixel_reference_is_basic<const planar_pixel_reference<TR, CS>> : std::true_type {};

/// \brief Determines if a given pixel iterator is basic
///    Basic iterators must use gil::pixel (if interleaved), gil::planar_pixel_iterator (if planar) and gil::memory_based_step_iterator (if step). They must use the standard constness rules.
/// \ingroup GILIsBasic
template <typename Iterator>
struct iterator_is_basic : std::false_type {};

/// \tparam T mutable interleaved pixel type
template <typename T, typename L>
struct iterator_is_basic<pixel<T, L>*> : std::true_type {};

/// \tparam T immutable interleaved pixel type
template <typename T, typename L>
struct iterator_is_basic<pixel<T, L> const*> : std::true_type {};

/// \tparam T mutable planar pixel type
template <typename T, typename CS>
struct iterator_is_basic<planar_pixel_iterator<T*, CS>> : std::true_type {};

/// \tparam T immutable planar pixel type
template <typename T, typename CS>
struct iterator_is_basic<planar_pixel_iterator<T const*, CS>> : std::true_type {};

/// \tparam T mutable interleaved step
template <typename T, typename L>
struct iterator_is_basic<memory_based_step_iterator<pixel<T, L>*>> : std::true_type {};

/// \tparam T immutable interleaved step
template <typename T, typename L>
struct iterator_is_basic<memory_based_step_iterator<pixel<T, L> const*>> : std::true_type {};

/// \tparam T mutable planar step
template <typename T, typename CS>
struct iterator_is_basic<memory_based_step_iterator<planar_pixel_iterator<T*, CS>>>
    : std::true_type
{};

/// \tparam T immutable planar step
template <typename T, typename CS>
struct iterator_is_basic<memory_based_step_iterator<planar_pixel_iterator<T const*, CS>>>
    : std::true_type
{};


/// \ingroup GILIsBasic
/// \brief Determines if a given locator is basic. A basic locator is memory-based and has basic x_iterator and y_iterator
template <typename Loc>
struct locator_is_basic : std::false_type {};

template <typename Iterator>
struct locator_is_basic
    <
        memory_based_2d_locator<memory_based_step_iterator<Iterator>>
    > : iterator_is_basic<Iterator>
{};

/// \ingroup GILIsBasic
/// \brief Basic views must be over basic locators
template <typename View>
struct view_is_basic : std::false_type {};

template <typename Loc>
struct view_is_basic<image_view<Loc>> : locator_is_basic<Loc> {};

/// \ingroup GILIsBasic
/// \brief Basic images must use basic views and std::allocator
template <typename Img>
struct image_is_basic : std::false_type {};

template <typename Pixel, bool IsPlanar, typename Alloc>
struct image_is_basic<image<Pixel, IsPlanar, Alloc>> : std::true_type {};


/// \defgroup GILIsStep xxx_is_step
/// \ingroup TypeAnalysis
/// \brief Determines if the given iterator/locator/view has a step that could be set dynamically

template <typename I>
struct iterator_is_step;

namespace detail {

template <typename It, bool IsBase, bool EqualsStepType>
struct iterator_is_step_impl;

// iterator that has the same type as its dynamic_x_step_type must be a step iterator
template <typename It, bool IsBase>
struct iterator_is_step_impl<It, IsBase, true> : std::true_type {};

// base iterator can never be a step iterator
template <typename It>
struct iterator_is_step_impl<It, true, false> : std::false_type {};

// for an iterator adaptor, see if its base is step
template <typename It>
struct iterator_is_step_impl<It, false, false>
    : public iterator_is_step<typename iterator_adaptor_get_base<It>::type> {};

} // namespace detail

/// \ingroup GILIsStep
/// \brief Determines if the given iterator has a step that could be set dynamically
template <typename I>
struct iterator_is_step
    : detail::iterator_is_step_impl
    <
        I,
        !is_iterator_adaptor<I>::value,
        std::is_same<I, typename dynamic_x_step_type<I>::type
    >::value
>
{};

/// \ingroup GILIsStep
/// \brief Determines if the given locator has a horizontal step that could be set dynamically
template <typename L> struct locator_is_step_in_x : public iterator_is_step<typename L::x_iterator> {};

/// \ingroup GILIsStep
/// \brief Determines if the given locator has a vertical step that could be set dynamically
template <typename L> struct locator_is_step_in_y : public iterator_is_step<typename L::y_iterator> {};

/// \ingroup GILIsStep
/// \brief Determines if the given view has a horizontal step that could be set dynamically
template <typename V> struct view_is_step_in_x : public locator_is_step_in_x<typename V::xy_locator> {};

/// \ingroup GILIsStep
/// \brief Determines if the given view has a vertical step that could be set dynamically
template <typename V> struct view_is_step_in_y : public locator_is_step_in_y<typename V::xy_locator> {};

/// \brief Determines whether the given pixel reference is a proxy class or a native C++ reference
/// \ingroup TypeAnalysis
template <typename PixelReference>
struct pixel_reference_is_proxy
    : mp11::mp_not
    <
        std::is_same
        <
            typename detail::remove_const_and_reference<PixelReference>::type,
            typename detail::remove_const_and_reference<PixelReference>::type::value_type
        >
    >
{};

/// \brief Given a model of a pixel, determines whether the model represents a pixel reference (as opposed to pixel value)
/// \ingroup TypeAnalysis
template <typename Pixel>
struct pixel_is_reference
    : mp11::mp_or<is_reference<Pixel>, pixel_reference_is_proxy<Pixel>> {};

/// \defgroup GILIsMutable xxx_is_mutable
/// \ingroup TypeAnalysis
/// \brief Determines if the given pixel reference/iterator/locator/view is mutable (i.e. its pixels can be changed)

/// \ingroup GILIsMutable
/// \brief Determines if the given pixel reference is mutable (i.e. its channels can be changed)
///
/// Note that built-in C++ references obey the const qualifier but reference proxy classes do not.
template <typename R>
struct pixel_reference_is_mutable
    : std::integral_constant<bool, std::remove_reference<R>::type::is_mutable>
{};

template <typename R>
struct pixel_reference_is_mutable<R const&>
    : mp11::mp_and<pixel_reference_is_proxy<R>, pixel_reference_is_mutable<R>>
{};

/// \ingroup GILIsMutable
/// \brief Determines if the given locator is mutable (i.e. its pixels can be changed)
template <typename L> struct locator_is_mutable : public iterator_is_mutable<typename L::x_iterator> {};
/// \ingroup GILIsMutable
/// \brief Determines if the given view is mutable (i.e. its pixels can be changed)
template <typename V> struct view_is_mutable : public iterator_is_mutable<typename V::x_iterator> {};


//////////////////////////////////////////////////
///
///  TYPE FACTORY METAFUNCTIONS
///  Metafunctions returning GIL types from other GIL types
///
//////////////////////////////////////////////////

/// \defgroup TypeFactoryFromElements xxx_type
/// \ingroup TypeFactory
/// \brief Returns the type of a homogeneous GIL construct given its elements (channel, layout, whether it is planar, step, mutable, etc.)

/// \defgroup TypeFactoryFromPixel xxx_type_from_pixel
/// \ingroup TypeFactory
/// \brief Returns the type of a GIL construct given its pixel type, whether it is planar, step, mutable, etc.

/// \defgroup TypeFactoryDerived derived_xxx_type
/// \ingroup TypeFactory
/// \brief Returns the type of a homogeneous GIL construct given a related construct by changing some of its properties

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous pixel reference given the channel type, layout, whether it operates on planar data and whether it is mutable
template <typename T, typename L, bool IsPlanar=false, bool IsMutable=true> struct pixel_reference_type{};
template <typename T, typename L> struct pixel_reference_type<T,L,false,true > { using type = pixel<T,L>&; };
template <typename T, typename L> struct pixel_reference_type<T,L,false,false> { using type = pixel<T,L> const&; };
template <typename T, typename L> struct pixel_reference_type<T,L,true,true> { using type = planar_pixel_reference<typename channel_traits<T>::reference,typename color_space_type<L>::type> const; };       // TODO: Assert M=identity
template <typename T, typename L> struct pixel_reference_type<T,L,true,false> { using type = planar_pixel_reference<typename channel_traits<T>::const_reference,typename color_space_type<L>::type> const; };// TODO: Assert M=identity

/// \ingroup TypeFactoryFromPixel
/// \brief Returns the type of a pixel iterator given the pixel type, whether it operates on planar data, whether it is a step iterator, and whether it is mutable
template <typename Pixel, bool IsPlanar=false, bool IsStep=false, bool IsMutable=true> struct iterator_type_from_pixel{};
template <typename Pixel> struct iterator_type_from_pixel<Pixel,false,false,true > { using type = Pixel *; };
template <typename Pixel> struct iterator_type_from_pixel<Pixel,false,false,false> { using type = const Pixel *; };
template <typename Pixel> struct iterator_type_from_pixel<Pixel,true,false,true> {
    using type = planar_pixel_iterator<typename channel_traits<typename channel_type<Pixel>::type>::pointer,typename color_space_type<Pixel>::type>;
};
template <typename Pixel> struct iterator_type_from_pixel<Pixel,true,false,false> {
    using type = planar_pixel_iterator<typename channel_traits<typename channel_type<Pixel>::type>::const_pointer,typename color_space_type<Pixel>::type>;
};
template <typename Pixel, bool IsPlanar, bool IsMutable> struct iterator_type_from_pixel<Pixel,IsPlanar,true,IsMutable> {
    using type = memory_based_step_iterator<typename iterator_type_from_pixel<Pixel,IsPlanar,false,IsMutable>::type>;
};

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous iterator given the channel type, layout, whether it operates on planar data, whether it is a step iterator, and whether it is mutable
template <typename T, typename L, bool IsPlanar=false, bool IsStep=false, bool IsMutable=true> struct iterator_type{};
template <typename T, typename L> struct iterator_type<T,L,false,false,true > { using type = pixel<T,L>*; };
template <typename T, typename L> struct iterator_type<T,L,false,false,false> { using type = pixel<T,L> const*; };
template <typename T, typename L> struct iterator_type<T,L,true,false,true> { using type = planar_pixel_iterator<T*,typename L::color_space_t>; };               // TODO: Assert M=identity
template <typename T, typename L> struct iterator_type<T,L,true,false,false> { using type = planar_pixel_iterator<const T*,typename L::color_space_t>; };        // TODO: Assert M=identity
template <typename T, typename L, bool IsPlanar, bool IsMutable> struct iterator_type<T,L,IsPlanar,true,IsMutable> {
    using type = memory_based_step_iterator<typename iterator_type<T,L,IsPlanar,false,IsMutable>::type>;
};

/// \brief Given a pixel iterator defining access to pixels along a row, returns the types of the corresponding built-in step_iterator, xy_locator, image_view
/// \ingroup TypeFactory
template <typename XIterator>
struct type_from_x_iterator
{
    using step_iterator_t = memory_based_step_iterator<XIterator>;
    using xy_locator_t = memory_based_2d_locator<step_iterator_t>;
    using view_t = image_view<xy_locator_t>;
};

namespace detail {

template <typename BitField, typename FirstBit, typename NumBits>
struct packed_channel_reference_type
{
    using type = packed_channel_reference
        <
            BitField, FirstBit::value, NumBits::value, true
        > const;
};

template <typename BitField, typename ChannelBitSizes>
class packed_channel_references_vector_type
{
    template <typename FirstBit, typename NumBits>
    using reference_type = typename packed_channel_reference_type<BitField, FirstBit, NumBits>::type;

    // If ChannelBitSizesVector is mp11::mp_list_c<int,7,7,2>
    // Then first_bits_vector will be mp11::mp_list_c<int,0,7,14,16>
    using first_bit_list = mp11::mp_fold_q
        <
            ChannelBitSizes,
            mp11::mp_list<std::integral_constant<int, 0>>,
            mp11::mp_bind
            <
                mp11::mp_push_back,
                mp11::_1,
                mp11::mp_bind
                <
                    mp11::mp_plus,
                    mp11::mp_bind<mp_back, mp11::_1>,
                    mp11::_2
                >
            >
        >;

    static_assert(mp11::mp_at_c<first_bit_list, 0>::value == 0, "packed channel first bit must be 0");

public:
    using type = mp11::mp_transform
        <
            reference_type,
            mp_pop_back<first_bit_list>,
            ChannelBitSizes
        >;
};

} // namespace detail

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a packed pixel given its bitfield type, the bit size of its channels and its layout.
///
/// A packed pixel has channels that cover bit ranges but itself is byte aligned. RGB565 pixel is an example.
///
/// The size of ChannelBitSizes must equal the number of channels in the given layout
/// The sum of bit sizes for all channels must be less than or equal to the number of bits in BitField (and cannot exceed 64).
///  If it is less than the number of bits in BitField, the last bits will be unused.
template <typename BitField, typename ChannelBitSizes, typename Layout>
struct packed_pixel_type
{
    using type = packed_pixel
        <
            BitField,
            typename detail::packed_channel_references_vector_type
            <
                BitField,
                ChannelBitSizes
            >::type,
        Layout>;
};

/// \defgroup TypeFactoryPacked packed_image_type,bit_aligned_image_type
/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of an image whose channels are not byte-aligned.
///
/// A packed image is an image whose pixels are byte aligned, such as "rgb565". <br>
/// A bit-aligned image is an image whose pixels are not byte aligned, such as "rgb222". <br>
///
/// The sum of the bit sizes of all channels cannot exceed 64.

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of an interleaved packed image: an image whose channels may not be byte-aligned, but whose pixels are byte aligned.
template <typename BitField, typename ChannelBitSizes, typename Layout, typename Alloc=std::allocator<unsigned char>>
struct packed_image_type
{
    using type = image<typename packed_pixel_type<BitField,ChannelBitSizes,Layout>::type,false,Alloc>;
};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a single-channel image given its bitfield type, the bit size of its channel and its layout
template <typename BitField, unsigned Size1, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct packed_image1_type
    : packed_image_type<BitField, mp11::mp_list_c<unsigned, Size1>, Layout, Alloc>
{};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a two channel image given its bitfield type, the bit size of its channels and its layout
template <typename BitField, unsigned Size1, unsigned Size2, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct packed_image2_type
    : packed_image_type<BitField, mp11::mp_list_c<unsigned, Size1, Size2>, Layout, Alloc>
{};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a three channel image given its bitfield type, the bit size of its channels and its layout
template <typename BitField, unsigned Size1, unsigned Size2, unsigned Size3, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct packed_image3_type
    : packed_image_type<BitField, mp11::mp_list_c<unsigned, Size1, Size2, Size3>, Layout, Alloc>
{};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a four channel image given its bitfield type, the bit size of its channels and its layout
template <typename BitField, unsigned Size1, unsigned Size2, unsigned Size3, unsigned Size4, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct packed_image4_type
    : packed_image_type<BitField, mp11::mp_list_c<unsigned, Size1, Size2, Size3, Size4>, Layout, Alloc>
{};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a five channel image given its bitfield type, the bit size of its channels and its layout
template <typename BitField, unsigned Size1, unsigned Size2, unsigned Size3, unsigned Size4, unsigned Size5, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct packed_image5_type
    : packed_image_type<BitField, mp11::mp_list_c<unsigned, Size1, Size2, Size3, Size4, Size5>, Layout, Alloc> {};


/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a packed image whose pixels may not be byte aligned. For example, an "rgb222" image is bit-aligned because its pixel spans six bits.
///
/// Note that the alignment parameter in the constructor of bit-aligned images is in bit units. For example, if you want to construct a bit-aligned
/// image whose rows are byte-aligned, use 8 as the alignment parameter, not 1.
///
template
<
    typename ChannelBitSizes,
    typename Layout,
    typename Alloc = std::allocator<unsigned char>
>
struct bit_aligned_image_type
{
private:

    static constexpr int bit_size =
        mp11::mp_fold
        <
            ChannelBitSizes,
            std::integral_constant<int, 0>,
            mp11::mp_plus
        >::value;

    using bitfield_t = typename detail::min_fast_uint<bit_size + 7>::type;
    using bit_alignedref_t = bit_aligned_pixel_reference<bitfield_t, ChannelBitSizes, Layout, true> const;

public:
    using type = image<bit_alignedref_t,false,Alloc>;
};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a single-channel bit-aligned image given the bit size of its channel and its layout
template <unsigned Size1, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct bit_aligned_image1_type : bit_aligned_image_type<mp11::mp_list_c<unsigned, Size1>, Layout, Alloc> {};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a two channel bit-aligned image given the bit size of its channels and its layout
template <unsigned Size1, unsigned Size2, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct bit_aligned_image2_type : bit_aligned_image_type<mp11::mp_list_c<unsigned, Size1, Size2>, Layout, Alloc> {};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a three channel bit-aligned image given the bit size of its channels and its layout
template <unsigned Size1, unsigned Size2, unsigned Size3, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct bit_aligned_image3_type : bit_aligned_image_type<mp11::mp_list_c<unsigned, Size1, Size2, Size3>, Layout, Alloc> {};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a four channel bit-aligned image given the bit size of its channels and its layout
template <unsigned Size1, unsigned Size2, unsigned Size3, unsigned Size4, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct bit_aligned_image4_type : bit_aligned_image_type<mp11::mp_list_c<unsigned, Size1, Size2, Size3, Size4>, Layout, Alloc> {};

/// \ingroup TypeFactoryPacked
/// \brief Returns the type of a five channel bit-aligned image given the bit size of its channels and its layout
template <unsigned Size1, unsigned Size2, unsigned Size3, unsigned Size4, unsigned Size5, typename Layout, typename Alloc = std::allocator<unsigned char>>
struct bit_aligned_image5_type : bit_aligned_image_type<mp11::mp_list_c<unsigned, Size1, Size2, Size3, Size4, Size5>, Layout, Alloc> {};


/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous pixel given the channel type and layout
template <typename Channel, typename Layout>
struct pixel_value_type
{
    // by default use gil::pixel. Specializations are provided for
    using type = pixel<Channel, Layout>;
};

// Specializations for packed channels
template <typename BitField, int NumBits, bool IsMutable, typename Layout>
struct pixel_value_type<packed_dynamic_channel_reference<BitField, NumBits, IsMutable>, Layout>
    : packed_pixel_type<BitField, mp11::mp_list_c<unsigned, NumBits>, Layout>
{};

template <typename BitField, int NumBits, bool IsMutable, typename Layout>
struct pixel_value_type<packed_dynamic_channel_reference<BitField, NumBits, IsMutable> const, Layout>
    : packed_pixel_type<BitField, mp11::mp_list_c<unsigned, NumBits>, Layout>
{};

template <typename BitField, int FirstBit, int NumBits, bool IsMutable, typename Layout>
struct pixel_value_type<packed_channel_reference<BitField, FirstBit, NumBits, IsMutable>, Layout>
    : packed_pixel_type<BitField, mp11::mp_list_c<unsigned, NumBits>, Layout>
{};

template <typename BitField, int FirstBit, int NumBits, bool IsMutable, typename Layout>
struct pixel_value_type<packed_channel_reference<BitField, FirstBit, NumBits, IsMutable> const, Layout>
    : packed_pixel_type<BitField, mp11::mp_list_c<unsigned, NumBits>, Layout>
{};

template <int NumBits, typename Layout>
struct pixel_value_type<packed_channel_value<NumBits>, Layout>
    : packed_pixel_type<typename detail::min_fast_uint<NumBits>::type, mp11::mp_list_c<unsigned, NumBits>, Layout>
{};

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous locator given the channel type, layout, whether it operates on planar data and whether it has a step horizontally
template <typename T, typename L, bool IsPlanar = false, bool IsStepX = false, bool IsMutable = true>
struct locator_type
{
    using type = typename type_from_x_iterator
        <
            typename iterator_type<T, L, IsPlanar, IsStepX, IsMutable>::type
        >::xy_locator_type;
};

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous view given the channel type, layout, whether it operates on planar data and whether it has a step horizontally
template <typename T, typename L, bool IsPlanar = false, bool IsStepX = false, bool IsMutable = true>
struct view_type
{
    using type = typename type_from_x_iterator
        <
            typename iterator_type<T, L, IsPlanar, IsStepX, IsMutable>::type
        >::view_t;
};

/// \ingroup TypeFactoryFromElements
/// \brief Returns the type of a homogeneous image given the channel type, layout, and whether it operates on planar data
template <typename T, typename L, bool IsPlanar = false, typename Alloc = std::allocator<unsigned char>>
struct image_type
{
    using type = image<pixel<T, L>, IsPlanar, Alloc>;
};

/// \ingroup TypeFactoryFromPixel
/// \brief Returns the type of a view the pixel type, whether it operates on planar data and whether it has a step horizontally
template <typename Pixel, bool IsPlanar=false, bool IsStepX=false, bool IsMutable=true>
struct view_type_from_pixel {
    using type = typename type_from_x_iterator<typename iterator_type_from_pixel<Pixel,IsPlanar,IsStepX,IsMutable>::type>::view_t;
};


/// \brief Constructs a pixel reference type from a source pixel reference type by changing some of the properties.
/// \ingroup TypeFactoryDerived
///  Use use_default for the properties of the source view that you want to keep
template
<
        typename Ref,
        typename T = use_default,
        typename L = use_default,
        typename IsPlanar = use_default,
        typename IsMutable = use_default>
class derived_pixel_reference_type
{
    using pixel_t = typename std::remove_reference<Ref>::type;

    using channel_t = typename mp11::mp_if
        <
            std::is_same<T, use_default>,
            typename channel_type<pixel_t>::type,
            T
        >::type;

    using layout_t = typename  mp11::mp_if
        <
            std::is_same<L, use_default>,
            layout
            <
                typename color_space_type<pixel_t>::type,
                typename channel_mapping_type<pixel_t>::type
            >,
            L
        >::type;

    static bool const mut = mp11::mp_if
        <
            std::is_same<IsMutable, use_default>,
            pixel_reference_is_mutable<Ref>,
            IsMutable
        >::value;

    static bool const planar = mp11::mp_if
        <
            std::is_same<IsPlanar, use_default>,
            is_planar<pixel_t>,
            IsPlanar
        >::value;

public:
    using type = typename pixel_reference_type<channel_t, layout_t, planar, mut>::type;
};

/// \brief Constructs a pixel iterator type from a source pixel iterator type by changing some of the properties.
/// \ingroup TypeFactoryDerived
///  Use use_default for the properties of the source view that you want to keep
template
<
    typename Iterator,
    typename T = use_default,
    typename L = use_default,
    typename IsPlanar = use_default,
    typename IsStep = use_default,
    typename IsMutable = use_default
>
class derived_iterator_type
{
    using channel_t = typename mp11::mp_if
        <
            std::is_same<T, use_default>,
            typename channel_type<Iterator>::type,
            T
        >::type;

    using layout_t = typename mp11::mp_if
        <
            std::is_same<L, use_default>,
            layout
            <
                typename color_space_type<Iterator>::type,
                typename channel_mapping_type<Iterator>::type
            >,
            L
        >::type;

    static const bool mut = mp11::mp_if
        <
            std::is_same<IsMutable, use_default>,
            iterator_is_mutable<Iterator>,
            IsMutable
        >::value;

    static bool const planar = mp11::mp_if
        <
            std::is_same<IsPlanar, use_default>,
            is_planar<Iterator>,
            IsPlanar
        >::value;

    static bool const step = mp11::mp_if
        <
            std::is_same<IsStep, use_default>,
            iterator_is_step<Iterator>,
            IsStep
        >::type::value;

public:
    using type = typename iterator_type<channel_t, layout_t, planar, step, mut>::type;
};

/// \brief Constructs an image view type from a source view type by changing some of the properties.
/// \ingroup TypeFactoryDerived
///  Use use_default for the properties of the source view that you want to keep
template <typename View, typename T = use_default, typename L = use_default, typename IsPlanar = use_default, typename StepX = use_default, typename IsMutable = use_default>
class derived_view_type
{
    using channel_t = typename mp11::mp_if
        <
            std::is_same<T, use_default>,
            typename channel_type<View>::type,
            T
        >;

    using layout_t = typename mp11::mp_if
        <
            std::is_same<L, use_default>,
            layout
            <
                typename color_space_type<View>::type,
                typename channel_mapping_type<View>::type
            >,
            L
        >;

    static bool const mut = mp11::mp_if
        <
            std::is_same<IsMutable, use_default>,
            view_is_mutable<View>,
            IsMutable
        >::value;

    static bool const planar = mp11::mp_if
        <
            std::is_same<IsPlanar, use_default>,
            is_planar<View>,
            IsPlanar
        >::value;

    static bool const step = mp11::mp_if
        <
            std::is_same<StepX, use_default>,
            view_is_step_in_x<View>,
            StepX
        >::value;

public:
    using type = typename view_type<channel_t, layout_t, planar, step, mut>::type;
};

/// \brief Constructs a homogeneous image type from a source image type by changing some of the properties.
/// \ingroup TypeFactoryDerived
///  Use use_default for the properties of the source image that you want to keep
template <typename Image, typename T = use_default, typename L = use_default, typename IsPlanar = use_default>
class derived_image_type
{
    using channel_t = typename mp11::mp_if
        <
            std::is_same<T, use_default>,
            typename channel_type<Image>::type,
            T
        >::type;

    using layout_t = typename mp11::mp_if
        <
            std::is_same<L, use_default>,
            layout
            <
                typename color_space_type<Image>::type,
                typename channel_mapping_type<Image>::type>,
                L
            >::type;

    static bool const planar = mp11::mp_if
        <
            std::is_same<IsPlanar, use_default>,
            is_planar<Image>,
            IsPlanar
        >::value;

public:
    using type = typename image_type<channel_t, layout_t, planar>::type;
};

}}  // namespace boost::gil

#endif

/* metafunctions.hpp
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
*/