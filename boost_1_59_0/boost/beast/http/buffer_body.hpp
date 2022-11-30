//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BUFFER_BODY_HPP
#define BOOST_BEAST_HTTP_BUFFER_BODY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/optional.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A <em>Body</em> using a caller provided buffer

    Messages using this body type may be serialized and parsed.
    To use this class, the caller must initialize the members
    of @ref buffer_body::value_type to appropriate values before
    each call to read or write during a stream operation.
*/
struct buffer_body
{
    /// The type of the body member when used in a message.
    struct value_type
    {
        /** A pointer to a contiguous area of memory of @ref size octets, else `nullptr`.

            @par When Serializing

            If this is `nullptr` and `more` is `true`, the error
            @ref error::need_buffer will be returned from @ref serializer::get
            Otherwise, the serializer will use the memory pointed to
            by `data` having `size` octets of valid storage as the
            next buffer representing the body.

            @par When Parsing

            If this is `nullptr`, the error @ref error::need_buffer
            will be returned from @ref parser::put. Otherwise, the
            parser will store body octets into the memory pointed to
            by `data` having `size` octets of valid storage. After
            octets are stored, the `data` and `size` members are
            adjusted: `data` is incremented to point to the next
            octet after the data written, while `size` is decremented
            to reflect the remaining space at the memory location
            pointed to by `data`.
        */
        void* data = nullptr;

        /** The number of octets in the buffer pointed to by @ref data.

            @par When Serializing

            If `data` is `nullptr` during serialization, this value
            is ignored. Otherwise, it represents the number of valid
            body octets pointed to by `data`.

            @par When Parsing

            The value of this field will be decremented during parsing
            to indicate the number of remaining free octets in the
            buffer pointed to by `data`. When it reaches zero, the
            parser will return @ref error::need_buffer, indicating to
            the caller that the values of `data` and `size` should be
            updated to point to a new memory buffer.
        */
        std::size_t size = 0;

        /** `true` if this is not the last buffer.

            @par When Serializing
            
            If this is `true` and `data` is `nullptr`, the error
            @ref error::need_buffer will be returned from @ref serializer::get

            @par When Parsing

            This field is not used during parsing.
        */
        bool more = true;
    };

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
        init(boost::optional<std::uint64_t> const&, error_code& ec)
        {
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            if(! body_.data)
            {
                ec = error::need_buffer;
                return 0;
            }
            auto const bytes_transferred =
                net::buffer_copy(net::buffer(
                    body_.data, body_.size), buffers);
            body_.data = static_cast<char*>(
                body_.data) + bytes_transferred;
            body_.size -= bytes_transferred;
            if(bytes_transferred == buffer_bytes(buffers))
                ec = {};
            else
                ec = error::need_buffer;
            return bytes_transferred;
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
        bool toggle_ = false;
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

        boost::optional<
            std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            if(toggle_)
            {
                if(body_.more)
                {
                    toggle_ = false;
                    ec = error::need_buffer;
                }
                else
                {
                    ec = {};
                }
                return boost::none;
            }
            if(body_.data)
            {
                ec = {};
                toggle_ = true;
                return {{const_buffers_type{
                    body_.data, body_.size}, body_.more}};
            }
            if(body_.more)
                ec = error::need_buffer;
            else
                ec = {};
            return boost::none;
        }
    };
#endif
};

#if ! BOOST_BEAST_DOXYGEN
// operator<< is not supported for buffer_body
template<bool isRequest, class Fields>
std::ostream&
operator<<(std::ostream& os, message<isRequest,
    buffer_body, Fields> const& msg) = delete;
#endif

} // http
} // beast
} // boost

#endif

/* buffer_body.hpp
91XZK1b3eAa49qCSGYVBm32SmS+sz6hUaBnQGaomr9ytsu2aOJXXYJAQWvweXsFr6z8RKelTDrrYcC424tP44oMvb4Nt4kB0MiYNQ2UE/MD6TNYPZRzhR7RAcKXNVGM7qzo5LZCFkIgn8/rE2Ss8EXGom0hGcTSa/+IL0bFcoskMKAM9jCK9Z1lGyuIvAh/EA0mXO5Pzm+AP+GkwBzpFbL6p62Cf20/0Lb/IGQnGasfBw8BIQPpJMNqE7esUvVTljLg4cAokITR4MxYGXlaEkiX4IgiZYPSpmou0T+La8YTH8C5r3Xp7cFJMSZSD8ZQaPTY+muvhbZji9MbUv0S10vHL3z97fJkimPiKo082pH8zvGqRlHceMY0QnMGAb314cNPSAriWQILWECRXwgsKGIUBWV0CowoZiqSL5zREq20bo5lPB76rMftdj21EqrebSAIqKo4b+B4YEcp1FEfc9yAEuiTYw7CZq8gCua0z+ITcMkekhNMTRwv4vA1m17ow7nzdncWy0binyNlX4kU6bdbQneWNn3nSwtm5t8nYjOR/rmgik3cAviogVxLvZbWNFB4YeoPf4jhCJ4V4qEO2Hkk0GwGyKKDeeYDYBBQE7P2eth3iPBm/tblzHXOwA81lZ7vpH8bKGbF7xS2ZQO5fWxm+5eIJW47CaJFa7iWILYVcfkYJaf2KRqlUH6fi1e/GvCUdJGopeD0YgmVNVbmFiXIofz7T0sWUF9FB/DmcjWYFkXf2MmdzknTp7JbXkOQ+REOJwU5J9NV4PDlwlglXqG8T4DoDzkzcHCbkE3raAem/6MvlCTF3f8xC7tWUMPbkSfCjLgWAlgL1BMkloeyX+Kq3XT3ARCn+cUMS6CAFZVHP8z93+KZFED/zrqY73QQ+sQGhRuX6waQh27/TjRlrhTnGgWYiy7HWqzeWvTamRjlyBkKQAroxPIicVDnjJXgyDmIyteqmVgZR9pYbJuJhE+1LM0pM7aUil39G80NEhJMC7ibrVk8OmkpcBZHBayMzWXRZzYK5wAF8PZSQbYsQ8sYtwzAIleSPjwqjUnBaNaig6hAKNxQOUqp2sevyiUw/ZWWMmhRpBmjYcrqT3HQzqwmHk07okUZ5o3tUn0p166FzwpVB1YxQEJVvJGv1IxVhM+BfNq3B86MIoBJsvU7ceQ9l8zlETvzz8KPtFKcNos27HhvPz6Nr1KOf+r728CKaK7Qt8kpEBz9eFpn/1kaMDmtIRdEQBv89FY5/aj69SRf19B7xzSuQjngvMqtpgLiB0a3lhA8GsFXPZHxkdYEtyPS38yKIZFGuRZsW7PrV4SumtTfMv5/owUIgiaZB6G1+esyNnL9gvSN+I+7ihrkYTLFvRdva1fJPMnCo8ckaOk3ZBSlyv+i341+Xs+sTZ/I9ChL4bF/GaKtDdMcQEHOLy36Jg9yZP9CZQnmCJ1e/LUxtbfq0f1Sx2kfnJQ36zIDL+JLy4kHt1V8H+37WKEn7cE3bmr4EK0IyYPl5fjeVWzzydrZfLeFXTsBT00zqTxScji2vI8qlrRMYrZ/GgSY2dtsYU+zDdEr025O8Yqze1U6t1Wtk6/yJ9vxUUohDLUUDzn0aNBt3O6+cuo6nhrSOXnGmt57sGoLwMyt0Kwpn3d2ntFi6VUCoxE6OUDOH45/NEGoEKC+F42fk6wWunfjyJ8pc9iatrWrqayiSvEQXd+LET9MOWHvd6YqofzaHJQKTK+ZmXuJicEkQ40eiZSXhL2hbKyYU7vIvzSntYmp47RINEsRug8x/0rHaXw0LFS7lA82Pdu7dzESUrGtv8r9uKQM5sQvnAvOkuqrRU6mNoU9mfv18JHrdnSlhXP5UbXT23boBbgDrtxSO9Xer1hAukVr2PgSzdjVU09WZG7P+D8hCchvJxJls64atK2Yo1q66p3SZPbnmCYlTfLNeQD04/bp2e2KI1BsslQgbClGJU1m3vqOIQgQjxtqhmmPUuBt5yInQF2JyL2IQ6SeceQagwsg+58x6pxtAw4B7aseLN+ec0RdBeVdxW0g6r1H7QnYLyZPwWxNGhTwZfqbHQXQbVdixDuFWbmxqkjnb+Etrd8gS6TZ9kF48DGCVP9kkA1FqRTecu19kdwcZtS3oh4m1xDmwf6ki111COtOsFKG9uVXx2F/U/rwwR91VhIGtAbVsBx/ZUmsYty1uF9tfURrY2exu77oViOzTeSDgteRDw79KKyyY5L/2bA2DoqNH8KcTIj/rfxo+acdWbShBdmT7QHblM4wekBYZYk8I9yB1Nffqd513UKux1IqBf6lGI/0Me8tvsItYDOEJgblandBM8hkFGEhNpGDtFt3Bnl26AKnTDcJAV9Dk4vHSM6IVqntjTDejdWlMM/er/jI9j1Ll8UGAWsWyglcGGyAYtnLcjyKJZDPE3etZB2n5iTCEhptFJB13C0sXw6VRmda9bcgRhm061O4YH7KQEv76jC3PSQnRGzSPI8PRZaw/Dk3YNkXxXc03Q1/AkcIcExJGea7kL40TKwzj/R8Cd5/HvzqhXQv/922VRhxFfPhPxi0gtQCr4MuwDe6pZAEloEWBMd7f0+TFEyjI7RuXcN/tEAxXXm07Msra5vYT5P5PR7iUELub4+NiCEaQ55vr5Cfag57f5bXDrQvuuPPuRt+kM7bZ3i1ukFzrxv5Q5uLh2akrF6a5d8ckWHJF8IcG1lt1sRbfEHVEAf/ltg71Jz3KBmi179b3WM7ajlNR1/2g9hL+wtWpASzGQ26sfDNg/w90VpSaWt1AUoATdx4zXRYa8hGKZI2HQfJ7itqL5roGTYYsDQbIzVbs9UjaKPMNKAYXQW/VXkLpH5iptcHgrA/IIDqgwAfC/BIXJr6GfOa0eSHY4Pqot4xGoYXjbEBcyeQ2PbyxlVWaC6QZWK3uNnJOV6sz80pnwHwKOUaZQcOghKAdeG0rXp+o2a+CEHK1ucOR4A8MezeGj6yL2b00weRhCmOjICTNHZkhq20BluA90kcvRImp/4BAs5jn74qKDlgkvq8xJ8jLdwSzgAPHsFHvnIdiEhZBk8I9lk7yni1MlUFFKtnBvmEjqiX35O1Kqr0LbruXC9KPm3ZZBTjmHoJBGNZQik7QuQulOuLoyQVbjuuYAndFgtFHNRiTMI7pWDWDOD7GJsyhSAR8bBCt0V2nRc+CAhwm44xdTb2V+JH9EklB1E4pOkRAoxOqzEsQB+OS1RWhd93mTg0FyyV7V5+EC5oSnd8SXhoHWx4uf+OrSRUGFu19M8rmBVQfaxEFcMgzgEcOh4wScVITK8DtF3Hph2bIAnPMypcK27wqX67shc1ipTMCeaI65OLxPABHT1icvgssh8kF+Sbvg1hByXQTzAN1UGPwyPoqZaXDCtHrFrjCAE4yPcqvweTAU7ayI5sUaTRxRUPiUchG3tjMJb+IAUI/QxBquUM/GQgUIZKQURspN79ggmXjskUj7mL1DjTaAcCfRljC5KbL/BOfVeqrJTUD2K+9v4erttUwNAQZvYdoUuICAURvct5oaThg10Tw3X3mL6QZbHPnL5Z7yBT6QAUvSZ4Q11h/lbagTw7s9jzG+al5FR5eTfQoAZ1yXjOn+MaD+Ns8CEnhwc5QABmqQqeHoBLAKundlueuoTAafB+NVZqpSjgKEEJpbSoMlRwbXJ6RRxcxreu7QDRmUfufL/aqKAM7EsL8gh2Ml1BDwixlyMG+Bx/PAhYzQVTmCpOFjkH6DViqpcbEJggIpnl8oOpx3FM7zdCjw82LHVi2IC1gb52ut3pFr73OJbPtP/uvMUPtuNFsSJ7v0zsBdC7qFV1v8D1Jha+teJgJH79tsCTDVqGuS5sf8FeEWRNkecmNDZLb++u+OQq/PXLBe/nrE8OCx7ieJCNKypLQvzAsac5YnD3LN1GcIFYcjY3jpRBR7N8c7hiXfALvRg0rgtP+6wSR3GghttUw8g1HSiW7CI1fs7S7S4HbbipeFPo+GO+RicDAcgpilxhY/CAqR022fm0HNAyY2akIVkoP3/T3bhY6l0AYtHm92aJVqio0C6FsxXfH1Cm1ruXz7xclYIKjquWExhPF6rqQqqu7Ny/tD5MFbJiVBCEbb2hA7mcPu+JFAuFFEyDR7mEcERk30AfdAOIKvXpaWxUgW+1LIQWjHAkamyWLk/AKrRdaB1WzClBs3lRWGt5dXWBDN5ZFf05YjC6tjqOAGAbpF6epAOjiQyZiHFeuVT3uxmw3s5EgoWAv9ICl0bczE6zhPr2kcZSDUN++0E9+QCCVMbo5R4I+1xfDrNyVdHwkMtSrb4YyXbtqGX0hU53DPSl46167f2qs916hfEL2W3JO7NU0ZwUP8IYeONSJVgQU/jTVxMNu/CoUTQZatzFsfZy7q9alDXgepe140OzjxbMRYPFl4bwoQDc5jOSRhqKgHtF1lf6l/2HQdnASoomIRHjiKScHKpBv8n/r10+cmE1F7wiSKbdbSmJFEVY3C+3FULU0wpJ5FoPBFvralxMAktxv5YSz+0zGFLcgXlSvuNRuH3ebZ/LAbGXYCet5cQ0Kza0phYfIiDeD81Cl/sdOQcPXDwp03eyUDzijOO9khdFOxbT7UF07/zOFWPnZoLVKH0Egx5MDu1Vx/ZidHMYD4q7qqZfjzR1akY4dEFceNE4ymHrfgM1aL9eZo84N/EFjgBLfDp+B69OwjrEd8VRIxCN6wVyv2nSF+DMI5gfGlGmyCvWm7OgKPxSgWFH3I8ZfqYWMdkT09e4CD4s9yL22wSJCb0KaFbf9fdewUC7eKiwJdN8KbPp+D38hlaNdjRfMTzKPklqOMMe0N59Ll08W/uBVgSquT098FyKr7kc4Ytka5FYft2zSGEEvUODfCxGOAe54U16YzImmnO0XKprYAD4ioZhSoHpf8RWMzZp8hYttLVUfapvOQxHd0oWt45pbZP9G/xsATGXkZMSOlr7gEomaDk8Al2QDbHQGqeok9viyTx+BU2glKx+PBd9kpPUvNZldK8aV7AFjOD7r370vOnmutLs7T7TnoIdbpPg8AxISBzkn+uZYO3OhCG+26WfWQY0kWu69Fx3oKCTlWyhQSQUoRGpMH/FGaDxKuxmvOlxmMIP6NwVJ8yt6C7xu9b28U27zRE7+p1VzLuEvGGXN2dWWwQJaqt+OMcZk1q2qA+RuasBtWl526oF8Qx7HaLZhBQN7c+BQQLeubwxUhrRSDCVp5H10BB4Dj08negAHLMhwuT1qiIVUNWS7bHPer2xHFh++LzYMCcg8EdPgC3EOkOCdfmZ4mBhcgPTg8LD9M/wtNw92mY+4kn5byfCdR+aG4uB7XYDPZzkA+rIuKkyniqhuCCHtrcle1chbeHju4vWkYM/6ORpj7jkNGJUbGMkENdhtmOds4TbyAKKmEyXaUvQwPUotPWh6cX5k+NiZjt84RDR6pMVUQDtp4IQDSX72XBdhAbfJpeSTxEC14nqXo0Nojkw/r58wAh+2ADFoMDOwkxA0MjKENTGP6w198oZZ5Iwu2jkXBgLSOjHlPd9ZFIqoNeo8SECXG0TfK5jpI3YJfZ6bmKcwR2QKrwJhdUV/1LIuXg7ZI8aEvu8v8+gGUvLBJ3l8APMPfjRf4QXW5jxsYdiCzXKZQldQuZzwWQJCD0YRGQZmWTxy294eeqKZMODy6X7nCX8uJLiD9J0Cf3yVzbx9pM+76sesv3yoYkqjl3C8rPUKcbwGBFep/TPduRpL9Rq5IXvKQEXOhHvP1iRNYEXNkz4GZxLitCiGw5wOAY3OOaOJyrW0aY1pGryciFHTMn9GOPOv+OZIqlLwVPbhg04Imt5wknnlBVAoz9oGEJoC/6mgauQcWgPPGbchdumAczccsmshvnrhOagXQles8cSRNBkTR8KjNjwTE5RB1aZkYQZYf0B0xsLgD8LroCHwqtjmxULzzv6zYxF/m3kMpRemhBNS5rAZm98sBwgJZDe5wTiufVeqzI0VCk7VfHR3jekKoumyslwSU/nlyxyF8iIzOvcwRcCOGeTGlZeQ/b8+RwZwZFHuQ/cRHxqy0qo+VVHOhbJbxq3dutHOiYADJySuMTlWhTEnP7hGI5qtMOTRvSBJS3liYg6QsFcB9/4rRJJEg7COyP/KxkYZKaFLoX4d4/nHT401d95J6PKn0lYCHThmGjAQEOxzbU68pXhr3jA7KLmVT+xUwyPK0TjroyApwSkCDJ/J57xx3u6wBDGjJjrp6nlwBDvUcpQ6wibNT5vdr8zErdmk8hcnYjNandyJ599Bw36ntoqvmiJOtfxBL4z54RA+wwzvKt6zcvIJdVnOh52cyLj2w9jK9eZSUVhr5lywku72A9gln1kEkoGBwnth3KcEb994T8sDfDS9VSkJeN5jBnK0E2M6GEHfbOXg+f9DyFH5ZzfhS07YFxcXp3kwh54io2qqdA5AvBFlNfCo7mSIesXZTNzKEc1CaXaGJ4BYGJmNUnsqYYeVw1yu2CZK/X5ioTK3WDtrBiG/nKrGT3ukRb8stPj+4Q39YjE/RAWz+MViAHJV6/soNHoCKfNzJQmkCxw688xsqTEaAeNgIAjsAXuuERmowRPOcThKyP7eh6r3oFRdge98GXnd0M+HAl4PmoPYJ1AuEsinFFrttutogUlE7JS2vI+emEDMPf8msRulLgrfPKVO9Iwwoy3A4TjRP7PZJZOCAOT+G4cgh4O9t/hIC3i51wI683VJkqPNE9SQW/AdMOgec1RSN4gzPMi1VLmFh0xdiQiEw3ENMGQOztTKmQLwsy0WoB5tsN+jLTL7j1cOh3DIunbK2idVPjkPlWHbwahP1EpuUZAPkpRfIZfqGnVOc71yYa1rupmHISxOOXCTS3Tj5mLkvH4bRVbxcpETce5H3jbciDFSDL1c7wg2kFKt3zpDVP39ZO6bOhWpluqHKVi2INSh9NZAscHaSxyJYbqOn2EiloXa9nUkjkTvgHv1A1uGnWZLiaLfg7BVMDHDeGRYD6eo+z3Jmpc2Iy5QNlvo3+mGGgG5LQAOcHBRPFAhpQK2Vlf83QZQvKgbMk0GHw6BcDM8zSlCSMo2Rc/TE3EDzZG9BOzI+Bzd5LqTVB5S0mLeAPJ6mEGBP0nfbOqd3HO+lBbCACBjfKPH4DBCBl3PSqHRoCz7Sv1fXwSZKRJ/5Sq5ELs55jtFrpbvV4EejkSXG5lHMUh6yZS1w/msTG24hyFmUw66SiIG+lsz2sSG90UqfK8NT5s1SnYAsaWdlZxBCuzFnxFwC2VsEht11tDhnyGYxPziROcqZZJ7CXA2jXLQhKqagFlObJDyKNM9VCBYZXmZ4M8vXHCGfhzORUM1mz/g9P15fl5RHJJeLj4ensbZJvJkjhzFzA0a7jcZ7KSJV1hpuXQt3kARx0KQBZBMGwAjDUw4pfuTdBq1+wr2b9xX3UcNl2yzSQbnJkhkk/kSqERPrBb/56g5pZiMNOvb+zx1GCrGV8eWjntqkq8VhjTetJrDFzQZsCog8BUetzNSAHCIbNTX/R8A4DQLE+4OveMEZgmxSJs4FjB7CLSU6SMEwbMoETPnG/DSg35kx+LioZGOq8MafHA88BShnl8i/AQeTS//VzXElWNJDLH9KLPxc/+WEOop4YW4ZuSg
*/