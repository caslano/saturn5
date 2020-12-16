//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNM Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , pnm_tag
                     >
{
public:

    using format_tag_t = pnm_tag;

public:

    writer_backend( const Device&                      io_dev
                  , const image_write_info< pnm_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

public:

    Device _io_dev;

    image_write_info< pnm_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
uJx4Ylw+IP/v0/abHhE5PCZyG3lf8lxCZhUl5IUk40M/NkyJydb05ahLEnLPUzE5fv+4HHRETN7YNSYnJmLyiyFxGb51XA6fhIyTVw3j9Bpjd8F9tDfFmCMbb9yXkF2qE/LwlLi0Hx+Xg0fGpOArCTl7Uly+9SWRHzUlpOLDmDxOPk0XJaTm9Zic8tu4LDooISu2icllV4n8cmFM7jg6IZ+jH5+mjw9eGJeVdQmZ+FRC2irjct1dMXl+BP32jbjUraAxtOVjxvEwxuTZFXFZhpwkV9DX3Qm5aklCTroEGTw4Lr8rpJ9aEjLokrhsURCT3Y6Ny6/K4/LjY8lvMLr9yYRsMigu1WMSMr0dm/XrhPS9LdJ7s8hXOlkvoVfnVyVkbmFCjvmiyDMvxuT2zri8hByveyImx16WkMadRQZtGZNd34nJEwfE5bJpcbn2o5jUP5mQkb+Nyaz5Cfnh3vTRSOwBaRvSVqSrDkbWGfOjfxeTI79GX7wYl8HggzoSsuNeyMUtCdmhOyaXL0F/0JGHjojLsbslZMpb2Az0a/17cdn+oLgcibwcv3tCxp6P7H4Qk2klcWmZQ13Qoatvj8vMnalbLC5foNteI//zTonJvYzj1DXY4d64HEgdHz4mLu90iXx9C+RvfUxKT43LN5GjCc/HZd68mPyOvdT1PQn5EXk/uTPPX478bJWQGZ/Fdt6ckGcfYYxXI1sTErIt43t9WVzmj4pL6qqY7ISdOItx2xmZOAV9mPwMcrJZTD5+OHi3Ly7fWx2XF1dhkwh2vP94QlaemJAPsF9D5sbl69T3a6TTSddNTcjub4jsW0N04cvsDX8/LrP/IDL01JhM+VZMNr+WfLAnrw6jjfDfS3qC9CzpRdI95ne7AuwYaSvSMlItaQnpeNKJpG+RziSdQ7qA9CvSr0kvkB4gvUQaMopySa3088RK9Pr0hDRcnpAPt4rL+8jvEefGZcZ3seu3YqP+GJO5ZyTkfmTtptW04Vdxue/4hPxmb2wzbRgzBh3dOyYv/CAhdxNU37SV/l6ckF/cG5efL2QszqM9bybka9jydT+NySsPJWRnbM73Dqe/b41L/KWEbH1WQrraRH6PjjZiF1fcEZObj4zJvDUJOfdC+pL8tl8fl2vIs3ArbD06/k3kfym6f2YvNvtS7GwBvJuht59LyPdp291BmoftoayFjPkPmuLMmdhx7EzyRZGPfo79Yow/szwhX90F7PvYvxKRtcjTh8czxpvGpespbPgmMTn3p8x774p8jBzsxDxzCDJdOD0uw25ISOtdxNOQ73EnM0ceSYyDuWePqZTzdIz6xbBrcfk2cvxrbNVa9Dtehx5h3x55AV3bkn58FX15JSEd7zE/nxGXY5jTFtwJdhqydn1CCh+My5od0Vf0+uxp2KnnmBfPRLeZq1o+h1zuIrITaSvSMNL18Hxm6xjKgf0/lvEvZc4aHpfPHhiTfbE5734JuaYvPvp6TE5tQTcfQI93iMn7v8embIct2ol6/iEux23PnHY7c8QPsH20pYT+/vYtcVn8KHm0M7/VYId44eviscjRZOZTbP2NF4schJ38BuM37OaYvEW/rGfuqKJex9En9Y3YoC3QL+zOVn3k+3pcLt8nLpPeZvxfQ66xhW/9QOSH19Nf2Pq2+TG5qScun/gEcyL24YMvxeQTu9Pn5LeAVEmqI11EuvdTCVkljPcNyPrzjBf/OAsbtdd9zB9/Jv8U+tkcl8nj43IFccOKurhcOoOxZs4743tgbHT8lrbP/31cpt4Tk4MfQV5viMsU6p+ahN06kPIJIq2m7a07UKdhcfnyyQmZyhx6ymlxeTOGDO2Dnq6ivGvRk150ifE9+rA=
*/