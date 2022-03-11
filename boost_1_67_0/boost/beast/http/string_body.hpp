//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_STRING_BODY_HPP
#define BOOST_BEAST_HTTP_STRING_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using `std::basic_string`

    This body uses `std::basic_string` as a memory-based container
    for holding message payloads. Messages using this body type
    may be serialized and parsed.
*/
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>>
struct basic_string_body
{
private:
    static_assert(
        std::is_integral<CharT>::value &&
            sizeof(CharT) == 1,
        "CharT requirements not met");

public:
    /** The type of container used for the body

        This determines the type of @ref message::body
        when this body type is used with a message container.
    */
    using value_type =
        std::basic_string<CharT, Traits, Allocator>;

    /** Returns the payload size of the body

        When this body is used with @ref message::prepare_payload,
        the Content-Length will be set to the payload size, and
        any chunked Transfer-Encoding will be removed.
    */
    static
    std::uint64_t
    size(value_type const& body)
    {
        return body.size();
    }

    /** The algorithm for parsing the body

        Meets the requirements of <em>BodyReader</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using reader = __implementation_defined__;
#else
    class reader
    {
        value_type& body_;

    public:
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type& b)
            : body_(b)
        {
        }

        void
        init(boost::optional<
            std::uint64_t> const& length, error_code& ec)
        {
            if(length)
            {
                if(*length > body_.max_size())
                {
                    ec = error::buffer_overflow;
                    return;
                }
                body_.reserve(beast::detail::clamp(*length));
            }
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            auto const extra = buffer_bytes(buffers);
            auto const size = body_.size();
            if (extra > body_.max_size() - size)
            {
                ec = error::buffer_overflow;
                return 0;
            }

            body_.resize(size + extra);
            ec = {};
            CharT* dest = &body_[size];
            for(auto b : beast::buffers_range_ref(buffers))
            {
                Traits::copy(dest, static_cast<
                    CharT const*>(b.data()), b.size());
                dest += b.size();
            }
            return extra;
        }

        void
        finish(error_code& ec)
        {
            ec = {};
        }
    };
#endif

    /** The algorithm for serializing the body

        Meets the requirements of <em>BodyWriter</em>.
    */
#if BOOST_BEAST_DOXYGEN
    using writer = __implementation_defined__;
#else
    class writer
    {
        value_type const& body_;

    public:
        using const_buffers_type =
            net::const_buffer;

        template<bool isRequest, class Fields>
        explicit
        writer(header<isRequest, Fields> const&, value_type const& b)
            : body_(b)
        {
        }

        void
        init(error_code& ec)
        {
            ec = {};
        }

        boost::optional<std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            ec = {};
            return {{const_buffers_type{
                body_.data(), body_.size()}, false}};
        }
    };
#endif
};

/// A <em>Body</em> using `std::string`
using string_body = basic_string_body<char>;

} // http
} // beast
} // boost

#endif

/* string_body.hpp
3nymV+3HH0invzwfAuRkNnmwoG/TP5YJxZPv+AO4IMV0VtoQq3MewZEChI3puZ83HK7/WwTxnD81cCj/Iu88vuYSA5g1R5Nfv8OSiUv0nTMfzCvdwF/2aYYNz/gJGYnrtfhJjqQmY+p4ItUIQJljs0TJBrTPyYYV3O47wYsb+fXU4AfvhbZklNVQ7hqIf16kgtX1g2MRqCD5+RGxdA2RHe5KZJu+QArLkRK1jpi9/eeUuG+4EZo2vXQxZefG4R8oWA84msQZFJvTijXNEs8vJX9J2bC/09wehE6J3+14I8s3AgkMD/0tdOuz4XfvmVM3zfQvBzR19LCry8TS0Px+RPk5ci5kmiw1dfvLCDNEJSwMbkQhDQG4FUvs+HG7aqgybAvlEkgeA+pQMQ8pLJGRi7sVQrzwywbkwIZMl3A5XpRlEPQs5DvptBLX24GqnR7w4woaES8UzFkpPCmO/20K4RF4hOsirtsVKA6gmk0P1r5GIdqqEcspvIYvPrNBW57Hve3fAh+oteuFHTgZuvXBsvzLf5zpgCXQ4g6KyyO2Wxv1U5dH5q/bqp2ovcaWBIzLXbVDdjQF+TdyxwiBB5mCI0tL6J0i1ISVAhYWJJQDW5Xc1IL2vm5W3UfqlUB5K8Pp4XaPiO5noIbjyUidkvphcjkBmaqIdJ9WGYdbT3YhwzB0I5M1epZpdzIO8ZTsRoE+Ja+VpFGBH9JKFzfi0rKaFQztxbmhD+Z0sE36yJBFCOlP7QNamkZqbccczi+KQDoiAFgMyPOZvb4tgoCHO3znwzfWscppTul8iF37N+4jjrg5zHOw7gT9OAeoRJyqUKZ7gksZ05fgcE+wqhf5f9v8WJiSzLAnNRuozcWCs7O39tafE/ks5F5fJpioRBIMexYI9q2uqOxS+r4iH9eW7XsiHK5jfckHLMy1/P2T4TgrWlLym7aGNnIjOSvbnzGXCJ4ImuPUULX0YfMFLJ3Cbvx784ytO093f5B563MwBqAk7JGeYVm6dcACKpWeYaq3BOtuKGfyY+YgaQvcF3gqesFE6RFel7dEWW/0Q5f8Ti/Y8gEMqH3PntNj09DQ909Kif1lfEljMSlG8O9MmQMj1gGD1z1CGNfgL+Xz7e0Y8WVOBMVr2XRe532sfD493C8oVNvQaH+WfMTR+Wyw5Li7J0z+5OQHVthLXyJXlCppnq4J+3KKAFz5IYu+jfQkhWH/TqZXYUZCRnig9RrGrkLLRoxj/cLzvQVPwIz5UDS7YhQJFnfGu2WRAKTayDnoE0HZXTFtaAFgOwG30ANUIL9BThO/fMAjUZuE2B5mDMUBY1o1w04Oq001kT7K8edg2Un/+qbVhaxrBK8ACO374WcYm7pM6VwmFx+Qb3aS1Itci3njg/emy2sV+oOxGkNfbsUjKg++JBxtkpD2cf/DpM6YN7nsn/soDVSjL2Z4qg/3tABjnyxNoevrh48qLNSZo7IHu8JCdAEQwIOucEFDnAmN9AHRXEbGE7YbO8pDggA6EjVtuyGwMwiESAGaTYat769nH4PORyZQiRwcTAVVTAX1yzXx4B76i8YgQ9EuOl0dwtfKH8eUAPBr3SJY2huNNYARkIhn9wQEbMUOCz1EKXBJmbfQBRvpLGE96EYhWwsQHKysN8tLOoQikG0NHgtipgVMI2bsVAGsagAkfL7LiVcS6ZpXDdm8CrrLs6OVDWsMcwEYHgDFA7o9ETAZdCJ4xGe0YsigMtV8ggWe3DY1HackjEgCKZ+FosaeBa8j7G1kxjcPFIPDRwmnHfEYLsKZ5VO+WWaewfL59OYOQsqCbXGiVT9HLLh7tC5pDRUGPLWnWbjYVVwyBV/9dDBIbxRKpskugzY8+EQjZBFY5FZ2olxf4mdLuLajdAuCeWt/t6OiRkyqTex0I08b9ceT5Gtook3zyoiHt0mX5N4bbuz3LfbfXWbZk3oa5zyJSY9p51KAQV8QNG3hyzFxLM0DlJFOOk3vy5d2Vn8/3u5oYOhue+7srFn3ETpSxUhqyafOKbLhbZtwbqvIl4d7ip2BDvYIzSY00X6uGR2SfMpuj6C3GrbHmQqlqsWBMuuHpsZEBQ0M7cJvsqqYZoAoYjIepfY+fGjmsAeVwVgMyM56d3Si7ZURw252/y8nkJeIRhp9fh+hgmeWtWfOazs/ldgrvcLGYwA83cpTy6/ffSFADZLrkdsq6SQt+hB1FVgU9WyqgW1p7xJojDtoMpqboIJgg4UTnd+xCSQKAHgiRgWZsIgdW6xsJrwapqeTPTYDPR74oRdZmHUwyM4DjUEN5bW171D3cDeHo0k3w4xaWOU36aSrljsTGLQGo1dUNl7Q0R+WaeTqqYsCSAxG1h6yVcoKqoUucy77C41m9qLYy7+LKtg+8jUhQ8w0VEixJFAFd21ROE+IH568/Y5QY06ivjxBCi4T2Q6zwCgPGJIvjunockPdcUDIzI1gQh5B7XGx76PPqADwwnXNXrDup6xBusFV9GftJdOpTMLv96qZ+TPcJQD/DWX8gAHWGkN8W1PTh1LVDIzTqCdQ7MkCd/k6BeGSIF0nWN7XdZgjVMyI65/plnooV3RJfShActsGGEYedo8U/N87WuMtj4yKjr6kA5mFXr+UU9dfCCJAAREWwHnwBUMv88yvhTjX5nCP+cmmZjXecU9BvkHDXqB2XEFIbI/SoS65ex3ATkOxvYjr39NQVPrYSN3cDRg4KpsS5YjrsyEeryM7lf2qLSfZ71H5sn61WBSuxb3TnDtvPHM8rh3PpPQMQYgtQy3Kn/DHYx5dV0H6cHPzAs82gWWkGRWQfF5+9tKhAIRxmweDVpJvigdGEthHmLZbD2+Sj+fkT6ulcSC3dHJbVVxXnHErlTP7rFOrGo/PTcVBJgsj8Nox99qrvyomieOcFPp9Q4l8Dt8SoK21/B8cvfh/arPLCy8o35+iTc6y0yw8DVwMltG1E6DS07lE/j/IaHL9QRoo9V1PPO7gSz+uiSEVXMl+UkkqxOr4F/60jLacNnO2R/x+Vnls09lseZ+WRXVOSy/TWlpaUimRy6qRK6qePrm4+PVZnAP2iQd9BPxja+tjKgD1xgVE/L1u6bobhHkx0foxQujjqX3LHxmHQa/NiXFY7ZuVGRfHBHoFbA3YRQwqSoPFLQPbWPC721+4koXWO99Y9/N439kGc6HYSKp9j+a9G62a/vSmkENEQ0MbjMQuy0yte7MZPuhdt+nhQ+vnQ3BmJpHz4wmzVlVVPWibnJwMfXj3Qw5DWx9IzxyiBAS13rTrHLhse6W0pJBaImyo2KoNVHOflRY434v1SGaCfQIkM01g0w2oAz8keLkxry7+lTiZYH8k6QLlqYmJCb+xyZmZmSDBxgsZX/IIAlj263sm/LbznOmjoyPV4k3IBcSFtbVyKyMjI7gA2x6EsUngWiMrtwrAhOUjQh+TZIfONB2pfbpaAJJrFimW86B3DtlEkDPGj+8H87R1Qr5qbq/QS0NuuYMZ8UMjlwg4BOuoVDIdHd3aBGcd/L2vgW6bnHcbPCUtLZqCmLYv+FhzIysbW1N/MysrayNAwihuZDU6OjrmngsQrNMQVFvT9wWH8wdp4F2WFeoN5McUKj4oHRNuv4TCJATRkQIjBDK4kJ2dnbeioiJBozBBEmjgDBgkdPkxjn/pwmMH8d8QyAREnPWi7fq2RfULrQBdfETjBcha1pWlJballRUOEFbh2EGu3FfLebBeZFqbvi/UNeO06dxvcQciYepItTH4eXnO3cCA4CSbrsdleOglcWJL8f5p4z5oWPPQ+Pj4j/l5Jda1oNfWFFHgam7tZ79ye3PO6RjbJ+uXBSrOpzRgVazaauUa05cxM3mlMbcJn8issqzMrLKqyiowWFABSmKOSBf6G/emx/VhTpzwQV/QyLCBbfw7DwoaqAi62wb95LjqFk1knJuRqPLvD8Lro/XnQOXN+eZKC/5I8V6PH7Cn897lHgiQUW8d/CkrKNY/ZIz3dqj50UyTi1I7G+RsBqqO83S9rRezpcEzDhnv2KYb8o60Kg6CMZ2P71hMSESsAqs/GWSrDbG7C/TACoJOJ8HNpcwvBuzfzbGFAQQBe9By4OBPbA17TVjrDAaOA/2XnHUfhWyjq7sPE00vn9UIP26NerfBq+Zrbba7ueVAOQ/XI+96wL4/AeN7uZ1Ii7Xevi/miL2ccyDDVMip8C8skPBYCgD9RH0ZRUpgrY64hBJoUEykdQ8Z1mBojnUquq+6NcUwLUJSUpLTv8cxagdqNXcq4mYbLLeT7pRw1FoAmLk2ILOYhhwtbSCfH6v/xmYxGkv8EyBGFUgi3RgEAMtHniN4iDC2f4io+/yxjKmTrBH5crqWvLPTBPEjCAZ6SJDfV6nBZIZgjprS+djz5kwQYNxd6EHUvokYiyrPWyd/D4Gz7/nrLah2pP6Oa4eA29EUmw2SmivBF9lWYdVNdsWmKBZeAAveTdCo4yECPfYmnWiXTQbKV6nLYqVas+L9kdr1Dtr3jpYUzxRyYCKVrIRX4roC4HY/xcEgVOQNil4JtaUv8lRrMDA+m0UtFjQMAb+70QcKSxWz/RPa1DLFWxM0oNp3sO2q17cbA1i2u0f2CvbOjZMycjSV8czh8+b12r4OYv9XrbUi7zp1xJtnn/LXXopC2cjAH30+IpOXm11jLFfMAlCWUmLLifHDJt/e66es+Ef4n+BgUZewEidvlhTDFE08zhelwyJYfkL3sC9ux0ErDB4lFJRb7ScNVMYL6EDE9CAhgBE49aNWae/9zp9cmzQ++4NRe5kFJSNbDzFwrE4MhVl5aVL6TxKiB5eQv80NgiorqUmOxT3OwlH99oEUFbvCcL/c0tYhsASawdeVNz51skfNuokYRsHaD5JeDtdApCBxspVMD38AiqzPl6vemWQnmbbCYr6tj4xC35UBRcxThY+m9lAQQAVsPZEiT4JmNB2/SBRSsUQEHFZTADWl8DBm5W8BSvW/zXnIhROWW6olQd7r0e5NdtJZ+R0uPgmaHd1iJnFxaUXMG58R1Cw07dTcTX8cBBf8zEwkKqlpxlRIQzDL7Qqkf7368oruRBJqlZMTaJaHR7R20XyKuR5CwQ2AYIAW/V5rNBPFGlX759RdOGjagR4UebvtUESvwm9UzFTFDdP+pjJu8PMZOrSM3//Ir0VpLuruH3gC3laszTJ77fMqQtBwRn2JIigm8rjaT5Wps66i90WeiGdTl01yUzBL3MnZAC14211YIn/fWAndSOl2nkcc2Q6SUGg8r82t4mAE+lkgl+Ub0Onhoi/cuj0SmlRnnXuNbP5TqGARNvaXIV0RSKP/YLTazgeHbz23TqME9zqGj1ynZFtqY9irdg3YwYe0wI+E3toMtczGRwFFpszmQ05Sj4vVuoDaaEXkQiZoZBzY5MuzCDLvszOtpX5RSPiari5lr9o8VeOj3xWVF3hWMNASCj+oSr5CQWQyzMVT6ruaRNGPjEu5WKDKSJEIC6MFzLF6lZPtycGhohB+vFnl2irMOCVG4XJcDQGz4aLBx7OQOnnPUqhQ9X/aHruIa6mFeSBx+2p77yXvloZ++/PBsAeA2cqs1/MUmRRDQ2r6E2f1qrfUifE9z2M8DvN0LO6hJwECQYQxNlybhJzlyJf1mFW8CSA7NOh9OauBiobL9L/hD08HEx1LzK2vZveT2LdTf1KCTIU0q/oOrcbnyzgdGAQsmVFE/yrB4xBKKpz9GQFFGboAYlWfw6KbG0S0K7RPh9TN7G6D3BUW7MQBzOfpDlNaDbjNY5vuS9+i039TmJaLIhTwhv5D/MBPNYeHBl3nPV8o9LlrsKLFZO16RpgBiJwyH0h2T8rKKKm3t1cxcHNtCYqy8BZkh1xIcwdmwbUQCUgf9jlD+DNy9/eXIWfgrNemlOsEBFsrk35iVXAGG5NPNbJWuZ40PVss+bdgVkTmdBU0jY9MY1X0+XuNTSuH8Ry0YXUY+JOPDf4eA1rvavR4f1pPOtvNrLMuHiLlyh5NsIy1hy2b5b/iMQLa7g6sWgyMRof0JYZ7/cDg5or2KirSQOFVwwED1bTMZCjk7IKtup7GFe4faQhndI4F9fd3bIyw4+NgbtJANPTj0vx8SxXtzKpP+HOYAU9Y2IampvuCZLNSG+VHw3PNPlzUgM5RoZ6M5KOoIaezpaDrsvwPF3Q/+9uRkQpJKseBwOdKpF2egdncw/+2zz4ols14MqyzI2v83gSMDQDGnuGNve5bZsDAdaiZ70fkUqgdNlrtTCOppTRAmtFtVy2TYesH+j86nljLPb7rpfhunxHKu6mEwQpsfb0ZqM/ihKCN7WBAQPQBaKfL8IrY5Fi+YbwqSukFdITGK5XVzSpLi43lZ2eqxi5T4LSLtDH8LcJ8Hy2P5sMHIGflEeRlMdnsYsZOc49wpFOQ4YOC+H/+S88SZnrUbTKeSP4szZGeu0EQ5aufWKLQg7taCHBcKBr/QGKs99cph0ElF2n/BYoIEtyqhH3bbrGsUibw6dbkfveKQE1TAzQ+xhTR5OeJ8nSMG6e503d45Ozvdsl9xcVZ+4Xgq9RWw2V+GWRsNpIKYaNeRnyocXYmXVwKN4NfAztnJbNY61dPB/iBPWq0Ynvf7nS+erg3Qbmu6CMQzP5qku/2cVTMFMa/FxbD55Zt8S2aAwHda4eLVd7xK7Wbbo8WPXRFh9rfD1AnKOhDEtzbun9VdKZXY7WSOyqoNm5T38ACTznuUNDO9NUKdeZExzrxNY6horOUzxalgyhH2MLGUd6/gei0mbSwhI4p1w8ubLiPBhoo5msYAO607KdRzbfsaNuvU91hTWCRkFlLOAI26En+tJka4zwj61h21zuZ4xdHuA+4jhVGLOtNJZ0vMqwGD2DULb3Rk27d1olhC+f5qlXn4/CpgBSbXc23BFaXY6WWSEkbzcS9L/Aj10jXnkisM7WjAs1UPZ5ZTwUFJvpPzzb6DZfW5qq9nWaknJ4DaJYQVqZ/pWQKMBnQUQMM2isF2G1L92VkGuGHSIzYfPvRn6XnGO1RTznmDvdA0Lqs39CAgGjinb8zvZOorfhe44lUwq/hFT08xg50uvqLhrlvE9vdNQSenlHj4wy/vPVt8QQV4AmUfPF7CLvvH9S//ALumqr6MFL5OjIeWoM6j0go/Oaho+4SeFLO6tZcbFILpnm5bq8Q+oiDH6UCCISwz7hcHs+WOuqkX4xClaE1WlGI/jLYeUxcssQDgiNBOL3lbWM1WEym8Yh3iJSthmEpT5yNmfhVkPjqxLI+wnrKQ3K2Ku+g4H9xYZmE7vo6n9yAslmJteFwtUvYaaoSDg5k94UsJicflt+iSi8VlhmHezPlKzqrmJQz+HwjOP3F/CpbVbksRzzgX8jTi1yk8esX3cJm+RO5o45qJ1dECyQPlt5gVJuXW0aQVut/Bwfi2W4gFE8Gtk/l8Hu9QZvG4jHLpVKCR+AiCau75XS+XZ+J9+hWprPkYsNGHNjx3bOCZ4CUyDGoDdTWUMHtR3nvHwLYKUuFh1NKwxImGC2OEf+0cabraZdv6emU8DsPsZwd97jpsbWkmm1Wnw1lBDRYDZsB6sqzBtpHaDE7/jrgxZJVF3+kFdpungNAOBFBSAkghYfvl9QmkxyKeBeWsWgJsRms1ZJ6x9/+Zl2XOdD7aFZtbRTaR4TzVWxeSMlm8QMRCP8iwU8t0nvD1g0LRwlJz4aO9VXq6WoEtb/PWCyJM3hJdX1+VSc2wQxnaST61dczZxOwIOTbcuAqjDWUbOpCjBa4yBIiQfLCisEPXK33SyaQ396A8zVgFHLZVkzAqrf96eF+ry9xLKq7Uw8zVJ+zRBCPoVPdeJqz+bEPaILu0CmYRTdeSQx26r8di/7MOqtn+JL+PHlqSZgnV9p2/As0/ODq/FcAp8piBH+E07GaTsM2LZRAbW0nb330gVxPSujymZxxx+vuxVl2ZdKSHATvHd9axfxfpyVLzV1W7fMHbqrkgoK2yGSf5GyI8HiZNcVAMGXUiF32zI95ZqdvvZWK+2r/Izk7S//2iVRetztG+B24XXxIjTYGiYTaaOU6IZ/UdZp/QxtcoOBSv/MboKrmNp8jGCBMBSeLKr9LU7f5MX+eoybwfamUpPwr+J8+tIDvTbxMNANbBP4iV75oOd0VlHMuxgkQM+kvVJqpJGwae8OnO9tX4y8icP0HCI8mK03VjsdQu9jqeATjWxCdpAZctivHROu37Qvb+//aHVeY1csTTR32Jj/u0wB+pwYYhK4UedmcEjhNG8uXt6RcrBghyEnO267ZX7T+YENkQDEYTi17XLfeEbRjws21N0V1yUvaXIv8+PE4sL6trPf+NXFi3+SiEVNpgWN36vJbKAB8s8pzdFJkoweV6NTeOWKmZOCBEghA1ADn/cGC3oYVqeiEM61eFAaFFenwXUCzFLTCX/C0TD0Dj94SJJPNDKzx1xp78ugIA6sUMk8QnsXaBXhkwemB7ByMKjNYL+lU062f70GG5ciMQw+T/YOvoz4BVKdvGl+yR0ytD2wI7WdKoELtuoH8COKjJRSee7NUY0griKMYxOZbBMfSs89t9Ti9SJH6ukjrKhvMzs7TnfdCA94OYuCYMtQJ/lQ8S4e2BQcHKJl82U+aPR8Ikd9+9HQH5AkNWpysmRQb9xcH62QxV44e8ESufE8llIvigGhaWlDEEWbx342Rtjpi7Tp/m5vlHpeu6RR83H9XjQ/cft/VxzuWicX0JVo3Kp3JETyVWNn5MgTKpqoXQxoQMZCX5CqocPw2t/q+DuJprzSKA+FnqBcUaBQn3/IgFMMWeklbTRZKC+fpym2V4Ug+RfHNtXhERXYBeVY1IA6FmIzD8BdZAEe5RjLSe2LR+wxxv8vRyu2uO0kxGD2Gk/rUKVdf2mh4Vi8qEMOsYMICkzJKilJeXGe+XzrUe+HRFdIiVPNaryf+qT8ghZ1Pu/sF8V9OdMyhrkvrJiKy7z4p4GsIkTPYUNovGzexv0HBmwhc5z40M4Jxy/Uyiw8Sz73XTFc1nbNM5hA9V1q08nGdfwBMDkweuDnaKtITp6FQ2e04QXMmj8QQU7H1aS/klgef18GGZh+0jp0CSlbC1Mkj0wIKvoMVAFpbk+pXtgELXw8r6hCKK5/XfFmqTNhzZmN+e4bT1W1ABqR6cmtrX++RJSOgf5LD6+LkKYL32Jg=
*/