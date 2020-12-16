//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_DETAIL_CONVERT_HPP_INCLUDED
#define BOOST_NOWIDE_DETAIL_CONVERT_HPP_INCLUDED

#include <boost/nowide/detail/utf.hpp>
#include <boost/nowide/replacement.hpp>
#include <iterator>
#include <string>

namespace boost {
namespace nowide {
    /// \cond INTERNAL
    namespace detail {
        ///
        /// Convert a buffer of UTF sequences in the range [source_begin, source_end)
        /// from \tparam CharIn to \tparam CharOut to the output \a buffer of size \a buffer_size.
        ///
        /// \return original buffer containing the NULL terminated string or NULL
        ///
        /// If there is not enough room in the buffer NULL is returned, and the content of the buffer is undefined.
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        ///
        template<typename CharOut, typename CharIn>
        CharOut*
        convert_buffer(CharOut* buffer, size_t buffer_size, const CharIn* source_begin, const CharIn* source_end)
        {
            CharOut* rv = buffer;
            if(buffer_size == 0)
                return 0;
            buffer_size--;
            while(source_begin != source_end)
            {
                using namespace detail::utf;
                code_point c = utf_traits<CharIn>::template decode(source_begin, source_end);
                if(c == illegal || c == incomplete)
                {
                    c = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                size_t width = utf_traits<CharOut>::width(c);
                if(buffer_size < width)
                {
                    rv = NULL;
                    break;
                }
                buffer = utf_traits<CharOut>::template encode(c, buffer);
                buffer_size -= width;
            }
            *buffer++ = 0;
            return rv;
        }

        ///
        /// Convert the UTF sequences in range [begin, end) from \tparam CharIn to \tparam CharOut
        /// and return it as a string
        ///
        /// Any illegal sequences are replaced with the replacement character, see #BOOST_NOWIDE_REPLACEMENT_CHARACTER
        ///
        template<typename CharOut, typename CharIn>
        std::basic_string<CharOut> convert_string(const CharIn* begin, const CharIn* end)
        {
            std::basic_string<CharOut> result;
            result.reserve(end - begin);
            typedef std::back_insert_iterator<std::basic_string<CharOut> > inserter_type;
            inserter_type inserter(result);
            using namespace detail::utf;
            code_point c;
            while(begin != end)
            {
                c = utf_traits<CharIn>::template decode(begin, end);
                if(c == illegal || c == incomplete)
                {
                    c = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                utf_traits<CharOut>::template encode(c, inserter);
            }
            return result;
        }

        /// Return the length of the given string.
        /// That is the number of characters until the first NULL character
        /// Equivalent to `std::strlen(s)` but can handle wide-strings
        template<typename Char>
        size_t strlen(const Char* s)
        {
            const Char* end = s;
            while(*end)
                end++;
            return end - s;
        }

    } // namespace detail
      /// \endcond
} // namespace nowide
} // namespace boost

#endif

/* convert.hpp
Ooy2kDVntr2BVx5nVbaJ7Mz+zHK3D/rFYNW/6fECc5fsKLOxv+SZDatiExlghns5yHIwu9t5Wz30C1kuZv2df1zHuBtsaPNY+d3jqjS2MMP9KGSxzHI8u94d/WIwf1n5Xk1RzSYaMPscMvgqxp3MBjN8l40sWO4+sq+ZeaawaxBkezXz0vK39v1HYr2tbhNrmfVI2+Q1yqxhE11N0rYUGIdxcNeyCWuItB+nX5Xf+q5DfcbinpYsZkZ+dbVjTM1KlXx3Auu0whIVJuoFt2iyqpotNPz+4GFxC4zPTZBFaDbf+Hwj2WZmrc2f5iOuvk0UY/Zh+GjMQfF98DLNZDxuXo+62NbFKuJcCotXmFthHoV5FeZTmF9hiQoLKCxJYSKWzvFghnM8MhvM8NygIs6liHMr4ryKOL8iLqCIEw0U+TVQ5KeIcyni3Io4ryLOr4gLKOJEnCK/OEV+PM5wX6xLUaZbUaaXLCezJqsvVMPcJcsGMzyr1zC4RSvMpTCPwvwKS1KYs1Fwi1WYW2E+sswww7N6CjM3Dm4xCotXmFdhiQoTTYJbtMJcCvMozE8Wq9k8Wnaed/oC6mtqE52ZdSk1MwxxZFWYjS+dfhLGtplNdGeWNUX/LRgjMhezFRlLTEV9zem41STtYpmSnZFDCxx/khmOP8nyh/xrc+n/tKMCeTFGrei8WEjL795fH2NksFVNrslve5A9Y3ZrSLdhGKM2NjE2pbRUVktt1NeZjmnDpVX5dXsm5NDTJloyOzH5+BfM+f42sd0kbciJ3mMw5wdq1540e7nthgvjQLaK2YffTxZHfoPo2I3ZrEaNbyKObDizv8VSef/EYJuIYxbRu4j8viEZyjQ8m5REtoTZb1HF5PWJIXo79tXQA+iXoTYxNJTFuWbEoUy3dtyqWdMGi4ejnSNtoo5J2tF6FWpijH62iecsbvaopejP6F/oeh1Mf73OQ9aSWY1sqy5hOzHaJrax+h7+vjUVthNjbcLN7K6Yin5x/obzMTLD9SWySJjhHk9FnFsR51XE+RVxAUWcGEfHPTD9+aaZLFhcNFmw+mIVFk+WEab/HdajiPOROTSbQ8vaf0cPw9wl62WSVnNq9jboswk2UZrFeQNvRmEOkjVmcc9rZ8mKuEk2cY3FfXc9nw99PVlva4qWy4i+9tB2kJnp1L5VGPcpdB2M2eRD91Kir6faxAlmj/buvA6bZhPrWDsrvXn5J8Zhhk1UY3ELj15+hv4k68IsXeEbVzB3Z9pEcVbm9N2D/0Bfz9LWFc1+TFOpJeqbbRO5mYkmvf3Ij2wDszfjrh7B+vC7Tcxi5n6dJN93P4fOgZjNGL9ajhFZhxBpuU6NSgubb6M/pFX/tWx1eY8S5hKZYX4qLJ7MAjNcA1TE+RSWSBYBM1wDVMQJb/A4szd4XDRZPs1+p2X5uANtkR9ZZpjh2IasNzNzwsQKKHMRHbcyu77wzheMO9lebYxmJ5dT7OcVyH2pTZQxSauzavQgxC2n7a6QFlU/PAPGaIVN3GRxX9Wb+hP6+g/67ZNZoZ0Hx6PM1TaxlbVlX8MJct+/ziaWh8NoPV40FuOwhdoppN0etLUwck8Ibm6yZ8zc3a/NRDu30lyCGX7vIIuEGd4/SBYB04+72BY8zkkWrL4YhbnIgtUXr4jzKNriU1giWVXNZhmuo0Rvt+HZsuSOLDJgwUPkvoOOpZhNSpO7JfqMLItJ2oEca6cgv11afpoNq1O0A/Ij68ys5Y5vSqC+3fQ7F7P6pUf+gXEnKxEmrao1JAXy228TPUOk1SkeOQHz7JBNpGft3NelcBaM0RGb8Gj1zaBlo7aTMJfEn3QszGxkxT2lEEfWOUxai6Xr/kQ=
*/