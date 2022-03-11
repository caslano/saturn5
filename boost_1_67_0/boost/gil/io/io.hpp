//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_IO_HPP
#define BOOST_GIL_IO_IO_HPP

/*!
 * \page iobackend Adding a new io backend
 * \section Overview of backend requirements
 * To add support for a new IO backend the following is required:
 *  - a format tag, to identify the image format, derived from boost::gil::format_tag
 *  - boolean meta function is_supported<PixelType,FormatTag> must be implemented for
 *    the new format tag
 *  - explicit specialisation of image_read_info<FormatTag> must be provided, containing
 *    runtime information available before/at reading the image
 *  - explicit specialisation of image_write_info<FormatTag> must be provided, containing
 *    runtime encoding parameters for writing an image
 *  - An image reader must be specialized:
 *    \code
 *      template<typename IODevice, typename ConversionPolicy>
 *      struct boost::gil::reader<IODevice,FormatTag,ConversionPolicy>
 *      {
 *        reader( IODevice & device )
 *        reader( IODevice & device, typename ConversionPolicy::color_converter_type const& cc )
 *        image_read_info<FormatTag> get_info();
 *        template<typename Image>
 *        void read_image( Image &, point_t const& top_left );
 *        template<typename View>
 *        void read_view( View &, point_t const& top_left );
 *      };
 *    \endcode
 *  - An image writer must be specialized:
 *    \code
 *      \template <typename IODevice>
 *      struct boost::gil::writer<IODevice,FormatTag>
 *      {
 *        writer( IODevice & device )
 *        template<typename View>
 *        void apply( View const&, point_t const& top_left );
 *        template<typename View>
 *        void apply( View const&, point_t const& top_left, image_write_info<FormatTag> const& );
 *      };
 *    \endcode
 *
 * Or instead of the items above implement overloads of read_view, read_and_convert_view, read_image,
 * read_and_convert_image, write_view and read_image_info.
 *
 * \section ConversionPolicy Interface of the ConversionPolicy
 * There are two different conversion policies in use, when reading images:
 * read_and_convert<ColorConverter> and read_and_no_convert. ColorConverter
 * can be a user defined color converter.
 *
 * \code
 * struct ConversionPolicy
 * {
 *    template<typename InputIterator,typename OutputIterator>
 *    void read( InputIterator in_begin, InputIterator in_end,
 *          OutputIterator out_end );
 * };
 * \endcode
 *
 * Methods like read_view and read_image are supposed to bail out with an
 * exception instead of converting the image
 *
 * \section IODevice Concept of IO Device
 * A Device is simply an object used to read and write data to and from a stream.
 * The IODevice was added as a template paramter to be able to replace the file_name
 * access functionality. This is only an interim solution, as soon as boost provides
 * a good IO library, interfaces/constraints provided by that library could be used.
 *
 * \code
 *  concept IODevice
 *  {
 *      void IODevice::read( unsigned char* data, int count );
 *      void IODevice::write( unsigned char* data, int count );
 *      void IODevice::seek(long count, int whence);
 *      void IODevice::flush();
 *  };
 * \endcode
 *
 * For the time being a boolean meta function must be specialized:
 * \code
 * namespace boost{namespace gil{namespace detail{
 *  template<typename Device>
 *  struct detail::is_input_device;
 * }}}
 * \endcode
 *
 */

#endif

/* io.hpp
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
*/