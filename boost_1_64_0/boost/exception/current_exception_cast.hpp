//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E83C166200811DE885E826156D89593
#define BOOST_EXCEPTION_7E83C166200811DE885E826156D89593

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class E>
    inline
    E *
    current_exception_cast()
        {
        try
            {
            throw;
            }
        catch(
        E & e )
            {
            return &e;
            }
        catch(
        ...)
            {
            return 0;
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* current_exception_cast.hpp
dcIeAWeey3ahesN+G1mYS/E4kR/V7AVD1RalC/KiAPahPE5uCUFiwxh8pM1EvvDOT7tIRq2VFv9ykw6Pl6Ek7iWjAdah2ZJt2oZWEcFcjI5UmJPxocP4FIhALK/Qa+xFdHtLsUqPlTssNgiRqZI9qleJbP7AwebEaDIxGr8RGJiIp2T5eGgE71zIWTy26Y0iC8yQ+UtRmMqsEMQ7Zx8uquz5cjXI9iGmb7qLpvEkpHOBExKGZqahFBh/kIfEEoIP7mAeBPhKZ842of+ln2aP9m1nezQSERjecajSGKLbiuiC/VQzNJjSYewBQFboBzJboTUBefev1ffd+OGS7fAAvhGHyyDnmt01BDbhEjrkOQm3rFbZtGnTL3zksAahquTx4o9ox8uMRMHRxRUD+TuIxhikDFA9mBTgY1M+7aoiety3OzSuC3YLvkgzNumj1x46ktLGZ/U2Hp+iD2x8Mtg/t6n10OsPJP0l2W6ysBCue7qcpL+UP0lXhR2ELeL4oWLAEEYoZlcC3fmhWbcUNV6oK6GrWbRJOVYtv2fQXtbpUwTZAVjg6ulNnI5i0i2kKS3dznm1CBZxQAn88eRHSfLSjoJf/yQbZaqJfHZRXcOhrox9gE9zdVhCq85H1XXyt5pi2/7OUp5v5nW62D/M3TNg/MPS7zfd06HoacOvk/5VIjA+09NkduBZnUpPAZoViJ4Cip4CfNJGpyd6o7qBnr7DB4vS7hhV00d50uRp6l+bod0KyG5JOt0y1NIRCEkqkjQJ7KI6yHClwERcknpCscdfSQ63oq0AQzcDlOtDp0WRLKtjR7BEMUfeZP8neV2Nn7vBpjIVqFO4WJIGRitd/T4STm/V7iPhCjdoFQKF8nU1+rF+U6MIOBFVv4kWn2/O4vOJn0vs86XLThd70jgf/sisy/teX8zbovgnupX5JySUQ2Ied1IVz1ISm/RSFFj2tJp2vUHTbmXZZ1JZOVFXbgV9s6B9829IwNgA3PKjtD9AGi1+WmIsS0U1sQd0ELeR/faqZRsNPOTnJnI/83lSR9J4dUcsl2vp+/1Lb2/Z+EsaTzQb0ACGeQCj+gAy+8oB9CNMWy5MMOC+iZWgeh6/umrTvYqbfwTfpjR4TQ5UmBMjycSIoJqkTPER+0qJIY4E0H0pPlUbO2nQENcbbz7jZObhn7Ixop7mVpzXye4SY+9x0arYL14qsjGIrwQhL/y1ADMvoz5o60J6feqeX/D8t8VCn2pACmjPRp+acnDKUXyafaBrYntelJqYmVb60szk11m41FN9i188pNrYZ17MqI1dv33AaGMZ/X/uVvTo+qVJH2N6vD0bfaz6IJSrtbcnlau4P+8DUunctx8Cle6/7B0NeFTF8V1yl1ySC3doAgF/uNqgVwF7CNqAsV402KNQPS3S9M9GpRik2iiJpq0gGNTQIy22asFai621/rWN9u/AVhNACMVWROtP1Tb0R9712gq2VWyr15md3bl9795dLgQtWB5fuPf2Z3Z2dnZ2dnZ2l/QNi5qiaXl5tLuXB2j448wU/OxAfrXOWQQL52d/583MrQ6qXZ2IYd0qnEO1CzupdhHtQEuHzPpiEGUIkxvBbHc0eW4O/Y+xF5E0gEyy4SgWY3LglVqfR+ereuig0/mG3H+bhP/v/bz/u8emD1Ln9eXWB/eP+kfDUbkoIXn7MBTCP7yYrRBufVFqfSxhd+8v3W9P4u3R/QbR/+7N6H/UYPW59b/hqXu9q800aZDUWs1JPO72oFAAcc4nGt+m6937/P9G13NsyqfvFk2pHdsym45rCQsyWbzeY9AQLljok1uW/uPihmA5S7RN8A4nJPBVh9OKyihKjEHKoR/N8Lai0fA=
*/