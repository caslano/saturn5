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
c02JZsbhBf2RWj1LKe4fg6ykZiGpglKSjpMjtuF01NAQmSiIArFzVqpFrKjFhz0w9zLfgtEES1pqGpzSuLp8lGZ+UtBdK+4UFaG1APg3FG059n72UPqDMNo11dBE0y/SQJ6mOZ9VCOuwoy9y8MDBYJcpzE23YFpIjr4YQmpFfxf4hxwIceZcDM4aoYR8h57JZHohKPem+tnth9w/8Ic5O3HPlTY3K4JfmXhK1RQjD2H0+dNV5/B//UN0P4XJNKL9Zz+1F53IxJcaYVZKT+sH+s1P4rvqe8xfN4x66VqpRxPxqDFLh+eZrwLJmCysJadPx5HAM7HzNVr8Ky1+XNjWCUZ91AglEZ6fmJWHLtD/40uTM8PBbshJywkg5YuTkiA5gl1KLrYOpeQ55xWUA3M2NZTIQginMsn8yhIkeLg/4sBbTizFDdXqHPsykkAtSMwsB5c33QTxcgWlmEhmMJNL4/Z/3JRH+hPjN8Qvl723HwX6Dr0aiLTOLwrMbI8XTsRKRvlCWRFoNnAiCWg6gkAQb9irjN6IR6on3zh6yoFvkSN3FvA1Tn7rGhLv4XxmzSldb1jEzG0lZSEoiDWOm8gLdVX6O5BQam/1Fnew0ajjBcxvkRQLY5HlQJwFEyOXNa8HOFA+fd5o1sjJqkbHO69a86cwZY/To7WYVUo9B2NlCXab5/2fKNQhew00fSr5eQrALTnIWbjkzDmhg4fb26WISBWq5Zx3sNzQKqIc7ABAyimAq5euEkKerFnpPDq8QoC2/32ltE1/nOcfnnQ4wCtJycYtLqHFuX5jGZDs5kgb6sgMRYu5pSZaD4/4GLjcByX+VkWPnwxaQm7jFSRGHdBygM/D9Nkwrp71Lkb3UtI440G9WWc8i0SQ9llc+HH8OK/0M35Kgah4Rhflhp3Hlc/dgCnnNhp/ivGo3swysvVmG96e8jidWtGixIgA1ZXPtTsoVL70BNjX7uijWjv1uyTvtNchGulyLq5XUY0caqhH80R+/+it/cQgQNj9hLnnjQsyy9DXsC46x24kghAQsVHA16GOTeS+VPVTtMwjyfyIZMShjX7GfB3lyCiL5MisejSmCSe7SrG350egZw5DDboTKtOUAxFpVLL2uNlw4BvRfskNZBLZ3LeYx7vt8rJIsITFy1JSeTDQjpsyvOpl8kYXZnfBVclcy6xwLP1TOUeh14Lv0c4jtax9YhWaDvjgd00EyiNPO0krJdEvtLwvtJaGpvqFOnyhHnzcZ6OXIK3HzWhw9MUQYlhWBGCdYrxbbKJfkGpKukjWFQva6Ly5qkaSMMRkcDMGV2+Xn5V6bVhZhFHP24EG7V97Cb4NMMk0hhb4QBE8fhefkFvUd+uxnsI5dSBKRGrBdeGbSU6StXr5hbwnIYXsOEde4Rpe41OBDv4uncA+Y8zOhuL3En7j8JuE3yf4fYXf9/j9gt8C/Jbjtx6/HfgdwK8Av7P4XTF/YQWBjgr4NcAvAb+H8BuA31D8svF7Hb/g49j3jF8sfrfj9xN+S/HbhF9XyNIPvyfxa4lfJH5p+CXil4lfyfl8VXMVLjrQnMAHxOPIm+ERrpA1j7DYZz6Dj8PcyNmsN9f9xtMkIbdlIKrUwImjaUT28kutUvuHfPq4bD/vDp58NK6mbR+rAj8tp/UPfsVYwQXfkOFI1bMIFWOhnCbBxQYmyfGj7kYlxXqglNeXd0hASXlrl5D326d98j7wWAl5/xgk8s74E3mri7zL+v535M1zlJT36b52eYuf8sn72cAS8iapvJf+RN4nrlDeqv+pvNL0efc/lxA61TWkqivkxz4i+HNewc/B8FEMlmAo2gaZMMW+DWK/9piIfSeoXrH1wAvwU+w=
*/