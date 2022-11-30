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
dLnREyNKWuryVxO/f9nxDUlvsrJt2aKcMGMxKRhDh9crxRRjMKwPGpZ6ueooKhaqej07lF+0TP0oKvFEE8HDLwYqPUhgBFH2aYwOkYkxivK+HxHllWDC505JDpnBnGUYmW9YFkSZk3qFlLkF+87jghZQRoxdYcxe9gN/bOUyZSwP6c3R4UWN+LOd8zVfbzCJfTwFmmJ9i1XXHJYT/Q+E5tyioND33Es49Xv4ACghV2wgB0YuGTl3ZpyQS66KsCQdFLDq014RRYkrAQUrlahlDTBnWPmBj9IIWc6o5C2ataetFnCmqVTaOABRxwTlTq8Mrs8oz4h35UqVgnVuoSErAKKhwgYldCrJ8hK3wuU4lK41jxm+Ip6XV4+2nrw5+4FcF8ogDRco+rB0U5WgMExMWYOIcfeq0aqlUZHMK41impeZEltccF7hEollEY3+xkim+6HAUrKVmnO5YTznqKkJI28Byxay4doTK9YBF+IS8Vpeyr7k5LyUqcci00WttGkM0XFyF4VxpU4YPZYWFRlUdl7OiUM1r6qNCwzhxZH4zys5X75nWBbFYoiAVYb3uu+ghVXTp0GI+ETUIi2pb1hfuRu0zGtQtsyFcAg9GpDiD28zcwzbc2lniXRUiGGXzTTcWOGbdpomif4GZXwzy27/KJe8jBNXs3wKZ+PCw49cNm/Dw7GeVlMtY6XKmgbMNY6whfzdtA33QPXbL3rT2MD0J2qmJmeG7m6FwQuvqVqtAdiMVu8SmfXqPOV1p+MgHwcpApoZ8ve2hD812EHbvx+1xV3kZajUhV2jD20B/8dze7zvbXl/7PPbJ8O32Py+pnN7lu+aIvmaJ/aonciiPtonOep3XsIfZnErkN1RL26bDs/KsvPI0T0machMxsdVm9sK1NYLyZV3/1KJKgXP+CFtyB/fvaaA+Hd4HsenkO1XSEjCbxHJTojiY4JrYcmZRG6QXS+4FDGBQ4jxJxFqyViQbtS7jedmEmeTlnmhjCziKhDque6YfNtLCK4v26Af1x6KdM5FZQyv8KHAS869qEBv+x4hv6Z1p3U7dLh8iLSvLGrSoowtQpgdbXBAbYlJELUsd4gqcgrqpo4kDW9DG+Iz50Sc2Ra30RfpFD6zHJUBzfxdQC/3xN4vQEKmrdJjYs5/9H1XgCWviVOvAL7UZ/E1xteWqGRbJxfQ8y0tICxPukAbPXLr+kizQg59gOlAOo0hzInPdaazxiJN0SYWrIG90Bas+Y84GpP5WEBasPMhuCAsUifg33eoN3Rd5+VBSwCyAMvrifh3WAMMD6VFeM8Aftx35qs/4HrgPNRUwpoqx1hPfBL8GlUWsMtrVtVuD1LPIfJ9W1bEbjoZDAelPeMFT6/9g1BoC1BocNcdWPURrwq/LT7eG4NczacsAs4Arm57Ek+QUg4GHBXDq98kkiWXcOduxNbMma9A9cEAUdMnNMXo2FgRDwKqII+L2SSZ8UfWLJIt1sCyuQJOpLInhO8ssmjEmNLJqhJhcOJM6BMOXm1AEzWsz0oPplk0AovWHt7K5iZMqrJeikrPpiSp7kCqOPVitURPLU4Y+9Kjrs9J2S466ovWsQpydWgFMXqXIVuGOvJqCHG6A47rnyGH+PSTh9tUxbDGT5uUuiUJZA+SiO82xeqx9TITt20rIbt+d9J+ijd1XIW/BXDfquDf4CqfgE+/ouE/RC9iwQ8zjiZJqHwdky3jRty2iRwJcuCWdejcZ/hHjdWd5xx+4QFGsBQ/ujXN6sXdPHuEp+nIuEchUKu1RMXrBN9erE3wx0L/fYBt0E2FNb7EFa0xESbs1CERhTW6QeNPTijKZPh2Sl1M4Rpog7U+4pIWOj25pwATn2gigJghBQlWpV6vNCoxto8B4oDebaviXmCTpNSE+AiHAnk9oz+crciPH7/nP7CrD7YHzfWqOvm74ew6wt8fYvd4A4SAEixTg/QXsz0RhnbXAeuBt9cGd59INW6h3MAVGENP7K4auagRvLP3eANNRL0cKWbRlGlkVQs9RAPIJT/YqiR31qZ8CMNCNuMjQUapcUkE3Nc7RgwC5XoH5j8L9LU1Cn+uQiIK/+cRqRVi3YHQEHAc7MFHDpHHPkCO70OkPnlYJzcf8aSVqNcUEGt/aQD6jTMf/x4x725ZtgZhGqx4abX8sTbgBIzjCTXRI+GHSt02r+fFDj3Rdq7LEnvH16MdUBxJZp2wlRtSDDqRIejkzC8a/V/Y0aIGJndOMitxLOurueRi9See5PF16N4CPQdbPkWbddfWjUqADgm2kclPLHTiVuSRp1cbzMQUtCnru3OBTujkqWkHP2YEiWrFHHDiltxmUc5tq4Dcja3MzeWctJM+UUW3LT5yR1NSxtZZXbvAqv6UgolJLgLi0JWgB0wTMCJ0Zg6E/viHI1DPCYQgI82t9DkzqD9j3b6JhxE4pRtolG6aaBTuv2VDn3kxLmwC9/cGgA6mcMskuNQokQ5Yvqd0wDyw8etn0eZpwlh8KtBq2B/JlI09HyKyY/kIhkwRmmXvI6v/eOUJoVx+WX/B714Aw45578oB489OUb/lT3B3ORR/D//zKYo0vi6PMr7eYMqbkV8Jxqh1ShicjQP+TMwb/CF1w8hLFZolWMXnBm94mcUhmXUn6mPxaoGiDP7vbVOiDnUQ6z6LYkef7ORw2CclIx7hcd/ILygDHmv4gtklwQin7wcnkR354YJr0hpVC4zpvRoY01eaZqnpjurt/j0o9KQplCCLHoHKONPvfalbdLzIZUQIsKdPfT7i1R3O5DpT+PYWvRp9/ZvF6zekPmdnl1Jl8fN4MCvQ6Bu88UeDTeHfL1ijWwzW+Aa9EYF6H41SH726wehPzLL9uzPuhTli2CiTl79krye7ZY/KI4a/LA21umjdJsiUjk5TyEWHjJx0zNnt266LDnisWMcPt2THM7XJpwbx0Vv0jwLMYTby0EVHzsMU6uJJo9s6Hd+czuyRNvAPF3TZLhr2BjcjWK/xkZshJekTitlDkA1x0JWeHMhEMAEkdcqH3GqyjcAOsXAdtHimYYd4uN6Bk2WaFhBbtDsi2/fGZREqFXi9UVURob5dyvED8R2+Qqo0ZLX1HFl/3ivaT/4az767Fy/hl1Td8WAgyOpRXj9UAlUP+ozKKM5Mpwt1jxf0xEL1BOyCTEkysgYyJlKGVLWUgW4rTyCrpg9QUXTBGouhEspl5QCwBvIrdn+LClXFATXkXZvCSOSUoiiyW1VX1HMD1PM3qvI9zV4V/9hH/P4+/Bw6On3uYN33SLHam6BkJWjFLnrIkwrQqbx1CAsepPvJRhODp8CN3JmBf8UzzosPsKa+AV9Mo0uvQnwJSI4J2XM67V3Rtykwt1+vTeBQbup1o7I+ySvx+qMk5l1+noyZrfzPpjyYjoV8rpU82ushCmX6+h3gnBTbFjjqRhyUKs+mIv7SR4Oc/PnY6ObVMJjkqKp5Ri4NuPei//33fwpRiHWJ3xl8w9PGZFROeF11yI/JJ4w9GNzx5wPlnjKu4HPGLt8i/+Z4Stt0RbzUEdfY0s+3tzti5L91Rk93O2DcJbtzUev8I9Tz+i4qen/vWZYugQ8Udskf1mn1+BFv+9jVl/3vO1W7yaLXducCd90I3y3Z8NKin+6NPBkLdZK/hj8+GP9pFi/xzoyuUywsw+ROPXwPd8dn3BKd6I74aKNM7Y6sdENKF2M3aS79O5969oC9vFeUT/aLmyL71nltPqrTCP3XKzOegwOqK7KZhuhxkR7xy7ONZ4/QqspG8aW/5xTofXv+qyEv+lQSLBcBplvsKr0PZ0QTKv6+uPdsD57O5eD5YGn3pRlSeQzr8qN6j+KAnRYw+Ev9X1+Z6af4yS8fRZ0Wxe3QhWpYdy3V5AOV5TVRFhdjkmaC1X42X5SotTmDLMgSU9LGMeZeFavaZm9/y7Zl4HONnlQAKoBfa0yyOvXwsyEvQmgVZ1OkS1Qc2RrBOmoLo734g6EXO+qEQNZWmIl9lkyBRtZWRDG07I2Ikz41hwmh5m72C3eSujdxcUPRBGFxYPWMiRxwfj37qZupAJpSZK90yUQxduVS0EUKve2tSLP3CU5oSXcryOUHzn99Jbgf2sQkD29OQfwQPqx3YXEeVQyGcJdlKfwdHNgHutmCpz3h87Jak+e74sbVMvGF/yLwtu96JpwWxlUlO0zHc55UNW4S9zDA41qkKcTvvAcDd8Xhvlo57zavqiwiKz1E7AZuD0mNeFilz1jHpLhM2cCMH1if5jBIThdIckBH9ZOvHySyVADrX7iSAAMs/NMCJV6K3ZETcQSTOXKJRBQFOJLcf1PHuj5Z7f6p1zvWRqd7saIAoQn0f94v+lhYKi4Xkgtk6iPPr7/9UudGFjg6MwYV9V9Hp49ph+5tlmIIkUaXHDwKIj7DFniQ6tngyxsK1f3qob+9Ko3CJgnmQj3Ue0zoWYak5UJNIUJr0BnwSb2fv91WzAcR9qsD/t4e/NarZ/L+avem5C7XVSGzPZlAfRrJhwp+GCPCLOoNemwaSerVICwkrwc7eJF+7Cgv/NwG2zCOG3FNFiGyEOVIad6S5m/CdfpFb46B/8tu4ouiAgfOgj+7Fo27L0QWkvmXuu6PzzZn/jD8H7iFVxRC1SviAXD0j/EXWZTLlI9G0/B7/QSdVLfYG0XWufRdNHDf8e/I3Fr46G77S13Rdd2D4mjs4YAFP8Y7rdVavJT9qt7xTpSTOLAdYPdPxctbQ/BvnBNTT+rlUhe0YUQvachnntKHuKtQocYOk/0qnOMBaxQ9/suVdn0kcLbq9bH7MrN++EMBARhCaZBDTKFPuFwusAa0gW5u4wLla+QYFs6zAQjBxy3EEZhk5jRrBDM43yrBdZzJ8161JCo0J/uYpJ+RLw4YXPkrXbMiuK0p/MkZ+ZNB3H8HeNP78Wh13r8G3tLr/hQvaXzxyTYiZBmVTpBLoAiR7gJJ9xSo8YNojVCcoRRUTygEfrvIErehHP+MWqqlWqmmxzkMiAI6sM2Nf/bfvbhIXl3V23nwAuyAnjDyzaZ2ixV39hQwj/2XxDo6BZL6nABbsQQeAEk5F8QkCruUxfEnxjaT4+9joDYoiuDRJWo+0TA0ByzgTFVgkeClZD0rLRqRJrq2OcRMYxRTaBZgGLS+gA2PpDBVA48g5JPmJD4mSHgFDvrwP/mhbVyeP+HCyxTJratBesWUPJsAd3r6R1eVjUPMOyOlqXsQWjUWJMEFEoCAeEnLgQeIU/LhQPBCAMbM/DxCXXCRvIuHZ9XfZocJvPC6J/utKah16i1QR+3ACIjh83/KYzxJTyYaym4lkm8Ia7rHseb93NNbD0U2sIhX3t1gXmD6Hz81sLWHaKwcWOjLACaAjmY0yDStSlYUG3sCZPglCOgRxmtzkjOcI6uKTJkXDwD+YU3BQomEI92XI8XjRYWOWuc/5Vpjo0jxgzI8EwIpF5TrNJRvwYm+A7XD9vdJWKkHQtA4AKghGQizFKIB+GEPTTSn81RGpKW8YQhs8ABJxQtyl0Cou7e1KY+StZonw6pgKMwBmcaJwX8PAxdh3KECIAP+wwieXNXohHX5D6Zi8AteAVOAr9tg/c7fZAAPcPyXHKhRbCrYaEqodhyHjYJlQSlv80R4TvDBmuXycevaRtp8TqXqKL/jyqxtJ29jZw0TUuZDf8CAG8OmEIYntHuhDYf1gPjvt2pKjBSqtZury6FWZaLqcetXTjgT3H9mJsAU6PCGjEFh4/AGnweIABwgzbRIAHqywMS7HSSa8mktG0nyaM2dwzHU9v8DKPXojR1dLZU9ZOFEfrHPtfk9MVwFfAt+n+6kOxtUKzGv4iz8BumEnzftQzibfIeq8QOPf7izuPFZVdnurLd8flcyq8qx0KPeelSBeQUlsAW1nHtf/BdmIN9xKlsh6P96xVHzPpeM1UyOQXI09JsTzjceZNU9lFzMuFKeR636kddxppngwxcf+8zzyNuq1J9NI9SsNI4vkP+TilANCgiNXBIURiba6OdTYFTuW6RzZnWXAYBXdNKQVvtqUDvah2fUPRQ8gj7r5TBifAUW7IIsYT9nqviBz6Px6HddkAHEGnACpMWVbvmNTfSqzpsh3DYQLEqv92SQ/OOMBxV+/0pBEztApEpzbfzXhQaj/OAmZ/YgDyyhKlD0n44INMR6oCbgBPGKEr31Q3NSBZseFniBYsBaYBbwAjOuZwNO7nxAg14OIinLGcCCixBJFxSrwYRdw28ibJ1CHLS1UNYJ0q7qT6cr5JCe84ZCvdRSbsVZ7mwRkomSbBkR7BR5DO6a5PiOt+XJm7kpLg+sd7sQP8qFCp6xe0ezXvt65qHaXQDzVALeYhNkR3OzuLLjFpneBBKDUBAT/PKNk/gOijKqcgEkQEp3JMrBKbNQJZ084DVw4+QBGT2G8HkXPsobed5GFNXFWO5lS125EmHzJNuR3mZJqhu2NKWSXOT8l8OaiyJsEKtziR/Xniha4ULhSh0vUGiw5OpwJ/6YOGAOKoSA/BlDF+sIpeXm9gLL4hDFTnA5crS7z+f12zsYkTtgZ+KJc5OEUHxlgJow4y+cbFgoMrBNi/nHZF41iN14jUp57y0O1DmMenDq/y2zDxCB0hBRRn8PokhlUYXMWzfcSWAYK/IMS1Xx5RonNiTKciEmKl3jA/ch762hUV6ejU81Nv3maIvDusSnuIiIUquIlMOLb5SrNrA7w8ZGvi7aAEkCk1AvnnD0xu8psuLZFiyLxG9n/IS1U6aJ4gNgKcrkNySyUSrtDsky7q0ClYBTUSB9q5hP8CrVaZSJAiVDx5QNT2hzbEgOnBPm8/iTl1s3mS6j59gtKr40IPnaowmGA+eAP6m1X+uEwGpmT8CEa2lsRMbXHzNGPy7RVHD3Apel7jV7sVknLeRkwOIV0rCgzucEyGXPiPVJk6Mh4iNOUsKyLaEBXegK5fcmzG1BSNZuYg+TyNlnAnHSNjA1gE0YvQcJgmB8sUbDlsPrWDYjBbcQDEsB7z0CZxKdhDlUD2YMfj+HDF/Ek+9JBa20arKJEz8D463sLWj9IJL9g7+jqEb5lscj/Qj/tNpfrG3ZaaZXwUHWgrQgyidOAZ0eKQLiWZxF8lal3XLvGEnyE1LNTCUlhyibQjFeA2+uya/xGBTzNgnPkq3eXIYy7bnnoBHEDLwhnNd1Xcpsi6kqmqAAcWAMoEwpq0OoNQMmeGS3o+1GvscXaAPGCi79ip8Pr/ooHRT1BmN5z8d8C5HdWLrgE6wu6rt7JxDFxQcMRAVZHRNUAA2iPqyhOaevPoY02FaNl97eQBGUAI4n+hGWnChux01ely84QMmM3GJXsiN3ypPowDnaSXJanlonOnaQ09OgP4ZK0KY7vmshMwxMoXbf0zzvb9oILGMHasGHQ3H2G88s1iFwmlCyI3Gil+pgHOelPR5MyKY/LiUuS3ZqSsSmP7bI8MhI0Y7R2Q2MauVnQBaGgS2PN3BMDrlXq9SH/+KkMDrGDADDI54fI86IP02rPcs4BYgEMpEA0d0ZTHsFEH6Ewxra9zAjYWrC41G+mDbMlwNtAX21ENG6kgcM1u4W7GpO6hL0bknpEuR+IXAPfrm2uwG73sHdgt0YEvuLjlz/ojnwduzmqqYO7Oa23WO7
*/