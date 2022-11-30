// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <algorithm>                               // min.
#include <boost/assert.hpp>
#include <memory>                                  // allocator.
#include <string>
#include <boost/config.hpp>                        // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/checked_operations.hpp>
#include <boost/iostreams/detail/ios.hpp>          // openmode, streamsize.
#include <boost/iostreams/read.hpp>                // check_eof 
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/write.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4244.

namespace boost { namespace iostreams {

//
// Template name: line_filter.
// Template parameters:
//      Ch - The character type.
//      Alloc - The allocator type.
// Description: Filter which processes data one line at a time.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class basic_line_filter {
private:
    typedef typename std::basic_string<Ch>::traits_type  string_traits;
public:
    typedef Ch                                           char_type;
    typedef char_traits<char_type>                       traits_type;
    typedef std::basic_string<
                Ch,
                string_traits,
                Alloc
            >                                            string_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };
protected:
    basic_line_filter(bool suppress_newlines = false) 
        : pos_(string_type::npos), 
          flags_(suppress_newlines ? f_suppress : 0) 
        { }
public:
    virtual ~basic_line_filter() { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(flags_ & f_write));
        flags_ |= f_read;

        // Handle unfinished business.
        std::streamsize result = 0;
        if (!cur_line_.empty() && (result = read_line(s, n)) == n)
            return n;

        typename traits_type::int_type status = traits_type::good();
        while (result < n && !traits_type::is_eof(status)) {

            // Call next_line() to retrieve a line of filtered text, and
            // read_line() to copy it into buffer s.
            if (traits_type::would_block(status = next_line(src)))
                return result;
            result += read_line(s + result, n - result);
        }

        return detail::check_eof(result);
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        using namespace std;
        BOOST_ASSERT(!(flags_ & f_read));
        flags_ |= f_write;

        // Handle unfinished business.
        if (pos_ != string_type::npos && !write_line(snk))
            return 0;

        const char_type *cur = s, *next;
        while (true) {

            // Search for the next full line in [cur, s + n), filter it
            // and write it to snk.
            typename string_type::size_type rest = n - (cur - s);
            if ((next = traits_type::find(cur, rest, traits_type::newline()))) {
                cur_line_.append(cur, next - cur);
                cur = next + 1;
                if (!write_line(snk))
                    return static_cast<std::streamsize>(cur - s);
            } else {
                cur_line_.append(cur, rest);
                return n;
            }
        }
    }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        if ((flags_ & f_read) && which == BOOST_IOS::in)
            close_impl();

        if ((flags_ & f_write) && which == BOOST_IOS::out) {
            try {
                if (!cur_line_.empty())
                    write_line(snk);
            } catch (...) {
                try {
                    close_impl();
                } catch (...) { }
                throw;
            }
            close_impl();
        }
    }
private:
    virtual string_type do_filter(const string_type& line) = 0;

    // Copies filtered characters fron the current line into
    // the given buffer.
    std::streamsize read_line(char_type* s, std::streamsize n)
    {
        using namespace std;
        std::streamsize result =
            (std::min) (n, static_cast<std::streamsize>(cur_line_.size()));
        traits_type::copy(s, cur_line_.data(), result);
        cur_line_.erase(0, result);
        return result;
    }

    // Attempts to retrieve a line of text from the given source; returns
    // an int_type as a good/eof/would_block status code.
    template<typename Source>
    typename traits_type::int_type next_line(Source& src)
    {
        using namespace std;
        typename traits_type::int_type c;
        while ( traits_type::is_good(c = iostreams::get(src)) &&
                c != traits_type::newline() )
        {
            cur_line_ += traits_type::to_int_type(c);
        }
        if (!traits_type::would_block(c)) {
            if (!cur_line_.empty() || c == traits_type::newline())
                cur_line_ = do_filter(cur_line_);
            if (c == traits_type::newline() && (flags_ & f_suppress) == 0)
                cur_line_ += c;
        }
        return c; // status indicator.
    }

    // Filters the current line and attemps to write it to the given sink.
    // Returns true for success.
    template<typename Sink>
    bool write_line(Sink& snk)
    {
        string_type line = do_filter(cur_line_);
        if ((flags_ & f_suppress) == 0)
            line += traits_type::newline();
        std::streamsize amt = static_cast<std::streamsize>(line.size());
        bool result = iostreams::write_if(snk, line.data(), amt) == amt;
        if (result)
            clear();
        return result;
    }

    void close_impl()
    {
        clear();
        flags_ &= f_suppress;
    }

    void clear()
    {
        cur_line_.erase();
        pos_ = string_type::npos;
    }

    enum flag_type {
        f_read      = 1,
        f_write     = f_read << 1,
        f_suppress  = f_write << 1
    };

    string_type                      cur_line_;
    typename string_type::size_type  pos_;
    int                              flags_;
};
BOOST_IOSTREAMS_PIPABLE(basic_line_filter, 2)

typedef basic_line_filter<char>     line_filter;
typedef basic_line_filter<wchar_t>  wline_filter;

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_LINE_FILTER_HPP_INCLUDED

/* line.hpp
uFMzA+3r46tRMFFEKxXJ/AEaqgFATIq/7Iq/VGM29cy2vc2KQH1q5WS3Thn5hWLz1DANQwSwIAT2IaeluEjmYuH5iYNAgKBFddvGNiLoaQObk59Is0qeSrH4yQVo+dxU8/YiVStg9HX+NG1iyL4YeFXvHRdNFfbK2Oi1VMANwFS7Ya9jAxqYKc1z4IpovAiEXwiL61S7sYDhODTcz58XAlafWaxQhhVi548zmW6/Y26LMkje0XLXybGR3MlSyzahZ7r7T48z8UdjUR05YuzNA6iDxWKdssjG8u7iZWV5UhdxTkk0NHC+JldjJDfrejOFtmEdW4ejIGPF+Cuv6p1YzeXEWumjIVkoRi9yEs5wHbTwAsZPpwMn0ZhjB3+Jrr+fqAs0VINb+C2F29NGCRy51yBl4CBkrrrXQNYWVxf8+c2E1m8mJH4zAQBAEsh7csvonOgbLaWKt2re/NJcYX5c0PhhIqbsHLuzCXYH6YfC8XM1ZDpQqkEzTSGsEeQpzlNrC1wXky0yxmDHcouqo95FwcZ7l4JNRxLIoVpA/9/8VMKMCSUI54PsVqBatgsCaEPoDpXLLwpfTBw2JAvI+57J0kzJpOJvcL2M3PZ1eIuhlEQL7VUCS5FF2QCyfBlwOj/Ct6uFGAM7R31pkyC5FhzetLXGM5cGtWdwFL9HbgRbddXo9ZyMWOmiiWq/hAXouD/xTh1ujrGh6S/k6E1fiJVLT7ssmkTw0aILjwJ1lMxkojbu/E3pP27kVVdGaLcKvxiAOi7FVE9KbkuDdTp8+e6VUWdtlnxFppVFmg+0sWQGUOcAoOFnAeDmnlXmPjw+tDA1TCoP/HL0OAwEnI0BUK0U+bcH6CZTIlUqExZ4udQx+N7LwYP5Q8kL+HdB7E3gVXHliEUKu8SiDA6D1F8w11NVo3Pv3wDIZW+PQA3Mtot+mJabjvZI235qiNV/H9rslMKMC0Pxo1X0U7QHLoPlI8vP7g1+293heyYtSwhtIy1rd/k4x321Te6m3YLAeT3Kk4asINaXLuFjaMuOhaZSMZQEWZJPTdBXJ47xm3ncgPbwkyE4d1UQLfM/kyeoiadr87Jd25ekvaOiPaK+o0Xko04jkR0YExMtbgxxK7MDCPeGJB2FNYajsWXUTb65LOm5cv29bDzxVoiNmdpP5DiJijN/90WdMSxKhU5GjmkAPEpr32dpA4zyR8NokkITJALA69XnOvxw1pFRp90d++ODmUFB070N6DFt7TbjWlg/qzxT7FEgOi1xEbaWrJY0Y535QgxpXVyFb205xdt5NabMBnM2yuA2tNPAolyEo7ThlsuRcesYUnYnDxmxtfhbrIK/xSrz/4s1IOW9523z4lJiE1ZEOh/gA8GBm3JZIECfcscnCkJmOAR6cmMyWiYyg/V7CPxhVy6htjRhbZOY5uB3Df74bw22XYIVqI8PzIear8hUyXCkoGEBEUyrldEIo5lE8kz4ijOQcizZ2zuKtsviwCw4JDkt4BickkGLV7Df40DwtlWmwtiOAINYUmePTc+Ovy1yiKfkzVHROvInpikGyIrv3CMdimcLiBuK3pTrLxEyLbFUctopRNOyzXW9766jIcSxgAiN11YXsLCMmR++B/zMCOGdqqb7rpN2zzmfa/4QhbdBaj1JF1T8SRRNIhAEWvDkzl1XO9Vb0WGmrg8HkJbcF1eFAtEEQBFHhXRmNQpHB8KRgLDHwfXp/ocLfeiG/4OgzLBDcLnPpe8m3kalIYU5DczDsgrLYsaSqXadVUAk73zfZpETf26Y4Vha+0z5US+T0c/zfKRCgBoviPuwcSrKXhudVJILSgTmoIFSBmIMcT1XbJiMj/M32jwSididGukkk1TzyZt20NJ8Xk6mBs321eHvbXFKCira8cmLOnAFIZYKaGEKhBFB8Lnpo25qJUUq00GNNKvJeHJuO3hwsDM8/TkPFkpjzjw/aqXbuCd54vJlw4XUWGA2MDQcC/HhFxnNKDugxdxDXNygCXX41Gm4L9EKIViFsXvU4ebUwqgOk6kO2nSUx4OmT70In6Oaq4u49bqpk3t5UaB24I2JfmO81zCj8hcSwzpfR13gO7UNbrO1NIduXN2WVitPT3fdmtcMsYEfT/PazGkdrgYaelGHoutf040bxMZUTKJg1NRSIOj8VHzeeCbW4NTl0EfMSzch7Jns5lM9T8GHbibZhENNNb0je/liwpAqCy3WHQNPaItQvlEEyDBLCAQB8HB/AL0FR1LyWsA9XmsA8ttpyj40fuZnpcL7KLEmdls4Dn4eAACIfwKZMOr6RNc//MIWWZiOO8B29sfnXwedjHQ4gh0UkiQUZv+gGvvsM21yQI64ljy0kqWxwjuwmEAH1X2XJc1p7WHNfB5oGVnJxZq7RlcLmOWPMsoG+mmTjOAtzV82KVc9BNZNx5p5paLRjq/842WfltKcWyoUE4/ObaEqDCgvauzFt8h7Bk0bBS8tqR7zyyX/6up5jA1IhAnkjoNDVg3fW4f1AYPx1sqVcXGCygwV360/IceTf576M8Re0sl5yimpXJe+j6ReYhioVmOXZ1DJ5HdwTWKmwsnCWxgHlZqyT25dQRw02xYZ0jhj9Gxrshj51/It2R3fNc5SMlXxD4CtMqWhMF6s6AbvHqMSVfe0colzjDtOLVTrq+TQTss7dThPuWF8K3B3+DGbQyRHHNvLa5d5uQOGdFkWheJyU8ifR5ijM7hEm6azSH2gV3gdVF8CAx1EI/vcux1bhjH9fRlJ3wyXS0Mdwcn0HZYTf0S6yzvwbe0JVPhC8dXR0LUnngPVZrji2lgvhkMewO7Kp0ms0lyttii4RGbetmQNhuJKJ6RlmuU7WqgL2v9j/VWvTKZxXjgiMn4uN8mtAR3s0jkaP6Sw6SdJmriCXkSOy9QERozR3VlGqt9tsLWIJ8FlSnYzvWnMoRRK+lgfw8CIVfOizkT7AdIhSLIIrVtqwMCzgbHK4THSH70gNNnXHSD6LruXWA74lOTmGhKCQ+g/SeWSfr/g1FUKSoglaOtzPPkJ1h0QW4HngRTx+dOSl5fz6WKiRZ0KfhXGIW+FNARxI8Ny5e1sOJiKLOPHfO75zpZ1LAGvoAWLiu4qu3hrTCAYFtadvA2yJOUQfIoQbMcJ41UZ3Oy9EHO2H6j6g6JyszTFK6qndKTf/Y+mm+iSASEPrbW0AhvUCCRPbaK7eL9iUq0ublKbolXefmazqAf+DmVK+hAEUUDeBkcYKtSrZOcGtPJvD1aP9vAEG7Y9fl0ErfdC4JuVUPywOfecf1trkn53vkexzQyLvIz35M7w9RHScTiooRfTGId1n/C8v4YmbW+u0kePiLXzGrCjZUgM3WYmf1vOYmxiqJBqvznNo9g5qXsyhvVwSVh8O96yB2RUwlMVlYni83KpMOv2k5zJcTQtp7F42WoooSuKhpQSMUovx7YeEMaBsI6j1XFt1SR/53jDGKbZecMHvytouInqEd8F7NzoqkhQj9q7Y3J2FWYAERaDusDkxfNkoaTVm+DzDxqGD36psG092T2csv+fOgBiYcZPtm08hiamAOBlu1bKnkEmOFVKLtSHbOuqGd+XwYLkuDG9vRrP6ole7UL1ZRHO0VwQbbnOWTXwwK7wUXLt6CpFHOwkYm3dXKay0eBr+xlndLdvmRKZIK2Cu1XEnhqPnZPCEiMTZKdNzdxaotI3aOamkLlHlgOba97voOSQPt98s/E+gsuhzS0H3hHyGHNq3RUgbVykn5/B29srv5+f+j2HzB0zo8+2nxfMMw31kyszzxnLszaOzl3ikNv+uwhuHeq/q/bIB7qa+tVoK1WXSu+TmvzxPJZgEMsXrhX7oaBYMXtlpM2wxwy4G5/Eq4Qju13PSFtS6ufuAxxdygAALP/T6kGVehRFGqUB6qU3S4AUTq+82lRYb+gE3S9Xn1qfhfneoq5Tly9C3z+p/fs4NF60L8araql6J9++AcBbLlye9izw59pgYWOCbU7dvR1HiJivtv2spVFCONB/fR/2ZgGMN/EqhbhpuqaF5T7oGnzY1Nu8b8tWxzaAte2vZG55oXMpPv2y1nSIjBPKetyigMuHdIE4AcxzBFRUWBdFfVMYU4Y5mheuSmcZJQ/wRWcnxciSilcCiIa4NKqPYLo6ZKyr6+Kyu0tVGjHw65YIQReSZnF1p6mtZiWZyGGWe3fc4jznMBWTEELsxyRhXYaVIZVFkoVywxMETiSIGi6B4SaoRR/rn1POwR1wbVOqc0Lde6envQSnJFfRbB1HxpLeKJXwjHECAnlempAMFMkFtRno4T8F/DhXl/gfTo7oLYMsBbww/J+S9j+qW6xyrRng58HCKTGfwBpUAJnpFuREMwUBRdOGwkLNBoizt6f5YtVFN6bZkJMrpGlo6OasdQfzdRFtGlggAU+rG3HuJ4bIOt0hVbsgHH0jy2cbjMjDiLnQ04PQDEkx3WYyZIUZk6aWVdDvHHiIz7vJxDBvpJjRjCZyNgn1+Zlu1PhnO4FBrAPFCJbRkKUBGYQzGKjiAoNJQYU+Xh4lPhpXXMIbN5GgW/pYjGP7e1+B9z75i4m8fIC5Z58vmKbV30ikoVZ0gUvjXQX++cHdMEJKxzfU1XI1Uo4sEbHZsgjkjA01AlW7XyHf3dL2JzV8BBBvOVGdCzrVcGpMt5453QUJ5dgdRZod9wjxj7YhU/qfUmlJ6iq/emhnNdFO6bgvNGfqMLn6sYxOCmYrGv4D1lc8lB4Bl9un+Z7BRxHKmKBkOZwtesT792O3RDdTrKKEMTCaYKUmZja0Jru8holtkrG197yiBZrzRI3SbUXFhPdDDSXlngXmaq9jHChN5+sYuYzQz0Xv/QMzKsGxa3g7HBzqp8zCJ/BP1/1qysnpcRhdfCwbzZLdGW6JvX5dCJxH0AAFpA5SsrdIbIPUrAnW0QFkaR2h+UW+UNl7VLW51EdwPj4CR77gr9HNeimhaAakJwZazBRWYc96LWDk4bIit2FcCKkCO46QT4l3eGFw29PBWkt3qKDUtKbBBBfMs3dxZ+z6lRtx3F7NZAt2p0myFrdbAOtAccnBttEmg02Ijlr2FasTbTWXZ9G77yxeXib95h8b7fNKa3lq3I0mdAiYZuwBMysgmtO1dhy5oWUDYIhsvVNRf49CHLiahueO9SRNyQZlOfwX77AmR4T66uJt781JjXH7HcW5AkySMYV2oWEFNJGdWM+5eXesrjhpFd3BLd/I/BXDk2+LD+YbVCIfk8oHTGap5QgTuacAdvXJPsHFnsyE004PVdhE/gPes+CrWaYNiarQTz6onbsGoktmNuc4ShDkzAQP1HUZuYouYJ657kzZZG8RJL1udRWF9boTeYMzjbQPLUIsVNBSkmGB+GGbqnCWGmEQRMUzYMHXTLM/RPSUzrQ/ryostgT7gdK2egHnUEJREfUmCBA6eBeSNFvqdKWjtBApZj1DGirL5tJ1aDI0npK3M/QX1ai55CtKkWqo2l6qZddYI3AVMiVcI6C64WRb6RS6UVzVJnVeuUI06p1CEI0sdcnBzwn3fzyJIPqI4tBxLrXbt59YaaT59O2x248a77lqNqi771fo0E/VaF2lik+iCUFOzVrsoL2YetJuAX+7TdDohpqlLZdoegektWXulpSfqeAyX5kW0Az25kOxejx8EZusQota8NSYp8yAgAUCJAoOQSAKwlcoI4M9iVKfiPzFfgPA8e+BH+YPLxmas+IawfXc7Cw6erkDiLMegeBA1Qr58/9OJNXijAlE8EMqAASTSIoiDb9BU0UdiCsE6SoNA1rqBcyRKNiHkoE3EiRHgcQ2pTn2yeuIEiS8C4X138+gCso4IvdfZC2jotIVOL0EvIupKMUt9aWeWis1yDHG21C388auTuGmnuhVhgY4TPVXZTZgAgvR2QwIjNBI3yK8/iWTXi3beWbHW/HlPi2ccbgZ1DFUOeau4S65TPQCr/TIaP2Ex6xa5KEokn6Fy8bg3jFP6m2wFSB86VHig2RNlCiXviavxdISlUaBR7u1cudn+yPiUzppic42cgqQCHmmM+HRrWn5V/rVzSvzbWr4VXOuAXO3FK2VpUQjEoMg1gwcgh8Af3wHn+aBHLhh2yXgMRFnBzacDK9oYAmMFjWQui2NXI3zqvr0v4eotoC5cCqlOn3QRq4OSP/4hl4e3VMm15wUW9bcuFCLNSdk6t1jgvbr6HwxkfBMQtKdJi/GtAKTBmoqbS4kaBQxKaH16UVXislTMgc9IexZb9K51G1AKbXkhkqIzlQkxWj5nRRyr+Bhp6v+ARBSxMND/M7LSmMUhFEBhD+EXeCKgqsiASxIvqAxy6Asi0zQ6KKxoxP42um+6r+OFiFLkyWs+pJQranrT6Mud18eMI5AdR2gncfrwEVzv51KtlXE8yzMRlVIEtA9B8XJg912Kcre90ENY2slT6JVGKrlHo1ylQ3J7BQTsKq8ygEgm+nenWczVGOnKGxHiya3GA8X6r5Tv6QO0qTHiiroNQNeNYOgm8Sq9TJwceZ8BmZKFBsWruPkXFoqY/nONmmSLO84JOV0Nop+fuiWgcsawcpJLS1Q0+BiItsHJUmi74Tq2yMydw5w2E59IaK4S39hGgC3eJS/R3zzWSDT8yHjCgQwghCI/kBo+U2bQ/Y+ob7AfPmffbZrYC4hk/yB/HEzollU44yi0dlmJoaaJhAjmjkJFjpUg4GNp8v/70crWMOCmPwkBbKVIhKp2qQUGYLNAkDAOPGZ16QGCLTaUDwhFpFnqrpmY5OTZFvUpCawOL3W13/L73HKadagSzvGsE99jn6QPcZnyf31/xA0gBQX8YYyDJGAbmwlprxBb0bSXDxIkUNukhVmDdIUn+GtmmPnFeZnWGqToGneUhxICa5kyqiJCflOvO9PgSarrQ+QHC//YXRlO8/C6zlSNRxpUlYrlbpRdY9RWmAkNXNZFUfBZqvov5h3c6zDpSWqrqFZdEWgj4q7xMPrkgwu9GrmkvGw2Hz25sDgkL2O7Zxt4GcHkqjgApt4hLVBC6gKSgG5T4GtMl6JjdJpq9ty5gg0HPQA9wcwpwA7qtOTgPV9BeDais0qfS+L23bk1a2B31xY2wTkLRSABwCoKDEJ9weSB/Dpe3boyX9FiTXfr/PqVxR/Cqq6QNYr8QM9C0vyJ2aVomGSzWf+PgJ3T/MUAOz2NBibY4fIwQvPxlMEPRdSUieTKFyieWJpgGI48rDxPpZsdZxnXluMaufLCEGbU9DVdpJ0qfEAFwuo33tu45oCVAaS1bHBI0bCNLmr3jF0VBaqZy2q0rvPHfQ4MUnrhAiGstbU4g6yEgbKQbGpZ812zbECnTsVaJs83v2De2nakY6la/dDG18hFUw10PUOLsrWSNcbeOpmns5NRmH9Zd4pvzAVJ0N1AH13tMFcaHTrdhBE7F7YC5Mu+C9ThWKRfhoo8YC2x/N294NH6uIoVJApc3a403xY8R+Niq9RukOrzrYYEIo8+HV/WV1Gy7bwHwf6XGctym4IZDwBuna/EzZbE7me4+c21cJpGmGPz5jGpefUzFsTAhl4/waWM5cBlCiBR5yxgmQP6Galv9QmzZ/nYdOpO1xOcZfTKOgI+LTwaKqIsZuK3gstJdJwCa/xi2/1TOkV
*/